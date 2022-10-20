//=============================================================================
//
// �v���C���[�̒e���� [playerbullet.h]
// Author : �H������
//
//=============================================================================
#ifndef _PLAYER_BULLET_H_
#define _PLAYER_BULLET_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "bullet.h"
#include "texture.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayerBullet : public CBullet
{
public:
	CPlayerBullet();	// �f�t�H���g�R���X�g���N�^
	~CPlayerBullet();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	static CPlayerBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 scale, string type, float fMoveSpeed);	// ����
private:
	D3DXVECTOR3 m_Size;	// �T�C�Y
	D3DXMATRIX m_mtxWorld;// ���[���h�}�g���b�N�X
	string m_Type;	// �e�N�X�`��
};

#endif