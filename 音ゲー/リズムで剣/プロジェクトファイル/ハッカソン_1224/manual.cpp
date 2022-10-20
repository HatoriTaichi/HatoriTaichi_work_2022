//=============================================================================
//
// 説明画面 [manual.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "manual.h"
#include "manager.h"
#include "textureobj.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CManual::CManual()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CManual::~CManual()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CManual::Init(void)
{
	// 2Dポリゴンを生成
	CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), "RULEBG");
	CUiObj::Create(D3DXVECTOR3(SCREEN_WIDTH - 100.0f, SCREEN_HEIGHT - 50.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "BUCK");

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CManual::Uninit(void)
{
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CManual::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CManual::Draw(void)
{

}