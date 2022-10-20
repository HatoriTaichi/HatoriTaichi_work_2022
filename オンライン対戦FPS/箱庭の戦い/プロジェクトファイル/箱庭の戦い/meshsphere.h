//=============================================================================
//
// �����|���S������ [floo.h]
// Author : �H������
//
//=============================================================================
#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

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
class CMeshsphere : public CScene3D
{
public:
	CMeshsphere();		// �f�t�H���g�R���X�g���N�^
	~CMeshsphere();	// �f�X�g���N�^
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	static CMeshsphere *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPolyX, int nPolyY, int nRadius, string type);	// ����
private:
	int m_nXPoly;	// X�̐�
	int m_nYPoly;	// Y�̐�
	int m_nRadius;	// ���a
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	string m_Type;	// �e�N�X�`��
};

#endif // !_SCENE3D_H_