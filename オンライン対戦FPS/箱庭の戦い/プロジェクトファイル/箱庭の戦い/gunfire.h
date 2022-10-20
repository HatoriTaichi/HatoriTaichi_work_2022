//=============================================================================
//
// �}�Y���t���b�V������ [gunfire.h]
// Author : �H������
//
//=============================================================================
#ifndef _GUNFIRE_H_
#define _GUNFIRE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "bilboard.h"
#include "texture.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGunFire : public CBilboard
{
public:
	CGunFire();	// �f�t�H���g�R���X�g���N�^
	~CGunFire();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	static CGunFire *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, string type);	// ����
private:
	D3DXVECTOR3 m_Size;	// �T�C�Y
	string m_Type;	// �e�N�X�`��
	int m_nClearCnt;	// ������܂ł̃J�E���g
};

#endif