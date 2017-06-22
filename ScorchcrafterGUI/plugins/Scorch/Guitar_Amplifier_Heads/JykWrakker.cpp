#include "ScorchCrafter_Plugin.hpp"
// #include "Plugins\Guitar_Amplifier_Heads\JykWrakker.hpp"
#include "JykWrakker.hpp"

#ifndef SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI
	#include "Plugins\Guitar_Amplifier_Heads\JykWrakker_GUI.hpp"
#endif // SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI

/*
#include "VstBase_2.hpp"

#include "audioeffect.cpp"
#include "audioeffectx.cpp"
#include "vstplugmain.cpp"
*/

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
		return new Plugins::GuitarAmpHead_JykWrakker();
	};
	SCRFT_EXPORT Base::BasePlugin* SCRFT_CopyPlugin(const Base::BasePlugin *other)
	{
		return new Plugins::GuitarAmpHead_JykWrakker( *other );
	};

	SCRFT_EXPORT Base::Plug_ParameterList* SCRFT_CreateParameterList()
	{
		return new Plugins::GuitarAmpHead_JykWrakker_Params();
	};
	SCRFT_EXPORT Base::Plug_ParameterList* SCRFT_CopyPluginParameters(const Base::Plug_ParameterList *other)
	{
		return new Plugins::GuitarAmpHead_JykWrakker_Params( *other );
	};
}

using namespace ::ScorchCrafter;
using namespace ::ScorchCrafter::DataTypes;
using namespace ::ScorchCrafter::Base;
using namespace ::ScorchCrafter::Plugins;

/*
class PlgEditor_SCplug;
class Scr_VST_Plugin;

#ifndef SCORCHCRAFTER_USE_NONSTANDARD_OR_NO_GUI

SCRFT_EXPORT AEffGUIEditor* SCRFT_createEditor(AudioEffectX* effect)
{
	return new PlgEditor_SCplug( effect );
};
SCRFT_EXPORT AEffGUIEditor* createEditor(AudioEffectX* effect)
{
	return new PlgEditor_SCplug( effect );
};

#endif

SCRFT_EXPORT AudioEffect* createEffectInstance(audioMasterCallback audioMaster)
{
	return new Scr_VST_Plugin( audioMaster );
}

*/