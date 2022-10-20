//=============================================================================
//
// �G�̒e���� [enemybullet.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player.h"
#include "playerbullet.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "game.h"
#include "enemy.h"
#include "communicationdata.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CPlayerBullet::CPlayerBullet()
{
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �T�C�Y
	D3DXMatrixIdentity(&m_mtxWorld);
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CPlayerBullet::~CPlayerBullet()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CPlayerBullet::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X���擾����

	//�e�N�X�`���̐ݒ�
	CBilboard::SetTexture(m_Type);

	//���_�o�b�t�@�̎擾
	LPDIRECT3DVERTEXBUFFER9 *ppVtxBuff = CBilboard::GetVtxBuff();

	int nNumVtx = CBilboard::GetNumVtx();	//���_���̎擾
	int nNumIdx = CBilboard::GetNumIdx();	//�C���f�b�N�X���̎擾

	// ���_�o�b�t�@�̐���
	if (*ppVtxBuff == NULL)
	{
		pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * nNumVtx,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_3D,
										D3DPOOL_MANAGED,
										ppVtxBuff,
										NULL);
	}

	//���_�o�b�t�@�̐ݒ�
	if (*ppVtxBuff != NULL)
	{
		VERTEX_3D *pVtx;	//���_�o�b�t�@�̃|�C���^

		//���_�o�b�t�@�����b�N
		(*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_Size.x, -m_Size.y, m_Size.z);
		pVtx[1].pos = D3DXVECTOR3(m_Size.x, -m_Size.y, m_Size.z);
		pVtx[2].pos = D3DXVECTOR3(-m_Size.x, m_Size.y, -m_Size.z);
		pVtx[3].pos = D3DXVECTOR3(m_Size.x, m_Size.y, -m_Size.z);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		(*ppVtxBuff)->Unlock();
	}

	//�C���f�b�N�X�o�b�t�@�̂̎擾
	LPDIRECT3DINDEXBUFFER9 *ppIdxBuff = CBilboard::GetIdxBuff();

	//�C���f�b�N�X�o�b�t�@�̐���
	if (*ppIdxBuff == NULL)
	{
		pDevice->CreateIndexBuffer(	sizeof(WORD) * nNumIdx,
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									ppIdxBuff,
									NULL);
	}
	//�C���f�b�N�X�o�b�t�@�̐ݒ�
	if (*ppIdxBuff != NULL)
	{
		WORD *pIdx;	//�C���f�b�N�X���ւ̃|�C���^

		//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
		(*ppIdxBuff)->Lock(0, 0, (void**)&pIdx, 0);

		//�ԍ��f�[�^�ݒ�
		pIdx[0] = 0;
		pIdx[1] = 1;
		pIdx[2] = 2;
		pIdx[3] = 3;

		//�C���f�b�N�X�o�b�t�@���A�����b�N����
		(*ppIdxBuff)->Unlock();
	}

	CBullet::Init();

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CPlayerBullet::Uninit(void)
{
	// �j��
	CBullet::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CPlayerBullet::Update(void)
{
	D3DXVECTOR3 Pos = CBullet::GetPos();	// �ʒu�̎擾
	CPlayer *pPlayer = CManager::GetGame()->GetPlayer();	// �v���C���[�̎擾
	CEnemy *pEnemy = CManager::GetGame()->GetEnemy();	// �G�̎擾
	CCommunicationData::COMMUNICATION_DATA *pData = pPlayer->GetCommuData();	// �ʐM�N���X�̎擾
	
	// �X�V
	CBullet::Update();

	// �������Ă�����
	if (pEnemy->ToBulletCollision(Pos, m_Size.x, m_Size.y) == true)
	{
		// �j��
		Uninit();
		for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
		{
			if (pData->Bullet[nCnt].bUse == true)
			{
				pData->Bullet[nCnt].bUse = false;
				break;
			}
		}
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CPlayerBullet::Draw(void)
{
	// �`��	
	CBullet::Draw();
}

//=============================================================================
// ����
//=============================================================================
CPlayerBullet *CPlayerBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 scale, string type, float fMoveSpeed)
{
	CPlayerBullet *pPlayerBullet;	// �e�̃|�C���^
	pPlayerBullet = new CPlayerBullet;	// ����

	// ��������Ă�����
	if (pPlayerBullet != NULL)
	{
		// �����̑��
		pPlayerBullet->m_Type = type;
		pPlayerBullet->m_Size = size;
		pPlayerBullet->m_fMoveSpeed = fMoveSpeed;
		pPlayerBullet->SetPos(pos);
		pPlayerBullet->SetRot(rot);
		pPlayerBullet->SetScale(scale);
		pPlayerBullet->SetNumVtx(4);
		pPlayerBullet->SetNumIdx(4);

		// ������
		pPlayerBullet->Init();
	}
	return pPlayerBullet;
}