//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "player.h"
#include "model.h"
#include "tcp_client.h"
#include "renderer.h"
#include "manager.h"
#include "motion.h"
#include "texture.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "playerbullet.h"
#include "camera.h"
#include "singlemodel.h"
#include "manager.h"
#include "game.h"
#include "textureobj.h"
#include "counter.h"
#include "gunfire.h"
#include "sound.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CPlayer::CPlayer(LAYER_TYPE Layer) : CScene(Layer)
{
	m_Boold.push_back(CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), "BLOOD_00"));
	m_Boold.push_back(CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), "BLOOD_01"));
	m_Boold.push_back(CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), "BLOODMASK"));
	m_Boold[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_Boold[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	D3DXVECTOR3 m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int m_nParts = 0;
	int m_nDamageTime = 0;
	int m_nStock = MAX_STOCK;
	int m_nRateTime = 0;
	int m_nReloadCnt = 0;
	float m_fMoveSpeed = 0;
	float m_fLife = MAX_LIFE;
	bool m_bRespawn = false;
	bool m_bDamageTime = false;
	bool m_bHitDamage = false;
	bool m_bAttack = false;
	bool m_bEndBattle = false;
	bool m_bShoot = true;
	bool m_bReload = false;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	FILE *pFile;	// ファイルのポインタ
	D3DXVECTOR3 Pos;	// 位置
	D3DXVECTOR3 Rot;	// 向き
	char aFile[128];	// ファイルの文字列バッファ
	vector<int> Parent;	// 親のインデックス
	int nKey = 0;	// キー
	int nCntKey = 0;	// キーカウント
	int nFrame = 0;	// フレーム
	int nCntModel = 0;	// モデルカウント
	int nCntMosion = 0;	// モーションカウント
	bool bLoop;	// ループ

	// ファイルを開く
	pFile = fopen("data/Txtdata/player.txt", "r");

	// ファイルが開けていたら
	if (pFile != NULL)
	{
		// 無限ループ
		while (true)
		{
			// ファイルの文字列を取得
			fscanf(pFile, "%s", &aFile[0]);

			// NUM_MODELの文字列を見つけたら
			if (strcmp(&aFile[0], "NUM_MODEL") == 0)
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nParts);
				for (int nCnt = 0; nCnt < m_nParts; nCnt++)
				{
					Parent.push_back(0);
				}
				break;
			}
		}
		// パーツ数分のループ
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			// モデルを生成
			m_pModel.push_back(CModel::Create((CModel::TYPE)nCnt, D3DXVECTOR3(1.0f, 1.0f, 1.0f), &Parent[nCnt], pFile));
		}
		// パーツ数分のループ
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			// 親の設定
			if (Parent[nCnt] == -1)
			{
				m_pModel[nCnt]->SetPrent(NULL);
			}
			else
			{
				m_pModel[nCnt]->SetPrent(m_pModel[Parent[nCnt]]);
			}
		}
		// 無限ループ
		while (true)
		{
			// ファイルの文字列を取得
			fscanf(pFile, "%s", &aFile[0]);

			// MOTIONSETの文字列を見つけたら
			if (strcmp(&aFile[0], "MOTIONSET") == 0)
			{
				int nLoop;
				fscanf(pFile, "%*s%*s%d", &nLoop);
				fscanf(pFile, "%*s%*s%*s%*s");
				fscanf(pFile, "%*s%*s%d", &nKey);
				bLoop = nLoop;

				for (int nCnt = 0; nCnt < m_nParts; nCnt++)
				{
					CModel::MOTIONINFO *pMosion = m_pModel[nCnt]->GetMotion(nCntMosion);
					for (int nCntKey = 0; nCntKey < nKey; nCntKey++)
					{
						pMosion->aKeyinfo.push_back(new CModel::KEYINFO);
					}
				}
			}
			// KEYSETの文字列を見つけたら
			if (strcmp(&aFile[0], "KEYSET") == 0)
			{
				fscanf(pFile, "%*s%*s%*s%*s%*s%*s%*s%*s%*s%*s");
				fscanf(pFile, "%*s%*s%d", &nFrame);
				while (true)
				{
					fscanf(pFile, "%s", &aFile[0]);
					// KEYの文字列を見つけたら
					if (strcmp(&aFile[0], "KEY") == 0)
					{
						fscanf(pFile, "%*s%*s%*s%*s%*s%*s");
						fscanf(pFile, "%*s%*s%f%f%f", &Pos.x, &Pos.y, &Pos.z);
						fscanf(pFile, "%*s%*s%f%f%f", &Rot.x, &Rot.y, &Rot.z);
					}
					// END_KEYの文字列を見つけたら
					if (strcmp(&aFile[0], "END_KEY") == 0)
					{
						CModel::MOTIONINFO *pMosion = m_pModel[nCntModel]->GetMotion(nCntMosion);

						pMosion->bLoop = bLoop;
						pMosion->nNumKey = nKey;
						pMosion->aKeyinfo[nCntKey]->fFrame = nFrame;

						pMosion->aKeyinfo[nCntKey]->aKey.fPosX = m_pModel[nCntModel]->GetPos().x + Pos.x;
						pMosion->aKeyinfo[nCntKey]->aKey.fPosY = m_pModel[nCntModel]->GetPos().y + Pos.y;
						pMosion->aKeyinfo[nCntKey]->aKey.fPosZ = m_pModel[nCntModel]->GetPos().z + Pos.z;

						pMosion->aKeyinfo[nCntKey]->aKey.fRotX = m_pModel[nCntModel]->GetRot().x + Rot.x;
						pMosion->aKeyinfo[nCntKey]->aKey.fRotY = m_pModel[nCntModel]->GetRot().y + Rot.y;
						pMosion->aKeyinfo[nCntKey]->aKey.fRotZ = m_pModel[nCntModel]->GetRot().z + Rot.z;

						nCntModel++;
					}
					// END_KEYSETの文字列を見つけたら
					if (strcmp(&aFile[0], "END_KEYSET") == 0) 
					{
						nCntModel = 0;
						nCntKey++;
						break;
					}
				}
			}
			// END_MOTIONSETの文字列を見つけたら
			if (strcmp(&aFile[0], "END_MOTIONSET") == 0)
			{
				nCntModel = 0;
				nCntKey = 0;
				nCntMosion++;
			}
			// END_SCRIPTの文字列を見つけたら
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
	}
	else
	{
		printf("モデルデータが読み取れませんでした。");
	}

	// ファイルを閉じる
	fclose(pFile);

	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	// パーツ数分のループ
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		// 破棄
		m_pModel[nCnt]->Uninit();
		delete m_pModel[nCnt];
		m_pModel[nCnt] = NULL;
	}
}

//=============================================================================
// モデルの更新処理
//=============================================================================
void CPlayer::Update(void)
{
	CTcpClient *pTcp = CManager::GetTcpClient();	// 通信クラスの取得
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// 通信データクラスの取得
	int nMaxModel = CManager::GetGame()->GetMaxModel();	// モデルの総数を取得

	// 前回の位置を保存
	m_PosOld = m_Pos;

	// 移動処理
	Move();

	// モーション処理
	Motion();

	// ダメージ処理
	Damage();

	// ストック処理
	CntStock();

	// 攻撃処理
	Attack();

	// リスポーンしてなかったら
	if (m_bRespawn == false)
	{
		// モデルの総数分のループ
		for (int nCnt = 0; nCnt < nMaxModel; nCnt++)
		{
			// モデルを取得
			CModel *pModel = CManager::GetGame()->GetModel(nCnt)->GetModel();

			// 当たり判定
			pModel->BoxCollision(&m_Pos, m_PosOld);
		}
	}
	// それ以外
	else
	{
		m_bRespawn = false;
	}

	// サーバーにsend
	pTcp->Send((char*)pData, sizeof(CCommunicationData::COMMUNICATION_DATA));
	pData->Player.bPushKey = false;
}

//=============================================================================
// モデルの描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; // デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	// デバイスを取得する

	//--------------------------------------
	//プレイヤー(原点)のマトリックスの設定
	//--------------------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	D3DXMatrixIdentity(&m_MtxWold);	//マトリックス初期化

	//向きの設定
	D3DXMatrixRotationYawPitchRoll(	&mtxRot,
									m_Rot.y,
									m_Rot.x,
									m_Rot.z);

	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxRot);
	//位置
	D3DXMatrixTranslation(	&mtxTrans,
							m_Pos.x,
							m_Pos.y,
							m_Pos.z);

	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxTrans);
	//マトリックスの設定
	pDevice->SetTransform(	D3DTS_WORLD,
							&m_MtxWold);
	// パーツ数分のループ
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		// 描画
		m_pModel[nCnt]->Draw();
	}
}

//=============================================================================
// 弾との当たり判定
//=============================================================================
bool CPlayer::ToBulletCollision(D3DXVECTOR3 pos, float fwigth, float fheight)
{
	D3DXVECTOR3 posdfrc;	// 差分
	int nMyR = PLAYER_RADIUS;	// 半径
	float fposdfrcX;	// 差分の半径
	bool bHit = false;	// 当たったか

	// 差分
	posdfrc.x = m_Pos.x - pos.x;
	posdfrc.z = m_Pos.z - pos.z;

	posdfrc.x = posdfrc.x * posdfrc.x;

	fposdfrcX = posdfrc.x + posdfrc.z;

	fposdfrcX = sqrtf(fposdfrcX);

	// 半径の中だったら
	if (m_Pos.y <= pos.y + fheight / 2 &&
		m_Pos.y + PLAYER_HEIGHT >= pos.y - fheight / 2 &&
		fposdfrcX < nMyR)
	{
		// 無敵時間じゃなかったら
		if (m_bInvincible == false)
		{
			m_fLife -= 3.0f;
			m_nDamageTime = 0;
			m_bDamageTime = true;
			m_bHitDamage = true;
			bHit = true;
		}
	}
	return bHit;
}

//=============================================================================
// モデルの生成
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = NULL;	// プレイヤーのポインタ

	// NULLだったら
	if (pPlayer == NULL)
	{
		// 生成
		pPlayer = new CPlayer;
	}

	// 引数の代入
	pPlayer->m_Pos = pos;
	pPlayer->m_Rot = rot;

	// 生成されていたら
	if (pPlayer != NULL)
	{
		// 初期化
		pPlayer->Init();
	}
	return pPlayer;
}

//=============================================================================
// 移動
//=============================================================================
void CPlayer::Move(void)
{
	CCamera *pCamera = CManager::GetCamera();	// カメラの取得
	CKeyboard *pKey = CManager::GetKeyboard();	// キーボードの取得
	CMouse *pMouse = CManager::GetMouse();	// マウスの取得
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// 通信データクラスの取得
	D3DXVECTOR3 Rot = pCamera->GetRot();	// カメラの向きの取得
	float fLong = pCamera->GetDestance();	// カメラの長さの取得
	float fMoveRot;	// 移動向き
	m_Rot.y = Rot.x;	// カメラの向きの代入
	m_Rot.y += D3DXToRadian(180.0f);	// 180度回転
	fMoveRot = m_Rot.y - D3DXToRadian(180.0f);	// 移動向きの代入

	if (m_bEndBattle == false)
	{
#if _DEBUG
		if (pKey->GetPress(pKey->LSHIFT) == true)
		{
			m_fMoveSpeed = DUSH_SPEED;
			m_Pos.y -= 1.0f;
		}
		else if (pKey->GetPress(pKey->LSHIFT) == false)
		{
			m_fMoveSpeed = NORMAL_SPEED;
		}
#endif
		// キーによって移動
		if (pKey->GetPress(pKey->W) == true)
		{
			m_Pos.x = m_Pos.x + sinf(fMoveRot) * m_fMoveSpeed;
			m_Pos.z = m_Pos.z + cosf(fMoveRot) * m_fMoveSpeed;
		}
		else if (pKey->GetPress(pKey->S) == true)
		{
			m_Pos.x = m_Pos.x - sinf(fMoveRot) * m_fMoveSpeed;
			m_Pos.z = m_Pos.z - cosf(fMoveRot) * m_fMoveSpeed;
		}
		if (pKey->GetPress(pKey->A) == true)
		{
			m_Pos.x = m_Pos.x - cosf(fMoveRot) * m_fMoveSpeed;
			m_Pos.z = m_Pos.z + sinf(fMoveRot) * m_fMoveSpeed;
		}
		else if (pKey->GetPress(pKey->D) == true)
		{
			m_Pos.x = m_Pos.x + cosf(fMoveRot) * m_fMoveSpeed;
			m_Pos.z = m_Pos.z - sinf(fMoveRot) * m_fMoveSpeed;
		}
		// 重力を加算
		m_Pos.y -= 1.0f;

		// 下に行きすぎたら
		if (m_Pos.y <= -50.0f)
		{
			m_bRespawn = true;
			m_nStock -= 1;
			if (pData->Player.nNumber == 1)
			{
				m_Pos = D3DXVECTOR3(-650.0f, 100.0f, -600.0f);
			}
			else
			{
				m_Pos = D3DXVECTOR3(650.0f, 100.0f, 600.0f);
			}
		}
	}

	// 通信データクラスに代入
	pData->Player.Pos = m_Pos;
	pData->Player.Rot = m_Rot;
}

//=============================================================================
// 攻撃
//=============================================================================
void CPlayer::Attack(void)
{
	CSound *pSound = CManager::GetSound();	// サウンドの取得
	CKeyboard *pKey = CManager::GetKeyboard();	// キーボードの取得
	CMouse *pMouse = CManager::GetMouse();	// マウスの取得
	CCamera *pCamera = CManager::GetCamera();	// カメラの取得
	CCounter *pCounter = CManager::GetGame()->GetAmmo();	// 残段数の取得
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// 通信データクラスの取得
	D3DXVECTOR3 Rot = pCamera->GetRot();	// カメラの向きの取得
	D3DXMATRIX WorldPos = m_pModel[11]->GetMatrix();	// モデルのマトリッックスの取得
	float fNorRot = m_Rot.y - D3DXToRadian(180.0f);	// 向きを計算

	// バトルが終わってなかったら
	if (m_bEndBattle == false)
	{
		// 弾の総数分のループ
		for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
		{
			// 左クリック && 弾を使って無かったら && 残段数があったら
			if (pMouse->GetPress(pMouse->LEFT_BOTTON) == true && pData->Bullet[nCnt].bUse == false && pCounter->GetCounterNum() != 0)
			{
				// うってたら
				if (m_bShoot == true)
				{
					// 再生
					pSound->PlaySound(CSound::X2SOUND_LABEL::SHOOT);
					Rot.y = Rot.y - 0.01f;
					pCamera->SetRot(Rot);
					pCounter->AddCounter(-1);
					m_bAttack = true;

					// 弾を生成
					CPlayerBullet::Create(D3DXVECTOR3(WorldPos._41, WorldPos._42, WorldPos._43), Rot, D3DXVECTOR3(5.0f, 5.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "BULLET", 1.0f);
					
					// マズルフラッシュの生成
					CGunFire::Create(D3DXVECTOR3(WorldPos._41, WorldPos._42, WorldPos._43), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "MASLE_FLASH");
					pData->Bullet[nCnt].Rot = Rot;
					m_bShoot = false;
					if (pData->Bullet[nCnt].bUse == false)
					{
						pData->Bullet[nCnt].bUse = true;
						break;
					}
				}
			}
		}
	}
	// うって無かったら
	if (m_bShoot == false)
	{
		m_nRateTime++;
	}
	if (m_nRateTime >= (FPS / 15))
	{
		m_bShoot = true;
		m_nRateTime = 0;
	}
	// Rを押したら
	if (pKey->GetTrigger(pKey->R) == true)
	{
		// 再生
		pSound->PlaySound(CSound::X2SOUND_LABEL::RELOAD);

		// リロード
		m_bReload = true;
	}
	// リロードしてたら
	if (m_bReload == true)
	{
		m_nReloadCnt++;
		if (m_nReloadCnt >= (FPS * 1.5f))
		{
			pCounter->SetCounterNum(30);
			for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
			{
				pData->Bullet[nCnt].bUse = false;
			}
			m_bReload = false;
			m_nReloadCnt = 0;
		}
	}
	// 左クリックしてなかったら
	if (pMouse->GetPress(pMouse->LEFT_BOTTON) == false)
	{
		pData->Player.bPushKey = false;
	}
	// 左クリックしてたら
	else if (pMouse->GetPress(pMouse->LEFT_BOTTON) == true)
	{
		pData->Player.bPushKey = true;
	}
#if _DEBUG
	if (pKey->GetTrigger(pKey->J) == true)
	{
		m_nStock -= 1;
	}
#endif // _DEBUG

}

//=============================================================================
// モーション
//=============================================================================
void CPlayer::Motion(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// 通信データの取得
	CKeyboard *pKey = CManager::GetKeyboard();	// キーボードの取得

	// 攻撃してなかったら
	if (m_bAttack == false)
	{
		// 動いて無かったら
		if (pKey->GetPress(pKey->W) == false &&
			pKey->GetPress(pKey->A) == false &&
			pKey->GetPress(pKey->S) == false &&
			pKey->GetPress(pKey->D) == false)
		{
			// モーションを設定
			m_Motion = CModel::MOSTION::NEUTRAL;
			pData->Player.Motion = CCommunicationData::MOSTION::NEUTRAL;

			// パーツ数分のループ
			for (int nCnt = 0; nCnt < m_nParts; nCnt++)
			{
				// モーションする
				CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)m_Motion);
				D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
				D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

				CMotion::PlayMotin(Motion, &Pos, &Rot);
				m_pModel[nCnt]->SetPos(Pos);
				m_pModel[nCnt]->SetRot(Rot);
			}
		}
		// 前進か左右移動してたら
		else if (pKey->GetPress(pKey->W) == true ||
				 pKey->GetPress(pKey->A) == true ||
				 pKey->GetPress(pKey->D) == true)
		{
			// モーションを設定
			m_Motion = CModel::MOSTION::WORK;
			pData->Player.Motion = CCommunicationData::MOSTION::WORK;

			// パーツ数分のループ
			for (int nCnt = 0; nCnt < m_nParts; nCnt++)
			{
				// モーションする
				CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)m_Motion);
				D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
				D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

				CMotion::PlayMotin(Motion, &Pos, &Rot);
				m_pModel[nCnt]->SetPos(Pos);
				m_pModel[nCnt]->SetRot(Rot);
			}
		}
		// 後退していたら
		else if (pKey->GetPress(pKey->S) == true)
		{
			// モーションを設定
			m_Motion = CModel::MOSTION::BUCK_WORK;
			pData->Player.Motion = CCommunicationData::MOSTION::BUCK_WORK;

			// パーツ数分のループ
			for (int nCnt = 0; nCnt < m_nParts; nCnt++)
			{
				// モーションする
				CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)m_Motion);
				D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
				D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

				CMotion::PlayMotin(Motion, &Pos, &Rot);
				m_pModel[nCnt]->SetPos(Pos);
				m_pModel[nCnt]->SetRot(Rot);
			}
		}
	}
	// うっていたら
	else if (m_bShoot == true)
	{
		// モーションを設定
		m_Motion = CModel::MOSTION::ATTACK;
		pData->Player.Motion = CCommunicationData::MOSTION::ATTACK;

		// パーツ数分のループ
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			// モーションする
			CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)m_Motion);
			D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
			D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

			if (CMotion::PlayMotin(Motion, &Pos, &Rot) == false)
			{
				m_pModel[nCnt]->SetPos(Pos);
				m_pModel[nCnt]->SetRot(Rot);
			}
			else
			{
				m_bAttack = false;
			}
		}
	}
}

//=============================================================================
// ダメージ
//=============================================================================
void CPlayer::Damage(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// 通信データの取得

	// 無敵なら
	if (m_bInvincible == true)
	{
		m_nIvbTime++;
	}
	// 時間まで無敵
	if (m_nIvbTime >= (FPS * 1.5))
	{
		m_bInvincible = false;
	}
	// ライフが削れていて && ダメージを受けていたら
	if (m_fLife < MAX_LIFE && m_bDamageTime == true)
	{
		m_nDamageTime++;
	}

	// 時間になったら
	if (m_nDamageTime >= RECOVERY_TIME)
	{
		// ダメージを受けてない
		m_nDamageTime = 0;
		m_bDamageTime = false;
	}

	// ダメージを受けてなかったら
	if (m_bDamageTime == false)
	{
		// 回復
		m_fLife += 0.1f;
	}

	// 回復数に応じて画面を変える
	if (m_fLife >= 80.0f)
	{
		m_Boold[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
	}
	if (m_fLife >= MAX_LIFE)
	{
		m_Boold[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	if (m_fLife >= MAX_LIFE)
	{
		m_fLife = MAX_LIFE;
	}

	if (m_fLife < MAX_LIFE && m_fLife >= 80.0f && m_bHitDamage == true)
	{
		m_Boold[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
		m_bHitDamage = false;
	}
	else if (m_fLife < 80.0f && m_bHitDamage == true)
	{
		m_Boold[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
		m_bHitDamage = false;
	}

	// 死んだら
	if (m_fLife <= 0.0f)
	{
		m_fLife = MAX_LIFE;
		m_bRespawn = true;
		m_bHitDamage = false;
		m_bDamageTime = false;
		m_bInvincible = true;
		m_nStock -= 1;
		m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		if (pData->Player.nNumber == 1)
		{
			m_Pos = D3DXVECTOR3(-650.0f, 100.0f, -600.0f);
		}
		else
		{
			m_Pos = D3DXVECTOR3(650.0f, 100.0f, 600.0f);
		}
	}

	// ストックを通信データに代入
	pData->Player.nStock = m_nStock;
}

//=============================================================================
// ストックカウンタ
//=============================================================================
void CPlayer::CntStock(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// 通信データの取得

	if (pData->Player.nNumber != 0)
	{
		CCounter *pCounter = CManager::GetGame()->GetCounter(pData->Player.nNumber - 1);
		pCounter->SetCounterNum(m_nStock);
	}
}