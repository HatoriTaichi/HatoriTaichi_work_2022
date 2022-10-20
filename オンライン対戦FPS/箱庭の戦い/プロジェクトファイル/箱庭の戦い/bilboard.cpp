//=============================================================================
//
// 3D�I�u�W�F�N�g���� [scene3D.cpp]
// Author : �H������
//
//=============================================================================
#include "bilboard.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CBilboard::CBilboard(LAYER_TYPE Layer) : CScene(Layer)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtxWorld);
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_nNumVtx = 0;
	m_nNumIdx = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBilboard::~CBilboard()
{

}

//=============================================================================
// 3D�I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CBilboard::Init(void)
{
	return S_OK;
}

//=============================================================================
// 3D�I�u�W�F�N�g�̏I������
//=============================================================================
void CBilboard::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// 3D�I�u�W�F�N�g�̍X�V����
//=============================================================================
void CBilboard::Update(void)
{
	
}

//=============================================================================
// 3D�I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CBilboard::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X���擾����

	// �t��]�J�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	D3DXMATRIX mtxScale, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �X�P�[���̐ݒ�
	D3DXMatrixScaling(	&mtxScale,
						m_Scale.x,
						m_Scale.y,
						m_Scale.z);

	D3DXMatrixMultiply(	&m_mtxWorld,
						&m_mtxWorld,
						&mtxScale);

	// �J�����̌������擾
	pDevice->GetTransform(	D3DTS_VIEW,
							&m_mtxView);

	// �J�����̏������āA�X�P�[���𔽉f
	m_mtxWorld._11 = m_mtxView._11;
	m_mtxWorld._12 = m_mtxView._21;
	m_mtxWorld._13 = m_mtxView._31;
	m_mtxWorld._21 = m_mtxView._12;
	m_mtxWorld._22 = m_mtxView._22;
	m_mtxWorld._23 = m_mtxView._32;
	m_mtxWorld._31 = m_mtxView._13;
	m_mtxWorld._32 = m_mtxView._23;
	m_mtxWorld._33 = m_mtxView._33;

	// �ʒu�𔽉f
	D3DXMatrixTranslation(	&mtxTrans,
							m_Pos.x,
							m_Pos.y,
							m_Pos.z);
	D3DXMatrixMultiply(	&m_mtxWorld,
						&m_mtxWorld,
						&mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture); // �e�N�X�`���̐ݒ�

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								m_pVtxBuff,
								0,
								sizeof(VERTEX_3D));
	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,
									0,
									0,
									m_nNumVtx,	// �g�p���钸�_��
									0,	// �����̒l���ŏ��̃C���f�b�N�X
									m_nNumIdx - 2);	// �O�p�`�̐�

	// �J�����O��߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

//=============================================================================
// ��������
//=============================================================================
CBilboard *CBilboard::Create(void)
{
	CBilboard *pBilboard = NULL;	// �r���{�[�h�̃|�C���^

	// NULL��������
	if (pBilboard == NULL)
	{
		// ����
		pBilboard = new CBilboard;
	}

	// ��������Ă�����
	if (pBilboard != NULL)
	{
		// ������
		pBilboard->Init();
	}

	return pBilboard;
}