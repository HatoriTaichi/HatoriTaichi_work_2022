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
	for (int count = 0; count < MAX_RANKING + 1; count++)
	{
		m_CommuData.ranking[count] = 0;
	}
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
	vector<int> ranking;	// 配列
	m_CommuData.ranking[MAX_RANKING] = my_score;	// 配列の最後に代入

	// ランキング分のループ
	for (int count = 0; count < MAX_RANKING + 1; count++)
	{
		// 配列を代入
		ranking.push_back(m_CommuData.ranking[count]);
	}

	// ソート(降順)
	sort(ranking.begin(), ranking.end(), std::greater<int>{});

	// ランキング分のループ
	for (int count = 0; count < MAX_RANKING + 1; count++)
	{
		// ランキングの保存
		m_CommuData.ranking[count] = ranking[count];
	}
}