#ifndef SCORCHCRAFTER_PLUGIN_BASE_HPP
#define SCORCHCRAFTER_PLUGIN_BASE_HPP

#include "Scorchcrafter_Platform.hpp"

namespace ScorchCrafter
{
	namespace DataTypes
	{
		#ifndef SCORCHCRAFTER_DATA_STRUCTS_DEFINED
		#define SCORCHCRAFTER_DATA_STRUCTS_DEFINED

		struct SCRFT_EXPORT txtString_128
		{
			char txt[128];

			inline void Clear()
			{
				strncpy( txt, "-", 127u );
			}
			inline void Set(const char* inp_txt, const u32 inp_length = 127u)
			{
				strncpy( txt, inp_txt, u32 ((inp_length > 127u) ? 127u : inp_length) );
			}
			inline void Get(char* out_txt, const u32 inp_length = 127u)
			{
				strncpy( out_txt, txt, u32 ((inp_length > 127u) ? 127u : inp_length) );
			}
			txtString_128()
			{
				strncpy( txt, "-", 127u );
			}
			txtString_128(const char* inp_txt)
			{
				strncpy( txt, inp_txt, 127u );
			}
			txtString_128& operator=(const txtString_128 &other)
			{
				strncpy( txt, other.txt, 127u );

				return *this;
			}
		};
		struct SCRFT_EXPORT txtString_16
		{
			char txt[16];

			inline void Clear()
			{
				strncpy( txt, "-", 15u );
			}
			inline void Set(const char* inp_txt, const u32 inp_length = 15u)
			{
				strncpy( txt, inp_txt, u32 ((inp_length > 15u) ? 15u : inp_length) );
			}
			inline void Get(char* out_txt, const u32 inp_length = 15u)
			{
				strncpy( out_txt, txt, u32 ((inp_length > 15u) ? 15u : inp_length) );
			}
			txtString_16()
			{
				strncpy( txt, "-", 15u );
			}
			txtString_16(const char* inp_txt)
			{
				strncpy( txt, inp_txt, 15u );
			}
			txtString_16& operator=(const txtString_16 &other)
			{
				strncpy( txt, other.txt, 15u );

				return *this;
			}
		};

		#endif // SCORCHCRAFTER_DATA_STRUCTS_DEFINED
	} // namespace DataTypes

	namespace Base
	{
		using namespace ::ScorchCrafter::DataTypes;

		struct SCRFT_EXPORT Plug_InfoData
		{
			char ID[4];
			int numInputs;
			int numOutputs;
			char* plugin_name;
			char* plugin_ID_string;
			s32 version;

			Plug_InfoData() :
				ID{ '-', '-', '-', '-' },
				numInputs( 0 ),
				numOutputs( 0 ),
				plugin_name( (char*)"-" ),
				plugin_ID_string( (char*)"-" ),
				version( 0 )
			{};
		};

		class SCRFT_EXPORT BasePlugin
		{
		public:
			virtual inline void Init(const f32 smpRate) {};

			virtual inline void SetSampleRate(const f32 inp_rate) {};

			virtual inline void SetParameter(const f64 &inp, const u32 &index) {};

			virtual inline f64 GetParameter(const u32 &index) { return 0.0; };

			virtual inline Plug_InfoData GetPlugInfo() { Plug_InfoData tmp; return tmp; };

			virtual inline void Run() {};

			virtual inline void RunSampleBlock() {};

			virtual inline void SetBlockSize(const u32 inp) {};

			bool runningOffline;
			f64 spRate;
			u32 oversampling_online;
			u32 oversampling_offline;
			u32 oversampling_current;
			u32 oversampling_old;
			f64 s_input[32];
			f64 s_output[32];

			BasePlugin() :
				runningOffline( false ),
				spRate( 44100.0 ),
				oversampling_online( 2u ),
				oversampling_offline( 2u ),
				oversampling_current( 2u ),
				oversampling_old( 2u )
			{
				for(u32 i = 0u; i < 32u; i++)
				{
					s_input[i] = 0.0;
					s_output[i] = 0.0;
				}
			};

			BasePlugin(const Base::BasePlugin &other) :
				runningOffline( false ),
				spRate( 44100.0 ),
				oversampling_online( 2u ),
				oversampling_offline( 2u ),
				oversampling_current( 2u ),
				oversampling_old( 2u )
			{
				for(u32 i = 0u; i < 32u; i++)
				{
					s_input[i] = 0.0;
					s_output[i] = 0.0;
				}
			};
		};

		class SCRFT_EXPORT Plug_ParameterList
		{
		public:
			virtual inline u32 GetNumberOfParameters() { return 0u; };

			virtual inline u32 GetNumberOfPresets() { return 0u; };

			virtual inline s32 GetID(const s32 index) { return 0; };

			virtual inline s32 GetVersionNumber() { return 0; };

			virtual inline void Reset() {};

			virtual inline void Reset(const u32 &preset_number) {};

			virtual inline void SetToPreset(const u32 &preset_number) {};

			virtual inline u32 GetCurrentPreset() { return 0u; };

			virtual inline void SetPresetName(const char* name, size_t length) {};

			virtual inline void GetPresetName(char *name, size_t length) {};

			virtual inline void GetPresetName(char *name, size_t length, const u32 &index) {};

			virtual inline void SetParameter(const u32 &index, const f64 &value) {};

			virtual inline f64 GetParameter(const u32 &index) { return 0.0; };

			virtual inline void GetParameterName(const u32 &index, char *name, size_t length) {};

			virtual inline void SetID() {};

			virtual inline void SetVersionInfo() {};

			virtual inline bool CompareID(const Plug_ParameterList &other) { return false; };

			Plug_ParameterList() {};

			Plug_ParameterList(const Plug_ParameterList &other) {};

			virtual Plug_ParameterList& operator=(const Plug_ParameterList &other)
			{
				return *this;
			};
		};
	} // namespace Base

	namespace Modules
	{
	}

	namespace Plugins
	{
	}
} // namespace ScorchCrafter

#endif // SCORCHCRAFTER_PLUGIN_BASE_HPP
