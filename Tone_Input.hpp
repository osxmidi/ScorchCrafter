#ifndef SCORCHCRAFTER_MODULE_Tone_Input_INC
#define SCORCHCRAFTER_MODULE_Tone_Input_INC

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
		//! --- FX Component :: Tone EQ Input --
		//! ----------------------------------------------------------------
		struct SCRFT_EXPORT Tone_Input
		{
			bool inp_bright;

			bool p_use_tone_adjust;
			const f64 p_tone_adjust;
			const f64 p_tone_adj_post_gain;

			EQ_HP f0_base_HP, f1_base_HP, f2_base_HP, f3_base_HP,
					f4_base_HP, f5_base_HP, f6_base_HP, f7_base_HP;

			EQ_LP f0_base_LP, f1_base_LP, f2_base_LP, f3_base_LP;

			EQ_HP f0_bright_HP, f1_bright_HP, f2_bright_HP, f3_bright_HP, f4_bright_HP, f5_bright_HP;

			EQ_HP f0_tone_HP, f1_tone_HP;
			EQ_LP f0_tone_LP, f1_tone_LP;
			EQ_DP f0_tone_HP_DP, f1_tone_HP_DP, f0_tone_LP_DP, f1_tone_LP_DP;

			inline void Clear()
			{
				f0_base_HP.Clear(); f1_base_HP.Clear(); f2_base_HP.Clear(); f3_base_HP.Clear();
				f4_base_HP.Clear(); f5_base_HP.Clear(); f6_base_HP.Clear(); f7_base_HP.Clear();

				f0_base_LP.Clear(); f1_base_LP.Clear(); f2_base_LP.Clear(); f3_base_LP.Clear();

				f0_bright_HP.Clear(); f1_bright_HP.Clear(); f2_bright_HP.Clear(); f3_bright_HP.Clear(); f4_bright_HP.Clear(); f5_bright_HP.Clear();

				f0_tone_HP.Clear(); f1_tone_HP.Clear();
				f0_tone_LP.Clear(); f1_tone_LP.Clear();
				f0_tone_HP_DP.Clear(); f1_tone_HP_DP.Clear(); f0_tone_LP_DP.Clear(); f1_tone_LP_DP.Clear();
			}
			inline void SetSampleRate(const f64 &inp_rate)
			{
				f64 sp_rate = (f64) inp_rate;

				if ( sp_rate < 44100.0 )
					sp_rate = 44100.0;

				f0_base_HP.SetSampleRate( sp_rate ); f1_base_HP.SetSampleRate( sp_rate ); f2_base_HP.SetSampleRate( sp_rate ); f3_base_HP.SetSampleRate( sp_rate );
				f4_base_HP.SetSampleRate( sp_rate ); f5_base_HP.SetSampleRate( sp_rate ); f6_base_HP.SetSampleRate( sp_rate ); f7_base_HP.SetSampleRate( sp_rate );

				f0_base_LP.SetSampleRate( sp_rate ); f1_base_LP.SetSampleRate( sp_rate ); f2_base_LP.SetSampleRate( sp_rate ); f3_base_LP.SetSampleRate( sp_rate );

				f0_bright_HP.SetSampleRate( sp_rate ); f1_bright_HP.SetSampleRate( sp_rate ); f2_bright_HP.SetSampleRate( sp_rate ); f3_bright_HP.SetSampleRate( sp_rate );
				f4_bright_HP.SetSampleRate( sp_rate ); f5_bright_HP.SetSampleRate( sp_rate );

				f0_tone_HP.SetSampleRate( sp_rate ); f1_tone_HP.SetSampleRate( sp_rate );
				f0_tone_LP.SetSampleRate( sp_rate ); f1_tone_LP.SetSampleRate( sp_rate );
				f0_tone_HP_DP.SetSampleRate( sp_rate ); f1_tone_HP_DP.SetSampleRate( sp_rate ); f0_tone_LP_DP.SetSampleRate( sp_rate ); f1_tone_LP_DP.SetSampleRate( sp_rate );

				Clear();
			}
			inline f64 Run(const f64 &inp)
			{
				f64 spl_fx = (f64) inp;

				f0_base_HP.RunFx( spl_fx );
				f1_base_HP.RunFx( spl_fx );
				f2_base_HP.RunFx( spl_fx );
				f3_base_HP.RunFx( spl_fx );
				f4_base_HP.RunFx( spl_fx );
				f5_base_HP.RunFx( spl_fx );
				f6_base_HP.RunFx( spl_fx );
				f7_base_HP.RunFx( spl_fx );

				if ( inp_bright == true )
				{
					f0_bright_HP.RunFx( spl_fx );
					f1_bright_HP.RunFx( spl_fx );
					f2_bright_HP.RunFx( spl_fx );
					f3_bright_HP.RunFx( spl_fx );
					f4_bright_HP.RunFx( spl_fx );
					f5_bright_HP.RunFx( spl_fx );
					spl_fx *= 1.9200;
				}

				if ( p_use_tone_adjust == true )
				{
					// 1st pass
					{
						f64 spl_tone_adj = spl_fx;
						f0_tone_HP_DP.RunFx( spl_fx );
						f0_tone_LP_DP.RunFx( spl_fx );
						f0_tone_HP.RunFx( spl_tone_adj );
						f0_tone_LP.RunFx( spl_tone_adj );
						spl_fx += spl_tone_adj * p_tone_adjust;
					}
					// 2nd pass
					{
						f64 spl_tone_adj = spl_fx;
						f1_tone_HP_DP.RunFx( spl_fx );
						f1_tone_LP_DP.RunFx( spl_fx );
						f1_tone_HP.RunFx( spl_tone_adj );
						f1_tone_LP.RunFx( spl_tone_adj );
						spl_fx += spl_tone_adj * p_tone_adjust;
					}

					spl_fx *= p_tone_adj_post_gain;
				}

				f0_base_LP.RunFx( spl_fx );
				f1_base_LP.RunFx( spl_fx );
				f2_base_LP.RunFx( spl_fx );
				f3_base_LP.RunFx( spl_fx );

				return spl_fx;
			}
			inline void SetBright(const bool &bright)
			{
				inp_bright = (bool) bright;
			}
			Tone_Input(	const f64 std_freq = 129.0,
						const f64 bright_freq = 165.0,
						const f64 tone_adj_HP_freq = 430.0,
						const f64 tone_adj_LP_freq = 3020.0,
						const f64 tone_adj_mix = 0.5124,
						const f64 tone_adj_post_gain = 0.7023 ) :
				inp_bright( false ),
				p_use_tone_adjust( true ),
				p_tone_adjust( (f64) tone_adj_mix ),
				p_tone_adj_post_gain( (f64) tone_adj_post_gain )
			{
				f0_base_HP.SetPassRate( std_freq );
				f1_base_HP.SetPassRate( std_freq );
				f2_base_HP.SetPassRate( std_freq );
				f3_base_HP.SetPassRate( std_freq );
				f4_base_HP.SetPassRate( std_freq );
				f5_base_HP.SetPassRate( std_freq );
				f6_base_HP.SetPassRate( std_freq );
				f7_base_HP.SetPassRate( std_freq );

				f0_base_LP.SetPassRate( 7500.0 );
				f1_base_LP.SetPassRate( 7500.0 );
				f2_base_LP.SetPassRate( 7500.0 );
				f3_base_LP.SetPassRate( 7500.0 );

				f0_bright_HP.SetPassRate( bright_freq );
				f1_bright_HP.SetPassRate( bright_freq );
				f2_bright_HP.SetPassRate( bright_freq );
				f3_bright_HP.SetPassRate( bright_freq );
				f4_bright_HP.SetPassRate( bright_freq );
				f5_bright_HP.SetPassRate( bright_freq );

				f0_tone_HP.SetPassRate( tone_adj_HP_freq );
				f1_tone_HP.SetPassRate( tone_adj_HP_freq );
				f0_tone_LP.SetPassRate( tone_adj_LP_freq );
				f1_tone_LP.SetPassRate( tone_adj_LP_freq );
				f0_tone_HP_DP.SetPassRate( tone_adj_HP_freq );
				f1_tone_HP_DP.SetPassRate( tone_adj_HP_freq );
				f0_tone_LP_DP.SetPassRate( tone_adj_LP_freq );
				f1_tone_LP_DP.SetPassRate( tone_adj_LP_freq );

				SetSampleRate( 44100.0 );
			}
		}; // struct Tone_Input

	} // namespace Modules
} // namespace ScorchCrafter

#endif // SCORCHCRAFTER_MODULE_Tone_Input_INC
