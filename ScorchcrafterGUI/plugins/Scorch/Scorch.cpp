/*
 * DISTRHO Plugin Framework (DPF)
 * Copyright (C) 2012-2015 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
 
#define kVstMaxProgNameLen 24

#define kVstMaxParamStrLen 8


#define SCRFT_STATIC 1

#define SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI 1

#define SCORCHCRAFTER_COMPILE_64 1
 
#include <cmath>

#include "DistrhoPlugin.hpp"

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


START_NAMESPACE_DISTRHO

int getCurrentProcessLevel()
{
return 0;
}


// -----------------------------------------------------------------------------------------------------------

class Scorch : public Plugin
{
public:
    Scorch()
        : Plugin(14, 42, 0), // 1 parameter
	Params( 0 ),
	numParameters( 0u ),
	Plg( 0 ),
	bypassActive( false )
    {
    
    	float srate = getSampleRate();
    	
        // allocates buffer
        sampleRateChanged(srate);
        
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
	
	Params->GetPresetName( tmpName, 127 );
	strncpy( programName, tmpName, kVstMaxProgNameLen );


		if ( (!srate) || (srate < 44100.f) )
		srate = 44100.f; // Minimum sample rate supported
	if ( srate > 16777216.f )
		srate = 16777216.f; // Maximum sample rate supported (allows for oversampling well over 64x with base rate of 192,000 Hz, and oversampling is capped at 64x, so this really should be enough...)
	Plg->Init( srate );

     	Params->Reset();
	for (u32 i = 0; i < numParameters; i++)
		Plg->SetParameter( Params->GetParameter( i ), i );

	Plg->SetSampleRate( srate ); 

	Plg->RunSampleBlock();
        
    }

    ~Scorch() override
    {
	if ( Params )
		delete Params;
	Params = 0;
	if ( Plg )
		delete Plg;
	Plg = 0;
    }

protected:
   /* --------------------------------------------------------------------------------------------------------
    * Information */

   /**
      Get the plugin label.
      This label is a short restricted name consisting of only _, a-z, A-Z and 0-9 characters.
    */
    const char* getLabel() const override
    {
        return "Scorchcrafter";
    }

   /**
      Get an extensive comment/description about the plugin.
    */
    const char* getDescription() const override
    {
        return "Scorchcrafter Amp Sim";
    }

   /**
      Get the plugin author/maker.
    */
    const char* getMaker() const override
    {
        return "Scorchcrafter";
    }

   /**
      Get the plugin homepage.
    */
    const char* getHomePage() const override
    {
        return " ";
    }

   /**
      Get the plugin license name (a single line of text).
      For commercial plugins this should return some short copyright information.
    */
    const char* getLicense() const override
    {
        return "GPL";
    }

   /**
      Get the plugin version, in hexadecimal.
    */
    uint32_t getVersion() const override
    {
        return d_version(1, 0, 0);
    }

   /**
      Get the plugin unique Id.
      This value is used by LADSPA, DSSI and VST plugin formats.
    */
    int64_t getUniqueId() const override
    {
        return d_cconst('S', '1', '2', '0');
    }

   /* --------------------------------------------------------------------------------------------------------
    * Init */
    
 void initProgramName(uint32_t index, String& programName) override
{

}
   
   
   /**
      Initialize the parameter @a index.
      This function will be called once, shortly after the plugin is created.
    */
    
    void initParameter(uint32_t index, Parameter& parameter) override
    {
                       
 	Params->GetParameterName( (u32) index, tmpName, 15 );

	if (index < numParameters)
	{
        parameter.name = tmpName;

        parameter.symbol = tmpName;
	}                      

        parameter.hints  = kParameterIsAutomable;

        parameter.ranges.def = 1.0f;
        
        parameter.ranges.min = 0.0f;
    
        parameter.ranges.max = 1.0f;

    }

   /* --------------------------------------------------------------------------------------------------------
    * Internal data */

   /**
      Get the current value of a parameter.
      The host may call this function from any context, including realtime processing.
    */
    float getParameterValue(uint32_t index) const override
    {
	if ( Params )
		return (float) Params->GetParameter( (u32) index );

	return 0.f;
    }

   /**
      Change a parameter value.
      The host may call this function from any context, including realtime processing.
      When a parameter is marked as automable, you must ensure no non-realtime operations are performed.
      @note This function will only be called for parameter inputs.
    */
    void setParameterValue(uint32_t index, float value) override
    {
	if ( (!Plg) || (!Params) )
		return;

        if((index == 0) || (index == 1))
                return;

	Plg->SetParameter( (f64) value, (u32) index );
	Params->SetParameter( (u32) index, (f64) value );
    }
        
    void loadProgram(uint32_t program) override
    {
	if ( (!Plg) || (!Params) )
		return;

	if ( program < 0 )
		return;

	Params->SetToPreset( (u32) program );

	 for(u32 prm_index = 0u; prm_index < (u32) numParameters; prm_index++)
		Plg->SetParameter( Params->GetParameter( prm_index ), prm_index );

    } 


uint32_t getProgramx() override
{

	if ( !Params )
	return 0;

	return (u32) Params->GetCurrentPreset();
}

void setProgramNamex (char* name) override
{
	if ( !Params )
	return;

	Params->SetPresetName( name, kVstMaxProgNameLen );

	strncpy (programName, name, kVstMaxProgNameLen);
}

void getProgramNamex (char* name) override
{
	if ( !Params )
	return;

	Params->GetPresetName( tmpName, 127 );

	strncpy(name, tmpName, kVstMaxProgNameLen);
}

bool getProgramNameIndexedx (uint32_t category, uint32_t index, char* text) override
{
	if ( !Params )
	return false;

	Params->GetPresetName( tmpName, 127, (u32) index );

	strncpy(text, tmpName, kVstMaxProgNameLen);

	return true;
}


   /* --------------------------------------------------------------------------------------------------------
    * Audio/MIDI Processing */

   /**
      Run/process function for plugins without MIDI input.
      @note Some parameters might be null if there are no audio inputs or outputs.
    */
    void run(const float** inputs, float** outputs, uint32_t sampleFrames) override
    {
	if ( Plg )
	{
		if (getCurrentProcessLevel() == 4) Plg->runningOffline = true;
		else Plg->runningOffline = false;

		Plg->RunSampleBlock();
	}

    uint32_t  sfr = 0;

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

   /* --------------------------------------------------------------------------------------------------------
    * Callbacks (optional) */

   /**
      Optional callback to inform the plugin about a sample rate change.
      This function will only be called when the plugin is deactivated.
    */
    void sampleRateChanged(double smplRate) override
    {
	if ( !Plg )
	return;

	if ( (!smplRate) || (smplRate < 44100.f) )
		smplRate = 44100.f; // Minimum sample rate supported
	if ( smplRate > 16777216.f )
		smplRate = 16777216.f; // Maximum sample rate supported (allows for oversampling well over 64x with base rate of 192,000 Hz, and oversampling is capped at 64x, so this really should be enough...)

	Plg->SetSampleRate( (float)smplRate );
    }

    // -------------------------------------------------------------------------------------------------------

protected:
	char programName[kVstMaxProgNameLen + 1];
	char tmpName[127];
	Plug_ParameterList* Params;
	u32 numParameters;
	Base::BasePlugin* Plg;
	Plug_InfoData PlgInfo;
	bool bypassActive;

   /**
      Set our plugin class as non-copyable and add a leak detector just in case.
    */
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Scorch)
};

/* ------------------------------------------------------------------------------------------------------------
 * Plugin entry point, called by DPF to create a new plugin instance. */

Plugin* createPlugin()
{
    return new Scorch();
}

// -----------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
