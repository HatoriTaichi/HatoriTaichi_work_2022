//=============================================================================
//
// �e�N�X�`������ [texture.h]
// Author : �H������
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTexture
{
public:
	CTexture();	// �f�t�H���g�R���X�g���N�^
	~CTexture();// �f�t�H���g�f�X�g���N�^
	static void Init(void);	// �e�N�X�`���̐���
	static LPDIRECT3DTEXTURE9 GetTexture(string type) { return m_pTexture[m_TexType[type]]; }	// �e�N�X�`���擾
	static int GetTexNum(void) { return m_nTextureMax; }	// �e�N�X�`���ő吔�̎擾
	static string *GetPasName(void) { return &m_FilePas[0]; }	// �p�X�̍ŏ��̃|�C���^�̎擾
	static string GetEnumName(int nCntPas) { return m_Enum[nCntPas]; }	// ���O�̎擾
	static void Uniinit(void);	// �I��
private:
	static vector<LPDIRECT3DTEXTURE9> m_pTexture;	//�e�N�X�`��
	static vector<string> m_FilePas;	// �t�@�C���̃p�X
	static vector<string> m_Enum;	// ������̕ۑ�
	static map<string, int> m_TexType;	// �������int��map
	static int m_nTextureMax;	// �ǂݍ��ރe�N�X�`���̍ő吔
};

#endif