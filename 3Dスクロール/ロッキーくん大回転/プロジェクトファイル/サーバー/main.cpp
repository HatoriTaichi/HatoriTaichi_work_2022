//==================================================
//
// メインCPP(main.cpp)
// Author：羽鳥太一
//
//==================================================
//------------------------
// インクルード
//------------------------
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <thread>
#include "main.h"
#include "tcp_listener.h"
#include "communication.h"
#include "communicationdata.h"

//------------------------
// グローバル変数
//------------------------
int g_accept_count = 0;
int g_stop = 1;

//------------------------
// メイン関数
//------------------------
void main(void)
{
#ifdef _DEBUG
	int size = sizeof(CCommunicationData::COMMUNICATION_DATA);
#endif // _DEBUG
	//------------------------
	// 初期化
	//------------------------
	WSADATA  wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);

	if (nErr != 0)
	{
		cout << "初期化に失敗しました" << endl;
	}

	// サーバーの生成
	CTcpListener *pListenner = new CTcpListener;

	// サーバーが生成されてたら && 初期化が成功してたら
	if (pListenner != NULL && pListenner->Init() == true)
	{
		// スレッドを生成
		thread th(StopOrSurver);

		// スレッドを切り離す
		th.detach();

		// サーバーがあったら無限ループ
		while (pListenner != NULL)
		{
			// 接続数が十人以下なら
			if (g_accept_count <= 10)
			{
				// スレッドを生成
				thread th(Accept, pListenner);

				// スレッドを切り離す
				th.detach();
			}
			if (g_stop == 0)
			{
				break;
			}
		}
	}
	if (pListenner != NULL)
	{
		pListenner->Uninit();
		delete pListenner;
		pListenner = NULL;
	}

	//------------------------
	// 終了
	//------------------------
	cout << "終了します。"<< endl;
	cout << "何かキーを押してください。"<< endl;
	KeyWait();
	WSACleanup();
}

//------------------------
// 接続待ち
//------------------------
void Accept(CTcpListener *listener)
{
	// 通信クラス
	CCommunication *communication;

	// 接続カウント
	g_accept_count++;

	// 接続待ち
	communication = listener->Accept();

	// カウントを出力
	cout << "g_accept_count->" << g_accept_count << endl;

	// スレッドを生成
	thread th(RankCommunication, communication);

	// スレッドを切り離す
	th.detach();
}

//------------------------
// ランキング送信受信
//------------------------
void RankCommunication(CCommunication *communication)
{
	CCommunicationData commu_data;	// 通信データクラス
	CCommunicationData::COMMUNICATION_DATA *data = commu_data.GetCommuData();	// 通信データを取得
	char recv_data[MAX_COMMUDATA];	// 受信データ
	char send_data[MAX_COMMUDATA];	// 送信データ
	int my_score;	// 自分のスコア

	// 受信
	communication->Recv(&recv_data[0], sizeof(int));

	// スコアをコピー
	memcpy(&my_score, recv_data, sizeof(int));

	// スコアをソート
	commu_data.RankingSort(my_score);

	// ソートしたスコアをコピー
	memcpy(&send_data, &data->ranking, sizeof(CCommunicationData::COMMUNICATION_DATA::ranking));

	// ソートしたスコアを送信
	communication->Send(&send_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA::ranking));

	// ランキングをセーブ
	commu_data.Save();

	// 終了
	communication->Uninit();

	// 接続数を減らす
	g_accept_count--;

	// 画面に出力
	cout << "g_accept_count->" << g_accept_count << endl;
}

//------------------------
// 選択処理
//------------------------
void StopOrSurver(void)
{
	cin >> g_stop;
}

//------------------------
// キー入力待ち
//------------------------
void KeyWait(void)
{
	rewind(stdin);
	getchar();
}