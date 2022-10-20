//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "player.h"
#include "shadow.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "camara.h"
#include "stage.h"
#include "bullet.h"
#include "guninfo.h"
#include "fade.h"
#include "guys.h"
#include "round.h"
#include "gunmodel.h"
#include "sound.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9	g_apTexturePlayer[MAX_PLAYER_PARTS_NUM][MAX_PLAYER_TEX] = {};	//�e�N�X�`���̃|�C���^
Player				g_aPlayer;	//�����̍\����

//---------------------------
//����������
//---------------------------
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̎擾

	//---------------------------------
	//�v���C���[(�p�[�c)���̏�����
	//---------------------------------
	g_aPlayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.nMotion = 0.0f;
	g_aPlayer.nKey = 0;
	g_aPlayer.aState = PLAYER_STATE_NEUTRAL;
	g_aPlayer.nIdex = 0;
	g_aPlayer.bUse = false;
	g_aPlayer.bJump = true;

	for (int nCntParts = 0; nCntParts < MAX_PLAYER_PARTS_NUM; nCntParts++)
	{
		g_aPlayer.aModel[nCntParts].vtxMax = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
		g_aPlayer.aModel[nCntParts].vtxMin = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);
		g_aPlayer.aModel[nCntParts].pBuffMat = {};
		g_aPlayer.aModel[nCntParts].pMesh = {};
	}

	//---------------------------
	//X�t�@�C���̓ǂݍ���
	//---------------------------
	D3DXLoadMeshFromX(	"data/Model/Player/guys1.4_body.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_aPlayer.aModel[0].pBuffMat,
						NULL,
						&g_aPlayer.aModel[0].pnNumMat,
						&g_aPlayer.aModel[0].pMesh);

	//---------------------------
	//�p�[�c�̊K�w�\��
	//---------------------------
	g_aPlayer.aModel[0].nIdx = -1;								//�e���f���̃C���f�b�N�X(�e������(���_)��-1)
	g_aPlayer.aModel[0].pos = D3DXVECTOR3(0.0f, 2.5f, 0.0f);	//�ʒu(�I�t�Z�b�g)
	g_aPlayer.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����

	//---------------------------
	//���_���W�̔����o��
	//---------------------------
	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^

	for (int nCntModel = 0; nCntModel < g_aPlayer.nNumModel; nCntModel++)
	{
		//���_�����擾
		nNumVtx = g_aPlayer.aModel[nCntModel].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aPlayer.aModel[nCntModel].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_aPlayer.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

			//���_�����r���čŏ��l�A�ő�l�𔲂�
			//X
			if (g_aPlayer.aModel[nCntModel].vtxMax.x <= vtx.x)
			{
				g_aPlayer.aModel[nCntModel].vtxMax.x = vtx.x;
			}
			if (g_aPlayer.aModel[nCntModel].vtxMin.x >= vtx.x)
			{
				g_aPlayer.aModel[nCntModel].vtxMin.x = vtx.x;
			}
			//Y
			if (g_aPlayer.aModel[nCntModel].vtxMax.y <= vtx.y)
			{
				g_aPlayer.aModel[nCntModel].vtxMax.y = vtx.y;
			}
			if (g_aPlayer.aModel[nCntModel].vtxMin.y >= vtx.y)
			{
				g_aPlayer.aModel[nCntModel].vtxMin.y = vtx.y;
			}
			//Z
			if (g_aPlayer.aModel[nCntModel].vtxMax.z <= vtx.z)
			{
				g_aPlayer.aModel[nCntModel].vtxMax.z = vtx.z;
			}
			if (g_aPlayer.aModel[nCntModel].vtxMin.z >= vtx.z)
			{
				g_aPlayer.aModel[nCntModel].vtxMin.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	//���_��i�߂�
		}
		//���_�o�b�t�@���A�����b�N
		g_aPlayer.aModel[nCntModel].pMesh->UnlockVertexBuffer();
	}
	g_aPlayer.nGun = SetGunModel(g_aPlayer.pos, g_aPlayer.rot, HANDGUN);
	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitPlayer(void)
{
	for (int nCntModelNum = 0; nCntModelNum < g_aPlayer.nNumModel; nCntModelNum++)
	{
		//---------------------------
		//���b�V���j��
		//---------------------------
		if (g_aPlayer.aModel[nCntModelNum].pMesh != NULL)
		{
			g_aPlayer.aModel[nCntModelNum].pMesh->Release();
			g_aPlayer.aModel[nCntModelNum].pMesh = NULL;
		}

		//---------------------------
		//�}�e���A���j��
		//---------------------------
		if (g_aPlayer.aModel[nCntModelNum].pBuffMat != NULL)
		{
			g_aPlayer.aModel[nCntModelNum].pBuffMat->Release();
			g_aPlayer.aModel[nCntModelNum].pBuffMat = NULL;
		}
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdatePlayer(void)
{
	Camera	*pCamera;
	static Guntype aGunType;
	int		nRound = GetRound();
	int		nRemaining = GetRemaining();
	static int nBulletSpan;

	nBulletSpan++;

	pCamera = GetCamera();

	//�O��̈ʒu��ۑ�
	g_aPlayer.posold = g_aPlayer.pos;

	//�J�����̌����ɓ��@
	g_aPlayer.rot.y = pCamera->Rot.y;

	//�d�̗͂�
	g_aPlayer.move.y += G_PPOW;

	//�d�͂�������
	g_aPlayer.pos += g_aPlayer.move;

	if (CollisionStage(&g_aPlayer.pos, &g_aPlayer.posold, &g_aPlayer.move, g_aPlayer.fWidth, g_aPlayer.fHight, g_aPlayer.fDepth, 0) == true)
	{
		g_aPlayer.bJump = true;
	}
	if (MouseDowan(MOUSE_LEFT_BOTTON) == true && nRemaining > 0 && nBulletSpan > 20)
	{
		PlaySound(SOUND_SHOT_00);
		SetBullet(D3DXVECTOR3(g_aPlayer.pos.x, g_aPlayer.pos.y + 25.0f, g_aPlayer.pos.z), pCamera->Rot, D3DXVECTOR3(sinf(pCamera->Rot.y) * BULLET_MOVE_SPEED, sinf(pCamera->Rot.x) * BULLET_MOVE_SPEED, cosf(pCamera->Rot.y) * BULLET_MOVE_SPEED), BULlET_SCALE_X, BULLET_SCALE_Y, BULLET_ASULT);
		AddRemaining(-1);
		nBulletSpan = 0;
	}
	if (GetKeyboardTrigger(DIK_R) == true)
	{
		if (aGunType == HANDGUN)
		{
			PlaySound(SOUND_RELOAD_00);
			SetGunType(GUNINFO_TYPE_00);
		}
		else if (aGunType == ASULTRIFLE)
		{
			PlaySound(SOUND_RELOAD_00);
			SetGunType(GUNINFO_TYPE_01);
		}
	}
	if (GetKeyboardTrigger(DIK_SPACE) == true && g_aPlayer.bJump == true)
	{
		g_aPlayer.move.y = JUMP_POW;
		g_aPlayer.bJump = false;
	}
	if (g_aPlayer.move.y > 0.0f)
	{
		pCamera->PosR.y = pCamera->PosR.y + g_aPlayer.move.y;
	}
	else if (g_aPlayer.move.y < 0.0f)
	{
		pCamera->PosR.y = pCamera->PosR.y + g_aPlayer.move.y;
	}

	if (GetMode() == MODE_GAME)
	{
		//���ɗ�������
		if (g_aPlayer.pos.y <= -2000.0f && GetFade() == FADE_NONE)
		{
			StopSound(SOUND_GAME_BGM);
			SetFade(MODE_RESULT);
		}
		if (CollisionGuys(&g_aPlayer.pos, &g_aPlayer.posold, &g_aPlayer.move, 50.0f, 50.0f, COLLISION_PLAYER) == true && GetFade() == FADE_NONE)
		{
			StopSound(SOUND_GAME_BGM);
			SetFade(MODE_RESULT);
		}
		if (CollisionGunModel(&g_aPlayer.pos, &g_aPlayer.posold, &g_aPlayer.move, 50.0f, 50.0f, &g_aPlayer.nGun) == true)
		{

		}
	}
	if (GetMode() == MODE_OPERATION)
	{
		if (g_aPlayer.pos.y <= -2000.0f && GetFade() == FADE_NONE)
		{
			pCamera->PosV = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
			g_aPlayer.pos = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
		}
	}

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_aPlayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
#endif

	//�e
	SetPointShadow(g_aPlayer.nIdex, g_aPlayer.pos, 30.0f, 30.0f, g_aPlayer.bUse);
	aGunType = SetPointGunModel(g_aPlayer.pos, pCamera->Rot, g_aPlayer.nGun);
}

//---------------------------
//�`�揈��
//---------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();					//�f�o�C�X���擾����

	//-------------------------------
	//�v���C���[(���_)�̃}�g���b�N�X�̐ݒ�
	//-------------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&g_aPlayer.mtxWold);	//�}�g���b�N�X������

	//�����̐ݒ�
	D3DXMatrixRotationYawPitchRoll(	&mtxRot,
									g_aPlayer.rot.y,
									g_aPlayer.rot.x,
									g_aPlayer.rot.z);

	D3DXMatrixMultiply(	&g_aPlayer.mtxWold,
						&g_aPlayer.mtxWold,
						&mtxRot);
	//�ʒu
	D3DXMatrixTranslation(	&mtxTrans,
							g_aPlayer.pos.x,
							g_aPlayer.pos.y,
							g_aPlayer.pos.z);

	D3DXMatrixMultiply(	&g_aPlayer.mtxWold,
						&g_aPlayer.mtxWold,
						&mtxTrans);
	//�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(	D3DTS_WORLD,
							&g_aPlayer.mtxWold);

	//---------------------------------
	//���f���p�[�c�̃}�g���b�N�X�̐ݒ�
	//---------------------------------
	for (int nCntModel = 0; nCntModel < g_aPlayer.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;					//�e�̃}�g���b�N�X

		D3DXMatrixIdentity(&g_aPlayer.aModel[nCntModel].mtxWold);	//�}�g���b�N�X������

		//�����̐ݒ�
		D3DXMatrixRotationYawPitchRoll(	&mtxRotModel,
										g_aPlayer.aModel[nCntModel].rot.y,
										g_aPlayer.aModel[nCntModel].rot.x,
										g_aPlayer.aModel[nCntModel].rot.z);

		D3DXMatrixMultiply(	&g_aPlayer.aModel[nCntModel].mtxWold,
							&g_aPlayer.aModel[nCntModel].mtxWold,
							&mtxRotModel);
		//�ʒu
		D3DXMatrixTranslation(	&mtxTransModel,
								g_aPlayer.aModel[nCntModel].pos.x,
								g_aPlayer.aModel[nCntModel].pos.y,
								g_aPlayer.aModel[nCntModel].pos.z);

		D3DXMatrixMultiply(	&g_aPlayer.aModel[nCntModel].mtxWold,
							&g_aPlayer.aModel[nCntModel].mtxWold,
							&mtxTransModel);

		//�p�[�c�̐e�̃}�g���b�N�X��ݒ�
		//�����e��������
		if (g_aPlayer.aModel[nCntModel].nIdx != -1)
		{
			mtxParent = g_aPlayer.aModel[g_aPlayer.aModel[nCntModel].nIdx].mtxWold;
		}
		else
		{
			mtxParent = g_aPlayer.mtxWold;
		}

		//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(	&g_aPlayer.aModel[nCntModel].mtxWold,
							&g_aPlayer.aModel[nCntModel].mtxWold,
							&mtxParent);

		//�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(	D3DTS_WORLD,
								&g_aPlayer.aModel[nCntModel].mtxWold);

		//---------------------------
		//�`�揈��
		//---------------------------
		D3DMATERIAL9		matDef;				//�}�e���A���̈ꎞ�ۑ�
		D3DXMATERIAL		*pMat;				//�}�e���A���f�[�^�̃|�C���^

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�̃|�C���^
		pMat = (D3DXMATERIAL*)g_aPlayer.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aPlayer.aModel[nCntModel].pnNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(	0,
									g_apTexturePlayer[nCntModel][nCntMat]);

			//���f���p�[�c�̕`��
			g_aPlayer.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
		//�ꎞ�ۑ����Ă�������ǂ�
		pDevice->SetMaterial(&matDef);
	}
}

//---------------------------
//�Z�b�g
//---------------------------
void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Camera *pCamera = GetCamera();

	if (g_aPlayer.bUse == false)
	{
		g_aPlayer.pos = pos;
		pCamera->PosV = pos;
		g_aPlayer.rot = rot;

		//�e��t����
		g_aPlayer.nIdex = SetShadow(g_aPlayer.pos, 30.0f, 30.0f);
		g_aPlayer.bUse = true;
	}
}

//---------------------------
//�v���C���[���
//---------------------------
Player *GetPlayer(void)
{
	return &g_aPlayer;
}
