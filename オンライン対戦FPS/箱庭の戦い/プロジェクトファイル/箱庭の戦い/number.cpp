//=============================================================================
//
// 数処理 [number.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "number.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CNumber::CNumber(LAYER_TYPE Layer) : CScene2D(Layer)
{
	
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CNumber::~CNumber()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CNumber::Init(void)
{
	CScene2D::SetTexType(m_Type);	// テクスチャを設定
	CScene2D::Init();	// 初期化
	CScene2D::SetPos(m_Pos);	// 位置の設定
	CScene2D::SetSize(m_Size);	// サイズの設定

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CNumber::Uninit(void)
{
	// 破棄
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CNumber::Update(void)
{

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CNumber::Draw(void)
{
	// 描画
	CScene2D::Draw();
}

//=============================================================================
// ゲッダー
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string Type)
{
	CNumber *pNumber = NULL;	// 数のポインタ

	// NULLだったら
	if (pNumber == NULL)
	{
		// 生成
		pNumber = new CNumber;
	}

	// 引数の代入
	pNumber->m_Pos = pos;
	pNumber->m_Size = size;
	pNumber->m_Type = Type;

	// 生成されていたら
	if (pNumber != NULL)
	{
		// 初期化
		pNumber->Init();
	}
	return pNumber;
}