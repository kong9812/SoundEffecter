//=============================================================================
//
// サウンドエフェクト処理 [soundEffect.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _SOUND_EFFECT_H_
#define _SOUND_EFFECT_H_

#include "main.h"
#include "SaiDelay.h"
#include "SaiFadeIn.h"
#include <xapobase.h>
#pragma comment (lib, "xapobase.lib")
#include <xaudio2fx.h>

//*****************************************************************************
// 定数定義
//*****************************************************************************
enum EFFECT_CHAIN
{
	EFFECT_CHAIN_SOURCE,
	EFFECT_CHAIN_MASTER,
	EFFECT_CHAIN_MAX
};

enum SOURCE_VOICE_EFFECT
{
	SOURCE_EFFECT_DELAY,
	SOURCE_EFFECT_FADE_IN,
	SOURCE_EFFECT_MAX
};

enum MASTER_VOICE_EFFECT
{
	MASTER_EFFECT_VOLUME_METER,
	MASTER_EFFECT_MAX
};


//*****************************************************************************
// クラス
//*****************************************************************************
class SOUND_EFFECT
{
public:

	// コンストラクタ
	SOUND_EFFECT(SOUND_TOOL *soundTool,IXAudio2MasteringVoice *masterVoice);
	// デストラクタ
	~SOUND_EFFECT(void);		

	// エフェクト
	HRESULT SetEffect(SOUND_TOOL *soundTool, int no, float percentage);

	// ボリュームメーター
	float GetVolumeMeter(int no);

	// パラメータ構造体を取得
	SAI_APO_DELAY GetDelayParmeters(void) { return delayParameters; };
	bool GetDelayState(void) { return delayUse; };
	SAI_APO_FADE_IN GetFadeParameters(void) { return fadeParameters; };
	bool GetFadeState(void) { return fadeUse; };

private:
	IXAudio2MasteringVoice *tmpMasterVoice;	// マスターボイス

	XAUDIO2_EFFECT_CHAIN		chain[2];					// エフェクトチェン
	XAUDIO2_EFFECT_DESCRIPTOR	masterDescriptor;			// エフェクトディスクリプタ
	XAUDIO2_EFFECT_DESCRIPTOR	sourceDescriptor[2];		// エフェクトディスクリプタ

	SAI_APO_DELAY	delayParameters;		// パラメータ構造体
	bool delayUse;
	SAI_APO_FADE_IN fadeParameters;			// パラメータ構造体
	bool fadeUse;

	XAUDIO2FX_VOLUMEMETER_LEVELS volumeMeter;	// ボリュームメーター

};

#endif