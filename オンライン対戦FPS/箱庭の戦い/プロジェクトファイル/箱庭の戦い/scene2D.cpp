//=============================================================================
//
// 2D�|���S������ [scene2D.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(LAYER_TYPE Layer) : CScene(Layer)
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CScene2D::Init(void)
{
	VERTEX_2D *pVtx;	// ���_���
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X���擾����

	m_pTexture = CTexture::GetTexture(m_TexType);	// �e�N�X�`���̓���

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUM,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_Size.x, m_Pos.y - m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_Size.x, m_Pos.y - m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_Size.x, m_Pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_Size.x, m_Pos.y + m_Size.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();	// �����̔j��
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X���擾����

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								m_pVtxBuff,
								0,
								sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);	// ���_�t�H�[�}�b�g�̐ݒ�

	pDevice->SetTexture(0, m_pTexture);	// �e�N�X�`���̐ݒ�

	// �|���S���̕`��
	pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, // �v���~�e�B�u�̎��
							0,
							2);
}

//=============================================================================
// �I�u�W�F�N�g�̐���
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string Type)
{
	CScene2D *pScene2D = NULL;	// 2D�I�u�W�F�N�g�̐���

	// NULL��������
	if (pScene2D == NULL)
	{
		// ����
		pScene2D = new CScene2D;
	}

	// �����̑��
	pScene2D->m_Pos = pos;
	pScene2D->m_Size = size;
	pScene2D->m_TexType = Type;

	// ��������Ă�����
	if (pScene2D != NULL)
	{
		// ������
		pScene2D->Init();
	}
	return pScene2D;
}

//=============================================================================
// �J���[�̐ݒ�
//=============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;	// ���_���

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CScene2D::SetPos(D3DXVECTOR3 pos)
{
	CScene::SetPos(pos);	// �ʒu�̐ݒ�
	m_Pos = pos;	// �ʒu�̐ݒ�

	VERTEX_2D *pVtx;	// ���_���

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - m_Size.x, pos.y - m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + m_Size.x, pos.y - m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - m_Size.x, pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + m_Size.x, pos.y + m_Size.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �T�C�Y�̐ݒ�
//=============================================================================
void CScene2D::SetSize(D3DXVECTOR3 size)
{
	CScene::SetSize(size);	// �T�C�Y�̐ݒ�
	m_Size = size;	// �T�C�Y�̐ݒ�

	VERTEX_2D *pVtx;	// ���_���

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - size.x, m_Pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + size.x, m_Pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - size.x, m_Pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + size.x, m_Pos.y + size.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void CScene2D::SetTex(int nScore)
{
	VERTEX_2D *pVtx;	// ���_���

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2((nScore * 0.1f) + 0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nScore * 0.1f) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nScore * 0.1f) + 0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nScore * 0.1f) + 0.1f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}