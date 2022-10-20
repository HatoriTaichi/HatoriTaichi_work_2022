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
	FILE *file;	// �t�@�C���̃|�C���^

	// �����L���O�̏�����
	for (int count = 0; count < MAX_RANKING + 1; count++)
	{
		m_CommuData.ranking[count] = 0;
	}

	// �t�@�C�����J��
	file = fopen("data/ranking.txt", "r");

	// �����L���O�����̃��[�v
	for (int count = 0; count < MAX_RANKING; count++)
	{
		// �����L���O���擾
		fscanf(file, "%d\n", &m_CommuData.ranking[count]);
	}

	// �t�@�C�������
	fclose(file);
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
	vector<int> ranking;	// �����L���O�̔z��
	m_CommuData.ranking[MAX_RANKING] = my_score;	// �Ō���Ɏ����̃X�R�A����

	// �����L���O�����̃��[�v
	for (int count = 0; count < MAX_RANKING + 1; count++)
	{
		// �����L���O�̔z��ɑ��
		ranking.push_back(m_CommuData.ranking[count]);
	}

	// �\�[�g(�~��)
	sort(ranking.begin(), ranking.end(), std::greater<int>{});

	// �����L���O�����̃��[�v
	for (int count = 0; count < MAX_RANKING + 1; count++)
	{
		// �����L���O��ۑ�
		m_CommuData.ranking[count] = ranking[count];
	}
}

//-------------------------------
// �f�[�^�̃Z�[�u
//-------------------------------
void CCommunicationData::Save(void)
{
	FILE *file;	// �t�@�C���̃|�C���^

	// �t�@�C�����J��
	file = fopen("data/ranking.txt", "w");

	// �����L���O�����̃��[�v
	for (int count = 0; count < MAX_RANKING; count++)
	{
		// �e�L�X�g�ɕۑ�
		fprintf(file, "%d\n", m_CommuData.ranking[count]);
	}

	// �t�@�C�������
	fclose(file);
}