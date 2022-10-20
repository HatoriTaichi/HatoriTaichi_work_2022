//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "game.h"
#include "meshfloo.h"
#include "enemy.h"
#include "player.h"
#include "model.h"
#include "tcp_client.h"
#include "singlemodel.h"
#include "sound.h"
#include "meshsphere.h"
#include "camera.h"
#include "manager.h"
#include "counter.h"
#include "textureobj.h"
#include "sound.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGame::CGame()
{
	bool m_bDoOnece = false;
	bool m_bShow = false;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CGame::Init(void)
{
	CTcpClient *pClient = CManager::GetTcpClient();	// 通信クラスの取得
	FILE *pFile;	// ファイルのポインタ
	D3DXVECTOR3 Pos;	// 位置
	D3DXVECTOR3 Rot;	// 向き
	D3DXVECTOR3 Scale;	// スケール
	char aFile[MAX_CHARDATA][MAX_CHARDATA * 2];	// ファイルの文字バッファ
	char RecvData[MAX_CHARDATA];	// 受信データ
	int nNumber;	// 番号

	// 受信
	pClient->Recv(&RecvData[0], sizeof(int));
	memcpy(&nNumber, &RecvData[0], sizeof(int));

	// ファイルを開く
	pFile = fopen("data/Txtdata/stagedata.txt", "r");

	// ファイルが開けていたら
	if (pFile != NULL)
	{
		// 無限ループ
		while (true)
		{
			// 文字を取得
			fscanf(pFile, "%s", &aFile[0]);

			// MODEL_NUMの文字列を見つけたら
			if (strcmp(aFile[0], "MODEL_NUM") == 0)
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nMaxModel);
			}
			// SET_MODELの文字列を見つけたら
			if (strcmp(aFile[0], "SET_MODEL") == 0)
			{
				// 無限ループ
				while (true)
				{
					// 文字を取得
					fscanf(pFile, "%s", &aFile[0]);

					// MODEL_INDXの文字列を見つけたら
					if (strcmp(aFile[0], "MODEL_INDX") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &m_nType);
					}
					// POSの文字列を見つけたら
					else if (strcmp(aFile[0], "POS") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f%f%f", &Pos.x, &Pos.y, &Pos.z);
					}
					// ROTの文字列を見つけたら
					else if (strcmp(aFile[0], "ROT") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f%f%f", &Rot.x, &Rot.y, &Rot.z);
					}
					// RSCALEの文字列を見つけたら
					else if (strcmp(aFile[0], "RSCALE") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f%f%f", &Scale.x, &Scale.y, &Scale.z);
					}
					// END_MODELSETの文字列を見つけたら
					else if (strcmp(aFile[0], "END_MODELSET") == 0)
					{
						// 取得した情報で生成
						m_pSingleModel.push_back(CSingleModel::Create(Pos, Rot, Scale, (CModel::TYPE)m_nType));
						break;
					}
				}
			}
			//ENDの文字列を見つけたら
			else if (strcmp(aFile[0], "END") == 0)
			{
				break;
			}
		}
	}
	else
	{
		printf("テクスチャデータが読み取れませんでした。");
	}

	// ファイルを閉じる
	fclose(pFile);

	// ステージの要素の生成
	CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 32, 8, 3200.0f, "SKY");
	CMeshFloo::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20, 20, 4100.0, 4100.0f, "SEE");
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f + 50.0f, 0.0f), D3DXVECTOR3(250.0f, 175.0f, 0.0f), "PLAYER_DIVIDE");
	CUiObj::Create(D3DXVECTOR3(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT - 100.0f, 0.0f), D3DXVECTOR3(150.0f, 100.0f, 0.0f), "WEAPONFRAME");
	CUiObj::Create(D3DXVECTOR3((SCREEN_WIDTH - 150.0f), (SCREEN_HEIGHT - 100.0f) - 45.0f, 0.0f), D3DXVECTOR3(100.0f, 45.0f, 0.0f), "WEAPON_VECTOR");
	CUiObj::Create(D3DXVECTOR3((SCREEN_WIDTH - 150.0f) + 50.0f, (SCREEN_HEIGHT - 100.0f) + 50.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "AMMOFRAME");
	CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), "BULLET");
	m_pMaxAmmo = CCounter::Create(D3DXVECTOR3(((SCREEN_WIDTH - 150.0f) + 50.0f) + 20.0f, ((SCREEN_HEIGHT - 100.0f) + 50.0f) + 15.0f, 0.0f), D3DXVECTOR3(15.0f, 25.0f, 0.0f), 2, "NUMBER_00");
	m_pMaxAmmo->AddCounter(30);
	m_pAmmo = CCounter::Create(D3DXVECTOR3(((SCREEN_WIDTH - 150.0f) + 50.0f) - 60.0f, ((SCREEN_HEIGHT - 100.0f) + 50.0f) - 15.0f, 0.0f), D3DXVECTOR3(15.0f, 25.0f, 0.0f), 2, "NUMBER_00");
	m_pAmmo->AddCounter(30);
	m_pKiilCount.push_back(CCounter::Create(D3DXVECTOR3(SCREEN_CENTER_X + 70.0f, 0.0f + 50.0f, 0.0f), D3DXVECTOR3(45.0f, 50.0f, 0.0f), 2, "NUMBER_P1"));
	m_pKiilCount.push_back(CCounter::Create(D3DXVECTOR3(SCREEN_CENTER_X - 170.0f, 0.0f + 50.0f, 0.0f), D3DXVECTOR3(45.0f, 50.0f, 0.0f), 2, "NUMBER_P2"));

	// プレイヤー番号でスポーン位置を変える
	if (nNumber == 1)
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(-650.0f, 100.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else if (nNumber == 2)
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(650.0f, 100.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	m_pPlayer->SetIndex(nNumber);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CGame::Uninit(void)
{
	// 破棄
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	// マウスの処理
	MouseProcess();

	// 勝敗処理
	WinOrLoss();
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// 勝敗
//=============================================================================
void CGame::WinOrLoss(void)
{
	CSound *pSound = CManager::GetSound();	// サウンドの取得
	CCommunicationData::COMMUNICATION_DATA *pData = m_pEnemy->GetCommuData();	// 通信データの取得
	int nStock[MAX_PLAYER];	// ストック

	// ストックを取得
	nStock[0] = m_pPlayer->GetStock();
	nStock[1] = m_pEnemy->GetStock();

	// 負けたら
	if (nStock[0] <= 0 && m_bDoOnece == false)
	{
		// 再生
		pSound->PlaySound(CSound::X2SOUND_LABEL::LOSE);

		// 文字の生成
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f + 250.0f, 0.0f), D3DXVECTOR3(150.0f, 75.0f, 0.0f), "LOSE");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f + 475.0f, 0.0f), D3DXVECTOR3(250.0f, 60.0f, 0.0f), "RESTART");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X - 200.0f, 0.0f + 760.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "YES");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X + 200.0f, 0.0f + 760.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "NO");
		pData->Player.bPushKey = false;
		for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
		{
			pData->Bullet[nCnt].bUse = false;
		}
		m_pPlayer->SetEndBattle(true);
		m_bDoOnece = true;
	}
	// 買ったら
	else if (nStock[1] <= 0 && m_bDoOnece == false)
	{
		// 再生
		pSound->PlaySound(CSound::X2SOUND_LABEL::WIN);

		// 文字の生成
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f + 250.0f, 0.0f), D3DXVECTOR3(150.0f, 75.0f, 0.0f), "WIN");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f + 475.0f, 0.0f), D3DXVECTOR3(250.0f, 60.0f, 0.0f), "RESTART");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X - 200.0f, 0.0f + 760.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "YES");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X + 200.0f, 0.0f + 760.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "NO");
		pData->Player.bPushKey = false;
		for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
		{
			pData->Bullet[nCnt].bUse = false;
		}
		m_pPlayer->SetEndBattle(true);
		m_bDoOnece = true;
	}
}

//=============================================================================
// マウス関連
//=============================================================================
void CGame::MouseProcess(void)
{
	CTcpClient *pClient = CManager::GetTcpClient();	// 通信クラスの取得

	// バトルが終わってなかったら
	if (m_pPlayer->GetEndBattle() == false)
	{
		// 中心にマウスを固定
		SetCursorPos(SCREEN_CENTER_X, SCREEN_CENTER_Y);

		// カーソルを消す
		if (m_bShow == false)
		{
			ShowCursor(FALSE);
			m_bShow = true;
		}
	}
	else
	{
		// カーソルを出す
		if (m_bShow == true)
		{
			pClient->Uninit();

			ShowCursor(TRUE);
			m_bShow = false;
		}
	}
}