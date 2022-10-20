//=============================================================================
//
// カウンター処理 [counter.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "counter.h"
#include "number.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCounter::CCounter()
{
	D3DXVECTOR3 m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int m_nNumberMax = 0;	// 桁数
	int m_nCounter = 0;	// スコア
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CCounter::~CCounter()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CCounter::Init(void)
{
	// 桁数分のループ
	for (int nNumber = 0; nNumber < m_nNumberMax; nNumber++)
	{
		// 数の生成
		m_pNumber.push_back(CNumber::Create(D3DXVECTOR3(m_Pos.x + (m_Size.x * 2) * nNumber, m_Pos.y, 0.0f), m_Size, m_Type));
	}
	m_nCounter = 0;

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CCounter::Uninit(void)
{
	// 桁数分のループ
	for (int nNumber = 0; nNumber < m_nNumberMax; nNumber++)
	{
		// 破棄
		m_pNumber[0]->Uninit();
		m_pNumber[0] = NULL;
		m_pNumber.erase(m_pNumber.begin());
	}
	// 破棄
	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CCounter::Update(void)
{
	// スコアの設定
	SetCounter(m_nCounter);
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CCounter::Draw(void)
{
	// 桁数分のループ
	for (int nNumber = 0; nNumber < m_nNumberMax; nNumber++)
	{
		m_pNumber[nNumber]->Draw();
	}
}

//=============================================================================
// 生成
//=============================================================================
CCounter *CCounter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumbderLength, string type)
{
	CCounter *pCount = NULL;	// カウンターのポインタ

	// NULLだったら
	if (pCount == NULL)
	{
		// 生成
		pCount = new CCounter;
	}

	// 引数の代入
	pCount->m_Pos = pos;
	pCount->m_Size = size;
	pCount->m_Type = type;
	pCount->m_nNumberMax = nNumbderLength;

	// 生成されていたら
	if (pCount != NULL)
	{
		// 初期化
		pCount->Init();
	}
	return pCount;
}

//=============================================================================
// スコアの設定
//=============================================================================
void CCounter::SetCounter(int nCounter)
{
	int *aNumber = new int[m_nNumberMax];	// 桁
	int nDivide = 10;	// 割られる方
	int nBreak = 1;	// 割る方

	for (int nCnt = 0; nCnt < m_nNumberMax - 1; nCnt++)
	{
		nDivide *= 10;
		nBreak *= 10;
	}

	for (int nCnt = 0; nCnt < m_nNumberMax; nCnt++)
	{
		aNumber[nCnt] = m_nCounter % nDivide / nBreak;
		nDivide /= 10;
		nBreak /= 10;
	}

	// 桁数分のループ
	for (int nNumber = 0; nNumber < m_nNumberMax; nNumber++)
	{
		// スコアの設定
		m_pNumber[nNumber]->SetScore(aNumber[nNumber]);
	}
}

//=============================================================================
// カラーの設定
//=============================================================================
void CCounter::SetCol(D3DCOLORVALUE col)
{
	// 桁数分のループ
	for (int nCntNumber = 0; nCntNumber < m_nNumberMax; nCntNumber++)
	{
		// カラーの設定
		m_pNumber[nCntNumber]->SetCol(col);
	}
}