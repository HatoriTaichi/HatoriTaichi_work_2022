#pragma once
#ifndef _BG_H_
#define _BG_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_BG_TEX (12)		//�e�N�X�`���̐�
#define MAX_BG (64)			//�摜���o����

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
} BG;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitBg(void);
void UninitBg(void);
void UpdateBg(void);
void DrawBg(void);
void SetBg(D3DXVECTOR3 pos, float fWigth, float fHeight, int nType);	//�ʒu�A���A�����A���
#endif 
