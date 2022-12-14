//=============================================================================
//
// モデルテスト処理 [modeltester.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "enemy.h"
#include "enemybullet.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "camera.h"
#include "tcp_client.h"
#include "singlemodel.h"
#include "game.h"
#include "counter.h"
#include "motion.h"
#include "sound.h"
#include "gunfire.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CCommunicationData CEnemy::m_CommuData;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CEnemy::CEnemy(LAYER_TYPE Layer) : CScene(Layer)
{
	D3DXVECTOR3 m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int m_nParts = 0;
	int m_nStock = MAX_STOCK;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
	
}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT CEnemy::Init(void)
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

	// スレッドを生成
	std::thread th(Recv);

	// スレッドを切り離す
	th.detach();

	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CEnemy::Uninit(void)
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
void CEnemy::Update(void)
{
	// 移動処理
	Move();

	// 攻撃処理
	Attack();

	// モーション
	Motion();

	// ストック
	StockCnt();
}

//=============================================================================
// モデルの描画処理
//=============================================================================
void CEnemy::Draw(void)
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
bool CEnemy::ToBulletCollision(D3DXVECTOR3 pos, float fwigth, float fheight)
{
	D3DXVECTOR3 posdfrc;	// 差分
	int nMyR = ENEMY_RADIUS;	// 半径
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
		m_Pos.y + ENEMY_HEIGHT >= pos.y - fheight / 2 &&
		fposdfrcX < nMyR)
	{
		bHit = true;
	}
	return bHit;
}

//=============================================================================
// モデルの生成
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pEnemy = NULL;	// 敵のポインタ

	// NULLだったら
	if (pEnemy == NULL)
	{
		// 生成
		pEnemy = new CEnemy;
	}

	// 引数の代入s
	pEnemy->m_Pos = pos;
	pEnemy->m_Rot = rot;

	// 生成されていたら
	if (pEnemy != NULL)
	{
		// 初期化
		pEnemy->Init();
	}
	return pEnemy;
}

//=============================================================================
// レシーブスレッド
//=============================================================================
void CEnemy::Recv(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// 通信データの取得

	// 繋がっている間はループ
	while (pData->bConnect == false)
	{
		CTcpClient *pTcp = CManager::GetTcpClient();	// 通信クラスの取得
		char aRecv[MAX_COMMUDATA];	// 受信データ

		// 受信
		int nRecvSize = pTcp->Recv(&aRecv[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
		
		// 受信データが無かったら
		if (nRecvSize < 0)
		{
			if (pTcp != NULL)
			{
				pTcp->Uninit();
				pTcp = NULL;
				break;
			}
		}
		// コピー
		memcpy(pData, &aRecv[0], (int)sizeof(CCommunicationData::COMMUNICATION_DATA));
	}
}

//=============================================================================
// 攻撃
//=============================================================================
void CEnemy::Attack(void)
{
	CSound *pSound = CManager::GetSound();	// サウンドの取得
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// 通信データの取得
	D3DXMATRIX WorldPos = m_pModel[11]->GetMatrix();	// モデルのマトリッックスの取得

	// 弾の総数分のループ
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		// キーを押してて && 使っていたら
		if (pData->Player.bPushKey == true && pData->Bullet[nCnt].bUse == true)
		{
			// 再生
			pSound->PlaySound(CSound::X2SOUND_LABEL::SHOOT);

			// 弾の生成
			CEnemyBullet::Create(D3DXVECTOR3(WorldPos._41, WorldPos._42, WorldPos._43), pData->Bullet[nCnt].Rot, D3DXVECTOR3(5.0f, 5.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "BULLET", 1.0f);

			// マズルフラッシュの生成
			CGunFire::Create(D3DXVECTOR3(WorldPos._41, WorldPos._42, WorldPos._43), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "MASLE_FLASH");
			pData->Bullet[nCnt].bUse = false;
			break;
		}
	}
}

//=============================================================================
// 移動
//=============================================================================
void CEnemy::Move(void)
{
	CSound *pSound = CManager::GetSound();	// サウンドの取得
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// 通信データの取得
	int nMaxModel = CManager::GetGame()->GetMaxModel();	// モデルの総数を取得

	// 位置が変わっていたら
	if (m_PosOld != m_Pos)
	{
		// 再生
		pSound->PlaySound(CSound::X2SOUND_LABEL::FOOT_STEP);
	}

	// 前回の位置を保存
	m_PosOld = m_Pos;

	// 通信データに代入
	m_Pos = pData->Player.Pos;
	m_Rot = pData->Player.Rot;
}

//=============================================================================
// モーション
//=============================================================================
void CEnemy::Motion(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// 通信データの取得

	// モーションに対応したモーションを再生
	switch (pData->Player.Motion)
	{
	case CCommunicationData::MOSTION::NEUTRAL:
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)CModel::MOSTION::NEUTRAL);
			D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
			D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

			CMotion::PlayMotin(Motion, &Pos, &Rot);
			m_pModel[nCnt]->SetPos(Pos);
			m_pModel[nCnt]->SetRot(Rot);
		}
		break;
	case CCommunicationData::MOSTION::WORK:
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)CModel::MOSTION::WORK);
			D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
			D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

			CMotion::PlayMotin(Motion, &Pos, &Rot);
			m_pModel[nCnt]->SetPos(Pos);
			m_pModel[nCnt]->SetRot(Rot);
		}
		break;
	case CCommunicationData::MOSTION::BUCK_WORK:
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)CModel::MOSTION::BUCK_WORK);
			D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
			D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

			CMotion::PlayMotin(Motion, &Pos, &Rot);
			m_pModel[nCnt]->SetPos(Pos);
			m_pModel[nCnt]->SetRot(Rot);
		}
		break;
	case CCommunicationData::MOSTION::ATTACK:
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)CModel::MOSTION::ATTACK);
			D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
			D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

			CMotion::PlayMotin(Motion, &Pos, &Rot);
			m_pModel[nCnt]->SetPos(Pos);
			m_pModel[nCnt]->SetRot(Rot);
		}
		break;
	}
}

//=============================================================================
// ストックカウンタ
//=============================================================================
void CEnemy::StockCnt(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// 通信データの取得

	if (pData->Player.nNumber != 0)
	{
		CCounter *pCounter = CManager::GetGame()->GetCounter(pData->Player.nNumber - 1);
		m_nStock = pData->Player.nStock;

		pCounter->SetCounterNum(m_nStock);
	}
}