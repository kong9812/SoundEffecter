//=============================================================================
//
// プロット処理 [plot.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _PLOT_H_
#define _PLOT_H_

#include "sound.h"
#include "basic.h"
#include "input.h"
#include "sound.h"
#include "Collider.h"
#include "soundControl.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// GNUPLOTの残留コマンド
#define GNUPLOT_PRESIST			" -persist"

// 初期パスからセーブフォルダまでのパス
#define SAVE_PATH				"\\data\\GNUPLOT"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool OpenGnuplot(HWND hWnd);												// GNUPLOTの読み込み
void OutputWaveGnuplot(SOUND_TOOL soundTool, char *path, short *otherWave);	// プロット

#endif