//=============================================================================
//
// �}�Y���t���b�V������ [gunfire.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "gunfire.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGunFire::CGunFire()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CGunFire::~CGunFire()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CGunFire::Init(void)
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
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nNumVtx,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									ppVtxBuff,
									NULL);
	}

	// ���_�o�b�t�@�̐ݒ�
	if (*ppVtxBuff != NULL)
	{
		VERTEX_3D *pVtx;	// ���_�o�b�t�@�̃|�C���^

		// ���_�o�b�t�@�����b�N
		(*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
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

		// ���_�o�b�t�@���A�����b�N����
		(*ppVtxBuff)->Unlock();
	}

	// �C���f�b�N�X�o�b�t�@�̂̎擾
	LPDIRECT3DINDEXBUFFER9 *ppIdxBuff = CBilboard::GetIdxBuff();

	// �C���f�b�N�X�o�b�t�@�̐���
	if (*ppIdxBuff == NULL)
	{
		pDevice->CreateIndexBuffer(	sizeof(WORD) * nNumIdx,
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									ppIdxBuff,
									NULL);
	}

	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	if (*ppIdxBuff != NULL)
	{
		WORD *pIdx;	// �C���f�b�N�X���ւ̃|�C���^

		// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
		(*ppIdxBuff)->Lock(0, 0, (void**)&pIdx, 0);

		// �ԍ��f�[�^�ݒ�
		pIdx[0] = 0;
		pIdx[1] = 1;
		pIdx[2] = 2;
		pIdx[3] = 3;

		// �C���f�b�N�X�o�b�t�@���A�����b�N����
		(*ppIdxBuff)->Unlock();
	}

	// ������
	CBilboard::Init();

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CGunFire::Uninit(void)
{
	// �j��
	CBilboard::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CGunFire::Update(void)
{
	// �����܂ł̃J�E���g
	m_nClearCnt++;
	if (m_nClearCnt >= (FPS / 10))
	{
		// �j��
		Uninit();
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CGunFire::Draw(void)
{
	// �`��
	CBilboard::Draw();
}

//=============================================================================
// ����
//=============================================================================
CGunFire *CGunFire::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, string type)
{
	CGunFire *pFire;	// �}�Y���t���b�V���̃|�C���^
	pFire = new CGunFire;	// ����

	// NULL����Ȃ�������
	if (pFire != NULL)
	{
		// �����̑��
		pFire->m_Type = type;
		pFire->m_Size = size;
		pFire->SetPos(pos);
		pFire->SetScale(scale);
		pFire->SetNumVtx(4);
		pFire->SetNumIdx(4);

		// ������
		pFire->Init();
	}

	return pFire;
}