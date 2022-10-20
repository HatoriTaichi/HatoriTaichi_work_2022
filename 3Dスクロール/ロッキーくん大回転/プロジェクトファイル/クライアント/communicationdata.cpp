//====================================================
//
// �ʐM�f�[�^�̃w�b�_�[�t�@�C��(communicationdata.cpp)
// Author : �H�� ����
//
//====================================================
//-------------------------------
// �C���N���[�h
//-------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include "communicationdata.h"

//-------------------------------
// �f�t�H���g�R���X�g���N�^
//-------------------------------
CCommunicationData::CCommunicationData()
{
	for (int count = 0; count < MAX_RANKING + 1; count++)
	{
		m_CommuData.ranking[count] = 0;
	}
}

//-------------------------------
// �f�t�H���g�f�X�g���N�^
//-------------------------------
CCommunicationData::~CCommunicationData()
{
	
}

//-------------------------------
// �\�[�g
//-------------------------------
void CCommunicationData::RankingSort(int my_score)
{
	vector<int> ranking;	// �z��
	m_CommuData.ranking[MAX_RANKING] = my_score;	// �z��̍Ō�ɑ��

	// �����L���O���̃��[�v
	for (int count = 0; count < MAX_RANKING + 1; count++)
	{
		// �z�����
		ranking.push_back(m_CommuData.ranking[count]);
	}

	// �\�[�g(�~��)
	sort(ranking.begin(), ranking.end(), std::greater<int>{});

	// �����L���O���̃��[�v
	for (int count = 0; count < MAX_RANKING + 1; count++)
	{
		// �����L���O�̕ۑ�
		m_CommuData.ranking[count] = ranking[count];
	}
}