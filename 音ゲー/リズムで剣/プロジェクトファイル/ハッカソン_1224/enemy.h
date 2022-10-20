//=============================================================================
//
// �G���� [enemy.h]
// Author : �H������
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemy : public CScene2D
{
public:
	CEnemy();	// �f�t�H���g�R���X�g���N�^
	~CEnemy();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);		// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void SetbMove(bool move) { m_bMove = move; }	// �����Ă�t���O�̐ݒ�
	void SetUse(bool use) { m_bUse = use; }	// �g���Ă邩�t���O�̐ݒ�
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string type);	// ����
private:
	D3DXVECTOR3 m_Pos;	// �ʒu
	D3DXVECTOR3 m_Size;	// �T�C�Y
	string m_Type;	// �^�C�v
	int m_nAnim;	// ���̃A�j���[�V����
	int m_nAnimFrame;	// ���̃A�j���[�V����
	int m_nDeth;	// �j��
	bool m_bMove = false;	// �����Ă邩
	bool m_bUse = false;	// �j���t���O
};

#endif