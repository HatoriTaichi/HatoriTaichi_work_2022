#pragma once
#ifndef _TRAP_H_
#define _TRAP_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define TRAP_X_SIZE (20.0f)	//�|���S���̔��aX�T�C�Y
#define TRAP_Y_SIZE (20.0f)	//�|���S���̔��aY�T�C�Y
#define MAX_TEX_TRAP (4)	//�g���b�v�̃e�N�X�`����
#define MAX_TRAP (128)		//�u���b�N�̍ő吔

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posold;	//�O��̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	float fWidth;		//��
	float fHeight;		//����
	float fTexwidth;	//�e�N�X�`���̕�
	float fTexheigth;	//�e�N�X�`���̍���
	int nType;			//����邢
	bool bUse;			//�g���Ă邩�ǂ���
} TRAP;
//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitTrap(void);
void UninitTrap(void);
void UpdateTrap(void);
void DrawTrap(void);
void SetTrap(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, float fTexwidth, float fTexheight, int nType);	//�ʒu�A�ړ��ʁA�����A�����A�e�N�X�`���̕��A�e�N�X�`���̍����A���
TRAP *GetTrap(void);
#endif 