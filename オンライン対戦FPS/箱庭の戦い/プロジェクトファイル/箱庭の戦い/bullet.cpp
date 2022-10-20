//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "bullet.h"
#include "mouseinput.h"
#include "manager.h"
#include "player.h"
#include "game.h"
#include "model.h"
#include "singlemodel.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CBullet::CBullet()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CBullet::Init(void)
{
	// 初期化
	CBilboard::Init();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	// 破棄
	CBilboard::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CBullet::Update(void)
{
	CMouse *pMouse = CManager::GetMouse();	// マウスの取得
	CPlayer *pPlayer = CManager::GetGame()->GetPlayer();	// プレイヤーの取得
	D3DXVECTOR3 Pos = CBilboard::GetPos();	// 位置の取得
	D3DXVECTOR3 Rot = CBilboard::GetRot();	// 向きの取得
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();	// プレイヤーの位置の取得
	D3DXVECTOR3 PosOld;	// 前回の位置
	int nMaxModel = CManager::GetGame()->GetMaxModel();	// モデルの総数

	// 前回の位置
	PosOld = Pos;

	// 移動量
	m_fMove += m_fMoveSpeed;

	// 移動
	Pos.x += (sinf(Rot.y) * sinf(Rot.x)) * m_fMove;
	Pos.y +=  cosf(Rot.y)				 * m_fMove;
	Pos.z += (sinf(Rot.y) * cosf(Rot.x)) * m_fMove;

	// 位置と向きの設定
	CBilboard::SetPos(Pos);
	CBilboard::SetRot(Rot);

	// 更新
	CBilboard::Update();

	// 範囲外に出たら破棄
	if (Pos.x >= 1000.0f)
	{
		Uninit();
	}
	else if (Pos.x <= -1000.0f)
	{
		Uninit();
	}

	if (Pos.y >= 1000.0f)
	{
		Uninit();
	}
	else if (Pos.y <= -1000.0f)
	{
		Uninit();
	}

	if (Pos.z >= 1000.0f)
	{
		Uninit();
	}
	else if (Pos.z <= -1000.0f)
	{
		Uninit();
	}

	// モデル数分のループ
	for (int nCnt = 0; nCnt < nMaxModel; nCnt++)
	{
		// モデルの取得
		CModel *pModel = CManager::GetGame()->GetModel(nCnt)->GetModel();

		// 当たった
		if (pModel->BoxCollision(&Pos, PosOld) == true)
		{
			// 破棄
			Uninit();
		}
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CBullet::Draw(void)
{
	// 描画
	CBilboard::Draw();
}