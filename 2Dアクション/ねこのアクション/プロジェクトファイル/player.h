#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define PLAYER_X_SIZE (60.0f)	//�|���S����X�̔��a�T�C�Y
#define PLAYER_Y_SIZE (60.0f)	//�|���S����Y�̔��a�T�C�Y
#define G_POW (0.5f)			//�d�̗͂�
#define JAMP_POW (-14.0f)		//�W�����v��
#define JAMP_MOVE_POW (-5.0)	//�ړ��W�����v
#define MOVE_SPEED (3.0)		//�ړ���

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//�|���S���̈ʒu
	D3DXVECTOR3 posold;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	float fWidth;			//��
	float fHeight;			//����
	int nLevel;				//���x�����
	bool bJamp;				//�W�����v�̏��
	bool bUse;				//�g���Ă邩�ǂ���
} PLAYER;
//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void SetPlayer(D3DXVECTOR3 pos, float fWidth, float fHeight);	//�ʒu�A���A����
PLAYER *GetPlayer(void);
#endif 
