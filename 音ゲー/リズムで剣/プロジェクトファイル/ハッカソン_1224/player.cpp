//=============================================================================
//
// ���͏��� [input.cpp]
// Author : �O���B
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyinput.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CPlayer::CPlayer()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	CScene2D::SetTexType(m_Type);
	CScene2D::Init();
	CScene2D::SetPos(m_Pos);
	CScene2D::SetSize(m_Size);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �U�����łȂ��Ȃ�
	if (!m_bNowAttack)
	{
		Attack();
	}

	// �U�����Ȃ�
	else
	{
		if (m_nAttackTime == 0)
		{
			switch (m_nMoveDirection)
			{
			case CKeyboard::UP:
				m_Pos.y -= m_fMove;
				break;
			case CKeyboard::LEFT:
				m_Pos.x -= m_fMove;
				break;
			case CKeyboard::DOWN:
				m_Pos.y += m_fMove;
				break;
			case CKeyboard::RIGHT:
				m_Pos.x += m_fMove;
				break;
			}
			m_fMove -= 0.1f;
		}

		if (m_fMove <= 0.0f)
		{
			m_nAttackTime++;

			if (m_nAttackTime > m_nMaxAttackTime ||
				Attack())
			{
				m_fMove = 2.5f;
				m_bNowAttack = false;
				m_nMoveDirection = 0;
				m_nAttackTime = 0;
				m_Pos = m_PosFix;
			}
		}
	}

	// �U�����łȂ��Ȃ�
	if (!m_bNowAttack)
	{
		Attack();
	}

	CScene2D::SetPos(m_Pos);

	CScene2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string type)
{
	CPlayer *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
	}

	pPlayer->m_Pos = pos;
	pPlayer->m_Size = size;
	pPlayer->m_Type = type;
	pPlayer->m_nMoveDirection = 0;
	pPlayer->m_bNowAttack = false;
	pPlayer->m_nAttackTime = 0;
	pPlayer->m_fMove = 2.5f;

	if (pPlayer != NULL)
	{
		pPlayer->Init();
	}

	return pPlayer;
}

bool CPlayer::Attack(void)
{
	CKeyboard *pKey = CManager::GetKeyboard();

	// ��
	if (pKey->GetTrigger(pKey->UP))
	{
		m_bNowAttack = true;
		m_nMoveDirection = pKey->UP;
		m_Pos.y -= m_fPosMoveStart;
		CScene2D::SetTex(3, 5, 1);
		return true;
	}

	// ��
	if (pKey->GetTrigger(pKey->LEFT))
	{
		m_bNowAttack = true;
		m_nMoveDirection = pKey->LEFT;
		m_Pos.x -= m_fPosMoveStart;
		CScene2D::SetTex(1, 5, 1);
		return true;
	}

	// ��
	if (pKey->GetTrigger(pKey->DOWN))
	{
		m_bNowAttack = true;
		m_nMoveDirection = pKey->DOWN;
		m_Pos.y += m_fPosMoveStart;
		CScene2D::SetTex(4, 5, 1);
		return true;
	}

	// �E
	if (pKey->GetTrigger(pKey->RIGHT))
	{
		m_bNowAttack = true;
		m_nMoveDirection = pKey->RIGHT;
		m_Pos.x += m_fPosMoveStart;
		CScene2D::SetTex(2, 5, 1);
		return true;
	}
	if (m_Pos == D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f))
	{
		CScene2D::SetTex(0, 5, 1);
	}

	return false;
}