//=============================================================================
//
// ボタンのアイコン処理 [bottonIcon.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "buttonIcon.h"
#include "soundControl.h"


//=============================================================================
// プロトタイプ宣言
//=============================================================================
void SetSongName(void);		// 文字描画処理

//=============================================================================
// グローバル変数:
//=============================================================================
TEXTURE	background;								// 背景
TEXTURE buttonIconTexture[BUTTON_MAX];			// ボタン
TEXTURE buttonLightTexture[BUTTON_MAX];			// ボタンのライト
TEXTURE volumeMeterBar[VOLUME_METER_BAR_MAX];	// ボリュームメーターバー
TEXTURE outputButton;							// アウトプットボタン
TEXTURE	wavePlot;								// GNUPLOTの出力ボタン(波形)
LPD3DXFONT	soundName = NULL;					// フォントへのポインタ
int			SongFontCnt = 0;					// フォントカウンター

float buttonRadian[BUTTON_MAX];					// 角度(ラジアン)

int	  buttonUse;								// 使用中のボタン

SOUND_CONTROL *soundControl;					// サウンドコントロールクラス

//=============================================================================
// 初期化
//=============================================================================
HRESULT InitButtonIcon(int InitType, HWND hWnd)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		for (int i = 0; i < BUTTON_MAX; i++)
		{
			// 初期化
			volumeMeterBar[0].texture = NULL;
			volumeMeterBar[1].texture = NULL;
			outputButton.texture	  = NULL;
			wavePlot.texture		  = NULL;

			// テクスチャの読み込み
			LoadTexture(pDevice, &outputButton, TEXTURE_OUTPUT);
			
			// テクスチャの読み込み
			LoadTexture(pDevice, &buttonIconTexture[i], TEXTURE_BUTTON_ICON);

			// テクスチャの読み込み
			LoadTexture(pDevice, &buttonLightTexture[i], TEXTURE_BUTTON_LIGHT);

			// テクスチャの読込み
			LoadTexture(pDevice, &buttonLightTexture[i], TEXTURE_BUTTON_LIGHT);

			// テクスチャの読込み
			LoadTexture(pDevice, &background, TEXTURE_BACKGROUND);

			// フォント
			D3DXCreateFont(pDevice, 50, 25, 0, 0, FALSE, SHIFTJIS_CHARSET,
				OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &soundName);
			
		}
	}

	{// 他の初期化

		{// 背景
			background.pos	= BACKGROUND_POS;
			background.size = BACKGROUND_SIZE;
		}

		{// ボタン
			for (int i = 0; i < BUTTON_MAX; i++)
			{
				buttonIconTexture[i].rot	= BUTTON_ROT;		// 回転
				buttonIconTexture[i].size	= BUTTON_SIZE;		// サイズ
				buttonIconTexture[i].col	= BUTTON_COL;		// 色
				buttonRadian[i]				= BUTTON_RADIAN;	// 角度(ラジアン)

				buttonLightTexture[i].size	= BUTTON_LIGHT_SIZE;// サイズ
				buttonLightTexture[i].col	= BUTTON_OFF_COL;	// 色(オフ)
			}

			buttonIconTexture[BUTTON_LIST::BUTTON_MAIN_VOL].pos			= BUTTON_POS_0;		// 位置0
			buttonLightTexture[BUTTON_LIST::BUTTON_MAIN_VOL].pos		= BUTTON_POS_0;		// 位置0
			buttonIconTexture[BUTTON_LIST::BUTTON_MAIN_VOL].rot			= BUTTON_ROT_0;		// 回転0

			buttonIconTexture[BUTTON_LIST::BUTTON_PAN_VOL].pos			= BUTTON_POS_1;		// 位置1
			buttonLightTexture[BUTTON_LIST::BUTTON_PAN_VOL].pos			= BUTTON_POS_1;		// 位置1
			buttonIconTexture[BUTTON_LIST::BUTTON_PAN_VOL].rot			= BUTTON_ROT_1;		// 回転1

			buttonIconTexture[BUTTON_LIST::BUTTON_FREQ].pos				= BUTTON_POS_2;		// 位置2
			buttonLightTexture[BUTTON_LIST::BUTTON_FREQ].pos			= BUTTON_POS_2;		// 位置2
			buttonIconTexture[BUTTON_LIST::BUTTON_FREQ].rot				= BUTTON_ROT_2;		// 回転2

			buttonIconTexture[BUTTON_LIST::BUTTON_DELAY_REVERB].pos		= BUTTON_POS_3;		// 位置3
			buttonLightTexture[BUTTON_LIST::BUTTON_DELAY_REVERB].pos	= BUTTON_POS_3;		// 位置3

			buttonIconTexture[BUTTON_LIST::BUTTON_FADE].pos				= BUTTON_POS_4;		// 位置4
			buttonLightTexture[BUTTON_LIST::BUTTON_FADE].pos			= BUTTON_POS_4;		// 位置4

			buttonIconTexture[BUTTON_LIST::BUTTON_WET_VOL].pos			= BUTTON_POS_5;		// 位置5
			buttonLightTexture[BUTTON_LIST::BUTTON_WET_VOL].pos			= BUTTON_POS_5;		// 位置5

			buttonIconTexture[BUTTON_LIST::BUTTON_DRY_VOL].pos			= BUTTON_POS_6;		// 位置6
			buttonLightTexture[BUTTON_LIST::BUTTON_DRY_VOL].pos			= BUTTON_POS_6;		// 位置6

			buttonIconTexture[BUTTON_LIST::BUTTON_DELAY_TIME].pos		= BUTTON_POS_7;		// 位置7
			buttonLightTexture[BUTTON_LIST::BUTTON_DELAY_TIME].pos		= BUTTON_POS_7;		// 位置7

			buttonIconTexture[BUTTON_LIST::BUTTON_REVERB_VOL].pos		= BUTTON_POS_8;		// 位置8
			buttonLightTexture[BUTTON_LIST::BUTTON_REVERB_VOL].pos		= BUTTON_POS_8;		// 位置8

			buttonIconTexture[BUTTON_LIST::BUTTON_FADE_TIME].pos		= BUTTON_POS_9;		// 位置9
			buttonLightTexture[BUTTON_LIST::BUTTON_FADE_TIME].pos		= BUTTON_POS_9;		// 位置9

			buttonUse													= INIT_BUTTON;		// 使用中のボタン
		}

		{// ボリュームメーターバー
			for (int i = 0; i < VOLUME_METER_BAR_MAX; i++)
			{
				volumeMeterBar[i].col = VOLUME_METER_BAR_COL_0;
				volumeMeterBar[i].size = VOLUME_METER_BAR_SIZE;
			}
			volumeMeterBar[0].pos = VOLUME_METER_BAR_POS_0;
			volumeMeterBar[1].pos = VOLUME_METER_BAR_POS_1;
		}

		{// アウトプットボタン
			outputButton.pos	= OUTPUT_BUTTON_POS;
			outputButton.size	= OUTPUT_BUTTON_SIZE;
			outputButton.col	= OUTPUT_BUTTON_COL_0;
		}

		{
			wavePlot.pos		= PLOT_POS;
			wavePlot.size		= PLOT_SIZE;
		}
	}

	for (int i = 0; i < BUTTON_MAX; i++)
	{
		// 頂点フォーマット
		MakeVtxCenterData(&buttonIconTexture[i]);

		// 頂点フォーマット
		MakeVtxCenterData(&buttonLightTexture[i]);
	}

	// 頂点フォーマット
	MakeVtx4PointData(&volumeMeterBar[0]);
	MakeVtx4PointData(&volumeMeterBar[1]);
	MakeVtx4PointData(&outputButton);
	MakeVtx4PointData(&wavePlot);
	MakeVtx4PointData(&background);

	// サウンドコントロール
	soundControl = new SOUND_CONTROL(hWnd);

	// テクスチャの読込み
	LoadTexture(pDevice, &wavePlot, TEXTURE_PLOT);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitButtonIcon(void)
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		SAFE_RELEASE(buttonIconTexture[i].texture)
		SAFE_RELEASE(buttonLightTexture[i].texture)
	}

	SAFE_RELEASE(volumeMeterBar[0].texture)
	SAFE_RELEASE(volumeMeterBar[0].texture)
	SAFE_RELEASE(outputButton.texture)
	SAFE_RELEASE(wavePlot.texture)
	SAFE_RELEASE(background.texture)
	
	// サウンドコントロール
	delete soundControl;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateButtonIcon(HWND hWnd)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 当たり判定
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		// パラメータボタンの当たり判定
		if (CheckHitBB(GetMousePos(hWnd), buttonIconTexture[i].pos, CURSOR_SIZE / 32, buttonIconTexture[i].size))
		{
			if ((IsMouseLeftTriggered() == true))
			{
				buttonUse = i;
			}
		}

		// 色処理
		buttonLightTexture[i].col = BUTTON_OFF_COL;
	}

	// 書き出しボタンの当たり判定
	if (CheckHitBB(GetMousePos(hWnd), outputButton.pos, CURSOR_SIZE / 32, outputButton.size))
	{
		// 色処理
		outputButton.col = OUTPUT_BUTTON_COL_1;

		if ((IsMouseLeftTriggered() == true))
		{
			// 書き出し
			soundControl->OutputWav();
		
			SAFE_RELEASE(wavePlot.texture)

			// テクスチャの読込み
			LoadTexture(pDevice, &wavePlot, TEXTURE_PLOT);
		}
	}

	// 色処理
	outputButton.col = OUTPUT_BUTTON_COL_0;

	if ((buttonUse != BUTTON_LIST::BUTTON_DELAY_REVERB) && (buttonUse != BUTTON_LIST::BUTTON_FADE))
	{
		// 右回転
		if (buttonIconTexture[buttonUse].rot.z < BUTTON_MAX_RADIAN)
		{
			// 右ボタン
			if (GetKeyboardPress(DIK_RIGHT))
			{
				buttonIconTexture[buttonUse].rot.z += BUTTON_MOVE;

				// プロセス
				soundControl->soundControlProcess(buttonUse,
					RadianToPercentage(buttonIconTexture[buttonUse].rot.z));
			}
		}

		// 左回転
		if (buttonIconTexture[buttonUse].rot.z > BUTTON_MIN_RADIAN)
		{
			// 左ボタン
			if (GetKeyboardPress(DIK_LEFT))
			{
				buttonIconTexture[buttonUse].rot.z -= BUTTON_MOVE;

				// プロセス
				soundControl->soundControlProcess(buttonUse,
					RadianToPercentage(buttonIconTexture[buttonUse].rot.z));
			}
		}
	}
	else
	{
		// 右回転
		if (buttonIconTexture[buttonUse].rot.z < BUTTON_MAX_RADIAN)
		{
			// 右ボタン
			if (GetKeyboardPress(DIK_RIGHT))
			{
				buttonIconTexture[buttonUse].rot.z += BUTTON_NO_OFF;

				// プロセス
				soundControl->soundControlProcess(buttonUse,
					RadianToPercentage(buttonIconTexture[buttonUse].rot.z));
			}
		}

		// 左回転
		if (buttonIconTexture[buttonUse].rot.z > BUTTON_MIN_RADIAN)
		{
			// 左ボタン
			if (GetKeyboardPress(DIK_LEFT))
			{
				buttonIconTexture[buttonUse].rot.z -= BUTTON_NO_OFF;

				// プロセス
				soundControl->soundControlProcess(buttonUse,
					RadianToPercentage(buttonIconTexture[buttonUse].rot.z));
			}
		}
	}

	// 使用中のボタン色
	buttonLightTexture[buttonUse].col = BUTTON_ON_COL;

	// ボリュームメーター
	for (int i = 0; i < VOLUME_METER_BAR_MAX; i++)
	{
		if (soundControl->GetBalVolumeMeter(i) >= 0.5f)
		{
			volumeMeterBar[i].col = VOLUME_METER_BAR_COL_1;
		}
		else
		{
			volumeMeterBar[i].col = VOLUME_METER_BAR_COL_0;
		}
	}
}

//=============================================================================
// 文字描画処理
//=============================================================================
void SetSongName(void)
{
	// フォント用
	RECT rect = { 0, 600, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[CHAR_MAX];

	// 曲名
	sprintf(str, _T("%s"), soundControl->GetSound()->GetFileName());
	soundName->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawButtonIcon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 描画
	DrawNormalObject(pDevice, background);

	// ボタンのアイコン
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		// 描画
		DrawRotCenterObject(pDevice, buttonIconTexture[i], buttonRadian[i], buttonIconTexture[i].size.x);

		// 描画
		DrawColorCenterObject(pDevice, buttonLightTexture[i]);
	}

	// 描画
	DrawGaugeObject(pDevice, volumeMeterBar[0], soundControl->GetBalVolumeMeter(0), GAUGE_DIRECTION::GAUGE_RIGHT);
	// 描画
	DrawGaugeObject(pDevice, volumeMeterBar[1], soundControl->GetBalVolumeMeter(1), GAUGE_DIRECTION::GAUGE_RIGHT);
	// 描画
	DrawColorCenterObject(pDevice, outputButton);
	// 描画
	DrawNormalObject(pDevice, wavePlot);

	// 文字描画処理
	SetSongName();

}

//=============================================================================
// ボタンの情報を取得
//=============================================================================
TEXTURE GetButtonTexture(int no)
{
	return buttonIconTexture[no];
}