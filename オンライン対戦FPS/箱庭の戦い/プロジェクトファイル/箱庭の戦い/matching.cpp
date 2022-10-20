//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "matching.h"
#include "manager.h"
#include "textureobj.h"
#include "tcp_client.h"
#include "fade.h"
#include "communicationdata.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
bool CMatching::m_bConnect = false;
bool CMatching::m_bEnemyConnect = false;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMatching::CMatching()
{
	m_bEnemyConnect = false;
	m_bConnect = false;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CMatching::~CMatching()
{
	
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CMatching::Init(void)
{
	CTcpClient *pClient = CManager::GetTcpClient();	// 通信クラスの取得

	// 取得出来ていたら
	if (pClient != NULL)
	{
		// 初期化
		pClient->Init();
	}

	// スレッドを生成
	thread th(ConnectTh);

	// スレッドを切り離す
	th.detach();

	// 生成
	CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(250.0f, 50.0f, 0.0f), "MATCHING");

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CMatching::Uninit(void)
{
	CSound *pSound = CManager::GetSound();	// サウンドの取得

	// 破棄
	CScene::ReleaseAll();

	// 再生
	pSound->StopSound(CSound::X2SOUND_LABEL::TITLE);
}

//=============================================================================
// 更新処理
//=============================================================================
void CMatching::Update(void)
{
	CFade *pFade = CManager::GetFade();	// フェードクラスの取得

	// 敵がつながっていて && フェードしていなかったら
	if (m_bEnemyConnect == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
	{
		// ゲーム画面に遷移
		pFade->SetFade(CManager::MODE::GAME);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CMatching::Draw(void)
{

}

//=============================================================================
// 通信スレッド
//=============================================================================
void CMatching::ConnectTh(void)
{
	CTcpClient *pClient = CManager::GetTcpClient();	// 通信クラスの取得
	char aRecvData[MAX_CHARDATA];	// 受信データ

	// つながるまでループ
	while (!m_bConnect)
	{
		m_bConnect = pClient->Connect();
	}
	// 敵がつながるまでループ
	while (!m_bEnemyConnect)
	{
		pClient->Recv(&aRecvData[0], sizeof(bool));
		memcpy(&m_bEnemyConnect, &aRecvData[0], sizeof(bool));
	}
}