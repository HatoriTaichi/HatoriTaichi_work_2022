//=============================================================================
//
// �m�[�c�̏��� [notes.h]
// Author : �H������
//
//=============================================================================
#ifndef _NOTES_H_
#define _NOTES_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2D.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CCollision;
class CEnemy;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CNotes : public CScene2D
{
public:
	CNotes();	// �f�t�H���g�R���X�g���N�^
	~CNotes();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	CEnemy *GetEnemy(void) { return m_pEnemy; }	// �G�̎擾
	static CNotes *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, string Type);	// ����
private:
	CCollision *m_pCollision;	// ����
	CEnemy *m_pEnemy;	// �G
	D3DXVECTOR3 m_Pos;	// �ʒu
	D3DXVECTOR2 m_Size;	// �T�C�Y
	string m_TexType;	// �e�N�X�`��
};

#endif