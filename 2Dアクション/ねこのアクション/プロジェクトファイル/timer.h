#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_TIMER (3)			//�摜���o����
#define TIMER_SIZE_Y (25)		//Y�̔��a
#define TIMER_SIZE_X (25)		//X�̔��a
#define ES_TIMER_SET (240)		//ES��������
#define NO_TIMER_SET (340)		//NO��������
#define HD_TIMER_SET (440)		//NO��������
#define DEBUG_MAXTIMER_SET (999)		//NO��������
#define DEBUG_MINITIMER_SET (10)		//NO��������

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3  pos;		//�|���S���̈ʒu
	bool		 bUse;		//�g���Ă邩�ǂ���
} TIMER;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
#endif 
