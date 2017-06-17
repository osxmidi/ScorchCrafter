#ifndef SCORCHCRAFTER_PLUGIN_RAGESTOMP_H
#define SCORCHCRAFTER_PLUGIN_RAGESTOMP_H

#define SC_PLG_VER_A 1

#define SC_PLG_VER_B 1

#define SC_PLG_VER_C 1

#define SC_PLG_VER_D 1


#include "ScorchCrafter_Plugin.hpp"
// #include <cmath>

using namespace ::ScorchCrafter;
using namespace ::ScorchCrafter::DataTypes;
using namespace ::ScorchCrafter::Base;
using namespace ::ScorchCrafter::Plugins;

namespace ScorchCrafter
{
	namespace Base
	{
		struct Plug_InfoData;
		class BasePlugin;
		class Plug_ParameterList;
	}

	namespace Plugins
	{
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!---  RageStomp Guitar Amplifier Head :: Parameters
//!---  --- Prototypes
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
		class SCRFT_EXPORT DistortionFX_RageStomp_Params : public ::ScorchCrafter::Base::Plug_ParameterList
		{
		public:
			enum kSCsoftParams
			{
				kOverSampling_On		= 0,
				kOverSampling_Off		= 1,
				kMasterVol				= 2,
				kInputBoost				= 3,
				kGainControl			= 4,
				kTone					= 5,
				kStompOnOff				= 6,
				kMax_Parameter_Count	= 7
			};
			struct SCRFT_EXPORT paramTextLabelList
			{
				txtString_16 label[kMax_Parameter_Count];

				void Init()
				{
					strncpy( label[kOverSampling_On].txt,		"smp on  ", 15 );
					strncpy( label[kOverSampling_Off].txt,		"smp off ", 15 );
					strncpy( label[kMasterVol].txt,				"master v", 15 );
					strncpy( label[kInputBoost].txt,			"in boost", 15 );
					strncpy( label[kGainControl].txt,			"gain    ", 15 );
					strncpy( label[kTone].txt,					"tone    ", 15 );
					strncpy( label[kStompOnOff].txt,			"FX OnOff", 15 );
				}
			};
			enum kPresetControlList
			{
				kPreset_Init					= 0,
				kPreset_Light_Crunch,
				kPreset_Moderate_Drive,
				kPreset_Heavy_Chunker,

				kPreset_User_1,
				kPreset_User_2,
				kPreset_User_3,
				kPreset_User_4,
				kPreset_User_5,
				kPreset_User_6,
				kPreset_User_7,
				kPreset_User_8,
				kPreset_User_9,
				kPreset_User_10,
				kPreset_User_11,
				kPreset_User_12,
				kPreset_User_13,
				kPreset_User_14,
				kPreset_User_15,
				kPreset_User_16,
				kPreset_User_17,
				kPreset_User_18,
				kPreset_User_19,
				kPreset_User_20,
				kPreset_User_21,
				kPreset_User_22,
				kPreset_User_23,
				kPreset_User_24,
				kPreset_User_25,
				kPreset_User_26,
				kPreset_User_27,
				kPreset_User_28,
				kPreset_User_29,
				kPreset_User_30,

				kPreset_MAX_COUNT
			};
			struct SCRFT_EXPORT presetTextLabelList
			{
				txtString_128 label[kPreset_MAX_COUNT];

				void Init()
				{
					strncpy( label[kPreset_Init].txt,					"- Init / Default -", 127 );
					strncpy( label[kPreset_Light_Crunch].txt,			"Light Crunch Touch", 127 );
					strncpy( label[kPreset_Moderate_Drive].txt,			"Moderate Distortion", 127 );
					strncpy( label[kPreset_Heavy_Chunker].txt,			"Heavy Thick Chunker", 127 );

					strncpy( label[kPreset_User_1].txt,					"User / Custom 1", 127 );
					strncpy( label[kPreset_User_2].txt,					"User / Custom 2", 127 );
					strncpy( label[kPreset_User_3].txt,					"User / Custom 3", 127 );
					strncpy( label[kPreset_User_4].txt,					"User / Custom 4", 127 );
					strncpy( label[kPreset_User_5].txt,					"User / Custom 5", 127 );
					strncpy( label[kPreset_User_6].txt,					"User / Custom 6", 127 );
					strncpy( label[kPreset_User_7].txt,					"User / Custom 7", 127 );
					strncpy( label[kPreset_User_8].txt,					"User / Custom 8", 127 );
					strncpy( label[kPreset_User_9].txt,					"User / Custom 9", 127 );
					strncpy( label[kPreset_User_10].txt,				"User / Custom 10", 127 );
					strncpy( label[kPreset_User_11].txt,				"User / Custom 11", 127 );
					strncpy( label[kPreset_User_12].txt,				"User / Custom 12", 127 );
					strncpy( label[kPreset_User_13].txt,				"User / Custom 13", 127 );
					strncpy( label[kPreset_User_14].txt,				"User / Custom 14", 127 );
					strncpy( label[kPreset_User_15].txt,				"User / Custom 15", 127 );
					strncpy( label[kPreset_User_16].txt,				"User / Custom 16", 127 );
					strncpy( label[kPreset_User_17].txt,				"User / Custom 17", 127 );
					strncpy( label[kPreset_User_18].txt,				"User / Custom 18", 127 );
					strncpy( label[kPreset_User_19].txt,				"User / Custom 19", 127 );
					strncpy( label[kPreset_User_20].txt,				"User / Custom 20", 127 );
					strncpy( label[kPreset_User_21].txt,				"User / Custom 21", 127 );
					strncpy( label[kPreset_User_22].txt,				"User / Custom 22", 127 );
					strncpy( label[kPreset_User_23].txt,				"User / Custom 23", 127 );
					strncpy( label[kPreset_User_24].txt,				"User / Custom 24", 127 );
					strncpy( label[kPreset_User_25].txt,				"User / Custom 25", 127 );
					strncpy( label[kPreset_User_26].txt,				"User / Custom 26", 127 );
					strncpy( label[kPreset_User_27].txt,				"User / Custom 27", 127 );
					strncpy( label[kPreset_User_28].txt,				"User / Custom 28", 127 );
					strncpy( label[kPreset_User_29].txt,				"User / Custom 29", 127 );
					strncpy( label[kPreset_User_30].txt,				"User / Custom 30", 127 );
				}
			};
			struct SCRFT_EXPORT Control_Preset_Bank
			{
				f64 prm[kMax_Parameter_Count];
			};
			struct SCRFT_EXPORT Control_Preset_Data
			{
				paramTextLabelList ControlLabels;
				presetTextLabelList PresetLabels;
				Control_Preset_Bank Bank[kPreset_MAX_COUNT];

				void Init()
				{
					ControlLabels.Init();
					PresetLabels.Init();

					for(u32 x = 0u; x < (u32) kPreset_MAX_COUNT; x++)
					{
						for(u32 y = 0u; y < (u32) kMax_Parameter_Count; y++)
						{
							Bank[x].prm[kOverSampling_On] = 0.010;
							Bank[x].prm[kOverSampling_Off] = 0.100;
							Bank[x].prm[kMasterVol] = 0.50;
							Bank[x].prm[kInputBoost] = 0.50;
							Bank[x].prm[kGainControl] = 0.50;
							Bank[x].prm[kTone] = 0.50;
							Bank[x].prm[kStompOnOff] = 1.00;
						}
					}

					Bank[kPreset_Light_Crunch].prm[kGainControl] = 0.12;

					Bank[kPreset_Moderate_Drive].prm[kGainControl] = 0.50;

					Bank[kPreset_Heavy_Chunker].prm[kGainControl] = 1.00;
				}
				Control_Preset_Data& operator= (const Control_Preset_Data &other)
				{
					ControlLabels.Init();
					PresetLabels.Init();

					for(u32 x = 0u; x < (u32) kPreset_MAX_COUNT; x++)
					{
						strncpy( PresetLabels.label[kPreset_Init].txt, other.PresetLabels.label[kPreset_Init].txt, 127 );

						for(u32 y = 0u; y < (u32) kMax_Parameter_Count; y++)
						{
							Bank[x].prm[y] = other.Bank[x].prm[y];
						}
					}
				}
			};

			DistortionFX_RageStomp_Params();

			DistortionFX_RageStomp_Params(const ::ScorchCrafter::Base::Plug_ParameterList &other);

			virtual DistortionFX_RageStomp_Params& operator=(const ::ScorchCrafter::Base::Plug_ParameterList &other);

			virtual inline u32 GetNumberOfParameters();

			virtual inline u32 GetNumberOfPresets();

			virtual inline s32 GetID(const s32 index);

			virtual inline s32 GetVersionNumber();

			virtual inline void Reset();

			virtual inline void Reset(const u32 &preset_number);

			virtual inline void SetToPreset(const u32 &preset_number);

			virtual inline u32 GetCurrentPreset();

			virtual inline void SetPresetName(const char* name, size_t length);

			virtual inline void GetPresetName(char *name, size_t length);

			virtual inline void GetPresetName(char *name, size_t length, const u32 &index);

			virtual inline void SetParameter(const u32 &index, const f64 &value);

			virtual inline f64 GetParameter(const u32 &index);

			virtual inline void GetParameterName(const u32 &index, char *name, size_t length);

			virtual inline void SetID();

			virtual inline void SetVersionInfo();

			virtual inline bool CompareID(const ::ScorchCrafter::Base::Plug_ParameterList &other);

			s32 ID[16];
			s32 versionNumber;
			Control_Preset_Data PresetData;
			u32 currentPreset;
		};
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!---  RageStomp Guitar Amplifier Head :: Audio Effect
//!---  --- Prototypes
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
		class SCRFT_EXPORT DistortionFX_RageStomp : public ::ScorchCrafter::Base::BasePlugin
		{
		public:
			DistortionFX_RageStomp();

			DistortionFX_RageStomp(const ::ScorchCrafter::Base::BasePlugin &other);

			virtual ~DistortionFX_RageStomp();

			virtual inline void Init(const f32 smpRate);

			virtual inline void SetSampleRate(const f32 inp_rate);

			virtual inline void SetParameter(const f64 &inp, const u32 &index);

			virtual inline f64 GetParameter(const u32 &index);

			virtual inline Plug_InfoData GetPlugInfo();

			virtual inline void Run();

			virtual inline void RunSampleBlock();

			virtual inline void SetBlockSize(const u32 inp);

		protected:
			Plug_InfoData InfoData;

			//! ----------------------------------------------------------------
			//! -- FX :: OverSampling EQ Filter --
			//! ----------------------------------------------------------------
			struct SCRFT_EXPORT OverSampling_Eq_Filter
			{
				const f80 _pi_f80;

				f64 smp_rate, os_mult, os_rate;
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

				OverSampling_Eq_Filter() :
					_pi_f80( (f80) 3.14159265358979323846264338327950288419716939937510L )
				{}
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
					cutoff_hp = (f80) 12.0L * (f80) 2.0L / (f80) os_rate;
					cutoff_lp = (f80) 0.4999725L * (f80) smp_rate * (f80) 2.0L / (f80) os_rate;

//					res_hp = 1.3335214321633240256759317152953L;
					res_hp = (f80) 1.1885022274370184377301224648922L;

					k = (f80) 0.5L * res_hp * (f80) sinl( _pi_f80 * cutoff_hp );
					c1 = (f80) 0.5L * ((f80) 1.0L - k) / ((f80) 1.0L + k);
					c2 = ((f80) 0.5L + c1) * (f80) cosl( _pi_f80 * cutoff_hp );
					c3 = ((f80) 0.5L + c1 + c2 ) * (f80) 0.25L;

					a0_hp = f64 ((f80) 2.0L * c3);
					a1_hp = f64 ((f80) -4.0L * c3);
					a2_hp = f64 ((f80) 2.0L * c3);
					b1_hp = f64 ((f80) -2.0L * c2);
					b2_hp = f64 ((f80) 2.0L * c1);

					res_lp = (f80) 1.1885022274370184377301224648922L;

					k = (f80) 0.5L * res_lp * (f80) sinl( _pi_f80 * cutoff_lp );
					c1 = (f80) 0.5L * ((f80) 1.0L - k) / ((f80) 1.0L + k);
					c2 = ((f80) 0.5L + c1) * (f80) cosl( _pi_f80 * cutoff_lp );
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
			}; // struct OverSampling_Eq_Filter
			//! ----------------------------------------------------------------
			//! --- FX :: EQ Filter :: Standard LP (Simple Low Pass) --
			//! ----------------------------------------------------------------
			struct SCRFT_EXPORT EQ_LP
			{
				const f80 _pi_f80;
				const f64 dn;

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

					const f80 t = (f80) expl( (f80) -2.0L * _pi_f80 * p_frequency / sp_rate );
					fq0 = f64 (1.0L - t);
					fq1 = f64 (-t);

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
					return f64 ( buffer = (fq0 * inp) - (fq1 * buffer) + dn );
				}
				EQ_LP() :
					_pi_f80( (f80) 3.14159265358979323846264338327950288419716939937510L ),
					dn( (f64) powl( (f80) 10.L, (f80) -30.L ) ),
					p_frequency( (f80) 1.0L ),
					sp_rate( (f80) 44100.0L ),
					buffer( 0.0 )
				{
					SetFilterVars();
				}
			}; // struct EQ_LP
			//! ----------------------------------------------------------------
			//! --- FX :: EQ Filter :: Standard HP (Simple High Pass) --
			//! ----------------------------------------------------------------
			struct SCRFT_EXPORT EQ_HP
			{
				const f80 _pi_f80;
				const f64 dn;

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

					const f80 t = (f80) expl( (f80) -2.0L * _pi_f80 * p_frequency / sp_rate );
					fq0 = f64 (1.0L - t);
					fq1 = f64 (-t);

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
					const f64 spl_delay = (fq0 * inp) - (fq1 * old_inp) + dn;

					old_inp = (f64) inp;

					buffer = (fq0 * inp) - (fq1 * buffer) + dn;

					return (spl_delay - buffer);
				}
				EQ_HP() :
					_pi_f80( (f80) 3.14159265358979323846264338327950288419716939937510L ),
					dn( (f64) powl( (f80) 10.L, (f80) -30.L ) ),
					p_frequency( (f80) 1.0L ),
					sp_rate( (f80) 44100.0L ),
					buffer( 0.0 )
				{
					SetFilterVars();
				}
			}; // struct EQ_HP
			//! ----------------------------------------------------------------
			//! --- FX :: EQ Filter :: Standard DP (Simple Delay Sync Pass) --
			//! ----------------------------------------------------------------
			struct SCRFT_EXPORT EQ_DP
			{
				const f80 _pi_f80;
				const f64 dn;

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

					const f80 t = (f80) expl( (f80) -2.0L * _pi_f80 * p_frequency / sp_rate );
					fq0 = f64 (1.0L - t);
					fq1 = f64 (-t);

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
					const f64 spl_delay = (fq0 * inp) - (fq1 * buffer) + dn;
					buffer = (f64) inp;

					return spl_delay;
				}
				EQ_DP() :
					_pi_f80( (f80) 3.14159265358979323846264338327950288419716939937510L ),
					dn( (f64) powl( (f80) 10.L, (f80) -30.L ) ),
					p_frequency( (f80) 1.0L ),
					sp_rate( (f80) 44100.0L ),
					buffer( 0.0 )
				{
					SetFilterVars();
				}
			}; // struct EQ_DP
			//! ----------------------------------------------------------------
			//! --- FX :: EQ Filter :: Dual LP (Dual-Rate Low Pass) --
			//! ----------------------------------------------------------------
			struct SCRFT_EXPORT EQ_Dual_LP
			{
				const f80 _pi_f80;
				const f64 dn;

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

					if ( p_frequency_a > f80 (sp_rate * 0.5L) )
						p_frequency_a = f80 (sp_rate * 0.5L);
					if ( p_frequency_a < (f80) 0.0000012L )
						p_frequency_a = (f80) 0.0000012L;

					if ( p_frequency_b > f80 (sp_rate * 0.5L) )
						p_frequency_b = f80 (sp_rate * 0.5L);
					if ( p_frequency_b < (f80) 0.0000012L )
						p_frequency_b = (f80) 0.0000012L;

					f80 t = (f80) expl( (f80) -2.0L * _pi_f80 * p_frequency_a / sp_rate );
					fq0_a = f64 (1.0L - t);
					fq1_a = f64 (-t);

					t = (f80) expl( (f80) -2.0L * _pi_f80 * p_frequency_b / sp_rate );
					fq0_b = f64 (1.0L - t);
					fq1_b = f64 (-t);

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
						buffer = (fq0_a * inp) - (fq1_a * buffer) + dn;
					else
						buffer = (fq0_b * inp) - (fq1_b * buffer) + dn;

					return buffer;
				}
				EQ_Dual_LP() :
					_pi_f80( (f80) 3.14159265358979323846264338327950288419716939937510L ),
					dn( (f64) powl( (f80) 10.L, (f80) -30.L ) ),
					p_frequency_a( (f80) 1.0L ),
					p_frequency_b( (f80) 1.0L ),
					sp_rate( (f80) 44100.0L ),
					buffer( 0.0 )
				{
					SetFilterVars();
				}
			}; // struct EQ_Dual_LP
			//! ----------------------------------------------------------------
			//! --- FX :: Amplifier Stage :: Tube FX Modifier --
			//! ----------------------------------------------------------------
			struct SCRFT_EXPORT TubeFX_mod
			{
				f64 fx_spl_a, fx_spl_b;

				EQ_HP f0_HP, f1_HP, f2_HP, f3_HP;
				EQ_HP f4_HP, f5_HP, f6_HP, f7_HP;

				EQ_LP f0_LP, f1_LP, f2_LP, f3_LP;

				EQ_LP f4_LP, f5_LP, f6_LP, f7_LP;

				inline void Clear()
				{
					fx_spl_a = 0.0;
					fx_spl_b = 0.0;

					f0_HP.Clear();
					f1_HP.Clear();
					f2_HP.Clear();
					f3_HP.Clear();
					f4_HP.Clear();
					f5_HP.Clear();
					f6_HP.Clear();
					f7_HP.Clear();

					f0_LP.Clear();
					f1_LP.Clear();
					f2_LP.Clear();
					f3_LP.Clear();

					f4_LP.Clear();
					f5_LP.Clear();
					f6_LP.Clear();
					f7_LP.Clear();
				}
				void SetSampleRate(const f64 &nRate)
				{
					f0_HP.SetSampleRate( nRate );
					f1_HP.SetSampleRate( nRate );
					f2_HP.SetSampleRate( nRate );
					f3_HP.SetSampleRate( nRate );
					f4_HP.SetSampleRate( nRate );
					f5_HP.SetSampleRate( nRate );
					f6_HP.SetSampleRate( nRate );
					f7_HP.SetSampleRate( nRate );

					f0_LP.SetSampleRate( nRate );
					f1_LP.SetSampleRate( nRate );
					f2_LP.SetSampleRate( nRate );
					f3_LP.SetSampleRate( nRate );

					f4_LP.SetSampleRate( nRate );
					f5_LP.SetSampleRate( nRate );
					f6_LP.SetSampleRate( nRate );
					f7_LP.SetSampleRate( nRate );

					Clear();
				}
				inline void Run(const f64 &inp)
				{
					f64 spl_fx = (f64) inp;

					spl_fx = f0_HP.Run( spl_fx );
					spl_fx = f1_HP.Run( spl_fx );
					spl_fx = f2_HP.Run( spl_fx );
					spl_fx = f3_HP.Run( spl_fx );
					spl_fx = f4_HP.Run( spl_fx );
					spl_fx = f5_HP.Run( spl_fx );
					spl_fx = f6_HP.Run( spl_fx );
					spl_fx = f7_HP.Run( spl_fx );

					spl_fx = scft_ExpFx64( spl_fx * 12.0, 901110.0 );

					spl_fx = f0_LP.Run( spl_fx );
					spl_fx = f1_LP.Run( spl_fx );
					spl_fx = f2_LP.Run( spl_fx );
					spl_fx = f3_LP.Run( spl_fx );

					spl_fx = scft_PowFx64( spl_fx, 1200.0 );

					spl_fx = f4_LP.Run( spl_fx );
					spl_fx = f5_LP.Run( spl_fx );
					spl_fx = f6_LP.Run( spl_fx );
					spl_fx = f7_LP.Run( spl_fx );

					spl_fx *= 0.1200;

					fx_spl_a = 1.0 - spl_fx;
					fx_spl_b = 1.0 + spl_fx;
				}
				inline void GetFxSplValues(f64 &val_a, f64 &val_b)
				{
					val_a = fx_spl_a;
					val_b = fx_spl_b;
				}
				TubeFX_mod()
				{
					f0_HP.SetPassRate( 120.0 );
					f1_HP.SetPassRate( 120.0 );
					f2_HP.SetPassRate( 120.0 );
					f3_HP.SetPassRate( 120.0 );
					f4_HP.SetPassRate( 120.0 );
					f5_HP.SetPassRate( 120.0 );
					f6_HP.SetPassRate( 120.0 );
					f7_HP.SetPassRate( 120.0 );

					f0_LP.SetPassRate( 12.0 );
					f1_LP.SetPassRate( 12.0 );
					f2_LP.SetPassRate( 12.0 );
					f3_LP.SetPassRate( 12.0 );

					f4_LP.SetPassRate( 120.0 );
					f5_LP.SetPassRate( 120.0 );
					f6_LP.SetPassRate( 120.0 );
					f7_LP.SetPassRate( 120.0 );

					SetSampleRate( (f64) 44100.0 );
				};
				~TubeFX_mod()
				{};
			}; // struct TubeFX_mod
			//! ----------------------------------------------------------------
			//! --- FX :: Amplifier Stage :: Tube --
			//! ----------------------------------------------------------------
			struct SCRFT_EXPORT Tube
			{
				// Parameter List selection, for which set of fixed parameters will be used
				const u32 parm_ID;

				// Fixed Parameters
				const f64	p_input_read_volume,
							p_input_vol_adjust, p_output_vol_adjust,
							p_buffer_range, p_dry_range,
							p_gain0_pullback_multiplier, p_gain1_pullback_multiplier, p_gain2_pullback_multiplier,
							p_gain0_pullback_factor, p_gain1_pullback_factor, p_gain2_pullback_factor,
							p_gain_clipping_curve,
							p_feedback_volume,
							p_dynamic_shaper_min, p_dynamic_shaper_max,
							p_min_bass, p_max_bass;

				// Dynamic Parameters
				f64 prm_gain,
					prm_dynamics;

				// Buffers
				f64 spl_buffer;
				f64 spl_feedback;

				// EQ effect objects
				EQ_LP f0_read_LP;

				EQ_HP f0_drive_HP, f1_drive_HP, f2_drive_HP, f3_drive_HP;
				EQ_LP f0_drive_LP, f1_drive_LP, f2_drive_LP, f3_drive_LP;

				EQ_HP f0_buffer_HP, f1_buffer_HP, f2_buffer_HP, f3_buffer_HP;
				EQ_LP f0_buffer_LP, f1_buffer_LP, f2_buffer_LP, f3_buffer_LP;

				EQ_LP f0_buffer_out_LP, f1_buffer_out_LP, f2_buffer_out_LP, f3_buffer_out_LP;

				EQ_LP f0_gain_inp_LP, f1_gain_inp_LP, f2_gain_inp_LP, f3_gain_inp_LP;

				EQ_LP f0_gain0_LP, f1_gain0_LP, f2_gain0_LP, f3_gain0_LP, f4_gain0_LP, f5_gain0_LP, f6_gain0_LP, f7_gain0_LP, f8_gain0_LP;
				EQ_LP f0_gain1_LP, f1_gain1_LP, f2_gain1_LP, f3_gain1_LP, f4_gain1_LP, f5_gain1_LP, f6_gain1_LP, f7_gain1_LP, f8_gain1_LP;
				EQ_LP f0_gain2_LP, f1_gain2_LP, f2_gain2_LP, f3_gain2_LP, f4_gain2_LP, f5_gain2_LP, f6_gain2_LP, f7_gain2_LP, f8_gain2_LP;

				EQ_DP f0_gain0_DP, f1_gain0_DP, f2_gain0_DP, f3_gain0_DP, f4_gain0_DP, f5_gain0_DP, f6_gain0_DP, f7_gain0_DP, f8_gain0_DP;
				EQ_DP f0_gain1_DP, f1_gain1_DP, f2_gain1_DP, f3_gain1_DP, f4_gain1_DP, f5_gain1_DP, f6_gain1_DP, f7_gain1_DP, f8_gain1_DP;
				EQ_DP f0_gain2_DP, f1_gain2_DP, f2_gain2_DP, f3_gain2_DP, f4_gain2_DP, f5_gain2_DP, f6_gain2_DP, f7_gain2_DP, f8_gain2_DP;

				EQ_HP f0_feedback_HP, f1_feedback_HP, f2_feedback_HP, f3_feedback_HP;
				EQ_LP f0_feedback_LP, f1_feedback_LP, f2_feedback_LP, f3_feedback_LP;

				EQ_LP f0_x_bass_LP, f1_x_bass_LP;
				EQ_DP f0_x_bass_DP, f1_x_bass_DP;

				EQ_HP f0_output_HP, f1_output_HP;

				inline void Clear()
				{
					spl_buffer = 0.0;
					spl_feedback = 0.0;

					f0_read_LP.Clear();

					f0_drive_HP.Clear(); f1_drive_HP.Clear(); f2_drive_HP.Clear(); f3_drive_HP.Clear();
					f0_drive_LP.Clear(); f1_drive_LP.Clear(); f2_drive_LP.Clear(); f3_drive_LP.Clear();

					f0_buffer_HP.Clear(); f1_buffer_HP.Clear(); f2_buffer_HP.Clear(); f3_buffer_HP.Clear();
					f0_buffer_LP.Clear(); f1_buffer_LP.Clear(); f2_buffer_LP.Clear(); f3_buffer_LP.Clear();

					f0_buffer_out_LP.Clear(); f1_buffer_out_LP.Clear(); f2_buffer_out_LP.Clear(); f3_buffer_out_LP.Clear();

					f0_gain_inp_LP.Clear(); f1_gain_inp_LP.Clear(); f2_gain_inp_LP.Clear(); f3_gain_inp_LP.Clear();

					f0_gain0_LP.Clear(); f1_gain0_LP.Clear(); f2_gain0_LP.Clear(); f3_gain0_LP.Clear(); f4_gain0_LP.Clear(); f5_gain0_LP.Clear(); f6_gain0_LP.Clear(); f7_gain0_LP.Clear(); f8_gain0_LP.Clear();
					f0_gain1_LP.Clear(); f1_gain1_LP.Clear(); f2_gain1_LP.Clear(); f3_gain1_LP.Clear(); f4_gain1_LP.Clear(); f5_gain1_LP.Clear(); f6_gain1_LP.Clear(); f7_gain1_LP.Clear(); f8_gain1_LP.Clear();
					f0_gain2_LP.Clear(); f1_gain2_LP.Clear(); f2_gain2_LP.Clear(); f3_gain2_LP.Clear(); f4_gain2_LP.Clear(); f5_gain2_LP.Clear(); f6_gain2_LP.Clear(); f7_gain2_LP.Clear(); f8_gain2_LP.Clear();

					f0_gain0_DP.Clear(); f1_gain0_DP.Clear(); f2_gain0_DP.Clear(); f3_gain0_DP.Clear(); f4_gain0_DP.Clear(); f5_gain0_DP.Clear(); f6_gain0_DP.Clear(); f7_gain0_DP.Clear(); f8_gain0_DP.Clear();
					f0_gain1_DP.Clear(); f1_gain1_DP.Clear(); f2_gain1_DP.Clear(); f3_gain1_DP.Clear(); f4_gain1_DP.Clear(); f5_gain1_DP.Clear(); f6_gain1_DP.Clear(); f7_gain1_DP.Clear(); f8_gain1_DP.Clear();
					f0_gain2_DP.Clear(); f1_gain2_DP.Clear(); f2_gain2_DP.Clear(); f3_gain2_DP.Clear(); f4_gain2_DP.Clear(); f5_gain2_DP.Clear(); f6_gain2_DP.Clear(); f7_gain2_DP.Clear(); f8_gain2_DP.Clear();

					f0_feedback_HP.Clear(); f1_feedback_HP.Clear(); f2_feedback_HP.Clear(); f3_feedback_HP.Clear();
					f0_feedback_LP.Clear(); f1_feedback_LP.Clear(); f2_feedback_LP.Clear(); f3_feedback_LP.Clear();

					f0_x_bass_LP.Clear(); f1_x_bass_LP.Clear();
					f0_x_bass_DP.Clear(); f1_x_bass_DP.Clear();

					f0_output_HP.Clear(); f1_output_HP.Clear();
				}
				void SetSampleRate(const f64 &nRate)
				{
					spl_buffer = 0.0;
					spl_feedback = 0.0;

					f0_read_LP.SetSampleRate( nRate );

					f0_drive_HP.SetSampleRate( nRate ); f1_drive_HP.SetSampleRate( nRate ); f2_drive_HP.SetSampleRate( nRate ); f3_drive_HP.SetSampleRate( nRate );
					f0_drive_LP.SetSampleRate( nRate ); f1_drive_LP.SetSampleRate( nRate ); f2_drive_LP.SetSampleRate( nRate ); f3_drive_LP.SetSampleRate( nRate );

					f0_buffer_HP.SetSampleRate( nRate ); f1_buffer_HP.SetSampleRate( nRate ); f2_buffer_HP.SetSampleRate( nRate ); f3_buffer_HP.SetSampleRate( nRate );
					f0_buffer_LP.SetSampleRate( nRate ); f1_buffer_LP.SetSampleRate( nRate ); f2_buffer_LP.SetSampleRate( nRate ); f3_buffer_LP.SetSampleRate( nRate );

					f0_buffer_out_LP.SetSampleRate( nRate ); f1_buffer_out_LP.SetSampleRate( nRate ); f2_buffer_out_LP.SetSampleRate( nRate ); f3_buffer_out_LP.SetSampleRate( nRate );

					f0_gain_inp_LP.SetSampleRate( nRate ); f1_gain_inp_LP.SetSampleRate( nRate ); f2_gain_inp_LP.SetSampleRate( nRate ); f3_gain_inp_LP.SetSampleRate( nRate );

					f0_gain0_LP.SetSampleRate( nRate ); f1_gain0_LP.SetSampleRate( nRate ); f2_gain0_LP.SetSampleRate( nRate ); f3_gain0_LP.SetSampleRate( nRate );
							f4_gain0_LP.SetSampleRate( nRate ); f5_gain0_LP.SetSampleRate( nRate ); f6_gain0_LP.SetSampleRate( nRate ); f7_gain0_LP.SetSampleRate( nRate );
							f8_gain0_LP.SetSampleRate( nRate );
					f0_gain1_LP.SetSampleRate( nRate ); f1_gain1_LP.SetSampleRate( nRate ); f2_gain1_LP.SetSampleRate( nRate ); f3_gain1_LP.SetSampleRate( nRate );
							f4_gain1_LP.SetSampleRate( nRate ); f5_gain1_LP.SetSampleRate( nRate ); f6_gain1_LP.SetSampleRate( nRate ); f7_gain1_LP.SetSampleRate( nRate );
							f8_gain1_LP.SetSampleRate( nRate );
					f0_gain2_LP.SetSampleRate( nRate ); f1_gain2_LP.SetSampleRate( nRate ); f2_gain2_LP.SetSampleRate( nRate ); f3_gain2_LP.SetSampleRate( nRate );
							f4_gain2_LP.SetSampleRate( nRate ); f5_gain2_LP.SetSampleRate( nRate ); f6_gain2_LP.SetSampleRate( nRate ); f7_gain2_LP.SetSampleRate( nRate );
							f8_gain2_LP.SetSampleRate( nRate );

					f0_gain0_DP.SetSampleRate( nRate ); f1_gain0_DP.SetSampleRate( nRate ); f2_gain0_DP.SetSampleRate( nRate ); f3_gain0_DP.SetSampleRate( nRate );
							f4_gain0_DP.SetSampleRate( nRate ); f5_gain0_DP.SetSampleRate( nRate ); f6_gain0_DP.SetSampleRate( nRate ); f7_gain0_DP.SetSampleRate( nRate );
							f8_gain0_DP.SetSampleRate( nRate );
					f0_gain1_DP.SetSampleRate( nRate ); f1_gain1_DP.SetSampleRate( nRate ); f2_gain1_DP.SetSampleRate( nRate ); f3_gain1_DP.SetSampleRate( nRate );
							f4_gain1_DP.SetSampleRate( nRate ); f5_gain1_DP.SetSampleRate( nRate ); f6_gain1_DP.SetSampleRate( nRate ); f7_gain1_DP.SetSampleRate( nRate );
							f8_gain1_DP.SetSampleRate( nRate );
					f0_gain2_DP.SetSampleRate( nRate ); f1_gain2_DP.SetSampleRate( nRate ); f2_gain2_DP.SetSampleRate( nRate ); f3_gain2_DP.SetSampleRate( nRate );
							f4_gain2_DP.SetSampleRate( nRate ); f5_gain2_DP.SetSampleRate( nRate ); f6_gain2_DP.SetSampleRate( nRate ); f7_gain2_DP.SetSampleRate( nRate );
							f8_gain2_DP.SetSampleRate( nRate );

					f0_feedback_HP.SetSampleRate( nRate ); f1_feedback_HP.SetSampleRate( nRate ); f2_feedback_HP.SetSampleRate( nRate ); f3_feedback_HP.SetSampleRate( nRate );
					f0_feedback_LP.SetSampleRate( nRate ); f1_feedback_LP.SetSampleRate( nRate ); f2_feedback_LP.SetSampleRate( nRate ); f3_feedback_LP.SetSampleRate( nRate );

					f0_x_bass_LP.SetSampleRate( nRate ); f1_x_bass_LP.SetSampleRate( nRate );
					f0_x_bass_DP.SetSampleRate( nRate ); f1_x_bass_DP.SetSampleRate( nRate );

					f0_output_HP.SetSampleRate( nRate ); f1_output_HP.SetSampleRate( nRate );
				}
				Tube(const s32 type_to_init=0) :
					parm_ID( (s32) type_to_init ),
					p_input_read_volume			( (parm_ID==1) ? 1.5600 : 1.5600 ),
					p_input_vol_adjust			( (parm_ID==1) ? 0.7500 : 0.9030 ),
					p_output_vol_adjust			( (parm_ID==1) ? 0.9030 : 0.9012 ),
					p_buffer_range				( (parm_ID==1) ? 1.7400 : 1.9200 ),
					p_dry_range					( (parm_ID==1) ? 0.6240 : 0.7500 ),
/*					p_gain0_pullback_multiplier	( (parm_ID==1) ? 1.2000 : 1.9200 ),
					p_gain1_pullback_multiplier	( (parm_ID==1) ? 1.2000 : 1.7400 ),
					p_gain2_pullback_multiplier	( (parm_ID==1) ? 1.2000 : 1.4520 ),
					p_gain0_pullback_factor		( (parm_ID==1) ? 0.5610 : 0.7500 ),
					p_gain1_pullback_factor		( (parm_ID==1) ? 0.4125 : 0.5025 ),
					p_gain2_pullback_factor		( (parm_ID==1) ? 0.2523 : 0.3900 ),	*/
					p_gain0_pullback_multiplier	( (parm_ID==1) ? 1.2000 : 1.4520 ),
					p_gain1_pullback_multiplier	( (parm_ID==1) ? 1.2000 : 1.4520 ),
					p_gain2_pullback_multiplier	( (parm_ID==1) ? 1.2000 : 1.4520 ),
					p_gain0_pullback_factor		( (parm_ID==1) ? 0.0120 : 0.0750 ),
					p_gain1_pullback_factor		( (parm_ID==1) ? 0.0120 : 0.0750 ),
					p_gain2_pullback_factor		( (parm_ID==1) ? 0.0120 : 0.0750 ),
					p_gain_clipping_curve		( (parm_ID==1) ? 120.0  : 120.0  ),
					p_feedback_volume			( (parm_ID==1) ? 0.9012 : 0.9300 ),
					p_dynamic_shaper_min		( (parm_ID==1) ? 0.0390 : 0.0750 ),
					p_dynamic_shaper_max		( (parm_ID==1) ? 0.2910 : 0.3900 ),
					p_min_bass					( (parm_ID==1) ?  0.309 :  0.525 ),
					p_max_bass					( (parm_ID==1) ? -0.345 : -0.660 ),
					prm_gain( 0.0 ),
					prm_dynamics( 0.0 ),
					spl_buffer( 0.0 ),
					spl_feedback( 0.0 )
				{}
				void Init()
				{
					prm_gain = 0.0;
					prm_dynamics = scft_Avg64( p_dynamic_shaper_min, p_dynamic_shaper_max, 0.50 );
					spl_buffer = 0.0;
					spl_feedback = 0.0;

					const f64 freq_read_LP =		( (parm_ID==1) ? 12.0	: 12.0		);
					const f64 freq_drive_HP =		( (parm_ID==1) ? 500.0	: 500.0		);
					const f64 freq_drive_LP =		( (parm_ID==1) ? 5000.0 : 5000.0	);
					const f64 freq_buffer_HP =		( (parm_ID==1) ? 12.0	: 12.0		);
					const f64 freq_buffer_LP =		( (parm_ID==1) ? 1200.0	: 1200.0	);
					const f64 freq_buffer_out_LP =	( (parm_ID==1) ? 120.0	: 120.0		);
					const f64 freq_gain_inp_LP =	( (parm_ID==1) ? 9300.0	: 9300.0	);
					const f64 freq_gain_0 =			( (parm_ID==1) ? 30.0	: 60.0		);
					const f64 freq_gain_1 =			( (parm_ID==1) ? 30.0	: 60.0		);
					const f64 freq_gain_2 =			( (parm_ID==1) ? 30.0	: 60.0		);
					const f64 freq_feedback_HP =	( (parm_ID==1) ? 12.0	: 12.0		);
					const f64 freq_feedback_LP =	( (parm_ID==1) ? 1200.0	: 1200.0	);
					const f64 freq_x_bass =			( (parm_ID==1) ? 120.0	: 120.0		);
					const f64 freq_output_HP =		( (parm_ID==1) ? 12.0	: 12.0		);

					f0_read_LP.SetPassRate( freq_read_LP );

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

					f0_gain0_LP.SetPassRate( freq_gain_0 );
					f1_gain0_LP.SetPassRate( freq_gain_0 );
					f2_gain0_LP.SetPassRate( freq_gain_0 );
					f3_gain0_LP.SetPassRate( freq_gain_0 );
					f4_gain0_LP.SetPassRate( freq_gain_0 );
					f5_gain0_LP.SetPassRate( freq_gain_0 );
					f6_gain0_LP.SetPassRate( freq_gain_0 );
					f7_gain0_LP.SetPassRate( freq_gain_0 );
					f8_gain0_LP.SetPassRate( freq_gain_0 );

					f0_gain1_LP.SetPassRate( freq_gain_1 );
					f1_gain1_LP.SetPassRate( freq_gain_1 );
					f2_gain1_LP.SetPassRate( freq_gain_1 );
					f3_gain1_LP.SetPassRate( freq_gain_1 );
					f4_gain1_LP.SetPassRate( freq_gain_1 );
					f5_gain1_LP.SetPassRate( freq_gain_1 );
					f6_gain1_LP.SetPassRate( freq_gain_1 );
					f7_gain1_LP.SetPassRate( freq_gain_1 );
					f8_gain1_LP.SetPassRate( freq_gain_1 );

					f0_gain2_LP.SetPassRate( freq_gain_2 );
					f1_gain2_LP.SetPassRate( freq_gain_2 );
					f2_gain2_LP.SetPassRate( freq_gain_2 );
					f3_gain2_LP.SetPassRate( freq_gain_2 );
					f4_gain2_LP.SetPassRate( freq_gain_2 );
					f5_gain2_LP.SetPassRate( freq_gain_2 );
					f6_gain2_LP.SetPassRate( freq_gain_2 );
					f7_gain2_LP.SetPassRate( freq_gain_2 );
					f8_gain2_LP.SetPassRate( freq_gain_2 );

					f0_gain0_DP.SetPassRate( freq_gain_0 );
					f1_gain0_DP.SetPassRate( freq_gain_0 );
					f2_gain0_DP.SetPassRate( freq_gain_0 );
					f3_gain0_DP.SetPassRate( freq_gain_0 );
					f4_gain0_DP.SetPassRate( freq_gain_0 );
					f5_gain0_DP.SetPassRate( freq_gain_0 );
					f6_gain0_DP.SetPassRate( freq_gain_0 );
					f7_gain0_DP.SetPassRate( freq_gain_0 );
					f8_gain0_DP.SetPassRate( freq_gain_0 );

					f0_gain1_DP.SetPassRate( freq_gain_1 );
					f1_gain1_DP.SetPassRate( freq_gain_1 );
					f2_gain1_DP.SetPassRate( freq_gain_1 );
					f3_gain1_DP.SetPassRate( freq_gain_1 );
					f4_gain1_DP.SetPassRate( freq_gain_1 );
					f5_gain1_DP.SetPassRate( freq_gain_1 );
					f6_gain1_DP.SetPassRate( freq_gain_1 );
					f7_gain1_DP.SetPassRate( freq_gain_1 );
					f8_gain1_DP.SetPassRate( freq_gain_1 );

					f0_gain2_DP.SetPassRate( freq_gain_2 );
					f1_gain2_DP.SetPassRate( freq_gain_2 );
					f2_gain2_DP.SetPassRate( freq_gain_2 );
					f3_gain2_DP.SetPassRate( freq_gain_2 );
					f4_gain2_DP.SetPassRate( freq_gain_2 );
					f5_gain2_DP.SetPassRate( freq_gain_2 );
					f6_gain2_DP.SetPassRate( freq_gain_2 );
					f7_gain2_DP.SetPassRate( freq_gain_2 );
					f8_gain2_DP.SetPassRate( freq_gain_2 );

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
					f0_x_bass_DP.SetPassRate( freq_x_bass );
					f1_x_bass_DP.SetPassRate( freq_x_bass );

					f0_output_HP.SetPassRate( freq_output_HP );
					f1_output_HP.SetPassRate( freq_output_HP );

					Clear();
				}
				inline void SetGain(const f64 &inp)
				{
					prm_gain = (f64) inp;

					prm_dynamics = scft_Avg64( p_dynamic_shaper_min, p_dynamic_shaper_max, inp );
				}
				inline f64 Run(const f64 SCRFT_RESTRICT_REF inp, const f64 SCRFT_RESTRICT_REF inp_modifier)
				{
					f64 spl_read = scft_Abs64( inp * p_input_read_volume );
					spl_read = scft_Clamp64( spl_read, (f64) 0.0, (f64) 1.0 );
					spl_read = f0_read_LP.Run( spl_read );

					const f64 spl_amp_skew_a = scft_Avg64( 1.20, 0.93, spl_read );
					const f64 spl_amp_skew_b = scft_Avg64( 1.00, spl_read * 1.65, prm_dynamics );

					f64 spl_fx = inp * p_input_vol_adjust;

					f64 spl_drive = spl_fx;
					spl_drive = f0_drive_HP.Run( spl_drive );
					spl_drive = f1_drive_HP.Run( spl_drive );
					spl_drive = f2_drive_HP.Run( spl_drive );
					spl_drive = f3_drive_HP.Run( spl_drive );
					spl_drive = f0_drive_LP.Run( spl_drive );
					spl_drive = f1_drive_LP.Run( spl_drive );
					spl_drive = f2_drive_LP.Run( spl_drive );
					spl_drive = f3_drive_LP.Run( spl_drive );

					spl_buffer += spl_drive;
					spl_buffer = f0_buffer_HP.Run( spl_buffer );
					spl_buffer = f1_buffer_HP.Run( spl_buffer );
					spl_buffer = f2_buffer_HP.Run( spl_buffer );
					spl_buffer = f3_buffer_HP.Run( spl_buffer );
					spl_buffer = f0_buffer_LP.Run( spl_buffer );
					spl_buffer = f1_buffer_LP.Run( spl_buffer );
					spl_buffer = f2_buffer_LP.Run( spl_buffer );
					spl_buffer = f3_buffer_LP.Run( spl_buffer );

					f64 buffer_out = spl_buffer * prm_gain * p_buffer_range;
					f0_buffer_out_LP.Run( buffer_out );
					f1_buffer_out_LP.Run( buffer_out );
					f2_buffer_out_LP.Run( buffer_out );
					f3_buffer_out_LP.Run( buffer_out );

					f64 spl_gain = (spl_fx * prm_gain * p_dry_range) + buffer_out;
					spl_gain = f0_gain_inp_LP.Run( spl_gain );
					spl_gain = f1_gain_inp_LP.Run( spl_gain );
					spl_gain = f2_gain_inp_LP.Run( spl_gain );
					spl_gain = f3_gain_inp_LP.Run( spl_gain );

					spl_gain *= spl_amp_skew_a;

					f64 spl_gain0_pullBase = spl_gain;
					spl_gain = f0_gain0_DP.Run( spl_gain );
					spl_gain = f1_gain0_DP.Run( spl_gain );
					spl_gain = f2_gain0_DP.Run( spl_gain );
					spl_gain = f3_gain0_DP.Run( spl_gain );
					spl_gain = f4_gain0_DP.Run( spl_gain );
					spl_gain = f5_gain0_DP.Run( spl_gain );
					spl_gain = f6_gain0_DP.Run( spl_gain );
					spl_gain = f7_gain0_DP.Run( spl_gain );
					spl_gain = f8_gain0_DP.Run( spl_gain );
					spl_gain0_pullBase = f0_gain0_LP.Run( spl_gain0_pullBase );
					spl_gain0_pullBase = f1_gain0_LP.Run( spl_gain0_pullBase );
					spl_gain0_pullBase = f2_gain0_LP.Run( spl_gain0_pullBase );
					spl_gain0_pullBase = scft_Abs64( spl_gain0_pullBase );
					spl_gain0_pullBase = f3_gain0_LP.Run( spl_gain0_pullBase );
					spl_gain0_pullBase = f4_gain0_LP.Run( spl_gain0_pullBase );
					spl_gain0_pullBase = f5_gain0_LP.Run( spl_gain0_pullBase );
					f64 spl_gain0_pullBack = p_gain0_pullback_multiplier * inp_modifier * scft_Max64( 1.0 - spl_gain0_pullBase, p_gain0_pullback_factor );
					spl_gain0_pullBack = f6_gain0_LP.Run( spl_gain0_pullBack );
					spl_gain0_pullBack = f7_gain0_LP.Run( spl_gain0_pullBack );
					spl_gain0_pullBack = f8_gain0_LP.Run( spl_gain0_pullBack );
					spl_gain *= spl_gain0_pullBack;

					f64 spl_gain1_pullBase = spl_gain;
					spl_gain = f0_gain1_DP.Run( spl_gain );
					spl_gain = f1_gain1_DP.Run( spl_gain );
					spl_gain = f2_gain1_DP.Run( spl_gain );
					spl_gain = f3_gain1_DP.Run( spl_gain );
					spl_gain = f4_gain1_DP.Run( spl_gain );
					spl_gain = f5_gain1_DP.Run( spl_gain );
					spl_gain = f6_gain1_DP.Run( spl_gain );
					spl_gain = f7_gain1_DP.Run( spl_gain );
					spl_gain = f8_gain1_DP.Run( spl_gain );
					spl_gain1_pullBase = f0_gain1_LP.Run( spl_gain1_pullBase );
					spl_gain1_pullBase = f1_gain1_LP.Run( spl_gain1_pullBase );
					spl_gain1_pullBase = f2_gain1_LP.Run( spl_gain1_pullBase );
					spl_gain1_pullBase = scft_Abs64( spl_gain1_pullBase );
					spl_gain1_pullBase = f3_gain1_LP.Run( spl_gain1_pullBase );
					spl_gain1_pullBase = f4_gain1_LP.Run( spl_gain1_pullBase );
					spl_gain1_pullBase = f5_gain1_LP.Run( spl_gain1_pullBase );
					f64 spl_gain1_pullBack = p_gain1_pullback_multiplier * inp_modifier * scft_Max64( 1.0 - spl_gain1_pullBase, p_gain1_pullback_factor );
					spl_gain1_pullBack = f6_gain1_LP.Run( spl_gain1_pullBack );
					spl_gain1_pullBack = f7_gain1_LP.Run( spl_gain1_pullBack );
					spl_gain1_pullBack = f8_gain1_LP.Run( spl_gain1_pullBack );
					spl_gain *= spl_gain1_pullBack;

					f64 spl_gain2_pullBase = spl_gain;
					spl_gain = f0_gain2_DP.Run( spl_gain );
					spl_gain = f1_gain2_DP.Run( spl_gain );
					spl_gain = f2_gain2_DP.Run( spl_gain );
					spl_gain = f3_gain2_DP.Run( spl_gain );
					spl_gain = f4_gain2_DP.Run( spl_gain );
					spl_gain = f5_gain2_DP.Run( spl_gain );
					spl_gain = f6_gain2_DP.Run( spl_gain );
					spl_gain = f7_gain2_DP.Run( spl_gain );
					spl_gain = f8_gain2_DP.Run( spl_gain );
					spl_gain2_pullBase = f0_gain2_LP.Run( spl_gain2_pullBase );
					spl_gain2_pullBase = f1_gain2_LP.Run( spl_gain2_pullBase );
					spl_gain2_pullBase = f2_gain2_LP.Run( spl_gain2_pullBase );
					spl_gain2_pullBase = scft_Abs64( spl_gain2_pullBase );
					spl_gain2_pullBase = f3_gain2_LP.Run( spl_gain2_pullBase );
					spl_gain2_pullBase = f4_gain2_LP.Run( spl_gain2_pullBase );
					spl_gain2_pullBase = f5_gain2_LP.Run( spl_gain2_pullBase );
					f64 spl_gain2_pullBack = p_gain2_pullback_multiplier * inp_modifier * scft_Max64( 1.0 - spl_gain2_pullBase, p_gain2_pullback_factor );
					spl_gain2_pullBack = f6_gain2_LP.Run( spl_gain2_pullBack );
					spl_gain2_pullBack = f7_gain2_LP.Run( spl_gain2_pullBack );
					spl_gain2_pullBack = f8_gain2_LP.Run( spl_gain2_pullBack );
					spl_gain *= spl_gain2_pullBack;

/*
					spl_gain *= inp_modifier * spl_amp_skew_a;

					f64 spl_gain0_pullBack = spl_gain;
					spl_gain = f0_gain0_DP.Run( spl_gain );
					spl_gain = f1_gain0_DP.Run( spl_gain );
					spl_gain = f2_gain0_DP.Run( spl_gain );
					spl_gain = f3_gain0_DP.Run( spl_gain );
					spl_gain = f4_gain0_DP.Run( spl_gain );
					spl_gain = f5_gain0_DP.Run( spl_gain );
					spl_gain = f6_gain0_DP.Run( spl_gain );
					spl_gain = f7_gain0_DP.Run( spl_gain );
					spl_gain = f8_gain0_DP.Run( spl_gain );
					spl_gain0_pullBack = f0_gain0_LP.Run( spl_gain0_pullBack );
					spl_gain0_pullBack = f1_gain0_LP.Run( spl_gain0_pullBack );
					spl_gain0_pullBack = f2_gain0_LP.Run( spl_gain0_pullBack );
					spl_gain0_pullBack = scft_Abs64( spl_gain0_pullBack );
					spl_gain0_pullBack = f3_gain0_LP.Run( spl_gain0_pullBack );
					spl_gain0_pullBack = f4_gain0_LP.Run( spl_gain0_pullBack );
					spl_gain0_pullBack = f5_gain0_LP.Run( spl_gain0_pullBack );
					spl_gain0_pullBack = p_gain0_pullback_multiplier / (1.0 + (spl_gain0_pullBack * p_gain0_pullback_factor));
					spl_gain0_pullBack = f6_gain0_LP.Run( spl_gain0_pullBack );
					spl_gain0_pullBack = f7_gain0_LP.Run( spl_gain0_pullBack );
					spl_gain0_pullBack = f8_gain0_LP.Run( spl_gain0_pullBack );
					spl_gain *= spl_gain0_pullBack;

					f64 spl_gain1_pullBack = spl_gain;
					spl_gain = f0_gain1_DP.Run( spl_gain );
					spl_gain = f1_gain1_DP.Run( spl_gain );
					spl_gain = f2_gain1_DP.Run( spl_gain );
					spl_gain = f3_gain1_DP.Run( spl_gain );
					spl_gain = f4_gain1_DP.Run( spl_gain );
					spl_gain = f5_gain1_DP.Run( spl_gain );
					spl_gain = f6_gain1_DP.Run( spl_gain );
					spl_gain = f7_gain1_DP.Run( spl_gain );
					spl_gain = f8_gain1_DP.Run( spl_gain );
					spl_gain1_pullBack = f0_gain1_LP.Run( spl_gain1_pullBack );
					spl_gain1_pullBack = f1_gain1_LP.Run( spl_gain1_pullBack );
					spl_gain1_pullBack = f2_gain1_LP.Run( spl_gain1_pullBack );
					spl_gain1_pullBack = scft_Abs64( spl_gain1_pullBack );
					spl_gain1_pullBack = f3_gain1_LP.Run( spl_gain1_pullBack );
					spl_gain1_pullBack = f4_gain1_LP.Run( spl_gain1_pullBack );
					spl_gain1_pullBack = f5_gain1_LP.Run( spl_gain1_pullBack );
					spl_gain1_pullBack = p_gain1_pullback_multiplier / (1.0 + (spl_gain1_pullBack * p_gain1_pullback_factor));
					spl_gain1_pullBack = f6_gain1_LP.Run( spl_gain1_pullBack );
					spl_gain1_pullBack = f7_gain1_LP.Run( spl_gain1_pullBack );
					spl_gain1_pullBack = f8_gain1_LP.Run( spl_gain1_pullBack );
					spl_gain *= spl_gain1_pullBack;

					f64 spl_gain2_pullBack = spl_gain;
					spl_gain = f0_gain2_DP.Run( spl_gain );
					spl_gain = f1_gain2_DP.Run( spl_gain );
					spl_gain = f2_gain2_DP.Run( spl_gain );
					spl_gain = f3_gain2_DP.Run( spl_gain );
					spl_gain = f4_gain2_DP.Run( spl_gain );
					spl_gain = f5_gain2_DP.Run( spl_gain );
					spl_gain = f6_gain2_DP.Run( spl_gain );
					spl_gain = f7_gain2_DP.Run( spl_gain );
					spl_gain = f8_gain2_DP.Run( spl_gain );
					spl_gain2_pullBack = f0_gain2_LP.Run( spl_gain2_pullBack );
					spl_gain2_pullBack = f1_gain2_LP.Run( spl_gain2_pullBack );
					spl_gain2_pullBack = f2_gain2_LP.Run( spl_gain2_pullBack );
					spl_gain2_pullBack = scft_Abs64( spl_gain2_pullBack );
					spl_gain2_pullBack = f3_gain2_LP.Run( spl_gain2_pullBack );
					spl_gain2_pullBack = f4_gain2_LP.Run( spl_gain2_pullBack );
					spl_gain2_pullBack = f5_gain2_LP.Run( spl_gain2_pullBack );
					spl_gain2_pullBack = p_gain2_pullback_multiplier / (1.0 + (spl_gain2_pullBack * p_gain2_pullback_factor));
					spl_gain2_pullBack = f6_gain2_LP.Run( spl_gain2_pullBack );
					spl_gain2_pullBack = f7_gain2_LP.Run( spl_gain2_pullBack );
					spl_gain2_pullBack = f8_gain2_LP.Run( spl_gain2_pullBack );
					spl_gain *= spl_gain2_pullBack;
*/
					spl_gain = scft_ExpFx64( spl_gain, p_gain_clipping_curve );

					spl_gain += spl_feedback * p_feedback_volume;

					spl_feedback = spl_fx;
					spl_feedback = f0_feedback_HP.Run( spl_feedback );
					spl_feedback = f1_feedback_HP.Run( spl_feedback );
					spl_feedback = f2_feedback_HP.Run( spl_feedback );
					spl_feedback = f3_feedback_HP.Run( spl_feedback );
					spl_feedback = f0_feedback_LP.Run( spl_feedback );
					spl_feedback = f1_feedback_LP.Run( spl_feedback );
					spl_feedback = f2_feedback_LP.Run( spl_feedback );
					spl_feedback = f3_feedback_LP.Run( spl_feedback );

					spl_fx = spl_gain * p_output_vol_adjust * spl_amp_skew_b;

					f64 spl_x_bass = spl_fx;
					spl_x_bass = f0_x_bass_LP.Run( spl_x_bass );
					spl_x_bass = f1_x_bass_LP.Run( spl_x_bass );
					spl_fx = f0_x_bass_DP.Run( spl_fx );
					spl_fx = f1_x_bass_DP.Run( spl_fx );
					spl_fx += spl_x_bass * scft_Avg64( p_min_bass, p_max_bass, spl_read );

					spl_fx = f0_output_HP.Run( spl_fx );
					spl_fx = f1_output_HP.Run( spl_fx );

					return spl_fx;
				}
			}; // struct Tube
			//! ----------------------------------------------------------------
			//! --- FX :: Amplifier Channel --
			//! ----------------------------------------------------------------
			struct SCRFT_EXPORT FxDrive_Channel
			{
				Tube tube1, tube2, tube3, tube4;
				u32 numTubeStages;

				TubeFX_mod tubeFX;

				f64 drive_min;
				f64 drive_max;
				f64 master_in;
				f64 master_out;

				FxDrive_Channel() :
					tube1( 0 ),
					tube2( 0 ),
					tube3( 1 ),
					tube4( 1 ),
					numTubeStages( 4u ),
					drive_min( 0.0 ),
					drive_max( 1.0 ),
					master_in( 1.0 ),
					master_out( 1.0 )
				{
					tube1.Init();
					tube2.Init();
					tube3.Init();
					tube4.Init();
				}
				FxDrive_Channel(const u32 inp_numTubeStages,
							const f64 inp_drive_min,
							const f64 inp_drive_max,
							const f64 inp_master_in,
							const f64 inp_master_out	) :
					numTubeStages( inp_numTubeStages ),
					drive_min( inp_drive_min ),
					drive_max( inp_drive_max ),
					master_in( inp_master_in ),
					master_out( inp_master_out )
				{
					tube1.Init();
					tube2.Init();
					tube3.Init();
					tube4.Init();
				}
				FxDrive_Channel& operator=(const FxDrive_Channel& other)
				{
					numTubeStages = other.numTubeStages;
					drive_min = other.drive_min;
					drive_max = other.drive_max;
					master_in = other.master_in;
					master_out = other.master_out;

					tube1.Init();
					tube2.Init();
					tube3.Init();
					tube4.Init();

					return *this;
				}
				inline void Clear()
				{
					tube1.Clear();
					tube2.Clear();
					tube3.Clear();
					tube4.Clear();

					tubeFX.Clear();
				}
				void SetSampleRate(const f64 &inp)
				{
					tube1.SetSampleRate( inp );
					tube2.SetSampleRate( inp );
					tube3.SetSampleRate( inp );
					tube4.SetSampleRate( inp );

					tubeFX.SetSampleRate( inp );
				}
				inline void SetGain(const f64 &inp)
				{
					const f64 gn = scft_Avg64( drive_min, drive_max, inp );
					tube1.SetGain( gn );
					tube2.SetGain( gn );
					tube3.SetGain( gn );
					tube4.SetGain( gn );
				}
				inline void RunFxRead(const f64 &inp)
				{
					tubeFX.Run( inp );
				}
				inline f64 Run(const f64 &inp)
				{
					if ( numTubeStages == 0u )
						return (f64) inp;

					f64 fx_spl = f64 (inp * master_in);

					const f64 spl_mod_a = tubeFX.fx_spl_a;
					const f64 spl_mod_b = tubeFX.fx_spl_b;

					fx_spl = tube1.Run( fx_spl, spl_mod_a );
					fx_spl = tube2.Run( fx_spl, spl_mod_b );

					if ( numTubeStages > 2u )
					{
						fx_spl = tube3.Run( fx_spl, spl_mod_a );
						fx_spl = tube4.Run( fx_spl, spl_mod_b );
					}

					return fx_spl * master_out;
				}
			}; // struct FxDrive_Channel
			//! ----------------------------------------------------------------
			//! --- FX :: Tone Input --
			//! ----------------------------------------------------------------
			struct SCRFT_EXPORT Tone_Input
			{
				f64 tone_control_adj;
				f64 vol_adj;

				EQ_HP f0_base_HP, f1_base_HP, f2_base_HP, f3_base_HP,
						f4_base_HP, f5_base_HP, f6_base_HP, f7_base_HP;

				EQ_LP f0_base_LP, f1_base_LP, f2_base_LP, f3_base_LP;

				EQ_HP f0_bright_a_HP, f1_bright_a_HP, f2_bright_a_HP, f3_bright_a_HP;
				EQ_HP f0_bright_b_HP, f1_bright_b_HP, f2_bright_b_HP, f3_bright_b_HP;

				inline void Clear()
				{
					f0_base_HP.Clear(); f1_base_HP.Clear(); f2_base_HP.Clear(); f3_base_HP.Clear();
					f4_base_HP.Clear(); f5_base_HP.Clear(); f6_base_HP.Clear(); f7_base_HP.Clear();

					f0_base_LP.Clear(); f1_base_LP.Clear(); f2_base_LP.Clear(); f3_base_LP.Clear();

					f0_bright_a_HP.Clear(); f1_bright_a_HP.Clear(); f2_bright_a_HP.Clear(); f3_bright_a_HP.Clear();
					f0_bright_b_HP.Clear(); f1_bright_b_HP.Clear(); f2_bright_b_HP.Clear(); f3_bright_b_HP.Clear();
				}
				void SetSampleRate(const f64 &inp_rate)
				{
					f64 sp_rate = (f64) inp_rate;

					if ( sp_rate < 44100.0 )
						sp_rate = 44100.0;

					f0_base_HP.SetSampleRate( sp_rate ); f1_base_HP.SetSampleRate( sp_rate ); f2_base_HP.SetSampleRate( sp_rate ); f3_base_HP.SetSampleRate( sp_rate );
					f4_base_HP.SetSampleRate( sp_rate ); f5_base_HP.SetSampleRate( sp_rate ); f6_base_HP.SetSampleRate( sp_rate ); f7_base_HP.SetSampleRate( sp_rate );

					f0_base_LP.SetSampleRate( sp_rate ); f1_base_LP.SetSampleRate( sp_rate ); f2_base_LP.SetSampleRate( sp_rate ); f3_base_LP.SetSampleRate( sp_rate );

					f0_bright_a_HP.SetSampleRate( sp_rate ); f1_bright_a_HP.SetSampleRate( sp_rate ); f2_bright_a_HP.SetSampleRate( sp_rate ); f3_bright_a_HP.SetSampleRate( sp_rate );
					f0_bright_b_HP.SetSampleRate( sp_rate ); f1_bright_b_HP.SetSampleRate( sp_rate ); f2_bright_b_HP.SetSampleRate( sp_rate ); f3_bright_b_HP.SetSampleRate( sp_rate );

					Clear();
				}
				inline f64 Run(const f64 &inp)
				{
					f64 spl_fx = (f64) inp * vol_adj;

					spl_fx = f0_base_HP.Run( spl_fx );
					spl_fx = f1_base_HP.Run( spl_fx );
					spl_fx = f2_base_HP.Run( spl_fx );
					spl_fx = f3_base_HP.Run( spl_fx );
					spl_fx = f4_base_HP.Run( spl_fx );
					spl_fx = f5_base_HP.Run( spl_fx );
					spl_fx = f6_base_HP.Run( spl_fx );
					spl_fx = f7_base_HP.Run( spl_fx );

					spl_fx = f0_base_LP.Run( spl_fx );
					spl_fx = f1_base_LP.Run( spl_fx );
					spl_fx = f2_base_LP.Run( spl_fx );
					spl_fx = f3_base_LP.Run( spl_fx );

					f64 spl_fx_0a = f0_bright_a_HP.Run( spl_fx );
					f64 spl_fx_0b = f0_bright_b_HP.Run( spl_fx );
					spl_fx = scft_Avg64( spl_fx_0a, spl_fx_0b, tone_control_adj );

					f64 spl_fx_1a = f1_bright_a_HP.Run( spl_fx );
					f64 spl_fx_1b = f1_bright_b_HP.Run( spl_fx );
					spl_fx = scft_Avg64( spl_fx_1a, spl_fx_1b, tone_control_adj );

					f64 spl_fx_2a = f2_bright_a_HP.Run( spl_fx );
					f64 spl_fx_2b = f2_bright_b_HP.Run( spl_fx );
					spl_fx = scft_Avg64( spl_fx_2a, spl_fx_2b, tone_control_adj );

					f64 spl_fx_3a = f3_bright_a_HP.Run( spl_fx );
					f64 spl_fx_3b = f3_bright_b_HP.Run( spl_fx );
					spl_fx = scft_Avg64( spl_fx_3a, spl_fx_3b, tone_control_adj );

					return spl_fx;
				}
				inline void SetTone(const f64 &inp)
				{
					tone_control_adj = inp;
					vol_adj = scft_Avg64( 1.20, 5.25, inp );
				}
				Tone_Input() :
					tone_control_adj( 0.50 ),
					vol_adj( 1.00 )
				{
					f0_base_HP.SetPassRate( 52.5 );
					f1_base_HP.SetPassRate( 52.5 );
					f2_base_HP.SetPassRate( 52.5 );
					f3_base_HP.SetPassRate( 52.5 );
					f4_base_HP.SetPassRate( 52.5 );
					f5_base_HP.SetPassRate( 52.5 );
					f6_base_HP.SetPassRate( 52.5 );
					f7_base_HP.SetPassRate( 52.5 );

					f0_base_LP.SetPassRate( 7500.0 );
					f1_base_LP.SetPassRate( 7500.0 );
					f2_base_LP.SetPassRate( 7500.0 );
					f3_base_LP.SetPassRate( 7500.0 );

					f0_bright_a_HP.SetPassRate( 309.0 );
					f1_bright_a_HP.SetPassRate( 309.0 );
					f2_bright_a_HP.SetPassRate( 309.0 );
					f3_bright_a_HP.SetPassRate( 309.0 );

					f0_bright_b_HP.SetPassRate( 903.0 );
					f1_bright_b_HP.SetPassRate( 903.0 );
					f2_bright_b_HP.SetPassRate( 903.0 );
					f3_bright_b_HP.SetPassRate( 903.0 );

					SetTone( 0.50 );

					Clear();
				}
			}; // struct Tone_Input
			//! ----------------------------------------------------------------
			//! --- FX :: Tone output --
			//! ----------------------------------------------------------------
			struct SCRFT_EXPORT Tone_Output
			{
/*				EQ_HP f0_tone_HP, f1_tone_HP, f2_tone_HP, f3_tone_HP,
						f4_tone_HP, f5_tone_HP, f6_tone_HP, f7_tone_HP;

				EQ_LP f0_tone_a_LP, f1_tone_a_LP, f2_tone_a_LP, f3_tone_a_LP;

				EQ_LP f0_tone_b_LP, f1_tone_b_LP, f2_tone_b_LP, f3_tone_b_LP;
*/
				EQ_LP f0_tone_LP, f1_tone_LP, f2_tone_LP, f3_tone_LP;

				inline void Clear()
				{
/*					f0_tone_HP.Clear(); f1_tone_HP.Clear(); f2_tone_HP.Clear(); f3_tone_HP.Clear();
					f4_tone_HP.Clear(); f5_tone_HP.Clear(); f6_tone_HP.Clear(); f7_tone_HP.Clear();

					f0_tone_a_LP.Clear(); f1_tone_a_LP.Clear(); f2_tone_a_LP.Clear(); f3_tone_a_LP.Clear();

					f0_tone_b_LP.Clear(); f1_tone_b_LP.Clear(); f2_tone_b_LP.Clear(); f3_tone_b_LP.Clear();
*/
					f0_tone_LP.Clear(); f1_tone_LP.Clear(); f2_tone_LP.Clear(); f3_tone_LP.Clear();
				}
				void SetSampleRate(const f64 &inp_rate)
				{
					f64 sp_rate = inp_rate;

					if ( sp_rate < 44100.0 )
						sp_rate = 44100.0;

/*					f0_tone_HP.SetSampleRate( sp_rate ); f1_tone_HP.SetSampleRate( sp_rate ); f2_tone_HP.SetSampleRate( sp_rate ); f3_tone_HP.SetSampleRate( sp_rate );
					f4_tone_HP.SetSampleRate( sp_rate ); f5_tone_HP.SetSampleRate( sp_rate ); f6_tone_HP.SetSampleRate( sp_rate ); f7_tone_HP.SetSampleRate( sp_rate );

					f0_tone_a_LP.SetSampleRate( sp_rate ); f1_tone_a_LP.SetSampleRate( sp_rate ); f2_tone_a_LP.SetSampleRate( sp_rate ); f3_tone_a_LP.SetSampleRate( sp_rate );

					f0_tone_b_LP.SetSampleRate( sp_rate ); f1_tone_b_LP.SetSampleRate( sp_rate ); f2_tone_b_LP.SetSampleRate( sp_rate ); f3_tone_b_LP.SetSampleRate( sp_rate );
*/
					f0_tone_LP.SetSampleRate( sp_rate ); f1_tone_LP.SetSampleRate( sp_rate ); f2_tone_LP.SetSampleRate( sp_rate ); f3_tone_LP.SetSampleRate( sp_rate );

					Clear();
				}
				inline f64 Run(const f64 &inp)
				{
					f64 spl_fx = (f64) inp;
/*
					spl_fx = f0_tone_HP.Run( spl_fx );
					spl_fx = f1_tone_HP.Run( spl_fx );
					spl_fx = f2_tone_HP.Run( spl_fx );
					spl_fx = f3_tone_HP.Run( spl_fx );
					spl_fx = f4_tone_HP.Run( spl_fx );
					spl_fx = f5_tone_HP.Run( spl_fx );
					spl_fx = f6_tone_HP.Run( spl_fx );
					spl_fx = f7_tone_HP.Run( spl_fx );

					f64 spl_fx_a = spl_fx;
					f64 spl_fx_b = spl_fx;
					spl_fx_a = f0_tone_a_LP.Run( spl_fx_a );
					spl_fx_b = f0_tone_b_LP.Run( spl_fx_b );
					spl_fx = scft_Avg64( spl_fx_a, spl_fx_b, tone_control_adj );

					spl_fx_a = spl_fx;
					spl_fx_b = spl_fx;
					spl_fx_a = f1_tone_a_LP.Run( spl_fx_a );
					spl_fx_b = f1_tone_b_LP.Run( spl_fx_b );
					spl_fx = scft_Avg64( spl_fx_a, spl_fx_b, tone_control_adj );

					spl_fx_a = spl_fx;
					spl_fx_b = spl_fx;
					spl_fx_a = f2_tone_a_LP.Run( spl_fx_a );
					spl_fx_b = f2_tone_b_LP.Run( spl_fx_b );
					spl_fx = scft_Avg64( spl_fx_a, spl_fx_b, tone_control_adj );

					spl_fx_a = spl_fx;
					spl_fx_b = spl_fx;
					spl_fx_a = f3_tone_a_LP.Run( spl_fx_a );
					spl_fx_b = f3_tone_b_LP.Run( spl_fx_b );
					spl_fx = scft_Avg64( spl_fx_a, spl_fx_b, tone_control_adj );
*/
					spl_fx = f0_tone_LP.Run( spl_fx );
					spl_fx = f1_tone_LP.Run( spl_fx );
					spl_fx = f2_tone_LP.Run( spl_fx );
					spl_fx = f3_tone_LP.Run( spl_fx );

					return spl_fx;
				}
				Tone_Output()
				{
/*					f0_tone_HP.SetPassRate( 5.25 );
					f1_tone_HP.SetPassRate( 5.25 );
					f2_tone_HP.SetPassRate( 5.25 );
					f3_tone_HP.SetPassRate( 5.25 );
					f4_tone_HP.SetPassRate( 5.25 );
					f5_tone_HP.SetPassRate( 5.25 );
					f6_tone_HP.SetPassRate( 5.25 );
					f7_tone_HP.SetPassRate( 5.25 );

					f0_tone_a_LP.SetPassRate( 6600.0 );
					f1_tone_a_LP.SetPassRate( 6600.0 );
					f2_tone_a_LP.SetPassRate( 6600.0 );
					f3_tone_a_LP.SetPassRate( 6600.0 );

					f0_tone_b_LP.SetPassRate( 7500.0 );
					f1_tone_b_LP.SetPassRate( 7500.0 );
					f2_tone_b_LP.SetPassRate( 7500.0 );
					f3_tone_b_LP.SetPassRate( 7500.0 );
*/
					f0_tone_LP.SetPassRate( 9300.0 );
					f1_tone_LP.SetPassRate( 9300.0 );
					f2_tone_LP.SetPassRate( 9300.0 );
					f3_tone_LP.SetPassRate( 9300.0 );

					Clear();
				}
			}; // struct Tone_Output
			//! ----------------------------------------------------------------
			//! --- Primary FX --
			//! ----------------------------------------------------------------
			struct SCRFT_EXPORT Channel_Audio_Effect
			{
				const f80 _pi_f80;
				const f64 dn;

				// Sample and rate data
				f64 spl[64];
				f64 spl_out_L, spl_out_R;
				f64 spRate;
				f64 osRate;
				u32 oversampling_factor;
				f64 spl_boost_factor;
				f64 spl_div_factor;

				// Post-DownSampling Filters to trim off excess (very low) frequencies
				EQ_HP f0_trim_L, f1_trim_L;
				EQ_HP f0_trim_R, f1_trim_R;

				// Parameters
				f64 gain_input;
				f64 gain;
				f64 spl_volume_input;
				f64 spl_volume;
				f64 tone_adj_input;
				f64 tone_adj;
				bool FxOn;

				// Parameter Smoothing
				EQ_LP f_prm_gain;
				EQ_LP f_prm_spl_volume;
				EQ_LP f_prm_tone;

				// FX Components
				OverSampling_Eq_Filter OS_Filter_up_L, OS_Filter_up_R;
				OverSampling_Eq_Filter OS_Filter_dn_L, OS_Filter_dn_R;
				FxDrive_Channel FxDriveChannel_1_L, FxDriveChannel_1_R;
				Tone_Input Tone_In_L, Tone_In_R;
				Tone_Output Tone_Out_L, Tone_Out_R;

				inline void Clear()
				{
					for (u32 i = 0u; i < 64u; i++)
						spl[i] = 0.0;

					spl_out_L = 0.0;
					spl_out_R = 0.0;

					f0_trim_L.Clear(); f1_trim_L.Clear();
					f0_trim_R.Clear(); f1_trim_R.Clear();

					f_prm_gain.Clear();
					f_prm_spl_volume.Clear();
					f_prm_tone.Clear();

					OS_Filter_up_L.Clear();
					OS_Filter_dn_L.Clear();
					OS_Filter_up_R.Clear();
					OS_Filter_dn_R.Clear();

					FxDriveChannel_1_L.Clear();
					FxDriveChannel_1_R.Clear();

					Tone_In_L.Clear();
					Tone_In_R.Clear();

					Tone_Out_L.Clear();
					Tone_Out_R.Clear();
				}
				inline void SetAndCheckSampleRates()
				{
					if ( oversampling_factor < 2u )
						oversampling_factor = 2u;
					if ( oversampling_factor > 64u )
						oversampling_factor = 64u;
					if ( spRate < 44100.0 )
						spRate = 44100.0;

					osRate = f64 (spRate * (f64) oversampling_factor);
					spl_boost_factor = (f64) oversampling_factor;
					spl_div_factor = f64 (1.0 / (f64) oversampling_factor);

					// Set rate data for input control buffers
					f_prm_gain.SetSampleRate( spRate );
					f_prm_spl_volume.SetSampleRate( spRate );
					f_prm_tone.SetSampleRate( spRate );

					// Set rates for all components
					OS_Filter_up_L.SetSampleRate( spRate );
					OS_Filter_dn_L.SetSampleRate( spRate );
					OS_Filter_up_L.SetOverSamplingMultiplier( oversampling_factor );
					OS_Filter_dn_L.SetOverSamplingMultiplier( oversampling_factor );
					OS_Filter_up_R.SetSampleRate( spRate );
					OS_Filter_dn_R.SetSampleRate( spRate );
					OS_Filter_up_R.SetOverSamplingMultiplier( oversampling_factor );
					OS_Filter_dn_R.SetOverSamplingMultiplier( oversampling_factor );

					f0_trim_L.SetSampleRate( spRate );
					f1_trim_L.SetSampleRate( spRate );
					f0_trim_R.SetSampleRate( spRate );
					f1_trim_R.SetSampleRate( spRate );

					FxDriveChannel_1_L.SetSampleRate( osRate );
					FxDriveChannel_1_R.SetSampleRate( osRate );

					Tone_In_L.SetSampleRate( osRate );
					Tone_In_R.SetSampleRate( osRate );

					Tone_Out_L.SetSampleRate( osRate );
					Tone_Out_R.SetSampleRate( osRate );
				}
				inline void SetSampleRate(const f64 &inp)
				{
					spRate = (f64) inp;

					SetAndCheckSampleRates();
				}
				inline void SetOverSamplingMultiplier(const u32 &inp)
				{
					oversampling_factor = (u32) inp;

					SetAndCheckSampleRates();
				}
				inline void Run(const f64 inp)
				{
					gain = f_prm_gain.Run( gain_input );
					spl_volume = f_prm_spl_volume.Run( spl_volume_input );
					tone_adj = f_prm_tone.Run( tone_adj_input );

					spl_volume *= spl_volume * 4.0;

					if ( !FxOn )
					{
						spl_out_L = inp;
						spl_out_R = inp;

						return;
					}

					FxDriveChannel_1_L.SetGain( gain );
					Tone_In_L.SetTone( tone_adj );
//					Tone_Out_L.SetTone( tone_adj );

					for (u32 i = 1u; i < oversampling_factor; i++)
						spl[i] = dn;

					spl[0] = inp;

					for (u32 i = 0u; i < oversampling_factor; i++)
					{
						f64 fx_spl = spl[i];

						fx_spl = OS_Filter_up_L.Run_LP( fx_spl );
						fx_spl *= spl_boost_factor;

						FxDriveChannel_1_L.RunFxRead( fx_spl );

						fx_spl = Tone_In_L.Run( fx_spl ) * spl_volume;

						fx_spl = FxDriveChannel_1_L.Run( fx_spl );

						fx_spl = Tone_Out_L.Run( fx_spl );

						spl[i] = OS_Filter_dn_L.Run_LP( fx_spl );
					}

					f64 spl_sum_L = 0.0;
					for (u32 i = 0u; i < oversampling_factor; i++)
						spl_sum_L += spl[i];

					spl_sum_L *= spl_div_factor;

					spl_sum_L = f0_trim_L.Run( spl_sum_L );
					spl_sum_L = f1_trim_L.Run( spl_sum_L );

					spl_out_L = spl_sum_L;
					spl_out_R = spl_sum_L;
				}
				inline void Run(const f64 inp_L, const f64 inp_R)
				{
					gain = f_prm_gain.Run( gain_input );
					spl_volume = f_prm_spl_volume.Run( spl_volume_input );
					tone_adj = f_prm_tone.Run( tone_adj_input );

					spl_volume *= spl_volume * 4.0;

					if ( !FxOn )
					{
						spl_out_L = inp_L;
						spl_out_R = inp_R;

						return;
					}

					FxDriveChannel_1_L.SetGain( gain );
					FxDriveChannel_1_R.SetGain( gain );
					Tone_In_L.SetTone( tone_adj );
					Tone_In_R.SetTone( tone_adj );
//					Tone_Out_L.SetTone( tone_adj );
//					Tone_Out_R.SetTone( tone_adj );

				// Left Stereo Channel
					for (u32 i = 1u; i < oversampling_factor; i++)
						spl[i] = dn;

					spl[0] = inp_L;

					for (u32 i = 0u; i < oversampling_factor; i++)
					{
						f64 fx_spl = spl[i];

						fx_spl = OS_Filter_up_L.Run_LP( fx_spl );
						fx_spl *= spl_boost_factor;

						FxDriveChannel_1_L.RunFxRead( fx_spl );

						fx_spl = Tone_In_L.Run( fx_spl ) * spl_volume;

						fx_spl = FxDriveChannel_1_L.Run( fx_spl );

						fx_spl = Tone_Out_L.Run( fx_spl );

						spl[i] = OS_Filter_dn_L.Run_LP( fx_spl );
					}

					f64 spl_sum_L = 0.0;
					for (u32 i = 0u; i < oversampling_factor; i++)
						spl_sum_L += spl[i];

					spl_sum_L *= spl_div_factor;

					spl_sum_L = f0_trim_L.Run( spl_sum_L );
					spl_sum_L = f1_trim_L.Run( spl_sum_L );

					spl_out_L = spl_sum_L;

				// Right Stereo Channel
					for (u32 i = 1u; i < oversampling_factor; i++)
						spl[i] = dn;

					spl[0] = inp_R;

					for (u32 i = 0u; i < oversampling_factor; i++)
					{
						f64 fx_spl = spl[i];

						fx_spl = OS_Filter_up_R.Run_LP( fx_spl );
						fx_spl *= spl_boost_factor;

						FxDriveChannel_1_R.RunFxRead( fx_spl );

						fx_spl = Tone_In_R.Run( fx_spl ) * spl_volume;

						fx_spl = FxDriveChannel_1_R.Run( fx_spl );

						fx_spl = Tone_Out_R.Run( fx_spl );

						spl[i] = OS_Filter_dn_R.Run_LP( fx_spl );
					}

					f64 spl_sum_R = 0.0;
					for (u32 i = 0u; i < oversampling_factor; i++)
						spl_sum_R += spl[i];

					spl_sum_R *= spl_div_factor;

					spl_sum_R = f0_trim_R.Run( spl_sum_R );
					spl_sum_R = f1_trim_R.Run( spl_sum_R );

					spl_out_R = spl_sum_R;
				}
				inline void SetGain(const f64 &inp)
				{
					gain_input = scft_Clamp64( inp, 0.0, 1.0 );
				}
				inline void SetInputBoost(const f64 &inp)
				{
					spl_volume_input = scft_Clamp64( inp, 0.0, 1.0 );
				}
				inline void SetTone(const f64 &inp)
				{
					tone_adj_input = scft_Clamp64( inp, 0.0, 1.0 );
				}
				inline void SetFxOnOff(const f64 &inp)
				{
					if ( inp < 0.5 )
						{
							FxOn = false;

							Clear();
						}
					else
						FxOn = true;
				}
				void Init()
				{
					for (u32 i = 0u; i < 64u; i++)
						spl[i] = 0.0;

					FxDriveChannel_1_L = FxDrive_Channel(	4u,		// Number of tubes in channel
														0.1200,		// Minimum gain setting
														1.0000,		// Maximum gain setting
														1.6500,		// Master input volume adjustment
														0.7500	);	// Master output volume adjustment

					FxDriveChannel_1_R = FxDriveChannel_1_L;

					f0_trim_L.SetPassRate( 12.0 );
					f1_trim_L.SetPassRate( 12.0 );
					f0_trim_R.SetPassRate( 12.0 );
					f1_trim_R.SetPassRate( 12.0 );

					f_prm_gain.SetPassRate( 25.50 );
					f_prm_spl_volume.SetPassRate( 25.50 );
					f_prm_tone.SetPassRate( 25.50 );

					Clear();

					SetAndCheckSampleRates();
				}
				void UnInit() const
				{}
				Channel_Audio_Effect() :
					_pi_f80( (f80) 3.14159265358979323846264338327950288419716939937510L ),
					dn( (f64) powl( (f80) 10.L, (f80) -30.L ) )
				{
					gain_input = 0.0;
					gain = 0.0;

					spl_volume_input = 0.0;
					spl_volume = 0.0;

					tone_adj_input = 0.0;
					tone_adj = 0.0;

					FxOn = true;

					Init();
				}
			}; // struct Channel_Audio_Effect

			//! ----------------------------------------------------------------
			f64 prm[DistortionFX_RageStomp_Params::kMax_Parameter_Count];
			bool prm_dirty[DistortionFX_RageStomp_Params::kMax_Parameter_Count];

			Channel_Audio_Effect FX0;

			inline void SetOverSamplingMultiplier(const u32 &inp, const bool inp_online);
			inline void CheckOverSamplingSettings();
		}; // class DistortionFX_RageStomp
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!---  RageStomp Guitar Amplifier Head :: Parameters
//!---  --- Definitions
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
		DistortionFX_RageStomp_Params::DistortionFX_RageStomp_Params()
		{
			SetID();
			SetVersionInfo();
			PresetData.Init();
			currentPreset = 0u;
		}
		DistortionFX_RageStomp_Params::DistortionFX_RageStomp_Params(const ::ScorchCrafter::Base::Plug_ParameterList &other)
		{
			SetID();
			SetVersionInfo();
			PresetData.Init();
			currentPreset = 0u;

			const u32 otherParamCount = (u32) ((DistortionFX_RageStomp_Params)other).GetNumberOfParameters();
			const u32 otherPresetCount = (u32) ((DistortionFX_RageStomp_Params)other).GetNumberOfPresets();
			const s32 otherVersionNumber = (s32) ((DistortionFX_RageStomp_Params)other).GetVersionNumber();

			if ( !CompareID( ((DistortionFX_RageStomp_Params)other) ) )
				return;
			if ( versionNumber != otherVersionNumber )
				return;
			if ( otherParamCount != (u32) kMax_Parameter_Count )
				return;
			if ( otherPresetCount != (u32) kPreset_MAX_COUNT )
				return;

			PresetData = ((DistortionFX_RageStomp_Params)other).PresetData;
			currentPreset = (u32) ((DistortionFX_RageStomp_Params)other).currentPreset;
		}
		inline DistortionFX_RageStomp_Params& DistortionFX_RageStomp_Params::operator=(const ::ScorchCrafter::Base::Plug_ParameterList &other)
		{
			SetID();
			SetVersionInfo();
			PresetData.Init();
			currentPreset = 0u;

			const u32 otherParamCount = (u32) ((DistortionFX_RageStomp_Params)other).GetNumberOfParameters();
			const u32 otherPresetCount = (u32) ((DistortionFX_RageStomp_Params)other).GetNumberOfPresets();
			const s32 otherVersionNumber = (s32) ((DistortionFX_RageStomp_Params)other).GetVersionNumber();

			if ( !CompareID( ((DistortionFX_RageStomp_Params)other) ) )
				return *this;
			if ( versionNumber != otherVersionNumber )
				return *this;
			if ( otherParamCount != (u32) kMax_Parameter_Count )
				return *this;
			if ( otherPresetCount != (u32) kPreset_MAX_COUNT )
				return *this;

			PresetData = ((DistortionFX_RageStomp_Params)other).PresetData;
			currentPreset = (u32) ((DistortionFX_RageStomp_Params)other).currentPreset;

			return *this;
		}

		inline u32 DistortionFX_RageStomp_Params::GetNumberOfParameters()
		{
			return (u32) kMax_Parameter_Count;
		}
		inline u32 DistortionFX_RageStomp_Params::GetNumberOfPresets()
		{
			return (u32) kPreset_MAX_COUNT;
		}
		inline s32 DistortionFX_RageStomp_Params::GetID(const s32 index)
		{
			if ( (index < 0) || (index >= 16) )
				return 0;

			return (s32) ID[index];
		}
		inline s32 DistortionFX_RageStomp_Params::GetVersionNumber()
		{
			return (s32) versionNumber;
		}
		inline void DistortionFX_RageStomp_Params::Reset()
		{
			currentPreset = 0u;
		}
		inline void DistortionFX_RageStomp_Params::Reset(const u32 &preset_number)
		{
			SetToPreset( preset_number );
		}
		inline void DistortionFX_RageStomp_Params::SetToPreset(const u32 &preset_number)
		{
			currentPreset = (u32) preset_number;

			if ( currentPreset >= (u32) kPreset_MAX_COUNT )
				currentPreset = (u32) (kPreset_MAX_COUNT - 1u);
		}
		inline u32 DistortionFX_RageStomp_Params::GetCurrentPreset()
		{
			return currentPreset;
		}
		inline void DistortionFX_RageStomp_Params::SetPresetName(const char* name, size_t length)
		{
			if ( currentPreset < (u32) kPreset_MAX_COUNT )
				strncpy ( PresetData.PresetLabels.label[currentPreset].txt, name, (length <= 127) ? length : 127 );
		}
		inline void DistortionFX_RageStomp_Params::GetPresetName(char *name, size_t length)
		{
			if ( currentPreset < (u32) kPreset_MAX_COUNT )
				strncpy ( name, PresetData.PresetLabels.label[currentPreset].txt, (length <= 127) ? length : 127 );
			else
				strncpy ( name, "-", length );
		}
		inline void DistortionFX_RageStomp_Params::GetPresetName(char *name, size_t length, const u32 &index)
		{
			if ( index < (u32) kPreset_MAX_COUNT )
				strncpy ( name, PresetData.PresetLabels.label[index].txt, (length <= 127) ? length : 127 );
			else
				strncpy ( name, "-", length );
		}
		inline void DistortionFX_RageStomp_Params::SetParameter(const u32 &index, const f64 &value)
		{
			if ( index < (u32) kMax_Parameter_Count )
				PresetData.Bank[currentPreset].prm[index] = value;
		}
		inline f64 DistortionFX_RageStomp_Params::GetParameter(const u32 &index)
		{
			if ( index < (u32) kMax_Parameter_Count )
				return PresetData.Bank[currentPreset].prm[index];

			return 0.0;
		}
		inline void DistortionFX_RageStomp_Params::GetParameterName(const u32 &index, char *name, size_t length)
		{
			if ( index < (u32) kMax_Parameter_Count )
				strncpy ( name, PresetData.ControlLabels.label[index].txt, (length <= 15) ? length : 15 );
			else
				strncpy ( name, "-", length );
		}
		inline void DistortionFX_RageStomp_Params::SetID()
		{
			ID[0] =		(s32) 'R';
			ID[1] =		(s32) 'a';
			ID[2] =		(s32) 'g';
			ID[3] =		(s32) 'e';
			ID[4] =		(s32) '-';
			ID[5] =		(s32) 'S';
			ID[6] =		(s32) 't';
			ID[7] =		(s32) 'o';
			ID[8] =		(s32) 'm';
			ID[9] =		(s32) 'p';
			ID[10] =	(s32) '-';
			ID[11] =	(s32) 'F';
			ID[12] =	(s32) 'X';
			ID[13] =	(s32) '-';

			#ifdef STEREO_FX_PLUG
				ID[14] =	(s32) 'S';
			#else
				ID[14] =	(s32) 'M';
			#endif

			#ifndef SCORCHCRAFTER_COMPILE_64
				ID[15] =	(s32) '6';
				ID[16] =	(s32) '4';
			#else
				ID[15] =	(s32) '3';
				ID[16] =	(s32) '2';
			#endif
		}
		inline void DistortionFX_RageStomp_Params::SetVersionInfo()
		{
			versionNumber = s32 (
									s32 (s32 (SC_PLG_VER_A) * 1000000) +
									s32 (s32 (SC_PLG_VER_B) * 10000) +
									s32 (s32 (SC_PLG_VER_C) * 100) +
									s32 (SC_PLG_VER_D)
								);
		}
		inline bool DistortionFX_RageStomp_Params::CompareID(const ::ScorchCrafter::Base::Plug_ParameterList &other)
		{
			bool chk_result = true;
			for (u32 i = 0u; i < 16u; i++)
			{
				if ( (s32) ID[i] != (s32) ((DistortionFX_RageStomp_Params)other).GetID( i ) )
					chk_result = false;
			}

			return chk_result;
		}

//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!---  RageStomp Guitar Amplifier Head :: Audio Effect
//!---  --- Definitions
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
		DistortionFX_RageStomp::DistortionFX_RageStomp()
		{
			for(u32 i = 0u; i < 32u; i++)
			{
				s_input[i] = 0.0;
				s_output[i] = 0.0;
			}

			#ifdef STEREO_FX_PLUG
				#ifndef SCORCHCRAFTER_COMPILE_64
					InfoData.ID[0] = 'r';
					InfoData.ID[1] = 'g';
					InfoData.ID[2] = 's';
					InfoData.ID[3] = '0';

					InfoData.numInputs = 2;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 32 RageStomp (Dual)";
					InfoData.plugin_ID_string = "SC32RgStmpD";
				#else
					InfoData.ID[0] = 'r';
					InfoData.ID[1] = 'g';
					InfoData.ID[2] = 's';
					InfoData.ID[3] = '1';

					InfoData.numInputs = 2;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 64 RageStomp (Dual)";
					InfoData.plugin_ID_string = "SC64RgStmpD";
				#endif // SCORCHCRAFTER_COMPILE_64
			#else
				#ifndef SCORCHCRAFTER_COMPILE_64
					InfoData.ID[0] = 'r';
					InfoData.ID[1] = 'g';
					InfoData.ID[2] = 's';
					InfoData.ID[3] = '2';

					InfoData.numInputs = 1;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 32 RageStomp (Mono)";
					InfoData.plugin_ID_string = "SC32RgStmp";
				#else
					InfoData.ID[0] = 'r';
					InfoData.ID[1] = 'g';
					InfoData.ID[2] = 's';
					InfoData.ID[3] = '3';

					InfoData.numInputs = 1;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 64 RageStomp (Mono)";
					InfoData.plugin_ID_string = "SC64RgStmp";
				#endif // SCORCHCRAFTER_COMPILE_64
			#endif // STEREO_FX_PLUG

			InfoData.version = s32 (
								s32 (s32 (SC_PLG_VER_A) * 1000000) +
								s32 (s32 (SC_PLG_VER_B) * 10000) +
								s32 (s32 (SC_PLG_VER_C) * 100) +
								s32 (SC_PLG_VER_D)
								);

			for (u32 i = 0u; i < (u32) DistortionFX_RageStomp_Params::kMax_Parameter_Count; i++)
			{
				prm[i] = 0.0;
				prm_dirty[i] = true;
			}

			FX0.Init();
			FX0.Clear();
			FX0.SetAndCheckSampleRates();

			spRate = 44100.0;

			oversampling_old = 0u;
			oversampling_current = 2u;
			oversampling_online = 2u;
			oversampling_offline = 2u;
		}
		DistortionFX_RageStomp::DistortionFX_RageStomp(const ::ScorchCrafter::Base::BasePlugin &other)
		{
			for(u32 i = 0u; i < 32u; i++)
			{
				s_input[i] = 0.0;
				s_output[i] = 0.0;
			}

			#ifdef STEREO_FX_PLUG
				#ifndef SCORCHCRAFTER_COMPILE_64
					InfoData.ID[0] = 'r';
					InfoData.ID[1] = 'g';
					InfoData.ID[2] = 's';
					InfoData.ID[3] = '0';

					InfoData.numInputs = 2;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 32 RageStomp (Dual)";
					InfoData.plugin_ID_string = "SC32RgStmpD";
				#else
					InfoData.ID[0] = 'r';
					InfoData.ID[1] = 'g';
					InfoData.ID[2] = 's';
					InfoData.ID[3] = '1';

					InfoData.numInputs = 2;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 64 RageStomp (Dual)";
					InfoData.plugin_ID_string = "SC64RgStmpD";
				#endif // SCORCHCRAFTER_COMPILE_64
			#else
				#ifndef SCORCHCRAFTER_COMPILE_64
					InfoData.ID[0] = 'r';
					InfoData.ID[1] = 'g';
					InfoData.ID[2] = 's';
					InfoData.ID[3] = '2';

					InfoData.numInputs = 1;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 32 RageStomp (Mono)";
					InfoData.plugin_ID_string = "SC32RgStmp";
				#else
					InfoData.ID[0] = 'r';
					InfoData.ID[1] = 'g';
					InfoData.ID[2] = 's';
					InfoData.ID[3] = '3';

					InfoData.numInputs = 1;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 64 RageStomp (Mono)";
					InfoData.plugin_ID_string = "SC64RgStmp";
				#endif // SCORCHCRAFTER_COMPILE_64
			#endif // STEREO_FX_PLUG

			InfoData.version = s32 (
								s32 (s32 (SC_PLG_VER_A) * 1000000) +
								s32 (s32 (SC_PLG_VER_B) * 10000) +
								s32 (s32 (SC_PLG_VER_C) * 100) +
								s32 (SC_PLG_VER_D)
								);

			for (u32 i = 0u; i < (u32) DistortionFX_RageStomp_Params::kMax_Parameter_Count; i++)
			{
				prm[i] = ((DistortionFX_RageStomp)other).GetParameter( i );
				prm_dirty[i] = true;
			}

			FX0.Init();
			FX0.Clear();
			FX0.SetAndCheckSampleRates();

			spRate = ((DistortionFX_RageStomp)other).spRate;

			oversampling_old = ((DistortionFX_RageStomp)other).oversampling_old;
			oversampling_current = ((DistortionFX_RageStomp)other).oversampling_current;
			oversampling_online = ((DistortionFX_RageStomp)other).oversampling_online;
			oversampling_offline = ((DistortionFX_RageStomp)other).oversampling_offline;

			FX0.SetSampleRate( spRate );
			FX0.SetOverSamplingMultiplier( oversampling_current );
		}
		DistortionFX_RageStomp::~DistortionFX_RageStomp()
		{
			FX0.UnInit();
		}
		inline void DistortionFX_RageStomp::Init(const f32 smpRate)
		{
			spRate = (f64) smpRate;
			if ( spRate < 44100.0 )
				spRate = 44100.0;

			FX0.Clear();
			FX0.SetSampleRate( spRate );
			FX0.SetOverSamplingMultiplier( oversampling_current );
		}
		inline void DistortionFX_RageStomp::SetSampleRate(const f32 inp_rate)
		{
			spRate = (f64) inp_rate;
			if ( spRate < 44100.0 )
				spRate = 44100.0;

			FX0.Clear();
			FX0.SetSampleRate( spRate );
			FX0.SetOverSamplingMultiplier( oversampling_current );
		}
		inline void DistortionFX_RageStomp::SetParameter(const f64 &inp, const u32 &index)
		{
			if ( index < (u32) DistortionFX_RageStomp_Params::kMax_Parameter_Count )
			{
				prm[index] = (f64) inp;
				prm_dirty[index] = true;
			}

			if ( index == (u32) DistortionFX_RageStomp_Params::kInputBoost )
			{
				FX0.SetInputBoost( prm[index] );
			} else
			if ( index == (u32) DistortionFX_RageStomp_Params::kGainControl )
			{
				FX0.SetGain( prm[index] );
			} else
			if ( index == (u32) DistortionFX_RageStomp_Params::kTone )
			{
				FX0.SetTone( prm[index] );
			} else
			if ( index == (u32) DistortionFX_RageStomp_Params::kStompOnOff )
			{
				FX0.SetFxOnOff( prm[index] );
			}
		}
		inline f64 DistortionFX_RageStomp::GetParameter(const u32 &index)
		{
			if ( index < (u32) DistortionFX_RageStomp_Params::kMax_Parameter_Count )
				return prm[index];

			return 0.0;
		}
		inline Plug_InfoData DistortionFX_RageStomp::GetPlugInfo()
		{
			return InfoData;
		}
		inline void DistortionFX_RageStomp::Run()
		{
		#ifdef STEREO_FX_PLUG
			FX0.Run( s_input[0], s_input[1] );
		#else
			FX0.Run( s_input[0] );
		#endif // STEREO_FX_PLUG

			s_output[0] = FX0.spl_out_L * prm[DistortionFX_RageStomp_Params::kMasterVol];
			s_output[1] = FX0.spl_out_R * prm[DistortionFX_RageStomp_Params::kMasterVol];
		}
		inline void DistortionFX_RageStomp::RunSampleBlock()
		{
			for (u32 index = 0u; index < (u32) DistortionFX_RageStomp_Params::kMax_Parameter_Count; index++)
			{
				if ( prm_dirty[index] )
				{
					if ( index == (u32) DistortionFX_RageStomp_Params::kOverSampling_On )
					{
						if ( prm[index] < 0.005 )
						{
							SetOverSamplingMultiplier( 2, true );
						} else
						{
							const f64 check_increment = 0.010;
							f64 check_value = 0.005;
							bool val_found = false;
							u32 multiplier = 0u;
							u32 multiplier_accum = 3u;

							while ( (!val_found) && (check_value <= 1.005) )
							{
								if ( (prm[index] >= check_value) && (prm[index] < (check_value+check_increment)) )
								{
									multiplier = multiplier_accum;
									val_found = true;

									break;
								}

								multiplier_accum++;
								check_value += check_increment;
							}

							if ( multiplier < 2u )
								multiplier = 2u;
							if ( multiplier > 99u )
								multiplier = 99u;

							SetOverSamplingMultiplier( multiplier, true );
						}
					} else
					if ( index == (u32) DistortionFX_RageStomp_Params::kOverSampling_Off )
					{
						if ( prm[index] < 0.005 )
						{
							SetOverSamplingMultiplier( 2, false );
						} else
						{
							const f64 check_increment = 0.010;
							f64 check_value = 0.005;
							bool val_found = false;
							u32 multiplier = 0u;
							u32 multiplier_accum = 3u;

							while ( (!val_found) && (check_value <= 1.005) )
							{
								if ( (prm[index] >= check_value) && (prm[index] < (check_value+check_increment)) )
								{
									multiplier = multiplier_accum;
									val_found = true;

									break;
								}

								multiplier_accum++;
								check_value += check_increment;
							}

							if ( multiplier < 2u )
								multiplier = 2u;
							if ( multiplier > 99u )
								multiplier = 99u;

							SetOverSamplingMultiplier( multiplier, false );
						}
					}

					prm_dirty[index] = false;
				}
			}

			CheckOverSamplingSettings();
		}
		inline void DistortionFX_RageStomp::SetBlockSize(const u32 inp)
		{}
		//! ----------------------------------------------------------------
		//! --  Private Functions  -----------------------------------------
		//! ----------------------------------------------------------------
		inline void DistortionFX_RageStomp::SetOverSamplingMultiplier(const u32 &inp, const bool inp_online)
		{
			u32 oversampling_new = (u32) inp;

			if ( oversampling_new < 2u )
				oversampling_new = 2u;

			if ( inp_online )
				oversampling_online = oversampling_new;
			else
				oversampling_offline = oversampling_new;

			if ( runningOffline )
				CheckOverSamplingSettings();
		}
		inline void DistortionFX_RageStomp::CheckOverSamplingSettings()
		{
			if ( !runningOffline )
				oversampling_current = oversampling_online;
			else
				oversampling_current = oversampling_offline;

			if ( oversampling_old != oversampling_current )
			{
				FX0.SetOverSamplingMultiplier( oversampling_current );
			}
			oversampling_old = oversampling_current;
		}
	} // namespace Plugins
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!---  ScorchCrafter VST Data
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
	const int SCRFT_PLG_NUM_PROGRAMS = (int) DistortionFX_RageStomp_Params::kPreset_MAX_COUNT;
	const int SCRFT_PLG_NUM_PARAMETERS = (int) DistortionFX_RageStomp_Params::kMax_Parameter_Count;
} // namespace ScorchCrafter

#endif // SCORCHCRAFTER_PLUGIN_RAGESTOMP_H

//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!---  General Information for ScorchCrafter Audio FX
//!---  - (In other words, how to use this header file)
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
/**

// This code should be in a C++ file that uses (#includes) the current header file you are now reading
//   in order to build a VST v2.4 Audio Effect.
// NOTE: There is a .cpp file aready in the code base, which should be found in the same directory / folder
//   as this header file, so you don't have to bother creating your own.
// NOTE: The code for the GUI is in a seperate header file, so if you don't like the original GUI you can
//   create your own version based upon the existing code in that header and link your own GUI instead.
// NOTE: The "VstBase_2.h" file will look for and try to include the following files:
//
// #include "../sdk_deps/zlib/zlib.h"
// #include "../sdk_deps/libpng/png.h"

// #include "aeffectx.h"
// #include "audioeffectx.h"
// #include "vstfxstore.h"

// #include "aeffeditor.h"
// #include "vstgui.h"

// #include "vstcontrols.h"
// #include "aeffguieditor.h"
//
// NOTE: If you want to build your own version which has your own custom
//   GUI with a different version of the VSTGUI library found with ScorchCrafter
//   software, or a different GUI library altogether, or even no GUI at all,
//   you can #define the following BEFORE #including any ScorchCrafter headers
//   or in your IDE's project file:
//
//   SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI
//
//   This #define will skip trying to load the included VSTGUI library,
//   as well as libpng and zlib libraries.  However, this plug-in header
//   will still attempt to access a "RageStomp_GUI.h" file, and use specific
//   classes and functions from such a file.
//   If you make your own GUI you will need to either write your own versions which
//   supply the expected class and function names, modify this header file, or
//   write a simple "dummy" header file which uses empty functions that do nothing,
//   depending on what your needs are and what you are trying to do.

// -- START of .cpp file -- (Note that there is more documentation you don't need later on down, so don't copy / paste from here all the way to the end of this file, thank you.)

	// These first four files are pretty much required, either the ones with the code base
	//   which are published with the ScorchCrafter project (currently on SourceForge),
	//   or your own versions if you want to make something based upon a ScorchCrafer
	//   software plug-in effect.
	#include "ScorchCrafter_Plugin.h"											//< For base class types
	#include "Plugins\Guitar_Amplifier_Heads\RageStomp.h"					//< The actual effect declarations and definitions, for both the effect and related parameters

	#ifndef SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI
		#include "Plugins\Guitar_Amplifier_Heads\RageStomp_GUI.h"				//< The GUI (Graphic User Interface) for the effect
	#endif

	#include "VstBase_2.h"														//< The VST wrapper audio effect class

	// These come from Steinberg's VST SDK.  Official ScorchCrafter Software
	//   uses mostly the 2.4 version of the SDK, although it might (or might not)
	//   work with other versions or wrappers / adapter code for your own software,
	//   results will certainly vary.
	// NOTE: As of this writing, there is development work being done to eventually
	//   update all of this to work with the newest 3.x SDK, but this is currently
	//   not complete.
	#include "audioeffect.cpp"													//< From the VST SDK by Steinberg
	#include "audioeffectx.cpp"													//< From the VST SDK by Steinberg
	#include "vstplugmain.cpp"													//< From the VST SDK by Steinberg

	// NOTE: The empty namespace declarations are to avoid compiler errors / warnings.
	namespace ScorchCrafter
	{
		namespace DataTypes
		{
		}
		namespace Base
		{
			struct Plug_InfoData;
			class BasePlugin;
			class Plug_ParameterList;
		}
		namespace Plugins
		{
		}

		SCRFT_EXPORT Base::BasePlugin* SCRFT_CreatePlugin()
		{
			Base::BasePlugin* Plg = new Plugins::DistortionFX_RageStomp();

			return Plg;
		};
		SCRFT_EXPORT Base::Plug_ParameterList* SCRFT_CreateParameterList()
		{
			Plug_ParameterList* ParamList = new Plugins::DistortionFX_RageStomp_Params();

			return ParamList;
		};
	}
	using namespace ScorchCrafter;
	using namespace ScorchCrafter::DataTypes;
	using namespace ScorchCrafter::Base;
	using namespace ScorchCrafter::Plugins;

	class PlgEditor_SCplug;
	class Scr_VST_Plugin;

	SCRFT_EXPORT AEffGUIEditor* SCRFT_createEditor(AudioEffectX* effect)
	{
		return new PlgEditor_SCplug( effect );
	};
	SCRFT_EXPORT AEffGUIEditor* createEditor(AudioEffectX* effect)
	{
		return new PlgEditor_SCplug( effect );
	};
	SCRFT_EXPORT AudioEffect* createEffectInstance(audioMasterCallback audioMaster)
	{
		return new Scr_VST_Plugin( audioMaster );
	}

// -- END of .cpp file -- (You don't need to copy this line or anything beyond it, unless you want to copy other project notes for handy reference right in your source code file.)
*/

/**
Official ScorchCrafter plug-ins are built with MinGW-w64 software, with the following
  switches, options, and settings below.  Of course you can use whatever
  compiler / options you want, these are here for reference.

g++ compiler options:
-std=c++11
-O2
-fexpensive-optimizations
-mtune=generic
-static
-fstrict-aliasing
-ffast-math
-funsafe-loop-optimizations
-funsafe-math-optimizations
-mthreads
-fno-rtti
-fno-exceptions
-std=gnu++11
-trigraphs
-Wno-multichar
-Wno-write-strings
-Wno-pointer-arith
-Wno-narrowing
-mwindows
-static-libgcc
-static-libstdc++
-finline-functions
-fno-math-errno
-ffinite-math-only
-fno-rounding-math
-fno-signaling-nans
-fno-trapping-math
-fno-signed-zeros
-fassociative-math
-fvisibility=default
-fno-common
-fdelete-dead-exceptions
-maccumulate-outgoing-args
-Wl,--strip-debug
-Wl,--strip-discarded

32-bits only:
-Wl,--large-address-aware

64-bits only:
-m64

g++ linker options (in addition to the ones listed for g++):
-def ..\..\src\plugin\jykwrakker\plg.def

Pre-Process #define(s):	// Note: Some of these are old (previous versions of the software) and not needed, this needs to be cleaned up at some point!
SC_PLG_VER_A=$VERSION_PART_A
SC_PLG_VER_B=$VERSION_PART_B
SC_PLG_VER_C=$VERSION_PART_C
SC_PLG_VER_D=$VERSION_PART_D
SC_PLG_VER_REL=$VERSION_IS_RELEASE
NDEBUG
_USE_MATH_DEFINES
CRT_SECURE_NO_WARNINGS=1
_CRT_SECURE_NO_WARNINGS=1
CRT_SECURE_NO_DEPRECATE=1
_CRT_SECURE_NO_DEPRECATE=1
EXPORTS
MINGW32
_MINGW32_
__MINGW32__
GNUC
_GNUC_
VST_PLUGCLASS=RageStomp
RageStomp_EXPORTS
VSTPluginMain_EXPORTS
EXPORTS_ALL
SC_Gen_Plugin_EXPORTS
Scr_VST_Plugin_EXPORTS
PlgEditor_SCplug_EXPORTS
VSTGUI_EXPORTS
BUILD_VST
SCORCHCRAFTER_WINDOWS
_USERDLL
ZLIB_EXPORTS
LIBZ_EXPORTS
Z_EXPORTS
NO_VIZ
LIBPNG_EXPORTS
PNG_STATIC
PNG_NO_CONSOLE_IO
USE_LIBPNG=1
ScorchCrafter_ENABLE_CHANGING_FPU_CW=1

64-bits only:
SCORCHCRAFTER_COMPILE_64

Stereo (both input and output) versions only: // Note that the mono versions still have stereo outputs, just mono inputs.
STEREO_FX_PLUG

C++ Dependencies:
ScorchCrafter source code looks for and expects the following C++ headers,
  (PLEASE NOTE that some of the files listed don't have an extension of ".h" or
  any extension at all, and this is NOT a typo!  If you are using a non-MinGW-w64
  compiler, you may need to tweak the code a bit or write wrapper files the
  compiler will find to #include the right stuff.

// C++
	<cmath>
	<cinttypes>

// ScorchCrafter
	"VstBase_2.h"
	"ScorchCrafter_Plugin.h"
	"(Plug-in FX Name).h" < This file you are now reading (Well, duh...)

// VSTGUI dependencies
	<zlib.h>
	<png.h>

// VSTGUI
	"vstgui.h"
	"vstcontrols.h"
	"aeffguieditor.h"

The ScorchCrafter header files also look for the VSTGUI library, the version found
with the official code base, as it is downloaded from SourceForge.  You can override
trying to #include such files, as well as the zlib and libpng headers, by #defining:
SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI to use a different library or your own GUI.

*/
