//=============================================================================
//
// ライト処理 [light.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CLight
{
public:
	CLight();	// デフォルトコンストラクタ
	~CLight();	// デフォルトデストラクタ
	HRESULT Init(D3DLIGHTTYPE Type, D3DCOLORVALUE Diffuse, D3DVECTOR Pos, D3DVECTOR Dir);	// カメラの初期化
	void Uninit(void);	// カメラの終了
	void Update(void);	// カメラの更新
	static CLight *Create(D3DLIGHTTYPE Type, D3DCOLORVALUE Diffuse, D3DVECTOR Pos, D3DVECTOR Dir);
	CLight *GetLight(void) { return this; }	// カメラの入手
private:
	D3DLIGHT9 m_Light;	// ライト
	static int m_nMaxNumber;	// ライトの数
	int m_nMyNumber;	// 自分の番号
};
#endif