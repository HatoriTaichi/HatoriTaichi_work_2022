//=============================================================================
//
// �������� [letter.h]
// Author : �H������
//
//=============================================================================
#ifndef _SCENELETTER_H_
#define _SCENELETTER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <tchar.h>
#include "main.h"
#include "object.h"
#include "object2D.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_CUSTOM (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) // ���W�ϊ��ςݒ��_
#define VERTEX_NUM (4)	// ���_�̐�

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CLetter : public CObject
{
public:
	CLetter(CObject::PRIORITY Layer = CObject::PRIORITY::SCORE);	// �f�t�H���g�R���X�g���N�^
	~CLetter();	// �f�t�H���g�f�X�g���N�^
	virtual HRESULT Init(void);	// �|���S���̏�����
	virtual void Uninit(void);	// �|���S���̏I��
	virtual void Update(void);	// �|���S���̍X�V
	virtual void Draw(void);	// �|���S���̕`��
	static void Load(void);	// �t�H���g�̃��[�h
	void SetFontType(string type) { m_font_type = type; }	// �t�H���g�̎�ނ̐ݒ�
	void SetFontSize(int nsize) { m_font_size = nsize; }	// �t�H���g�̃T�C�Y�̐ݒ�
	void SetFontWeight(int nweight) { m_font_weight = nweight; }	// �t�H���g�̑����̐ݒ�
	void SetText(wchar_t text) { m_text = text; }	// �o�������e�L�X�g�̐ݒ�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	// �|���S���ʒu�̐ݒ�
	void SetSize(D3DXVECTOR3 size) { m_size = size; }	// �|���S���T�C�Y�̐ݒ�
private:
	LPDIRECT3DTEXTURE9	m_texture = NULL;	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_vtx_buff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;	// �|���S���̌��_
	D3DXVECTOR3	m_size;	// �T�C�Y
	string	m_font_type;	// �e�N�X�`���^�C�v
	wchar_t	m_text;	// �e�L�X�g
	int	m_font_size;	// ����(���������ŕ������܂�)
	int	m_font_weight;	// ����
};

#endif