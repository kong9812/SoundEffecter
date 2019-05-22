//=============================================================================
//
// サウンドコントロール [soundControl.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _SOUND_CONTROL_
#define _SOUND_CONTROL_

#include "main.h"
#include "sound.h"
#include "soundEffect.h"
#include "buttonIcon.h"
#include "plot.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// パラメータの初期値
//-------------再生用-------------//
#define INIT_MAIN_VOL		(1.0f)		// メインボリュム
#define MAX_MAIN_VOL		(1.0f)
#define MIN_MAIN_VOL		(0.0f)

#define INIT_PAN_VOL		(0.0f)		// パンヴォリューム
#define MAX_PAN_VOL			(1.0f)
#define MIN_PAN_VOL			(-1.0f)

#define INIT_FREQ			(1.0f)		// (再生周波数)ピーチ
#define MAX_FREQ			(2.0f)
#define MIN_FREQ			(-1.0f)

//-------ディレイ＋リバーブ-------//
#define INIT_DELAY_REVERB	(false)		// ディレイ＋リバーブ

#define INIT_WET_VOL		(0.0f)		// ウェットボイスのボリューム
#define MAX_WET_VOL			(0.5f)
#define MIN_WET_VOL			(0.0f)

#define INIT_DRY_VOL		(0.0f)		// ドライボイスのボリューム
#define MAX_DRY_VOL			(0.5f)
#define MIN_DRY_VOL			(0.0f)

#define INIT_DELAY_TIME		(0.0f)		// ディレイタイム
#define MAX_DELAY_TIME		(2.0f)
#define MIN_DELAY_TIME		(0.0f)

#define INIT_REVERB_VOL		(0.0f)		// 残響のボリューム
#define MAX_REVERB_VOL		(0.5f)
#define MIN_REVERB_VOL		(0.0f)

//------------フェイド------------//
#define INIT_FADE			(false)		// フェイド

#define INIT_FADE_TIME		(0.0f)		// フェイドタイム
#define MAX_FADE_TIME		(10.0f)
#define MIN_FADE_TIME		(0.0f)

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct
{
	//--------再生用--------//
	float mainVol;		// メインボリュム			
	float panVol;		// パンヴォリューム
	float freq;			// (再生周波数)ピーチ

	//--ディレイ＋リバーブ--// 
	bool  delayReverb;	// ディレイ＋リバーブ
	float wetVol;		// ウェットボイスのボリューム
	float dryVol;		// ドライボイスのボリューム
	float delayTime;	// ディレイタイム		
	float reverbVol;	// 残響のボリューム 

	//-------フェイド-------//
	bool  fade;			// フェイド
	float fadeTime;		// フェイドタイム		

}SOUND_PARAMETER;				

//*****************************************************************************
// クラス
//*****************************************************************************
class SOUND_CONTROL
{
public:
	SOUND_CONTROL(HWND hWnd);			// コンストラクタ
	~SOUND_CONTROL();					// デストラクタ

	void soundControlProcess(int no, float percentage);		// プロセス

	float GetBalVolumeMeter(int no);						// ボリュームメーター

	// 音の書き出し
	void OutputWav(void);

	// soundを取得
	SOUND *GetSound(void) { return sound; };

private:
	SOUND				*sound;			// サウンド用
	SOUND_EFFECT		*soundEffect;	// サウンドエフェクト用
	SOUND_TOOL			soundTool;		// サウンド用

	SOUND_PARAMETER		soundParameter;	// パラメータ構造体

	float				tmpVolMeter;
	float				volMeter;
	int					frameCnt;
								
};
#endif