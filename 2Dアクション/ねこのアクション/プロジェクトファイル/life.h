#pragma once
#ifndef _LIFE_H_
#define _LIFE_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define LIFE_Y (25)		//���a
#define LIFE_X (75)		//���a
#define MAX_LIFE (10)	//�̗͂̐�

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
} LIFE;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
void AddLife(int nMinus);
#endif