//=============================================================================
//
// �e���� [bullet.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "bullet.h"
#include "mouseinput.h"
#include "manager.h"
#include "player.h"
#include "game.h"
#include "model.h"
#include "singlemodel.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CBullet::CBullet()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CBullet::Init(void)
{
	// ������
	CBilboard::Init();

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CBullet::Uninit(void)
{
	// �j��
	CBilboard::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CBullet::Update(void)
{
	CMouse *pMouse = CManager::GetMouse();	// �}�E�X�̎擾
	CPlayer *pPlayer = CManager::GetGame()->GetPlayer();	// �v���C���[�̎擾
	D3DXVECTOR3 Pos = CBilboard::GetPos();	// �ʒu�̎擾
	D3DXVECTOR3 Rot = CBilboard::GetRot();	// �����̎擾
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();	// �v���C���[�̈ʒu�̎擾
	D3DXVECTOR3 PosOld;	// �O��̈ʒu
	int nMaxModel = CManager::GetGame()->GetMaxModel();	// ���f���̑���

	// �O��̈ʒu
	PosOld = Pos;

	// �ړ���
	m_fMove += m_fMoveSpeed;

	// �ړ�
	Pos.x += (sinf(Rot.y) * sinf(Rot.x)) * m_fMove;
	Pos.y +=  cosf(Rot.y)				 * m_fMove;
	Pos.z += (sinf(Rot.y) * cosf(Rot.x)) * m_fMove;

	// �ʒu�ƌ����̐ݒ�
	CBilboard::SetPos(Pos);
	CBilboard::SetRot(Rot);

	// �X�V
	CBilboard::Update();

	// �͈͊O�ɏo����j��
	if (Pos.x >= 1000.0f)
	{
		Uninit();
	}
	else if (Pos.x <= -1000.0f)
	{
		Uninit();
	}

	if (Pos.y >= 1000.0f)
	{
		Uninit();
	}
	else if (Pos.y <= -1000.0f)
	{
		Uninit();
	}

	if (Pos.z >= 1000.0f)
	{
		Uninit();
	}
	else if (Pos.z <= -1000.0f)
	{
		Uninit();
	}

	// ���f�������̃��[�v
	for (int nCnt = 0; nCnt < nMaxModel; nCnt++)
	{
		// ���f���̎擾
		CModel *pModel = CManager::GetGame()->GetModel(nCnt)->GetModel();

		// ��������
		if (pModel->BoxCollision(&Pos, PosOld) == true)
		{
			// �j��
			Uninit();
		}
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	// �`��
	CBilboard::Draw();
}