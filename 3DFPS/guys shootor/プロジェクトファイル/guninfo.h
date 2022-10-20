#pragma once
#ifndef _GUNINFO_H_
#define _GUNINFO_H_

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_GUNINFO_TEX (1)	//�e�N�X�`���̐�
#define MAX_GUNDIGIT (2)	//�c�i���̌���
#define GUN_X (30)			//X
#define GUN_Y (30)			//Y

//---------------------------
//�񋓌^.���[�h�̎��
//---------------------------
typedef enum
{
	GUNINFO_TYPE_00 = 0,//�n���h�K��
	GUNINFO_TYPE_01,	//�A�T���g
	GUNINFO_MAX,
} GUNINFO_TYPE;

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//�|���S���̈ʒu
	float fWidth;		//��
	float fHeight;		//����
	int nRemaining;		//�f�w
} Guninfo;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitGuninfo(void);
void UninitGuninfo(void);
void UpdateGuninfo(void);
void DrawGuninfo(void);
void AddRemaining(int nShoot);
void SetGunType(GUNINFO_TYPE aType);
int GetRemaining(void);
#endif 
