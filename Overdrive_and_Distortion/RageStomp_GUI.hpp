#ifndef SCORCHCRAFTER_PLUGIN_GUI_RAGESTOMP_H
#define SCORCHCRAFTER_PLUGIN_GUI_RAGESTOMP_H

#include "ScorchCrafter_Plugin.h"

namespace ScorchCrafter
{
	namespace Base
	{
		struct Plug_InfoData;
		class BasePlugin;
		class Plug_ParameterList;
	}

	extern Base::Plug_ParameterList* SCRFT_CreateParameterList();

	extern const int SCRFT_PLG_NUM_PROGRAMS;
	extern const int SCRFT_PLG_NUM_PARAMETERS;
}

using namespace ::ScorchCrafter;
using namespace ::ScorchCrafter::DataTypes;
using namespace ::ScorchCrafter::Base;
using namespace ::ScorchCrafter::Plugins;

#include "../sdk_deps/zlib/zlib.h"
#include "../sdk_deps/libpng/png.h"

#include "aeffectx.h"
#include "audioeffectx.h"
#include "vstfxstore.h"

#include "aeffeditor.h"
#include "vstgui.h"

#include "vstcontrols.h"
#include "aeffguieditor.h"

#include "Plugins\Overdrive_and_Distortion\RageStomp.h"

using namespace VSTGUI;

using namespace ::ScorchCrafter::Plugins;

class __declspec(dllexport) PlgEditor_SCplug : public AEffGUIEditor, public CControlListener
{
public:
	PlgEditor_SCplug(void* ptr);
	virtual ~PlgEditor_SCplug();

	// from AEffGUIEditor
	virtual inline bool open(void* ptr);
	virtual inline void close();
	virtual inline void setParameter(VstInt32 index, float value);

	// from CControlListener
	virtual inline void valueChanged(CControl* pControl);

	virtual inline void idle();

protected:
	enum ControlTags
	{
		CTag_None						= 0,
		CTag_Master_Volume,
		CTag_Gain,
		CTag_Tone,
		CTag_Input,
		CTag_FxOn,
		CTag_FxActive,
		CTag_OverSample_Online_Up,
		CTag_OverSample_Online_Down,
		CTag_OverSample_Offline_Up,
		CTag_OverSample_Offline_Down,
		CTag_Max_Count
	};

	inline s32 CalculateSamplingValueFromFloat(const f32 inp);

	Plug_ParameterList* Params;

	CBitmap* pic_BG;
	CBitmap* pic_Knob;
	CBitmap* pic_Digits;
	CBitmap* pic_ButtonGreen;
	CBitmap* pic_ButtonStomp;
	CBitmap* pic_Blank;

	CView* gfx_View;

	CAnimKnob* ktl_Master;
	CAnimKnob* ktl_Gain;
	CAnimKnob* ktl_Input;
	CAnimKnob* ktl_Tone;

	CSpecialDigit* dgt_Master;
	CSpecialDigit* dgt_Gain;
	CSpecialDigit* dgt_Input;
	CSpecialDigit* dgt_Tone;
	CSpecialDigit* dgt_Sampling_Online;
	CSpecialDigit* dgt_Sampling_Offline;
//	CSpecialDigit* dgt_Version[4];

	CKickButton* btn_Stomp;
	COnOffButton* btn_FxActive;
	COnOffButton* btn_OverSamplingOnline_plus;
	COnOffButton* btn_OverSamplingOnline_minus;
	COnOffButton* btn_OverSamplingOffline_plus;
	COnOffButton* btn_OverSamplingOffline_minus;

	s32 sampling_online;
	s32 sampling_offline;
};
/*
//------------------------------------------------------------------------------------
inline __declspec(dllexport) AEffGUIEditor* SCRFT_createEditor(AudioEffectX* effect)
{
	return new PlgEditor_SCplug( effect );
};
*/
//------------------------------------------------------------------------------------
PlgEditor_SCplug::PlgEditor_SCplug(void* ptr) :
	AEffGUIEditor( ptr ),
	Params( 0 )
{
	Params = SCRFT_CreateParameterList();

	rect.left   = 0;
	rect.top    = 0;
	rect.right  = 256;
	rect.bottom = 376;
}
PlgEditor_SCplug::~PlgEditor_SCplug()
{
	if ( Params )
		delete Params;
	Params = 0;

	if ( frame )
	{
		CFrame* oldFrame = frame;
		frame = 0;
		if ( oldFrame )
			oldFrame->forget();
	}
}
inline s32 PlgEditor_SCplug::CalculateSamplingValueFromFloat(const f32 inp)
{
	s32 value = 2;
	const f32 v_increment = 0.01f;

	if ( inp < v_increment )
		return value;

	bool val_found = false;
	f32 v_check = 0.005f;
	s32 value_accum = 3;
	while ( (!val_found) && (v_check < 1.005f) )
	{
		if ( (inp >= v_check) && (inp < (v_check + v_increment)) )
		{
			value = value_accum;
			val_found = true;

			break;
		}

		value_accum++;
		v_check += v_increment;
	}

	if ( value < 2 )
		value = 2;
	if ( value > 64 )
		value = 64;

	return value;
}
inline bool PlgEditor_SCplug::open(void* ptr)
{
	if ( !Params )
		return false;

	AEffGUIEditor::open(ptr);

	CRect frameSize (0, 0, rect.right, rect.bottom);
	CFrame *nFrame = new CFrame (frameSize, ptr, this);

	pic_BG = new CBitmap("Rage_Stomp.png");
	pic_Knob = new CBitmap("mini_knob_2a.png");
	pic_Digits = new CBitmap("Digit_Numbers_160x16.png");
	pic_ButtonGreen = new CBitmap("OnOff_Button_Green.png");
	pic_ButtonStomp = new CBitmap("RgStmp_Bttn.png");
	pic_Blank = new CBitmap("blank_16x16.png");

	gfx_View = new CView (frameSize);
	gfx_View->setBackground(pic_BG);
	nFrame->addView(gfx_View);

	const u32 prmCount = Params->GetNumberOfParameters();
	for (u32 i = 0; i < prmCount; i++)
		Params->SetParameter( i, ((AudioEffectX*)effect)->getParameter( (VstInt32) i ) );

	ktl_Master = new CAnimKnob( CRect(156,144,188,176), this, CTag_Master_Volume, pic_Knob, CPoint(0,0) );
	ktl_Master->setValue( Params->GetParameter( (u32) DistortionFX_RageStomp_Params::kMasterVol ) );
	nFrame->addView( ktl_Master );
	dgt_Master = new CSpecialDigit( CRect(148,179,196,195), this, CTag_None, 0, 3, NULL, NULL, 16, 16, pic_Digits );
	dgt_Master->setValue( int ( f64 ( Params->GetParameter( (u32) DistortionFX_RageStomp_Params::kMasterVol ) * 200.0 ) ) );
	nFrame->addView( dgt_Master );

	ktl_Gain = new CAnimKnob( CRect(68,80,100,112), this, CTag_Gain, pic_Knob, CPoint(0,0) );
	ktl_Gain->setValue( Params->GetParameter( (u32) DistortionFX_RageStomp_Params::kGainControl ) );
	nFrame->addView( ktl_Gain );
	dgt_Gain = new CSpecialDigit( CRect(60,115,108,131), this, CTag_None, 0, 3, NULL, NULL, 16, 16, pic_Digits );
	dgt_Gain->setValue( int ( f64 ( Params->GetParameter( (u32) DistortionFX_RageStomp_Params::kGainControl ) * 500.0 ) ) );
	nFrame->addView( dgt_Gain );

	ktl_Tone = new CAnimKnob( CRect(156,80,188,112), this, CTag_Tone, pic_Knob, CPoint(0,0) );
	ktl_Tone->setValue( Params->GetParameter( (u32) DistortionFX_RageStomp_Params::kTone ) );
	nFrame->addView( ktl_Tone );
	dgt_Tone = new CSpecialDigit( CRect(148,115,196,131), this, CTag_None, 0, 3, NULL, NULL, 16, 16, pic_Digits );
	dgt_Tone->setValue( int ( f64 ( Params->GetParameter( (u32) DistortionFX_RageStomp_Params::kTone ) * 100.0 ) ) );
	nFrame->addView( dgt_Tone );

	ktl_Input = new CAnimKnob( CRect(68,144,100,176), this, CTag_Input, pic_Knob, CPoint(0,0) );
	ktl_Input->setValue( Params->GetParameter( (u32) DistortionFX_RageStomp_Params::kInputBoost ) );
	nFrame->addView( ktl_Input );
	dgt_Input = new CSpecialDigit( CRect(60,179,108,195), this, CTag_None, 0, 3, NULL, NULL, 16, 16, pic_Digits );
	const f64 val_input_boost = Params->GetParameter( (u32) DistortionFX_RageStomp_Params::kInputBoost );
	dgt_Input->setValue( int ( f64 (val_input_boost * val_input_boost * 400.0) ) );
	nFrame->addView( dgt_Input );

	btn_Stomp = new CKickButton( CRect(0,216,256,376), this, CTag_FxOn, pic_ButtonStomp );
	btn_FxActive = new COnOffButton( CRect(120,82,136,98), this, CTag_FxActive, pic_ButtonGreen );
	btn_Stomp->setValue( 0.0f );
	btn_FxActive->setValue( Params->GetParameter( (u32) DistortionFX_RageStomp_Params::kStompOnOff ) );
	nFrame->addView( btn_Stomp );
	nFrame->addView( btn_FxActive );

	sampling_online = CalculateSamplingValueFromFloat( (f32) Params->GetParameter( DistortionFX_RageStomp_Params::kOverSampling_On ) );
	sampling_offline = CalculateSamplingValueFromFloat( (f32) Params->GetParameter( DistortionFX_RageStomp_Params::kOverSampling_Off ) );
	dgt_Sampling_Online = new CSpecialDigit( CRect(59,43,91,59), this, CTag_None, 0, 2, NULL, NULL, 16, 16, pic_Digits );
	dgt_Sampling_Offline = new CSpecialDigit( CRect(165,43,630,197), this, CTag_None, 0, 2, NULL, NULL, 16, 16, pic_Digits );
	dgt_Sampling_Online->setValue( sampling_online );
	dgt_Sampling_Offline->setValue( sampling_offline );
	nFrame->addView( dgt_Sampling_Online );
	nFrame->addView( dgt_Sampling_Offline );

	btn_OverSamplingOnline_plus = new COnOffButton( CRect(91,43,107,59), this, CTag_OverSample_Online_Up, pic_Blank );
	btn_OverSamplingOnline_minus = new COnOffButton( CRect(43,43,59,59), this, CTag_OverSample_Online_Down, pic_Blank );
	btn_OverSamplingOffline_plus = new COnOffButton( CRect(197,43,213,59), this, CTag_OverSample_Offline_Up, pic_Blank );
	btn_OverSamplingOffline_minus = new COnOffButton( CRect(149,43,165,59), this, CTag_OverSample_Offline_Down, pic_Blank );
	btn_OverSamplingOnline_plus->setValue( 0.f );
	btn_OverSamplingOnline_minus->setValue( 0.f );
	btn_OverSamplingOffline_plus->setValue( 0.f );
	btn_OverSamplingOffline_minus->setValue( 0.f );
	nFrame->addView( btn_OverSamplingOnline_plus );
	nFrame->addView( btn_OverSamplingOnline_minus );
	nFrame->addView( btn_OverSamplingOffline_plus );
	nFrame->addView( btn_OverSamplingOffline_minus );

/*
	dgt_Version[0] = new CSpecialDigit( CRect(368,224,400,240), this, CTag_None, 0, 2, NULL, NULL, 16, 16, pic_Digits );
	dgt_Version[1] = new CSpecialDigit( CRect(416,224,448,240), this, CTag_None, 0, 2, NULL, NULL, 16, 16, pic_Digits );
	dgt_Version[2] = new CSpecialDigit( CRect(464,224,496,240), this, CTag_None, 0, 2, NULL, NULL, 16, 16, pic_Digits );
	dgt_Version[3] = new CSpecialDigit( CRect(512,224,544,240), this, CTag_None, 0, 2, NULL, NULL, 16, 16, pic_Digits );
	dgt_Version[0]->setValue( SC_PLG_VER_A );
	dgt_Version[1]->setValue( SC_PLG_VER_B );
	dgt_Version[2]->setValue( SC_PLG_VER_C );
	dgt_Version[3]->setValue( SC_PLG_VER_D );
	nFrame->addView( dgt_Version[0] );
	nFrame->addView( dgt_Version[1] );
	nFrame->addView( dgt_Version[2] );
	nFrame->addView( dgt_Version[3] );
*/

	frame = nFrame;

	setKnobMode(kLinearMode);

	pic_BG->forget();
	pic_Knob->forget();
	pic_Digits->forget();
	pic_ButtonGreen->forget();
	pic_ButtonStomp->forget();
	pic_Blank->forget();

	return true;
}
inline void PlgEditor_SCplug::close()
{
	if ( frame )
	{
		CFrame* oldFrame = frame;
		frame = 0;
		if ( oldFrame )
			oldFrame->forget();
	}
}
inline void PlgEditor_SCplug::setParameter(VstInt32 index, float value)
{
	Params->SetParameter( (u32) index, value );

	if ( !frame )
		return;

	if ( index == DistortionFX_RageStomp_Params::kMasterVol )
	{
		ktl_Master->setValue( value );
		dgt_Master->setValue( int (f64 (value * 200.0)) );
		ktl_Master->invalid();
		dgt_Master->invalid();
	} else
	if ( index == DistortionFX_RageStomp_Params::kGainControl )
	{
		ktl_Gain->setValue( value );
		dgt_Gain->setValue( int (f64 (value * 500.0)) );
		ktl_Gain->invalid();
		dgt_Gain->invalid();
	} else
	if ( index == DistortionFX_RageStomp_Params::kTone )
	{
		ktl_Tone->setValue( value );
		dgt_Tone->setValue( int (f64 (value * 100.0)) );
		ktl_Tone->invalid();
		dgt_Tone->invalid();
	} else
	if ( index == DistortionFX_RageStomp_Params::kInputBoost )
	{
		ktl_Input->setValue( value );
		const f64 val_input_boost = value * value * 400.0;
		dgt_Input->setValue( int (val_input_boost) );
		ktl_Input->invalid();
		dgt_Input->invalid();
	} else
	if ( index == DistortionFX_RageStomp_Params::kStompOnOff )
	{
		btn_FxActive->setValue( value );
		btn_Stomp->invalid();
		btn_FxActive->invalid();
	} else
	if ( index == DistortionFX_RageStomp_Params::kOverSampling_On )
	{
		const f32 smpl_value = (f32) Params->GetParameter( DistortionFX_RageStomp_Params::kOverSampling_On );
		sampling_online = CalculateSamplingValueFromFloat( smpl_value );
		dgt_Sampling_Online->setValue( sampling_online );
		dgt_Sampling_Online->invalid();
	} else
	if ( index == DistortionFX_RageStomp_Params::kOverSampling_Off )
	{
		const f32 smpl_value = (f32) Params->GetParameter( DistortionFX_RageStomp_Params::kOverSampling_Off );
		sampling_offline = CalculateSamplingValueFromFloat( smpl_value );
		dgt_Sampling_Offline->setValue( sampling_offline );
		dgt_Sampling_Offline->invalid();
	}
};
inline void PlgEditor_SCplug::valueChanged(CControl* pControl)
{
	const s32 index = (s32) pControl->getTag();

	if ( index == CTag_Master_Volume )
		((AudioEffectX*)effect)->setParameter( (VstInt32) DistortionFX_RageStomp_Params::kMasterVol, pControl->getValue() );
	else
	if ( index == CTag_Gain )
		((AudioEffectX*)effect)->setParameter( (VstInt32) DistortionFX_RageStomp_Params::kGainControl, pControl->getValue() );
	else
	if ( index == CTag_Tone )
		((AudioEffectX*)effect)->setParameter( (VstInt32) DistortionFX_RageStomp_Params::kTone, pControl->getValue() );
	else
	if ( index == CTag_Input )
		((AudioEffectX*)effect)->setParameter( (VstInt32) DistortionFX_RageStomp_Params::kInputBoost, pControl->getValue() );
	else
	if ( index == CTag_FxOn )
	{
		if ( pControl->getValue() > 0.5f )
		{
			if ( Params->GetParameter( DistortionFX_RageStomp_Params::kStompOnOff ) > 0.50 )
				((AudioEffectX*)effect)->setParameter( (VstInt32) DistortionFX_RageStomp_Params::kStompOnOff, 0.0f );
			else
				((AudioEffectX*)effect)->setParameter( (VstInt32) DistortionFX_RageStomp_Params::kStompOnOff, 1.0f );
		}
	}
	else
	if ( index == CTag_FxActive )
		((AudioEffectX*)effect)->setParameter( (VstInt32) DistortionFX_RageStomp_Params::kStompOnOff, pControl->getValue() );
	else
	if ( index == CTag_OverSample_Online_Up )
	{
		sampling_online++;
		if ( sampling_online > 64 )
			sampling_online = 64;
		((AudioEffectX*)effect)->setParameter( (VstInt32) DistortionFX_RageStomp_Params::kOverSampling_On, f32 ((f32) (sampling_online - 2) * 0.01f ) );
	}
	else
	if ( index == CTag_OverSample_Online_Down )
	{
		sampling_online--;
		if ( sampling_online < 2)
			sampling_online = 2;
		((AudioEffectX*)effect)->setParameter( (VstInt32) DistortionFX_RageStomp_Params::kOverSampling_On, f32 ((f32) (sampling_online - 2) * 0.01f ) );
	}
	else
	if ( index == CTag_OverSample_Offline_Up )
	{
		sampling_offline++;
		if ( sampling_offline > 64 )
			sampling_offline = 64;
		((AudioEffectX*)effect)->setParameter( (VstInt32) DistortionFX_RageStomp_Params::kOverSampling_Off, f32 ((f32) (sampling_offline - 2) * 0.01f ) );
	}
	else
	if ( index == CTag_OverSample_Offline_Down )
	{
		sampling_offline--;
		if ( sampling_offline < 2)
			sampling_offline = 2;
		((AudioEffectX*)effect)->setParameter( (VstInt32) DistortionFX_RageStomp_Params::kOverSampling_Off, f32 ((f32) (sampling_offline - 2) * 0.01f ) );
	}
};
inline void PlgEditor_SCplug::idle()
{
	AEffGUIEditor::idle();
};

#endif // SCORCHCRAFTER_PLUGIN_GUI_RAGESTOMP_H
