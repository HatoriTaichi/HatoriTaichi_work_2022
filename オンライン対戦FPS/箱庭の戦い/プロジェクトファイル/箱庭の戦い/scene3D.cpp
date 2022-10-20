//=============================================================================
//
// 3D�I�u�W�F�N�g���� [scene3D.cpp]
// Author : �H������
//
//=============================================================================
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CScene3D::CScene3D()
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
CScene3D::~CScene3D()
{

}

//=============================================================================
// 3D�I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CScene3D::Init(void)
{
	return S_OK;
}

//=============================================================================
// 3D�I�u�W�F�N�g�̏I������
//=============================================================================
void CScene3D::Uninit(void)
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
void CScene3D::Update(void)
{

}

//=============================================================================
// 3D�I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CScene3D::Draw(void) 
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X���擾����

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	// ���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(	&mtxRot, 
									m_Rot.y, 
									m_Rot.x, 
									m_Rot.z);
	D3DXMatrixMultiply(	&m_mtxWorld, 
						&m_mtxWorld, 
						&mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(	&mtxTrans,
							m_Pos.x, 
							m_Pos.y, 
							m_Pos.z);
	D3DXMatrixMultiply(	&m_mtxWorld, 
						&m_mtxWorld, 
						&mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture); //�e�N�X�`���̐ݒ�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0, 
								m_pVtxBuff, 
								0, 
								sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,
									0,
									0,
									m_nNumVtx,	// �g�p���钸�_��
									0,	// �����̒l���ŏ��̃C���f�b�N�X
									m_nNumIdx - 2);	// �O�p�`�̐�

	// ���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

//=============================================================================
// ��������
//=============================================================================
CScene3D* CScene3D::Create(void) 
{
	CScene3D* pScene3D = NULL;	// 3D�I�u�W�F�N�g�̃|�C���^

	// NULL��������
	if (pScene3D == NULL)
	{
		// ����
		pScene3D = new CScene3D;
	}

	// ��������Ă�����
	if (pScene3D != NULL)
	{
		// ������
		pScene3D->Init();
	}

	return pScene3D;
}