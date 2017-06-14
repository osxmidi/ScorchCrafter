#ifndef __SCORCHCRAFTER_VST_2_Plugin_Base__
#define __SCORCHCRAFTER_VST_2_Plugin_Base__

#include "ScorchCrafter_Plugin.hpp"

namespace ScorchCrafter
{
	namespace Base
	{
		struct Plug_InfoData;
		class BasePlugin;
		class Plug_ParameterList;
	}

	extern Base::BasePlugin* SCRFT_CreatePlugin();
	extern Base::BasePlugin* SCRFT_CopyPlugin(const Base::BasePlugin *other);

	extern Base::Plug_ParameterList* SCRFT_CreateParameterList();
	extern Base::Plug_ParameterList* SCRFT_CopyPluginParameters(const Base::Plug_ParameterList *other);

	extern const int SCRFT_PLG_NUM_PROGRAMS;
	extern const int SCRFT_PLG_NUM_PARAMETERS;
}

using namespace ScorchCrafter;
using namespace ScorchCrafter::DataTypes;
using namespace ScorchCrafter::Base;
using namespace ScorchCrafter::Plugins;

#ifndef SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI
	#include "../sdk_deps/zlib/zlib.h"
	#include "../sdk_deps/libpng/png.h"
#endif // SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI

#include "aeffectx.h"
#include "audioeffectx.h"
#include "vstfxstore.h"

 #ifndef SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI
#include "aeffeditor.h"
 #endif

#ifndef SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI
	#include "vstgui.h"

	#include "vstcontrols.h"
	#include "aeffguieditor.h"
#endif // SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI

class PlgEditor_SCplug;

#ifndef SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI
extern AEffGUIEditor* SCRFT_createEditor(AudioEffectX* effect);
#endif

//!-------------------------------------------------------------------------------------------------------
class SCRFT_EXPORT Scr_VST_Plugin : public AudioEffectX
{
public:
	Scr_VST_Plugin(audioMasterCallback audioMaster);
	explicit Scr_VST_Plugin(const Scr_VST_Plugin &other);
	virtual Scr_VST_Plugin& operator= (const Scr_VST_Plugin &other);
	virtual ~Scr_VST_Plugin();

//! Processing
	virtual void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
	virtual void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

//! Program
	virtual void setProgram(VstInt32 program);
	virtual VstInt32 getProgram ();
	virtual void setProgramName (char* name);
	virtual void getProgramName (char* name);

//! Parameters
	virtual void setParameter (VstInt32 index, float value);
	virtual float getParameter (VstInt32 index);
	virtual void getParameterLabel (VstInt32 index, char* label);
	virtual void getParameterDisplay (VstInt32 index, char* text);
	virtual void getParameterName (VstInt32 index, char* text);
	virtual bool getProgramNameIndexed (VstInt32 category, VstInt32 index, char* text);
	virtual bool beginSetProgram ();
	virtual bool endSetProgram ();

	virtual void open();
	virtual void close();
	virtual void suspend();
	virtual void resume();
	virtual bool setBypass(bool onOff);
	virtual bool setProcessPrecision (VstInt32 precision) { return true; };

//!	Plug-in Info
	virtual bool getEffectName (char* name);
	virtual bool getVendorString (char* text);
	virtual bool getProductString (char* text);
	virtual VstInt32 getVendorVersion ();
	virtual VstInt32 canDo(char* text);

//!	Special
	virtual void setSampleRate (float smplRate);
	virtual void setBlockSize (VstInt32 blockSize);

protected:
	char programName[kVstMaxProgNameLen + 1];
	char tmpName[127];
	Plug_ParameterList* Params;
	u32 numParameters;
	Base::BasePlugin* Plg;
	Plug_InfoData PlgInfo;
	bool bypassActive;
};

#include <cmath>

/*
//! -------------------------------------------------------------------------------------------------------
inline __declspec(dllexport) AudioEffect* createEffectInstance(audioMasterCallback audioMaster)
{
	return new Scr_VST_Plugin( audioMaster );
}
*/
//!-------------------------------------------------------------------------------------------------------
Scr_VST_Plugin::Scr_VST_Plugin(audioMasterCallback audioMaster) : AudioEffectX (
		audioMaster,
		SCRFT_PLG_NUM_PROGRAMS,
		SCRFT_PLG_NUM_PARAMETERS),
	Params( 0 ),
	numParameters( 0u ),
	Plg( 0 ),
	bypassActive( false )
{
	if ( Params )
		delete Params;
	Params = 0;
	if ( Plg )
		delete Plg;
	Plg = 0;

	Plg = SCRFT_CreatePlugin();
	PlgInfo = Plg->GetPlugInfo();

	Params = SCRFT_CreateParameterList();

	numParameters = Params->GetNumberOfParameters();

	setNumInputs( PlgInfo.numInputs );
	setNumOutputs( PlgInfo.numOutputs );

	setUniqueID( CCONST(
					PlgInfo.ID[0],
					PlgInfo.ID[1],
					PlgInfo.ID[2],
					PlgInfo.ID[3] )
				);
	canProcessReplacing( true );
	canDoubleReplacing( true );
	noTail( false );
//	programsAreChunks( false );
	isSynth( false );

	Params->GetPresetName( tmpName, 127 );
	vst_strncpy( programName, tmpName, kVstMaxProgNameLen );

#ifndef SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI
	setEditor( (AEffGUIEditor*)SCRFT_createEditor( this ) );
#endif
	if (getCurrentProcessLevel() == 4)
		Plg->runningOffline = true;
	else
		Plg->runningOffline = false;

	float srate = getSampleRate();
	if ( (!srate) || (srate < 44100.f) )
		srate = 44100.f; // Minimum sample rate supported
	if ( srate > 16777216.f )
		srate = 16777216.f; // Maximum sample rate supported (allows for oversampling well over 64x with base rate of 192,000 Hz, and oversampling is capped at 64x, so this really should be enough...)
	Plg->Init( srate );

	Plg->SetBlockSize( (u32) blockSize );

	Params->Reset();
	for (u32 i = 0; i < numParameters; i++)
		Plg->SetParameter( Params->GetParameter( i ), i );

	Plg->SetSampleRate( srate );

	Plg->RunSampleBlock();
}
Scr_VST_Plugin::Scr_VST_Plugin(const Scr_VST_Plugin &other) : AudioEffectX (
		((Scr_VST_Plugin)other).audioMaster,
		SCRFT_PLG_NUM_PROGRAMS,
		SCRFT_PLG_NUM_PARAMETERS),
	Params( 0 ),
	numParameters( 0u ),
	Plg( 0 ),
	bypassActive( false )
{
	if ( Params )
		delete Params;
	Params = 0;
	if ( Plg )
		delete Plg;
	Plg = 0;

	if ( ((Scr_VST_Plugin)other).Plg )
		Plg = SCRFT_CopyPlugin( ((Scr_VST_Plugin)other).Plg );
	else
		Plg = SCRFT_CreatePlugin();
	PlgInfo = Plg->GetPlugInfo();

	if ( ((Scr_VST_Plugin)other).Params )
		Params = SCRFT_CopyPluginParameters( ((Scr_VST_Plugin)other).Params );
	else
		Params = SCRFT_CreateParameterList();

	numParameters = Params->GetNumberOfParameters();

	setNumInputs( PlgInfo.numInputs );
	setNumOutputs( PlgInfo.numOutputs );

	setUniqueID( CCONST(
					PlgInfo.ID[0],
					PlgInfo.ID[1],
					PlgInfo.ID[2],
					PlgInfo.ID[3] )
				);
	canProcessReplacing( true );
	canDoubleReplacing( true );
	noTail( false );
//	programsAreChunks( false );
	isSynth( false );

	Params->GetPresetName( tmpName, 127 );
	vst_strncpy( programName, tmpName, kVstMaxProgNameLen );

#ifndef SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI
	setEditor( (AEffGUIEditor*)SCRFT_createEditor( this ) );
#endif
	if (getCurrentProcessLevel() == 4)
		Plg->runningOffline = true;
	else
		Plg->runningOffline = false;

	float srate = getSampleRate();
	if ( (!srate) || (srate < 44100.f) )
		srate = 44100.f; // Minimum sample rate supported
	if ( srate > 16777216.f )
		srate = 16777216.f; // Maximum sample rate supported (allows for oversampling well over 64x with base rate of 192,000 Hz, and oversampling is capped at 64x, so this really should be enough...)
	Plg->Init( srate );

	Plg->SetBlockSize( (u32) blockSize );

	Params->Reset();
	for (u32 i = 0; i < numParameters; i++)
		Plg->SetParameter( Params->GetParameter( i ), i );

	Plg->SetSampleRate( srate );

	Plg->RunSampleBlock();
}
Scr_VST_Plugin& Scr_VST_Plugin::operator= (const Scr_VST_Plugin &other)
{
	if ( !((Scr_VST_Plugin)other).Plg )
		return *this;
	if ( !((Scr_VST_Plugin)other).Params )
		return *this;

	if ( Params )
		delete Params;
	Params = 0;
	if ( Plg )
		delete Plg;
	Plg = 0;

	Plg = SCRFT_CopyPlugin( ((Scr_VST_Plugin)other).Plg );

	Params = SCRFT_CopyPluginParameters( ((Scr_VST_Plugin)other).Params );

	return *this;
}
Scr_VST_Plugin::~Scr_VST_Plugin()
{
	if ( Params )
		delete Params;
	Params = 0;
	if ( Plg )
		delete Plg;
	Plg = 0;
}
inline bool Scr_VST_Plugin::setBypass(bool onOff)
{
	bypassActive = onOff;

	return true;
}
inline void Scr_VST_Plugin::open()
{
	if ( Plg )
	{
		if (getCurrentProcessLevel() == 4)
			Plg->runningOffline = true;
		else
			Plg->runningOffline = false;

		Plg->RunSampleBlock();
	}
}
inline void Scr_VST_Plugin::close()
{
	//x
}
inline void Scr_VST_Plugin::suspend()
{
	//x
}
inline void Scr_VST_Plugin::resume()
{
	if ( Plg )
	{
		if (getCurrentProcessLevel() == 4)
			Plg->runningOffline = true;
		else
			Plg->runningOffline = false;

		Plg->RunSampleBlock();
	}
}
inline void Scr_VST_Plugin::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames)
{
	if ( Plg )
	{
		if (getCurrentProcessLevel() == 4) Plg->runningOffline = true;
		else Plg->runningOffline = false;

		Plg->RunSampleBlock();
	}

    VstInt32 sfr = 0;

	if ( (!bypassActive) && (Plg) )
	{
		while (sfr < sampleFrames)
		{
			for (int chan = 0; chan < PlgInfo.numInputs; chan++)
				Plg->s_input[chan] = (f64) inputs[chan][sfr];

			Plg->Run();

			for (int chan = 0; chan < PlgInfo.numOutputs; chan++)
				outputs[chan][sfr] = (float) Plg->s_output[chan];

			sfr++;
		}
	} else
	{
		while (sfr < sampleFrames)
		{
			for (int chan = 0; chan < PlgInfo.numOutputs; chan++)
				outputs[chan][sfr] = 0.f;

			sfr++;
		}
	}

	sampleFrames = 0;
}
inline void Scr_VST_Plugin::processDoubleReplacing (double** inputs, double** outputs, VstInt32 sampleFrames)
{
	if ( Plg )
	{
		if (getCurrentProcessLevel() == 4) Plg->runningOffline = true;
		else Plg->runningOffline = false;

		Plg->RunSampleBlock();
	}

	VstInt32 sfr = 0;

	if ( (!bypassActive) && (Plg) )
	{
		while (sfr < sampleFrames)
		{
			for (int chan = 0; chan < PlgInfo.numInputs; chan++)
				Plg->s_input[chan] = (f64) inputs[chan][sfr];

			Plg->Run();

			for (int chan = 0; chan < PlgInfo.numOutputs; chan++)
				outputs[chan][sfr] = (double) Plg->s_output[chan];

			sfr++;
		}
	} else
	{
		while (sfr < sampleFrames)
		{
			for (int chan = 0; chan < PlgInfo.numOutputs; chan++)
				outputs[chan][sfr] = 0.0;

			sfr++;
		}
	}

	sampleFrames = 0;
}
inline void Scr_VST_Plugin::setProgram (VstInt32 program)
{
	if ( (!Plg) || (!Params) )
		return;

	if ( program < 0 )
		return;

	Params->SetToPreset( (u32) program );

	for(u32 prm_index = 0u; prm_index < (u32) numParameters; prm_index++)
		Plg->SetParameter( Params->GetParameter( prm_index ), prm_index );

#ifndef SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI

	if( editor )
	{
		for(u32 prm_index = 0u; prm_index < (u32) numParameters; prm_index++)
			((AEffGUIEditor*)editor)->setParameter( prm_index, Params->GetParameter( prm_index ) );
	}

#endif

}
inline VstInt32 Scr_VST_Plugin::getProgram()
{
	if ( !Params )
		return 0;

	return (VstInt32) Params->GetCurrentPreset();
}
inline void Scr_VST_Plugin::setBlockSize (VstInt32 blockSize)
{
	if ( !Plg )
		return;

	AudioEffectX::setBlockSize(blockSize);

	Plg->SetBlockSize( (u32) blockSize );
}
inline void Scr_VST_Plugin::setProgramName (char* name)
{
	if ( !Params )
		return;

	Params->SetPresetName( name, kVstMaxProgNameLen );

	vst_strncpy (programName, name, kVstMaxProgNameLen);
}
inline void Scr_VST_Plugin::getProgramName (char* name)
{
	if ( !Params )
		return;

	Params->GetPresetName( tmpName, 127 );

	vst_strncpy(name, tmpName, kVstMaxProgNameLen);
}
inline bool Scr_VST_Plugin::getProgramNameIndexed (VstInt32 category, VstInt32 index, char* text)
{
	if ( !Params )
		return false;

	Params->GetPresetName( tmpName, 127, (u32) index );

	vst_strncpy(text, tmpName, kVstMaxProgNameLen);

	return true;
}
inline bool Scr_VST_Plugin::beginSetProgram ()
{
	return false;
}
inline bool Scr_VST_Plugin::endSetProgram ()
{
	return false;
}
inline void Scr_VST_Plugin::setParameter (VstInt32 index, float value)
{
	if ( (!Plg) || (!Params) )
		return;

	Plg->SetParameter( (f64) value, (u32) index );
	Params->SetParameter( (u32) index, (f64) value );

#ifndef SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI

	// If the GUI is up and running, pass the value to the GUI
	if(editor)
	{
		((AEffGUIEditor*)editor)->setParameter( index, value );
	}

#endif

}
inline float Scr_VST_Plugin::getParameter(VstInt32 index)
{
	if ( Params )
		return (float) Params->GetParameter( (u32) index );

	return 0.f;
}
inline void Scr_VST_Plugin::getParameterLabel (VstInt32 index, char* label)
{
	vst_strncpy (label, " ", kVstMaxParamStrLen);
}
inline void Scr_VST_Plugin::getParameterDisplay (VstInt32 index, char* text)
{
	if(index < numParameters)
	{
		float2string( Params->GetParameter( (u32) index ), text, kVstMaxParamStrLen );
	}
}
inline void Scr_VST_Plugin::getParameterName (VstInt32 index, char* text)
{
	Params->GetParameterName( (u32) index, tmpName, 15 );

	if (index < numParameters)
	{
		vst_strncpy( text, tmpName, kVstMaxParamStrLen );
	}
}
inline bool Scr_VST_Plugin::getEffectName (char* name)
{
	vst_strncpy(name, PlgInfo.plugin_name, kVstMaxEffectNameLen);
	return true;
}
inline bool Scr_VST_Plugin::getProductString (char* text)
{
	vst_strncpy(text, PlgInfo.plugin_ID_string, kVstMaxProductStrLen);
	return true;
}
inline bool Scr_VST_Plugin::getVendorString (char* text)
{
	vst_strncpy(text, "ScorchCrafter", kVstMaxVendorStrLen);
	return true;
}
inline VstInt32 Scr_VST_Plugin::getVendorVersion ()
{
	return VstInt32 ( PlgInfo.version );
}
inline void Scr_VST_Plugin::setSampleRate (float smplRate)
{
	if ( !Plg )
		return;

	if ( (!smplRate) || (smplRate < 44100.f) )
		smplRate = 44100.f; // Minimum sample rate supported
	if ( smplRate > 16777216.f )
		smplRate = 16777216.f; // Maximum sample rate supported (allows for oversampling well over 64x with base rate of 192,000 Hz, and oversampling is capped at 64x, so this really should be enough...)

	Plg->SetSampleRate( smplRate );
}
inline VstInt32 Scr_VST_Plugin::canDo (char* text)
{
	if (!strcmp (text, "receiveVstTimeInfo"))
		return -1;
	else
	if (!strcmp (text, "receiveVstEvents"))
		return -1;
	else
	if (!strcmp (text, "receiveVstMidiEvent"))
		return -1;
	else
	if (!strcmp (text, "midiProgramNames"))
		return -1;

	return 0;	// 0 = don't know / not specified
}

#endif // __SCORCHCRAFTER_VST_2_Plugin_Base__
