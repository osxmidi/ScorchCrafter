#ifndef SCORCHCRAFTER_MODULE_EQ_xP_INC
#define SCORCHCRAFTER_MODULE_EQ_xP_INC

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
		//! --- FX Component :: EQ Filter :: Standard LP (Simple Low Pass) --
		//! ----------------------------------------------------------------
		struct SCRFT_EXPORT EQ_LP
		{
			f80 p_frequency;

			f80 sp_rate;
			f64 fq0, fq1, buffer;

			inline void Clear()
			{
				buffer = 0.0;
			}
			void SetFilterVars()
			{
				if ( sp_rate < (f80) 44100.0L )
					sp_rate = (f80) 44100.0L;

				if ( p_frequency > f80 (sp_rate * (f80) 0.5L) )
					p_frequency = f80 (sp_rate * (f80) 0.5L);
				if ( p_frequency < (f80) 0.0000012L )
					p_frequency = (f80) 0.0000012L;

				const f80 t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * p_frequency / sp_rate );
				fq0 = f64 (f80 ((f80) 1.0L - t));
				fq1 = f64 (f80 (-t));

				Clear();
			}
			void SetSampleRate(const f64 &inp_rate)
			{
				sp_rate = (f80) inp_rate;

				SetFilterVars();
			}
			void SetPassRate(const f64 &inp_frequency)
			{
				p_frequency = (f80) inp_frequency;

				SetFilterVars();
			}
			inline f64 Run(const f64 &inp)
			{
				return f64 ( buffer = (fq0 * inp) - (fq1 * buffer) + SCRFT_dn_f64 );
			}
			inline void RunFx(f64 &inp)
			{
				buffer = (fq0 * inp) - (fq1 * buffer) + SCRFT_dn_f64;

				inp = (f64) buffer;
			}
			EQ_LP() :
				p_frequency( (f80) 1.0L ),
				sp_rate( (f80) 44100.0L ),
				buffer( 0.0 )
			{
				SetFilterVars();
			}
			EQ_LP(const f64 pass_frequency) :
				p_frequency( (f80) pass_frequency ),
				sp_rate( (f80) 44100.0L ),
				buffer( 0.0 )
			{
				SetFilterVars();
			}
		}; // struct EQ_LP
		//! ----------------------------------------------------------------
		//! --- FX Component :: EQ Filter :: Standard HP (Simple High Pass) --
		//! ----------------------------------------------------------------
		struct SCRFT_EXPORT EQ_HP
		{
			f80 p_frequency;

			f80 sp_rate;
			f64 fq0, fq1, buffer;
			f64 old_inp;

			inline void Clear()
			{
				buffer = 0.0;
				old_inp = 0.0;
			}
			void SetFilterVars()
			{
				if ( sp_rate < (f80) 44100.0L )
					sp_rate = (f80) 44100.0L;

				if ( p_frequency > f80 (sp_rate * (f80) 0.5L) )
					p_frequency = f80 (sp_rate * (f80) 0.5L);
				if ( p_frequency < (f80) 0.0000012L )
					p_frequency = (f80) 0.0000012L;

				const f80 t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * p_frequency / sp_rate );
				fq0 = f64 (f80 ((f80) 1.0L - t));
				fq1 = f64 (f80 (-t));

				Clear();
			}
			void SetSampleRate(const f64 &inp_rate)
			{
				sp_rate = (f80) inp_rate;

				SetFilterVars();
			}
			void SetPassRate(const f64 &inp_frequency)
			{
				p_frequency = (f80) inp_frequency;

				SetFilterVars();
			}
			inline f64 Run(const f64 &inp)
			{
				const f64 spl_delay = (fq0 * old_inp) - (fq1 * inp);

				old_inp = (f64) inp;

				buffer = (fq0 * inp) - (fq1 * buffer) + SCRFT_dn_f64;

				return (spl_delay - buffer);
			}
			inline void RunFx(f64 &inp)
			{
				const f64 spl_delay = (fq0 * old_inp) - (fq1 * inp);

				old_inp = (f64) inp;

				buffer = (fq0 * inp) - (fq1 * buffer) + SCRFT_dn_f64;

				inp = f64 (spl_delay - buffer);
			}
			EQ_HP() :
				p_frequency( (f80) 1.0L ),
				sp_rate( (f80) 44100.0L ),
				buffer( 0.0 )
			{
				SetFilterVars();
			}
			EQ_HP(const f64 pass_frequency) :
				p_frequency( (f80) pass_frequency ),
				sp_rate( (f80) 44100.0L ),
				buffer( 0.0 )
			{
				SetFilterVars();
			}
		}; // struct EQ_HP
		//! ----------------------------------------------------------------
		//! --- FX Component :: EQ Filter :: Standard DP (Simple Delay Sync Pass) --
		//! ----------------------------------------------------------------
		struct SCRFT_EXPORT EQ_DP
		{
			f80 p_frequency;

			f80 sp_rate;
			f64 fq0, fq1, buffer;

			inline void Clear()
			{
				buffer = 0.0;
			}
			void SetFilterVars()
			{
				if ( sp_rate < (f80) 44100.0L )
					sp_rate = (f80) 44100.0L;

				if ( p_frequency > f80 (sp_rate * (f80) 0.5L) )
					p_frequency = f80 (sp_rate * (f80) 0.5L);
				if ( p_frequency < (f80) 0.0000012L )
					p_frequency = (f80) 0.0000012L;

				const f80 t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * p_frequency / sp_rate );
				fq0 = f64 (f80 ((f80) 1.0L - t));
				fq1 = f64 (f80 (-t));

				Clear();
			}
			void SetSampleRate(const f64 &inp_rate)
			{
				sp_rate = (f80) inp_rate;

				SetFilterVars();
			}
			void SetPassRate(const f64 &inp_frequency)
			{
				p_frequency = (f80) inp_frequency;

				SetFilterVars();
			}
			inline f64 Run(const f64 &inp)
			{
				const f64 spl_delay = (fq0 * buffer) - (fq1 * inp);

				buffer = (f64) inp;

				return spl_delay;
			}
			inline void RunFx(f64 &inp)
			{
				const f64 spl_delay = (fq0 * buffer) - (fq1 * inp);

				buffer = (f64) inp;

				inp = (f64) spl_delay;
			}
			EQ_DP() :
				p_frequency( (f80) 1.0L ),
				sp_rate( (f80) 44100.0L ),
				buffer( 0.0 )
			{
				SetFilterVars();
			}
			EQ_DP(const f64 pass_frequency) :
				p_frequency( (f80) pass_frequency ),
				sp_rate( (f80) 44100.0L ),
				buffer( 0.0 )
			{
				SetFilterVars();
			}
		}; // struct EQ_DP
		//! ----------------------------------------------------------------
		//! --- FX Component :: EQ Filter :: Dual LP (Dual-Rate Low Pass) --
		//! ----------------------------------------------------------------
		struct SCRFT_EXPORT EQ_Dual_LP
		{
			f80 p_frequency_a;
			f80 p_frequency_b;

			f80 sp_rate;
			f64 fq0_a, fq1_a;
			f64 fq0_b, fq1_b;
			f64 buffer;

			inline void Clear()
			{
				buffer = 0.0;
			}
			void SetFilterVars()
			{
				if ( sp_rate < (f80) 44100.0L )
					sp_rate = (f80) 44100.0L;

				if ( p_frequency_a > f80 (sp_rate * (f80) 0.5L) )
					p_frequency_a = f80 (sp_rate * (f80) 0.5L);
				if ( p_frequency_a < (f80) 0.0000012L )
					p_frequency_a = (f80) 0.0000012L;

				if ( p_frequency_b > f80 (sp_rate * (f80) 0.5L) )
					p_frequency_b = f80 (sp_rate * (f80) 0.5L);
				if ( p_frequency_b < (f80) 0.0000012L )
					p_frequency_b = (f80) 0.0000012L;

				f80 t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * p_frequency_a / sp_rate );
				fq0_a = f64 (f80 ((f80) 1.0L - t));
				fq1_b = f64 (f80 (-t));

				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * p_frequency_b / sp_rate );
				fq0_b = f64 (f80 ((f80) 1.0L - t));
				fq1_b = f64 (f80 (-t));

				Clear();
			}
			void SetSampleRate(const f64 &inp_rate)
			{
				sp_rate = (f80) inp_rate;

				SetFilterVars();
			}
			void SetPassRates(const f64 &inp_frequency_a, const f64 &inp_frequency_b)
			{
				p_frequency_a = (f80) inp_frequency_a;
				p_frequency_b = (f80) inp_frequency_b;

				SetFilterVars();
			}
			inline f64 Run(const f64 &inp)
			{
				if ( scft_Abs64( (f64) inp ) >= scft_Abs64( buffer ) )
					buffer = (fq0_a * inp) - (fq1_a * buffer) + SCRFT_dn_f64;
				else
					buffer = (fq0_b * inp) - (fq1_b * buffer) + SCRFT_dn_f64;

				return buffer;
			}
			inline void RunFx(f64 &inp)
			{
				if ( scft_Abs64( (f64) inp ) >= scft_Abs64( buffer ) )
					buffer = (fq0_a * inp) - (fq1_a * buffer) + SCRFT_dn_f64;
				else
					buffer = (fq0_b * inp) - (fq1_b * buffer) + SCRFT_dn_f64;

				inp = (f64) buffer;
			}
			EQ_Dual_LP() :
				p_frequency_a( (f80) 1.0L ),
				p_frequency_b( (f80) 1.0L ),
				sp_rate( (f80) 44100.0L ),
				buffer( 0.0 )
			{
				SetFilterVars();
			}
			EQ_Dual_LP(const f64 pass_frequency_a, const f64 pass_frequency_b) :
				p_frequency_a( (f80) pass_frequency_a ),
				p_frequency_b( (f80) pass_frequency_b ),
				sp_rate( (f80) 44100.0L ),
				buffer( 0.0 )
			{
				SetFilterVars();
			}
		}; // struct EQ_Dual_LP

	} // namespace Modules
} // namespace ScorchCrafter

#endif // SCORCHCRAFTER_MODULE_EQ_xP_INC
