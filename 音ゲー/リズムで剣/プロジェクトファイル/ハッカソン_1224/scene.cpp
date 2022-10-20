//=============================================================================
//
// �I�u�W�F�N�g���� [scene.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
vector<CScene*> CScene::m_pObjet[(int)LAYER_TYPE::MAX_LAYER];

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CScene::CScene(LAYER_TYPE Layer)
{
	m_bDeth = false;	// �j������Ă��Ȃ�
	m_nPriority = static_cast<int>(Layer);	// �`�揇�̐ݒ�

	// �z��ɕۑ�
	m_pObjet[m_nPriority].push_back(this);
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
	
}

//=============================================================================
// �S���폜
//=============================================================================
void CScene::ReleaseAll(void)
{
	// ���C���[�����̃��[�v
	for (int nCnt = 0; nCnt < static_cast<int>(LAYER_TYPE::MAX_LAYER); nCnt++)
	{
		// �T�C�Y�̎擾
		int nPrioltySize = m_pObjet[nCnt].size();

		// �T�C�Y�����̃��[�v
		for (int nCntPop = 0; nCntPop < nPrioltySize; nCntPop++)
		{
			// �j��
			delete m_pObjet[nCnt][nCntPop];
		}

		// �T�C�Y�����̃��[�v
		for (int nCntPop = 0; nCntPop < nPrioltySize; nCntPop++)
		{
			// �z�񂩂�j��
			m_pObjet[nCnt].pop_back();
		}
	}
}

//=============================================================================
// �S���X�V
//=============================================================================
void CScene::UpdateAll(void)
{
	// ���C���[�����̃��[�v
	for (int nCnt = 0; nCnt < static_cast<int>(LAYER_TYPE::MAX_LAYER); nCnt++)
	{
		// �T�C�Y�̎擾
		int nUpdateSize = m_pObjet[nCnt].size();

		// �T�C�Y�����̃��[�v
		for (int nCntUpdate = 0; nCntUpdate < nUpdateSize; nCntUpdate++)
		{
			// �j���t���O�������ĂȂ�������
			if (m_pObjet[nCnt][nCntUpdate]->m_bDeth == false)
			{
				// �X�V
				m_pObjet[nCnt][nCntUpdate]->Update();
			}
			// �j���t���O�������Ă���
			else if (m_pObjet[nCnt][nCntUpdate]->m_bDeth == true)
			{
				// �j��
				delete m_pObjet[nCnt][nCntUpdate];
				m_pObjet[nCnt][nCntUpdate] = NULL;
				m_pObjet[nCnt].erase(m_pObjet[nCnt].begin() + nCntUpdate);
			}
		}
	}
}

//=============================================================================
// �S���`��
//=============================================================================
void CScene::DrawAll(void)
{
	// ���C���[�����̃��[�v
	for (int nCnt = 0; nCnt < (int)LAYER_TYPE::MAX_LAYER; nCnt++)
	{
		// �T�C�Y�̎擾
		int nDrawSize = m_pObjet[nCnt].size();

		// �T�C�Y�����̃��[�v
		for (int nCntUpdate = 0; nCntUpdate < nDrawSize; nCntUpdate++)
		{
			// �`��
			m_pObjet[nCnt][nCntUpdate]->Draw();
		}
	}
}