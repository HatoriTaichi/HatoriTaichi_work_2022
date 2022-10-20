#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_ENEMY (128)				//�G�̍ő吔
#define MAX_ENEMY_TEX (3)			//�e�N�X�`���̍ő吔
#define ENEMY_X_SIZE (60.0f)		//�|���S����X�̔��a�T�C�Y
#define ENEMY_Y_SIZE (60.0f)		//�|���S����Y�̔��a�T�C�Y
#define G_POW (0.5f)				//�d�̗͂�
#define ES_BOS_MOVE_SPEED (-10.0f)	//�C�[�W�[�̃X�e�[�W�{�X�̈ړ���
#define ENEMY_POS_X (0.0f + ENEMY_X_SIZE)	//�G�̈ʒu
#define ENEMY_POS_Y (SCREEN_HEIGHT)			//�G�̈ʒu

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//�|���S���̈ʒu
	D3DXVECTOR3 posold;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nLife;				//�̗�
	float fWidth;			//��
	float fHeight;			//����
	int nType;				//���
	bool bJump;				//�W�����v�̏��
	bool bUse;				//�g���Ă邩�ǂ���
	bool bDamage;			//�_���[�W
} ENEMY;
//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, int nType, int nLife);	//�ʒu�A�ړ��ʁA���A�����A��ށA�̗�
ENEMY *GetEnemy(void);
#endif 