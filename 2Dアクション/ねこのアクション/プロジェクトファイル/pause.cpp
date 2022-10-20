//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "life.h"
#include "player.h"
#include "block.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "timer.h"
#include "trap.h"
#include "bg.h"
#include "esystage01.h"
#include "sound.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTexturePause[MAX_PAUSE_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;					//���_�o�b�t�@�ւ̃|�C���^
PAUSE					g_pause[MAX_PAUSE];						//BG�̍\����
bool					g_bPuse = false;

//---------------------------
//����������
//---------------------------
HRESULT InitPause(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D			*pVtx;		//���_���ւ̃|�C���^
	int					nHeight = 0;	

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		g_pause[nCntPause].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / (3 + 1)) + ((SCREEN_HEIGHT / (3 + 1)) * nCntPause), 0.0f);
		g_pause[nCntPause].nType = nCntPause;
		g_pause[nCntPause].bUse = true;
	}
	if (g_pause[0].bUse == true)
	{
		g_pause[1].bUse = false;
		g_pause[2].bUse = false;
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/gamemenyu00.png",	//�e�N�X�`��
								&g_pTexturePause[0]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/gamemenyu01.png",	//�e�N�X�`��
								&g_pTexturePause[1]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/gamemenyu02.png",	//�e�N�X�`��
								&g_pTexturePause[2]);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_PAUSE,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffPause,
									NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//�u���b�N�̐����[�v
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x - PAUSE_X, g_pause[nCntPause].pos.y - PAUSE_Y, g_pause[nCntPause].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x + PAUSE_X, g_pause[nCntPause].pos.y - PAUSE_Y, g_pause[nCntPause].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x - PAUSE_X, g_pause[nCntPause].pos.y + PAUSE_Y, g_pause[nCntPause].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x + PAUSE_X, g_pause[nCntPause].pos.y + PAUSE_Y, g_pause[nCntPause].pos.z);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();


	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitPause(void)
{
	for (int nCntTex = 0; nCntTex < MAX_PAUSE_TEX; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePause[nCntTex] != NULL)
		{
			g_pTexturePause[nCntTex]->Release();
			g_pTexturePause[nCntTex] = NULL;
		}

	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
bool UpdatePause(void)
{
	VERTEX_2D			*pVtx;		//���_���ւ̃|�C���^
	PLAYER				*pPlayer;	//�v���C���[�̍\����

	pPlayer = GetPlayer();			//�v���C���[�̏����擾

	g_bPuse = false;				//�|�[�Y��

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_S) == true || GetKeyboardTrigger(DIK_DOWN) == true)
	{
		if (g_pause[0].bUse == true)
		{
			g_pause[0].bUse = false;
			g_pause[1].bUse = true;
		}
		else if (g_pause[1].bUse == true)
		{
			g_pause[1].bUse = false;
			g_pause[2].bUse = true;
		}
		else if (g_pause[2].bUse == true)
		{
			g_pause[2].bUse = false;
			g_pause[0].bUse = true;
		}
	}
	else if (GetKeyboardTrigger(DIK_W) == true || GetKeyboardTrigger(DIK_UP) == true)
	{
		if (g_pause[0].bUse == true)
		{
			g_pause[0].bUse = false;
			g_pause[2].bUse = true;
		}
		else if (g_pause[1].bUse == true)
		{
			g_pause[1].bUse = false;
			g_pause[0].bUse = true;
		}
		else if (g_pause[2].bUse == true)
		{
			g_pause[2].bUse = false;
			g_pause[1].bUse = true;
		}
	}

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		if (g_pause[nCntPause].bUse == true)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else if (g_pause[nCntPause].bUse == false)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 150);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 150);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 150);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 150);
		}
		if (GetKeyboardPress(DIK_Z) == true || GetKeyboardPress(DIK_LSHIFT) == true)
		{
			PlaySound(SOUND_LABEL_SE000);
			if (g_pause[nCntPause].nType == 0 && g_pause[nCntPause].bUse == true)
			{
				g_bPuse = true;
			}
			else if (g_pause[nCntPause].nType == 1 && g_pause[nCntPause].bUse == true)
			{
				g_bPuse = true;
				pPlayer->bUse = false;
				AddLife(-1);
				if (GetMode() == MODE_ES_STAGE01)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_ES_STAGE02)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 290.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_ES_STAGE03)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_NO_STAGE01)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 300.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_NO_STAGE02)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 400.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_NO_STAGE03)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 650.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_NO_STAGE04)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_HD_STAGE01)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
			}
			else if (g_pause[nCntPause].nType == 2 && g_pause[nCntPause].bUse == true && GetFade() == FADE_NONE)
			{
				UninitScore();

				UninitTimer();

				UninitLife();
				
				SetFade(MODE_HOME);
			}
		}
		pVtx += 4;	//���_��i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	return g_bPuse;
}

//---------------------------
//�`�揈��
//---------------------------
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X���擾����

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffPause,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//���_�t�H�[�}�b�g�̐ݒ�

									//�u���b�N�̐����[�v
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		pDevice->SetTexture(0, g_pTexturePause[g_pause[nCntPause].nType]);		//�e�N�X�`���̐ݒ�
		//�|���S���̕`��
		pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
								nCntPause * 4,
								2);
	}
}