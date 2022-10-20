//=============================================================================
//
// �I�u�W�F�N�g���� [object.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "object.h"
#include "pause.h"
#include "manager.h"
#include "game01.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
vector<CObject*> CObject::m_object[(int)PRIORITY::MAX];

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CObject::CObject(PRIORITY priolty)
{
	// ������
	m_obj_type = OBJTYPE::NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_deth = false;

	// �`�揇�̐ݒ�
	m_priority = static_cast<int>(priolty);

	// �z��Ɏ������i�[
	m_object[m_priority].push_back(this);
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CObject::~CObject()
{
	
}

//=============================================================================
// �S���폜
//=============================================================================
void CObject::ReleaseAll(void)
{
	// �`�揇���̃��[�v
	for (int nCnt = 0; nCnt < static_cast<int>(PRIORITY::MAX); nCnt++)
	{
		// ���̃T�C�Y���擾
		int nPrioltySize = m_object[nCnt].size();

		// �T�C�Y���̃��[�v
		for (int nCntPop = 0; nCntPop < nPrioltySize; nCntPop++)
		{
			// ���̃^�C�v�ȊO�Ȃ�
			if (m_object[nCnt][nCntPop]->m_priority != static_cast<int>(PRIORITY::FADE) &&
				m_object[nCnt][nCntPop]->m_priority != static_cast<int>(PRIORITY::HISTORY_LETTER))
			{
				// �j��
				delete m_object[nCnt][nCntPop];
			}
		}

		// ���̃T�C�Y���擾
		nPrioltySize = m_object[nCnt].size();

		// �T�C�Y���̃��[�v
		for (int nCntPop = 0; nCntPop < nPrioltySize; nCntPop++)
		{
			// ���̃^�C�v�ȊO�Ȃ�
			if (m_object[nCnt][nCntPop]->m_priority != static_cast<int>(PRIORITY::FADE)  &&
				m_object[nCnt][nCntPop]->m_priority != static_cast<int>(PRIORITY::HISTORY_LETTER))
			{
				// �z�񂩂�폜
				m_object[nCnt].pop_back();
				nPrioltySize = m_object[nCnt].size();
				nCntPop--;
			}
		}
	}
}

//=============================================================================
// �S���X�V
//=============================================================================
void CObject::UpdateAll(void)
{
	// �`�揇���̃��[�v
	for (int count_priolty = 0; count_priolty < static_cast<int>(PRIORITY::MAX); count_priolty++)
	{
		// ���̃T�C�Y���擾
		int object_size = m_object[count_priolty].size();

		// �T�C�Y���̃��[�v
		for (int count_object = 0; count_object < object_size; count_object++)
		{
			// �j���t���O�������Ă���
			if (m_object[count_priolty][count_object]->m_deth == true)
			{
				// �j��
				delete m_object[count_priolty][count_object];
				m_object[count_priolty][count_object] = NULL;
				m_object[count_priolty].erase(m_object[count_priolty].begin() + count_object);
				object_size = m_object[count_priolty].size();
				count_object--;
			}
			// ����ȊO
			else
			{
				// �Q�[����ʂȂ�
				if (CManager::GetMode() == CManager::MODE::GAME01)
				{
					// �|���S���|�[�Y���Ă���
					if (CPause::GetPause() == false)
					{
						// �Z���t���o���Ė���������
						if (CManager::GetInstance()->GetGame01()->GetDialog() == false)
						{
							// �X�V
							m_object[count_priolty][count_object]->Update();
						}
						// ����ȊO
						else
						{
							// �����̕`�揇������Ȃ�
							if (count_priolty == static_cast<int>(PRIORITY::GAME) || count_priolty == static_cast<int>(PRIORITY::FADE) ||
								count_priolty == static_cast<int>(PRIORITY::CLICK_EFFECT) || count_priolty == static_cast<int>(PRIORITY::NEXT_DIALOG_UI) ||
								count_priolty == static_cast<int>(PRIORITY::DIALOG))
							{
								// �X�V
								m_object[count_priolty][count_object]->Update();
							}
						}
					}
					// ����ȊO
					else
					{
						// �����̕`�揇������Ȃ�
						if (count_priolty == static_cast<int>(PRIORITY::PAUSE) || count_priolty == static_cast<int>(PRIORITY::FADE) || count_priolty == static_cast<int>(PRIORITY::CLICK_EFFECT) || count_priolty == static_cast<int>(PRIORITY::HISTORY_LETTER))
						{
							// �X�V
							m_object[count_priolty][count_object]->Update();
						}
					}
				}
				// ����ȊO
				else
				{
					// �X�V
					m_object[count_priolty][count_object]->Update();
				}
			}
		}
	}
}

//=============================================================================
// �S���`��
//=============================================================================
void CObject::DrawAll(void)
{
	// �`�揇���̃��[�v
	for (int count_priolty = 0; count_priolty < static_cast<int>(PRIORITY::MAX); count_priolty++)
	{
		// ���̃T�C�Y���擾
		int object_size = m_object[count_priolty].size();

		// �T�C�Y���̃��[�v
		for (int count_object = 0; count_object < object_size; count_object++)
		{
			// �j���t���O�������Ė���������
			if (m_object[count_priolty][count_object]->m_deth == false)
			{
				// �`��
				m_object[count_priolty][count_object]->Draw();
			}
		}
	}
}

//================================================
//�v���C�I���e�B�ݒ菈��
//================================================
void CObject::SetPriority(const int &nPriority)
{
	m_object[nPriority].push_back(this);	// �ݒ肵�����`�揇�Ɏ���������

	int nthis_priority = this->m_priority;	// ���̕`�揇
	int object_size = m_object[nthis_priority].size();	// ���̃T�C�Y���擾

	// �T�C�Y���̃��[�v
	for (int count_object = 0; count_object < object_size; count_object++)
	{
		// �����Ȃ�
		if (m_object[nthis_priority][count_object] == this)
		{
			// �z�񂩂�폜
			m_object[nthis_priority].erase(m_object[nthis_priority].begin() + count_object);
			object_size = m_object[nthis_priority].size();
			break;
		}
	}

	// �`�揇��ۑ�
	this->m_priority = nPriority;
}
