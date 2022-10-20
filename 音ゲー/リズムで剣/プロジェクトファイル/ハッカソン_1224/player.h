//=============================================================================
//
// ���͏��� [input.h]
// Author : �O���B
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CScene2D
{
public:
	CPlayer();	// �f�t�H���g�R���X�g���N�^
	~CPlayer();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string type);

	bool Attack();		// �U��
private:
	D3DXVECTOR3 m_Pos;	// �ʒu
	D3DXVECTOR3 m_Size;	// �T�C�Y
	string m_Type;		// �^�C�v

	bool m_bNowAttack;	// ���U������

	float m_fMove = 2.5f;				// �ړ���
	int m_nAttackTime;					// �U���̃^�C�}�[
	const int m_nMaxAttackTime = 24;	// �U���̎�������

	int m_nMoveDirection;		// �؂����

	const float m_fPosMoveStart = 300.0f;	// �ړ��̎n�_
	const D3DXVECTOR3 m_PosFix = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);	// �����ʒu
};

#endif