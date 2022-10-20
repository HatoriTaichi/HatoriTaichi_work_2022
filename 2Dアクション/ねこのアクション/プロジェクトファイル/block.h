#pragma once
#ifndef _BLOCK_H_
#define _BLOCK_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define BLOCK_X_SIZE (20.0f)	//�|���S���̔��aX�T�C�Y
#define BLOCK_Y_SIZE (20.0f)	//�|���S���̔��aY�T�C�Y
#define MAX_BLOCK (256)			//�u���b�N�̍ő吔
#define MAX_BLOCK_TEX (3)		//�e�N�X�`���̍ő吔

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 nowmove;//���݂̈ړ���
	float fWidth;		//��
	float fHeight;		//����
	float fTexwidth;	//�e�N�X�`���̕�
	float fTexheigth;	//�e�N�X�`���̍���
	int nType;			//�u���b�N�̎��
	bool bPuse;			//�����Ԃ����
	bool bUse;			//�g���Ă邩�ǂ���
} BLOCK;
//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, float fTexwidth, float fTexheight, int nType);	//�ʒu�A�ړ��ʁA�����A�����A�e�N�X�`���̕��A�e�N�X�`���̍����A���
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove, float fWidth, float fHeight, int nType);	//���݈ʒu�A�O��ʒu�A�ړ��ʁA�����A�c���A���
BLOCK *GetBlock(void);
#endif 