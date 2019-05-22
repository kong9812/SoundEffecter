//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include "LoadSoundClass.h"
#include <xaudio2.h>
#pragma comment (lib, "xaudio2.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SOUND_INIT_SUCCEEDED				(3)
#define SOUND_DEFAULT_VOLUME				(1.0f)
#define SOUND_LOOP_CNT_NOPE					(XAUDIO2_NO_LOOP_REGION)
#define SOUND_LOOP_CNT_INFINITE				(XAUDIO2_LOOP_INFINITE)

//*****************************************************************************
//構造体宣言
//*****************************************************************************
typedef struct
{
	IXAudio2SourceVoice *sourceVoice;		// 変更しないでください! DONT CHANGE ANYTHING!
	IXAudio2SubmixVoice *mainSubmixVoice;	// 変更しないでください! DONT CHANGE ANYTHING!
	IXAudio2SubmixVoice *DrySubmixVoice;	// 変更しないでください! DONT CHANGE ANYTHING!
	IXAudio2SubmixVoice *WetSubmixVoice;	// 変更しないでください! DONT CHANGE ANYTHING!
	WAV_FILE			wavFmt;				// 変更しないでください! DONT CHANGE ANYTHING!
	bool				isPlay;				// 変更しないでください! DONT CHANGE ANYTHING!
	int					loopCnt;			// ループ用カウンター
}SOUND_BASE;

typedef struct
{
	float				freqPich;			// ピーチ
	
}SOUND_SECONDARY;

typedef struct
{
	SOUND_BASE		svtBase;			// SVTのベース部分
	SOUND_SECONDARY	svtSecondary;		// SVTの基本パラメータ

}SOUND_TOOL;

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class SOUND
{
public:
	SOUND(void);	// 初期化
	~SOUND(void);	// 終了処理

	// ロードサウンド関数
	IXAudio2SourceVoice *LoadXAudio2Voice(HWND hWnd, SOUND_TOOL *svt);

	// 初期化の結果(True:成功 False:失敗)
	bool InitCheck();

	// マスターボイスを取得
	IXAudio2MasteringVoice *GetMasterVoice(void);

	// 再生
	HRESULT PlayVoice(SOUND_TOOL *svt);

	// 再生
	HRESULT StopVoice(SOUND_TOOL *svt);

	// 一時停止
	HRESULT PauseVoice(SOUND_TOOL *svt);

	// メインボリュム
	HRESULT SetMainVolume(SOUND_TOOL *svt, float volume);

	// パンボリューム
	HRESULT SetPanVolume(SOUND_TOOL *svt, float panVolume);

	// (frequency ratio)ピーチ
	HRESULT SetPitch(SOUND_TOOL *svt,float pitch);
	float	GetPitch(SOUND_TOOL *svt);

	// WAVファイルを取得
	SAI_LOAD_WAV *GetWavFile(void) { return wavFile; };

	// ファイル名
	char *GetFileName(void) { return fileName; };

private:
	SAI_LOAD_WAV			*wavFile;					// wavファイルの読み込み用クラス

	IXAudio2MasteringVoice	*masteringVoice = NULL;		// マスターボイス
	IXAudio2				*xAudio2		= NULL;		// XAudio2のインターフェイス
	
	int						initCheck		= 0;		// 初期化の結果
	float					*channelVolume	= NULL;		// ボリューム
	char					fileName[CHAR_MAX];			// サウンドの名前
	char					soundPath[CHAR_MAX];		// サウンドファイルのパス
};

#endif