//=============================================================================
//
// オブジェクト処理 [scene.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
vector<CScene*> CScene::m_pObjet[(int)LAYER_TYPE::MAX_LAYER];

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CScene::CScene(LAYER_TYPE Layer)
{
	m_bDeth = false;	// 破棄されていない
	m_nPriority = static_cast<int>(Layer);	// 描画順の設定

	// 配列に保存
	m_pObjet[m_nPriority].push_back(this);
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CScene::~CScene()
{
	
}

//=============================================================================
// 全部削除
//=============================================================================
void CScene::ReleaseAll(void)
{
	// レイヤー数分のループ
	for (int nCnt = 0; nCnt < static_cast<int>(LAYER_TYPE::MAX_LAYER); nCnt++)
	{
		// サイズの取得
		int nPrioltySize = m_pObjet[nCnt].size();

		// サイズ数分のループ
		for (int nCntPop = 0; nCntPop < nPrioltySize; nCntPop++)
		{
			// 破棄
			delete m_pObjet[nCnt][nCntPop];
		}

		// サイズ数分のループ
		for (int nCntPop = 0; nCntPop < nPrioltySize; nCntPop++)
		{
			// 配列から破棄
			m_pObjet[nCnt].pop_back();
		}
	}
}

//=============================================================================
// 全部更新
//=============================================================================
void CScene::UpdateAll(void)
{
	// レイヤー数分のループ
	for (int nCnt = 0; nCnt < static_cast<int>(LAYER_TYPE::MAX_LAYER); nCnt++)
	{
		// サイズの取得
		int nUpdateSize = m_pObjet[nCnt].size();

		// サイズ数分のループ
		for (int nCntUpdate = 0; nCntUpdate < nUpdateSize; nCntUpdate++)
		{
			// 破棄フラグが立ってなかったら
			if (m_pObjet[nCnt][nCntUpdate]->m_bDeth == false)
			{
				// 更新
				m_pObjet[nCnt][nCntUpdate]->Update();
			}
			// 破棄フラグが立ってたら
			else if (m_pObjet[nCnt][nCntUpdate]->m_bDeth == true)
			{
				// 破棄
				delete m_pObjet[nCnt][nCntUpdate];
				m_pObjet[nCnt][nCntUpdate] = NULL;
				m_pObjet[nCnt].erase(m_pObjet[nCnt].begin() + nCntUpdate);
			}
		}
	}
}

//=============================================================================
// 全部描画
//=============================================================================
void CScene::DrawAll(void)
{
	// レイヤー数分のループ
	for (int nCnt = 0; nCnt < (int)LAYER_TYPE::MAX_LAYER; nCnt++)
	{
		// サイズの取得
		int nDrawSize = m_pObjet[nCnt].size();

		// サイズ数分のループ
		for (int nCntUpdate = 0; nCntUpdate < nDrawSize; nCntUpdate++)
		{
			// 描画
			m_pObjet[nCnt][nCntUpdate]->Draw();
		}
	}
}