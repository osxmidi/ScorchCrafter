#ifndef SCORCHCRAFTER_MODULE_Stereo_split_INC
#define SCORCHCRAFTER_MODULE_Stereo_split_INC

#include "Scorchcrafter_Platform.hpp"

#include "EQ_xP.hpp"

using namespace ::ScorchCrafter;
using namespace ::ScorchCrafter::DataTypes;
using namespace ::ScorchCrafter::Base;
using namespace ::ScorchCrafter::Modules;

namespace ScorchCrafter
{
	namespace Modules
	{
		//! ----------------------------------------------------------------
		//! --- FX Component :: Stereo Splitter (Mono input to Stereo output) --
		//! ----------------------------------------------------------------
		struct SCRFT_EXPORT Mono_To_Stereo_Splitter
		{
			f64 fx_strength;
			const f64 stride_base;
			const f64 smoothing_frequency;
			const s32 buffer_position_reads;
			const f64 stride_multiplier_base;
			f64 stride_multiplier_inv;
			f64 sp_rate;
			f64* buffer;
			bool fx_auto_strength_enable;
			f64 fx_min_strength;
			f64 fx_max_strength;
			const f64 strength_smooth_frequency;
			s32 buffer_size;
			s32 buffer_padded_size;
			s32 pos;
			s32 stride_length;

			f64 spl_L, spl_R;

			EQ_LP f_diff_smooth;

			EQ_LP f_strength_smooth;

			inline void Clear()
			{
				f_diff_smooth.Clear();

				f_strength_smooth.Clear();

				spl_L = 0.0;
				spl_R = 0.0;
			}
			inline void SetSampleRate(const f64 &inp_rate)
			{
				sp_rate = (f64) inp_rate;
				if ( (!sp_rate) || (sp_rate < 44100.0) )
					sp_rate = 44100.0;
				if ( sp_rate > 16777216.0 )
					sp_rate = 16777216.0;

				pos = 0;
				if ( buffer )
					delete [] buffer;
				buffer = 0;

				const f64 stride_length_f64 = f64 (stride_base * sp_rate);
				stride_length = (s32) stride_length_f64;
				buffer_size = stride_length * (buffer_position_reads + 3);
				buffer_padded_size = stride_length * (buffer_position_reads + 4);

				buffer = new f64[buffer_padded_size];

				for ( s32 i = 0; i < buffer_padded_size; i++ )
					buffer[i] = 0.0;

				f_diff_smooth.SetSampleRate( sp_rate );
				f_diff_smooth.SetPassRate( smoothing_frequency );

				f_strength_smooth.SetSampleRate( sp_rate );
				f_strength_smooth.SetPassRate( smoothing_frequency );

				Clear();
			}
			inline void SetSampleRate()
			{
				if ( (!sp_rate) || (sp_rate < 44100.0) )
					sp_rate = 44100.0;
				if ( sp_rate > 16777216.0 )
					sp_rate = 16777216.0;

				pos = 0;
				if ( buffer )
					delete [] buffer;
				buffer = 0;

				const f64 stride_length_f64 = f64 (stride_base * sp_rate);
				stride_length = (s32) stride_length_f64;
				buffer_size = stride_length * (buffer_position_reads + 3);
				buffer_padded_size = stride_length * (buffer_position_reads + 4);

				buffer = new f64[buffer_padded_size];

				for ( s32 i = 0; i < buffer_padded_size; i++ )
					buffer[i] = 0.0;

				f_diff_smooth.SetSampleRate( sp_rate );
				f_diff_smooth.SetPassRate( strength_smooth_frequency );

				f_strength_smooth.SetSampleRate( sp_rate );
				f_strength_smooth.SetPassRate( smoothing_frequency );

				Clear();
			}
			inline void SetStrengthRange(const f64 inp_low = 0.0, const f64 inp_high = 1.0)
			{
				fx_min_strength = inp_low;
				fx_max_strength = inp_high;
			}
			inline void SetStrength(const f64 &inp)
			{
				const f64 fx_abs = scft_Abs64( inp );
				const f64 fx_new_strength = f_strength_smooth.Run( f64 ( (fx_abs > 1.0) ? 1.0 : fx_abs ) );

				fx_strength = scft_Avg64( fx_min_strength, fx_max_strength, fx_new_strength );

				stride_multiplier_inv = fx_strength / stride_multiplier_base;
			}
			inline void EnableAutoStrength(const bool inp = true)
			{
				fx_auto_strength_enable = (bool) inp;
			}
			inline void Run(const f64 &inp)
			{
				if ( !buffer )
					SetSampleRate();

				pos++;
				if ( pos >= buffer_size )
					pos = 0;
				buffer[pos] = inp;

				if ( fx_auto_strength_enable )
					SetStrength( inp );

				const f64 output_amp = f_diff_smooth.Run( scft_Abs64( inp ) );

				bool flip = true;
				f64 multiplier = stride_multiplier_base;
				s32 read_pos = pos;
				spl_L = 0.0;
				spl_R = 0.0;
				for ( s32 i = buffer_position_reads; i > 1; i -= 2 )
				{
					read_pos -= stride_length;
					if ( read_pos < 0 )
						read_pos += buffer_size;
					const f64 read_L = inp - buffer[read_pos];

					read_pos -= stride_length;
					if ( read_pos < 0 )
						read_pos += buffer_size;
					const f64 read_R = inp - buffer[read_pos];

					if ( !flip )
					{
						spl_L += read_L * multiplier;
						spl_R += read_R * multiplier;
					} else
					{
						spl_L -= read_L * multiplier;
						spl_R -= read_R * multiplier;
					}

					multiplier -= 1.0;
					flip = !flip;
				}

				spl_L *= output_amp * stride_multiplier_inv;
				spl_R *= output_amp * stride_multiplier_inv;
				spl_L += inp;
				spl_R += inp;
			}
			inline void GetOutputs(f64 SCRFT_RESTRICT_REF outp_L, f64 SCRFT_RESTRICT_REF outp_R)
			{
				outp_L = spl_L;
				outp_R = spl_R;
			}
			Mono_To_Stereo_Splitter(const f64 inp_fx_strength, // This value is a percentage of how strong the resulting stereo effect will be, this could be set up to 1.00 for 100% full effect
									const s32 inp_num_steps, // Should be an EVEN-numbered (divisible by 2) integer greater than zero, thank you...
									const f64 inp_stride_ms, // Time in milliseconds, default is 12.0 which is 12 ms
									const f64 inp_smoothing_frequency, // Should be low enough to be below typical audible frequencies (at a reasonable volume, of course)
									const f64 inp_strength_smooth_frequency = 12.0 // Should be low enough to be below typical audible frequencies (at a reasonable volume, of course)
									) :		// Initializers past here (broken up into multiple lines for readability)
				fx_strength( f64	(
										( (f64) inp_fx_strength < 0.0001 ) ?
											0.0001
										:
											(f64) inp_fx_strength
									) ),
				stride_base( f64	(
										0.001 *
										f64 (
												( (f64) inp_stride_ms < 0.25 ) ?
													0.25
												:
													(f64) inp_stride_ms
											)
									) ),
				smoothing_frequency( f64	(
												( (f64) inp_smoothing_frequency < 0.1 ) ?
													0.1
												:
													(f64) inp_smoothing_frequency
											) ),
				buffer_position_reads( s32	(
												( (s32) inp_num_steps < 2 ) ?
													2
												:
													(s32) inp_num_steps
											) ),
				stride_multiplier_base( f64 (buffer_position_reads / 2) ),
				stride_multiplier_inv( f64 (fx_strength / stride_multiplier_base) ),
				sp_rate( 44100.0 ),
				buffer( 0 ),
				fx_auto_strength_enable( false ),
				fx_min_strength( 0.0 ),
				fx_max_strength( 1.0 ),
				strength_smooth_frequency( (f64) inp_strength_smooth_frequency ),
				spl_L( 0.0 ),
				spl_R( 0.0 )
			{}
			~Mono_To_Stereo_Splitter()
			{
				if ( buffer )
					delete [] buffer;
				buffer = 0;
			}
		}; // struct Mono_To_Stereo_Splitter
		//! ----------------------------------------------------------------
		//! --- FX Component :: Stereo Splitter (Stereo input to Stereo output) --
		//! ----------------------------------------------------------------
		struct SCRFT_EXPORT Stereo_To_Stereo_Splitter
		{
			f64 fx_strength_L;
			f64 fx_strength_R;
			const f64 stride_base;
			const f64 smoothing_frequency;
			const s32 buffer_position_reads;
			const f64 stride_multiplier_base;
			f64 stride_multiplier_inv_L;
			f64 stride_multiplier_inv_R;
			f64 sp_rate;
			f64* buffer_L;
			f64* buffer_R;
			bool fx_auto_strength_enable;
			f64 fx_min_strength;
			f64 fx_max_strength;
			const f64 strength_smooth_frequency;
			s32 buffer_size;
			s32 buffer_padded_size;
			s32 pos;
			s32 stride_length;

			f64 spl_L, spl_R;

			EQ_LP f_diff_smooth[2];

			EQ_LP f_strength_smooth[2];

			inline void Clear()
			{
				f_diff_smooth[0].Clear();
				f_diff_smooth[1].Clear();

				f_strength_smooth[0].Clear();
				f_strength_smooth[1].Clear();

				spl_L = 0.0;
				spl_R = 0.0;
			}
			inline void SetSampleRate(const f64 inp_rate)
			{
				sp_rate = (f64) inp_rate;
				if ( (!sp_rate) || (sp_rate < 44100.0) )
					sp_rate = 44100.0;
				if ( sp_rate > 16777216.0 )
					sp_rate = 16777216.0;

				pos = 0;
				if ( buffer_L )
					delete [] buffer_L;
				if ( buffer_R )
					delete [] buffer_R;
				buffer_L = 0;
				buffer_R = 0;

				const f64 stride_length_f64 = f64 (stride_base * sp_rate);
				stride_length = (s32) stride_length_f64;
				buffer_size = stride_length * (buffer_position_reads + 3);
				buffer_padded_size = stride_length * (buffer_position_reads + 4);

				buffer_L = new f64[buffer_padded_size];
				buffer_R = new f64[buffer_padded_size];

				for ( s32 i = 0; i < buffer_padded_size; i++ )
				{
					buffer_L[i] = 0.0;
					buffer_R[i] = 0.0;
				}

				f_diff_smooth[0].SetSampleRate( sp_rate );
				f_diff_smooth[0].SetPassRate( smoothing_frequency );
				f_diff_smooth[1].SetSampleRate( sp_rate );
				f_diff_smooth[1].SetPassRate( smoothing_frequency );

				f_strength_smooth[0].SetSampleRate( sp_rate );
				f_strength_smooth[0].SetPassRate( smoothing_frequency );
				f_strength_smooth[1].SetSampleRate( sp_rate );
				f_strength_smooth[1].SetPassRate( smoothing_frequency );

				Clear();
			}
			inline void SetSampleRate()
			{
				if ( (!sp_rate) || (sp_rate < 44100.0) )
					sp_rate = 44100.0;
				if ( sp_rate > 16777216.0 )
					sp_rate = 16777216.0;

				pos = 0;
				if ( buffer_L )
					delete [] buffer_L;
				if ( buffer_R )
					delete [] buffer_R;
				buffer_L = 0;
				buffer_R = 0;

				const f64 stride_length_f64 = f64 (stride_base * sp_rate);
				stride_length = (s32) stride_length_f64;
				buffer_size = stride_length * (buffer_position_reads + 3);
				buffer_padded_size = stride_length * (buffer_position_reads + 4);

				buffer_L = new f64[buffer_padded_size];
				buffer_R = new f64[buffer_padded_size];

				for ( s32 i = 0; i < buffer_padded_size; i++ )
				{
					buffer_L[i] = 0.0;
					buffer_R[i] = 0.0;
				}

				f_diff_smooth[0].SetSampleRate( sp_rate );
				f_diff_smooth[0].SetPassRate( smoothing_frequency );
				f_diff_smooth[1].SetSampleRate( sp_rate );
				f_diff_smooth[1].SetPassRate( smoothing_frequency );

				f_strength_smooth[0].SetSampleRate( sp_rate );
				f_strength_smooth[0].SetPassRate( smoothing_frequency );
				f_strength_smooth[1].SetSampleRate( sp_rate );
				f_strength_smooth[1].SetPassRate( smoothing_frequency );

				Clear();
			}
			inline void SetStrengthRange(const f64 inp_low = 0.0, const f64 inp_high = 1.0)
			{
				fx_min_strength = inp_low;
				fx_max_strength = inp_high;
			}
			inline void SetStrength(const f64 &inp_L, const f64 &inp_R)
			{
				const f64 fx_L = scft_Abs64( inp_L );
				const f64 fx_R = scft_Abs64( inp_R );

				const f64 fx_new_strength_L = f_strength_smooth[0].Run( f64 ( (fx_L > 1.0) ? 1.0 : fx_L ) );
				const f64 fx_new_strength_R = f_strength_smooth[1].Run( f64 ( (fx_R > 1.0) ? 1.0 : fx_R ) );

				fx_strength_L = scft_Avg64( fx_min_strength, fx_max_strength, fx_new_strength_L );
				fx_strength_R = scft_Avg64( fx_min_strength, fx_max_strength, fx_new_strength_R );

				stride_multiplier_inv_L = fx_strength_L / stride_multiplier_base;
				stride_multiplier_inv_R = fx_strength_R / stride_multiplier_base;
			}
			inline void EnableAutoStrength(const bool inp = true)
			{
				fx_auto_strength_enable = inp;
			}
			inline void Run(const f64 &inp_L, const f64 &inp_R)
			{
				if ( (!buffer_L) || (!buffer_R) )
					SetSampleRate();

				pos++;
				if ( pos >= buffer_size )
					pos = 0;
				buffer_L[pos] = inp_L;
				buffer_R[pos] = inp_R;

				if ( fx_auto_strength_enable )
					SetStrength( inp_L, inp_R );

				const f64 output_amp_L = f_diff_smooth[0].Run( scft_Abs64( inp_L ) );
				const f64 output_amp_R = f_diff_smooth[1].Run( scft_Abs64( inp_R ) );

				bool flip = true;
				f64 multiplier = stride_multiplier_base;
				s32 read_pos = pos;
				spl_L = 0.0;
				spl_R = 0.0;
				for ( s32 i = buffer_position_reads; i > 1; i -= 2 )
				{
					read_pos -= stride_length;
					if ( read_pos < 0 )
						read_pos += buffer_size;
					const f64 read_L = inp_L - buffer_L[read_pos];

					read_pos -= stride_length;
					if ( read_pos < 0 )
						read_pos += buffer_size;
					const f64 read_R = inp_R - buffer_R[read_pos];

					if ( !flip )
					{
						spl_L += read_L * multiplier;
						spl_R += read_R * multiplier;
					} else
					{
						spl_L -= read_L * multiplier;
						spl_R -= read_R * multiplier;
					}

					multiplier -= 1.0;
					flip = !flip;
				}

				spl_L *= output_amp_L * stride_multiplier_inv_L;
				spl_R *= output_amp_R * stride_multiplier_inv_R;
				spl_L += inp_L;
				spl_R += inp_R;
			}
			inline void GetOutputs(f64 SCRFT_RESTRICT_REF outp_L, f64 SCRFT_RESTRICT_REF outp_R)
			{
				outp_L = spl_L;
				outp_R = spl_R;
			}
			Stereo_To_Stereo_Splitter(const f64 inp_fx_strength, // This value is a percentage of how strong the resulting stereo effect will be, this could be set up to 1.00 for 100% full effect
									const s32 inp_num_steps, // Should be an EVEN-numbered (divisible by 2) integer greater than zero, thank you...
									const f64 inp_stride_ms, // Time in milliseconds, default is 12.0 which is 12 ms
									const f64 inp_smoothing_frequency, // Should be low enough to be below typical audible frequencies (at a reasonable volume, of course)
									const f64 inp_strength_smooth_frequency = 12.0 // Should be low enough to be below typical audible frequencies (at a reasonable volume, of course)
									) :		// Initializers past here (broken up into multiple lines for readability)
				fx_strength_L( f64	(
										( (f64) inp_fx_strength < 0.0001 ) ?
											0.0001
										:
											(f64) inp_fx_strength
									) ),
				fx_strength_R( f64	(
										( (f64) inp_fx_strength < 0.0001 ) ?
											0.0001
										:
											(f64) inp_fx_strength
									) ),
				stride_base( f64	(
										0.001 *
										f64 (
												( (f64) inp_stride_ms < 0.25 ) ?
													0.25
												:
													(f64) inp_stride_ms
											)
									) ),
				smoothing_frequency( f64	(
												( (f64) inp_smoothing_frequency < 0.1 ) ?
													0.1
												:
													(f64) inp_smoothing_frequency
											) ),
				buffer_position_reads( s32	(
												( (s32) inp_num_steps < 2 ) ?
													2
												:
													(s32) inp_num_steps
											) ),
				stride_multiplier_base( f64 (buffer_position_reads / 2) ),
				stride_multiplier_inv_L( f64 (fx_strength_L / stride_multiplier_base) ),
				stride_multiplier_inv_R( f64 (fx_strength_R / stride_multiplier_base) ),
				sp_rate( 44100.0 ),
				buffer_L( 0 ),
				buffer_R( 0 ),
				fx_auto_strength_enable( false ),
				fx_min_strength( 0.0 ),
				fx_max_strength( 1.0 ),
				strength_smooth_frequency( (f64) inp_strength_smooth_frequency ),
				spl_L( 0.0 ),
				spl_R( 0.0 )
			{}
			~Stereo_To_Stereo_Splitter()
			{
				if ( buffer_L )
					delete [] buffer_L;
				if ( buffer_R )
					delete [] buffer_R;
				buffer_L = 0;
				buffer_R = 0;
			}
		}; // struct Stereo_To_Stereo_Splitter

	} // namespace Modules
} // namespace ScorchCrafter

#endif // SCORCHCRAFTER_MODULE_Stereo_split_INC
