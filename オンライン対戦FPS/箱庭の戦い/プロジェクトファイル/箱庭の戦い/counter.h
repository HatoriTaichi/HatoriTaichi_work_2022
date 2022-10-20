//=============================================================================
//
// �J�E���^�[���� [counter.h]
// Author : �H������
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCounter : public CScene
{
public:
	CCounter();	// �f�t�H���g�R���X�g���N�^
	~CCounter();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void AddCounter(int nValue) { m_nCounter += nValue; }	// �X�R�A���Z
	int GetCounter(void) { return m_nCounter; }	// �X�R�A�̎擾
	void SetCounter(int nCounter);	// �X�R�A�̐ݒ�
	void SetCol(D3DCOLORVALUE col);	// �J���[�̐ݒ�
	void SetCounterNum(int nCounter) { m_nCounter = nCounter; }	// �X�R�A�̐ݒ�
	int GetCounterNum(void) { return m_nCounter; }	// �X�R�A�̎擾
	static CCounter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumbderLength, string type);	// ����
private:
	vector<CNumber*> m_pNumber;	// ��
	D3DXVECTOR3 m_Pos;	// �ʒu
	D3DXVECTOR3 m_Size;	// �T�C�Y
	string m_Type;	// �e�N�X�`��
	int m_nNumberMax;	// ����
	int m_nCounter;	// �X�R�A
};

#endif