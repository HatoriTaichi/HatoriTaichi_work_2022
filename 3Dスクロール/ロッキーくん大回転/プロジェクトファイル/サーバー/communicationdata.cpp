//====================================================
//
// 通信データのヘッダーファイル(communicationdata.cpp)
// Author : 羽鳥 太一
//
//====================================================
//-------------------------------
// インクルード
//-------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include "communicationdata.h"

//-------------------------------
// デフォルトコンストラクタ
//-------------------------------
CCommunicationData::CCommunicationData()
{
	FILE *file;	// ファイルのポインタ

	// ランキングの初期化
	for (int count = 0; count < MAX_RANKING + 1; count++)
	{
		m_CommuData.ranking[count] = 0;
	}

	// ファイルを開く
	file = fopen("data/ranking.txt", "r");

	// ランキング数分のループ
	for (int count = 0; count < MAX_RANKING; count++)
	{
		// ランキングを取得
		fscanf(file, "%d\n", &m_CommuData.ranking[count]);
	}

	// ファイルを閉じる
	fclose(file);
}

//-------------------------------
// デフォルトデストラクタ
//-------------------------------
CCommunicationData::~CCommunicationData()
{

}

//-------------------------------
// ソート
//-------------------------------
void CCommunicationData::RankingSort(int my_score)
{
	vector<int> ranking;	// ランキングの配列
	m_CommuData.ranking[MAX_RANKING] = my_score;	// 最後尾に自分のスコアを代入

	// ランキング数分のループ
	for (int count = 0; count < MAX_RANKING + 1; count++)
	{
		// ランキングの配列に代入
		ranking.push_back(m_CommuData.ranking[count]);
	}

	// ソート(降順)
	sort(ranking.begin(), ranking.end(), std::greater<int>{});

	// ランキング数分のループ
	for (int count = 0; count < MAX_RANKING + 1; count++)
	{
		// ランキングを保存
		m_CommuData.ranking[count] = ranking[count];
	}
}

//-------------------------------
// データのセーブ
//-------------------------------
void CCommunicationData::Save(void)
{
	FILE *file;	// ファイルのポインタ

	// ファイルを開く
	file = fopen("data/ranking.txt", "w");

	// ランキング数分のループ
	for (int count = 0; count < MAX_RANKING; count++)
	{
		// テキストに保存
		fprintf(file, "%d\n", m_CommuData.ranking[count]);
	}

	// ファイルを閉じる
	fclose(file);
}