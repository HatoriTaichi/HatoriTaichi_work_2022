//=============================================================================
//
// �����|���S���̏��� [textureobj.h]
// Author : �H������
//
//=============================================================================
#ifndef _UIOBJ_H_
#define _UIOBJ_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CUiObj : public CScene2D
{
public:
	CUiObj();	// �f�t�H���g�R���X�g���N�^
	~CUiObj();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	void SetAlpha(float a) { m_Color.a = a; CScene2D::SetCol(m_Color); }	// ���l�̐ݒ�
	void SetSelect(bool select) { m_bSelect = select; }	// �I��ł���t���O�̐ݒ�
	string GetType(void) { return m_TexType; }	// �e�N�X�`���̎�ނ̎擾
	bool GetSelect(void) { return m_bSelect; }	// �I��ł���t���O�̎擾
	static CUiObj *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string Type);	// ����
private:
	D3DXVECTOR3 m_Pos;	// �ʒu
	D3DXVECTOR3 m_Size;	// �T�C�Y
	string m_TexType;	// �e�N�X�`��
	D3DXCOLOR m_Color;	// �J���[
	int m_nChangeCnt;	// �_�ŃJ�E���g
	bool m_bAlpha = false;	// �A���t�@�̃`�F���W
	bool m_bSelect = false;	// �I��
};

#endif