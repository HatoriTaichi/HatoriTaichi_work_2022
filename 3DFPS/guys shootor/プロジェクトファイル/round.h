#pragma once
#ifndef _ROUND_H_
#define _ROUND_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_ROUND_TEX (1)	//�e�N�X�`���̐�
#define MAX_ROUNDDIGIT (2)	//�c�i���̌���
#define ROUND_X (30)			//X
#define ROUND_Y (30)			//Y

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//�|���S���̈ʒu
	float fWidth;		//��
	float fHeight;		//����
} Round;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitRound(void);
void UninitRound(void);
void UpdateRound(void);
void DrawRound(void);
void AddRound(int nRound);
int GetRound(void);
#endif