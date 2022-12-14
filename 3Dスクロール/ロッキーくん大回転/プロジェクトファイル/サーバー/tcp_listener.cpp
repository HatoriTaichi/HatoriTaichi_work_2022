//====================================================
//
// サーバークラス(tcp_listener.cpp)
// Author : 羽鳥 太一
//
//====================================================
//-------------------------------
// インクルード
//-------------------------------
#include "tcp_listener.h"

//-------------------------------
// デフォルトコンストラクタ
//-------------------------------
CTcpListener::CTcpListener()
{
	m_sockServer = INVALID_SOCKET;
}

//-------------------------------
// デフォルトデストラクタ
//-------------------------------
CTcpListener::~CTcpListener()
{

}

//-------------------------------
// 初期化
//-------------------------------
bool CTcpListener::Init(void)
{
	FILE *pFile;	// ファイルのポインタ
	char aFile[64];	// ファイルの文字バッファ
	int nPort;	// ポート番号
	int nWait;	// 接続待ち人数

	// ファイルを開く
	pFile = fopen("data/severdata.txt", "r");

	// ファイルが開けていたら
	if (pFile != NULL)
	{
		// 無限ループ
		while (true)
		{
			// 文字を取得
			fscanf(pFile, "%s", &aFile[0]);

			// PORT_NUMの文字列を見つけたら
			if (strcmp(&aFile[0], "PORT_NUM") == 0)
			{
				fscanf(pFile, "%s", &aFile[1]);
				fscanf(pFile, "%d", &nPort);
			}
			// MAX_WAITの文字列を見つけたら
			if (strcmp(&aFile[0], "MAX_WAIT") == 0)
			{
				fscanf(pFile, "%s", &aFile[1]);
				fscanf(pFile, "%d", &nWait);
			}
			//END_SCRIPTの文字列を見つけたら
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
	}
	else
	{
		printf("サーバーデータが読み取れませんでした。");
	}

	// ファイルを閉じる
	fclose(pFile);

	//------------------------
	// ソケット作成
	//------------------------
	m_sockServer = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sockServer == INVALID_SOCKET)
	{
		printf("接続待ちソケットが作れませんでした。");
		return false;
	}

	//------------------------
	// 受付準備
	//------------------------
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;	// どの通信か
	addr.sin_port = htons(nPort);	// ポート番号
	addr.sin_addr.S_un.S_addr = INADDR_ANY;	// 誰でもアクセスできる

	bind(m_sockServer,
		(struct sockaddr*)&addr,
		sizeof(addr));

	listen(m_sockServer, nWait);	// 最大待機数

	return true;
}

//-------------------------------
// 接続受付
//-------------------------------
CCommunication * CTcpListener::Accept(void)
{
	CCommunication *pSendRecv = new CCommunication;

	//------------------------
	// 接続待ち
	//------------------------
	struct sockaddr_in clientAddr;
	int nLength = sizeof(clientAddr);

	// 通信待ち
	SOCKET sock = accept(	m_sockServer,
							(struct sockaddr*)&clientAddr,
							&nLength);

	printf("接続出来ました。\n");
	if (pSendRecv != NULL)
	{
		pSendRecv->Init(sock);
	}

	return pSendRecv;
}

//-------------------------------
// 終了
//-------------------------------
void CTcpListener::Uninit(void)
{
	if (m_sockServer == INVALID_SOCKET)
	{
		return;
	}

	//------------------------
	// 接続切断
	//------------------------
	printf("接続を切断します。\n");
	closesocket(m_sockServer);	// 接続受付用ソケット
	m_sockServer = INVALID_SOCKET;
}