#pragma once
#ifndef _PAUSE_H_
#define _PAUSE_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_PAUSE_TEX (3)		//�e�N�X�`���̐�
#define MAX_PAUSE (3)			//�摜���o����
#define PAUSE_X (200.0f)		//X�̃T�C�Y
#define PAUSE_Y (50.0f)			//Y�̃T�C�Y1

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3  pos;		//�|���S���̈ʒu
	float		 fWidth;	//��
	float		 fHeight;	//����
	int			 nType;		//���
	bool		 bUse;		//�g���Ă邩�ǂ���
} PAUSE;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitPause(void);
void UninitPause(void);
bool UpdatePause(void);
void DrawPause(void);
#endif 
