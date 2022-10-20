//=============================================================================
//
// �Q�[�� [game.h]
// Author : �H������
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CUiObj;
class CCounter;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGame
{
public:
	CGame();	// �f�t�H���g�R���X�g���N�^
	~CGame();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);		// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	CCounter *GetCombo(void) { return m_pCombo; }	// �R���{�J�E���^�[�̎擾
	CCounter *GetScore(void) { return m_pScore; }	// �X�R�A�J�E���^�[�̎擾
private:
	vector<string> m_Type;	// �e�N�X�`���^�C�v
	vector<string> m_NotesType;	// �e�N�X�`���^�C�v
	vector<float> m_nSecond;	// �b��
	CCounter *m_pCombo;	// �R���{�J�E���^�[
	CCounter *m_pScore;	// �X�R�A�J�E���^�[
	int m_nUiNum;	// UI��
	int m_nNotesNum;	// �m�[�c��
	int m_nNotes;	// �ǂ̃m�[�c
	int m_nTimer;	// �^�C�}�[
	float m_nLimit;	// ����
	bool m_bFade = false;	// �t�F�[�h
};

#endif