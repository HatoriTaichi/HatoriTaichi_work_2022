//=============================================================================
//
// オブジェクト処理 [object.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "object.h"
#include "pause.h"
#include "manager.h"
#include "game01.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
vector<CObject*> CObject::m_object[(int)PRIORITY::MAX];

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CObject::CObject(PRIORITY priolty)
{
	// 初期化
	m_obj_type = OBJTYPE::NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_deth = false;

	// 描画順の設定
	m_priority = static_cast<int>(priolty);

	// 配列に自分を格納
	m_object[m_priority].push_back(this);
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CObject::~CObject()
{
	
}

//=============================================================================
// 全部削除
//=============================================================================
void CObject::ReleaseAll(void)
{
	// 描画順分のループ
	for (int nCnt = 0; nCnt < static_cast<int>(PRIORITY::MAX); nCnt++)
	{
		// 中のサイズを取得
		int nPrioltySize = m_object[nCnt].size();

		// サイズ分のループ
		for (int nCntPop = 0; nCntPop < nPrioltySize; nCntPop++)
		{
			// このタイプ以外なら
			if (m_object[nCnt][nCntPop]->m_priority != static_cast<int>(PRIORITY::FADE) &&
				m_object[nCnt][nCntPop]->m_priority != static_cast<int>(PRIORITY::HISTORY_LETTER))
			{
				// 破棄
				delete m_object[nCnt][nCntPop];
			}
		}

		// 中のサイズを取得
		nPrioltySize = m_object[nCnt].size();

		// サイズ分のループ
		for (int nCntPop = 0; nCntPop < nPrioltySize; nCntPop++)
		{
			// このタイプ以外なら
			if (m_object[nCnt][nCntPop]->m_priority != static_cast<int>(PRIORITY::FADE)  &&
				m_object[nCnt][nCntPop]->m_priority != static_cast<int>(PRIORITY::HISTORY_LETTER))
			{
				// 配列から削除
				m_object[nCnt].pop_back();
				nPrioltySize = m_object[nCnt].size();
				nCntPop--;
			}
		}
	}
}

//=============================================================================
// 全部更新
//=============================================================================
void CObject::UpdateAll(void)
{
	// 描画順分のループ
	for (int count_priolty = 0; count_priolty < static_cast<int>(PRIORITY::MAX); count_priolty++)
	{
		// 中のサイズを取得
		int object_size = m_object[count_priolty].size();

		// サイズ分のループ
		for (int count_object = 0; count_object < object_size; count_object++)
		{
			// 破棄フラグが立ってたら
			if (m_object[count_priolty][count_object]->m_deth == true)
			{
				// 破棄
				delete m_object[count_priolty][count_object];
				m_object[count_priolty][count_object] = NULL;
				m_object[count_priolty].erase(m_object[count_priolty].begin() + count_object);
				object_size = m_object[count_priolty].size();
				count_object--;
			}
			// それ以外
			else
			{
				// ゲーム画面なら
				if (CManager::GetMode() == CManager::MODE::GAME01)
				{
					// ポリゴンポーズしてたら
					if (CPause::GetPause() == false)
					{
						// セリフを出して無かったら
						if (CManager::GetInstance()->GetGame01()->GetDialog() == false)
						{
							// 更新
							m_object[count_priolty][count_object]->Update();
						}
						// それ以外
						else
						{
							// 自分の描画順がこれなら
							if (count_priolty == static_cast<int>(PRIORITY::GAME) || count_priolty == static_cast<int>(PRIORITY::FADE) ||
								count_priolty == static_cast<int>(PRIORITY::CLICK_EFFECT) || count_priolty == static_cast<int>(PRIORITY::NEXT_DIALOG_UI) ||
								count_priolty == static_cast<int>(PRIORITY::DIALOG))
							{
								// 更新
								m_object[count_priolty][count_object]->Update();
							}
						}
					}
					// それ以外
					else
					{
						// 自分の描画順がこれなら
						if (count_priolty == static_cast<int>(PRIORITY::PAUSE) || count_priolty == static_cast<int>(PRIORITY::FADE) || count_priolty == static_cast<int>(PRIORITY::CLICK_EFFECT) || count_priolty == static_cast<int>(PRIORITY::HISTORY_LETTER))
						{
							// 更新
							m_object[count_priolty][count_object]->Update();
						}
					}
				}
				// それ以外
				else
				{
					// 更新
					m_object[count_priolty][count_object]->Update();
				}
			}
		}
	}
}

//=============================================================================
// 全部描画
//=============================================================================
void CObject::DrawAll(void)
{
	// 描画順分のループ
	for (int count_priolty = 0; count_priolty < static_cast<int>(PRIORITY::MAX); count_priolty++)
	{
		// 中のサイズを取得
		int object_size = m_object[count_priolty].size();

		// サイズ分のループ
		for (int count_object = 0; count_object < object_size; count_object++)
		{
			// 破棄フラグが立って無かったら
			if (m_object[count_priolty][count_object]->m_deth == false)
			{
				// 描画
				m_object[count_priolty][count_object]->Draw();
			}
		}
	}
}

//================================================
//プライオリティ設定処理
//================================================
void CObject::SetPriority(const int &nPriority)
{
	m_object[nPriority].push_back(this);	// 設定したい描画順に自分を入れる

	int nthis_priority = this->m_priority;	// 今の描画順
	int object_size = m_object[nthis_priority].size();	// 中のサイズを取得

	// サイズ分のループ
	for (int count_object = 0; count_object < object_size; count_object++)
	{
		// 自分なら
		if (m_object[nthis_priority][count_object] == this)
		{
			// 配列から削除
			m_object[nthis_priority].erase(m_object[nthis_priority].begin() + count_object);
			object_size = m_object[nthis_priority].size();
			break;
		}
	}

	// 描画順を保存
	this->m_priority = nPriority;
}
