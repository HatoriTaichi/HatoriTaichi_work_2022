#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define BULLET_SIZE_X (5.0f)	//�ʃT�C�YX���a
#define BULLET_SIZE_Y (5.0f)	//�ʃT�C�YY���a
#define MAX_BULLET (256)		//�ʂ̍ő吔
#define BULLET_SPAN (10)		//�e�̃N�[���^�C��
#define ENEMY_BULLET_SPAN (150)	//�e�̃N�[���^�C��
#define MAX_TEX (4)				//�e�N�X�`���̐�

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//�|���S���̈ʒu
	D3DXVECTOR3 posold;		//�O��̈ʒu
	D3DXVECTOR3 posdfrc;	//����
	D3DXVECTOR3 move;		//�ړ���
	float fWidth;			//��
	float fHeight;			//����
	int nType;				//���
	bool bRft;				//����
	bool bUse;				//�g���Ă邩�ǂ���
} BULLET;
//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);	//�N���A����
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, int nType);	//�ʒu�A�ړ��ʁA���A�����A���
BULLET *GetBullet(void);
#endif 
