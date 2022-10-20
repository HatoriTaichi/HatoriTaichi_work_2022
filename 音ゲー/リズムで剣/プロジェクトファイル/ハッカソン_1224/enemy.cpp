//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "enemy.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CEnemy::CEnemy()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CEnemy::Init(void)
{
	CScene2D::SetTexType(m_Type);	// テクスチャの設定
	CScene2D::Init();	// 初期化
	CScene2D::SetPos(m_Pos);	// 位置の設定
	CScene2D::SetSize(m_Size);	// サイズの設定

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CEnemy::Uninit(void)
{
	// 破棄
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
	D3DXVECTOR3 Pos = CScene2D::GetPos();	// 位置を取得

	// アニメーションカウントアップ
	m_nAnimFrame++;

	// 動いてるなら
	if (m_bMove == true)
	{
		// 種類によって移動を変える
		if (m_Type == "ENEMY_LEFT")
		{
			Pos.x -= 10.0f;
			CScene2D::SetPos(Pos);
		}
		else if (m_Type == "ENEMY_RIGHT")
		{
			Pos.x += 10.0f;
			CScene2D::SetPos(Pos);
		}
		else if (m_Type == "ENEMY_UP")
		{
			Pos.y -= 10.0f;
			CScene2D::SetPos(Pos);
		}
		else if (m_Type == "ENEMY_DOWN")
		{
			Pos.y += 10.0f;
			CScene2D::SetPos(Pos);
		}
		
		// アニメーションを切り替えるタイミングなら
		if (m_nAnimFrame >= (FPS / 8))
		{
			// アニメーションテクスチャを設定
			if (m_Type == "ENEMY_RIGHT" ||
				m_Type == "ENEMY_LEFT")
			{
				CScene2D::SetTex(m_nAnim, 8, 1);
				m_nAnimFrame = 0;
				m_nAnim++;
			}
			else if (m_Type == "ENEMY_UP" ||
					 m_Type == "ENEMY_DOWN")
			{
				CScene2D::SetTex(m_nAnim, 4, 1);
				m_nAnimFrame = 0;
				m_nAnim++;
			}
		}

		// 破棄していない
		if (m_bUse == false)
		{
			// 画面外に出たら
			if (Pos.x < 0.0f ||
				Pos.x > SCREEN_WIDTH ||
				Pos.y < 0.0f || 
				Pos.y > SCREEN_HEIGHT)
			{
				// 破棄
				Uninit();
			}
		}
	}
	// それ以外
	else
	{
		// ダメージを受けてなかったら
		if (m_Type != "ENEMY_DAMAGE")
		{
			// アニメーションを切り替えるタイミングなら
			if (m_nAnimFrame >= (FPS / 8))
			{
				// アニメーションテクスチャを設定
				if (m_Type == "ENEMY_RIGHT" ||
					m_Type == "ENEMY_LEFT")
				{
					CScene2D::SetTex(m_nAnim, 8, 1);
					m_nAnimFrame = 0;
					m_nAnim++;
				}
				else if (m_Type == "ENEMY_UP" ||
						 m_Type == "ENEMY_DOWN")
				{
					CScene2D::SetTex(m_nAnim, 4, 1);
					m_nAnimFrame = 0;
					m_nAnim++;
				}
			}
		}
	}

	// ポリゴンの更新
	CScene2D::Update();

	// 破棄するなら
	if (m_bUse == true)
	{
		Pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		CScene2D::SetPos(Pos);
		m_Type = "ENEMY_DAMAGE";
		CScene2D::SetTexType(m_Type);
		CScene2D::SetTex(0, 1, 1);
		m_nDeth++;
		if (m_nDeth >= (FPS * 2))
		{
			Uninit();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	// 描画
	CScene2D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string type)
{
	CEnemy *pEnemy = NULL;	// 敵のポインタ

	// NULLなら
	if (pEnemy == NULL)
	{
		// 生成
		pEnemy = new CEnemy;
	}

	// 引数の代入
	pEnemy->m_Pos = pos;
	pEnemy->m_Size = size;
	pEnemy->m_Type = type;

	// 生成されていたら
	if (pEnemy != NULL)
	{
		// 初期化
		pEnemy->Init();
	}

	return pEnemy;
}
