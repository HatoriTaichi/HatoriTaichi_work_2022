//=============================================================================
//
// �����b�V���|���S������ [floo.h]
// Author : �H������
//
//=============================================================================
#ifndef _MESHFLOO_H_
#define _MESHFLOO_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene3D.h"
#include "manager.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMeshFloo : public CScene3D
{
public:
	CMeshFloo();		// �f�t�H���g�R���X�g���N�^
	~CMeshFloo();	// �f�X�g���N�^
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	static CMeshFloo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPolyX, int nPolyZ, int nRadiusX, int nRadiusZ, string type);	// ����
private:
	int m_nXPoly;	// X�̐�
	int m_nZPoly;	// Z�̐�
	int m_nXRadius;	// X�̔��a
	int m_nZRadius;	// Z���a
	int m_nMoveReversCnt;	// ���]�J�E���g
	bool m_bRevers;	// ���]�t���O
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	string m_Type;	// �e�N�X�`��
};

#endif // !_SCENE3D_H_