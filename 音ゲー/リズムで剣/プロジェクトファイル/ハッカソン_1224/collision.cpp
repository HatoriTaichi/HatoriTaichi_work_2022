//=============================================================================
//
// 当たり判定の処理 [collision.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "collision.h"
#include "manager.h"
#include "fade.h"
#include "mouseinput.h"
#include "fade.h"
#include "Notes.h"
#include "keyinput.h"
#include "enemy.h"
#include "counter.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCollision::CCollision()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CCollision::~CCollision()
{

}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CCollision::Init(void)
{
	CScene2D::SetTexType(m_TexType);	// テクスチャの設定
	CScene2D::Init();	// 初期化
	CScene2D::SetPos(m_Pos);	// 位置の設定
	CScene2D::SetSize(D3DXVECTOR3(m_Size.x, m_Size.y, 0.0f));	// サイズの設定

	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void CCollision::Uninit(void)
{
	// 破棄
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CCollision::Update(void)
{
	CKeyboard *pKey = CManager::GetKeyboard();	// キーボードの取得
	CSound *pSound = CManager::GetSound();	// サウンドの取得
	CCounter *pCombo = CManager::GetGame()->GetCombo();	// コンボカウンターの取得
	CCounter *pScore = CManager::GetGame()->GetScore();	// スコアの取得
	D3DXVECTOR3 Pos = CScene2D::GetPos();	// 位置の取得
	D3DXVECTOR2 Size = CScene2D::GetSize();	// サイズの取得

	// 移動
	Pos.y += 1.0f;

	// テクスチャのタイプによって処理分け
	if (m_TexType == "LEFT_ARROWFRAME" ||
		m_TexType == "RIGHT_ARROWFRAME")
	{
		// サイズを変える
		Size.x -= 1.0f;
		Size.y -= 0.5f;

		// ノーツが判定内なら
		if ((m_pNoets->GetSize().x * MAX_EXTENSION) >= Size.x &&
			(m_pNoets->GetSize().y * MAX_EXTENSION) >= Size.y)
		{
			// キーを押したら
			if (pKey->GetTrigger(pKey->LEFT) == true || pKey->GetTrigger(pKey->RIGHT) == true)
			{
				m_pNoets->GetEnemy()->SetUse(true);	// 破棄
				pSound->Play(CSound::SOUND_LABEL_SE_TAP);	//再生
				pCombo->AddCounter(1);	// カウンター加算
				pScore->AddCounter(1000);	// スコア加算
			}
		}
		else if ((m_pNoets->GetSize().x * MIN_EXTENSION) >= Size.x &&
				 (m_pNoets->GetSize().y * MIN_EXTENSION) >= Size.y)
		{
			// キーを押したら
			if (pKey->GetTrigger(pKey->LEFT) == true || pKey->GetTrigger(pKey->RIGHT) == true)
			{
				m_pNoets->GetEnemy()->SetUse(true);	// 破棄
				pSound->Play(CSound::SOUND_LABEL_SE_TAP);	//再生
				pCombo->AddCounter(1);	// カウンター加算
				pScore->AddCounter(500);	// スコア加算
			}
		}
		else if ((m_pNoets->GetSize().x * MAX_EXTENSION) <= Size.x &&
				 (m_pNoets->GetSize().y * MAX_EXTENSION) <= Size.y)
		{
			// キーを押したら
			if (pKey->GetTrigger(pKey->LEFT) == true || pKey->GetTrigger(pKey->RIGHT) == true)
			{
				m_pNoets->GetEnemy()->SetbMove(true);	// 破棄
				pCombo->SetCounterNum(0);	// 加算しない
			}
		}
	}
	// テクスチャのタイプによって処理分け
	else if (m_TexType == "UP_ARROWFRAME" ||
			 m_TexType == "DOWN_ARROWFRAME")
	{
		// サイズを変える
		Size.x -= 0.5f;
		Size.y -= 1.0f;

		// ノーツが判定内なら
		if ((m_pNoets->GetSize().x * MAX_EXTENSION) >= Size.x &&
			(m_pNoets->GetSize().y * MAX_EXTENSION) >= Size.y)
		{
			// キーを押したら
			if (pKey->GetTrigger(pKey->UP) == true || pKey->GetTrigger(pKey->DOWN) == true)
			{
				m_pNoets->GetEnemy()->SetUse(true);	// 破棄
				pSound->Play(CSound::SOUND_LABEL_SE_TAP);	//再生
				pCombo->AddCounter(1);	// カウンター加算
				pScore->AddCounter(1000);	// スコア加算
			}
		}
		else if ((m_pNoets->GetSize().x * MIN_EXTENSION) >= Size.x &&
				 (m_pNoets->GetSize().y * MIN_EXTENSION) >= Size.y)
		{
			// キーを押したら
			if (pKey->GetTrigger(pKey->LEFT) == true || pKey->GetTrigger(pKey->RIGHT) == true)
			{
				m_pNoets->GetEnemy()->SetUse(true);	// 破棄
				pSound->Play(CSound::SOUND_LABEL_SE_TAP);	//再生
				pCombo->AddCounter(1);	// カウンター加算
				pScore->AddCounter(500);	// スコア加算
			}
		}
		else if ((m_pNoets->GetSize().x * MAX_EXTENSION) <= Size.x &&
				 (m_pNoets->GetSize().y * MAX_EXTENSION) <= Size.y)
		{
			// キーを押したら
			if (pKey->GetTrigger(pKey->UP) == true || pKey->GetTrigger(pKey->DOWN) == true)
			{
				m_pNoets->GetEnemy()->SetbMove(true);	// 破棄
				pCombo->SetCounterNum(0);	// 加算しない
			}
		}
	}

	// 位置を設定
	CScene2D::SetPos(Pos);

	// サイズを設定
	CScene2D::SetSize(D3DXVECTOR3(Size.x, Size.y, 0.0f));

	// ポリゴンの更新
	CScene2D::Update();

	// タイミングを逃したら
	if ((m_pNoets->GetSize().x * MIN_EXTENSION) >= Size.x &&
		(m_pNoets->GetSize().y * MIN_EXTENSION) >= Size.y)
	{
		// 破棄
		m_pNoets->GetEnemy()->SetbMove(true);
		m_pNoets->Uninit();
		m_pNoets = NULL;
		Uninit();
	}
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CCollision::Draw(void)
{
	// 描画
	CScene2D::Draw();
}

//=============================================================================
// 生成
//=============================================================================
CCollision *CCollision::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, string Type, CNotes *pNotes)
{
	CCollision *pCollision = NULL;	// 当たり判定のポインタ

	// NULLだったら
	if (pCollision == NULL)
	{
		// 生成
		pCollision = new CCollision;
	}

	// 引数の代入
	pCollision->m_Pos = pos;
	pCollision->m_Size = size;
	pCollision->m_TexType = Type;
	pCollision->m_pNoets = pNotes;

	// 生成されていたら
	if (pCollision != NULL)
	{
		// 初期化
		pCollision->Init();
	}
	return pCollision;
}