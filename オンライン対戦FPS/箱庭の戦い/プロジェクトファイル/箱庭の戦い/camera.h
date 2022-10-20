//=============================================================================
//
// �J�������� [camera.h]
// Author : �H������
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_DESTAANCE (500)		//�J�����ƒ����_�̋���
#define CAMERA_ZOOM_MAX (10)	// �Y�[��
#define CAMERA_ZOOM_NORMAL (90)	// �m�[�}��

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCamera
{
public:
	CCamera();	// �f�t�H���g�R���X�g���N�^
	~CCamera();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR, D3DXVECTOR3 Rot);	// �J�����̏�����
	void Uninit(void);	// �J�����̏I��
	void Update(void);	// �J�����̍X�V
	void SetCamera(void);	// �J�����̕`��
	static CCamera *Create(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR, D3DXVECTOR3 Rot);	// ����
	void SetPosV(D3DXVECTOR3 pos) { m_PosV = pos; }	// �J�����ʒu�̐ݒ�
	void SetPosR(D3DXVECTOR3 pos) { m_PosR = pos; }	// �����_�ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }	// �����̐ݒ�
	D3DXVECTOR3 GetPosV(void) { return m_PosV; }	// �J�����ʒu�̎擾
	D3DXVECTOR3 GetPosR(void) { return m_PosR; }	// �����_�ʒu�̎擾
	D3DXVECTOR3 GetRot(void) { return m_Rot; }	// �����̎擾
	D3DXVECTOR3 GetVecU(void) { return m_VecU; }	// �J�����̏�̃x�N�g���̎擾
	D3DXMATRIX GetViewMtx(void) { return m_mtxView; }	// �r���[�}�g���b�N�X�̎擾
	D3DXMATRIX GetProjecMtx(void) { return m_mtxProjection; }	// �v���W�F�N�V�����}�g���b�N�X�̎擾
	float GetDestance(void) { return m_fLong; }	// �����̎擾
private:
	D3DXVECTOR3 m_PosV;	// ���_
	D3DXVECTOR3 m_PosR;	// �����_
	D3DXVECTOR3 m_Rot;	// �J�����̌���
	D3DXVECTOR3 m_VecU;	// ������x�N�g��
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;	// �r���[�}�g���b�N�X
	float m_fLong;	// ��
	float m_fZoom;	// �Y�[��
};
#endif