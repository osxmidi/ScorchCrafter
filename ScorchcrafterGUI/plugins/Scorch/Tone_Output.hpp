#ifndef SCORCHCRAFTER_MODULE_Tone_Output_INC
#define SCORCHCRAFTER_MODULE_Tone_Output_INC

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
		//! --- FX Component :: Tone EQ Output --
		//! ----------------------------------------------------------------
		struct SCRFT_EXPORT Output_Tone_Stack
		{
			const f64 dn;

			f80 sp_rate;

			f64 adj_bass, adj_mids, adj_treble, adj_presence, adj_contour;
			const f64 min_bass, min_mids, min_treble, min_presence, min_contour;
			const f64 max_bass, max_mids, max_treble, max_presence, max_contour;

			const f64 master_vol_adj;

			f64 fq0_bass, fq1_bass, fq2_bass, fq3_bass;
			f64 fq0_mids, fq1_mids, fq2_mids, fq3_mids;
			f64 fq0_treble, fq1_treble, fq2_treble, fq3_treble;
			f64 fq0_presence, fq1_presence, fq2_presence, fq3_presence;
			f64 fq0_contour, fq1_contour, fq2_contour, fq3_contour;

			f64 fq0_final, fq1_final, fq2_final, fq3_final;

			f64 buf0_bass, buf1_bass, buf2_bass, buf3_bass;
			f64 buf0_mids, buf1_mids, buf2_mids, buf3_mids;
			f64 buf0_treble, buf1_treble, buf2_treble, buf3_treble;
			f64 buf0_presence, buf1_presence, buf2_presence, buf3_presence;
			f64 buf0_contour, buf1_contour, buf2_contour, buf3_contour;

			f64 buf00_final, buf01_final, buf02_final, buf03_final, buf04_final, buf05_final,
				buf06_final, buf07_final, buf08_final, buf09_final, buf10_final, buf11_final;

			inline void Clear()
			{
				buf0_bass = 0.0; buf1_bass = 0.0; buf2_bass = 0.0; buf3_bass = 0.0;
				buf0_mids = 0.0; buf1_mids = 0.0; buf2_mids = 0.0; buf3_mids = 0.0;
				buf0_treble = 0.0; buf1_treble = 0.0; buf2_treble = 0.0; buf3_treble = 0.0;
				buf0_presence = 0.0; buf1_presence = 0.0; buf2_presence = 0.0; buf3_presence = 0.0;
				buf0_contour = 0.0; buf1_contour = 0.0; buf2_contour = 0.0; buf3_contour = 0.0;

				buf00_final = 0.0; buf01_final = 0.0; buf02_final = 0.0; buf03_final = 0.0; buf04_final = 0.0; buf05_final = 0.0;
				buf06_final = 0.0; buf07_final = 0.0; buf08_final = 0.0; buf09_final = 0.0; buf10_final = 0.0; buf11_final = 0.0;
			}
			void SetSampleRate(const f64 &inp)
			{
				sp_rate = (f80) inp;

				if ( sp_rate < (f80) 44100.0L )
					sp_rate = (f80) 44100.0L;

				f80 t = (f80) 0.0L;

				// Bass
				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * (f80) 12.0L / sp_rate ); // HP (EQ Band Bottom) Frequency
				fq0_bass = f64 (1.0L - t);
				fq1_bass = f64 (-t);
				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * (f80) 160.0L / sp_rate ); // LP (EQ Band Top) Frequency
				fq2_bass = f64 (1.0L - t);
				fq3_bass = f64 (-t);

				// Mids
				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * (f80) 160.0L / sp_rate ); // HP (EQ Band Bottom) Frequency
				fq0_mids = f64 (1.0L - t);
				fq1_mids = f64 (-t);
				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * (f80) 1200.0L / sp_rate ); // LP (EQ Band Top) Frequency
				fq2_mids = f64 (1.0L - t);
				fq3_mids = f64 (-t);

				// Treble
				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * (f80) 1200.0L / sp_rate ); // HP (EQ Band Bottom) Frequency
				fq0_treble = f64 (1.0L - t);
				fq1_treble = f64 (-t);
				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * (f80) 5000.0L / sp_rate ); // LP (EQ Band Top) Frequency
				fq2_treble = f64 (1.0L - t);
				fq3_treble = f64 (-t);

				// Presence (High treble)
				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * (f80) 3000.0L / sp_rate ); // HP (EQ Band Bottom) Frequency
				fq0_presence = f64 (1.0L - t);
				fq1_presence = f64 (-t);
				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * (f80) 7500.0L / sp_rate ); // LP (EQ Band Top) Frequency
				fq2_presence = f64 (1.0L - t);
				fq3_presence = f64 (-t);

				// Contour (Mid-High EQ, used to shape or "scoop" sound)
				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * (f80) 700.0L / sp_rate ); // HP (EQ Band Bottom) Frequency
				fq0_contour = f64 (1.0L - t);
				fq1_contour = f64 (-t);
				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * (f80) 900.0L / sp_rate ); // LP (EQ Band Top) Frequency
				fq2_contour = f64 (1.0L - t);
				fq3_contour = f64 (-t);

				// Final, Ending EQ adjustment frequencies, for trimming (mostly) inaudible excess sound at extreme low and high frequencies
				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * (f80) 12.0L / sp_rate ); // HP (EQ Band Bottom) Frequency
				fq0_final = f64 (1.0L - t);
				fq1_final = f64 (-t);
				t = (f80) expl( (f80) -2.0L * SCRFT_pi_f80 * (f80) 12000.0L / sp_rate ); // LP (EQ Band Top) Frequency
				fq2_final = f64 (1.0L - t);
				fq3_final = f64 (-t);

				Clear();
			}
			inline void InputBandControl_Bass(const f64 &inp)
			{
				adj_bass = scft_Avg64( min_bass, max_bass, inp );
			}
			inline void InputBandControl_Mids(const f64 &inp)
			{
				adj_mids = scft_Avg64( min_mids, max_mids, inp );
			}
			inline void InputBandControl_Treble(const f64 &inp)
			{
				adj_treble = scft_Avg64( min_treble, max_treble, inp );
			}
			inline void InputBandControl_Presence(const f64 &inp)
			{
				adj_presence = scft_Avg64( min_presence, max_presence, inp );
			}
			inline void InputBandControl_Contour(const f64 &inp)
			{
				adj_contour = scft_Avg64( min_contour, max_contour, inp );
			}
			inline void ZeroBandValues()
			{
				InputBandControl_Bass( 0.5 );
				InputBandControl_Mids( 0.5 );
				InputBandControl_Treble( 0.5 );
				InputBandControl_Presence( 0.5 );
				InputBandControl_Contour( 0.5 );
			}
			inline void Init() const
			{}
			inline f64 Run(const f64 &inp)
			{
				f64 spl_fx = inp;

				// First Pass(es)
				f64 eq0 = spl_fx;
				f64 eq1 = spl_fx;
				f64 eq2 = spl_fx;
				eq0 -= ( buf0_bass = (fq0_bass*eq0) - (fq1_bass*buf0_bass) + dn );
				eq0 = ( buf1_bass = (fq2_bass*eq0) - (fq3_bass*buf1_bass) + dn );
				eq1 -= ( buf0_mids = (fq0_mids*eq1) - (fq1_mids*buf0_mids) + dn );
				eq1 = ( buf1_mids = (fq2_mids*eq1) - (fq3_mids*buf1_mids) + dn );
				eq2 -= ( buf0_treble = (fq0_treble*eq2) - (fq1_treble*buf0_treble) + dn );
				eq2 = ( buf1_treble = (fq2_treble*eq2) - (fq3_treble*buf1_treble) + dn );
				spl_fx += (eq0 * adj_bass) + (eq1 * adj_mids) + (eq2 * adj_treble);

				f64 eq3 = spl_fx;
				f64 eq4 = spl_fx;
				eq3 -= ( buf0_presence = (fq0_presence*eq3) - (fq1_presence*buf0_presence) + dn );
				eq3 = ( buf1_presence = (fq2_presence*eq3) - (fq3_presence*buf1_presence) + dn );
				eq4 -= ( buf0_contour = (fq0_contour*eq4) - (fq1_contour*buf0_contour) + dn );
				eq4 = ( buf1_contour = (fq2_contour*eq4) - (fq3_contour*buf1_contour) + dn );
				spl_fx += (eq3 * adj_presence) + (eq4 * adj_contour);

				// Second Pass(es)
				eq0 = spl_fx;
				eq1 = spl_fx;
				eq2 = spl_fx;
				eq0 -= ( buf2_bass = (fq0_bass*eq0) - (fq1_bass*buf2_bass) + dn );
				eq0 = ( buf3_bass = (fq2_bass*eq0) - (fq3_bass*buf3_bass) + dn );
				eq1 -= ( buf2_mids = (fq0_mids*eq1) - (fq1_mids*buf2_mids) + dn );
				eq1 = ( buf3_mids = (fq2_mids*eq1) - (fq3_mids*buf3_mids) + dn );
				eq2 -= ( buf2_treble = (fq0_treble*eq2) - (fq1_treble*buf2_treble) + dn );
				eq2 = ( buf3_treble = (fq2_treble*eq2) - (fq3_treble*buf3_treble) + dn );
				spl_fx += (eq0 * adj_bass) + (eq1 * adj_mids) + (eq2 * adj_treble);

				eq3 = spl_fx;
				eq4 = spl_fx;
				eq3 -= ( buf2_presence = (fq0_presence*eq3) - (fq1_presence*buf2_presence) + dn );
				eq3 = ( buf3_presence = (fq2_presence*eq3) - (fq3_presence*buf3_presence) + dn );
				eq4 -= ( buf2_contour = (fq0_contour*eq4) - (fq1_contour*buf2_contour) + dn );
				eq4 = ( buf3_contour = (fq2_contour*eq4) - (fq3_contour*buf3_contour) + dn );
				spl_fx += (eq3 * adj_presence) + (eq4 * adj_contour);

				// Final Output EQ Pass(es)
				spl_fx -= ( buf00_final = (fq0_final*spl_fx) - (fq1_final*buf00_final) + dn );
				spl_fx -= ( buf01_final = (fq0_final*spl_fx) - (fq1_final*buf01_final) + dn );
				spl_fx -= ( buf02_final = (fq0_final*spl_fx) - (fq1_final*buf02_final) + dn );
				spl_fx -= ( buf03_final = (fq0_final*spl_fx) - (fq1_final*buf03_final) + dn );
				spl_fx -= ( buf04_final = (fq0_final*spl_fx) - (fq1_final*buf04_final) + dn );
				spl_fx -= ( buf05_final = (fq0_final*spl_fx) - (fq1_final*buf05_final) + dn );
				spl_fx -= ( buf06_final = (fq0_final*spl_fx) - (fq1_final*buf06_final) + dn );
				spl_fx -= ( buf07_final = (fq0_final*spl_fx) - (fq1_final*buf07_final) + dn );
				spl_fx = ( buf08_final = (fq2_final*spl_fx) - (fq3_final*buf08_final) + dn );
				spl_fx = ( buf09_final = (fq2_final*spl_fx) - (fq3_final*buf09_final) + dn );
				spl_fx = ( buf10_final = (fq2_final*spl_fx) - (fq3_final*buf10_final) + dn );
				spl_fx = ( buf11_final = (fq2_final*spl_fx) - (fq3_final*buf11_final) + dn );

				spl_fx *= master_vol_adj;

				return spl_fx;
			}
			Output_Tone_Stack(const s32 inp_prm_set = 0) :
				dn( SCRFT_dn_f64 ),

				min_bass		(  0.00 ),
				min_mids		(  0.00 ),
				min_treble		(  0.00 ),
				min_presence	(  0.00 ),
				min_contour		( -1.00 ),

				max_bass		(  6.00 ),
				max_mids		(  2.00 ),
				max_treble		(  6.00 ),
				max_presence	(  1.65 ),
				max_contour		(  1.00 ),

				master_vol_adj( 0.0453 )
			{
				SetSampleRate( (f80) 44100.0L );

				ZeroBandValues();
			}
		}; // struct Output_Tone_Stack
		//! ----------------------------------------------------------------
		//! --- FX Component :: Tone EQ Output version 2 --
		//! ----------------------------------------------------------------
		struct SCRFT_EXPORT Output_Tone_Stack_v2
		{
			//! ----------------------------------------------------------------
			//! --- FX Component :: Tone EQ Output version 2 :: Tone EQ Adjustment Band, Single --
			//! ----------------------------------------------------------------
			struct SCRFT_EXPORT Tone_FX
			{
				f64 prm_tone_volume;

				EQ_LP f0_LP, f1_LP;
				EQ_HP f0_HP, f1_HP;

				EQ_DP f0_LP_DP, f1_LP_DP;
				EQ_DP f0_HP_DP, f1_HP_DP;

				inline void Clear()
				{
					f0_LP.Clear();
					f1_LP.Clear();
					f0_HP.Clear();
					f1_HP.Clear();

					f0_LP_DP.Clear();
					f1_LP_DP.Clear();
					f0_HP_DP.Clear();
					f1_HP_DP.Clear();
				}
				inline void SetVolume(const f64 &inp)
				{
					prm_tone_volume = (f64) inp;
				}
				inline void SetSampleRate(const f64 &inp)
				{
					f0_LP.SetSampleRate( inp );
					f1_LP.SetSampleRate( inp );
					f0_HP.SetSampleRate( inp );
					f1_HP.SetSampleRate( inp );

					f0_LP_DP.SetSampleRate( inp );
					f1_LP_DP.SetSampleRate( inp );
					f0_HP_DP.SetSampleRate( inp );
					f1_HP_DP.SetSampleRate( inp );
				}
				inline void SetFrequencies(const f64 band_low, const f64 band_high)
				{
					f0_HP.SetPassRate( band_low );
					f1_HP.SetPassRate( band_low );
					f0_LP.SetPassRate( band_high );
					f1_LP.SetPassRate( band_high );

					f0_HP_DP.SetPassRate( band_low );
					f1_HP_DP.SetPassRate( band_low );
					f0_LP_DP.SetPassRate( band_high );
					f1_LP_DP.SetPassRate( band_high );
				}
				inline f64 RunEQ(const f64 &inp)
				{
					f64 spl_tone = inp;

					f0_HP.RunFx( spl_tone );
					f1_HP.RunFx( spl_tone );
					f0_LP.RunFx( spl_tone );
					f1_LP.RunFx( spl_tone );

					return f64 (spl_tone * prm_tone_volume);
				}
				inline f64 RunDP(const f64 &inp)
				{
					f64 spl_fx = inp;

					f0_HP_DP.RunFx( spl_fx );
					f1_HP_DP.RunFx( spl_fx );
					f0_LP_DP.RunFx( spl_fx );
					f1_LP_DP.RunFx( spl_fx );

					return spl_fx;
				}
				inline f64 Run(const f64 &inp)
				{
					f64 spl_fx = inp;
					f64 spl_tone = spl_fx;

					f0_HP.RunFx( spl_tone );
					f1_HP.RunFx( spl_tone );
					f0_LP.RunFx( spl_tone );
					f1_LP.RunFx( spl_tone );

					f0_HP_DP.RunFx( spl_fx );
					f1_HP_DP.RunFx( spl_fx );
					f0_LP_DP.RunFx( spl_fx );
					f1_LP_DP.RunFx( spl_fx );

					return f64 (spl_fx + (spl_tone * prm_tone_volume));
				}
			};

			// ID for Which set of parameters are used (Zero will use defaults, negative values result in a BYPASS effect where output matches input)
			s32 prm_set;

			f64 sp_rate;

			f64 prm_adj_bass, prm_adj_mids, prm_adj_treble, prm_adj_presence, prm_adj_contour;

			f64 p_min_bass, p_min_mids, p_min_treble, p_min_presence, p_min_contour;
			f64 p_max_bass, p_max_mids, p_max_treble, p_max_presence, p_max_contour;
			f64 p_master_vol_adj;

			Tone_FX Eq_Band_0_Bass, Eq_Band_1_Bass, Eq_Band_2_Bass;
			Tone_FX Eq_Band_0_Mid, Eq_Band_1_Mid, Eq_Band_2_Mid;
			Tone_FX Eq_Band_0_Treble, Eq_Band_1_Treble, Eq_Band_2_Treble;
			Tone_FX Eq_Band_0_Presence, Eq_Band_1_Presence, Eq_Band_2_Presence;
			Tone_FX Eq_Band_0_Contour, Eq_Band_1_Contour, Eq_Band_2_Contour;

			EQ_HP f0_HP, f1_HP, f2_HP, f3_HP, f4_HP, f5_HP, f6_HP, f7_HP;
			EQ_LP f0_LP, f1_LP, f2_LP, f3_LP, f4_LP, f5_LP, f6_LP, f7_LP;

			inline void Clear()
			{
				f0_LP.Clear();
				f1_LP.Clear();
				f2_LP.Clear();
				f3_LP.Clear();
				f4_LP.Clear();
				f5_LP.Clear();
				f6_LP.Clear();
				f7_LP.Clear();

				f0_HP.Clear();
				f1_HP.Clear();
				f2_HP.Clear();
				f3_HP.Clear();
				f4_HP.Clear();
				f5_HP.Clear();
				f6_HP.Clear();
				f7_HP.Clear();

				Eq_Band_0_Bass.Clear();
				Eq_Band_1_Bass.Clear();
				Eq_Band_2_Bass.Clear();

				Eq_Band_0_Mid.Clear();
				Eq_Band_1_Mid.Clear();
				Eq_Band_2_Mid.Clear();

				Eq_Band_0_Treble.Clear();
				Eq_Band_1_Treble.Clear();
				Eq_Band_2_Treble.Clear();

				Eq_Band_0_Presence.Clear();
				Eq_Band_1_Presence.Clear();
				Eq_Band_2_Presence.Clear();

				Eq_Band_0_Contour.Clear();
				Eq_Band_1_Contour.Clear();
				Eq_Band_2_Contour.Clear();
			}
			void SetSampleRate(const f64 &inp)
			{
				sp_rate = (f64) inp;

				if ( sp_rate < (f64) 44100.0 )
					sp_rate = (f64) 44100.0;

				f0_LP.SetSampleRate( sp_rate );
				f1_LP.SetSampleRate( sp_rate );
				f2_LP.SetSampleRate( sp_rate );
				f3_LP.SetSampleRate( sp_rate );
				f4_LP.SetSampleRate( sp_rate );
				f5_LP.SetSampleRate( sp_rate );
				f6_LP.SetSampleRate( sp_rate );
				f7_LP.SetSampleRate( sp_rate );

				f0_HP.SetSampleRate( sp_rate );
				f1_HP.SetSampleRate( sp_rate );
				f2_HP.SetSampleRate( sp_rate );
				f3_HP.SetSampleRate( sp_rate );
				f4_HP.SetSampleRate( sp_rate );
				f5_HP.SetSampleRate( sp_rate );
				f6_HP.SetSampleRate( sp_rate );
				f7_HP.SetSampleRate( sp_rate );

				Eq_Band_0_Bass.SetSampleRate( sp_rate );
				Eq_Band_1_Bass.SetSampleRate( sp_rate );
				Eq_Band_2_Bass.SetSampleRate( sp_rate );

				Eq_Band_0_Mid.SetSampleRate( sp_rate );
				Eq_Band_1_Mid.SetSampleRate( sp_rate );
				Eq_Band_2_Mid.SetSampleRate( sp_rate );

				Eq_Band_0_Treble.SetSampleRate( sp_rate );
				Eq_Band_1_Treble.SetSampleRate( sp_rate );
				Eq_Band_2_Treble.SetSampleRate( sp_rate );

				Eq_Band_0_Presence.SetSampleRate( sp_rate );
				Eq_Band_1_Presence.SetSampleRate( sp_rate );
				Eq_Band_2_Presence.SetSampleRate( sp_rate );

				Eq_Band_0_Contour.SetSampleRate( sp_rate );
				Eq_Band_1_Contour.SetSampleRate( sp_rate );
				Eq_Band_2_Contour.SetSampleRate( sp_rate );

				Clear();
			}
			inline void InputBandControl_Bass(const f64 &inp)
			{
				prm_adj_bass = scft_Avg64( p_min_bass, p_max_bass, inp );

				Eq_Band_0_Bass.SetVolume( prm_adj_bass );
				Eq_Band_1_Bass.SetVolume( prm_adj_bass );
				Eq_Band_2_Bass.SetVolume( prm_adj_bass );
			}
			inline void InputBandControl_Mids(const f64 &inp)
			{
				prm_adj_mids = scft_Avg64( p_min_mids, p_max_mids, inp );

				Eq_Band_0_Mid.SetVolume( prm_adj_mids );
				Eq_Band_1_Mid.SetVolume( prm_adj_mids );
				Eq_Band_2_Mid.SetVolume( prm_adj_mids );
			}
			inline void InputBandControl_Treble(const f64 &inp)
			{
				prm_adj_treble = scft_Avg64( p_min_treble, p_max_treble, inp );

				Eq_Band_0_Treble.SetVolume( prm_adj_treble );
				Eq_Band_1_Treble.SetVolume( prm_adj_treble );
				Eq_Band_2_Treble.SetVolume( prm_adj_treble );
			}
			inline void InputBandControl_Presence(const f64 &inp)
			{
				prm_adj_presence = scft_Avg64( p_min_presence, p_max_presence, inp );

				Eq_Band_0_Presence.SetVolume( prm_adj_presence );
				Eq_Band_1_Presence.SetVolume( prm_adj_presence );
				Eq_Band_2_Presence.SetVolume( prm_adj_presence );
			}
			inline void InputBandControl_Contour(const f64 &inp)
			{
				prm_adj_contour = scft_Avg64( p_min_contour, p_max_contour, inp );

				Eq_Band_0_Contour.SetVolume( prm_adj_contour );
				Eq_Band_1_Contour.SetVolume( prm_adj_contour );
				Eq_Band_2_Contour.SetVolume( prm_adj_contour );
			}
			inline void ZeroBandValues()
			{
				InputBandControl_Bass( 0.5 );
				InputBandControl_Mids( 0.5 );
				InputBandControl_Treble( 0.5 );
				InputBandControl_Presence( 0.5 );
				InputBandControl_Contour( 0.5 );
			}
			inline void Init() const
			{}
			inline void InitInternals()
			{
				f64 p_output_HP_freq =		12.0;
				f64 p_output_LP_freq =		9000.0;

				p_min_bass =		  0.0000;
				p_max_bass =		  2.0000;
				f64 p_freq_bass_low =		50.0;
				f64 p_freq_bass_high =		200.0;

				p_min_mids =		  0.0000;
				p_max_mids =		  2.0000;
				f64 p_freq_mids_low =		200.0;
				f64 p_freq_mids_high =		1200.0;

				p_min_treble =		  0.0000;
				p_max_treble =		  2.0000;
				f64 p_freq_treble_low =		1200.0;
				f64 p_freq_treble_high =	9000.0;

				p_min_presence =	 -1.0000;
				p_max_presence =	  1.0000;
				f64 p_freq_presence_low =	3000.0;
				f64 p_freq_presence_high =	5000.0;

				p_min_contour =		 -1.0000;
				p_max_contour =		  1.0000;
				f64 p_freq_contour_low =	700.0;
				f64 p_freq_contour_high =	900.0;

				p_master_vol_adj =	  0.5000;

				if ( prm_set == 1 )
				{
					p_output_HP_freq =			35.0;
					p_output_LP_freq =			12000.0;

					p_min_bass =			 -1.0000;
					p_max_bass =			  2.5000;
					p_freq_bass_low =			90.0;
					p_freq_bass_high =			200.0;

					p_min_mids =			 -1.0000;
					p_max_mids =			  1.0000;
					p_freq_mids_low =			200.0;
					p_freq_mids_high =			1600.0;

					p_min_treble =			 -1.0000;
					p_max_treble =		 	  2.5000;
					p_freq_treble_low =			1600.0;
					p_freq_treble_high =		5000.0;

					p_min_presence =	 	 -1.0000;
					p_max_presence =	 	  2.0000;
					p_freq_presence_low =		5000.0;
					p_freq_presence_high =		7500.0;

					p_min_contour =			 -1.0000;
					p_max_contour =			  1.0000;
					p_freq_contour_low =		700.0;
					p_freq_contour_high =		900.0;

					p_master_vol_adj =	  	0.25023;
				}

				Eq_Band_0_Bass.SetFrequencies( p_freq_bass_low, p_freq_bass_high );
				Eq_Band_1_Bass.SetFrequencies( p_freq_bass_low, p_freq_bass_high );
				Eq_Band_2_Bass.SetFrequencies( p_freq_bass_low, p_freq_bass_high );

				Eq_Band_0_Mid.SetFrequencies( p_freq_mids_low, p_freq_mids_high );
				Eq_Band_1_Mid.SetFrequencies( p_freq_mids_low, p_freq_mids_high );
				Eq_Band_2_Mid.SetFrequencies( p_freq_mids_low, p_freq_mids_high );

				Eq_Band_0_Treble.SetFrequencies( p_freq_treble_low, p_freq_treble_high );
				Eq_Band_1_Treble.SetFrequencies( p_freq_treble_low, p_freq_treble_high );
				Eq_Band_2_Treble.SetFrequencies( p_freq_treble_low, p_freq_treble_high );

				Eq_Band_0_Presence.SetFrequencies( p_freq_presence_low, p_freq_presence_high );
				Eq_Band_1_Presence.SetFrequencies( p_freq_presence_low, p_freq_presence_high );
				Eq_Band_2_Presence.SetFrequencies( p_freq_presence_low, p_freq_presence_high );

				Eq_Band_0_Contour.SetFrequencies( p_freq_contour_low, p_freq_contour_high );
				Eq_Band_1_Contour.SetFrequencies( p_freq_contour_low, p_freq_contour_high );
				Eq_Band_2_Contour.SetFrequencies( p_freq_contour_low, p_freq_contour_high );

				f0_HP.SetPassRate( p_output_HP_freq );
				f1_HP.SetPassRate( p_output_HP_freq );
				f2_HP.SetPassRate( p_output_HP_freq );
				f3_HP.SetPassRate( p_output_HP_freq );
				f4_HP.SetPassRate( p_output_HP_freq );
				f5_HP.SetPassRate( p_output_HP_freq );
				f6_HP.SetPassRate( p_output_HP_freq );
				f7_HP.SetPassRate( p_output_HP_freq );

				f0_LP.SetPassRate( p_output_LP_freq );
				f1_LP.SetPassRate( p_output_LP_freq );
				f2_LP.SetPassRate( p_output_LP_freq );
				f3_LP.SetPassRate( p_output_LP_freq );
				f4_LP.SetPassRate( p_output_LP_freq );
				f5_LP.SetPassRate( p_output_LP_freq );
				f6_LP.SetPassRate( p_output_LP_freq );
				f7_LP.SetPassRate( p_output_LP_freq );

				ZeroBandValues();
			}
			inline f64 Run(const f64 &inp)
			{
				f64 spl_fx = inp;

				if ( prm_set < 0 )
					return spl_fx;

				// Pass 1
				{
					const f64 spl_bass = Eq_Band_0_Bass.RunEQ( spl_fx );
					const f64 spl_mid = Eq_Band_0_Mid.RunEQ( spl_fx );
					const f64 spl_treble = Eq_Band_0_Treble.RunEQ( spl_fx );

					spl_fx = Eq_Band_0_Bass.RunDP( spl_fx );
					spl_fx = Eq_Band_0_Mid.RunDP( spl_fx );
					spl_fx = Eq_Band_0_Treble.RunDP( spl_fx );

					spl_fx += f64 (spl_bass + spl_mid + spl_treble);

					const f64 spl_presence = Eq_Band_0_Presence.RunEQ( spl_fx );
					const f64 spl_contour = Eq_Band_0_Contour.RunEQ( spl_fx );

					spl_fx = Eq_Band_0_Presence.RunDP( spl_fx );
					spl_fx = Eq_Band_0_Contour.RunDP( spl_fx );

					spl_fx += f64 (spl_presence + spl_contour);
				}

				// Pass 2
				{
					const f64 spl_bass = Eq_Band_1_Bass.RunEQ( spl_fx );
					const f64 spl_mid = Eq_Band_1_Mid.RunEQ( spl_fx );
					const f64 spl_treble = Eq_Band_1_Treble.RunEQ( spl_fx );

					spl_fx = Eq_Band_1_Bass.RunDP( spl_fx );
					spl_fx = Eq_Band_1_Mid.RunDP( spl_fx );
					spl_fx = Eq_Band_1_Treble.RunDP( spl_fx );

					spl_fx += f64 (spl_bass + spl_mid + spl_treble);

					const f64 spl_presence = Eq_Band_1_Presence.RunEQ( spl_fx );
					const f64 spl_contour = Eq_Band_1_Contour.RunEQ( spl_fx );

					spl_fx = Eq_Band_1_Presence.RunDP( spl_fx );
					spl_fx = Eq_Band_1_Contour.RunDP( spl_fx );

					spl_fx += f64 (spl_presence + spl_contour);
				}

				// Pass 3
				{
					const f64 spl_bass = Eq_Band_2_Bass.RunEQ( spl_fx );
					const f64 spl_mid = Eq_Band_2_Mid.RunEQ( spl_fx );
					const f64 spl_treble = Eq_Band_2_Treble.RunEQ( spl_fx );

					spl_fx = Eq_Band_2_Bass.RunDP( spl_fx );
					spl_fx = Eq_Band_2_Mid.RunDP( spl_fx );
					spl_fx = Eq_Band_2_Treble.RunDP( spl_fx );

					spl_fx += f64 (spl_bass + spl_mid + spl_treble);

					const f64 spl_presence = Eq_Band_2_Presence.RunEQ( spl_fx );
					const f64 spl_contour = Eq_Band_2_Contour.RunEQ( spl_fx );

					spl_fx = Eq_Band_2_Presence.RunDP( spl_fx );
					spl_fx = Eq_Band_2_Contour.RunDP( spl_fx );

					spl_fx += f64 (spl_presence + spl_contour);
				}

				// Output Bottom and Top Edge Trim Pass
				f0_HP.RunFx( spl_fx );
				f1_HP.RunFx( spl_fx );
				f2_HP.RunFx( spl_fx );
				f3_HP.RunFx( spl_fx );
				f4_HP.RunFx( spl_fx );
				f5_HP.RunFx( spl_fx );
				f6_HP.RunFx( spl_fx );
				f7_HP.RunFx( spl_fx );

				f0_LP.RunFx( spl_fx );
				f1_LP.RunFx( spl_fx );
				f2_LP.RunFx( spl_fx );
				f3_LP.RunFx( spl_fx );
				f4_LP.RunFx( spl_fx );
				f5_LP.RunFx( spl_fx );
				f6_LP.RunFx( spl_fx );
				f7_LP.RunFx( spl_fx );

				spl_fx *= p_master_vol_adj;

				return spl_fx;
			}
			Output_Tone_Stack_v2(const s32 inp_prm_set = 0) :
				prm_set( (s32) inp_prm_set )
			{
				InitInternals();

				SetSampleRate( (f64) 44100.0 );
			}
		}; // struct Output_Tone_Stack

	} // namespace Modules
} // namespace ScorchCrafter

#endif // SCORCHCRAFTER_MODULE_Tone_Output_INC
