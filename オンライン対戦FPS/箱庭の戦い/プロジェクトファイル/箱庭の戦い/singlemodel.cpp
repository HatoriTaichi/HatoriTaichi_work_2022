//=============================================================================
//
// �P�̃��f�� [singlemodel.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "singlemodel.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CSingleModel::CSingleModel(LAYER_TYPE Layer) : CScene(Layer)
{
	
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CSingleModel::~CSingleModel()
{

}

//=============================================================================
// ���f���̏���������
//=============================================================================
HRESULT CSingleModel::Init(void)
{
	m_pModel = CModel::Create(m_Type);	// ���f���̐���
	m_pModel->SetScale(m_Scale);	// �X�P�[���̐ݒ�
	m_pModel->SetPrent(NULL);	// �e�̐ݒ�

	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CSingleModel::Uninit(void)
{
	// �j��
	m_pModel->Uninit();
	delete m_pModel;
	m_pModel = NULL;
}

//=============================================================================
// ���f���̍X�V����
//=============================================================================
void CSingleModel::Update(void)
{
	// �X�V
	m_pModel->Update();
}

//=============================================================================
// ���f���̕`�揈��
//=============================================================================
void CSingleModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; // �f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X���擾����

	//--------------------------------------
	//�v���C���[(���_)�̃}�g���b�N�X�̐ݒ�
	//--------------------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&m_MtxWold);	//�}�g���b�N�X������

	//�����̐ݒ�
	D3DXMatrixRotationYawPitchRoll(	&mtxRot,
									m_Rot.y,
									m_Rot.x,
									m_Rot.z);

	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxRot);
	//�ʒu
	D3DXMatrixTranslation(	&mtxTrans,
							m_Pos.x,
							m_Pos.y,
							m_Pos.z);

	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxTrans);
	//�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(	D3DTS_WORLD,
							&m_MtxWold);
	// �`��
	m_pModel->Draw();
}

//=============================================================================
// ���f���̐���
//=============================================================================
CSingleModel *CSingleModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, CModel::TYPE type)
{
	CSingleModel *pModel = NULL;	// ���f���̃|�C���^

	// NULL��������
	if (pModel == NULL)
	{
		// ����
		pModel = new CSingleModel;
	}

	// �����̑��
	pModel->m_Pos = pos;
	pModel->m_Rot = rot;
	pModel->m_Scale = scale;
	pModel->m_Type = type;

	// ��������Ă�����
	if (pModel != NULL)
	{
		// ������
		pModel->Init();
	}
	return pModel;
}