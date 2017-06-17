#include "ScorchCrafter_Plugin.hpp"
#include "MagmaTouch.hpp"

#ifndef SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI
	#include "MagmaTouch_GUI.hpp"
#endif // SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI

#include "VstBase_2.hpp"

#include "audioeffect.cpp"
#include "audioeffectx.cpp"
#include "vstplugmain.cpp"

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
		return new Plugins::Reverb_MagmaTouch();
	};
	SCRFT_EXPORT Base::BasePlugin* SCRFT_CopyPlugin(const Base::BasePlugin *other)
	{
		return new Plugins::Reverb_MagmaTouch( *other );
	};

	SCRFT_EXPORT Base::Plug_ParameterList* SCRFT_CreateParameterList()
	{
		return new Plugins::Reverb_MagmaTouch_Params();
	};
	SCRFT_EXPORT Base::Plug_ParameterList* SCRFT_CopyPluginParameters(const Base::Plug_ParameterList *other)
	{
		return new Plugins::Reverb_MagmaTouch_Params( *other );
	};
}

using namespace ::ScorchCrafter;
using namespace ::ScorchCrafter::DataTypes;
using namespace ::ScorchCrafter::Base;
using namespace ::ScorchCrafter::Plugins;

class PlgEditor_SCplug;
class Scr_VST_Plugin;

#ifndef SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI

__declspec(dllexport) AEffGUIEditor* SCRFT_createEditor(AudioEffectX* effect)
{
	return new PlgEditor_SCplug( effect );
};
__declspec(dllexport) AEffGUIEditor* createEditor(AudioEffectX* effect)
{
	return new PlgEditor_SCplug( effect );
};

#endif

SCRFT_EXPORT AudioEffect* createEffectInstance(audioMasterCallback audioMaster)
{
	return new Scr_VST_Plugin( audioMaster );
}
