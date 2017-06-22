#ifndef SCORCHCRAFTER_MODULE_Noise_Gate_INC
#define SCORCHCRAFTER_MODULE_Noise_Gate_INC

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
		//! --- FX Component :: Noise Gate --
		//! ----------------------------------------------------------------
		struct SCRFT_EXPORT Noise_Gate
		{
			const f64 _pi_f64_x4;
			const f64 _pi_f64_x8;
			const f64 dn;

			f80 sp_rate;

			f64 threshold;
			f64 rate_attack;
			f64 rate_release;
			f64 rate_output;
			f64 hold_length;
			f64 hold_distance;

			f64 fq0_attack, fq1_attack;
			f64 fq0_release, fq1_release;
			f64 fq0_output, fq1_output;
			f64 buf_gate;
			f64 buf_output;
			f64 buf_hold_attack;
			f64 buf_hold_release;

			f64 noise_level;

			f64 buf_dn;
			f64 dn_rate;
			const f64 dn_level;
			const f64 dn_threshold;
			const f64 dn_offset;
			f64 dn_wave;

			bool p_enabled;

			inline void Clear()
			{
				buf_gate = 0.0;
				buf_output = 0.0;
				noise_level = 0.0;
				buf_hold_attack = 0.125130;
				buf_hold_release = 0.125130;

				buf_dn = 0.0;
				dn_wave = dn_level;
			}
			void SetRateVariables()
			{
				f80 t = (f80) 0.0L;

				// Attack
				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * (f80) rate_attack / sp_rate ); // Low Pass Frequency
				fq0_attack = f64 (f80 (1.0L - t));
				fq1_attack = f64 (f80 (-t));

				// Release
				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * (f80) rate_release / sp_rate ); // Low Pass Frequency
				fq0_release = f64 (f80 (1.0L - t));
				fq1_release = f64 (f80 (-t));

				// Output
				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * (f80) rate_output / sp_rate ); // Low Pass Frequency
				fq0_output = f64 (f80 (1.0L - t));
				fq1_output = f64 (f80 (-t));

				dn_rate = f64 ( f80 (SCRFT_pi_f80 / (f80) 8.L) );

				hold_distance = hold_length * (f64) sp_rate;
			}
			void CheckRates()
			{
				if ( sp_rate < (f80) 44100.0L )
					sp_rate = (f80) 44100.0L;

				if ( rate_attack < 1.0 )
					rate_attack = 1.0;

				if ( rate_release < 1.0 )
					rate_release = 1.0;

				if ( rate_output < 1.0 )
					rate_output = 1.0;

				if ( threshold < 12.0 )
					threshold = 12.0;

				if ( hold_length < 0.00275 )
					hold_length = 0.00275;
			}
			void SetSampleRate(const f64 &inp_rate)
			{
				sp_rate = (f80) inp_rate;

				CheckRates();
				SetRateVariables();

				Clear();
			}
			void Init()
			{
				CheckRates();
				SetRateVariables();

				Clear();

				p_enabled = true;
			}
			void SetRates(const f64 attack_rate, const f64 release_rate, const f64 fade_hold_length, const f64 output_rate)
			{
				rate_attack = scft_Abs64( attack_rate );
				rate_release = scft_Abs64( release_rate );
				rate_output = scft_Abs64( output_rate );
				hold_length = scft_Abs64( fade_hold_length );

				CheckRates();
				SetRateVariables();

				Clear();
			}
			inline void SetThreshold_dB(const f64 &inp_dB)
			{
				const f64 threshold_dB = scft_Abs64( inp_dB );

				threshold = pow( 2.0, threshold_dB / 6.0 );

				if ( threshold < 4.0 )
					threshold = 4.0;
			}
			inline void RunDetectionOnInput(const f64 &inp)
			{
				buf_dn += dn_rate;
				if ( buf_dn >= _pi_f64_x8 )
					buf_dn -= _pi_f64_x4;

				dn_wave = f64 ((f64) sin( buf_dn ) * dn_level) + dn_offset;

				if ( p_enabled == false )
					return;

				const f64 spl_check = scft_Abs64( inp * threshold );

				if ( spl_check < buf_gate )
				{
					if ( buf_hold_attack <= 0.0 )
					{
						buf_gate = (fq0_attack*spl_check) - (fq1_attack*buf_gate) + dn;
					} else
						buf_hold_attack -= 1.0;
				} else
				{
					buf_hold_attack = hold_distance;
					buf_gate = (fq0_release*spl_check) - (fq1_release*buf_gate) + dn;
				}

				if ( buf_gate > 1.0 )
					buf_gate = 1.0;

				noise_level = buf_gate;
				noise_level *= noise_level * noise_level * noise_level * noise_level * noise_level;

				noise_level = ( buf_output = (fq0_output*noise_level) - (fq1_output*buf_output) + dn );
			}
			inline f64 Run(const f64 inp)
			{
				if ( p_enabled == false )
				{
					if ( scft_Abs64( inp ) < dn_threshold )
						return dn_wave;

					return inp;
				}

				const f64 fx_output = inp * noise_level;

				if ( scft_Abs64( fx_output ) < dn_threshold )
					return dn_wave;

				return fx_output;
			}
			inline void SetEnabled(const bool turn_on = true)
			{
				p_enabled = (bool) turn_on;
			}
			Noise_Gate() :
				_pi_f64_x4( f64 (SCRFT_pi_f80 * (f80) 4.0L) ),
				_pi_f64_x8( f64 (SCRFT_pi_f80 * (f80) 8.0L) ),
				dn( f64 ((f80) powl( (f80) 10.0L, (f80) -30.0L )) ),
				dn_level( f64 ((f80) powl( (f80) 10.0L, (f80) -29.1L )) ),
				dn_threshold( dn_level * 2.37 ),
				dn_offset( dn_level * 1.29 )
			{
				sp_rate = (f80) 44100.0L;
				threshold = 1024.0;

				CheckRates();
				SetRateVariables();

				Clear();

				p_enabled = true;
			}
		}; // struct Noise_Gate

	} // namespace Modules
} // namespace ScorchCrafter

#endif // SCORCHCRAFTER_MODULE_Noise_Gate_INC
