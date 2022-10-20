#pragma once
#ifndef _STAGE_H
#define _STAGE_H
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_STAGE_MODEL (64)		//�v���C���[���f���̍ő吔
#define MAX_STAGE_TEX (128)		//�v���C���[���f���̃p�[�c�̃e�N�X�`���̍ő吔

//---------------------------
//�񋓌^
//---------------------------
typedef enum
{
	STAGE_FLOO_00 = 0,	//��0
	STAGE_FENCE_00,		//��0
	STAGE_MOVEFLOO_00,	//�ړ���
	STAGE_MODEL_MAX			//���X�g�̐�
} MODEL_TYPE;

//---------------------------
//�\����
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 apos[4];	//
	D3DXVECTOR3 avec[4];	//
	D3DXMATRIX mtxWold;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 vtxMinModel, vtxMaxModel;	//���_�̒[���
	DWORD pnNumMat;			//�}�e���A���̐�
	LPD3DXMESH pMesh;		//���b�V���̃|�C���^
	LPD3DXBUFFER pBuffMat;	//�}�e���A���̃|�C���^
	MODEL_TYPE aType;		//���
	float fWidth;			//
	float fHight;			//
	float fDepth;			//
	int nIdex;				//�e�̔ԍ�
	bool bUse;				//�g���Ă邩
} Stage;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitStage(void);
void UninitStage(void);
void UpdateStage(void);
void DrawStage(void);
void SetStage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, MODEL_TYPE Type);	//�ʒu�A�����A���
bool CollisionStage(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType);
Stage *GetStage(void);
#endif