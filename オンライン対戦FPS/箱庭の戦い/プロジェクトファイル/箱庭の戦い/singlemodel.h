//=============================================================================
//
// �P�̃��f������ [player.h]
// Author : �H������
//
//=============================================================================
#ifndef _SINGLEMODEL_H_
#define _SINGLEMODEL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "model.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSingleModel : public CScene
{
public:
	CSingleModel(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// �f�t�H���g�R���X�g���N�^
	~CSingleModel();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	static CSingleModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, CModel::TYPE type);	// ����
	void SetScale(D3DXVECTOR3 scale) { m_pModel->SetScale(scale); }	// �X�P�[���̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_Pos; }	// �ʒu�̎擾
	D3DXVECTOR3 GetRot(void) { return m_Rot; }	// �����̎擾
	CModel *GetModel(void) { return m_pModel; }	// ���f���̎擾
private:
	CModel *m_pModel;	// ���f��
	CModel::TYPE m_Type;	// ���
	D3DXVECTOR3 m_Pos;	// �ʒu
	D3DXVECTOR3 m_Rot;	// ����
	D3DXVECTOR3 m_Scale;	// �X�P�[��
	D3DXMATRIX m_MtxWold;	// ���[���h�}�g���b�N�X
};

#endif