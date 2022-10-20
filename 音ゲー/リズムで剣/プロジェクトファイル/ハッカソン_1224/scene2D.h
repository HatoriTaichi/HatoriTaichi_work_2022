//=============================================================================
//
// 2D�|���S������ [scene2D.h]
// Author : �H������
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) //2D�̏_��Ȓ��_�t�H�[�}�b�g
#define VERTEX_NUM (4)	// ���_�̐�

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;		//1.0f�ŌŒ�
	D3DCOLOR col;	//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
} VERTEX_2D;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);	// �f�t�H���g�R���X�g���N�^
	~CScene2D();	// �f�t�H���g�f�X�g���N�^
	virtual HRESULT Init(void);	// �|���S���̏�����
	virtual void Uninit(void);	// �|���S���̏I��
	virtual void Update(void);	// �|���S���̍X�V
	virtual void Draw(void);	// �|���S���̕`��
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string Type);	// ����
	D3DXVECTOR3 GetPos(void) { return m_Pos; }	// �ʒu�̎擾
	D3DXVECTOR3 GetSize(void) { return m_Size; }	// �T�C�Y�̎擾
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�̐ݒ�
	void SetSize(D3DXVECTOR3 size);	// �T�C�Y�̐ݒ�
	void SetTexType(string type) { m_TexType = type; m_pTexture = CTexture::GetTexture(m_TexType); }	// �e�N�X�`���̐ݒ�
	void SetCol(D3DXCOLOR col);	// �J���[�̐ݒ�
	void SetTex(int nScore);	// �e�N�X�`�����W�̐ݒ�(����)
	void SetTex(int nPattern, int nAnimMaxX, int nAnimMaxY);	// �e�N�X�`�����W�̐ݒ�(�e�N�X�`���A�j���[�V����)
private:
	LPDIRECT3DTEXTURE9	m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_Pos;	// �|���S���̌��_
	D3DXVECTOR3	m_Size;	// �T�C�Y
	string	m_TexType;	// �e�N�X�`���^�C�v
};

#endif