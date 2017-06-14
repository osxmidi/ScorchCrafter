#ifndef SCORCHCRAFTER_PLUGIN_JYKWRAKKER_HPP
#define SCORCHCRAFTER_PLUGIN_JYKWRAKKER_HPP

#define SC_PLG_VER_A 1

#define SC_PLG_VER_B 1

#define SC_PLG_VER_C 1

#define SC_PLG_VER_D 1



#include "ScorchCrafter_Plugin.hpp"

#include "EQ_xP.hpp"
#include "OverSample.hpp"
#include "Tube_Overdrive.hpp"
#include "Noise_Gate.hpp"
#include "Stereo_Split.hpp"
#include "Tone_Input.hpp"
#include "Tone_Output.hpp"

using namespace ::ScorchCrafter;
using namespace ::ScorchCrafter::DataTypes;
using namespace ::ScorchCrafter::Base;
using namespace ::ScorchCrafter::Modules;
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
		static const u32 JykWrakker_LIMITS_Oversampling_min = 2u;
		static const u32 JykWrakker_LIMITS_Oversampling_max = 32u;
		static const u32 JykWrakker_LIMITS_Oversampling_bypass = 2u;
		static const u32 JykWrakker_LIMITS_Oversampling_init_A = 4u;
		static const u32 JykWrakker_LIMITS_Oversampling_init_B = 12u;
		static const f64 JykWrakker_LIMITS_Noise_Gate_min = 12.0;
		static const f64 JykWrakker_LIMITS_Noise_Gate_max = 96.0;
		static const f64 JykWrakker_LIMITS_Noise_Gate_skew = 1.5132;
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!---  JykWrakker Guitar Amplifier Head :: Parameters
//!---  --- Prototypes
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
		class SCRFT_EXPORT GuitarAmpHead_JykWrakker_Params : public ::ScorchCrafter::Base::Plug_ParameterList
		{
		public:
			enum kSCsoftParams
			{
				kOverSampling_On		= 0,
				kOverSampling_Off		= 1,
				kMasterVol				= 2,
				kInputBoost				= 3,
				kGainControl			= 4,
				kBright					= 5,
				kAmpChan				= 6,
				kEQBass					= 7,
				kEQMid					= 8,
				kEQTreble				= 9,
				kEQPresence				= 10,
				kEQContour				= 11,
				kNoiseFilter_On			= 12,
				kNoiseFilter_Level		= 13,
				kMax_Parameter_Count	= 14
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
					strncpy( label[kBright].txt,				"bright  ", 15 );
					strncpy( label[kAmpChan].txt,				"channel ", 15 );
					strncpy( label[kEQBass].txt,				"q bass  ", 15 );
					strncpy( label[kEQMid].txt,					"q mid   ", 15 );
					strncpy( label[kEQTreble].txt,				"q treble", 15 );
					strncpy( label[kEQPresence].txt,			"q pres  ", 15 );
					strncpy( label[kEQContour].txt,				"q contr ", 15 );
					strncpy( label[kNoiseFilter_On].txt,		"ns filt ", 15 );
					strncpy( label[kNoiseFilter_Level].txt,		"filt lev", 15 );
				}
			};
			enum kPresetControlList
			{
				kPreset_Init					= 0,
				kPreset_Preset_01				= 1,
				kPreset_Preset_02				= 2,
				kPreset_Preset_03				= 3,
				kPreset_Preset_04				= 4,
				kPreset_Preset_05				= 5,
				kPreset_Preset_06				= 6,
				kPreset_Preset_07				= 7,
				kPreset_Preset_08				= 8,
				kPreset_Preset_09				= 9,
				kPreset_Preset_10				= 10,
				kPreset_Preset_11				= 11,
				kPreset_Preset_12				= 12,

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
					strncpy( label[kPreset_Preset_01].txt,				"Crystal Clean, Body", 127 );
					strncpy( label[kPreset_Preset_02].txt,				"Crystal Clean, Bright", 127 );
					strncpy( label[kPreset_Preset_03].txt,				"Buzzy Crunch, Body", 127 );
					strncpy( label[kPreset_Preset_04].txt,				"Buzzy Crunch, Bright", 127 );
					strncpy( label[kPreset_Preset_05].txt,				"Light Rock, Body", 127 );
					strncpy( label[kPreset_Preset_06].txt,				"Light Rock, Bright", 127 );
					strncpy( label[kPreset_Preset_07].txt,				"Rock, Body", 127 );
					strncpy( label[kPreset_Preset_08].txt,				"Rock, Bright", 127 );
					strncpy( label[kPreset_Preset_09].txt,				"Hi-Gain, Body", 127 );
					strncpy( label[kPreset_Preset_10].txt,				"Hi-Gain, Bright", 127 );
					strncpy( label[kPreset_Preset_11].txt,				"Heavy Hi-Gain, Body", 127 );
					strncpy( label[kPreset_Preset_12].txt,				"Heavy Hi-Gain, Bright", 127 );

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
							Bank[x].prm[kOverSampling_On] = 0.020;
							Bank[x].prm[kOverSampling_Off] = 0.100;
							Bank[x].prm[kMasterVol] = 0.500;
							Bank[x].prm[kInputBoost] = 0.000;
							Bank[x].prm[kGainControl] = 0.500;
							Bank[x].prm[kBright] = 0.000;
							Bank[x].prm[kAmpChan] = 0.500;
							Bank[x].prm[kEQBass] = 0.500;
							Bank[x].prm[kEQMid] = 0.500;
							Bank[x].prm[kEQTreble] = 0.500;
							Bank[x].prm[kEQPresence] = 0.500;
							Bank[x].prm[kEQContour] = 0.500;
							Bank[x].prm[kNoiseFilter_On] = 0.000;
							Bank[x].prm[kNoiseFilter_Level] = 0.600;
						}
					}

					Bank[kPreset_Preset_01].prm[kBright] = 0.00;
					Bank[kPreset_Preset_01].prm[kAmpChan] = 0.00;
					Bank[kPreset_Preset_01].prm[kNoiseFilter_On] = 0.00;

					Bank[kPreset_Preset_02].prm[kBright] = 1.00;
					Bank[kPreset_Preset_02].prm[kAmpChan] = 0.00;
					Bank[kPreset_Preset_02].prm[kNoiseFilter_On] = 0.00;

					Bank[kPreset_Preset_03].prm[kBright] = 0.00;
					Bank[kPreset_Preset_03].prm[kAmpChan] = 0.20;
					Bank[kPreset_Preset_03].prm[kNoiseFilter_On] = 0.00;

					Bank[kPreset_Preset_04].prm[kBright] = 1.00;
					Bank[kPreset_Preset_04].prm[kAmpChan] = 0.20;
					Bank[kPreset_Preset_04].prm[kNoiseFilter_On] = 0.00;

					Bank[kPreset_Preset_05].prm[kBright] = 0.00;
					Bank[kPreset_Preset_05].prm[kAmpChan] = 0.30;
					Bank[kPreset_Preset_05].prm[kNoiseFilter_On] = 0.00;

					Bank[kPreset_Preset_06].prm[kBright] = 1.00;
					Bank[kPreset_Preset_06].prm[kAmpChan] = 0.30;
					Bank[kPreset_Preset_06].prm[kNoiseFilter_On] = 0.00;

					Bank[kPreset_Preset_07].prm[kBright] = 0.00;
					Bank[kPreset_Preset_07].prm[kAmpChan] = 0.50;
					Bank[kPreset_Preset_07].prm[kNoiseFilter_On] = 1.00;

					Bank[kPreset_Preset_08].prm[kBright] = 1.00;
					Bank[kPreset_Preset_08].prm[kAmpChan] = 0.50;
					Bank[kPreset_Preset_08].prm[kNoiseFilter_On] = 1.00;

					Bank[kPreset_Preset_09].prm[kBright] = 0.00;
					Bank[kPreset_Preset_09].prm[kAmpChan] = 0.60;
					Bank[kPreset_Preset_09].prm[kNoiseFilter_On] = 1.00;

					Bank[kPreset_Preset_10].prm[kBright] = 1.00;
					Bank[kPreset_Preset_10].prm[kAmpChan] = 0.60;
					Bank[kPreset_Preset_10].prm[kNoiseFilter_On] = 1.00;

					Bank[kPreset_Preset_11].prm[kBright] = 0.00;
					Bank[kPreset_Preset_11].prm[kAmpChan] = 0.80;
					Bank[kPreset_Preset_11].prm[kNoiseFilter_On] = 1.00;

					Bank[kPreset_Preset_12].prm[kBright] = 1.00;
					Bank[kPreset_Preset_12].prm[kAmpChan] = 0.80;
					Bank[kPreset_Preset_12].prm[kNoiseFilter_On] = 1.00;
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

			GuitarAmpHead_JykWrakker_Params();

			GuitarAmpHead_JykWrakker_Params(const ::ScorchCrafter::Base::Plug_ParameterList &other);

			virtual GuitarAmpHead_JykWrakker_Params& operator=(const ::ScorchCrafter::Base::Plug_ParameterList &other);

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
//!---  JykWrakker Guitar Amplifier Head :: Audio Effect
//!---  --- Prototypes
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
		class SCRFT_EXPORT GuitarAmpHead_JykWrakker : public ::ScorchCrafter::Base::BasePlugin
		{
		public:
			GuitarAmpHead_JykWrakker();

			GuitarAmpHead_JykWrakker(const ::ScorchCrafter::Base::BasePlugin &other);

			virtual ~GuitarAmpHead_JykWrakker();

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
			//! --- Primary FX --
			//! ----------------------------------------------------------------
			struct SCRFT_EXPORT Channel_Audio_Effect
			{
				const f64 noiseSetting_skew;
				const f64 noiseGate_min;
				const f64 noiseGate_max;

				const f64 denormal_offset;

				const bool hasStereoProcessSupport;

				// Sample and rate data
				f64 spl[JykWrakker_LIMITS_Oversampling_max];
				f64 spl_out_L, spl_out_R;
				f64 spRate;
				f64 osRate;
				u32 oversampling_factor;
				f64 spl_boost_factor;
				f64 spl_div_factor;

				// Post-DownSampling Filters to trim off excess (very low) frequencies
				EQ_HP f0_trim, f1_trim, f2_trim, f3_trim, f4_trim, f5_trim, f6_trim, f7_trim;

				// Parameters
				f64 gain_input;
				f64 gain;
				f64 spl_boost;
				bool bright;
				u32 channel;
				u32 channel_old;

				// Parameter Low-Pass input buffer data
				f64 buffer_gain;
				f64 fq0_gain, fq1_gain;

				// FX Components
				Noise_Gate NoiseGate[2];
				OverSampling_Eq_Filter OS_Filter_up[4];
				OverSampling_Eq_Filter OS_Filter_dn[4];
				Tone_Input ToneInput[2];
				Tube_Set AmpChannel[9][2];
				Output_Tone_Stack_v2 ToneStack[2];
				Mono_To_Stereo_Splitter Splitter_M;
				Mono_To_Stereo_Splitter Splitter_S_L, Splitter_S_R;

				inline void Clear()
				{
					for (u32 i = 0u; i < JykWrakker_LIMITS_Oversampling_max; i++)
						spl[i] = 0.0;

					spl_out_L = 0.0;
					spl_out_R = 0.0;

					buffer_gain = 0.0;

					f0_trim.Clear(); f1_trim.Clear(); f2_trim.Clear(); f3_trim.Clear();
					f4_trim.Clear(); f5_trim.Clear(); f6_trim.Clear(); f7_trim.Clear();

					if ( hasStereoProcessSupport == true )
					{
						NoiseGate[0].Clear();
						NoiseGate[1].Clear();

						OS_Filter_up[0].Clear();
						OS_Filter_dn[0].Clear();
						OS_Filter_up[1].Clear();
						OS_Filter_dn[1].Clear();
						OS_Filter_up[2].Clear();
						OS_Filter_dn[2].Clear();
						OS_Filter_up[3].Clear();
						OS_Filter_dn[3].Clear();

						ToneInput[0].Clear();
						ToneInput[1].Clear();

						for ( u32 cnt = 0u; cnt < 9u; cnt++ )
						{
							AmpChannel[cnt][0].Clear();
							AmpChannel[cnt][1].Clear();
						}

						ToneStack[0].Clear();
						ToneStack[1].Clear();

						Splitter_M.Clear();
						Splitter_S_L.Clear();
						Splitter_S_R.Clear();
					} else
					{
						NoiseGate[0].Clear();

						OS_Filter_up[0].Clear();
						OS_Filter_dn[0].Clear();
						OS_Filter_up[1].Clear();
						OS_Filter_dn[1].Clear();

						ToneInput[0].Clear();

						for ( u32 cnt = 0u; cnt < 9u; cnt++ )
							AmpChannel[cnt][0].Clear();

						ToneStack[0].Clear();

						Splitter_M.Clear();
					}
				}
				inline void SetAndCheckSampleRates()
				{
					if ( oversampling_factor < JykWrakker_LIMITS_Oversampling_min )
						oversampling_factor = JykWrakker_LIMITS_Oversampling_min;
					if ( oversampling_factor > JykWrakker_LIMITS_Oversampling_max )
						oversampling_factor = JykWrakker_LIMITS_Oversampling_max;
					if ( spRate < 44100.0 )
						spRate = 44100.0;

					osRate = f64 (spRate * (f64) oversampling_factor);
					spl_boost_factor = (f64) oversampling_factor;
					spl_div_factor = f64 (1.0 / (f64) oversampling_factor);

					// Set rate data for input control buffers
					f64 t = 0.0;

					t = exp( -2.0 * SCRFT_pi_f64 * 12.4230 / spRate );
					fq0_gain = f64 (1.0 - t);
					fq1_gain = f64 (-t);

					const f64 trim_rate = 25.2120;
					f0_trim.SetSampleRate( spRate );
					f1_trim.SetSampleRate( spRate );
					f2_trim.SetSampleRate( spRate );
					f3_trim.SetSampleRate( spRate );
					f4_trim.SetSampleRate( spRate );
					f5_trim.SetSampleRate( spRate );
					f6_trim.SetSampleRate( spRate );
					f7_trim.SetSampleRate( spRate );
					f0_trim.SetPassRate( trim_rate );
					f1_trim.SetPassRate( trim_rate );
					f2_trim.SetPassRate( trim_rate );
					f3_trim.SetPassRate( trim_rate );
					f4_trim.SetPassRate( trim_rate );
					f5_trim.SetPassRate( trim_rate );
					f6_trim.SetPassRate( trim_rate );
					f7_trim.SetPassRate( trim_rate );

					if ( hasStereoProcessSupport == true )
					{
						// Set rates for all components
						NoiseGate[0].SetSampleRate( osRate );
						NoiseGate[1].SetSampleRate( osRate );

						OS_Filter_up[0].SetSampleRate( spRate );
						OS_Filter_dn[0].SetSampleRate( spRate );
						OS_Filter_up[0].SetOverSamplingMultiplier( oversampling_factor );
						OS_Filter_dn[0].SetOverSamplingMultiplier( oversampling_factor );
						OS_Filter_up[1].SetSampleRate( spRate );
						OS_Filter_dn[1].SetSampleRate( spRate );
						OS_Filter_up[1].SetOverSamplingMultiplier( oversampling_factor );
						OS_Filter_dn[1].SetOverSamplingMultiplier( oversampling_factor );
						OS_Filter_up[2].SetSampleRate( spRate );
						OS_Filter_dn[2].SetSampleRate( spRate );
						OS_Filter_up[2].SetOverSamplingMultiplier( oversampling_factor );
						OS_Filter_dn[2].SetOverSamplingMultiplier( oversampling_factor );
						OS_Filter_up[3].SetSampleRate( spRate );
						OS_Filter_dn[3].SetSampleRate( spRate );
						OS_Filter_up[3].SetOverSamplingMultiplier( oversampling_factor );
						OS_Filter_dn[3].SetOverSamplingMultiplier( oversampling_factor );

						ToneInput[0].SetSampleRate( osRate );
						ToneInput[1].SetSampleRate( osRate );

						for ( u32 cnt = 0u; cnt < 9u; cnt++ )
						{
							AmpChannel[cnt][0].SetSampleRate( osRate );
							AmpChannel[cnt][1].SetSampleRate( osRate );
						}

						ToneStack[0].SetSampleRate( osRate );
						ToneStack[1].SetSampleRate( osRate );

						Splitter_M.SetSampleRate( spRate );
						Splitter_S_L.SetSampleRate( spRate );
						Splitter_S_R.SetSampleRate( spRate );
					} else
					{
						// Set rates for all components
						NoiseGate[0].SetSampleRate( osRate );

						OS_Filter_up[0].SetSampleRate( spRate );
						OS_Filter_dn[0].SetSampleRate( spRate );
						OS_Filter_up[0].SetOverSamplingMultiplier( oversampling_factor );
						OS_Filter_dn[0].SetOverSamplingMultiplier( oversampling_factor );
						OS_Filter_up[1].SetSampleRate( spRate );
						OS_Filter_dn[1].SetSampleRate( spRate );
						OS_Filter_up[1].SetOverSamplingMultiplier( oversampling_factor );
						OS_Filter_dn[1].SetOverSamplingMultiplier( oversampling_factor );

						ToneInput[0].SetSampleRate( osRate );

						for ( u32 cnt = 0u; cnt < 9u; cnt++ )
							AmpChannel[cnt][0].SetSampleRate( osRate );

						ToneStack[0].SetSampleRate( osRate );

						Splitter_M.SetSampleRate( spRate );
					}
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
				inline void Run(const f64 &inp)
				{
					if ( oversampling_factor == JykWrakker_LIMITS_Oversampling_bypass )
					{
						spl_out_L = 0.0;
						spl_out_R = 0.0;

						return;
					}

					buffer_gain = (fq0_gain*gain_input) - (fq1_gain*buffer_gain) + SCRFT_dn_f64;
					gain = buffer_gain;

					if ( hasStereoProcessSupport == true )
					{
						f64 inp_smpl_L = inp;
						f64 inp_smpl_R = inp;

						Splitter_S_L.SetStrength( inp_smpl_L );
						Splitter_S_R.SetStrength( inp_smpl_R );
						Splitter_S_L.Run( inp_smpl_L );
						Splitter_S_R.Run( inp_smpl_R );

					// Left Stereo Channel
						AmpChannel[channel][0].SetGain( gain );

						for (u32 i = 1u; i < oversampling_factor; i++)
							spl[i] = denormal_offset;

						spl[0] = Splitter_S_L.spl_L;

						for (u32 i = 0u; i < oversampling_factor; i++)
						{
							f64& fx_spl = spl[i];

							fx_spl = OS_Filter_up[0].Run_LP( fx_spl );
							fx_spl = OS_Filter_up[1].Run_LP( fx_spl );
							fx_spl *= spl_boost_factor;

							NoiseGate[0].RunDetectionOnInput( fx_spl );

							fx_spl *= spl_boost;

							AmpChannel[channel][0].RunGritFx( fx_spl );

							fx_spl = NoiseGate[0].Run( fx_spl );

							fx_spl = ToneInput[0].Run( fx_spl );

							fx_spl = AmpChannel[channel][0].Run( fx_spl );

							fx_spl = ToneStack[0].Run( fx_spl );

							fx_spl = OS_Filter_dn[0].Run_LP( fx_spl );
							fx_spl = OS_Filter_dn[1].Run_LP( fx_spl );
						}

						f64 spl_sum = 0.0;
						for (u32 i = 0u; i < oversampling_factor; i++)
							spl_sum += spl[i];
						spl_sum *= spl_div_factor;

						spl_out_L = spl_sum;

					// Right Stereo Channel
						AmpChannel[channel][1].SetGain( gain );

						for (u32 i = 1u; i < oversampling_factor; i++)
							spl[i] = denormal_offset;

						spl[0] = Splitter_S_R.spl_R;

						for (u32 i = 0u; i < oversampling_factor; i++)
						{
							f64& fx_spl = spl[i];

							fx_spl = OS_Filter_up[2].Run_LP( fx_spl );
							fx_spl = OS_Filter_up[3].Run_LP( fx_spl );
							fx_spl *= spl_boost_factor;

							NoiseGate[1].RunDetectionOnInput( fx_spl );

							fx_spl *= spl_boost;

							AmpChannel[channel][1].RunGritFx( fx_spl );

							fx_spl = NoiseGate[1].Run( fx_spl );

							fx_spl = ToneInput[1].Run( fx_spl );

							fx_spl = AmpChannel[channel][1].Run( fx_spl );

							fx_spl = ToneStack[1].Run( fx_spl );

							fx_spl = OS_Filter_dn[2].Run_LP( fx_spl );
							fx_spl = OS_Filter_dn[3].Run_LP( fx_spl );
						}

						spl_sum = 0.0;
						for (u32 i = 0u; i < oversampling_factor; i++)
							spl_sum += spl[i];
						spl_sum *= spl_div_factor;

						spl_out_R = spl_sum;
					} else
					{
						f64 inp_smpl = inp;

						Splitter_M.SetStrength( inp_smpl );

						AmpChannel[channel][0].SetGain( gain );

						for (u32 i = 1u; i < oversampling_factor; i++)
							spl[i] = denormal_offset;

						spl[0] = inp_smpl;

						for (u32 i = 0u; i < oversampling_factor; i++)
						{
							f64& fx_spl = spl[i];

							fx_spl = OS_Filter_up[0].Run_LP( fx_spl );
							fx_spl = OS_Filter_up[1].Run_LP( fx_spl );
							fx_spl *= spl_boost_factor;

							NoiseGate[0].RunDetectionOnInput( fx_spl );

							fx_spl *= spl_boost;

							AmpChannel[channel][0].RunGritFx( fx_spl );

							fx_spl = NoiseGate[0].Run( fx_spl );

							fx_spl = ToneInput[0].Run( fx_spl );

							fx_spl = AmpChannel[channel][0].Run( fx_spl );

							fx_spl = ToneStack[0].Run( fx_spl );

							fx_spl = OS_Filter_dn[0].Run_LP( fx_spl );
							fx_spl = OS_Filter_dn[1].Run_LP( fx_spl );
						}

						f64 spl_sum = 0.0;
						for (u32 i = 0u; i < oversampling_factor; i++)
							spl_sum += spl[i];

						spl_sum *= spl_div_factor;

						Splitter_M.Run( spl_sum );
						Splitter_M.GetOutputs( spl_out_L, spl_out_R );
					}

				// Final adjustment on both output channels
					f0_trim.RunFx( spl_out_L );
					f1_trim.RunFx( spl_out_L );
					f2_trim.RunFx( spl_out_R );
					f3_trim.RunFx( spl_out_R );
					f4_trim.RunFx( spl_out_L );
					f5_trim.RunFx( spl_out_L );
					f6_trim.RunFx( spl_out_R );
					f7_trim.RunFx( spl_out_R );
				}
				inline void Run(const f64 &inp_L, const f64 &inp_R)
				{
					if ( oversampling_factor == JykWrakker_LIMITS_Oversampling_bypass )
					{
						spl_out_L = 0.0;
						spl_out_R = 0.0;

						return;
					}

					buffer_gain = (fq0_gain*gain_input) - (fq1_gain*buffer_gain) + SCRFT_dn_f64;
					gain = buffer_gain;

					if ( hasStereoProcessSupport == true )
					{
						f64 inp_smpl_L = inp_L;
						f64 inp_smpl_R = inp_R;

						Splitter_S_L.SetStrength( inp_smpl_L );
						Splitter_S_R.SetStrength( inp_smpl_R );
						Splitter_S_L.Run( inp_smpl_L );
						Splitter_S_R.Run( inp_smpl_R );

					// Left Stereo Channel
						AmpChannel[channel][0].SetGain( gain );

						for (u32 i = 1u; i < oversampling_factor; i++)
							spl[i] = denormal_offset;

						spl[0] = Splitter_S_L.spl_L;

						for (u32 i = 0u; i < oversampling_factor; i++)
						{
							f64& fx_spl = spl[i];

							fx_spl = OS_Filter_up[0].Run_LP( fx_spl );
							fx_spl = OS_Filter_up[1].Run_LP( fx_spl );
							fx_spl *= spl_boost_factor;

							NoiseGate[0].RunDetectionOnInput( fx_spl );

							fx_spl *= spl_boost;

							AmpChannel[channel][0].RunGritFx( fx_spl );

							fx_spl = NoiseGate[0].Run( fx_spl );

							fx_spl = ToneInput[0].Run( fx_spl );

							fx_spl = AmpChannel[channel][0].Run( fx_spl );

							fx_spl = ToneStack[0].Run( fx_spl );

							fx_spl = OS_Filter_dn[0].Run_LP( fx_spl );
							fx_spl = OS_Filter_dn[1].Run_LP( fx_spl );
						}

						f64 spl_sum = 0.0;
						for (u32 i = 0u; i < oversampling_factor; i++)
							spl_sum += spl[i];
						spl_sum *= spl_div_factor;

						spl_out_L = spl_sum;

					// Right Stereo Channel
						AmpChannel[channel][1].SetGain( gain );

						for (u32 i = 1u; i < oversampling_factor; i++)
							spl[i] = denormal_offset;

						spl[0] = Splitter_S_R.spl_R;

						for (u32 i = 0u; i < oversampling_factor; i++)
						{
							f64& fx_spl = spl[i];

							fx_spl = OS_Filter_up[2].Run_LP( fx_spl );
							fx_spl = OS_Filter_up[3].Run_LP( fx_spl );
							fx_spl *= spl_boost_factor;

							NoiseGate[1].RunDetectionOnInput( fx_spl );

							fx_spl *= spl_boost;

							AmpChannel[channel][1].RunGritFx( fx_spl );

							fx_spl = NoiseGate[1].Run( fx_spl );

							fx_spl = ToneInput[1].Run( fx_spl );

							fx_spl = AmpChannel[channel][1].Run( fx_spl );

							fx_spl = ToneStack[1].Run( fx_spl );

							fx_spl = OS_Filter_dn[2].Run_LP( fx_spl );
							fx_spl = OS_Filter_dn[3].Run_LP( fx_spl );
						}

						spl_sum = 0.0;
						for (u32 i = 0u; i < oversampling_factor; i++)
							spl_sum += spl[i];
						spl_sum *= spl_div_factor;

						spl_out_R = spl_sum;
					} else
					{
						f64 inp_smpl = inp_L;

						Splitter_M.SetStrength( inp_smpl );

						AmpChannel[channel][0].SetGain( gain );

						for (u32 i = 1u; i < oversampling_factor; i++)
							spl[i] = denormal_offset;

						spl[0] = inp_smpl;

						for (u32 i = 0u; i < oversampling_factor; i++)
						{
							f64& fx_spl = spl[i];

							fx_spl = OS_Filter_up[0].Run_LP( fx_spl );
							fx_spl = OS_Filter_up[1].Run_LP( fx_spl );
							fx_spl *= spl_boost_factor;

							NoiseGate[0].RunDetectionOnInput( fx_spl );

							fx_spl *= spl_boost;

							AmpChannel[channel][0].RunGritFx( fx_spl );

							fx_spl = NoiseGate[0].Run( fx_spl );

							fx_spl = ToneInput[0].Run( fx_spl );

							fx_spl = AmpChannel[channel][0].Run( fx_spl );

							fx_spl = ToneStack[0].Run( fx_spl );

							fx_spl = OS_Filter_dn[0].Run_LP( fx_spl );
							fx_spl = OS_Filter_dn[1].Run_LP( fx_spl );
						}

						f64 spl_sum = 0.0;
						for (u32 i = 0u; i < oversampling_factor; i++)
							spl_sum += spl[i];

						spl_sum *= spl_div_factor;

						Splitter_M.Run( spl_sum );
						Splitter_M.GetOutputs( spl_out_L, spl_out_R );
					}

				// Final adjustment on both output channels
					f0_trim.RunFx( spl_out_L );
					f1_trim.RunFx( spl_out_L );
					f2_trim.RunFx( spl_out_R );
					f3_trim.RunFx( spl_out_R );
					f4_trim.RunFx( spl_out_L );
					f5_trim.RunFx( spl_out_L );
					f6_trim.RunFx( spl_out_R );
					f7_trim.RunFx( spl_out_R );
				}
				inline void SetGain(f64 &inp)
				{
					gain_input = scft_Clamp64( inp, 0.0, 1.0 );
				}
				inline void SetBright(const f64 &inp)
				{
					if ( inp >= 0.5 )
						bright = true;
					else
						bright = false;

					ToneInput[0].SetBright( bright );
					if ( hasStereoProcessSupport == true )
						ToneInput[1].SetBright( bright );
				}
				inline void SetInputBoost(const f64 &inp)
				{
					spl_boost = f64 (( inp > 0.5 ) ? 3.0 : 1.0 );
				}
				inline void SetNoiseFilterLevel(const f64 &inp)
				{
					const f64 noiseGateSetting = 1.0 - pow( 1.0 - inp, noiseSetting_skew );
					const f64 noiseGateThresh = (noiseGate_min * (1.0 - noiseGateSetting)) + (noiseGate_max * noiseGateSetting);

					SetNoiseFilterLevel_dB( noiseGateThresh );
				}
				inline void SetNoiseFilterLevel_dB(const f64 &inp_dB)
				{
					NoiseGate[0].SetThreshold_dB( inp_dB );
					if ( hasStereoProcessSupport == true )
						NoiseGate[1].SetThreshold_dB( inp_dB );
				}
				inline void SetNoiseFilterEnabled(const bool &set_to_on)
				{
					NoiseGate[0].SetEnabled( (Scft_Bool) set_to_on );
					if ( hasStereoProcessSupport == true )
						NoiseGate[1].SetEnabled( (Scft_Bool) set_to_on );
				}
				inline void SetEQBass(const f64 &inp)
				{
					ToneStack[0].InputBandControl_Bass( inp );
					if ( hasStereoProcessSupport == true )
						ToneStack[1].InputBandControl_Bass( inp );
				}
				inline void SetEQMid(const f64 &inp)
				{
					ToneStack[0].InputBandControl_Mids( inp );
					if ( hasStereoProcessSupport == true )
						ToneStack[1].InputBandControl_Mids( inp );
				}
				inline void SetEQTreble(const f64 &inp)
				{
					ToneStack[0].InputBandControl_Treble( inp );
					if ( hasStereoProcessSupport == true )
						ToneStack[1].InputBandControl_Treble( inp );
				}
				inline void SetEQPresence(const f64 &inp)
				{
					ToneStack[0].InputBandControl_Presence( inp );
					if ( hasStereoProcessSupport == true )
						ToneStack[1].InputBandControl_Presence( inp );
				}
				inline void SetEQContour(const f64 &inp)
				{
					ToneStack[0].InputBandControl_Contour( inp );
					if ( hasStereoProcessSupport == true )
						ToneStack[1].InputBandControl_Contour( inp );
				}
				inline void SetChannel(const f64 &inp)
				{
					channel = 0u;
					if ( inp >= 0.05 )
						channel = 1u;
					if ( inp >= 0.15 )
						channel = 2u;
					if ( inp >= 0.25 )
						channel = 3u;
					if ( inp >= 0.35 )
						channel = 4u;
					if ( inp >= 0.45 )
						channel = 5u;
					if ( inp >= 0.55 )
						channel = 6u;
					if ( inp >= 0.65 )
						channel = 7u;
					if ( inp >= 0.75 )
						channel = 8u;

					if ( channel_old != channel )
					{
						channel_old = channel;

						Clear();
					}
				}
				void Init()
				{
					NoiseGate[0].Init();
					NoiseGate[0].SetRates( 12.0, 120.0, 0.057, 93.0 );
					NoiseGate[0].SetThreshold_dB( 72.0 );

					if ( hasStereoProcessSupport == true )
					{
						NoiseGate[1].Init();
						NoiseGate[1].SetRates( 12.0, 120.0, 0.057, 93.0 );
						NoiseGate[1].SetThreshold_dB( 72.0 );
					}

					// Channels 1, 2, 3
					// Uses 2 simulated tube overdrive passes
					// Clean and low gain / crunch
					Tube_Set_Parameters Channel_1(	2u,			// Number of Tube Stages
													1,			// Tube Init Paramater Set
													1,			// Grit FX Init Paramater Set
													0.0129,		// Input Volume min
													1.0236,		// Input Volume max
													0.0372,		// Overdrive min
													0.7500,		// Overdrive max
													1.0000,		// Output Volume min
													1.0000		// Output Volume max
												);
					Tube_Set_Parameters Channel_2(	2u,			// Number of Tube Stages
													1,			// Tube Init Paramater Set
													1,			// Grit FX Init Paramater Set
													0.1245,		// Input Volume min
													1.2513,		// Input Volume max
													0.1920,		// Overdrive min
													1.0000,		// Overdrive max
													1.0000,		// Output Volume min
													1.0000		// Output Volume max
												);
					Tube_Set_Parameters Channel_3(	2u,			// Number of Tube Stages
													1,			// Tube Init Paramater Set
													1,			// Grit FX Init Paramater Set
													0.3045,		// Input Volume min
													1.8012,		// Input Volume max
													0.3900,		// Overdrive min
													1.0000,		// Overdrive max
													1.0000,		// Output Volume min
													1.0000		// Output Volume max
												);

					// Channels 4, 5, 6
					// Uses 3 simulated tube overdrive passes
					// Mid-range gain, moderate overdrive
					Tube_Set_Parameters Channel_4(	3u,			// Number of Tube Stages
													2,			// Tube Init Paramater Set
													2,			// Grit FX Init Paramater Set
													0.0093,		// Input Volume min
													0.6420,		// Input Volume max
													0.0912,		// Overdrive min
													0.9012,		// Overdrive max
													1.0000,		// Output Volume min
													1.0000		// Output Volume max
												);
					Tube_Set_Parameters Channel_5(	3u,			// Number of Tube Stages
													2,			// Tube Init Paramater Set
													2,			// Grit FX Init Paramater Set
													0.0525,		// Input Volume min
													1.2045,		// Input Volume max
													0.1920,		// Overdrive min
													1.0000,		// Overdrive max
													1.0000,		// Output Volume min
													1.0000		// Output Volume max
												);
					Tube_Set_Parameters Channel_6(	3u,			// Number of Tube Stages
													2,			// Tube Init Paramater Set
													2,			// Grit FX Init Paramater Set
													0.1425,		// Input Volume min
													1.4250,		// Input Volume max
													0.4512,		// Overdrive min
													1.0000,		// Overdrive max
													1.0000,		// Output Volume min
													1.0000		// Output Volume max
												);

					// Channels 7, 8, 9
					// Uses 4 simulated tube overdrive passes
					// High-gain overdrive
					Tube_Set_Parameters Channel_7(	4u,			// Number of Tube Stages
													3,			// Tube Init Paramater Set
													3,			// Grit FX Init Paramater Set
													0.0570,		// Input Volume min
													0.9300,		// Input Volume max
													0.2523,		// Overdrive min
													0.9705,		// Overdrive max
													1.0000,		// Output Volume min
													1.0000		// Output Volume max
												);
					Tube_Set_Parameters Channel_8(	4u,			// Number of Tube Stages
													3,			// Tube Init Paramater Set
													3,			// Grit FX Init Paramater Set
													0.0930,		// Input Volume min
													1.0245,		// Input Volume max
													0.3045,		// Overdrive min
													1.0000,		// Overdrive max
													1.0000,		// Output Volume min
													1.0000		// Output Volume max
												);
					Tube_Set_Parameters Channel_9(	4u,			// Number of Tube Stages
													3,			// Tube Init Paramater Set
													3,			// Grit FX Init Paramater Set
													0.1920,		// Input Volume min
													1.2405,		// Input Volume max
													0.4215,		// Overdrive min
													1.0000,		// Overdrive max
													1.0000,		// Output Volume min
													1.0000		// Output Volume max
												);

					AmpChannel[0][0] = Channel_1;
					AmpChannel[1][0] = Channel_2;
					AmpChannel[2][0] = Channel_3;
					AmpChannel[3][0] = Channel_4;
					AmpChannel[4][0] = Channel_5;
					AmpChannel[5][0] = Channel_6;
					AmpChannel[6][0] = Channel_7;
					AmpChannel[7][0] = Channel_8;
					AmpChannel[8][0] = Channel_9;

					if ( hasStereoProcessSupport == true )
					{
						AmpChannel[0][1] = Channel_1;
						AmpChannel[1][1] = Channel_2;
						AmpChannel[2][1] = Channel_3;
						AmpChannel[3][1] = Channel_4;
						AmpChannel[4][1] = Channel_5;
						AmpChannel[5][1] = Channel_6;
						AmpChannel[6][1] = Channel_7;
						AmpChannel[7][1] = Channel_8;
						AmpChannel[8][1] = Channel_9;
					}

					Clear();

					gain_input = 0.0;
					spl_boost = 1.0;

					channel = 0u;
					channel_old = 0u;

					SetAndCheckSampleRates();

					SetChannel( 0.0 );
				}
				void UnInit() const
				{
				}
				Channel_Audio_Effect(const bool enable_stereo = false) :
					noiseSetting_skew( (f64) JykWrakker_LIMITS_Noise_Gate_skew ),
					noiseGate_min( (f64) JykWrakker_LIMITS_Noise_Gate_min ),
					noiseGate_max( (f64) JykWrakker_LIMITS_Noise_Gate_max ),
					// Note:  This should be tiny but a little LARGER THAN (static const f64) SCRFT_dn_f64 as declared and set in "Scorchcrafter_Platform.hpp"
					denormal_offset( f64 ((f80) powl( (f80) 10.L, (f80) -28.20L )) ),
					hasStereoProcessSupport( (bool) enable_stereo ),
					spl_out_L( 0.0 ), spl_out_R( 0.0 ),
					spRate( 44100.0 ),
					osRate( 88200.0 ),
					oversampling_factor( (u32) JykWrakker_LIMITS_Oversampling_bypass ),
					spl_boost_factor( 2.0 ),
					spl_div_factor( 0.5 ),
					gain_input( 0.01 ),
					gain( 0.01 ),
					spl_boost( 1.0 ),
					bright( false ),
					channel( 1u ),
					channel_old( 0u ),
					buffer_gain( 0.01 ),
					fq0_gain( 0.5 ),
					fq1_gain( 0.5 ),
					ToneStack{ 1, 1 },
					// For quick reference, the constructor we are using here for the stereo splitter struct is:
					//   Mono_To_Stereo_Splitter( (f64) fx_strength, (s32) num_steps, (f64) stride_ms, (f64) smoothing_frequency, (f64) inp_strength_smooth_frequency = 12.0 )
					Splitter_M		( 0.3234, 12, 0.7500, 30.0 ),
					Splitter_S_L	( 0.3234, 12, 3.4230, 30.0 ),
					Splitter_S_R	( 0.3234, 12, 3.4230, 30.0 )
				{
					for (u32 i = 0u; i < JykWrakker_LIMITS_Oversampling_max; i++)
						spl[i] = 0.0;

					NoiseGate[0].Init();
					NoiseGate[0].SetRates( 12.0, 120.0, 0.057, 93.0 );
					NoiseGate[0].SetThreshold_dB( 72.0 );
					if ( hasStereoProcessSupport == true )
					{
						NoiseGate[1].Init();
						NoiseGate[1].SetRates( 12.0, 120.0, 0.057, 93.0 );
						NoiseGate[1].SetThreshold_dB( 72.0 );
					}

					Splitter_M.SetStrengthRange		( 0.1920, 0.0012 );
					Splitter_M.EnableAutoStrength	( false );
					Splitter_S_L.SetStrengthRange	( 0.3612, 0.0192 );
					Splitter_S_L.SetStrengthRange	( 0.3612, 0.0192 );
					Splitter_S_R.EnableAutoStrength	( false );
					Splitter_S_R.EnableAutoStrength	( false );
				}
			}; // struct Channel_Audio_Effect

			//! ----------------------------------------------------------------
			f64 prm[GuitarAmpHead_JykWrakker_Params::kMax_Parameter_Count];
			bool prm_dirty[GuitarAmpHead_JykWrakker_Params::kMax_Parameter_Count];

			Channel_Audio_Effect FX0;

			inline void SetOverSamplingMultiplier(const u32 &inp, const bool inp_online);
			inline void CheckOverSamplingSettings();
		}; // class GuitarAmpHead_JykWrakker
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!---  JykWrakker Guitar Amplifier Head :: Parameters
//!---  --- Definitions
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
		GuitarAmpHead_JykWrakker_Params::GuitarAmpHead_JykWrakker_Params()
		{
			SetID();
			SetVersionInfo();
			PresetData.Init();
			currentPreset = 0u;
		}
		GuitarAmpHead_JykWrakker_Params::GuitarAmpHead_JykWrakker_Params(const ::ScorchCrafter::Base::Plug_ParameterList &other)
		{
			SetID();
			SetVersionInfo();
			PresetData.Init();
			currentPreset = 0u;

			const u32 otherParamCount = (u32) ((GuitarAmpHead_JykWrakker_Params)other).GetNumberOfParameters();
			const u32 otherPresetCount = (u32) ((GuitarAmpHead_JykWrakker_Params)other).GetNumberOfPresets();
			const s32 otherVersionNumber = (s32) ((GuitarAmpHead_JykWrakker_Params)other).GetVersionNumber();

			if ( !CompareID( ((GuitarAmpHead_JykWrakker_Params)other) ) )
				return;
			if ( versionNumber != otherVersionNumber )
				return;
			if ( otherParamCount != (u32) kMax_Parameter_Count )
				return;
			if ( otherPresetCount != (u32) kPreset_MAX_COUNT )
				return;

			PresetData = ((GuitarAmpHead_JykWrakker_Params)other).PresetData;
			currentPreset = (u32) ((GuitarAmpHead_JykWrakker_Params)other).currentPreset;
		}
		inline GuitarAmpHead_JykWrakker_Params& GuitarAmpHead_JykWrakker_Params::operator=(const ::ScorchCrafter::Base::Plug_ParameterList &other)
		{
			SetID();
			SetVersionInfo();
			PresetData.Init();
			currentPreset = 0u;

			const u32 otherParamCount = (u32) ((GuitarAmpHead_JykWrakker_Params)other).GetNumberOfParameters();
			const u32 otherPresetCount = (u32) ((GuitarAmpHead_JykWrakker_Params)other).GetNumberOfPresets();
			const s32 otherVersionNumber = (s32) ((GuitarAmpHead_JykWrakker_Params)other).GetVersionNumber();

			if ( !CompareID( ((GuitarAmpHead_JykWrakker_Params)other) ) )
				return *this;
			if ( versionNumber != otherVersionNumber )
				return *this;
			if ( otherParamCount != (u32) kMax_Parameter_Count )
				return *this;
			if ( otherPresetCount != (u32) kPreset_MAX_COUNT )
				return *this;

			PresetData = ((GuitarAmpHead_JykWrakker_Params)other).PresetData;
			currentPreset = (u32) ((GuitarAmpHead_JykWrakker_Params)other).currentPreset;

			return *this;
		}

		inline u32 GuitarAmpHead_JykWrakker_Params::GetNumberOfParameters()
		{
			return (u32) kMax_Parameter_Count;
		}
		inline u32 GuitarAmpHead_JykWrakker_Params::GetNumberOfPresets()
		{
			return (u32) kPreset_MAX_COUNT;
		}
		inline s32 GuitarAmpHead_JykWrakker_Params::GetID(const s32 index)
		{
			if ( (index < 0) || (index >= 16) )
				return 0;

			return (s32) ID[index];
		}
		inline s32 GuitarAmpHead_JykWrakker_Params::GetVersionNumber()
		{
			return (s32) versionNumber;
		}
		inline void GuitarAmpHead_JykWrakker_Params::Reset()
		{
			currentPreset = 0u;
		}
		inline void GuitarAmpHead_JykWrakker_Params::Reset(const u32 &preset_number)
		{
			SetToPreset( preset_number );
		}
		inline void GuitarAmpHead_JykWrakker_Params::SetToPreset(const u32 &preset_number)
		{
			currentPreset = (u32) preset_number;

			if ( currentPreset >= (u32) kPreset_MAX_COUNT )
				currentPreset = (u32) (kPreset_MAX_COUNT - 1u);
		}
		inline u32 GuitarAmpHead_JykWrakker_Params::GetCurrentPreset()
		{
			return currentPreset;
		}
		inline void GuitarAmpHead_JykWrakker_Params::SetPresetName(const char* name, size_t length)
		{
			if ( currentPreset < (u32) kPreset_MAX_COUNT )
				strncpy ( PresetData.PresetLabels.label[currentPreset].txt, name, (length <= 127) ? length : 127 );
		}
		inline void GuitarAmpHead_JykWrakker_Params::GetPresetName(char *name, size_t length)
		{
			if ( currentPreset < (u32) kPreset_MAX_COUNT )
				strncpy ( name, PresetData.PresetLabels.label[currentPreset].txt, (length <= 127) ? length : 127 );
			else
				strncpy ( name, "-", length );
		}
		inline void GuitarAmpHead_JykWrakker_Params::GetPresetName(char *name, size_t length, const u32 &index)
		{
			if ( index < (u32) kPreset_MAX_COUNT )
				strncpy ( name, PresetData.PresetLabels.label[index].txt, (length <= 127) ? length : 127 );
			else
				strncpy ( name, "-", length );
		}
		inline void GuitarAmpHead_JykWrakker_Params::SetParameter(const u32 &index, const f64 &value)
		{
			if ( index < (u32) kMax_Parameter_Count )
				PresetData.Bank[currentPreset].prm[index] = value;
		}
		inline f64 GuitarAmpHead_JykWrakker_Params::GetParameter(const u32 &index)
		{
			if ( index < (u32) kMax_Parameter_Count )
				return PresetData.Bank[currentPreset].prm[index];

			return 0.0;
		}
		inline void GuitarAmpHead_JykWrakker_Params::GetParameterName(const u32 &index, char *name, size_t length)
		{
			if ( index < (u32) kMax_Parameter_Count )
				strncpy ( name, PresetData.ControlLabels.label[index].txt, (length <= 15) ? length : 15 );
			else
				strncpy ( name, "-", length );
		}
		inline void GuitarAmpHead_JykWrakker_Params::SetID()
		{
			ID[0] =		(s32) 'J';
			ID[1] =		(s32) 'y';
			ID[2] =		(s32) 'k';
			ID[3] =		(s32) 'W';
			ID[4] =		(s32) 'r';
			ID[5] =		(s32) 'a';
			ID[6] =		(s32) 'k';
			ID[7] =		(s32) 'k';
			ID[8] =		(s32) 'e';
			ID[9] =		(s32) 'r';
			ID[10] =	(s32) 'A';
			ID[11] =	(s32) 'm';
			ID[12] =	(s32) 'p';
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
		inline void GuitarAmpHead_JykWrakker_Params::SetVersionInfo()
		{
			versionNumber = s32 (
									s32 (s32 (SC_PLG_VER_A) * 1000000) +
									s32 (s32 (SC_PLG_VER_B) * 10000) +
									s32 (s32 (SC_PLG_VER_C) * 100) +
									s32 (SC_PLG_VER_D)
								);
		}
		inline bool GuitarAmpHead_JykWrakker_Params::CompareID(const ::ScorchCrafter::Base::Plug_ParameterList &other)
		{
			bool chk_result = true;
			for (u32 i = 0u; i < 16u; i++)
			{
				if ( (s32) ID[i] != (s32) ((GuitarAmpHead_JykWrakker_Params)other).GetID( i ) )
					chk_result = false;
			}

			return chk_result;
		}

//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!---  JykWrakker Guitar Amplifier Head :: Audio Effect
//!---  --- Definitions
//!--------------------------------------------------------------------------------------------------------------------------------------------------
//!--------------------------------------------------------------------------------------------------------------------------------------------------
		GuitarAmpHead_JykWrakker::GuitarAmpHead_JykWrakker() :
		#ifdef STEREO_FX_PLUG
			FX0( true )
		#else
			FX0( false )
		#endif // STEREO_FX_PLUG
		{
			for(u32 i = 0u; i < 32u; i++)
			{
				s_input[i] = 0.0;
				s_output[i] = 0.0;
			}

			#ifdef STEREO_FX_PLUG
				#ifndef SCORCHCRAFTER_COMPILE_64
					InfoData.ID[0] = 'j';
					InfoData.ID[1] = 'k';
					InfoData.ID[2] = '4';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 2;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 32 JykWrakker (Dual)";
					InfoData.plugin_ID_string = "SC32jykD";
				#else
					InfoData.ID[0] = 'j';
					InfoData.ID[1] = 'k';
					InfoData.ID[2] = '8';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 2;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 64 JykWrakker (Dual)";
					InfoData.plugin_ID_string = "SC64jykD";
				#endif // SCORCHCRAFTER_COMPILE_64
			#else
				#ifndef SCORCHCRAFTER_COMPILE_64
					InfoData.ID[0] = 'j';
					InfoData.ID[1] = 'k';
					InfoData.ID[2] = '3';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 1;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 32 JykWrakker (Single)";
					InfoData.plugin_ID_string = "SC32jykr";
				#else
					InfoData.ID[0] = 'j';
					InfoData.ID[1] = 'k';
					InfoData.ID[2] = '6';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 1;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 64 JykWrakker (Single)";
					InfoData.plugin_ID_string = "SC64jykr";
				#endif // SCORCHCRAFTER_COMPILE_64
			#endif // STEREO_FX_PLUG

			InfoData.version = s32 (
								s32 (s32 (SC_PLG_VER_A) * 1000000) +
								s32 (s32 (SC_PLG_VER_B) * 10000) +
								s32 (s32 (SC_PLG_VER_C) * 100) +
								s32 (SC_PLG_VER_D)
								);

			for (u32 i = 0u; i < (u32) GuitarAmpHead_JykWrakker_Params::kMax_Parameter_Count; i++)
			{
				prm[i] = 0.0;
				prm_dirty[i] = true;
			}

			FX0.Init();
			FX0.Clear();
			FX0.SetAndCheckSampleRates();

			spRate = 44100.0;

			oversampling_old = JykWrakker_LIMITS_Oversampling_bypass;
			oversampling_current = JykWrakker_LIMITS_Oversampling_init_A;
			oversampling_online = JykWrakker_LIMITS_Oversampling_init_A;
			oversampling_offline = JykWrakker_LIMITS_Oversampling_init_B;

			FX0.SetSampleRate( spRate );
			FX0.SetOverSamplingMultiplier( oversampling_current );
		}
		GuitarAmpHead_JykWrakker::GuitarAmpHead_JykWrakker(const ::ScorchCrafter::Base::BasePlugin &other) :
		#ifdef STEREO_FX_PLUG
			FX0( true )
		#else
			FX0( false )
		#endif // STEREO_FX_PLUG
		{
			for(u32 i = 0u; i < 32u; i++)
			{
				s_input[i] = 0.0;
				s_output[i] = 0.0;
			}

			#ifdef STEREO_FX_PLUG
				#ifndef SCORCHCRAFTER_COMPILE_64
					InfoData.ID[0] = 'j';
					InfoData.ID[1] = 'k';
					InfoData.ID[2] = '4';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 2;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 32 JykWrakker (Dual)";
					InfoData.plugin_ID_string = "SC32jykD";
				#else
					InfoData.ID[0] = 'j';
					InfoData.ID[1] = 'k';
					InfoData.ID[2] = '8';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 2;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 64 JykWrakker (Dual)";
					InfoData.plugin_ID_string = "SC64jykD";
				#endif // SCORCHCRAFTER_COMPILE_64
			#else
				#ifndef SCORCHCRAFTER_COMPILE_64
					InfoData.ID[0] = 'j';
					InfoData.ID[1] = 'k';
					InfoData.ID[2] = '3';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 1;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 32 JykWrakker (Single)";
					InfoData.plugin_ID_string = "SC32jykr";
				#else
					InfoData.ID[0] = 'j';
					InfoData.ID[1] = 'k';
					InfoData.ID[2] = '6';
					InfoData.ID[3] = 't';

					InfoData.numInputs = 1;
					InfoData.numOutputs = 2;

					InfoData.plugin_name = "SC 64 JykWrakker (Single)";
					InfoData.plugin_ID_string = "SC64jykr";
				#endif // SCORCHCRAFTER_COMPILE_64
			#endif // STEREO_FX_PLUG

			InfoData.version = s32 (
								s32 (s32 (SC_PLG_VER_A) * 1000000) +
								s32 (s32 (SC_PLG_VER_B) * 10000) +
								s32 (s32 (SC_PLG_VER_C) * 100) +
								s32 (SC_PLG_VER_D)
								);

			for (u32 i = 0u; i < (u32) GuitarAmpHead_JykWrakker_Params::kMax_Parameter_Count; i++)
			{
				prm[i] = ((GuitarAmpHead_JykWrakker)other).GetParameter( i );
				prm_dirty[i] = true;
			}

			FX0.Init();
			FX0.Clear();
			FX0.SetAndCheckSampleRates();

			spRate = ((GuitarAmpHead_JykWrakker)other).spRate;
			if ( spRate < 44100.0 )
				spRate = 44100.0;

			oversampling_old = ((GuitarAmpHead_JykWrakker)other).oversampling_old;
			oversampling_current = ((GuitarAmpHead_JykWrakker)other).oversampling_current;
			oversampling_online = ((GuitarAmpHead_JykWrakker)other).oversampling_online;
			oversampling_offline = ((GuitarAmpHead_JykWrakker)other).oversampling_offline;

			FX0.SetSampleRate( spRate );
			FX0.SetOverSamplingMultiplier( oversampling_current );
		}
		GuitarAmpHead_JykWrakker::~GuitarAmpHead_JykWrakker()
		{
			FX0.UnInit();
		}
		inline void GuitarAmpHead_JykWrakker::Init(const f32 smpRate)
		{
			spRate = (f64) smpRate;
			if ( spRate < 44100.0 )
				spRate = 44100.0;

			FX0.Clear();
			FX0.SetSampleRate( spRate );
			FX0.SetOverSamplingMultiplier( oversampling_current );
		}
		inline void GuitarAmpHead_JykWrakker::SetSampleRate(const f32 inp_rate)
		{
			spRate = (f64) inp_rate;
			if ( spRate < 44100.0 )
				spRate = 44100.0;

			FX0.Clear();
			FX0.SetSampleRate( spRate );
			FX0.SetOverSamplingMultiplier( oversampling_current );
		}
		inline void GuitarAmpHead_JykWrakker::SetParameter(const f64 &inp, const u32 &index)
		{
			if ( index < (u32) GuitarAmpHead_JykWrakker_Params::kMax_Parameter_Count )
			{
				prm[index] = (f64) inp;
				prm_dirty[index] = true;
			}

			if ( index == (u32) GuitarAmpHead_JykWrakker_Params::kInputBoost )
			{
				FX0.SetInputBoost( prm[index] );
			} else
			if ( index == (u32) GuitarAmpHead_JykWrakker_Params::kGainControl )
			{
				FX0.SetGain( prm[index] );
			} else
			if ( index == (u32) GuitarAmpHead_JykWrakker_Params::kBright )
			{
				FX0.SetBright( prm[index] );
			} else
			if ( index == (u32) GuitarAmpHead_JykWrakker_Params::kEQBass )
			{
				FX0.SetEQBass( prm[index] );
			} else
			if ( index == (u32) GuitarAmpHead_JykWrakker_Params::kEQMid )
			{
				FX0.SetEQMid( prm[index] );
			} else
			if ( index == (u32) GuitarAmpHead_JykWrakker_Params::kEQTreble )
			{
				FX0.SetEQTreble( prm[index] );
			} else
			if ( index == (u32) GuitarAmpHead_JykWrakker_Params::kEQPresence )
			{
				FX0.SetEQPresence( prm[index] );
			} else
			if ( index == (u32) GuitarAmpHead_JykWrakker_Params::kEQContour )
			{
				FX0.SetEQContour( prm[index] );
			} else
			if ( index == (u32) GuitarAmpHead_JykWrakker_Params::kAmpChan )
			{
				FX0.SetChannel( prm[index] );
			} else
			if ( index == (u32) GuitarAmpHead_JykWrakker_Params::kNoiseFilter_Level )
			{
				FX0.SetNoiseFilterLevel( prm[index] );
			} else
			if ( index == (u32) GuitarAmpHead_JykWrakker_Params::kNoiseFilter_On )
			{
				if ( prm[index] >= 0.5 )
					FX0.SetNoiseFilterEnabled( true );
				else
					FX0.SetNoiseFilterEnabled( false );
			}
		}
		inline f64 GuitarAmpHead_JykWrakker::GetParameter(const u32 &index)
		{
			if ( index < (u32) GuitarAmpHead_JykWrakker_Params::kMax_Parameter_Count )
				return prm[index];

			return 0.0;
		}
		inline Plug_InfoData GuitarAmpHead_JykWrakker::GetPlugInfo()
		{
			return InfoData;
		}
		inline void GuitarAmpHead_JykWrakker::Run()
		{
		#ifdef STEREO_FX_PLUG
			FX0.Run( s_input[0], s_input[1] );
		#else
			FX0.Run( s_input[0] );
		#endif // STEREO_FX_PLUG

			s_output[0] = FX0.spl_out_L * prm[GuitarAmpHead_JykWrakker_Params::kMasterVol];
			s_output[1] = FX0.spl_out_R * prm[GuitarAmpHead_JykWrakker_Params::kMasterVol];
		}
		inline void GuitarAmpHead_JykWrakker::RunSampleBlock()
		{
			for (u32 index = 0u; index < (u32) GuitarAmpHead_JykWrakker_Params::kMax_Parameter_Count; index++)
			{
				if ( prm_dirty[index] )
				{
					if ( index == (u32) GuitarAmpHead_JykWrakker_Params::kOverSampling_On )
					{
						if ( prm[index] < 0.005 )
						{
							SetOverSamplingMultiplier( JykWrakker_LIMITS_Oversampling_min, true );
						} else
						{
							const f64 check_increment = 0.010;
							f64 check_value = 0.005;
							bool val_found = false;
							u32 multiplier = 0u;
							u32 multiplier_accum = JykWrakker_LIMITS_Oversampling_min + 1u;

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

							if ( multiplier < JykWrakker_LIMITS_Oversampling_min )
								multiplier = JykWrakker_LIMITS_Oversampling_min;
							if ( multiplier > JykWrakker_LIMITS_Oversampling_max )
								multiplier = JykWrakker_LIMITS_Oversampling_max;

							SetOverSamplingMultiplier( multiplier, true );
						}
					} else
					if ( index == (u32) GuitarAmpHead_JykWrakker_Params::kOverSampling_Off )
					{
						if ( prm[index] < 0.005 )
						{
							SetOverSamplingMultiplier( JykWrakker_LIMITS_Oversampling_min, false );
						} else
						{
							const f64 check_increment = 0.010;
							f64 check_value = 0.005;
							bool val_found = false;
							u32 multiplier = 0u;
							u32 multiplier_accum = JykWrakker_LIMITS_Oversampling_min + 1u;

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

							if ( multiplier < JykWrakker_LIMITS_Oversampling_min )
								multiplier = JykWrakker_LIMITS_Oversampling_min;
							if ( multiplier > JykWrakker_LIMITS_Oversampling_max )
								multiplier = JykWrakker_LIMITS_Oversampling_max;

							SetOverSamplingMultiplier( multiplier, false );
						}
					}

					prm_dirty[index] = false;
				}
			}

			CheckOverSamplingSettings();
		}
		inline void GuitarAmpHead_JykWrakker::SetBlockSize(const u32 inp)
		{}
		//! ----------------------------------------------------------------
		//! --  Private Functions  -----------------------------------------
		//! ----------------------------------------------------------------
		inline void GuitarAmpHead_JykWrakker::SetOverSamplingMultiplier(const u32 &inp, const bool inp_online)
		{
			u32 oversampling_new = (u32) inp;

			if ( oversampling_new < JykWrakker_LIMITS_Oversampling_min )
				oversampling_new = JykWrakker_LIMITS_Oversampling_min;
			if ( oversampling_new > JykWrakker_LIMITS_Oversampling_max )
				oversampling_new = JykWrakker_LIMITS_Oversampling_max;

			if ( inp_online )
				oversampling_online = oversampling_new;
			else
				oversampling_offline = oversampling_new;

			if ( runningOffline )
				CheckOverSamplingSettings();
		}
		inline void GuitarAmpHead_JykWrakker::CheckOverSamplingSettings()
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
	const int SCRFT_PLG_NUM_PROGRAMS = (int) GuitarAmpHead_JykWrakker_Params::kPreset_MAX_COUNT;
	const int SCRFT_PLG_NUM_PARAMETERS = (int) GuitarAmpHead_JykWrakker_Params::kMax_Parameter_Count;
} // namespace ScorchCrafter

#endif // SCORCHCRAFTER_PLUGIN_JYKWRAKKER_HPP
