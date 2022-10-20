//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "player.h"
#include "input.h"
#include "block.h"
#include "bullet.h"
#include "enemy.h"
#include "fade.h"
#include "life.h"
#include "bullet.h"
#include "sound.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTexturePlayer = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
PLAYER					g_player;					//�v���C���[�̍\����
bool					g_bLand = true;				//���n

//---------------------------
//����������
//---------------------------
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D			*pVtx;		//���_���ւ̃|�C���^
	FILE			    *pFile;		//�t�@�C���J��

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�v���C���[�̏����ʒu
	g_player.posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�v���C���[�̑O��ʒu
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�v���C���[�̈ړ���
	g_player.fHeight = 0;								//�v���C���[�̍���
	g_player.fWidth = 0;								//�v���C���[�̕�
	g_player.bUse = true;								//�v���C���[�̏��
	g_player.bJamp = false;								//�W�����v���
	g_player.nLevel = 0;
#ifdef _DEBUG
	g_player.nLevel = 2;
#endif

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/cat.png",			//�e�N�X�`��
								&g_pTexturePlayer);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffPlayer,
									NULL);
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth / 2, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth / 2, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth / 2, g_player.pos.y, g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth / 2, g_player.pos.y, g_player.pos.z);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();

	//�t�@�C���J��
	pFile = fopen("stat.bin", "rb");
	//�Ȃ񂩓����Ă���
	if (pFile != NULL)
	{
		//�����L���O����
		fscanf(pFile, "%d", &g_player.nLevel);
		//����
		fclose(pFile);
	}
	else
	{
		printf("�ǂݎ��Ȃ���");
	}

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdatePlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D			*pVtx;		//���_���ւ̃|�C���^
	static int			nSpan;		//�e�̔��˃N�[���^�C��
	static int			nTimer;		//���G����
	static int			nTimer2;	//���G����
	static int			nTimer3;	//���G����
	static int			nCol = 255;	//�`�J�`�J

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	g_player.posold = g_player.pos;	//�O��̈ʒu��ۑ�
	nSpan++;						//�J�E���g

	//�������_���[�W����Ă���
	if (g_player.bUse == false)
	{
		nTimer++;	//���G���ԃJ�E���g
		nTimer3++;	//�_�Ń^�C�~���O

		//���G���ԏI���
		if (nTimer >= 500)
		{
			g_player.bUse = true;	//�_���H����ĂȂ�
			nTimer = 0;				//�J�E���g�߂�
		}
		//�_�Ń^�C�~���O�ɂȂ���
		if (nTimer3 == 30)
		{
			nTimer2 = nTimer3;	//�^�C�~���O��n����
			nTimer3 = 0;		//0�ɂȂ�
		}
		//A��255�� && �^�C�~���O�����Ă���
		if (nCol == 255 && nTimer2 == 30)
		{
			nCol = 0;		//����
			nTimer2 = 0;	//�^�C�~���O������
		}
		//A��0�� && �^�C�~���O�����Ă�
		else if (nCol == 0 && nTimer2 == 30)
		{
			nCol = 255;		//������
			nTimer2 = 0;	//�^�C�~���O������
		}
	}
	else if (g_player.bUse == true)
	{
		nCol = 255;
	}

	//���������ꂽ�� || A
	if (GetKeyboardPress(DIK_LEFT) == true || GetKeyboardPress(DIK_A) == true)
	{
		g_player.move.x = -MOVE_SPEED;
		g_player.pos.x += g_player.move.x;
		if (g_player.bJamp == false)
		{
			//�W�����v���
			g_player.bJamp = true;
			//�W�����v
			g_player.move.y = JAMP_MOVE_POW;
		}
	}
	//���������ꂽ�� || D
	else if (GetKeyboardPress(DIK_RIGHT) == true || GetKeyboardPress(DIK_D) == true)
	{
		g_player.move.x = MOVE_SPEED;
		g_player.pos.x += g_player.move.x;
		if (g_player.bJamp == false)
		{
			//�W�����v���
			g_player.bJamp = true;
			//�W�����v
			g_player.move.y = JAMP_MOVE_POW;
		}
	}
	//������� || ���U���g���
	if (GetMode() == MODE_OPERATION || GetMode() == MODE_RESULT)
	{
		g_player.move.x = -MOVE_SPEED;
		g_player.pos.x += g_player.move.x;
		if (g_player.bJamp == false)
		{
			//�W�����v���
			g_player.bJamp = true;
			//�W�����v
			g_player.move.y = JAMP_MOVE_POW;
		}
	}
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//�E�����Ă�
	if (g_player.move.x >= 0.0f)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.45f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.45f, 0.5f);
	}
	//�������Ă�
	else if (g_player.move.x <= 0.0f)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[1].tex = D3DXVECTOR2(0.45f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.45f, 1.0f);
	}
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���U���g�ƃz�[���ȊO
	if (GetMode() != MODE_OPERATION && GetMode() != MODE_RESULT)
	{
		//�X�y�[�X�������ꂽ�� && �W�����v��Ԃ���Ȃ�
		if (GetKeyboardPress(DIK_SPACE) == true && g_player.bJamp == false)
		{
			//�W�����v���
			g_player.bJamp = true;
			//�W�����v
			g_player.move.y = JAMP_POW;
		}
		//Z�������ꂽ��
		if (GetKeyboardPress(DIK_Z) == true && nSpan > BULLET_SPAN)
		{
			PlaySound(SOUND_LABEL_SE001);
			SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y - g_player.fHeight / 2, 0.0f), D3DXVECTOR3(g_player.move.x * 2, 0.0f, 0.0f), BULLET_SIZE_X * 2, BULLET_SIZE_Y * 2, 0);
			nSpan = 0;
		}
		//F�������ꂽ��
		else if (GetKeyboardPress(DIK_F) == true && nSpan > BULLET_SPAN)
		{
			PlaySound(SOUND_LABEL_SE001);
			SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y - g_player.fHeight / 2, 0.0f), D3DXVECTOR3(g_player.move.x * 2, 0.0f, 0.0f), BULLET_SIZE_X * 2, BULLET_SIZE_Y * 2, 0);
			nSpan = 0;
		}
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth / 2, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth / 2, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth / 2, g_player.pos.y, g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth / 2, g_player.pos.y, g_player.pos.z);

	if (g_player.bUse == false)
	{
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nCol);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nCol);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nCol);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nCol);
	}

	if (g_player.bUse == true)
	{
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();

	//���t���[���d�͂��{
	g_player.move.y += G_POW;
	//�ړ��ʂ��{
	g_player.pos.y += g_player.move.y;
	
	//�u���b�N�ɒ��n���Ă�����
	if (CollisionBlock(&g_player.pos, &g_player.posold, &g_player.move, g_player.fWidth, g_player.fHeight, 0) == true)
	{
		//�E�����Ă�
		if (g_player.move.x >= 0.0f)
		{
			pVtx[0].tex = D3DXVECTOR2(0.452f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.452f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
		}
		//�������Ă�
		else if (g_player.move.x <= 0.0f)
		{
			pVtx[0].tex = D3DXVECTOR2(0.452f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.452f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		//�W�����v��Ԃ���Ȃ�
		g_player.bJamp = false;
	}
	//�u���b�N���痎������
	else if (CollisionBlock(&g_player.pos, &g_player.posold, &g_player.move, g_player.fWidth, g_player.fHeight, 0) == false)
	{
		//�W�����v���
		g_player.bJamp = true;
	}
	//�z�[���ɂ�����
	if (GetMode() == MODE_HOME)
	{
		//��ʉE�[�ɏo����
		if (g_player.pos.x + g_player.fWidth / 2 >= SCREEN_WIDTH)
		{
			//���[�ɃZ�b�g
			g_player.pos.x = 0 + g_player.fWidth / 2;
		}
		//��ʍ��[�ɏo����
		else if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//�E�[�ɃZ�b�g
			g_player.pos.x = SCREEN_WIDTH - g_player.fWidth / 2;
		}
	}
	//�C�[�W�[�̃X�e�[�W1��������
	else if (GetMode() == MODE_ES_STAGE01)
	{
		//��ʍ��[�ɏo����
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//���[�ɃZ�b�g
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//�C�[�W�[�̃X�e�[�W1���N���A������
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_ES_STAGE02);
		}
		//���ɗ�������
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
			}
			g_player.bUse = false;
			SetPlayer(D3DXVECTOR3(0.0f + g_player.fWidth / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
	}
	//�C�[�W�[�̃X�e�[�W2��������
	else if (GetMode() == MODE_ES_STAGE02)
	{
		//��ʍ��[�ɏo����
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//���[�ɃZ�b�g
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//���ɗ�������
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
			}
			g_player.bUse = false;
			SetPlayer(D3DXVECTOR3(0.0f + g_player.fWidth / 2 * 1.1f, 290.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
		//�C�[�W�[�̃X�e�[�W2���N���A������
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_ES_STAGE03);
		}
	}
	//�C�[�W�[�̃X�e�[�W3��������
	else if (GetMode() == MODE_ES_STAGE03)
	{
		//��ʍ��[�ɏo����
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//���[�ɃZ�b�g
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
	}
	//�m�[�}���̃X�e�[�W1��������
	else if (GetMode() == MODE_NO_STAGE01)
	{
		//��ʍ��[�ɏo����
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//���[�ɃZ�b�g
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//���ɗ�������
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
			}
			g_player.bUse = false;
			SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 300.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
		//�C�[�W�[�̃X�e�[�W2���N���A������
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_NO_STAGE02);
		}
	}
	//�m�[�}���̃X�e�[�W2��������
	else if (GetMode() == MODE_NO_STAGE02)
	{
		//��ʍ��[�ɏo����
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//���[�ɃZ�b�g
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//���ɗ�������
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
			}
			g_player.bUse = false;
			SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 400.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
		//�C�[�W�[�̃X�e�[�W2���N���A������
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_NO_STAGE03);
		}
	}
	//�́[�܂�̃X�e�[�W3
	else if (GetMode() == MODE_NO_STAGE03)
	{
		//��ʍ��[�ɏo����
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//���[�ɃZ�b�g
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//���ɗ�������
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
			}
			g_player.bUse = false;
			SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 650.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
		//�́[�܂�̃X�e�[�W3���N���A������
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_NO_STAGE04);
		}
	}
	//�́[�܂�[�̃X�e�[�W4��������
	else if (GetMode() == MODE_NO_STAGE04)
	{
		//��ʍ��[�ɏo����
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//���[�ɃZ�b�g
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
	}
	//�́[�ǂ̃X�e�[�W3��������
	else if (GetMode() == MODE_HD_STAGE01)
	{
		//��ʍ��[�ɏo����
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//���[�ɃZ�b�g
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//���ɗ�������
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
			}
			g_player.bUse = false;
			SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
		//�́[�܂�̃X�e�[�W3���N���A������
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_HD_STAGE02);
		}
	}
	//�́[�ǂ̃X�e�[�W3��������
	else if (GetMode() == MODE_HD_STAGE02)
	{
		//��ʍ��[�ɏo����
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//���[�ɃZ�b�g
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//���ɗ�������
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
			}
			g_player.bUse = false;
			SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 670.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
		//�́[�܂�̃X�e�[�W3���N���A������
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_HD_STAGE03);
		}
	}
	//�́[�ǂ̃X�e�[�W3��������
	else if (GetMode() == MODE_HD_STAGE03)
	{
		//��ʍ��[�ɏo����
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//���[�ɃZ�b�g
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//���ɗ�������
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
				SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 650.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
			}
			g_player.bUse = false;
			
		}
		//�́[�܂�̃X�e�[�W3���N���A������
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_HD_STAGE04);
		}
	}
	//�́[�ǂ̃X�e�[�W3��������
	else if (GetMode() == MODE_HD_STAGE04)
	{
		//��ʍ��[�ɏo����
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//���[�ɃZ�b�g
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
	}
	//�́[�ǂ̃X�e�[�W3��������
	else if (GetMode() == MODE_HD_STAGE05)
	{
		//��ʍ��[�ɏo����
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//���[�ɃZ�b�g
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//���ɗ�������
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.2f, SCREEN_HEIGHT - 11.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
			}
		}
	}
	//����������߂� || ���U���g���
	if (GetMode() == MODE_OPERATION || GetMode() == MODE_RESULT)
	{
		//���ɗ�������
		if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			SetPlayer(D3DXVECTOR3(SCREEN_WIDTH - (300.0f + PLAYER_X_SIZE), SCREEN_HEIGHT, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
	}
}

//---------------------------
//�`�揈��
//---------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();		//�f�o�C�X���擾����

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffPlayer,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//���_�t�H�[�}�b�g�̐ݒ�

	pDevice->SetTexture(0, g_pTexturePlayer);		//�e�N�X�`���̐ݒ�
	//�|���S���̕`��
	pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
							0,
							2);
}

//---------------------------
//�v���C���[�̃Z�b�g
//---------------------------
void SetPlayer(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	g_player.pos = pos;				//�����Ă����ʒu����
	g_player.fWidth = fWidth;		//�����Ă���������
	g_player.fHeight = fHeight;		//�����Ă�����������

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth / 2, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth / 2, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth / 2, g_player.pos.y, g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth / 2, g_player.pos.y, g_player.pos.z);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.45f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.45f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//---------------------------
//�v���C���[���̎擾
//---------------------------
PLAYER *GetPlayer(void)
{
	return &g_player;
}