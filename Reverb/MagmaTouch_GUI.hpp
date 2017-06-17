#ifndef SCORCHCRAFTER_PLUGIN_GUI_JYKWRAKKER_H
#define SCORCHCRAFTER_PLUGIN_GUI_JYKWRAKKER_H

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

#include "Plugins\Reverb\MagmaTouch.h"

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
		CTag_None,
		CTag_Master_Volume,
		CTag_Gain,
		CTag_NoiseGate_Level,
		CTag_NoiseGate_Enable,
		CTag_EQ_Bass,
		CTag_EQ_Mids,
		CTag_EQ_Treble,
		CTag_EQ_Presence,
		CTag_EQ_Contour,
		CTag_Amp_Bright,
		CTag_Amp_Channel_1,
		CTag_Amp_Channel_2,
		CTag_Amp_Channel_3,
		CTag_Amp_Channel_4,
		CTag_Amp_Input_Boost,
		CTag_OverSample_Online_Up,
		CTag_OverSample_Online_Down,
		CTag_OverSample_Offline_Up,
		CTag_OverSample_Offline_Down,
		CTag_Max_Count
	};

	inline u32 CalculateSamplingValueFromFloat(const f32 inp);

	Plug_ParameterList* Params;

	const f64 noiseSetting_skew;
	const f64 noiseGate_min;
	const f64 noiseGate_max;

	CBitmap* pic_BG;
	CBitmap* pic_Knob;
	CBitmap* pic_Digits;
	CBitmap* pic_ButtonRed;
	CBitmap* pic_ButtonGreen;
	CBitmap* pic_ButtonBlue;
	CBitmap* pic_Blank;

	CView* gfx_View;

	CAnimKnob* ktl_Master;
	CAnimKnob* ktl_Gain;
	CAnimKnob* ktl_NoiseGate;
	CAnimKnob* ktl_EQ[5];

	CSpecialDigit* dgt_Master;
	CSpecialDigit* dgt_Gain;
	CSpecialDigit* dgt_NoiseGate;
	CSpecialDigit* dgt_NoiseGate_frac;
	CSpecialDigit* dgt_EQ[5];
	CSpecialDigit* dgt_Sampling_Online;
	CSpecialDigit* dgt_Sampling_Offline;
	CSpecialDigit* dgt_Version[4];

	COnOffButton* btn_InputBoost;
	COnOffButton* btn_AmpBright;
	COnOffButton* btn_AmpChannel[4];
	COnOffButton* btn_NoiseGateEnable;
	COnOffButton* btn_OverSamplingOnline_plus;
	COnOffButton* btn_OverSamplingOnline_minus;
	COnOffButton* btn_OverSamplingOffline_plus;
	COnOffButton* btn_OverSamplingOffline_minus;

	u32 sampling_online;
	u32 sampling_offline;
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
	Params( 0 ),
	noiseSetting_skew( 1.425 ),
	noiseGate_min( 12.0 ),
	noiseGate_max( 96.0 )
{
	Params = SCRFT_CreateParameterList();

	rect.left   = 0;
	rect.top    = 0;
	rect.right  = 800;
	rect.bottom = 384;
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
inline u32 PlgEditor_SCplug::CalculateSamplingValueFromFloat(const f32 inp)
{
	u32 value = 2;
	const f32 v_increment = 0.01f;

	if ( inp < v_increment )
		return value;

	bool val_found = false;
	f32 v_check = 0.005f;
	u32 value_accum = 3;
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

	pic_BG = new CBitmap("Jyk_new_BG_panel.png");
	pic_Knob = new CBitmap("ArcKnob_1_80x64.png");
	pic_Digits = new CBitmap("Digit_Numbers_160x16.png");
	pic_ButtonRed = new CBitmap("OnOff_Button_Red.png");
	pic_ButtonGreen = new CBitmap("OnOff_Button_Green.png");
	pic_ButtonBlue = new CBitmap("OnOff_Button_Blue.png");
	pic_Blank = new CBitmap("blank_16x16.png");

	gfx_View = new CView (frameSize);
	gfx_View->setBackground(pic_BG);
	nFrame->addView(gfx_View);

	const u32 prmCount = Params->GetNumberOfParameters();
	for (u32 i = 0; i < prmCount; i++)
		Params->SetParameter( i, ((AudioEffectX*)effect)->getParameter( (VstInt32) i ) );
/*
	ktl_Master = new CAnimKnob( CRect(24,272,104,336), this, CTag_Master_Volume, pic_Knob, CPoint(0,0) );
	ktl_Master->setValue( Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kMasterVol ) );
	nFrame->addView( ktl_Master );
	dgt_Master = new CSpecialDigit( CRect(32,336,96,352), this, CTag_None, 0, 4, NULL, NULL, 16, 16, pic_Digits );
	dgt_Master->setValue( int (Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kMasterVol ) * 1000) );
	nFrame->addView( dgt_Master );

	ktl_Gain = new CAnimKnob( CRect(104,272,184,336), this, CTag_Gain, pic_Knob, CPoint(0,0) );
	ktl_Gain->setValue( Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kGainControl ) );
	nFrame->addView( ktl_Gain );
	dgt_Gain = new CSpecialDigit( CRect(112,336,176,352), this, CTag_None, 0, 4, NULL, NULL, 16, 16, pic_Digits );
	dgt_Gain->setValue( int (Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kGainControl ) * 1000) );
	nFrame->addView( dgt_Gain );

	btn_AmpBright = new COnOffButton( CRect(192,256,208,272), this, CTag_Amp_Bright, pic_ButtonBlue );
	btn_InputBoost = new COnOffButton( CRect(192,272,208,288), this, CTag_Amp_Input_Boost, pic_ButtonBlue );
	btn_AmpBright->setValue( Params->GetParameter( Reverb_MagmaTouch_Params::kBright ) );
	btn_InputBoost->setValue( Params->GetParameter( Reverb_MagmaTouch_Params::kInputBoost ) );
	nFrame->addView( btn_AmpBright );
	nFrame->addView( btn_InputBoost );

	btn_AmpChannel[0] = new COnOffButton( CRect(192,320,208,336), this, CTag_Amp_Channel_1, pic_ButtonRed );
	btn_AmpChannel[1] = new COnOffButton( CRect(224,320,240,336), this, CTag_Amp_Channel_2, pic_ButtonRed );
	btn_AmpChannel[2] = new COnOffButton( CRect(256,320,272,336), this, CTag_Amp_Channel_3, pic_ButtonRed );
	btn_AmpChannel[3] = new COnOffButton( CRect(288,320,304,336), this, CTag_Amp_Channel_4, pic_ButtonRed );
	f32 chan_value[4] = { 0.f, 0.f, 0.f, 0.f };
	f32 val = Params->GetParameter( Reverb_MagmaTouch_Params::kAmpChan );
	if ( val < 0.05f ) chan_value[0] = 1.f;
	if ( (val >= 0.05f) && (val < 0.15f) ) chan_value[1] = 1.f;
	if ( (val >= 0.15f) && (val < 0.25f) ) chan_value[2] = 1.f;
	if ( (val >= 0.25f) && (val < 0.35f) ) chan_value[3] = 1.f;
	btn_AmpChannel[0]->setValue( chan_value[0] );
	btn_AmpChannel[1]->setValue( chan_value[1] );
	btn_AmpChannel[2]->setValue( chan_value[2] );
	btn_AmpChannel[3]->setValue( chan_value[3] );
	nFrame->addView( btn_AmpChannel[0] );
	nFrame->addView( btn_AmpChannel[1] );
	nFrame->addView( btn_AmpChannel[2] );
	nFrame->addView( btn_AmpChannel[3] );

	ktl_EQ[0] = new CAnimKnob( CRect(376,272,456,336), this, CTag_EQ_Bass, pic_Knob, CPoint(0,0) );
	ktl_EQ[1] = new CAnimKnob( CRect(456,272,536,336), this, CTag_EQ_Mids, pic_Knob, CPoint(0,0) );
	ktl_EQ[2] = new CAnimKnob( CRect(536,272,616,336), this, CTag_EQ_Treble, pic_Knob, CPoint(0,0) );
	ktl_EQ[3] = new CAnimKnob( CRect(616,272,696,336), this, CTag_EQ_Presence, pic_Knob, CPoint(0,0) );
	ktl_EQ[4] = new CAnimKnob( CRect(696,272,776,336), this, CTag_EQ_Contour, pic_Knob, CPoint(0,0) );
	ktl_EQ[0]->setValue( Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kEQBass ) );
	ktl_EQ[1]->setValue( Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kEQMid ) );
	ktl_EQ[2]->setValue( Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kEQTreble ) );
	ktl_EQ[3]->setValue( Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kEQPresence ) );
	ktl_EQ[4]->setValue( Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kEQContour ) );
	nFrame->addView( ktl_EQ[0] );
	nFrame->addView( ktl_EQ[1] );
	nFrame->addView( ktl_EQ[2] );
	nFrame->addView( ktl_EQ[3] );
	nFrame->addView( ktl_EQ[4] );
	dgt_EQ[0] = new CSpecialDigit( CRect(384,336,448,352), this, CTag_None, 0, 4, NULL, NULL, 16, 16, pic_Digits );
	dgt_EQ[1] = new CSpecialDigit( CRect(464,336,528,352), this, CTag_None, 0, 4, NULL, NULL, 16, 16, pic_Digits );
	dgt_EQ[2] = new CSpecialDigit( CRect(544,336,608,352), this, CTag_None, 0, 4, NULL, NULL, 16, 16, pic_Digits );
	dgt_EQ[3] = new CSpecialDigit( CRect(624,336,688,352), this, CTag_None, 0, 4, NULL, NULL, 16, 16, pic_Digits );
	dgt_EQ[4] = new CSpecialDigit( CRect(704,336,768,352), this, CTag_None, 0, 4, NULL, NULL, 16, 16, pic_Digits );
	dgt_EQ[0]->setValue( int (Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kEQBass ) * 1000) );
	dgt_EQ[1]->setValue( int (Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kEQMid ) * 1000) );
	dgt_EQ[2]->setValue( int (Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kEQTreble ) * 1000) );
	dgt_EQ[3]->setValue( int (Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kEQPresence ) * 1000) );
	dgt_EQ[4]->setValue( int (Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kEQContour ) * 1000) );
	nFrame->addView( dgt_EQ[0] );
	nFrame->addView( dgt_EQ[1] );
	nFrame->addView( dgt_EQ[2] );
	nFrame->addView( dgt_EQ[3] );
	nFrame->addView( dgt_EQ[4] );

	ktl_NoiseGate = new CAnimKnob( CRect(24,160,104,224), this, CTag_NoiseGate_Level, pic_Knob, CPoint(0,0) );
	ktl_NoiseGate->setValue( Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kNoiseFilter_Level ) );
	nFrame->addView( ktl_NoiseGate );
	dgt_NoiseGate = new CSpecialDigit( CRect(24,224,56,240), this, CTag_None, 0, 2, NULL, NULL, 16, 16, pic_Digits );
	dgt_NoiseGate_frac = new CSpecialDigit( CRect(72,224,104,240), this, CTag_None, 0, 2, NULL, NULL, 16, 16, pic_Digits );
	f64 noiseSetting = Params->GetParameter( (u32) Reverb_MagmaTouch_Params::kNoiseFilter_Level );
	noiseSetting = 1.0 - pow( 1.0 - noiseSetting, noiseSetting_skew );
	const f64 noiseGateThresh = (noiseGate_min * (1.0 - noiseSetting)) + (noiseGate_max * noiseSetting);
	const f64 noiseSetting_value = floor( noiseGateThresh );
	const f64 noiseSetting_frac = (noiseGateThresh * 100.0) - (noiseSetting_value * 100.0);
	dgt_NoiseGate->setValue( (int) noiseSetting_value );
	dgt_NoiseGate_frac->setValue( (int) noiseSetting_frac );
	nFrame->addView( dgt_NoiseGate );
	nFrame->addView( dgt_NoiseGate_frac );

	btn_NoiseGateEnable = new COnOffButton( CRect(112,176,128,192), this, CTag_NoiseGate_Enable, pic_ButtonGreen );
	btn_NoiseGateEnable->setValue( Params->GetParameter( Reverb_MagmaTouch_Params::kNoiseFilter_On ) );
	nFrame->addView( btn_NoiseGateEnable );

	sampling_online = CalculateSamplingValueFromFloat( (f32) Params->GetParameter( Reverb_MagmaTouch_Params::kOverSampling_On ) );
	sampling_offline = CalculateSamplingValueFromFloat( (f32) Params->GetParameter( Reverb_MagmaTouch_Params::kOverSampling_Off ) );
	dgt_Sampling_Online = new CSpecialDigit( CRect(598,176,630,192), this, CTag_None, 0, 2, NULL, NULL, 16, 16, pic_Digits );
	dgt_Sampling_Offline = new CSpecialDigit( CRect(598,192,630,208), this, CTag_None, 0, 2, NULL, NULL, 16, 16, pic_Digits );
	dgt_Sampling_Online->setValue( sampling_online );
	dgt_Sampling_Offline->setValue( sampling_offline );
	nFrame->addView( dgt_Sampling_Online );
	nFrame->addView( dgt_Sampling_Offline );

	btn_OverSamplingOnline_plus = new COnOffButton( CRect(576,176,592,192), this, CTag_OverSample_Online_Up, pic_Blank );
	btn_OverSamplingOnline_minus = new COnOffButton( CRect(560,176,576,192), this, CTag_OverSample_Online_Down, pic_Blank );
	btn_OverSamplingOffline_plus = new COnOffButton( CRect(576,192,592,208), this, CTag_OverSample_Offline_Up, pic_Blank );
	btn_OverSamplingOffline_minus = new COnOffButton( CRect(560,192,576,208), this, CTag_OverSample_Offline_Down, pic_Blank );
	btn_OverSamplingOnline_plus->setValue( 0.f );
	btn_OverSamplingOnline_minus->setValue( 0.f );
	btn_OverSamplingOffline_plus->setValue( 0.f );
	btn_OverSamplingOffline_minus->setValue( 0.f );
	nFrame->addView( btn_OverSamplingOnline_plus );
	nFrame->addView( btn_OverSamplingOnline_minus );
	nFrame->addView( btn_OverSamplingOffline_plus );
	nFrame->addView( btn_OverSamplingOffline_minus );

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
	pic_ButtonRed->forget();
	pic_ButtonGreen->forget();
	pic_ButtonBlue->forget();
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
/*
	if ( index == Reverb_MagmaTouch_Params::kMasterVol )
	{
		ktl_Master->setValue( value );
		dgt_Master->setValue( int (value * 1000) );
		ktl_Master->invalid();
		dgt_Master->invalid();
	} else
	if ( index == Reverb_MagmaTouch_Params::kGainControl )
	{
		ktl_Gain->setValue( value );
		dgt_Gain->setValue( int (value * 1000) );
		ktl_Gain->invalid();
		dgt_Gain->invalid();
	} else
	if ( index == Reverb_MagmaTouch_Params::kAmpChan )
	{
		f32 chan_value[4] = { 0.f, 0.f, 0.f, 0.f };
		const f32 val = value;
		if ( val < 0.05f ) chan_value[0] = 1.f;
		if ( (val >= 0.05f) && (val < 0.15f) ) chan_value[1] = 1.f;
		if ( (val >= 0.15f) && (val < 0.25f) ) chan_value[2] = 1.f;
		if ( (val >= 0.25f) && (val < 0.35f) ) chan_value[3] = 1.f;
		btn_AmpChannel[0]->setValue( chan_value[0] );
		btn_AmpChannel[1]->setValue( chan_value[1] );
		btn_AmpChannel[2]->setValue( chan_value[2] );
		btn_AmpChannel[3]->setValue( chan_value[3] );
		btn_AmpChannel[0]->invalid();
		btn_AmpChannel[1]->invalid();
		btn_AmpChannel[2]->invalid();
		btn_AmpChannel[3]->invalid();
	} else
	if ( index == Reverb_MagmaTouch_Params::kBright )
	{
		btn_AmpBright->setValue( value );
		btn_AmpBright->invalid();
	} else
	if ( index == Reverb_MagmaTouch_Params::kInputBoost )
	{
		btn_InputBoost->setValue( value );
		btn_InputBoost->invalid();
	} else
	if ( index == Reverb_MagmaTouch_Params::kEQBass )
	{
		ktl_EQ[0]->setValue( value );
		dgt_EQ[0]->setValue( int (value * 1000) );
		ktl_EQ[0]->invalid();
		dgt_EQ[0]->invalid();
	} else
	if ( index == Reverb_MagmaTouch_Params::kEQMid )
	{
		ktl_EQ[1]->setValue( value );
		dgt_EQ[1]->setValue( int (value * 1000) );
		ktl_EQ[1]->invalid();
		dgt_EQ[1]->invalid();
	} else
	if ( index == Reverb_MagmaTouch_Params::kEQTreble )
	{
		ktl_EQ[2]->setValue( value );
		dgt_EQ[2]->setValue( int (value * 1000) );
		ktl_EQ[2]->invalid();
		dgt_EQ[2]->invalid();
	} else
	if ( index == Reverb_MagmaTouch_Params::kEQPresence )
	{
		ktl_EQ[3]->setValue( value );
		dgt_EQ[3]->setValue( int (value * 1000) );
		ktl_EQ[3]->invalid();
		dgt_EQ[3]->invalid();
	} else
	if ( index == Reverb_MagmaTouch_Params::kEQContour )
	{
		ktl_EQ[4]->setValue( value );
		dgt_EQ[4]->setValue( int (value * 1000) );
		ktl_EQ[4]->invalid();
		dgt_EQ[4]->invalid();
	} else
	if ( index == Reverb_MagmaTouch_Params::kNoiseFilter_Level )
	{
		ktl_NoiseGate->setValue( value );
		ktl_NoiseGate->invalid();
		f64 noiseSetting = value;
		noiseSetting = 1.0 - pow( 1.0 - noiseSetting, noiseSetting_skew );
		const f64 noiseGateThresh = (noiseGate_min * (1.0 - noiseSetting)) + (noiseGate_max * noiseSetting);
		const f64 noiseSetting_value = floor( noiseGateThresh );
		const f64 noiseSetting_frac = (noiseGateThresh * 100.0) - (noiseSetting_value * 100.0);
		dgt_NoiseGate->setValue( (int) noiseSetting_value );
		dgt_NoiseGate_frac->setValue( (int) noiseSetting_frac );
		dgt_NoiseGate->invalid();
		dgt_NoiseGate_frac->invalid();
	} else
	if ( index == Reverb_MagmaTouch_Params::kNoiseFilter_On )
	{
		btn_NoiseGateEnable->setValue( value );
		btn_NoiseGateEnable->invalid();
	} else
	if ( index == Reverb_MagmaTouch_Params::kOverSampling_On )
	{
		const f32 smpl_value = (f32) Params->GetParameter( Reverb_MagmaTouch_Params::kOverSampling_On );
		sampling_online = CalculateSamplingValueFromFloat( smpl_value );
		dgt_Sampling_Online->setValue( sampling_online );
		dgt_Sampling_Online->invalid();
	} else
	if ( index == Reverb_MagmaTouch_Params::kOverSampling_Off )
	{
		const f32 smpl_value = (f32) Params->GetParameter( Reverb_MagmaTouch_Params::kOverSampling_Off );
		sampling_offline = CalculateSamplingValueFromFloat( smpl_value );
		dgt_Sampling_Offline->setValue( sampling_offline );
		dgt_Sampling_Offline->invalid();
	}	*/
}
inline void PlgEditor_SCplug::valueChanged(CControl* pControl)
{
	const u32 index = (u32) pControl->getTag();
/*
	if ( index == CTag_Master_Volume )
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kMasterVol, pControl->getValue() );
	else

	if ( index == CTag_Gain )
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kGainControl, pControl->getValue() );
	else

	if ( index == CTag_Amp_Bright )
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kBright, pControl->getValue() );
	else
	if ( index == CTag_Amp_Input_Boost )
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kInputBoost, pControl->getValue() );
	else

	if ( index == CTag_Amp_Channel_1 )
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kAmpChan, 0.0f );
	else
	if ( index == CTag_Amp_Channel_2 )
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kAmpChan, 0.1f );
	else
	if ( index == CTag_Amp_Channel_3 )
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kAmpChan, 0.2f );
	else
	if ( index == CTag_Amp_Channel_4 )
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kAmpChan, 0.3f );
	else

	if ( index == CTag_EQ_Bass )
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kEQBass, pControl->getValue() );
	else
	if ( index == CTag_EQ_Mids )
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kEQMid, pControl->getValue() );
	else
	if ( index == CTag_EQ_Treble )
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kEQTreble, pControl->getValue() );
	else
	if ( index == CTag_EQ_Presence )
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kEQPresence, pControl->getValue() );
	else
	if ( index == CTag_EQ_Contour )
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kEQContour, pControl->getValue() );
	else

	if ( index == CTag_NoiseGate_Level )
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kNoiseFilter_Level, pControl->getValue() );
	else
	if ( index == CTag_NoiseGate_Enable )
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kNoiseFilter_On, pControl->getValue() );
	else

	if ( index == CTag_OverSample_Online_Up )
	{
		sampling_online++;
		if ( sampling_online > 64 )
			sampling_online = 64;
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kOverSampling_On, f32 ((f32) (sampling_online - 2) * 0.01f ) );
	}
	else
	if ( index == CTag_OverSample_Online_Down )
	{
		sampling_online--;
		if ( sampling_online < 2)
			sampling_online = 2;
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kOverSampling_On, f32 ((f32) (sampling_online - 2) * 0.01f ) );
	}
	else
	if ( index == CTag_OverSample_Offline_Up )
	{
		sampling_offline++;
		if ( sampling_offline > 64 )
			sampling_offline = 64;
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kOverSampling_Off, f32 ((f32) (sampling_offline - 2) * 0.01f ) );
	}
	else
	if ( index == CTag_OverSample_Offline_Down )
	{
		sampling_offline--;
		if ( sampling_offline < 2)
			sampling_offline = 2;
		((AudioEffectX*)effect)->setParameter( (VstInt32) Reverb_MagmaTouch_Params::kOverSampling_Off, f32 ((f32) (sampling_offline - 2) * 0.01f ) );
	} */
}
inline void PlgEditor_SCplug::idle()
{
	AEffGUIEditor::idle();
}

#endif // SCORCHCRAFTER_PLUGIN_GUI_JYKWRAKKER_H
