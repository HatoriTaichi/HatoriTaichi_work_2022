//=============================================================================
//
// �����蔻��̏��� [collision.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "collision.h"
#include "manager.h"
#include "fade.h"
#include "mouseinput.h"
#include "fade.h"
#include "Notes.h"
#include "keyinput.h"
#include "enemy.h"
#include "counter.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CCollision::CCollision()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CCollision::~CCollision()
{

}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CCollision::Init(void)
{
	CScene2D::SetTexType(m_TexType);	// �e�N�X�`���̐ݒ�
	CScene2D::Init();	// ������
	CScene2D::SetPos(m_Pos);	// �ʒu�̐ݒ�
	CScene2D::SetSize(D3DXVECTOR3(m_Size.x, m_Size.y, 0.0f));	// �T�C�Y�̐ݒ�

	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CCollision::Uninit(void)
{
	// �j��
	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CCollision::Update(void)
{
	CKeyboard *pKey = CManager::GetKeyboard();	// �L�[�{�[�h�̎擾
	CSound *pSound = CManager::GetSound();	// �T�E���h�̎擾
	CCounter *pCombo = CManager::GetGame()->GetCombo();	// �R���{�J�E���^�[�̎擾
	CCounter *pScore = CManager::GetGame()->GetScore();	// �X�R�A�̎擾
	D3DXVECTOR3 Pos = CScene2D::GetPos();	// �ʒu�̎擾
	D3DXVECTOR2 Size = CScene2D::GetSize();	// �T�C�Y�̎擾

	// �ړ�
	Pos.y += 1.0f;

	// �e�N�X�`���̃^�C�v�ɂ���ď�������
	if (m_TexType == "LEFT_ARROWFRAME" ||
		m_TexType == "RIGHT_ARROWFRAME")
	{
		// �T�C�Y��ς���
		Size.x -= 1.0f;
		Size.y -= 0.5f;

		// �m�[�c��������Ȃ�
		if ((m_pNoets->GetSize().x * MAX_EXTENSION) >= Size.x &&
			(m_pNoets->GetSize().y * MAX_EXTENSION) >= Size.y)
		{
			// �L�[����������
			if (pKey->GetTrigger(pKey->LEFT) == true || pKey->GetTrigger(pKey->RIGHT) == true)
			{
				m_pNoets->GetEnemy()->SetUse(true);	// �j��
				pSound->Play(CSound::SOUND_LABEL_SE_TAP);	//�Đ�
				pCombo->AddCounter(1);	// �J�E���^�[���Z
				pScore->AddCounter(1000);	// �X�R�A���Z
			}
		}
		else if ((m_pNoets->GetSize().x * MIN_EXTENSION) >= Size.x &&
				 (m_pNoets->GetSize().y * MIN_EXTENSION) >= Size.y)
		{
			// �L�[����������
			if (pKey->GetTrigger(pKey->LEFT) == true || pKey->GetTrigger(pKey->RIGHT) == true)
			{
				m_pNoets->GetEnemy()->SetUse(true);	// �j��
				pSound->Play(CSound::SOUND_LABEL_SE_TAP);	//�Đ�
				pCombo->AddCounter(1);	// �J�E���^�[���Z
				pScore->AddCounter(500);	// �X�R�A���Z
			}
		}
		else if ((m_pNoets->GetSize().x * MAX_EXTENSION) <= Size.x &&
				 (m_pNoets->GetSize().y * MAX_EXTENSION) <= Size.y)
		{
			// �L�[����������
			if (pKey->GetTrigger(pKey->LEFT) == true || pKey->GetTrigger(pKey->RIGHT) == true)
			{
				m_pNoets->GetEnemy()->SetbMove(true);	// �j��
				pCombo->SetCounterNum(0);	// ���Z���Ȃ�
			}
		}
	}
	// �e�N�X�`���̃^�C�v�ɂ���ď�������
	else if (m_TexType == "UP_ARROWFRAME" ||
			 m_TexType == "DOWN_ARROWFRAME")
	{
		// �T�C�Y��ς���
		Size.x -= 0.5f;
		Size.y -= 1.0f;

		// �m�[�c��������Ȃ�
		if ((m_pNoets->GetSize().x * MAX_EXTENSION) >= Size.x &&
			(m_pNoets->GetSize().y * MAX_EXTENSION) >= Size.y)
		{
			// �L�[����������
			if (pKey->GetTrigger(pKey->UP) == true || pKey->GetTrigger(pKey->DOWN) == true)
			{
				m_pNoets->GetEnemy()->SetUse(true);	// �j��
				pSound->Play(CSound::SOUND_LABEL_SE_TAP);	//�Đ�
				pCombo->AddCounter(1);	// �J�E���^�[���Z
				pScore->AddCounter(1000);	// �X�R�A���Z
			}
		}
		else if ((m_pNoets->GetSize().x * MIN_EXTENSION) >= Size.x &&
				 (m_pNoets->GetSize().y * MIN_EXTENSION) >= Size.y)
		{
			// �L�[����������
			if (pKey->GetTrigger(pKey->LEFT) == true || pKey->GetTrigger(pKey->RIGHT) == true)
			{
				m_pNoets->GetEnemy()->SetUse(true);	// �j��
				pSound->Play(CSound::SOUND_LABEL_SE_TAP);	//�Đ�
				pCombo->AddCounter(1);	// �J�E���^�[���Z
				pScore->AddCounter(500);	// �X�R�A���Z
			}
		}
		else if ((m_pNoets->GetSize().x * MAX_EXTENSION) <= Size.x &&
				 (m_pNoets->GetSize().y * MAX_EXTENSION) <= Size.y)
		{
			// �L�[����������
			if (pKey->GetTrigger(pKey->UP) == true || pKey->GetTrigger(pKey->DOWN) == true)
			{
				m_pNoets->GetEnemy()->SetbMove(true);	// �j��
				pCombo->SetCounterNum(0);	// ���Z���Ȃ�
			}
		}
	}

	// �ʒu��ݒ�
	CScene2D::SetPos(Pos);

	// �T�C�Y��ݒ�
	CScene2D::SetSize(D3DXVECTOR3(Size.x, Size.y, 0.0f));

	// �|���S���̍X�V
	CScene2D::Update();

	// �^�C�~���O�𓦂�����
	if ((m_pNoets->GetSize().x * MIN_EXTENSION) >= Size.x &&
		(m_pNoets->GetSize().y * MIN_EXTENSION) >= Size.y)
	{
		// �j��
		m_pNoets->GetEnemy()->SetbMove(true);
		m_pNoets->Uninit();
		m_pNoets = NULL;
		Uninit();
	}
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CCollision::Draw(void)
{
	// �`��
	CScene2D::Draw();
}

//=============================================================================
// ����
//=============================================================================
CCollision *CCollision::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, string Type, CNotes *pNotes)
{
	CCollision *pCollision = NULL;	// �����蔻��̃|�C���^

	// NULL��������
	if (pCollision == NULL)
	{
		// ����
		pCollision = new CCollision;
	}

	// �����̑��
	pCollision->m_Pos = pos;
	pCollision->m_Size = size;
	pCollision->m_TexType = Type;
	pCollision->m_pNoets = pNotes;

	// ��������Ă�����
	if (pCollision != NULL)
	{
		// ������
		pCollision->Init();
	}
	return pCollision;
}