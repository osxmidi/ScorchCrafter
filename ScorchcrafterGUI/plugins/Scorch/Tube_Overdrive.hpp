#ifndef SCORCHCRAFTER_MODULE_Tube_Overdrive_INC
#define SCORCHCRAFTER_MODULE_Tube_Overdrive_INC

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
		//! --- FX Component :: Tube Overdrive Channel :: Tube Grit FX --
		//! ----------------------------------------------------------------
		struct SCRFT_EXPORT Tube_Grit_Fx
		{
			s32 prm_set;

			f64 p_fx_multiplier,
				p_fx_factor,
				p_fx_read_multiplier,
				p_fx_read_factor;

			f64 spl_fx;

			EQ_HP f0_wave_HP, f1_wave_HP, f2_wave_HP, f3_wave_HP;
			EQ_LP f0_wave_LP, f1_wave_LP;
			EQ_LP f0_wave2_LP, f1_wave2_LP;

			EQ_LP f0_read_LP, f1_read_LP;

			inline void Clear()
			{
				spl_fx = 0.0;

				f0_wave_HP.Clear();
				f1_wave_HP.Clear();
				f2_wave_HP.Clear();
				f3_wave_HP.Clear();

				f0_wave_LP.Clear();
				f1_wave_LP.Clear();

				f0_wave2_LP.Clear();
				f1_wave2_LP.Clear();

				f0_read_LP.Clear();
				f1_read_LP.Clear();
			}
			void SetSampleRate(const f64 &nRate)
			{
				f0_wave_HP.SetSampleRate( nRate );
				f1_wave_HP.SetSampleRate( nRate );
				f2_wave_HP.SetSampleRate( nRate );
				f3_wave_HP.SetSampleRate( nRate );

				f0_wave_LP.SetSampleRate( nRate );
				f1_wave_LP.SetSampleRate( nRate );

				f0_wave2_LP.SetSampleRate( nRate );
				f1_wave2_LP.SetSampleRate( nRate );

				f0_read_LP.SetSampleRate( nRate );
				f1_read_LP.SetSampleRate( nRate );

				Clear();
			}
			inline void SetGain(const f64 &inp)
			{
				return;

/*				const f64 base_gain = scft_Clamp64( inp, 0.0, 1.0 );

				const f64 skewed_gain = base_gain * base_gain * 0.75;

				prm_gain = 0.25 + skewed_gain;	*/
			}
			inline f64 Run(const f64 &inp)
			{
				if ( prm_set < 0 )
					return 0.0;

		//		f64 spl_wave = ( inp < 0.0 ) ? -1.0 : 1.0;

		//		f0_wave_LP.RunFx( spl_wave );
		//		f1_wave_LP.RunFx( spl_wave );

				f64 spl_wave = (f64) inp;

				f0_wave_HP.RunFx( spl_wave );
				f1_wave_HP.RunFx( spl_wave );
				f2_wave_HP.RunFx( spl_wave );
				f3_wave_HP.RunFx( spl_wave );

				f64 spl_read = spl_wave;

		//		spl_wave = ( (spl_wave > -0.000012) && (spl_wave < 0.000012) ) ? 0.0 : (( spl_wave < 0.0 ) ? -1.0 : 1.0);
				spl_wave = ( spl_wave > 0.0 ) ? 1.0 : -1.0;

				f0_wave_LP.RunFx( spl_wave );
				f1_wave_LP.RunFx( spl_wave );

				spl_wave = scft_ExpFx64( spl_wave * p_fx_multiplier, p_fx_factor );

				f0_wave2_LP.RunFx( spl_wave );
				f1_wave2_LP.RunFx( spl_wave );

				spl_read = scft_ExpFxA64( spl_read * p_fx_read_multiplier, p_fx_read_factor );
				f0_read_LP.RunFx( spl_read );
				f1_read_LP.RunFx( spl_read );

				spl_fx = scft_Avg64( 0.0, (1.0 - spl_wave) * 0.5 , spl_read );

				return spl_fx;
			}
			inline f64 GetOutput() const
			{
				return spl_fx;
			}
			Tube_Grit_Fx(const s32 inp_prm_set = 0) :
				prm_set( inp_prm_set ),

				p_fx_multiplier( 12.0 ),
				p_fx_factor( 1.2045 ),
				p_fx_read_multiplier( 120.0 ),
				p_fx_read_factor( 1.2045 ),

				spl_fx( 0.0 )
			{
				f64 freq_wave_LP = 60.0;
				f64 freq_wave2_LP = 60.0;
				f64 freq_wave_HP = 12.0;

				f64 freq_read_LP = 12.0;

				if ( prm_set == 1 )
				{
					freq_wave_LP = 12.0;
					freq_wave2_LP = 12.0;
					freq_wave_HP = 120.0;

					freq_read_LP = 12.0;

					p_fx_multiplier = 12.0;
					p_fx_factor = 1200.0;
					p_fx_read_multiplier = 0.7500;
					p_fx_read_factor = 120.0;
				} else
				if ( prm_set == 2 )
				{
					freq_wave_LP = 12.0;
					freq_wave2_LP = 12.0;
					freq_wave_HP = 120.0;

					freq_read_LP = 12.0;

					p_fx_multiplier = 12.0;
					p_fx_factor = 1200.0;
					p_fx_read_multiplier = 0.7500;
					p_fx_read_factor = 120.0;
				} else
				if ( prm_set == 3 )
				{
					freq_wave_LP = 12.0;
					freq_wave2_LP = 12.0;
					freq_wave_HP = 120.0;

					freq_read_LP = 12.0;

					p_fx_multiplier = 12.0;
					p_fx_factor = 1200.0;
					p_fx_read_multiplier = 0.7500;
					p_fx_read_factor = 120.0;
				}

				f0_wave_HP.SetPassRate( freq_wave_HP );
				f1_wave_HP.SetPassRate( freq_wave_HP );
				f2_wave_HP.SetPassRate( freq_wave_HP );
				f3_wave_HP.SetPassRate( freq_wave_HP );

				f0_wave_LP.SetPassRate( freq_wave_LP );
				f1_wave_LP.SetPassRate( freq_wave_LP );

				f0_wave2_LP.SetPassRate( freq_wave2_LP );
				f1_wave2_LP.SetPassRate( freq_wave2_LP );

				f0_read_LP.SetPassRate( freq_read_LP );
				f1_read_LP.SetPassRate( freq_read_LP );

				SetSampleRate( (f64) 44100.0 );
			};
		}; // struct Tube_Grit_Fx
		//! ----------------------------------------------------------------
		//! --- FX Component :: Tube Overdrive Channel :: Tube --
		//! ----------------------------------------------------------------
		struct SCRFT_EXPORT Tube
		{
			// ID for Which set of parameters are used (Not all tube types use this)
			s32 prm_set;

			// Fixed parameters (Set at initialization, shouldn't be changed afterwards)
			f64 p_input_read_volume,
				p_input_vol_adjust, p_output_vol_adjust,
				p_buffer_range, p_dry_range,
				p_grit_low_adjust,
				p_gain_pre_clip_adjust,
				p_gain_clipping_curve,
				p_feedback_volume,
				p_min_bass, p_max_bass;

			// Dynamic parameters (Updated frequently while audio effect is loaded and running)
			f64 prm_gain;

			// Feedback buffer(s)
			f64 spl_buffer,
				spl_feedback;

			// EQ Filters
			EQ_LP f0_read_LP, f1_read_LP;

			EQ_LP f0_grit_high_LP, f1_grit_high_LP, f2_grit_high_LP, f3_grit_high_LP;
			EQ_LP f0_grit_low_LP, f1_grit_low_LP, f2_grit_low_LP, f3_grit_low_LP;
			EQ_DP f0_grit_high_DP, f1_grit_high_DP, f2_grit_high_DP, f3_grit_high_DP;
			EQ_DP f0_grit_low_DP, f1_grit_low_DP, f2_grit_low_DP, f3_grit_low_DP;

			EQ_HP f0_drive_HP, f1_drive_HP, f2_drive_HP, f3_drive_HP;
			EQ_LP f0_drive_LP, f1_drive_LP, f2_drive_LP, f3_drive_LP;

			EQ_HP f0_buffer_HP, f1_buffer_HP, f2_buffer_HP, f3_buffer_HP;
			EQ_LP f0_buffer_LP, f1_buffer_LP, f2_buffer_LP, f3_buffer_LP;

			EQ_LP f0_buffer_out_LP, f1_buffer_out_LP, f2_buffer_out_LP, f3_buffer_out_LP;

			EQ_LP f0_gain_inp_LP, f1_gain_inp_LP, f2_gain_inp_LP, f3_gain_inp_LP;

			EQ_LP f0_dist_LP, f1_dist_LP, f2_dist_LP, f3_dist_LP;
			EQ_DP f0_diff_DP, f1_diff_DP, f2_diff_DP, f3_diff_DP;
			EQ_DP f0_dist_DP, f1_dist_DP, f2_dist_DP, f3_dist_DP;

			EQ_HP f0_feedback_HP, f1_feedback_HP, f2_feedback_HP, f3_feedback_HP;
			EQ_LP f0_feedback_LP, f1_feedback_LP, f2_feedback_LP, f3_feedback_LP;

			EQ_LP f0_x_bass_LP, f1_x_bass_LP, f2_x_bass_LP, f3_x_bass_LP;
			EQ_DP f0_x_bass_DP, f1_x_bass_DP, f2_x_bass_DP, f3_x_bass_DP;

			EQ_HP f0_output_HP, f1_output_HP, f2_output_HP, f3_output_HP;
			EQ_LP f0_output_LP, f1_output_LP, f2_output_LP, f3_output_LP;

			inline void Clear()
			{
				spl_buffer = 0.0;
				spl_feedback = 0.0;

				f0_read_LP.Clear(); f1_read_LP.Clear();

				f0_grit_high_LP.Clear(); f1_grit_high_LP.Clear(); f2_grit_high_LP.Clear(); f3_grit_high_LP.Clear();
				f0_grit_low_LP.Clear(); f1_grit_low_LP.Clear(); f2_grit_low_LP.Clear(); f3_grit_low_LP.Clear();
				f0_grit_high_DP.Clear(); f1_grit_high_DP.Clear(); f2_grit_high_DP.Clear(); f3_grit_high_DP.Clear();
				f0_grit_low_DP.Clear(); f1_grit_low_DP.Clear(); f2_grit_low_DP.Clear(); f3_grit_low_DP.Clear();

				f0_drive_HP.Clear(); f1_drive_HP.Clear(); f2_drive_HP.Clear(); f3_drive_HP.Clear();
				f0_drive_LP.Clear(); f1_drive_LP.Clear(); f2_drive_LP.Clear(); f3_drive_LP.Clear();

				f0_buffer_HP.Clear(); f1_buffer_HP.Clear(); f2_buffer_HP.Clear(); f3_buffer_HP.Clear();
				f0_buffer_LP.Clear(); f1_buffer_LP.Clear(); f2_buffer_LP.Clear(); f3_buffer_LP.Clear();

				f0_buffer_out_LP.Clear(); f1_buffer_out_LP.Clear(); f2_buffer_out_LP.Clear(); f3_buffer_out_LP.Clear();

				f0_gain_inp_LP.Clear(); f1_gain_inp_LP.Clear(); f2_gain_inp_LP.Clear(); f3_gain_inp_LP.Clear();

				f0_dist_LP.Clear(); f1_dist_LP.Clear(); f2_dist_LP.Clear(); f3_dist_LP.Clear();
				f0_diff_DP.Clear(); f1_diff_DP.Clear(); f2_diff_DP.Clear(); f3_diff_DP.Clear();
				f0_dist_DP.Clear(); f1_dist_DP.Clear(); f2_dist_DP.Clear(); f3_dist_DP.Clear();

				f0_feedback_HP.Clear(); f1_feedback_HP.Clear(); f2_feedback_HP.Clear(); f3_feedback_HP.Clear();
				f0_feedback_LP.Clear(); f1_feedback_LP.Clear(); f2_feedback_LP.Clear(); f3_feedback_LP.Clear();

				f0_x_bass_LP.Clear(); f1_x_bass_LP.Clear(); f2_x_bass_LP.Clear(); f3_x_bass_LP.Clear();
				f0_x_bass_DP.Clear(); f1_x_bass_DP.Clear(); f2_x_bass_DP.Clear(); f3_x_bass_DP.Clear();

				f0_output_HP.Clear(); f1_output_HP.Clear(); f2_output_HP.Clear(); f3_output_HP.Clear();
				f0_output_LP.Clear(); f1_output_LP.Clear(); f2_output_LP.Clear(); f3_output_LP.Clear();
			}
			void SetSampleRate(const f64 &nRate)
			{
				spl_buffer = 0.0;
				spl_feedback = 0.0;

				f0_read_LP.SetSampleRate( nRate ); f1_read_LP.SetSampleRate( nRate );

				f0_grit_high_LP.SetSampleRate( nRate ); f1_grit_high_LP.SetSampleRate( nRate ); f2_grit_high_LP.SetSampleRate( nRate ); f3_grit_high_LP.SetSampleRate( nRate );
				f0_grit_low_LP.SetSampleRate( nRate ); f1_grit_low_LP.SetSampleRate( nRate ); f2_grit_low_LP.SetSampleRate( nRate ); f3_grit_low_LP.SetSampleRate( nRate );
				f0_grit_high_DP.SetSampleRate( nRate ); f1_grit_high_DP.SetSampleRate( nRate ); f2_grit_high_DP.SetSampleRate( nRate ); f3_grit_high_DP.SetSampleRate( nRate );
				f0_grit_low_DP.SetSampleRate( nRate ); f1_grit_low_DP.SetSampleRate( nRate ); f2_grit_low_DP.SetSampleRate( nRate ); f3_grit_low_DP.SetSampleRate( nRate );

				f0_drive_HP.SetSampleRate( nRate ); f1_drive_HP.SetSampleRate( nRate ); f2_drive_HP.SetSampleRate( nRate ); f3_drive_HP.SetSampleRate( nRate );
				f0_drive_LP.SetSampleRate( nRate ); f1_drive_LP.SetSampleRate( nRate ); f2_drive_LP.SetSampleRate( nRate ); f3_drive_LP.SetSampleRate( nRate );

				f0_buffer_HP.SetSampleRate( nRate ); f1_buffer_HP.SetSampleRate( nRate ); f2_buffer_HP.SetSampleRate( nRate ); f3_buffer_HP.SetSampleRate( nRate );
				f0_buffer_LP.SetSampleRate( nRate ); f1_buffer_LP.SetSampleRate( nRate ); f2_buffer_LP.SetSampleRate( nRate ); f3_buffer_LP.SetSampleRate( nRate );

				f0_buffer_out_LP.SetSampleRate( nRate ); f1_buffer_out_LP.SetSampleRate( nRate ); f2_buffer_out_LP.SetSampleRate( nRate ); f3_buffer_out_LP.SetSampleRate( nRate );

				f0_gain_inp_LP.SetSampleRate( nRate ); f1_gain_inp_LP.SetSampleRate( nRate ); f2_gain_inp_LP.SetSampleRate( nRate ); f3_gain_inp_LP.SetSampleRate( nRate );

				f0_dist_LP.SetSampleRate( nRate ); f1_dist_LP.SetSampleRate( nRate ); f2_dist_LP.SetSampleRate( nRate ); f3_dist_LP.SetSampleRate( nRate );
				f0_diff_DP.SetSampleRate( nRate ); f1_diff_DP.SetSampleRate( nRate ); f2_diff_DP.SetSampleRate( nRate ); f3_diff_DP.SetSampleRate( nRate );
				f0_dist_DP.SetSampleRate( nRate ); f1_dist_DP.SetSampleRate( nRate ); f2_dist_DP.SetSampleRate( nRate ); f3_dist_DP.SetSampleRate( nRate );

				f0_feedback_HP.SetSampleRate( nRate ); f1_feedback_HP.SetSampleRate( nRate ); f2_feedback_HP.SetSampleRate( nRate ); f3_feedback_HP.SetSampleRate( nRate );
				f0_feedback_LP.SetSampleRate( nRate ); f1_feedback_LP.SetSampleRate( nRate ); f2_feedback_LP.SetSampleRate( nRate ); f3_feedback_LP.SetSampleRate( nRate );

				f0_x_bass_LP.SetSampleRate( nRate ); f1_x_bass_LP.SetSampleRate( nRate ); f2_x_bass_LP.SetSampleRate( nRate ); f3_x_bass_LP.SetSampleRate( nRate );
				f0_x_bass_DP.SetSampleRate( nRate ); f1_x_bass_DP.SetSampleRate( nRate ); f2_x_bass_DP.SetSampleRate( nRate ); f3_x_bass_DP.SetSampleRate( nRate );

				f0_output_HP.SetSampleRate( nRate ); f1_output_HP.SetSampleRate( nRate ); f2_output_HP.SetSampleRate( nRate ); f3_output_HP.SetSampleRate( nRate );
				f0_output_LP.SetSampleRate( nRate ); f1_output_LP.SetSampleRate( nRate ); f2_output_LP.SetSampleRate( nRate ); f3_output_LP.SetSampleRate( nRate );
			}
			void Init()
			{
				prm_gain = 0.0;
				spl_buffer = 0.0;
				spl_feedback = 0.0;

				f64 freq_read_LP = 12.0;
				f64 freq_grit_high_LP = 7200.0;
				f64 freq_grit_low_LP = 1200.0;
				f64 freq_drive_HP = 500.0;
				f64 freq_drive_LP = 5000.0;
				f64 freq_buffer_HP = 12.0;
				f64 freq_buffer_LP = 1200.0;
				f64 freq_buffer_out_LP = 7500.0;
				f64 freq_gain_inp_LP = 7500.0;
				f64 freq_dist_LP = 16500.0;
				f64 freq_feedback_HP = 12.0;
				f64 freq_feedback_LP = 1200.0;
				f64 freq_x_bass = 120.0;
				f64 freq_output_HP = 12.0;
				f64 freq_output_LP = 20000.0;

				if ( prm_set == 1 )
				{
					p_input_read_volume = 12.5013;
					p_input_vol_adjust = 0.9300;
					p_output_vol_adjust = 1.2045;
					p_buffer_range = 5.0124;
					p_dry_range = 2.7210;
					p_grit_low_adjust = 0.5025;
					p_gain_pre_clip_adjust = 1.8012;
					p_gain_clipping_curve = 2.5023;
					p_feedback_volume = 0.7500;
					p_min_bass =  0.3243;
					p_max_bass = -0.3243;

					freq_read_LP = 12.0;
					freq_grit_high_LP = 12000.0;
					freq_grit_low_LP = 5000.0;
					freq_drive_HP = 500.0;
					freq_drive_LP = 5000.0;
					freq_buffer_HP = 12.0;
					freq_buffer_LP = 1200.0;
					freq_buffer_out_LP = 5000.0;
					freq_gain_inp_LP = 7120.0;
					freq_dist_LP = 14250.0;
					freq_feedback_HP = 12.0;
					freq_feedback_LP = 5000.0;
					freq_x_bass = 120.0;
					freq_output_HP = 12.0;
					freq_output_LP = 9000.0;
				} else
				if ( prm_set == 2 )
				{
					p_input_read_volume = 7.0023;
					p_input_vol_adjust = 0.9012;
					p_output_vol_adjust = 0.9300;
					p_buffer_range = 5.2500;
					p_dry_range = 4.1205;
					p_grit_low_adjust = 0.5025;
					p_gain_pre_clip_adjust = 1.9200;
					p_gain_clipping_curve = 3.2412;
					p_feedback_volume = 0.9012;
					p_min_bass =  0.2910;
					p_max_bass = -0.2910;

					freq_read_LP = 12.0;
					freq_grit_high_LP = 12000.0;
					freq_grit_low_LP = 5000.0;
					freq_drive_HP = 500.0;
					freq_drive_LP = 5000.0;
					freq_buffer_HP = 12.0;
					freq_buffer_LP = 1200.0;
					freq_buffer_out_LP = 5000.0;
					freq_gain_inp_LP = 7120.0;
					freq_dist_LP = 14250.0;
					freq_feedback_HP = 12.0;
					freq_feedback_LP = 5000.0;
					freq_x_bass = 120.0;
					freq_output_HP = 12.0;
					freq_output_LP = 9000.0;
				} else
				if ( prm_set == 3 )
				{
					p_input_read_volume = 7.0023;
					p_input_vol_adjust = 0.9012;
					p_output_vol_adjust = 0.9300;
					p_buffer_range = 5.2500;
					p_dry_range = 4.1205;
					p_grit_low_adjust = 0.5025;
					p_gain_pre_clip_adjust = 2.4150;
					p_gain_clipping_curve = 3.6012;
					p_feedback_volume = 0.9012;
					p_min_bass =  0.2613;
					p_max_bass = -0.2613;

					freq_read_LP = 12.0;
					freq_grit_high_LP = 12000.0;
					freq_grit_low_LP = 5000.0;
					freq_drive_HP = 500.0;
					freq_drive_LP = 5000.0;
					freq_buffer_HP = 12.0;
					freq_buffer_LP = 1200.0;
					freq_buffer_out_LP = 5000.0;
					freq_gain_inp_LP = 7120.0;
					freq_dist_LP = 14250.0;
					freq_feedback_HP = 12.0;
					freq_feedback_LP = 5000.0;
					freq_x_bass = 120.0;
					freq_output_HP = 12.0;
					freq_output_LP = 9000.0;
				} else
				if ( prm_set == 4 )
				{
					p_input_read_volume = 9.1200;
					p_input_vol_adjust = 0.9012;
					p_output_vol_adjust = 0.9300;
					p_buffer_range = 5.0025;
					p_dry_range = 3.9000;
					p_grit_low_adjust = 0.9012;
					p_gain_pre_clip_adjust = 1.2450;
					p_gain_clipping_curve = 12.0;
					p_feedback_volume = 0.9012;
					p_min_bass =  0.2613;
					p_max_bass = -0.2613;

					freq_read_LP = 12.0;
					freq_grit_high_LP = 7200.0;
					freq_grit_low_LP = 1200.0;
					freq_drive_HP = 500.0;
					freq_drive_LP = 5000.0;
					freq_buffer_HP = 12.0;
					freq_buffer_LP = 1200.0;
					freq_buffer_out_LP = 5000.0;
					freq_gain_inp_LP = 7120.0;
					freq_dist_LP = 16500.0;
					freq_feedback_HP = 12.0;
					freq_feedback_LP = 1200.0;
					freq_x_bass = 120.0;
					freq_output_HP = 12.0;
					freq_output_LP = 9000.0;
				}

				f0_read_LP.SetPassRate( freq_read_LP );
				f1_read_LP.SetPassRate( freq_read_LP );

				f0_grit_high_LP.SetPassRate( freq_grit_high_LP );
				f1_grit_high_LP.SetPassRate( freq_grit_high_LP );
				f2_grit_high_LP.SetPassRate( freq_grit_high_LP );
				f3_grit_high_LP.SetPassRate( freq_grit_high_LP );
				f0_grit_high_DP.SetPassRate( freq_grit_high_LP );
				f1_grit_high_DP.SetPassRate( freq_grit_high_LP );
				f2_grit_high_DP.SetPassRate( freq_grit_high_LP );
				f3_grit_high_DP.SetPassRate( freq_grit_high_LP );
				f0_grit_low_LP.SetPassRate( freq_grit_low_LP );
				f1_grit_low_LP.SetPassRate( freq_grit_low_LP );
				f2_grit_low_LP.SetPassRate( freq_grit_low_LP );
				f3_grit_low_LP.SetPassRate( freq_grit_low_LP );
				f0_grit_low_DP.SetPassRate( freq_grit_low_LP );
				f1_grit_low_DP.SetPassRate( freq_grit_low_LP );
				f2_grit_low_DP.SetPassRate( freq_grit_low_LP );
				f3_grit_low_DP.SetPassRate( freq_grit_low_LP );

				f0_drive_HP.SetPassRate( freq_drive_HP );
				f1_drive_HP.SetPassRate( freq_drive_HP );
				f2_drive_HP.SetPassRate( freq_drive_HP );
				f3_drive_HP.SetPassRate( freq_drive_HP );
				f0_drive_LP.SetPassRate( freq_drive_LP );
				f1_drive_LP.SetPassRate( freq_drive_LP );
				f2_drive_LP.SetPassRate( freq_drive_LP );
				f3_drive_LP.SetPassRate( freq_drive_LP );

				f0_buffer_HP.SetPassRate( freq_buffer_HP );
				f1_buffer_HP.SetPassRate( freq_buffer_HP );
				f2_buffer_HP.SetPassRate( freq_buffer_HP );
				f3_buffer_HP.SetPassRate( freq_buffer_HP );
				f0_buffer_LP.SetPassRate( freq_buffer_LP );
				f1_buffer_LP.SetPassRate( freq_buffer_LP );
				f2_buffer_LP.SetPassRate( freq_buffer_LP );
				f3_buffer_LP.SetPassRate( freq_buffer_LP );

				f0_buffer_out_LP.SetPassRate( freq_buffer_out_LP );
				f1_buffer_out_LP.SetPassRate( freq_buffer_out_LP );
				f2_buffer_out_LP.SetPassRate( freq_buffer_out_LP );
				f3_buffer_out_LP.SetPassRate( freq_buffer_out_LP );

				f0_gain_inp_LP.SetPassRate( freq_gain_inp_LP );
				f1_gain_inp_LP.SetPassRate( freq_gain_inp_LP );
				f2_gain_inp_LP.SetPassRate( freq_gain_inp_LP );
				f3_gain_inp_LP.SetPassRate( freq_gain_inp_LP );

				f0_dist_LP.SetPassRate( freq_dist_LP );
				f1_dist_LP.SetPassRate( freq_dist_LP );
				f2_dist_LP.SetPassRate( freq_dist_LP );
				f3_dist_LP.SetPassRate( freq_dist_LP );
				f0_diff_DP.SetPassRate( freq_dist_LP );
				f1_diff_DP.SetPassRate( freq_dist_LP );
				f2_diff_DP.SetPassRate( freq_dist_LP );
				f3_diff_DP.SetPassRate( freq_dist_LP );
				f0_dist_DP.SetPassRate( freq_dist_LP );
				f1_dist_DP.SetPassRate( freq_dist_LP );
				f2_dist_DP.SetPassRate( freq_dist_LP );
				f3_dist_DP.SetPassRate( freq_dist_LP );

				f0_feedback_HP.SetPassRate( freq_feedback_HP );
				f1_feedback_HP.SetPassRate( freq_feedback_HP );
				f2_feedback_HP.SetPassRate( freq_feedback_HP );
				f3_feedback_HP.SetPassRate( freq_feedback_HP );
				f0_feedback_LP.SetPassRate( freq_feedback_LP );
				f1_feedback_LP.SetPassRate( freq_feedback_LP );
				f2_feedback_LP.SetPassRate( freq_feedback_LP );
				f3_feedback_LP.SetPassRate( freq_feedback_LP );

				f0_x_bass_LP.SetPassRate( freq_x_bass );
				f1_x_bass_LP.SetPassRate( freq_x_bass );
				f2_x_bass_LP.SetPassRate( freq_x_bass );
				f3_x_bass_LP.SetPassRate( freq_x_bass );
				f0_x_bass_DP.SetPassRate( freq_x_bass );
				f1_x_bass_DP.SetPassRate( freq_x_bass );
				f2_x_bass_DP.SetPassRate( freq_x_bass );
				f3_x_bass_DP.SetPassRate( freq_x_bass );

				f0_output_HP.SetPassRate( freq_output_HP );
				f1_output_HP.SetPassRate( freq_output_HP );
				f2_output_HP.SetPassRate( freq_output_HP );
				f3_output_HP.SetPassRate( freq_output_HP );
				f0_output_LP.SetPassRate( freq_output_LP );
				f1_output_LP.SetPassRate( freq_output_LP );
				f2_output_LP.SetPassRate( freq_output_LP );
				f3_output_LP.SetPassRate( freq_output_LP );

				Clear();
			}
			Tube(const s32 inp_prm_set = 0) :
				prm_set( inp_prm_set ),

				p_input_read_volume( 1.0 ),
				p_input_vol_adjust( 1.0 ),
				p_output_vol_adjust( 1.0 ),
				p_buffer_range( 1.0 ),
				p_dry_range( 1.0 ),
				p_grit_low_adjust( 1.0 ),
				p_gain_pre_clip_adjust( 0.50 ),
				p_gain_clipping_curve( 120.0 ),
				p_feedback_volume( 1.0 ),
				p_min_bass( 0.0 ),
				p_max_bass( 0.0 ),

				prm_gain( 0.0 ),

				spl_buffer( 0.0 ),
				spl_feedback( 0.0 )
			{
				Init();
			}
			inline void SetGain(const f64 &inp)
			{
				prm_gain = (f64) inp;
			}
			inline void ScaleHighValue(f64 &spl_value)
			{
				spl_value = f64 ( spl_value > 0.75 ) ?
									f64 ( 0.75 + (0.25 * (spl_value - 0.75)) )
								:
									spl_value ;
			}
			inline void RunGritModifier(f64 SCRFT_RESTRICT_REF spl_value, const f64 SCRFT_RESTRICT_REF spl_modifier_inp)
			{
				f64 spl_modified = spl_value;

				{
					const f64 spl_high = f0_grit_high_LP.Run( spl_modified );
					const f64 spl_low = f0_grit_low_LP.Run( spl_modified * p_grit_low_adjust );

					spl_modified = scft_Avg64( f0_grit_low_DP.Run( spl_high ), f0_grit_high_DP.Run( spl_low ), spl_modifier_inp );
				}
				{
					const f64 spl_high = f1_grit_high_LP.Run( spl_modified );
					const f64 spl_low = f1_grit_low_LP.Run( spl_modified * p_grit_low_adjust );

					spl_modified = scft_Avg64( f1_grit_low_DP.Run( spl_high ), f1_grit_high_DP.Run( spl_low ), spl_modifier_inp );
				}
				{
					const f64 spl_high = f2_grit_high_LP.Run( spl_modified );
					const f64 spl_low = f2_grit_low_LP.Run( spl_modified * p_grit_low_adjust );

					spl_modified = scft_Avg64( f2_grit_low_DP.Run( spl_high ), f2_grit_high_DP.Run( spl_low ), spl_modifier_inp );
				}
				{
					const f64 spl_high = f3_grit_high_LP.Run( spl_modified );
					const f64 spl_low = f3_grit_low_LP.Run( spl_modified * p_grit_low_adjust );

					spl_modified = scft_Avg64( f3_grit_low_DP.Run( spl_high ), f3_grit_high_DP.Run( spl_low ), spl_modifier_inp );
				}

				spl_value = spl_modified;
			}
			inline f64 Run(const f64 SCRFT_RESTRICT_REF inp, const f64 SCRFT_RESTRICT_REF inp_modifier)
			{
				f64 spl_read = scft_Abs64( inp * p_input_read_volume );
				{
					ScaleHighValue( spl_read );
					ScaleHighValue( spl_read );
					ScaleHighValue( spl_read );
					ScaleHighValue( spl_read );
					spl_read = scft_Clamp64( spl_read, 0.0, 1.0 );
					f0_read_LP.RunFx( spl_read );
					f1_read_LP.RunFx( spl_read );
				}

				const f64 x_bass_ampl = scft_Avg64( p_min_bass, p_max_bass, spl_read );

				f64 spl_fx = inp * p_input_vol_adjust;

				f64 spl_drive = spl_fx;

				{
					f0_drive_HP.RunFx( spl_drive );
					f0_drive_LP.RunFx( spl_drive );
					f1_drive_HP.RunFx( spl_drive );
					f1_drive_LP.RunFx( spl_drive );
					f2_drive_HP.RunFx( spl_drive );
					f2_drive_LP.RunFx( spl_drive );
					f3_drive_HP.RunFx( spl_drive );
					f3_drive_LP.RunFx( spl_drive );
				}

				spl_buffer += spl_drive;

				{
					f0_buffer_HP.RunFx( spl_buffer );
					f0_buffer_LP.RunFx( spl_buffer );
					f1_buffer_HP.RunFx( spl_buffer );
					f1_buffer_LP.RunFx( spl_buffer );
					f2_buffer_HP.RunFx( spl_buffer );
					f2_buffer_LP.RunFx( spl_buffer );
					f3_buffer_HP.RunFx( spl_buffer );
					f3_buffer_LP.RunFx( spl_buffer );
				}

				f64 spl_gain = spl_buffer * p_buffer_range;

				{
					f0_buffer_out_LP.RunFx( spl_gain );
					f1_buffer_out_LP.RunFx( spl_gain );
					f2_buffer_out_LP.RunFx( spl_gain );
					f3_buffer_out_LP.RunFx( spl_gain );
				}

				spl_gain += spl_fx * p_dry_range;

				{
					f0_gain_inp_LP.RunFx( spl_gain );
					f1_gain_inp_LP.RunFx( spl_gain );
					f2_gain_inp_LP.RunFx( spl_gain );
					f3_gain_inp_LP.RunFx( spl_gain );
				}

				spl_gain *= prm_gain * p_gain_pre_clip_adjust;

				{
					const f64 spl_high = f0_grit_high_LP.Run( spl_gain );
					const f64 spl_low = f0_grit_low_LP.Run( spl_gain * p_grit_low_adjust );
					const f64 spl_modified = scft_Avg64( f0_grit_low_DP.Run( spl_high ), f0_grit_high_DP.Run( spl_low ), inp_modifier );

					spl_gain = scft_Avg64( spl_gain, spl_modified, prm_gain );
				}
				{
					const f64 spl_high = f1_grit_high_LP.Run( spl_gain );
					const f64 spl_low = f1_grit_low_LP.Run( spl_gain * p_grit_low_adjust );
					const f64 spl_modified = scft_Avg64( f1_grit_low_DP.Run( spl_high ), f1_grit_high_DP.Run( spl_low ), inp_modifier );

					spl_gain = scft_Avg64( spl_gain, spl_modified, prm_gain );
				}
				{
					const f64 spl_high = f2_grit_high_LP.Run( spl_gain );
					const f64 spl_low = f2_grit_low_LP.Run( spl_gain * p_grit_low_adjust );
					const f64 spl_modified = scft_Avg64( f2_grit_low_DP.Run( spl_high ), f2_grit_high_DP.Run( spl_low ), inp_modifier );

					spl_gain = scft_Avg64( spl_gain, spl_modified, prm_gain );
				}
				{
					const f64 spl_high = f3_grit_high_LP.Run( spl_gain );
					const f64 spl_low = f3_grit_low_LP.Run( spl_gain * p_grit_low_adjust );
					const f64 spl_modified = scft_Avg64( f3_grit_low_DP.Run( spl_high ), f3_grit_high_DP.Run( spl_low ), inp_modifier );

					spl_gain = scft_Avg64( spl_gain, spl_modified, prm_gain );
				}

		//		spl_gain = scft_ExpFx64( spl_gain, p_gain_clipping_curve );

		//		RunGritModifier( spl_gain, inp_modifier );
/*
				{
		//			const f64 spl_sign = f64 (( spl_gain < 0.0 ) ? -1.0 : 1.0 );
					f64 spl_dist = scft_ExpFx64( spl_gain, p_gain_clipping_curve );
		//			f64 spl_dist_mod = spl_dist - spl_gain;

					f0_dist_LP.RunFx( spl_dist );
					f1_dist_LP.RunFx( spl_dist );
					f2_dist_LP.RunFx( spl_dist );
					f3_dist_LP.RunFx( spl_dist );

					f0_dist_DP.RunFx( spl_gain );
					f1_dist_DP.RunFx( spl_gain );
					f2_dist_DP.RunFx( spl_gain );
					f3_dist_DP.RunFx( spl_gain );

					spl_gain = scft_ExpFx64( spl_dist - spl_gain, p_gain_clipping_curve );
				}
*/
				const f64 spl_sign = f64 (( spl_gain < 0.0 ) ? -1.0 : 1.0 );
				const f64 spl_offset_abs = (spl_gain * spl_sign) + 12.0;
				const f64 spl_dist = scft_ExpFxA64( spl_gain, p_gain_clipping_curve );
				const f64 spl_dist_offset = scft_ExpFxA64( spl_offset_abs, p_gain_clipping_curve );
				f64 spl_dist_diff = spl_dist / spl_dist_offset;
				f64 spl_dist_mod = spl_dist_offset / spl_offset_abs;
				{
					f0_dist_LP.RunFx( spl_dist_mod );
					f1_dist_LP.RunFx( spl_dist_mod );
					f2_dist_LP.RunFx( spl_dist_mod );
					f3_dist_LP.RunFx( spl_dist_mod );
				}
				{
					f0_diff_DP.RunFx( spl_dist_diff );
					f1_diff_DP.RunFx( spl_dist_diff );
					f2_diff_DP.RunFx( spl_dist_diff );
					f3_diff_DP.RunFx( spl_dist_diff );
				}
				{
					f0_dist_DP.RunFx( spl_gain );
					f1_dist_DP.RunFx( spl_gain );
					f2_dist_DP.RunFx( spl_gain );
					f3_dist_DP.RunFx( spl_gain );
				}

				const f64 spl_dist2_offset = (scft_Abs64( spl_gain ) + 12.0) * spl_dist_mod;
				const f64 spl_dist2 = spl_dist2_offset * spl_dist_diff;
				spl_gain = spl_dist2 * spl_sign;

				spl_gain += spl_feedback * p_feedback_volume;

				{
					spl_feedback = spl_fx;
					f0_feedback_HP.RunFx( spl_feedback );
					f0_feedback_LP.RunFx( spl_feedback );
					f1_feedback_HP.RunFx( spl_feedback );
					f1_feedback_LP.RunFx( spl_feedback );
					f2_feedback_HP.RunFx( spl_feedback );
					f2_feedback_LP.RunFx( spl_feedback );
					f3_feedback_HP.RunFx( spl_feedback );
					f3_feedback_LP.RunFx( spl_feedback );
				}

				spl_fx = spl_gain * p_output_vol_adjust;

				{
					const f64 spl_x0_bass = f0_x_bass_LP.Run( spl_fx ) * x_bass_ampl;
					f0_x_bass_DP.RunFx( spl_fx );
					spl_fx += spl_x0_bass;
				}
				{
					const f64 spl_x1_bass = f1_x_bass_LP.Run( spl_fx ) * x_bass_ampl;
					f1_x_bass_DP.RunFx( spl_fx );
					spl_fx += spl_x1_bass;
				}
				{
					const f64 spl_x2_bass = f2_x_bass_LP.Run( spl_fx ) * x_bass_ampl;
					f2_x_bass_DP.RunFx( spl_fx );
					spl_fx += spl_x2_bass;
				}
				{
					const f64 spl_x3_bass = f3_x_bass_LP.Run( spl_fx ) * x_bass_ampl;
					f3_x_bass_DP.RunFx( spl_fx );
					spl_fx += spl_x3_bass;
				}

				{
					f0_output_HP.RunFx( spl_fx );
					f1_output_HP.RunFx( spl_fx );
					f2_output_HP.RunFx( spl_fx );
					f3_output_HP.RunFx( spl_fx );

					f0_output_LP.RunFx( spl_fx );
					f1_output_LP.RunFx( spl_fx );
					f2_output_LP.RunFx( spl_fx );
					f3_output_LP.RunFx( spl_fx );
				}

				return spl_fx;
			}
		}; // struct Tube
		//! ----------------------------------------------------------------
		//! --- FX Component :: Tube Overdrive Channel :: Tube Drive Set (Overdrive Channel) Parameter List --
		//! ----------------------------------------------------------------
		struct SCRFT_EXPORT Tube_Set_Parameters
		{
			u32 numTubeStages;
			s32 tube_prms_0, tube_prms_1, tube_prms_2, tube_prms_3;
			s32 tube_grit_prms;

			f64 input_vol_min;
			f64 input_vol_max;
			f64 drive_min;
			f64 drive_max;
			f64 output_vol_min;
			f64 output_vol_max;

			Tube_Set_Parameters(	const u32 number_stages = 1u,
									const s32 tube_params = 0,
									const s32 tube_grit_params = 0,
									const f64 channel_input_vol_min = 0.1200,
									const f64 channel_input_vol_max = 1.0000,
									const f64 channel_min_drive = 0.0120,
									const f64 channel_max_drive = 1.0000,
									const f64 channel_output_vol_min = 0.5025,
									const f64 channel_output_vol_max = 0.5025	) :
				numTubeStages( number_stages ),
				tube_prms_0( tube_params ),
				tube_prms_1( tube_params ),
				tube_prms_2( tube_params ),
				tube_prms_3( tube_params ),
				tube_grit_prms( tube_grit_params ),

				input_vol_min( channel_input_vol_min ),
				input_vol_max( channel_input_vol_max ),
				drive_min( channel_min_drive ),
				drive_max( channel_max_drive ),
				output_vol_min( channel_output_vol_min ),
				output_vol_max( channel_output_vol_max )
			{}
			Tube_Set_Parameters& operator= (const Tube_Set_Parameters &other)
			{
				memcpy( this, &other, sizeof( *this ) );

				return *this;
			}
		}; // struct Tube_Set_Parameters
		//! ----------------------------------------------------------------
		//! --- FX Component :: Tube Overdrive Channel :: Tube Drive Set (Overdrive Channel) --
		//! ----------------------------------------------------------------
		struct SCRFT_EXPORT Tube_Set
		{
			u32 numTubeStages;
			s32 tube_prms_0, tube_prms_1, tube_prms_2, tube_prms_3;
			s32 tube_grit_prms;

			f64 spl_fx;
			f64 spl_grit;

			Tube Tube0, Tube1, Tube2, Tube3;

			Tube_Grit_Fx TubeGrit;

			f64 input_vol_min;
			f64 input_vol_max;
			f64 drive_min;
			f64 drive_max;
			f64 output_vol_min;
			f64 output_vol_max;

			f64 prm_input_vol,
				prm_gain,
				prm_output_vol;

			void CheckParameters()
			{
				if ( numTubeStages > 6u )
					numTubeStages = 6u;

				drive_min = scft_Clamp64( drive_min, 0.0, 1.0 );
				drive_max = scft_Clamp64( drive_max, 0.0, 1.0 );
			}
			Tube_Set(	const u32 number_stages = 4u,
						const s32 tube_params = 0,
						const s32 tube_grit_params = 0,
						const f64 channel_input_vol_min = 0.0912,
						const f64 channel_input_vol_max = 1.0000,
						const f64 channel_min_drive = 0.0120,
						const f64 channel_max_drive = 1.0000,
						const f64 channel_output_vol_min = 0.5025,
						const f64 channel_output_vol_max = 0.5025	) :
				numTubeStages( (u32) number_stages ),
				tube_prms_0( tube_params ),
				tube_prms_1( tube_params ),
				tube_prms_2( tube_params ),
				tube_prms_3( tube_params ),
				tube_grit_prms( tube_grit_params ),

				spl_fx( 0.0 ),
				spl_grit( 0.0 ),

				Tube0( tube_prms_0 ),
				Tube1( tube_prms_1 ),
				Tube2( tube_prms_2 ),
				Tube3( tube_prms_3 ),
				TubeGrit( tube_grit_prms ),

				input_vol_min( channel_input_vol_min ),
				input_vol_max( channel_input_vol_max ),
				drive_min( channel_min_drive ),
				drive_max( channel_max_drive ),
				output_vol_min( channel_output_vol_min ),
				output_vol_max( channel_output_vol_max ),

				prm_input_vol( 0.5 ),
				prm_gain( 0.5 ),
				prm_output_vol( 0.5 )
			{
				CheckParameters();
			}
			Tube_Set(const Tube_Set_Parameters &inp_prms) :
				numTubeStages( inp_prms.numTubeStages ),
				tube_prms_0( inp_prms.tube_prms_0 ),
				tube_prms_1( inp_prms.tube_prms_1 ),
				tube_prms_2( inp_prms.tube_prms_2 ),
				tube_prms_3( inp_prms.tube_prms_3 ),
				tube_grit_prms( inp_prms.tube_grit_prms ),

				spl_fx( 0.0 ),
				spl_grit( 0.0 ),

				Tube0( tube_prms_0 ),
				Tube1( tube_prms_1 ),
				Tube2( tube_prms_2 ),
				Tube3( tube_prms_3 ),
				TubeGrit( tube_grit_prms ),

				input_vol_min( inp_prms.input_vol_min ),
				input_vol_max( inp_prms.input_vol_max ),
				drive_min( inp_prms.drive_min ),
				drive_max( inp_prms.drive_max ),
				output_vol_min( inp_prms.output_vol_min ),
				output_vol_max( inp_prms.output_vol_max ),

				prm_input_vol( 0.5 ),
				prm_gain( 0.5 ),
				prm_output_vol( 0.5 )
			{
				CheckParameters();
			}
			Tube_Set& operator= (const Tube_Set &other)
			{
				memcpy( this, &other, sizeof( *this ) );

				CheckParameters();

				return *this;
			}
			Tube_Set& operator= (const Tube_Set_Parameters &other_prms)
			{
				*this = Tube_Set( other_prms );

				CheckParameters();

				return *this;
			}
			inline void Clear()
			{
				spl_fx = 0.0;
				spl_grit = 0.0;

				Tube0.Clear();
				Tube1.Clear();
				Tube2.Clear();
				Tube3.Clear();

				TubeGrit.Clear();
			}
			void SetSampleRate(const f64 &inp)
			{
				Tube0.SetSampleRate( inp );
				Tube1.SetSampleRate( inp );
				Tube2.SetSampleRate( inp );
				Tube3.SetSampleRate( inp );

				TubeGrit.SetSampleRate( inp );
			}
			inline void SetGain(const f64 &inp)
			{
				const f64 inp_skew = inp * (2.0 - inp);

				prm_gain = scft_Avg64( drive_min, drive_max, inp_skew );
				prm_input_vol = scft_Avg64( input_vol_min, input_vol_max, inp_skew );
				prm_output_vol = scft_Avg64( output_vol_min, output_vol_max, inp_skew * (2.0 - inp_skew) );

				Tube0.SetGain( prm_gain );
				Tube1.SetGain( prm_gain );
				Tube2.SetGain( prm_gain );
				Tube3.SetGain( prm_gain );

				TubeGrit.SetGain( inp );
			}
			inline void RunGritFx(const f64 &inp)
			{
				spl_grit = TubeGrit.Run( inp );
			}
			inline f64 Run(const f64 &inp)
			{
				spl_fx = f64 (inp * prm_input_vol);

				if ( numTubeStages > 0u )
					spl_fx = Tube0.Run( spl_fx, spl_grit );
				if ( numTubeStages > 1u )
					spl_fx = Tube1.Run( spl_fx, spl_grit );
				if ( numTubeStages > 2u )
					spl_fx = Tube2.Run( spl_fx, spl_grit );
				if ( numTubeStages > 3u )
					spl_fx = Tube3.Run( spl_fx, spl_grit );

				spl_fx *= prm_output_vol;

				return spl_fx;
			}
			inline f64 GetLastOutput() const
			{
				return spl_fx;
			}
		}; // struct Tube_Set

	} // namespace Modules
} // namespace ScorchCrafter

#endif // SCORCHCRAFTER_MODULE_Tube_Overdrive_INC
