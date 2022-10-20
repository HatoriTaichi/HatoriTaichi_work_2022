#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_CAMERA (2)				//�J�����̍ő吔
#define CAMERA_MOVE_SPEED (1.0f)	//�v���C���[�̈ړ���
#define CAMERA_DESTAANCE (200)		//�v���C���[�ƒ����_�̋���

//---------------------------
//�\����
//---------------------------
typedef struct
{
	D3DXVECTOR3 PosV;			//���_
	D3DXVECTOR3 PosR;			//�����_
	D3DXVECTOR3 Rot;			//�J�����̌���
	POINT Pointer;				//�}�E�X�̈ʒu
	POINT Poimove;				//�}�E�X�̈ړ���
	D3DXVECTOR3 VecU;			//������x�N�g��
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
	D3DVIEWPORT9 viewport;		//�r���[�|�[�g
	float Long;					//��
	bool bUse;					//�g���Ă邩
} Camera;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nIdx);
Camera *GetCamera(void);
#endif