#pragma once
#ifndef _HOME_H_
#define _HOME_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------


//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;  //�|���S���̈ʒu
} HOME;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitHome(void);
void UninitHome(void);
void UpdateHome(void);
void DrawHome(void);
#endif 
