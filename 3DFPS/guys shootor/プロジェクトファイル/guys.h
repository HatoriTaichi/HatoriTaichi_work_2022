#pragma once
#ifndef _GUYS_H_
#define _GUYS_H_
//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_GUYS (30)
#define MAX_GUYS_NUM (9)
#define G_GPOW (-0.5f)

//---------------------------
//�񋓌^.���[�h�̎��
//---------------------------
typedef enum
{
	GUYS_STATE_NEUTRAL = 0,	//�j���[�g�������[�V����
	GUYS_STATE_WORK,			//����
	GUYS_STATE_MAX			//���X�g�̐�
} Guysstate;

typedef enum
{
	COLLISION_PLAYER = 0,
	COLLISION_BULLET,
	COLLISION_MAX
} CollisionType;

//---------------------------
//�\����
//---------------------------
typedef struct
{
	float fPosX;	//�ʒuX
	float fPosY;	//�ʒuY
	float fPosZ;	//�ʒuZ
	float fRotX;	//����X
	float fRotY;	//����Y
	float fRotZ;	//����Z
} Key;

typedef struct
{
	float nFrame;					//�Đ��t���[��
	Key aKey[MAX_GUYS_NUM];	//���f�����̃L�[�v�f
} Keyinfo;

typedef struct
{
	bool bLoop;				//���[�v���邩
	int nNumKey;			//�L�[�̑���
	Keyinfo aKeyinfo[8];	//�L�[�̏��(�L�[�̑�����)
} Motioninfo;

typedef struct
{
	LPD3DXMESH pMesh;			//���b�V���̃|�C���^
	LPD3DXBUFFER pBuffMat;		//�}�e���A���̃|�C���^
	DWORD pnNumMat;				//�}�e���A���̐�
	D3DXVECTOR3 PosModel;		//�ʒu
	D3DXVECTOR3 RotModel;		//����
	D3DXVECTOR3 vtxMin, vtxMax;	//���_�̒[���
	D3DXMATRIX mtxWold;			//���[���h�}�g���b�N�X
	int nIdx;					//�e���f���̃C���f�b�N�X
} Guysmodel;

typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 posold;						//�O��̈ʒu
	D3DXVECTOR3 move;						//�ړ���
	D3DXVECTOR3 posdfrc;					//����
	D3DXVECTOR3 rot;						//����
	D3DXVECTOR3 apos[4];					//
	D3DXVECTOR3 avec[4];					//
	D3DXMATRIX mtxWold;						//���[���h�}�g���b�N�X
	D3DXMATRIX mtxView;						//�J�����̌���
	int nIdex;								//�e�̔ԍ�
	bool bLand;								//�n�ʂɂ��Ă邩
	Guysmodel aModel[MAX_GUYS_NUM];			//���f���̃p�[�c
	int nNumModel = MAX_GUYS_NUM;			//���f���̃p�[�c��
	Motioninfo aMotioninfo[GUYS_STATE_MAX];	//���[�V�������
	int nNumnMotion;						//���[�V������
	bool bLoopMotion;						//���[�v���邩
	int	nNumKey;							//�L�[��
	int nKey;								//�L�[No
	int nLife;								//�̗�
	float fMoveSpeed;
	float fWidth = 25.0f;					//���aX
	float fHight = 25.0f;					//���aY
	float fDepth = 25.0f;					//���aZ
	float fMotion;							//���[�V�����̃J�E���g
	Guysstate aState;						//���[�V�������
	bool bUse;								//�g���Ă邩
} Guys;
//---------------------------
//�v���g�^�C�v�錾
//---------------------------
HRESULT InitGuys(void);
void UninitGuys(void);
void UpdateGuys(void);
void DrawGuys(void);
void SetGuys(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, float fMoveSpeed);
bool CollisionGuys(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, CollisionType nType);
int GetDeth(void);
void ResetsDeth(void);
Guys *GetGuys(void);
#endif