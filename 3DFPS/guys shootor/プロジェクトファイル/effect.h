#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_EFFECT (10000)	//�e�̍ő吔
#define MAX_EFFECT_TEX (EFFECT_TEX_MAX)
#define EFFECT_X (0.5f)		//�e��X
#define EFFECT_Z (0.5f)		//�e��Y

//---------------------------
//�񋓌^.���[�h�̎��
//---------------------------
typedef enum
{
	EFFECT_GUN = 0,		//�e
	EFFECT_DETH,		//���񂾂Ƃ�
	EFFECT_MAX			//���X�g�̐�
} EffectType;

typedef enum
{
	EFFECT_TEX_GUN = 0,		//�e
	EFFECT_TEX_DETH,		//���񂾂Ƃ�
	EFFECT_TEX_MAX			//���X�g�̐�
} Effecttextype;

//---------------------------
//�\����
//---------------------------
typedef struct
{
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXMATRIX mtxView;		//�r���{�[�h
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����
	float fWhith;			//��
	float fHeiht;			//����
	float fDepht;			//���s
	float fAlpha;			//��
	EffectType aType;		//���
	Effecttextype aTex;		//�e�N�X�`�����
	int nLife;				//���ŃJ�E���g
	bool bUse;				//�g���Ă邩�ǂ���
} Effect;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWhith, float fHeight, EffectType aType, Effecttextype aTex, int nLife);	//�ʒu�A���A����
#endif