//=============================================================================
//
// �G�̒e���� [playerbullet.h]
// Author : �H������
//
//=============================================================================
#ifndef _ENEMY_BULLET_H_
#define _ENEMY_BULLET_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "bullet.h"
#include "texture.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemyBullet : public CBullet
{
public:
	CEnemyBullet();	// �f�t�H���g�R���X�g���N�^
	~CEnemyBullet();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	static CEnemyBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 scale, string type, float fMoveSpeed);	// ����
private:
	D3DXVECTOR3 m_Size;	// �T�C�Y
	D3DXVECTOR3 m_Scale;	// �X�P�[��
	D3DXMATRIX m_mtxWorld;// ���[���h�}�g���b�N�X
	string m_Type;	// �e�N�X�`��
};

#endif 