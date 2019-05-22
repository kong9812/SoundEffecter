//=============================================================================
//
// 波形データの書き出し処理 [waveOut.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _WAVE_OUT_H_
#define _WAVE_OUT_H_

#include "main.h"
#include "sound.h"
#include "basic.h"
#include "sound.h"
#include "Collider.h"
#include "soundControl.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 構造体宣言
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetWaveData(SOUND_TOOL *soundTool, char *oldPath, SOUND_PARAMETER parameter);


#endif