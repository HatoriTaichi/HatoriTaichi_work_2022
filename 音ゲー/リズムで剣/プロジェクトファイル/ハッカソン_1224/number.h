//=============================================================================
//
// ������ [number.h]
// Author : �H������
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CNumber : public CScene2D
{
public:
	CNumber();	// �f�t�H���g�R���X�g���N�^
	~CNumber();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����(�ʒu�A�T�C�Y�A�e�N�X�`��)
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string type);	// ����
	void SetScore(int nScore) { CScene2D::SetTex(nScore); };	// �X�R�A�̐ݒ�
	void SetCol(D3DCOLORVALUE col) { CScene2D::SetCol(col); }	// �J���[�̐ݒ�
private:
	D3DXVECTOR3 m_Pos;	// �ʒu
	D3DXVECTOR3 m_Size;	// �T�C�Y
	string m_Type;	// �e�N�X�`��
};

#endif