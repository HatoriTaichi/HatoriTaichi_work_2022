//=============================================================================
//
// �m�[�c���� [notes.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "notes.h"
#include "manager.h"
#include "fade.h"
#include "mouseinput.h"
#include "fade.h"
#include "collision.h"
#include "enemy.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CNotes::CNotes()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CNotes::~CNotes()
{

}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CNotes::Init(void)
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
void CNotes::Uninit(void)
{
	// �j��
	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CNotes::Update(void)
{
	D3DXVECTOR3 Pos = CScene2D::GetPos();	// �ʒu�̎擾
	D3DXVECTOR2 Size = CScene2D::GetSize();	// �T�C�Y�̎擾

	// �ʒu���ړ�
	Pos.y += 1.0f;

	// �ʒu���̍X�V
	CScene2D::SetPos(Pos);

	// �X�V
	CScene2D::Update();
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CNotes::Draw(void)
{
	// �`��
	CScene2D::Draw();
}

//=============================================================================
// �C���N���[�h
//=============================================================================
CNotes *CNotes::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, string Type)
{
	CNotes *pNotes = NULL;	// �m�[�c�̃|�C���^

	// NULL�Ȃ�
	if (pNotes == NULL)
	{
		// ����
		pNotes = new CNotes;
	}

	// �����̑��
	pNotes->m_Pos = pos;
	pNotes->m_Size = size;
	pNotes->m_TexType = Type;

	// �e�N�X�`���ɂ���Đݒ��ς���
	if (Type == "RIGHT_ARROW")
	{
		pNotes->m_pCollision = CCollision::Create(pos, D3DXVECTOR2(size.x * 2, size.y * 2), "RIGHT_ARROWFRAME", pNotes);
		pNotes->m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), "ENEMY_LEFT");
	}
	else if (Type == "LEFT_ARROW")
	{
		pNotes->m_pCollision = CCollision::Create(pos, D3DXVECTOR2(size.x * 2, size.y * 2), "LEFT_ARROWFRAME", pNotes);
		pNotes->m_pEnemy = CEnemy::Create(D3DXVECTOR3(0.0f, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), "ENEMY_RIGHT");
	}
	else if (Type == "UP_ARROW")
	{
		pNotes->m_pCollision = CCollision::Create(pos, D3DXVECTOR2(size.x * 2, size.y * 2), "UP_ARROWFRAME", pNotes);
		pNotes->m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), "ENEMY_DOWN");
	}
	else if (Type == "DOWN_ARROW")
	{
		pNotes->m_pCollision = CCollision::Create(pos, D3DXVECTOR2(size.x * 2, size.y * 2), "DOWN_ARROWFRAME", pNotes);
		pNotes->m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), "ENEMY_UP");
	}

	// ������Ă�����
	if (pNotes != NULL)
	{
		// ������
		pNotes->Init();
	}
	return pNotes;
}