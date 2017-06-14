#ifndef SCORCHCRAFTER_MODULE_OverSample_INC
#define SCORCHCRAFTER_MODULE_OverSample_INC

#include "Scorchcrafter_Platform.hpp"

using namespace ::ScorchCrafter;
using namespace ::ScorchCrafter::DataTypes;
using namespace ::ScorchCrafter::Base;
using namespace ::ScorchCrafter::Modules;

namespace ScorchCrafter
{
	namespace Modules
	{
		//! ----------------------------------------------------------------
		//! --- FX Component :: OverSampling EQ Filter --
		//! ----------------------------------------------------------------
		struct SCRFT_EXPORT OverSampling_Eq_Filter
		{
			f64 smp_rate, os_mult, os_rate;

			f80 freq_highpass;
			f80 cutoff_lp, cutoff_hp, k, c1, c2, c3, res_hp, res_lp;

			f64 a0_hp, a1_hp, a2_hp, b1_hp, b2_hp;
			f64 a0_lp, a1_lp, a2_lp, b1_lp, b2_lp;

			f64 buf_l0_0, buf_l1_0, buf_l2_0, buf_l3_0, buf_l4_0;
			f64 buf_l0_1, buf_l1_1, buf_l2_1, buf_l3_1, buf_l4_1;
			f64 buf_l0_2, buf_l1_2, buf_l2_2, buf_l3_2, buf_l4_2;
			f64 buf_l0_3, buf_l1_3, buf_l2_3, buf_l3_3, buf_l4_3;
			f64 buf_l0_4, buf_l1_4, buf_l2_4, buf_l3_4, buf_l4_4;
			f64 buf_l0_5, buf_l1_5, buf_l2_5, buf_l3_5, buf_l4_5;

			f64 buf_h0_0, buf_h1_0, buf_h2_0, buf_h3_0, buf_h4_0;
			f64 buf_h0_1, buf_h1_1, buf_h2_1, buf_h3_1, buf_h4_1;
			f64 buf_h0_2, buf_h1_2, buf_h2_2, buf_h3_2, buf_h4_2;
			f64 buf_h0_3, buf_h1_3, buf_h2_3, buf_h3_3, buf_h4_3;
			f64 buf_h0_4, buf_h1_4, buf_h2_4, buf_h3_4, buf_h4_4;
			f64 buf_h0_5, buf_h1_5, buf_h2_5, buf_h3_5, buf_h4_5;

			inline void Clear()
			{
				buf_l0_0 = 0.0; buf_l1_0 = 0.0; buf_l2_0 = 0.0; buf_l3_0 = 0.0; buf_l4_0 = 0.0;
				buf_l0_1 = 0.0; buf_l1_1 = 0.0; buf_l2_1 = 0.0; buf_l3_1 = 0.0; buf_l4_1 = 0.0;
				buf_l0_2 = 0.0; buf_l1_2 = 0.0; buf_l2_2 = 0.0; buf_l3_2 = 0.0; buf_l4_2 = 0.0;
				buf_l0_3 = 0.0; buf_l1_3 = 0.0; buf_l2_3 = 0.0; buf_l3_3 = 0.0; buf_l4_3 = 0.0;
				buf_l0_4 = 0.0; buf_l1_4 = 0.0; buf_l2_4 = 0.0; buf_l3_4 = 0.0; buf_l4_4 = 0.0;
				buf_l0_5 = 0.0; buf_l1_5 = 0.0; buf_l2_5 = 0.0; buf_l3_5 = 0.0; buf_l4_5 = 0.0;

				buf_h0_0 = 0.0; buf_h1_0 = 0.0; buf_h2_0 = 0.0; buf_h3_0 = 0.0; buf_h4_0 = 0.0;
				buf_h0_1 = 0.0; buf_h1_1 = 0.0; buf_h2_1 = 0.0; buf_h3_1 = 0.0; buf_h4_1 = 0.0;
				buf_h0_2 = 0.0; buf_h1_2 = 0.0; buf_h2_2 = 0.0; buf_h3_2 = 0.0; buf_h4_2 = 0.0;
				buf_h0_3 = 0.0; buf_h1_3 = 0.0; buf_h2_3 = 0.0; buf_h3_3 = 0.0; buf_h4_3 = 0.0;
				buf_h0_4 = 0.0; buf_h1_4 = 0.0; buf_h2_4 = 0.0; buf_h3_4 = 0.0; buf_h4_4 = 0.0;
				buf_h0_5 = 0.0; buf_h1_5 = 0.0; buf_h2_5 = 0.0; buf_h3_5 = 0.0; buf_h4_5 = 0.0;
			}
			inline void SetInternalRates()
			{
				cutoff_hp = freq_highpass * (f80) 2.0L / (f80) os_rate;
				cutoff_lp = (f80) smp_rate / (f80) os_rate;

				k = (f80) 0.5L * res_hp * (f80) sinl( SCRFT_pi_f80 * cutoff_hp );
				c1 = (f80) 0.5L * ((f80) 1.0L - k) / ((f80) 1.0L + k);
				c2 = ((f80) 0.5L + c1) * (f80) cosl( SCRFT_pi_f80 * cutoff_hp );
				c3 = ((f80) 0.5L + c1 + c2 ) * (f80) 0.25L;

				a0_hp = f64 ((f80) 2.0L * c3);
				a1_hp = f64 ((f80) -4.0L * c3);
				a2_hp = f64 ((f80) 2.0L * c3);
				b1_hp = f64 ((f80) -2.0L * c2);
				b2_hp = f64 ((f80) 2.0L * c1);

				k = (f80) 0.5L * res_lp * (f80) sinl( SCRFT_pi_f80 * cutoff_lp );
				c1 = (f80) 0.5L * ((f80) 1.0L - k) / ((f80) 1.0L + k);
				c2 = ((f80) 0.5L + c1) * (f80) cosl( SCRFT_pi_f80 * cutoff_lp );
				c3 = ((f80) 0.5L + c1 - c2) * (f80) 0.25L;

				a0_lp = f64 ((f80) 2.0L * c3);
				a1_lp = f64 ((f80) 4.0L * c3);
				a2_lp = f64 ((f80) 2.0L * c3);
				b1_lp = f64 ((f80) -2.0L * c2);
				b2_lp = f64 ((f80) 2.0L * c1);
			}
			inline void SetOverSamplingMultiplier(u32 inp_os_mult)
			{
				if ( inp_os_mult < 2u )
					inp_os_mult = 2u;
				if ( smp_rate < 44100.0 )
					smp_rate = 44100.0;

				os_mult = (f64) inp_os_mult;
				os_rate = smp_rate * os_mult;

				SetInternalRates();
				Clear();
			}
			void SetSampleRate(const f64 inp_rate)
			{
				smp_rate = inp_rate;

				if ( os_mult < 2.0 )
					os_mult = 2.0;
				if ( smp_rate < 44100.0 )
					smp_rate = 44100.0;

				os_rate = smp_rate * os_mult;

				SetInternalRates();
				Clear();
			}
			inline f64 Run_LP(const f64 &inp)
			{
				f64 fx_sp = (f64) inp;

				buf_l0_0 = a0_lp*fx_sp + a1_lp*buf_l1_0 + a2_lp*buf_l2_0 - b1_lp*buf_l3_0 - b2_lp*buf_l4_0;
				buf_l2_0 = buf_l1_0;  buf_l1_0 = fx_sp;  buf_l4_0 = buf_l3_0;  buf_l3_0 = buf_l0_0;
				fx_sp = buf_l0_0;

				buf_l0_1 = a0_lp*fx_sp + a1_lp*buf_l1_1 + a2_lp*buf_l2_1 - b1_lp*buf_l3_1 - b2_lp*buf_l4_1;
				buf_l2_1 = buf_l1_1;  buf_l1_1 = fx_sp;  buf_l4_1 = buf_l3_1;  buf_l3_1 = buf_l0_1;
				fx_sp = buf_l0_1;

				buf_l0_2 = a0_lp*fx_sp + a1_lp*buf_l1_2 + a2_lp*buf_l2_2 - b1_lp*buf_l3_2 - b2_lp*buf_l4_2;
				buf_l2_2 = buf_l1_2;  buf_l1_2 = fx_sp;  buf_l4_2 = buf_l3_2;  buf_l3_2 = buf_l0_2;
				fx_sp = buf_l0_2;

				buf_l0_3 = a0_lp*fx_sp + a1_lp*buf_l1_3 + a2_lp*buf_l2_3 - b1_lp*buf_l3_3 - b2_lp*buf_l4_3;
				buf_l2_3 = buf_l1_3;  buf_l1_3 = fx_sp;  buf_l4_3 = buf_l3_3;  buf_l3_3 = buf_l0_3;
				fx_sp = buf_l0_3;

				buf_l0_4 = a0_lp*fx_sp + a1_lp*buf_l1_4 + a2_lp*buf_l2_4 - b1_lp*buf_l3_4 - b2_lp*buf_l4_4;
				buf_l2_4 = buf_l1_4;  buf_l1_4 = fx_sp;  buf_l4_4 = buf_l3_4;  buf_l3_4 = buf_l0_4;
				fx_sp = buf_l0_4;

				buf_l0_5 = a0_lp*fx_sp + a1_lp*buf_l1_5 + a2_lp*buf_l2_5 - b1_lp*buf_l3_5 - b2_lp*buf_l4_5;
				buf_l2_5 = buf_l1_5;  buf_l1_5 = fx_sp;  buf_l4_5 = buf_l3_5;  buf_l3_5 = buf_l0_5;
				fx_sp = buf_l0_5;

				return fx_sp;
			}
			inline f64 Run_HP(const f64 &inp)
			{
				f64 fx_sp = (f64) inp;

				buf_h0_0 = a0_hp*fx_sp + a1_hp*buf_h1_0 + a2_hp*buf_h2_0 - b1_hp*buf_h3_0 - b2_hp*buf_h4_0;
				buf_h2_0 = buf_h1_0;  buf_h1_0 = fx_sp;  buf_h4_0 = buf_h3_0;  buf_h3_0 = buf_h0_0;
				fx_sp = buf_h0_0;

				buf_h0_1 = a0_hp*fx_sp + a1_hp*buf_h1_1 + a2_hp*buf_h2_1 - b1_hp*buf_h3_1 - b2_hp*buf_h4_1;
				buf_h2_1 = buf_h1_1;  buf_h1_1 = fx_sp;  buf_h4_1 = buf_h3_1;  buf_h3_1 = buf_h0_1;
				fx_sp = buf_h0_1;

				buf_h0_2 = a0_hp*fx_sp + a1_hp*buf_h1_2 + a2_hp*buf_h2_2 - b1_hp*buf_h3_2 - b2_hp*buf_h4_2;
				buf_h2_2 = buf_h1_2;  buf_h1_2 = fx_sp;  buf_h4_2 = buf_h3_2;  buf_h3_2 = buf_h0_2;
				fx_sp = buf_h0_2;

				buf_h0_3 = a0_hp*fx_sp + a1_hp*buf_h1_3 + a2_hp*buf_h2_3 - b1_hp*buf_h3_3 - b2_hp*buf_h4_3;
				buf_h2_3 = buf_h1_3;  buf_h1_3 = fx_sp;  buf_h4_3 = buf_h3_3;  buf_h3_3 = buf_h0_3;
				fx_sp = buf_h0_3;

				buf_h0_4 = a0_hp*fx_sp + a1_hp*buf_h1_4 + a2_hp*buf_h2_4 - b1_hp*buf_h3_4 - b2_hp*buf_h4_4;
				buf_h2_4 = buf_h1_4;  buf_h1_4 = fx_sp;  buf_h4_4 = buf_h3_4;  buf_h3_4 = buf_h0_4;
				fx_sp = buf_h0_4;

				buf_h0_5 = a0_hp*fx_sp + a1_hp*buf_h1_5 + a2_hp*buf_h2_5 - b1_hp*buf_h3_5 - b2_hp*buf_h4_5;
				buf_h2_5 = buf_h1_5;  buf_h1_5 = fx_sp;  buf_h4_5 = buf_h3_5;  buf_h3_5 = buf_h0_5;
				fx_sp = buf_h0_5;

				return fx_sp;
			}
			inline f64 Run_HPLP(const f64 &inp)
			{
				f64 fx_sp = (f64) inp;

				buf_h0_0 = a0_hp*fx_sp + a1_hp*buf_h1_0 + a2_hp*buf_h2_0 - b1_hp*buf_h3_0 - b2_hp*buf_h4_0;
				buf_h2_0 = buf_h1_0;  buf_h1_0 = fx_sp;  buf_h4_0 = buf_h3_0;  buf_h3_0 = buf_h0_0;
				fx_sp = buf_h0_0;
				buf_l0_0 = a0_lp*fx_sp + a1_lp*buf_l1_0 + a2_lp*buf_l2_0 - b1_lp*buf_l3_0 - b2_lp*buf_l4_0;
				buf_l2_0 = buf_l1_0;  buf_l1_0 = fx_sp;  buf_l4_0 = buf_l3_0;  buf_l3_0 = buf_l0_0;
				fx_sp = buf_l0_0;

				buf_h0_1 = a0_hp*fx_sp + a1_hp*buf_h1_1 + a2_hp*buf_h2_1 - b1_hp*buf_h3_1 - b2_hp*buf_h4_1;
				buf_h2_1 = buf_h1_1;  buf_h1_1 = fx_sp;  buf_h4_1 = buf_h3_1;  buf_h3_1 = buf_h0_1;
				fx_sp = buf_h0_1;
				buf_l0_1 = a0_lp*fx_sp + a1_lp*buf_l1_1 + a2_lp*buf_l2_1 - b1_lp*buf_l3_1 - b2_lp*buf_l4_1;
				buf_l2_1 = buf_l1_1;  buf_l1_1 = fx_sp;  buf_l4_1 = buf_l3_1;  buf_l3_1 = buf_l0_1;
				fx_sp = buf_l0_1;

				buf_h0_2 = a0_hp*fx_sp + a1_hp*buf_h1_2 + a2_hp*buf_h2_2 - b1_hp*buf_h3_2 - b2_hp*buf_h4_2;
				buf_h2_2 = buf_h1_2;  buf_h1_2 = fx_sp;  buf_h4_2 = buf_h3_2;  buf_h3_2 = buf_h0_2;
				fx_sp = buf_h0_2;
				buf_l0_2 = a0_lp*fx_sp + a1_lp*buf_l1_2 + a2_lp*buf_l2_2 - b1_lp*buf_l3_2 - b2_lp*buf_l4_2;
				buf_l2_2 = buf_l1_2;  buf_l1_2 = fx_sp;  buf_l4_2 = buf_l3_2;  buf_l3_2 = buf_l0_2;
				fx_sp = buf_l0_2;

				buf_h0_3 = a0_hp*fx_sp + a1_hp*buf_h1_3 + a2_hp*buf_h2_3 - b1_hp*buf_h3_3 - b2_hp*buf_h4_3;
				buf_h2_3 = buf_h1_3;  buf_h1_3 = fx_sp;  buf_h4_3 = buf_h3_3;  buf_h3_3 = buf_h0_3;
				fx_sp = buf_h0_3;
				buf_l0_3 = a0_lp*fx_sp + a1_lp*buf_l1_3 + a2_lp*buf_l2_3 - b1_lp*buf_l3_3 - b2_lp*buf_l4_3;
				buf_l2_3 = buf_l1_3;  buf_l1_3 = fx_sp;  buf_l4_3 = buf_l3_3;  buf_l3_3 = buf_l0_3;
				fx_sp = buf_l0_3;

				buf_h0_4 = a0_hp*fx_sp + a1_hp*buf_h1_4 + a2_hp*buf_h2_4 - b1_hp*buf_h3_4 - b2_hp*buf_h4_4;
				buf_h2_4 = buf_h1_4;  buf_h1_4 = fx_sp;  buf_h4_4 = buf_h3_4;  buf_h3_4 = buf_h0_4;
				fx_sp = buf_h0_4;
				buf_l0_4 = a0_lp*fx_sp + a1_lp*buf_l1_4 + a2_lp*buf_l2_4 - b1_lp*buf_l3_4 - b2_lp*buf_l4_4;
				buf_l2_4 = buf_l1_4;  buf_l1_4 = fx_sp;  buf_l4_4 = buf_l3_4;  buf_l3_4 = buf_l0_4;
				fx_sp = buf_l0_4;

				buf_h0_5 = a0_hp*fx_sp + a1_hp*buf_h1_5 + a2_hp*buf_h2_5 - b1_hp*buf_h3_5 - b2_hp*buf_h4_5;
				buf_h2_5 = buf_h1_5;  buf_h1_5 = fx_sp;  buf_h4_5 = buf_h3_5;  buf_h3_5 = buf_h0_5;
				fx_sp = buf_h0_5;
				buf_l0_5 = a0_lp*fx_sp + a1_lp*buf_l1_5 + a2_lp*buf_l2_5 - b1_lp*buf_l3_5 - b2_lp*buf_l4_5;
				buf_l2_5 = buf_l1_5;  buf_l1_5 = fx_sp;  buf_l4_5 = buf_l3_5;  buf_l3_5 = buf_l0_5;
				fx_sp = buf_l0_5;

				return fx_sp;
			}
			void SetHighPassFrequency(const f64 inp_frequency = 12.450)
			{
				freq_highpass = scft_Max80( (f80) 1.0L, (f80) inp_frequency );

				SetInternalRates();
			}
			void SetHighPassFrequency(const f80 inp_frequency = (f80) 12.450L)
			{
				freq_highpass = scft_Max80( (f80) 1.0L, inp_frequency );

				SetInternalRates();
			}
			void SetResonance()
			{
	//			res_hp = (f80) 1.1885022274370184377301224648922L;
	//			res_lp = (f80) 1.1885022274370184377301224648922L;

				res_hp = (f80) 1.0L;
				res_lp = (f80) 1.0L;

	//			SetInternalRates();
			}
			void SetResonance(const f64 inp_hp_and_lp)
			{
				res_hp = (f80) inp_hp_and_lp;
				res_lp = (f80) inp_hp_and_lp;

	//			SetInternalRates();
			}
			void SetResonance(const f64 inp_hp, const f64 inp_lp)
			{
				res_hp = (f80) inp_hp;
				res_lp = (f80) inp_lp;

	//			SetInternalRates();
			}
			OverSampling_Eq_Filter() :
				smp_rate( 44100.0 ),
				os_mult( 2.0 ),
				os_rate( 88200.0 ),
				freq_highpass( (f80) 12.450L ),
				res_hp( (f80) 1.0L ),
				res_lp( (f80) 1.0L )
			{
				SetInternalRates();

				Clear();
			}
			OverSampling_Eq_Filter(	const f64 inp_smp_rate,
									const u32 inp_rate_multiplier = 2u,
									const f80 inp_freq_highpass = (f80) 12.450L,
									const f80 inp_res_hp = (f80) 1.0L,
									const f80 inp_res_lp = (f80) 1.0L	) :
				smp_rate( (inp_smp_rate < 44100.0) ? 44100.0 : (f64) inp_smp_rate ),
				os_mult( (inp_rate_multiplier < 2u) ? 2.0 : (f64) inp_rate_multiplier ),
				os_rate( smp_rate * os_mult ),
				freq_highpass( (f80) inp_freq_highpass ),
				res_hp( (f80) inp_res_hp ),
				res_lp( (f80) inp_res_lp )
			{
				freq_highpass = scft_Max80( (f80) 1.0L, freq_highpass );

				SetInternalRates();

				Clear();
			}
			OverSampling_Eq_Filter& operator=(const OverSampling_Eq_Filter &other)
			{
				smp_rate = scft_Max64( (f64) other.smp_rate, 44100.0 );
				os_mult = scft_Max64( (f64) other.os_mult, 2.0 );
				os_rate = smp_rate * os_mult;

				freq_highpass = scft_Max80( (f80) 1.0L, (f80) other.freq_highpass );

				res_hp = (f80) other.res_hp;
				res_lp = (f80) other.res_lp;

				SetInternalRates();

				Clear();

				return *this;
			}
		}; // struct OverSampling_Eq_Filter

	} // namespace Modules
} // namespace ScorchCrafter

#endif // SCORCHCRAFTER_MODULE_OverSample_INC
