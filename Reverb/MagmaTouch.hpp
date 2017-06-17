#ifndef SCORCHCRAFTER_PLUGIN_JYKWRAKKER_H
#define SCORCHCRAFTER_PLUGIN_JYKWRAKKER_H

#define SC_PLG_VER_A 1

#define SC_PLG_VER_B 1

#define SC_PLG_VER_C 1

#define SC_PLG_VER_D 1


#include "ScorchCrafter_Plugin.hpp"
#include <cmath>

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
//!---  MagmaTouch Reverb :: Parameters
//!---  --- Prototypes
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
		class SCRFT_EXPORT Reverb_MagmaTouch_Params : public ::ScorchCrafter::Base::Plug_ParameterList
		{
		public:
			enum kSCsoftParams
			{
				kOverSampling_On		= 0,
				kOverSampling_Off		= 1,
				kMasterVol				= 2,
				kWetDryMix				= 3,
				kEQ_HP					= 4,
				kEQ_LP					= 5,
				kEQ_ExtraPass			= 6,
				kPreDelay				= 7,
				kPreDelayFine			= 8,
				kReverbLength			= 9,
				kReverbLengthFine		= 10,
				kBypassFX				= 11,
				kMax_Parameter_Count	= 12
			};
			struct SCRFT_EXPORT paramTextLabelList
			{
				txtString_16 label[kMax_Parameter_Count];

				void Init()
				{
					strncpy( label[kOverSampling_On].txt,		"Smp on  ", 15 );
					strncpy( label[kOverSampling_Off].txt,		"Smp off ", 15 );
					strncpy( label[kMasterVol].txt,				"Master v", 15 );
					strncpy( label[kWetDryMix].txt,				"Mix     ", 15 );
					strncpy( label[kEQ_HP].txt,					"EQ HP   ", 15 );
					strncpy( label[kEQ_LP].txt,					"EQ LP   ", 15 );
					strncpy( label[kEQ_ExtraPass].txt,			"EQ xtra ", 15 );
					strncpy( label[kPreDelay].txt,				"preDly  ", 15 );
					strncpy( label[kPreDelayFine].txt,			"preDlyFn", 15 );
					strncpy( label[kReverbLength].txt,			"Length  ", 15 );
					strncpy( label[kReverbLengthFine].txt,		"LengthFn", 15 );
					strncpy( label[kBypassFX].txt,				"Bypass  ", 15 );
				}
			};
			enum kPresetControlList
			{
				kPreset_Init					= 0,
				kPreset_Clean_Bright,
				kPreset_Clean_Warm,
				kPreset_BuzzyClean_Bright,
				kPreset_BuzzyClean_Warm,
				kPreset_LightCrunch_Bright,
				kPreset_LightCrunch_Warm,
				kPreset_BoostedCrunch_Bright,
				kPreset_BoostedCrunch_Warm,
				kPreset_LightDrive_Bright,
				kPreset_LightDrive_Warm,
				kPreset_BoostedDrive_Bright,
				kPreset_BoostedDrive_Warm,
				kPreset_HiGain_Bright,
				kPreset_HiGain_Warm,
				kPreset_HeavyHiGain_Bright,
				kPreset_HeavyHiGain_Warm,

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
					strncpy( label[kPreset_Clean_Bright].txt,			"Crystal Clean, Bright", 127 );
					strncpy( label[kPreset_Clean_Warm].txt,				"Crystal Clean, Warm", 127 );
					strncpy( label[kPreset_BuzzyClean_Bright].txt,		"Buzzy Clean, Bright", 127 );
					strncpy( label[kPreset_BuzzyClean_Warm].txt,		"Buzzy Clean, Warm", 127 );
					strncpy( label[kPreset_LightCrunch_Bright].txt,		"Light Crunch, Bright", 127 );
					strncpy( label[kPreset_LightCrunch_Warm].txt,		"Light Crunch, Warm", 127 );
					strncpy( label[kPreset_BoostedCrunch_Bright].txt,	"Strong Crunch, Bright", 127 );
					strncpy( label[kPreset_BoostedCrunch_Warm].txt,		"Strong Crunch, Warm", 127 );
					strncpy( label[kPreset_LightDrive_Bright].txt,		"Light OverDrive, Bright", 127 );
					strncpy( label[kPreset_LightDrive_Warm].txt,		"Light OverDrive, Warm", 127 );
					strncpy( label[kPreset_BoostedDrive_Bright].txt,	"Strong OverDrive, Bright", 127 );
					strncpy( label[kPreset_BoostedDrive_Warm].txt,		"Strong OverDrive, Warm", 127 );
					strncpy( label[kPreset_HiGain_Bright].txt,			"Hi-Gain, Bright", 127 );
					strncpy( label[kPreset_HiGain_Warm].txt,			"Hi-Gain, Warm", 127 );
					strncpy( label[kPreset_HeavyHiGain_Bright].txt,		"Heavy Hi-Gain, Bright", 127 );
					strncpy( label[kPreset_HeavyHiGain_Warm].txt,		"Heavy Hi-Gain, Warm", 127 );

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
							Bank[x].prm[kOverSampling_On]		= 0.01;
							Bank[x].prm[kOverSampling_Off]		= 0.10;
							Bank[x].prm[kMasterVol]				= 1.00;
							Bank[x].prm[kWetDryMix]				= 0.50;
							Bank[x].prm[kEQ_HP]					= 0.00;
							Bank[x].prm[kEQ_LP]					= 1.00;
							Bank[x].prm[kEQ_ExtraPass]			= 0.00;
							Bank[x].prm[kPreDelay]				= 0.00;
							Bank[x].prm[kPreDelayFine]			= 0.00;
							Bank[x].prm[kReverbLength]			= 0.50;
							Bank[x].prm[kReverbLengthFine]		= 0.00;
							Bank[x].prm[kBypassFX]				= 0.00;
						}
					}
/*
					Bank[kPreset_Clean_Bright].prm[kInputBoost] = 0.00;
					Bank[kPreset_Clean_Bright].prm[kBright] = 1.00;
					Bank[kPreset_Clean_Bright].prm[kAmpChan] = 0.00;
					Bank[kPreset_Clean_Bright].prm[kNoiseFilter_On] = 0.00;

					Bank[kPreset_Clean_Warm].prm[kInputBoost] = 0.00;
					Bank[kPreset_Clean_Warm].prm[kBright] = 0.00;
					Bank[kPreset_Clean_Warm].prm[kAmpChan] = 0.00;
					Bank[kPreset_Clean_Warm].prm[kNoiseFilter_On] = 0.00;

					Bank[kPreset_BuzzyClean_Bright].prm[kInputBoost] = 1.00;
					Bank[kPreset_BuzzyClean_Bright].prm[kBright] = 1.00;
					Bank[kPreset_BuzzyClean_Bright].prm[kAmpChan] = 0.00;
					Bank[kPreset_BuzzyClean_Bright].prm[kNoiseFilter_On] = 0.00;

					Bank[kPreset_BuzzyClean_Warm].prm[kInputBoost] = 1.00;
					Bank[kPreset_BuzzyClean_Warm].prm[kBright] = 0.00;
					Bank[kPreset_BuzzyClean_Warm].prm[kAmpChan] = 0.00;
					Bank[kPreset_BuzzyClean_Warm].prm[kNoiseFilter_On] = 0.00;

					Bank[kPreset_LightCrunch_Bright].prm[kInputBoost] = 0.00;
					Bank[kPreset_LightCrunch_Bright].prm[kBright] = 1.00;
					Bank[kPreset_LightCrunch_Bright].prm[kAmpChan] = 0.10;
					Bank[kPreset_LightCrunch_Bright].prm[kNoiseFilter_On] = 0.00;

					Bank[kPreset_LightCrunch_Warm].prm[kInputBoost] = 0.00;
					Bank[kPreset_LightCrunch_Warm].prm[kBright] = 0.00;
					Bank[kPreset_LightCrunch_Warm].prm[kAmpChan] = 0.10;
					Bank[kPreset_LightCrunch_Warm].prm[kNoiseFilter_On] = 0.00;

					Bank[kPreset_BoostedCrunch_Bright].prm[kInputBoost] = 1.00;
					Bank[kPreset_BoostedCrunch_Bright].prm[kBright] = 1.00;
					Bank[kPreset_BoostedCrunch_Bright].prm[kAmpChan] = 0.10;
					Bank[kPreset_BoostedCrunch_Bright].prm[kNoiseFilter_On] = 0.00;

					Bank[kPreset_BoostedCrunch_Warm].prm[kInputBoost] = 1.00;
					Bank[kPreset_BoostedCrunch_Warm].prm[kBright] = 0.00;
					Bank[kPreset_BoostedCrunch_Warm].prm[kAmpChan] = 0.10;
					Bank[kPreset_BoostedCrunch_Warm].prm[kNoiseFilter_On] = 0.00;

					Bank[kPreset_LightDrive_Bright].prm[kInputBoost] = 0.00;
					Bank[kPreset_LightDrive_Bright].prm[kBright] = 1.00;
					Bank[kPreset_LightDrive_Bright].prm[kAmpChan] = 0.20;
					Bank[kPreset_LightDrive_Bright].prm[kNoiseFilter_On] = 1.0;

					Bank[kPreset_LightDrive_Warm].prm[kInputBoost] = 0.00;
					Bank[kPreset_LightDrive_Warm].prm[kBright] = 0.00;
					Bank[kPreset_LightDrive_Warm].prm[kAmpChan] = 0.20;
					Bank[kPreset_LightDrive_Warm].prm[kNoiseFilter_On] = 1.0;

					Bank[kPreset_BoostedDrive_Bright].prm[kInputBoost] = 1.00;
					Bank[kPreset_BoostedDrive_Bright].prm[kBright] = 1.00;
					Bank[kPreset_BoostedDrive_Bright].prm[kAmpChan] = 0.20;
					Bank[kPreset_BoostedDrive_Bright].prm[kNoiseFilter_On] = 1.0;

					Bank[kPreset_BoostedDrive_Warm].prm[kInputBoost] = 1.00;
					Bank[kPreset_BoostedDrive_Warm].prm[kBright] = 0.00;
					Bank[kPreset_BoostedDrive_Warm].prm[kAmpChan] = 0.20;
					Bank[kPreset_BoostedDrive_Warm].prm[kNoiseFilter_On] = 1.0;

					Bank[kPreset_HiGain_Bright].prm[kInputBoost] = 0.00;
					Bank[kPreset_HiGain_Bright].prm[kBright] = 1.00;
					Bank[kPreset_HiGain_Bright].prm[kAmpChan] = 0.30;
					Bank[kPreset_HiGain_Bright].prm[kNoiseFilter_On] = 1.0;

					Bank[kPreset_HiGain_Warm].prm[kInputBoost] = 0.00;
					Bank[kPreset_HiGain_Warm].prm[kBright] = 0.00;
					Bank[kPreset_HiGain_Warm].prm[kAmpChan] = 0.30;
					Bank[kPreset_HiGain_Warm].prm[kNoiseFilter_On] = 1.0;

					Bank[kPreset_HeavyHiGain_Bright].prm[kInputBoost] = 1.00;
					Bank[kPreset_HeavyHiGain_Bright].prm[kBright] = 1.00;
					Bank[kPreset_HeavyHiGain_Bright].prm[kAmpChan] = 0.30;
					Bank[kPreset_HeavyHiGain_Bright].prm[kNoiseFilter_On] = 1.0;

					Bank[kPreset_HeavyHiGain_Warm].prm[kInputBoost] = 1.00;
					Bank[kPreset_HeavyHiGain_Warm].prm[kBright] = 0.00;
					Bank[kPreset_HeavyHiGain_Warm].prm[kAmpChan] = 0.30;
					Bank[kPreset_HeavyHiGain_Warm].prm[kNoiseFilter_On] = 1.0;
*/				}
				Control_Preset_Data& operator= (const Control_Preset_Data &other)
				{
					ControlLabels.Init();
					PresetLabels.Init();

					for(u32 x = 0; x < (u32) kPreset_MAX_COUNT; x++)
					{
						strncpy( PresetLabels.label[kPreset_Init].txt, other.PresetLabels.label[kPreset_Init].txt, 127 );

						for(u32 y = 0; y < (u32) kMax_Parameter_Count; y++)
						{
							Bank[x].prm[y] = other.Bank[x].prm[y];
						}
					}
				}
			};

			Reverb_MagmaTouch_Params();

			Reverb_MagmaTouch_Params(const ::ScorchCrafter::Base::Plug_ParameterList &other);

			virtual Reverb_MagmaTouch_Params& operator=(const ::ScorchCrafter::Base::Plug_ParameterList &other);

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
//!---  MagmaTouch Guitar Amplifier Head :: Audio Effect
//!---  --- Prototypes
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
		class SCRFT_EXPORT Reverb_MagmaTouch : public ::ScorchCrafter::Base::BasePlugin
		{
		public:
			Reverb_MagmaTouch();

			Reverb_MagmaTouch(const ::ScorchCrafter::Base::BasePlugin &other);

			virtual ~Reverb_MagmaTouch();

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
					_pi_f80( 3.14159265358979323846264338327950288419716939937510L )
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
					cutoff_hp = 7.5L * 2.0L / (f80) os_rate;
					cutoff_lp = 0.4999725L * (f80) smp_rate * 2.0L / (f80) os_rate;

//					res_hp = 1.3335214321633240256759317152953L;
					res_hp = 1.1885022274370184377301224648922L;

					k = 0.5L * res_hp * sinl( _pi_f80 * cutoff_hp );
					c1 = 0.5L * (1.0L - k) / (1.0L + k);
					c2 = (0.5L + c1) * cosl( _pi_f80 * cutoff_hp );
					c3 = (0.5L + c1 + c2 ) * 0.25L;

					a0_hp = 2.0L * c3;
					a1_hp = -4.0L * c3;
					a2_hp = 2.0L * c3;
					b1_hp = -2.0L * c2;
					b2_hp = 2.0L * c1;

					res_lp = 1.1885022274370184377301224648922L;

					k = 0.5L * res_lp * sinl( _pi_f80 * cutoff_lp );
					c1 = 0.5L * (1.0L - k) / (1.0L + k);
					c2 = (0.5L + c1) * cosl( _pi_f80 * cutoff_lp );
					c3 = (0.5L + c1 - c2) * 0.25L;

					a0_lp = 2.0L * c3;
					a1_lp = 4.0L * c3;
					a2_lp = 2.0L * c3;
					b1_lp = -2.0L * c2;
					b2_lp = 2.0L * c1;
				}
				inline void SetOverSamplingMultiplier(u32 inp_os_mult)
				{
					if ( inp_os_mult < 2 )
						inp_os_mult = 2;
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
					f64 fx_sp = inp;

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
					f64 fx_sp = inp;

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
					f64 fx_sp = inp;

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
					if ( sp_rate < 44100.0L )
						sp_rate = 44100.0L;

					if ( p_frequency > (sp_rate * 0.5L) )
						p_frequency = sp_rate * 0.5L;
					if ( p_frequency < 0.0000012L )
						p_frequency = 0.0000012L;

					const f80 t = expl( -2.0L * _pi_f80 * p_frequency / sp_rate );
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
					_pi_f80( 3.14159265358979323846264338327950288419716939937510L ),
					dn( (f64) powl( 10.L, -30.L ) ),
					p_frequency( 1.0L ),
					sp_rate( 44100.0L ),
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
					if ( sp_rate < 44100.0L )
						sp_rate = 44100.0L;

					if ( p_frequency > (sp_rate * 0.5L) )
						p_frequency = sp_rate * 0.5L;
					if ( p_frequency < 0.0000012L )
						p_frequency = 0.0000012L;

					const f80 t = expl( -2.0L * _pi_f80 * p_frequency / sp_rate );
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

					return spl_delay - buffer;
				}
				EQ_HP() :
					_pi_f80( 3.14159265358979323846264338327950288419716939937510L ),
					dn( (f64) powl( 10.L, -30.L ) ),
					p_frequency( 1.0L ),
					sp_rate( 44100.0L ),
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
					if ( sp_rate < 44100.0L )
						sp_rate = 44100.0L;

					if ( p_frequency > (sp_rate * 0.5L) )
						p_frequency = sp_rate * 0.5L;
					if ( p_frequency < 0.0000012L )
						p_frequency = 0.0000012L;

					const f80 t = expl( -2.0L * _pi_f80 * p_frequency / sp_rate );
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
					_pi_f80( 3.14159265358979323846264338327950288419716939937510L ),
					dn( (f64) powl( 10.L, -30.L ) ),
					p_frequency( 1.0L ),
					sp_rate( 44100.0L ),
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

				inline f64 c_internal_abs(const f64 &inp) const
				{
					return f64 (
									(inp >=  0.0) ?
										inp
									:
										-inp
								);
				}
				inline void Clear()
				{
					buffer = 0.0;
				}
				void SetFilterVars()
				{
					if ( sp_rate < 44100.0L )
						sp_rate = 44100.0L;

					if ( p_frequency_a > (sp_rate * 0.5L) )
						p_frequency_a = sp_rate * 0.5L;
					if ( p_frequency_a < 0.0000012L )
						p_frequency_a = 0.0000012L;

					if ( p_frequency_b > (sp_rate * 0.5L) )
						p_frequency_b = sp_rate * 0.5L;
					if ( p_frequency_b < 0.0000012L )
						p_frequency_b = 0.0000012L;

					f80 t = expl( -2.0L * _pi_f80 * p_frequency_a / sp_rate );
					fq0_a = f64 (1.0L - t);
					fq1_a = f64 (-t);

					t = expl( -2.0L * _pi_f80 * p_frequency_b / sp_rate );
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
					if ( c_internal_abs( inp ) >= c_internal_abs( buffer ) )
						buffer = (fq0_a * inp) - (fq1_a * buffer) + dn;
					else
						buffer = (fq0_b * inp) - (fq1_b * buffer) + dn;

					return buffer;
				}
				EQ_Dual_LP() :
					_pi_f80( 3.14159265358979323846264338327950288419716939937510L ),
					dn( (f64) powl( 10.L, -30.L ) ),
					p_frequency_a( 1.0L ),
					p_frequency_b( 1.0L ),
					sp_rate( 44100.0L ),
					buffer( 0.0 )
				{
					SetFilterVars();
				}
			}; // struct EQ_Dual_LP
			//! ----------------------------------------------------------------
			//! --- Reverb FX --
			//! ----------------------------------------------------------------
			struct SCRFT_EXPORT ReverbFX
			{
				const f80 _pi_f80;
				const f64 c_denorm;

				const s64 vi_0;
				const s64 vi_1;
				const s64 vi_2;
				const s64 vi_3;
				const s64 vi_4;
				const s64 vi_5;
				const s64 vi_6;
				const s64 vi_7;
				const s64 vi_8;
				const s64 vi_diff_min;
				const f80 diff_min_spacing_factor;
				const f80 damp_swell_freq0;
				const f80 damp_swell_freq1;
				const f80 damp_swell_ms;
				f64 sRate;
				f64 damp_freq0;
				f64 damp_freq1;
				f64 freq_HP;
				f64 freq_LP;

				f64 *hist_L;
				f64 *hist_R;
				f64 *preBuffer_L;
				f64 *preBuffer_R;
				f64 preBuffer_setting;
				f64 preBuffer_setting_max_ms;
				s64 preBuffer_max_size;
				s64 preBuffer_length;
				s64 hist_length;
				s64 max_echo;
				f80 maxLength_base;
				f64 maxLength;
				int diff_pulse_count;
				f64 inv_pulse_count;
				f64 diff_min_spacing;
				f64 diff_spacing;
				s64 diff_stride;
				f64 diff_base;
				s64 pos;
				s64 preBuffer_pos;

				f64 buff_L;
				f64 buff_R;
				f64 vol_buffer_L;
				f64 vol_buffer_R;

				f64 fx_strength;
				f64 cutback;

				f64 fSwell_a0;
				f64 fSwell_b0;
				f64 fSwell_a1;
				f64 fSwell_b1;
				f64 fDamp_a0;
				f64 fDamp_b0;
				f64 fDamp_a1;
				f64 fDamp_b1;

				f64 fHP_a;
				f64 fHP_b;
				f64 fLP_a;
				f64 fLP_b;

				f64 EqBuff_L[4];
				f64 EqBuff_R[4];

				f64 v_out_L, v_out_R;

				bool isReady;
				bool varsReady;
				bool sRateReady;

				inline f64 c_internal_abs(const f64 &inp) const
				{
					return f64 (
									(inp >=  0.0) ?
										inp
									:
										-inp
								);
				}
				inline f64 Avg(const f64 &inp_a, const f64 &inp_b, const f64 &skew_toward_b) const
				{
					return f64 (
									(inp_a * (1.0 - skew_toward_b)) +
									(inp_b * skew_toward_b)
								);
				}
				void SetFreqVars_VolRead()
				{
					const f80 x_val0 = (f80) expl( f80 (-2.0L * (f80) _pi_f80 * damp_swell_freq0 / (f80) sRate) );
					fSwell_a0 = f64 (f80 (1.0L - x_val0));
					fSwell_b0 = f64 (f80 (-x_val0));

					const f80 x_val1 = (f80) expl( f80 (-2.0L * (f80) _pi_f80 * damp_swell_freq1 / (f80) sRate) );
					fSwell_a1 = f64 (f80 (1.0L - x_val1));
					fSwell_b1 = f64 (f80 (-x_val1));
				};
				void SetFreqVars_Damp()
				{
					const f80 x_val0 = (f80) expl( f80 (-2.0L * (f80) _pi_f80 * (f80) damp_freq0 / (f80) sRate) );
					fDamp_a0 = f64 (f80 (1.0L - x_val0));
					fDamp_b0 = f64 (f80 (-x_val0));

					const f80 x_val1 = (f80) expl( f80 (-2.0L * (f80) _pi_f80 * (f80) damp_freq1 / (f80) sRate) );
					fDamp_a1 = f64 (f80 (1.0L - x_val1));
					fDamp_b1 = f64 (f80 (-x_val1));
				};
				void SetFreqVars_HP()
				{
					const f80 x_val = (f80) expl( f80 (-2.0L * (f80) _pi_f80 * (f80) freq_HP / (f80) sRate) );
					fHP_a = f64 (f80 (1.0L - x_val));
					fHP_b = f64 (f80 (-x_val));
				};
				void SetFreqVars_LP()
				{
					const f80 x_val = (f80) expl( f80 (-2.0L * (f80) _pi_f80 * (f80) freq_LP / (f80) sRate) );
					fLP_a = f64 (f80 (1.0L - x_val));
					fLP_b = f64 (f80 (-x_val));
				};
				void SetDiffRanges()
				{
					diff_spacing = f64 ( (f64) max_echo / (f64) diff_pulse_count );
					if ( diff_spacing < diff_min_spacing )
						diff_spacing = diff_min_spacing;

					diff_stride = s64 ( diff_spacing );

					if ( diff_stride < vi_2 )
						diff_stride = vi_2;

					pos = vi_0;
				};
				void SetPreDelayRange()
				{
					preBuffer_max_size = s64 (f80 ((f80) preBuffer_setting_max_ms * (f80) sRate * 0.00120L));

					if ( preBuffer_L )
						delete [] preBuffer_L;
					if ( preBuffer_R )
						delete [] preBuffer_R;

					preBuffer_L = new f64[preBuffer_max_size];
					preBuffer_R = new f64[preBuffer_max_size];
					for (s64 i = vi_0; (s64) i < preBuffer_max_size; i++)
					{
						preBuffer_L[i] = 0.0;
						preBuffer_R[i] = 0.0;
					}

					preBuffer_length = s64 ( f64 (preBuffer_setting * (f64) sRate / 1000.0) );
					if ( preBuffer_length >= preBuffer_max_size )
						preBuffer_length = s64 (preBuffer_max_size - vi_4);

					preBuffer_pos = vi_0;
				}
				void Init(const f64 maxLength_ms, const f64 strength, const int numDelays, const f64 pre_delay_max_length_ms, const f64 newSampleRate=44100.0)
				{
					fx_strength = f64 (strength);
					cutback = f64 (1.0 / f80 ( 1.0L + f80 (fx_strength * 2.0L) ));

					diff_pulse_count = (int) numDelays;
					if ( diff_pulse_count < 4 )
						diff_pulse_count = 4;
					if ( diff_pulse_count > 512 )
						diff_pulse_count = 512;

					inv_pulse_count = f64 (1.0 / diff_pulse_count);

					SetFreqVars_VolRead();
					SetFreqVars_Damp();

					ClearBuffers();

					pos = vi_0;

					maxLength_base = f80 (maxLength_ms);
					maxLength = f80 ((f80) maxLength_base + damp_swell_ms);

					hist_length = s64 ( f80 ((f80) sRate * (f80) maxLength / 1000.L) );
					max_echo = s64 (hist_length - vi_8);

					if ( hist_L )
						delete [] hist_L;
					if ( hist_R )
						delete [] hist_R;

					hist_L = new f64[hist_length];
					hist_R = new f64[hist_length];
					for (s64 i = vi_0; (s64) i < (s64) hist_length; i++)
					{
						hist_L[i] = 0.0;
						hist_R[i] = 0.0;
					}

					SetDiffRanges();

					SetFreqVars_HP();
					SetFreqVars_LP();

					preBuffer_setting_max_ms = (f64) pre_delay_max_length_ms;
					SetPreDelayRange();
					preBuffer_pos = vi_0;

					varsReady = true;

					if ( varsReady && sRateReady )
						isReady = true;

					SetNewSampleRate( newSampleRate );
				}
				bool CheckState(const f64 nRate,
								const f64 maxLength_ms,
								const f64 strength,
								const int numDelays,
								const f64 pre_delay_max_length_ms)
				{
					bool val = true;

					if ( !hist_L )
						val = false;
					if ( !hist_R )
						val = false;
					if ( !preBuffer_L )
						val = false;
					if ( !preBuffer_R )
						val = false;
					if ( !isReady )
						val = false;

					if ( val == true )
						return val;

					if ( hist_L )
						delete [] hist_L;
					if ( hist_R )
						delete [] hist_R;
					if ( preBuffer_L )
						delete [] preBuffer_L;
					if ( preBuffer_R )
						delete [] preBuffer_R;

					hist_L = 0;
					hist_R = 0;
					preBuffer_L = 0;
					preBuffer_R = 0;

					isReady = false;
					varsReady = false;
					sRateReady = false;

					sRate = nRate;

					Init( maxLength_ms, strength, numDelays, pre_delay_max_length_ms );
					SetNewSampleRate( nRate );

					return false;
				}
				void SetLength(const f64 newLength_ms)
				{
					diff_base = (f64) newLength_ms;

					pos = vi_0;

					SetDiffRanges();

					SetFreq_Damp( f64 (32000.0 / diff_base), f64 (1000.0 / diff_base) );

					ClearBuffers();
				}
				void SetNewNumberOfDelays(const s32 numDelays)
				{
					diff_pulse_count = (s32) numDelays;
					if ( diff_pulse_count < 4 )
						diff_pulse_count = 4;
					if ( diff_pulse_count > 512 )
						diff_pulse_count = 512;

					inv_pulse_count = f64 (1.0 / diff_pulse_count);

					SetDiffRanges();

					ClearBuffers();

					pos = vi_0;
				}
				void SetFreq_Damp(const f64 &newDampFreq_0, const f64 &newDampFreq_1)
				{
					damp_freq0 = (f64) newDampFreq_0;
					damp_freq1 = (f64) newDampFreq_1;

					SetFreqVars_Damp();
				}
				void SetFreq_HP(const f64 &newFreq)
				{
					freq_HP = (f64) newFreq;

					SetFreqVars_HP();
				}
				void SetFreq_LP(const f64 &newFreq)
				{
					freq_LP = (f64) newFreq;

					SetFreqVars_LP();
				}
				void SetPreDelay(const f64 &nDelay)
				{
					preBuffer_setting = (f64) nDelay;

					preBuffer_length = s64 ( f64 (preBuffer_setting * (f64) sRate / 1000.0) );
					if ( preBuffer_length >= preBuffer_max_size )
						preBuffer_length = s64 (preBuffer_max_size - vi_2);

					preBuffer_pos = vi_0;
				}
				void ClearBuffers()
				{
					buff_L = 0.0;
					buff_R = 0.0;
					vol_buffer_L = 0.0;
					vol_buffer_R = 0.0;
					v_out_L = 0.0;
					v_out_R = 0.0;

					EqBuff_L[0] = 0.0;
					EqBuff_L[1] = 0.0;
					EqBuff_L[2] = 0.0;
					EqBuff_L[3] = 0.0;
					EqBuff_R[0] = 0.0;
					EqBuff_R[1] = 0.0;
					EqBuff_R[2] = 0.0;
					EqBuff_R[3] = 0.0;
				}
				inline void Clear()
				{
					ClearBuffers();
				}
				void SetNewSampleRate(const f64 &nRate)
				{
					sRate = f64 (nRate);

					if ( sRate < 44100.0 )
						sRate = 44100.0;

					diff_min_spacing = f80 ( (f80) sRate * diff_min_spacing_factor );

					ClearBuffers();

					pos = vi_0;
					preBuffer_pos = vi_0;

					maxLength = f80 ((f80) maxLength_base + damp_swell_ms);

					hist_length = s64 ( f80 ((f80) sRate * (f80) maxLength / 1000.L) );
					max_echo = s64 (hist_length - vi_8);

					if ( hist_L )
						delete [] hist_L;
					if ( hist_R )
						delete [] hist_R;

					hist_L = new f64[hist_length];
					hist_R = new f64[hist_length];
					for (s64 i = vi_0; (s64) i < (s64) hist_length; i++)
					{
						hist_L[i] = 0.0;
						hist_R[i] = 0.0;
					}

					SetFreqVars_VolRead();
					SetFreqVars_Damp();

					SetDiffRanges();

					SetFreqVars_HP();
					SetFreqVars_LP();

					SetPreDelayRange();

					sRateReady = true;

					if ( varsReady && sRateReady )
						isReady = true;
				}
				inline void SetEqHP(const f64 &inp)
				{
					SetFreq_HP( inp );
				}
				inline void SetEqLP(const f64 &inp)
				{
					SetFreq_LP( inp );
				}
				inline void SetEqExtraPasses(const bool &inp)
				{
				}
				inline void SetReverbLength(const f64 &inp)
				{
					SetLength( inp );
				}
				inline void Run(f64 spl_L, f64 spl_R)
				{
					if ( !isReady )
						return;

					f64 v_in_L = (f64) spl_L;
					f64 v_in_R = (f64) spl_R;

					const f64 vol_hold_L = c_internal_abs( v_in_L );
					const f64 vol_hold_R = c_internal_abs( v_in_R );

					if ( vol_buffer_L < vol_hold_L )
						vol_buffer_L = c_internal_abs( f64 (f64 (fSwell_a0 * vol_hold_L) - f64 (fSwell_b0 * vol_buffer_L) + c_denorm) );
					else
						vol_buffer_L = c_internal_abs( f64 (f64 (fSwell_a1 * vol_hold_L) - f64 (fSwell_b1 * vol_buffer_L) + c_denorm) );
					if ( vol_buffer_R < vol_hold_R )
						vol_buffer_R = c_internal_abs( f64 (f64 (fSwell_a0 * vol_hold_R) - f64 (fSwell_b0 * vol_buffer_R) + c_denorm) );
					else
						vol_buffer_R = c_internal_abs( f64 (f64 (fSwell_a1 * vol_hold_R) - f64 (fSwell_b1 * vol_buffer_R) + c_denorm) );

					if ( buff_L < vol_buffer_L )
						buff_L = c_internal_abs( f64 (f64 (fDamp_a0 * vol_buffer_L) - f64 (fDamp_b0 * buff_L) + c_denorm) );
					else
						buff_L = c_internal_abs( f64 (f64 (fDamp_a1 * vol_buffer_L) - f64 (fDamp_b1 * buff_L) + c_denorm) );
					if ( buff_R < vol_buffer_R )
						buff_R = c_internal_abs( f64 (f64 (fDamp_a0 * vol_buffer_R) - f64 (fDamp_b0 * buff_R) + c_denorm) );
					else
						buff_R = c_internal_abs( f64 (f64 (fDamp_a1 * vol_buffer_R) - f64 (fDamp_b1 * buff_R) + c_denorm) );

					hist_L[pos] = f64 (v_in_L);
					hist_R[pos] = f64 (v_in_R);
					pos += vi_1;
					if (pos >= max_echo) pos = vi_0;

					s64 pos_read = pos;
					s64 stride_count = vi_0;
					f64 out_L = 0.0;
					f64 out_R = 0.0;
					f64 fade_count = 0.0;
					for ( int pulse = 0; pulse < diff_pulse_count; pulse += 2 )
					{
						pos_read -= diff_stride;
						if ( pos_read < vi_0 )
							pos_read += max_echo;
						if ( pos_read >= max_echo )
							pos_read = max_echo - vi_1;

						stride_count += diff_stride;
						if ( stride_count >= max_echo )
							break;

						const f64 pos_read_val_L = hist_L[pos_read];

						pos_read -= diff_stride;
						if ( pos_read < vi_0 )
							pos_read += max_echo;
						if ( pos_read >= max_echo )
							pos_read = max_echo - vi_1;

						stride_count += diff_stride;
						if ( stride_count >= max_echo )
							break;

						const f64 pos_read_val_R = hist_R[pos_read];

						fade_count += inv_pulse_count + inv_pulse_count;
						const f64 fade_cut = Avg( 1.0, inv_pulse_count, fade_count );

						const f64 x_diff_L = f64 (fx_strength * buff_L * f64 (pos_read_val_L - v_in_L));
						const f64 x_diff_R = f64 (fx_strength * buff_R * f64 (pos_read_val_R - v_in_R));

						out_L = f64 ( out_L + f64 (cutback * f64 (v_in_L - x_diff_L) * fade_cut) );
						out_R = f64 ( out_R + f64 (cutback * f64 (v_in_R - x_diff_R) * fade_cut) );
					}

					v_out_L = (out_L - v_in_L);
					v_out_R = (out_R - v_in_R);

					EqBuff_L[0] = f64 ( f64 (f64 (fHP_a * v_out_L) - f64 (fHP_b * EqBuff_L[0]) + c_denorm) );
					EqBuff_R[0] = f64 ( f64 (f64 (fHP_a * v_out_R) - f64 (fHP_b * EqBuff_R[0]) + c_denorm) );
					v_out_L -= EqBuff_L[0];
					v_out_R -= EqBuff_R[0];
					EqBuff_L[1] = f64 ( f64 (f64 (fHP_a * v_out_L) - f64 (fHP_b * EqBuff_L[1]) + c_denorm) );
					EqBuff_R[1] = f64 ( f64 (f64 (fHP_a * v_out_R) - f64 (fHP_b * EqBuff_R[1]) + c_denorm) );
					v_out_L -= EqBuff_L[1];
					v_out_R -= EqBuff_R[1];

					EqBuff_L[2] = f64 ( f64 (f64 (fLP_a * v_out_L) - f64 (fLP_b * EqBuff_L[2]) + c_denorm) );
					EqBuff_R[2] = f64 ( f64 (f64 (fLP_a * v_out_R) - f64 (fLP_b * EqBuff_R[2]) + c_denorm) );
					v_out_L = EqBuff_L[2];
					v_out_R = EqBuff_R[2];
					EqBuff_L[3] = f64 ( f64 (f64 (fLP_a * v_out_L) - f64 (fLP_b * EqBuff_L[3]) + c_denorm) );
					EqBuff_R[3] = f64 ( f64 (f64 (fLP_a * v_out_R) - f64 (fLP_b * EqBuff_R[3]) + c_denorm) );
					v_out_L = EqBuff_L[3];
					v_out_R = EqBuff_R[3];

					if ( preBuffer_length > vi_0 )
					{
						preBuffer_L[preBuffer_pos] = (f64) v_out_L;
						preBuffer_R[preBuffer_pos] = (f64) v_out_R;
						preBuffer_pos += vi_1;
						if ( preBuffer_pos >= preBuffer_length )
							preBuffer_pos = vi_0;
						v_out_L = (f64) preBuffer_L[preBuffer_pos];
						v_out_R = (f64) preBuffer_R[preBuffer_pos];
					}
				}
				ReverbFX() :
					_pi_f80( 3.14159265358979323846264338327950288419716939937510L ),
					c_denorm( (f64) powl( 10.L, -30.L ) ),
					vi_0( (s64) 0LL ),
					vi_1( (s64) 1LL ),
					vi_2( (s64) 2LL ),
					vi_3( (s64) 3LL ),
					vi_4( (s64) 4LL ),
					vi_5( (s64) 5LL ),
					vi_6( (s64) 6LL ),
					vi_7( (s64) 7LL ),
					vi_8( (s64) 8LL ),
					vi_diff_min( (s64) 32LL ),
					diff_min_spacing_factor( 0.021L ),
					damp_swell_freq0( 39.0L ),
					damp_swell_freq1( 12.0L ),
					damp_swell_ms( 120.0L ),
					sRate( 44100.0 ),
					damp_freq0( 1.2 ),
					damp_freq1( 1.2 ),
					freq_HP( 90.0 ),
					freq_LP( 7200.0 ),
					hist_L( 0 ),
					hist_R( 0 ),
					preBuffer_L( 0 ),
					preBuffer_R( 0 ),
					preBuffer_setting( 0.0L ),
					preBuffer_setting_max_ms( 120.0L ),
					preBuffer_max_size( (s64) 900LL ),
					preBuffer_length( (s64) 0LL ),
					hist_length( (s64) 512LL ),
					diff_pulse_count( 8 ),
					max_echo( (s64) 500LL ),
					maxLength_base( 750.0L ),
					maxLength( 750.0L ),
					diff_base( 120.0L ),
					pos( (s64) 0LL ),
					preBuffer_pos( (s64) 0LL ),
					fx_strength( 12.0 ),
					cutback( f64 (1.L / 6.L) ),
					v_out_L( 0.0 ),
					v_out_R( 0.0 ),
					isReady( false ),
					varsReady( false ),
					sRateReady( false )
				{
					cutback = f64 (1.0 / f80 ( 1.0 + f80 (fx_strength * 2.0) ));

					inv_pulse_count = f64 (1.0 / diff_pulse_count);

					diff_min_spacing = f80 ( (f80) sRate * diff_min_spacing_factor );

					maxLength = f80 ((f80) maxLength_base + damp_swell_ms);

					hist_length = s64 ( f80 ((f80) sRate * (f80) maxLength / 1000.L) );
					max_echo = s64 (hist_length - vi_8);

					if ( hist_L )
						delete [] hist_L;
					if ( hist_R )
						delete [] hist_R;

					hist_L = new f64[hist_length];
					hist_R = new f64[hist_length];
					for (s64 i = vi_0; (s64) i < (s64) hist_length; i++)
					{
						hist_L[i] = 0.0;
						hist_R[i] = 0.0;
					}

					preBuffer_max_size = s64 (f80 ((f80) preBuffer_setting_max_ms * (f80) sRate * 0.00120L));

					if ( preBuffer_L )
						delete [] preBuffer_L;
					if ( preBuffer_R )
						delete [] preBuffer_R;

					preBuffer_L = new f64[preBuffer_max_size];
					preBuffer_R = new f64[preBuffer_max_size];
					for (s64 i = vi_0; (s64) i < (s64) preBuffer_max_size; i++)
					{
						preBuffer_L[i] = 0.0;
						preBuffer_R[i] = 0.0;
					}

					SetPreDelayRange();

					SetDiffRanges();
					SetFreqVars_VolRead();
					SetFreqVars_Damp();

					ClearBuffers();

					SetFreqVars_HP();
					SetFreqVars_LP();
				}
				~ReverbFX()
				{
					if ( hist_L )
						delete [] hist_L;
					if ( hist_R )
						delete [] hist_R;
					hist_L = 0;
					hist_R = 0;

					if ( preBuffer_L )
						delete [] preBuffer_L;
					if ( preBuffer_R )
						delete [] preBuffer_R;
					preBuffer_L = 0;
					preBuffer_R = 0;
				}
			}; // struct ReverbFX
			//! ----------------------------------------------------------------
			//! --- Reverb Audio FX --
			//! ----------------------------------------------------------------
			class SCRFT_EXPORT ReverbAudioFX
			{
			private:
				const f80 _pi_f80;
				const f80 _pi_f64;
				const f64 dn;
				const f64 sp_rate_max;
				f64 sp_rate;

				f64 fq_HP, fq_LP;
				bool fq_doublePass;
				f64 fqa_HP, fqb_HP;
				f64 fqa_LP, fqb_LP;
				f64 buf0_HP, buf1_HP, buf2_HP, buf3_HP;
				f64 buf0_LP, buf1_LP, buf2_LP, buf3_LP;

				f64 damping_auto, damping_prm;

				f64 reverb_length, reverb_preDelay;
				f64 reverb_length_min, reverb_length_max, reverb_preDelay_max;

				u32 pos_reverb;
				u32 pos_reverb_max;
				u32 pos_reverb_size;
				u32 pos_preDelay;
				u32 pos_preDelay_max;
				u32 pos_preDelay_size;

				f64 reverb_step_size_ms;
				f64 reverb_step_size;
				u32 reverb_step_u32;

				f64* buffer_reverb_L;
				f64* buffer_reverb_R;
				f64* buffer_pre_L;
				f64* buffer_pre_R;

				f64 spl_out_L, spl_out_R;

				inline f64 c_internal_abs(const f64 &inp) const
				{
					return f64 ( (inp >=  0.0) ? inp : -inp );
				}
				inline f64 c_internal_clamp(const f64 &inp, const f64 &inp_min, const f64 &inp_max) const
				{
					return f64 ( (inp >= inp_max) ? inp_max : ( (inp <= inp_min) ? inp_min : inp ) );
				}
				inline f64 Avg(const f64 &inp_a, const f64 &inp_b, const f64 &skew_toward_b) const
				{
					return f64 ( (inp_a * (1.0 - skew_toward_b)) + (inp_b * skew_toward_b) );
				}
				inline u32 GetSizeFromMilliSeconds_u32(const f64 &inp_ms) const
				{
					return u32 ( f64 ((f64) inp_ms * 0.001 * sp_rate) );
				}
				inline void CalculateAutoDamping()
				{
					if ( (pos_reverb_max > 0u) && ((f64) pos_reverb_max > reverb_step_size) )
						damping_auto = -1.0 + f64 (reverb_step_size / (f64) pos_reverb_max);
					else
						damping_auto = -1.0;
				}
				inline void CalculateReverbLength()
				{
					pos_reverb_max = GetSizeFromMilliSeconds_u32(
							c_internal_clamp( reverb_length, reverb_length_min, reverb_length_max ) );

					if ( pos_reverb_max < 2u )
						pos_reverb_max = 2u;

					if ( pos_reverb_max > pos_reverb_size )
						pos_reverb_max = pos_reverb_size;

					if ( pos_reverb >= pos_reverb_max )
						pos_reverb = 0u;
				}
				inline void CalculateReverbPreDelay()
				{
					pos_preDelay_max = GetSizeFromMilliSeconds_u32(
							c_internal_clamp( reverb_preDelay, 0.0, reverb_preDelay_max ) );

					if ( pos_preDelay_max > pos_preDelay_size )
						pos_preDelay_max = pos_preDelay_size;

					if ( pos_preDelay >= pos_preDelay_max )
						pos_preDelay = 0u;
				}
				inline void CalculateReverbStepSize()
				{
					reverb_step_size = reverb_step_size_ms * 0.001 * sp_rate;
					reverb_step_u32 = (u32) reverb_step_size;

					if ( reverb_step_u32 < 1u )
						reverb_step_u32 = 1u;
					if ( reverb_step_u32 >= pos_reverb_max )
						reverb_step_u32 = pos_reverb_max - 1u;
				}
				inline void CalculateEqHP()
				{
					const f64 t = (f64) exp( -2.0 * _pi_f64 * fq_HP / sp_rate );
					fqa_HP = 1.0 - t;
					fqb_HP = -t;
				}
				inline void CalculateEqLP()
				{
					const f64 t = (f64) exp( -2.0 * _pi_f64 * fq_LP / sp_rate );
					fqa_LP = 1.0 - t;
					fqb_LP = -t;
				}

			public:
				inline void Clear()
				{
					buf0_HP = 0.0; buf1_HP = 0.0; buf2_HP = 0.0; buf3_HP = 0.0;
					buf0_LP = 0.0; buf1_LP = 0.0; buf2_LP = 0.0; buf3_LP = 0.0;

					spl_out_L = 0.0;
					spl_out_R = 0.0;
				}
				inline void SetEqHP(const f64 &inp)
				{
					fq_HP = (f64) inp;

					CalculateEqHP();
				}
				inline void SetEqLP(const f64 &inp)
				{
					fq_LP = (f64) inp;

					CalculateEqLP();
				}
				inline void SetDampingLevel(const f64 &inp)
				{
					damping_prm = f64 ( 	( (f64) inp < 0.0 ) ?
												1.00 :
											( (f64) inp > 1.0 ) ?
												0.25 :
											1.0 - ((f64) inp * 0.75)	);
				}
				inline void SetEqExtraPasses(const bool &inp)
				{
					fq_doublePass = (bool) inp;
				}
				inline void SetReverbLength(const f64 &inp)
				{
					reverb_length = (f64) inp;

					CalculateReverbLength();
					CalculateReverbStepSize();
					CalculateAutoDamping();
				}
				inline void SetPreDelay(const f64 &inp)
				{
					reverb_preDelay = (f64) inp;

					CalculateReverbPreDelay();
				}
				inline void SetReverbStepSize(const f64 &inp)
				{
					reverb_step_size_ms = c_internal_clamp( (f64) inp, 1.0, 1200.0 );

					CalculateReverbLength();
					CalculateReverbStepSize();
					CalculateAutoDamping();
				}
				inline void Run(f64 &spl_L, f64 &spl_R)
				{
					if ( (!buffer_reverb_L) || (!buffer_reverb_R) || (!buffer_pre_L) || (!buffer_pre_R) )
						return;

					f64 spl_fx_L = (f64) spl_L;
					f64 spl_fx_R = (f64) spl_R;

					spl_fx_L -= ( buf0_HP = (fqa_HP*spl_fx_L) - (fqb_HP*buf0_HP) + dn );
					spl_fx_R -= ( buf1_HP = (fqa_HP*spl_fx_R) - (fqb_HP*buf1_HP) + dn );
					spl_fx_L =  ( buf0_LP = (fqa_LP*spl_fx_L) - (fqb_LP*buf0_LP) + dn );
					spl_fx_R =  ( buf1_LP = (fqa_LP*spl_fx_R) - (fqb_LP*buf1_LP) + dn );

					u32 pos_count = pos_reverb;

					buffer_reverb_L[pos_reverb] = spl_fx_L;
					buffer_reverb_R[pos_reverb] = spl_fx_R;
					pos_reverb += 1u;
					if ( pos_reverb >= pos_reverb_max )
						pos_reverb = 0u;

					f64 damping = 1.0;
					if ( reverb_step_u32 < pos_reverb_max )
					{
						spl_fx_L = 0.0;
						spl_fx_R = 0.0;

						for ( u32 cnt = 0u; cnt < pos_reverb_max; cnt += reverb_step_u32 )
						{
							if ( pos_count >= reverb_step_u32 )
								pos_count -= reverb_step_u32;
							else
								pos_count = pos_reverb_max - (reverb_step_u32 - pos_count);

							const f64 spl_accum_L = buffer_reverb_L[pos_count] * damping;
							const f64 spl_accum_R = buffer_reverb_R[pos_count] * damping;
							spl_fx_L += spl_accum_L + (spl_accum_R * (1.0 - c_internal_abs(damping)));
							spl_fx_R += spl_accum_R + (spl_accum_L * (1.0 - c_internal_abs(damping)));

							damping *= damping_auto * damping_prm;
						}
					}

					if ( fq_doublePass )
					{
						spl_fx_L -= ( buf2_HP = (fqa_HP*spl_fx_L) - (fqb_HP*buf2_HP) + dn );
						spl_fx_R -= ( buf3_HP = (fqa_HP*spl_fx_R) - (fqb_HP*buf3_HP) + dn );
						spl_fx_L =  ( buf2_LP = (fqa_LP*spl_fx_L) - (fqb_LP*buf2_LP) + dn );
						spl_fx_R =  ( buf3_LP = (fqa_LP*spl_fx_R) - (fqb_LP*buf3_LP) + dn );
					}

					spl_out_L = spl_fx_L;
					spl_out_R = spl_fx_R;

					if ( pos_preDelay_max > 0u )
					{
						buffer_pre_L[pos_preDelay] = spl_out_L;
						buffer_pre_R[pos_preDelay] = spl_out_R;

						pos_preDelay += 1u;
						if ( pos_preDelay >= pos_preDelay_max )
							pos_preDelay = 0u;

						if ( pos_preDelay == 0u )
						{
							spl_out_L = buffer_pre_L[pos_preDelay_max - 1u];
							spl_out_R = buffer_pre_R[pos_preDelay_max - 1u];
						} else
						{
							spl_out_L = buffer_pre_L[pos_preDelay];
							spl_out_R = buffer_pre_R[pos_preDelay];
						}
					}

					spl_L = spl_out_L;
					spl_R = spl_out_R;
				}
				inline void GetOutputs(f64 &spl_L, f64 &spl_R)
				{
					spl_L = spl_out_L;
					spl_R = spl_out_R;
				}

			private:
				void InitBufferArrays()
				{
					if ( buffer_reverb_L )
						delete [] buffer_reverb_L;
					if ( buffer_reverb_R )
						delete [] buffer_reverb_R;
					if ( buffer_pre_L )
						delete [] buffer_pre_L;
					if ( buffer_pre_R )
						delete [] buffer_pre_R;

					buffer_reverb_L = 0;
					buffer_reverb_R = 0;
					buffer_pre_L = 0;
					buffer_pre_R = 0;

					pos_reverb_size = GetSizeFromMilliSeconds_u32( reverb_length_max ) + 16u;
					pos_preDelay_size = GetSizeFromMilliSeconds_u32( reverb_preDelay_max ) + 16u;

					CalculateReverbLength();
					CalculateReverbStepSize();
					CalculateAutoDamping();
					CalculateReverbPreDelay();

					Clear();

					if ( sp_rate < 40000.0 )
						return;

					buffer_reverb_L = new f64[pos_reverb_size];
					buffer_reverb_R = new f64[pos_reverb_size];
					buffer_pre_L = new f64[pos_preDelay_size];
					buffer_pre_R = new f64[pos_preDelay_size];
					for ( u32 cnt = 0u; cnt < pos_reverb_size; cnt++ )
					{
						buffer_reverb_L[cnt] = 0.0;
						buffer_reverb_R[cnt] = 0.0;
					}
					for ( u32 cnt = 0u; cnt < pos_preDelay_size; cnt++ )
					{
						buffer_pre_L[cnt] = 0.0;
						buffer_pre_R[cnt] = 0.0;
					}
				}

			public:
				void SetSampleRate(const f64 nRate)
				{
					sp_rate = c_internal_clamp( (f64) nRate, 44100.0, sp_rate_max );

					CalculateEqHP();
					CalculateEqLP();

					InitBufferArrays();
				}
				void Init(const f64 reverbLength, const f64 reverbPreDelay, const f64 reverbStepSize)
				{
					reverb_length_max = c_internal_clamp( reverbLength, reverb_length_min, 16000.0 );
					reverb_preDelay_max = c_internal_clamp( reverbPreDelay, 1.0, 16000.0 );
					reverb_step_size_ms = c_internal_clamp( reverbStepSize, 0.01, 16000.0 );

					InitBufferArrays();
				}
				void Init()
				{
					sp_rate = c_internal_clamp( (f64) sp_rate, 44100.0, sp_rate_max );

					reverb_length_max = c_internal_clamp( reverb_length_max, reverb_length_min, 16000.0 );
					reverb_preDelay_max = c_internal_clamp( reverb_preDelay_max, 1.0, 16000.0 );
					reverb_step_size_ms = c_internal_clamp( reverb_step_size_ms, 0.01, 16000.0 );

					InitBufferArrays();
				}
				ReverbAudioFX() :
					_pi_f80( (f80) 3.14159265358979323846264338327950288419716939937510L ),
					_pi_f64( (f64) 3.14159265358979323846264338327950288419716939937510 ),
					dn( f64 ((f80) powl( (f80) 10.L, (f80) -30.L )) ),
					sp_rate_max( 12288000.0 ),
					sp_rate( 44100.0 ),
					fq_HP( 12.0 ),
					fq_LP( 22000.0 ),
					fq_doublePass( false ),
					fqa_HP( 0.5 ), fqb_HP( 0.5 ),
					fqa_LP( 0.5 ), fqb_LP( 0.5 ),
					damping_auto( -0.5 ),
					damping_prm( 0.5 ),
					reverb_length( 100.0 ),
					reverb_preDelay( 0.0 ),
					reverb_length_min( 50.0 ),
					reverb_length_max( 1000.0 ),
					reverb_preDelay_max( 120.0 ),
					pos_reverb( 0u ),
					pos_reverb_max( 5u ),
					pos_reverb_size( 10u ),
					pos_preDelay( 0u ),
					pos_preDelay_max( 0u ),
					pos_preDelay_size( 10u ),
					reverb_step_size_ms( 31.25 ),
					reverb_step_size( 32.0 ),
					reverb_step_u32( 32u ),
					buffer_reverb_L( 0 ), buffer_reverb_R( 0 ),
					buffer_pre_L( 0 ), buffer_pre_R( 0 ),
					spl_out_L( 0.0 ), spl_out_R( 0.0 )
				{}
				~ReverbAudioFX()
				{
					if ( buffer_reverb_L )
						delete [] buffer_reverb_L;
					if ( buffer_reverb_R )
						delete [] buffer_reverb_R;
					if ( buffer_pre_L )
						delete [] buffer_pre_L;
					if ( buffer_pre_R )
						delete [] buffer_pre_R;

					buffer_reverb_L = 0;
					buffer_reverb_R = 0;
					buffer_pre_L = 0;
					buffer_pre_R = 0;
				}
			}; // struct ReverbAudioFX
			//! ----------------------------------------------------------------
			//! --- Primary FX --
			//! ----------------------------------------------------------------
			struct SCRFT_EXPORT Channel_Audio_Effect
			{
				const f80 _pi_f80;
				const f64 dn;
				const f64 reverb_prm_preDelay_min;
				const f64 reverb_prm_preDelay_max;
				const f64 reverb_prm_Length_min;
				const f64 reverb_prm_Length_max;
				const f64 reverb_prm_EQ_HP_min;
				const f64 reverb_prm_EQ_HP_max;
				const f64 reverb_prm_EQ_LP_min;
				const f64 reverb_prm_EQ_LP_max;

				// Sample and rate data
				f64 spl_L[64];
				f64 spl_R[64];
				f64 spl_out_L, spl_out_R;
				f64 spRate;
				f64 osRate;
				u32 oversampling_factor;
				f64 spl_boost_factor;
				f64 spl_div_factor;

				// Post-DownSampling Filters to trim off excess (very low) frequencies
				EQ_HP f0_trim, f1_trim, f2_trim, f3_trim;

				// Parameters
				f64 p_mix;
				f64 p_preDelay;
				f64 p_preDelayFine;
				f64 p_reverbLength;
				f64 p_reverbLengthFine;
				bool p_bypass;
				f64 prm_preDelay;
				f64 prm_reverbLength;
				f64 prm_Eq_HP;
				f64 prm_Eq_LP;

				// FX Components
				ReverbAudioFX Reverb_FX;
				OverSampling_Eq_Filter OS_Filter_up[2];
				OverSampling_Eq_Filter OS_Filter_dn[2];

				inline f64 c_internal_abs(const f64 &inp) const
				{
					return f64 (
									(inp >=  0.0) ?
										inp
									:
										-inp
								);
				}
				inline f64 Avg(const f64 &inp_a, const f64 &inp_b, const f64 &skew_toward_b) const
				{
					return f64 (
									(inp_a * (1.0 - skew_toward_b)) +
									(inp_b * skew_toward_b)
								);
				}
				inline void Clear()
				{
					for (u32 i = 0u; i < 64u; i++)
					{
						spl_L[i] = 0.0;
						spl_R[i] = 0.0;
					}

					spl_out_L = 0.0;
					spl_out_R = 0.0;

					f0_trim.Clear(); f1_trim.Clear(); f2_trim.Clear(); f3_trim.Clear();

					Reverb_FX.Clear();
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
					f0_trim.SetSampleRate( spRate );
					f1_trim.SetSampleRate( spRate );
					f2_trim.SetSampleRate( spRate );
					f3_trim.SetSampleRate( spRate );
					f0_trim.SetPassRate( 12.0 );
					f1_trim.SetPassRate( 12.0 );
					f2_trim.SetPassRate( 12.0 );
					f3_trim.SetPassRate( 12.0 );

					OS_Filter_up[0].SetSampleRate( spRate );
					OS_Filter_dn[0].SetSampleRate( spRate );
					OS_Filter_up[0].SetOverSamplingMultiplier( oversampling_factor );
					OS_Filter_dn[0].SetOverSamplingMultiplier( oversampling_factor );
					OS_Filter_up[1].SetSampleRate( spRate );
					OS_Filter_dn[1].SetSampleRate( spRate );
					OS_Filter_up[1].SetOverSamplingMultiplier( oversampling_factor );
					OS_Filter_dn[1].SetOverSamplingMultiplier( oversampling_factor );

					Reverb_FX.SetSampleRate( osRate );

					Clear();
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
				inline void SetMix(const f64 inp)
				{
					p_mix = inp;
				}
				inline void SetEqHP(const f64 inp)
				{
					prm_Eq_HP = inp;

					Reverb_FX.SetEqHP( Avg( reverb_prm_EQ_HP_min, reverb_prm_EQ_HP_max, prm_Eq_HP ) );
				}
				inline void SetEqLP(const f64 inp)
				{
					prm_Eq_LP = inp;

					Reverb_FX.SetEqLP( Avg( reverb_prm_EQ_LP_min, reverb_prm_EQ_LP_max, prm_Eq_LP ) );
				}
				inline void SetEqExtraPasses(const bool inp)
				{
					Reverb_FX.SetEqExtraPasses( inp );
				}
				inline void SetPreDelay(const f64 inp)
				{
					p_preDelay = inp;

					prm_preDelay = ( (p_preDelay * 0.99) + (p_preDelayFine * 0.01)  );

					Reverb_FX.SetPreDelay( Avg( reverb_prm_preDelay_min, reverb_prm_preDelay_max, prm_preDelay ) );
				}
				inline void SetPreDelayFine(const f64 inp)
				{
					p_preDelayFine = inp;

					prm_preDelay = ( (p_preDelay * 0.99) + (p_preDelayFine * 0.01)  );

					Reverb_FX.SetPreDelay( Avg( reverb_prm_preDelay_min, reverb_prm_preDelay_max, prm_preDelay ) );
				}
				inline void SetReverbLength(const f64 inp)
				{
					p_reverbLength = inp;

					prm_reverbLength = ( (p_reverbLength * 0.99) + (p_reverbLengthFine * 0.01)  );

					Reverb_FX.SetReverbLength( Avg( reverb_prm_Length_min, reverb_prm_Length_max, prm_reverbLength ) );
				}
				inline void SetReverbLengthFine(const f64 inp)
				{
					p_reverbLengthFine = inp;

					prm_reverbLength = ( (p_reverbLength * 0.99) + (p_reverbLengthFine * 0.01)  );

					Reverb_FX.SetReverbLength( Avg( reverb_prm_Length_min, reverb_prm_Length_max, prm_reverbLength ) );
				}
				inline void SetBypass(const bool inp)
				{
					p_bypass = inp;
				}
				inline void Run(const f64 inp_L, const f64 inp_R)
				{
					if ( p_bypass )
					{
						spl_out_L = inp_L;
						spl_out_R = inp_R;

						return;
					}

					spl_L[0] = inp_L;
					spl_R[0] = inp_R;

					for (u32 i = 1u; i < oversampling_factor; i++)
					{
						spl_L[i] = dn;
						spl_R[i] = dn;
					}

					for (u32 i = 0u; i < oversampling_factor; i++)
					{
						f64 fx_spl_L = spl_L[i];
						f64 fx_spl_R = spl_R[i];

						fx_spl_L = OS_Filter_up[0].Run_LP( fx_spl_L );
						fx_spl_R = OS_Filter_up[1].Run_LP( fx_spl_R );
						fx_spl_L *= spl_boost_factor;
						fx_spl_R *= spl_boost_factor;

						const f64 fx_spl_L_dry = fx_spl_L * (1.0 - p_mix);
						const f64 fx_spl_R_dry = fx_spl_R * (1.0 - p_mix);

						Reverb_FX.Run( fx_spl_L, fx_spl_R );
//						fx_spl_L = Reverb_FX.v_out_L;
//						fx_spl_R = Reverb_FX.v_out_R;

						fx_spl_L *= p_mix;
						fx_spl_R *= p_mix;
						fx_spl_L += fx_spl_L_dry;
						fx_spl_R += fx_spl_R_dry;

						fx_spl_L = ( fx_spl_L < -7.5 ) ? -7.5 : ( fx_spl_L > 7.5 ) ? 7.5 : fx_spl_L;
						fx_spl_R = ( fx_spl_R < -7.5 ) ? -7.5 : ( fx_spl_R > 7.5 ) ? 7.5 : fx_spl_R;

						spl_L[i] = OS_Filter_dn[0].Run_LP( fx_spl_L );
						spl_R[i] = OS_Filter_dn[1].Run_LP( fx_spl_R );
					}

					f64 spl_sum_L = 0.0;
					f64 spl_sum_R = 0.0;
					for (u32 i = 0u; i < oversampling_factor; i++)
					{
						spl_sum_L += spl_L[i];
						spl_sum_R += spl_R[i];
					}
					spl_sum_L *= spl_div_factor;
					spl_sum_R *= spl_div_factor;

					spl_sum_L = f0_trim.Run( spl_sum_L );
					spl_sum_L = f1_trim.Run( spl_sum_L );
					spl_sum_R = f2_trim.Run( spl_sum_R );
					spl_sum_R = f3_trim.Run( spl_sum_R );

					spl_out_L = spl_sum_L;
					spl_out_R = spl_sum_R;
				}
				inline void Run(const f64 inp)
				{
					Run( inp, inp );
				}
				Channel_Audio_Effect() :
					_pi_f80( (f80) 3.14159265358979323846264338327950288419716939937510L ),
					dn( f64 ((f80) powl( (f80) 10.L, (f80) -30.L )) ),
					reverb_prm_preDelay_min( 0.0 ),
					reverb_prm_preDelay_max( 320.0 ),
					reverb_prm_Length_min( 100.0 ),
					reverb_prm_Length_max( 5000.0 ),
					reverb_prm_EQ_HP_min( 30.0 ),
					reverb_prm_EQ_HP_max( 900.0 ),
					reverb_prm_EQ_LP_min( 3000.0 ),
					reverb_prm_EQ_LP_max( 20000.0 ),
					p_mix( 0.5 ),
					p_preDelay( 0.0 ),
					p_preDelayFine( 0.0 ),
					p_reverbLength( 0.0 ),
					p_reverbLengthFine( 0.0 ),
					p_bypass( false ),
					prm_preDelay( 0.0 ),
					prm_reverbLength( 0.0 ),
					prm_Eq_HP( 0.0 ),
					prm_Eq_LP( 1.0 )
				{
					for (u32 i = 0u; i < 64u; i++)
					{
						spl_L[i] = 0.0;
						spl_R[i] = 0.0;
					}
/*
					Reverb_FX.Init( 5110.0, 120.0, 32, 327.0 );
					Reverb_FX.SetPreDelay( Avg( reverb_prm_preDelay_min, reverb_prm_preDelay_max, prm_preDelay ) );
					Reverb_FX.SetReverbLength( Avg( reverb_prm_Length_min, reverb_prm_Length_max, prm_reverbLength ) );
					Reverb_FX.SetEqHP( Avg( reverb_prm_EQ_HP_min, reverb_prm_EQ_HP_max, prm_Eq_HP ) );
					Reverb_FX.SetEqLP( Avg( reverb_prm_EQ_LP_min, reverb_prm_EQ_LP_max, prm_Eq_LP ) );
*/
					Reverb_FX.Init( 5020.0, 331.0, 75.0 );

					SetAndCheckSampleRates();

					Reverb_FX.SetDampingLevel( 0.5 );
					Reverb_FX.SetReverbStepSize( 75.0 );
					Reverb_FX.SetPreDelay( Avg( reverb_prm_preDelay_min, reverb_prm_preDelay_max, prm_preDelay ) );
					Reverb_FX.SetReverbLength( Avg( reverb_prm_Length_min, reverb_prm_Length_max, prm_reverbLength ) );
					Reverb_FX.SetEqHP( Avg( reverb_prm_EQ_HP_min, reverb_prm_EQ_HP_max, prm_Eq_HP ) );
					Reverb_FX.SetEqLP( Avg( reverb_prm_EQ_LP_min, reverb_prm_EQ_LP_max, prm_Eq_LP ) );
				}
			}; // struct Channel_Audio_Effect

			//! ----------------------------------------------------------------
			f64 prm[Reverb_MagmaTouch_Params::kMax_Parameter_Count];
			bool prm_dirty[Reverb_MagmaTouch_Params::kMax_Parameter_Count];

			Channel_Audio_Effect FX0;

			inline void SetOverSamplingMultiplier(const u32 &inp, const bool inp_online);
			inline void CheckOverSamplingSettings();
		}; // class Reverb_MagmaTouch
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!---  MagmaTouch Guitar Amplifier Head :: Parameters
//!---  --- Definitions
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
		Reverb_MagmaTouch_Params::Reverb_MagmaTouch_Params()
		{
			SetID();
			SetVersionInfo();
			PresetData.Init();
			currentPreset = 0u;
		}
		Reverb_MagmaTouch_Params::Reverb_MagmaTouch_Params(const ::ScorchCrafter::Base::Plug_ParameterList &other)
		{
			SetID();
			SetVersionInfo();
			PresetData.Init();
			currentPreset = 0u;

			const u32 otherParamCount = (u32) ((Reverb_MagmaTouch_Params)other).GetNumberOfParameters();
			const u32 otherPresetCount = (u32) ((Reverb_MagmaTouch_Params)other).GetNumberOfPresets();
			const s32 otherVersionNumber = (s32) ((Reverb_MagmaTouch_Params)other).GetVersionNumber();

			if ( !CompareID( ((Reverb_MagmaTouch_Params)other) ) )
				return;
			if ( versionNumber != otherVersionNumber )
				return;
			if ( otherParamCount != (u32) kMax_Parameter_Count )
				return;
			if ( otherPresetCount != (u32) kPreset_MAX_COUNT )
				return;

			PresetData = ((Reverb_MagmaTouch_Params)other).PresetData;
			currentPreset = (u32) ((Reverb_MagmaTouch_Params)other).currentPreset;
		}
		inline Reverb_MagmaTouch_Params& Reverb_MagmaTouch_Params::operator=(const ::ScorchCrafter::Base::Plug_ParameterList &other)
		{
			SetID();
			SetVersionInfo();
			PresetData.Init();
			currentPreset = 0u;

			const u32 otherParamCount = (u32) ((Reverb_MagmaTouch_Params)other).GetNumberOfParameters();
			const u32 otherPresetCount = (u32) ((Reverb_MagmaTouch_Params)other).GetNumberOfPresets();
			const s32 otherVersionNumber = (s32) ((Reverb_MagmaTouch_Params)other).GetVersionNumber();

			if ( !CompareID( ((Reverb_MagmaTouch_Params)other) ) )
				return *this;
			if ( versionNumber != otherVersionNumber )
				return *this;
			if ( otherParamCount != (u32) kMax_Parameter_Count )
				return *this;
			if ( otherPresetCount != (u32) kPreset_MAX_COUNT )
				return *this;

			PresetData = ((Reverb_MagmaTouch_Params)other).PresetData;
			currentPreset = (u32) ((Reverb_MagmaTouch_Params)other).currentPreset;

			return *this;
		}

		inline u32 Reverb_MagmaTouch_Params::GetNumberOfParameters()
		{
			return (u32) kMax_Parameter_Count;
		}
		inline u32 Reverb_MagmaTouch_Params::GetNumberOfPresets()
		{
			return (u32) kPreset_MAX_COUNT;
		}
		inline s32 Reverb_MagmaTouch_Params::GetID(const s32 index)
		{
			if ( (index < 0) || (index >= 16) )
				return 0;

			return (s32) ID[index];
		}
		inline s32 Reverb_MagmaTouch_Params::GetVersionNumber()
		{
			return (s32) versionNumber;
		}
		inline void Reverb_MagmaTouch_Params::Reset()
		{
			currentPreset = 0u;
		}
		inline void Reverb_MagmaTouch_Params::Reset(const u32 &preset_number)
		{
			SetToPreset( preset_number );
		}
		inline void Reverb_MagmaTouch_Params::SetToPreset(const u32 &preset_number)
		{
			currentPreset = (u32) preset_number;

			if ( currentPreset >= (u32) kPreset_MAX_COUNT )
				currentPreset = (u32) (kPreset_MAX_COUNT - 1u);
		}
		inline u32 Reverb_MagmaTouch_Params::GetCurrentPreset()
		{
			return currentPreset;
		}
		inline void Reverb_MagmaTouch_Params::SetPresetName(const char* name, size_t length)
		{
			if ( currentPreset < (u32) kPreset_MAX_COUNT )
				strncpy ( PresetData.PresetLabels.label[currentPreset].txt, name, (length <= 127) ? length : 127 );
		}
		inline void Reverb_MagmaTouch_Params::GetPresetName(char *name, size_t length)
		{
			if ( currentPreset < (u32) kPreset_MAX_COUNT )
				strncpy ( name, PresetData.PresetLabels.label[currentPreset].txt, (length <= 127) ? length : 127 );
			else
				strncpy ( name, "-", length );
		}
		inline void Reverb_MagmaTouch_Params::GetPresetName(char *name, size_t length, const u32 &index)
		{
			if ( index < (u32) kPreset_MAX_COUNT )
				strncpy ( name, PresetData.PresetLabels.label[index].txt, (length <= 127) ? length : 127 );
			else
				strncpy ( name, "-", length );
		}
		inline void Reverb_MagmaTouch_Params::SetParameter(const u32 &index, const f64 &value)
		{
			if ( index < (u32) kMax_Parameter_Count )
				PresetData.Bank[currentPreset].prm[index] = value;
		}
		inline f64 Reverb_MagmaTouch_Params::GetParameter(const u32 &index)
		{
			if ( index < (u32) kMax_Parameter_Count )
				return PresetData.Bank[currentPreset].prm[index];

			return 0.0;
		}
		inline void Reverb_MagmaTouch_Params::GetParameterName(const u32 &index, char *name, size_t length)
		{
			if ( index < (u32) kMax_Parameter_Count )
				strncpy ( name, PresetData.ControlLabels.label[index].txt, (length <= 15) ? length : 15 );
			else
				strncpy ( name, "-", length );
		}
		inline void Reverb_MagmaTouch_Params::SetID()
		{
			ID[0] =		(s32) 'M';
			ID[1] =		(s32) 'a';
			ID[2] =		(s32) 'g';
			ID[3] =		(s32) 'm';
			ID[4] =		(s32) 'a';
			ID[5] =		(s32) 'T';
			ID[6] =		(s32) 'o';
			ID[7] =		(s32) 'u';
			ID[8] =		(s32) 'c';
			ID[9] =		(s32) 'h';
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
		inline void Reverb_MagmaTouch_Params::SetVersionInfo()
		{
			versionNumber = s32 (
									s32 (s32 (SC_PLG_VER_A) * 1000000) +
									s32 (s32 (SC_PLG_VER_B) * 10000) +
									s32 (s32 (SC_PLG_VER_C) * 100) +
									s32 (SC_PLG_VER_D)
								);
		}
		inline bool Reverb_MagmaTouch_Params::CompareID(const ::ScorchCrafter::Base::Plug_ParameterList &other)
		{
			bool chk_result = true;
			for (u32 i = 0u; i < 16u; i++)
			{
				if ( (s32) ID[i] != (s32) ((Reverb_MagmaTouch_Params)other).GetID( i ) )
					chk_result = false;
			}

			return chk_result;
		}

//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!---  MagmaTouch Guitar Amplifier Head :: Audio Effect
//!---  --- Definitions
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
		Reverb_MagmaTouch::Reverb_MagmaTouch()
		{
			for(u32 i = 0u; i < 32u; i++)
			{
				s_input[i] = 0.0;
				s_output[i] = 0.0;
			}

			#ifdef STEREO_FX_PLUG
				#ifndef SCORCHCRAFTER_COMPILE_64
					InfoData.ID[0] = 'm';
					InfoData.ID[1] = 't';
					InfoData.ID[2] = '4';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 2;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 32 MagmaTouch";
					InfoData.plugin_ID_string = "SC32mgtr";
				#else
					InfoData.ID[0] = 'm';
					InfoData.ID[1] = 't';
					InfoData.ID[2] = '8';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 2;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 64 MagmaTouch";
					InfoData.plugin_ID_string = "SC64mgtr";
				#endif // SCORCHCRAFTER_COMPILE_64
			#else
				#ifndef SCORCHCRAFTER_COMPILE_64
					InfoData.ID[0] = 'm';
					InfoData.ID[1] = 't';
					InfoData.ID[2] = '3';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 1;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 32 MagmaTouch";
					InfoData.plugin_ID_string = "SC32Mgtr";
				#else
					InfoData.ID[0] = 'm';
					InfoData.ID[1] = 't';
					InfoData.ID[2] = '6';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 1;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 64 MagmaTouch";
					InfoData.plugin_ID_string = "SC64Mgtr";
				#endif // SCORCHCRAFTER_COMPILE_64
			#endif // STEREO_FX_PLUG

			InfoData.version = s32 (
								s32 (s32 (SC_PLG_VER_A) * 1000000) +
								s32 (s32 (SC_PLG_VER_B) * 10000) +
								s32 (s32 (SC_PLG_VER_C) * 100) +
								s32 (SC_PLG_VER_D)
								);

			for (u32 i = 0u; i < (u32) Reverb_MagmaTouch_Params::kMax_Parameter_Count; i++)
			{
				prm[i] = 0.0;
				prm_dirty[i] = true;
			}

			FX0.Clear();
			FX0.SetAndCheckSampleRates();

			spRate = 44100.0;

			oversampling_old = 0u;
			oversampling_current = 2u;
			oversampling_online = 2u;
			oversampling_offline = 2u;
		}
		Reverb_MagmaTouch::Reverb_MagmaTouch(const ::ScorchCrafter::Base::BasePlugin &other)
		{
			for(u32 i = 0u; i < 32u; i++)
			{
				s_input[i] = 0.0;
				s_output[i] = 0.0;
			}

			#ifdef STEREO_FX_PLUG
				#ifndef SCORCHCRAFTER_COMPILE_64
					InfoData.ID[0] = 'm';
					InfoData.ID[1] = 't';
					InfoData.ID[2] = '4';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 2;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 32 MagmaTouch";
					InfoData.plugin_ID_string = "SC32mgtr";
				#else
					InfoData.ID[0] = 'm';
					InfoData.ID[1] = 't';
					InfoData.ID[2] = '8';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 2;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 64 MagmaTouch";
					InfoData.plugin_ID_string = "SC64mgtr";
				#endif // SCORCHCRAFTER_COMPILE_64
			#else
				#ifndef SCORCHCRAFTER_COMPILE_64
					InfoData.ID[0] = 'm';
					InfoData.ID[1] = 't';
					InfoData.ID[2] = '3';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 1;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 32 MagmaTouch";
					InfoData.plugin_ID_string = "SC32Mgtr";
				#else
					InfoData.ID[0] = 'm';
					InfoData.ID[1] = 't';
					InfoData.ID[2] = '6';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 1;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 64 MagmaTouch";
					InfoData.plugin_ID_string = "SC64Mgtr";
				#endif // SCORCHCRAFTER_COMPILE_64
			#endif // STEREO_FX_PLUG

			InfoData.version = s32 (
								s32 (s32 (SC_PLG_VER_A) * 1000000) +
								s32 (s32 (SC_PLG_VER_B) * 10000) +
								s32 (s32 (SC_PLG_VER_C) * 100) +
								s32 (SC_PLG_VER_D)
								);

			for (u32 i = 0u; i < (u32) Reverb_MagmaTouch_Params::kMax_Parameter_Count; i++)
			{
				prm[i] = ((Reverb_MagmaTouch)other).GetParameter( i );
				prm_dirty[i] = true;
			}

			FX0.Clear();
			FX0.SetAndCheckSampleRates();

			spRate = ((Reverb_MagmaTouch)other).spRate;

			oversampling_old = ((Reverb_MagmaTouch)other).oversampling_old;
			oversampling_current = ((Reverb_MagmaTouch)other).oversampling_current;
			oversampling_online = ((Reverb_MagmaTouch)other).oversampling_online;
			oversampling_offline = ((Reverb_MagmaTouch)other).oversampling_offline;

			FX0.SetSampleRate( spRate );
			FX0.SetOverSamplingMultiplier( oversampling_current );
		}
		Reverb_MagmaTouch::~Reverb_MagmaTouch()
		{
			// x
		}
		inline void Reverb_MagmaTouch::Init(const f32 smpRate)
		{
			spRate = (f64) smpRate;
			if ( spRate < 44100.0 )
				spRate = 44100.0;

			FX0.Clear();
			FX0.SetSampleRate( spRate );
			FX0.SetOverSamplingMultiplier( oversampling_current );
		}
		inline void Reverb_MagmaTouch::SetSampleRate(const f32 inp_rate)
		{
			spRate = (f64) inp_rate;
			if ( spRate < 44100.0 )
				spRate = 44100.0;

			FX0.Clear();
			FX0.SetSampleRate( spRate );
			FX0.SetOverSamplingMultiplier( oversampling_current );
		}
		inline void Reverb_MagmaTouch::SetParameter(const f64 &inp, const u32 &index)
		{
			if ( index < (u32) Reverb_MagmaTouch_Params::kMax_Parameter_Count )
			{
				prm[index] = (f64) inp;
				prm_dirty[index] = true;
			}

			if ( index == (u32) Reverb_MagmaTouch_Params::kWetDryMix )
			{
				FX0.SetMix( prm[index] );
			} else
			if ( index == (u32) Reverb_MagmaTouch_Params::kEQ_HP )
			{
				FX0.SetEqHP( prm[index] );
			} else
			if ( index == (u32) Reverb_MagmaTouch_Params::kEQ_LP )
			{
				FX0.SetEqLP( prm[index] );
			} else
			if ( index == (u32) Reverb_MagmaTouch_Params::kEQ_ExtraPass )
			{
				if ( prm[index] >= 0.5 )
					FX0.SetEqExtraPasses( true );
				else
					FX0.SetEqExtraPasses( false );
			} else
			if ( index == (u32) Reverb_MagmaTouch_Params::kPreDelay )
			{
				FX0.SetPreDelay( prm[index] );
			} else
			if ( index == (u32) Reverb_MagmaTouch_Params::kPreDelayFine )
			{
				FX0.SetPreDelayFine( prm[index] );
			} else
			if ( index == (u32) Reverb_MagmaTouch_Params::kReverbLength )
			{
				FX0.SetReverbLength( prm[index] );
			} else
			if ( index == (u32) Reverb_MagmaTouch_Params::kReverbLengthFine )
			{
				FX0.SetReverbLengthFine( prm[index] );
			} else
			if ( index == (u32) Reverb_MagmaTouch_Params::kBypassFX )
			{
				if ( prm[index] >= 0.5 )
					FX0.SetBypass( true );
				else
					FX0.SetBypass( false );
			}
		}
		inline f64 Reverb_MagmaTouch::GetParameter(const u32 &index)
		{
			if ( index < (u32) Reverb_MagmaTouch_Params::kMax_Parameter_Count )
				return prm[index];

			return 0.0;
		}
		inline Plug_InfoData Reverb_MagmaTouch::GetPlugInfo()
		{
			return InfoData;
		}
		inline void Reverb_MagmaTouch::Run()
		{
		#ifdef STEREO_FX_PLUG
			FX0.Run( s_input[0], s_input[1] );
		#else
			FX0.Run( s_input[0] );
		#endif // STEREO_FX_PLUG

			s_output[0] = FX0.spl_out_L * prm[Reverb_MagmaTouch_Params::kMasterVol];
			s_output[1] = FX0.spl_out_R * prm[Reverb_MagmaTouch_Params::kMasterVol];
		}
		inline void Reverb_MagmaTouch::RunSampleBlock()
		{
			for (u32 index = 0u; index < (u32) Reverb_MagmaTouch_Params::kMax_Parameter_Count; index++)
			{
				if ( prm_dirty[index] )
				{
					if ( index == (u32) Reverb_MagmaTouch_Params::kOverSampling_On )
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
					if ( index == (u32) Reverb_MagmaTouch_Params::kOverSampling_Off )
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
		inline void Reverb_MagmaTouch::SetBlockSize(const u32 inp)
		{}
		//! ----------------------------------------------------------------
		//! --  Private Functions  -----------------------------------------
		//! ----------------------------------------------------------------
		inline void Reverb_MagmaTouch::SetOverSamplingMultiplier(const u32 &inp, const bool inp_online)
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
		inline void Reverb_MagmaTouch::CheckOverSamplingSettings()
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
	const int SCRFT_PLG_NUM_PROGRAMS = (int) Reverb_MagmaTouch_Params::kPreset_MAX_COUNT;
	const int SCRFT_PLG_NUM_PARAMETERS = (int) Reverb_MagmaTouch_Params::kMax_Parameter_Count;
} // namespace ScorchCrafter

#endif // SCORCHCRAFTER_PLUGIN_JYKWRAKKER_H

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
//   will still attempt to access a "MagmaTouch_GUI.h" file, and use specific
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
	#include "Plugins\Guitar_Amplifier_Heads\MagmaTouch.h"					//< The actual effect declarations and definitions, for both the effect and related parameters

	#ifndef SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI
		#include "Plugins\Guitar_Amplifier_Heads\MagmaTouch_GUI.h"				//< The GUI (Graphic User Interface) for the effect
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
			Base::BasePlugin* Plg = new Plugins::Reverb_MagmaTouch();

			return Plg;
		};
		SCRFT_EXPORT Base::Plug_ParameterList* SCRFT_CreateParameterList()
		{
			Plug_ParameterList* ParamList = new Plugins::Reverb_MagmaTouch_Params();

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
VST_PLUGCLASS=MagmaTouch
MagmaTouch_EXPORTS
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
