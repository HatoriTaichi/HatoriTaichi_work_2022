#pragma once
#ifndef _DIFFICULTY_LEVE_H_
#define _DIFFICULTY_LEVE_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define TETTER_POS_00_X (SCREEN_WIDTH / 4)	//ESAY��X�ʒu
#define TETTER_POS_00_Y (SCREEN_HEIGHT / 2)	//ESAY��Y�ʒu
#define TETTER_POS_01_X ((SCREEN_WIDTH / 4) * 3)	//NORMR��X�ʒu
#define TETTER_POS_01_Y (SCREEN_HEIGHT / 2)	//NORMR��Y�ʒu
#define TETTER_POS_02_X (SCREEN_WIDTH / 2)	//HEARD��X�ʒu
#define TETTER_POS_02_Y (SCREEN_HEIGHT / 2)	//HEARD��Y�ʒu
#define TETTER_X (100.0f)	//X�̔��a
#define TETTER_Y (30.0f)	//Y�̔��a
#define MAX_LEVEL (3)		//���x���̐�

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int	nType;			//���
	bool nUse;			//�g�������
} LETTER;
//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitLetter(void);
void UninitLetter(void);
void UpdateLetter(void);
void DrawLetter(void);
void SetLetter(D3DXVECTOR3 pos, int nType);	//�ʒu�A���
LETTER *GetLetter(void);
#endif 
