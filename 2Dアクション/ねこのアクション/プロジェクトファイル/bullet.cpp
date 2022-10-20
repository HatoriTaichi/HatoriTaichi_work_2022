//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "bullet.h"
#include "block.h"
#include "enemy.h"
#include "player.h"
#include "score.h"
#include "life.h"
#include "fade.h"
#include "sound.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureBullet[MAX_TEX] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			//���_�o�b�t�@�ւ̃|�C���^
BULLET					g_Bullet[MAX_BULLET];				//�ʂ̍\����
int						g_nLevel;							//���x������̊Ǘ�

//---------------------------
//����������
//---------------------------
HRESULT InitBullet(void)
{
	FILE				*pFile;		//�t�@�C���J��
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D			*pVtx;		//���_���ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̎擾
	//�e�̏�����
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_Bullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		g_Bullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ�
		g_Bullet[nCntBullet].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
		g_Bullet[nCntBullet].fHeight = 0.0f;							//����
		g_Bullet[nCntBullet].fWidth = 0.0f;								//��
		g_Bullet[nCntBullet].bUse = false;								//�g���Ă邩�ǂ���
		g_Bullet[nCntBullet].bRft = true;								//���˂�����
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/bullet00.png",
								&g_pTextureBullet[0]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/bullet01.png",
								&g_pTextureBullet[1]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/bullet02.png",
								&g_pTextureBullet[2]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/bullet03.png",
								&g_pTextureBullet[3]);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_BULLET,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffBullet,
									NULL);
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();

	//�t�@�C���J��
	pFile = fopen("stat.bin", "rb");
	//�Ȃ񂩓����Ă���
	if (pFile != NULL)
	{
		//�����L���O����
		fscanf(pFile, "%d", &g_nLevel);
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
void UninitBullet(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_TEX; nCntBullet++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBullet[nCntBullet] != NULL)
		{
			g_pTextureBullet[nCntBullet]->Release();
			g_pTextureBullet[nCntBullet] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateBullet(void)
{
	VERTEX_2D	*pVtx;		//���_���ւ̃|�C���^
	FILE		*pFile;		//�t�@�C���J��
	ENEMY		*pEnemy;	//�e�̃|�C���^
	PLAYER		*pPlayer;	//�v���C���[�̃|�C���^

	pEnemy = GetEnemy();	//�G�̏����擾
	pPlayer = GetPlayer();	//�v���C���[�̏����擾

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//�O��̈ʒu��ۑ�
		g_Bullet[nCntBullet].posold = g_Bullet[nCntBullet].pos;
	}
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//�e���g���Ă���
		if (g_Bullet[nCntBullet].bUse == true)
		{
			//�����̒e
			if (g_Bullet[nCntBullet].nType == 0)
			{
				//�G�𐔂���
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					//�G���g���Ă���
					if (pEnemy->bUse == true)
					{
						//�G�ɓ���������
						if (g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2 >= pEnemy->pos.x - pEnemy->fWidth / 2 &&
							g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2 <= pEnemy->pos.x + pEnemy->fWidth / 2 &&
							g_Bullet[nCntBullet].pos.y >= pEnemy->pos.y - pEnemy->fHeight &&
							g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight <= pEnemy->pos.y &&
							GetMode() != MODE_HOME)
						{
							PlaySound(SOUND_LABEL_SE002);
							AddScore(50);
							//�G�̃^�C�v��2
							if (pEnemy->nType == 2)
							{
								pEnemy->bDamage = false;
								AddScore(100);
								//�g���ĂȂ�
								g_Bullet[nCntBullet].bUse = false;	
								//�G�̗̑͂�����
								pEnemy->nLife--;
								//�̗͂�0�ɂȂ�����
								if (pEnemy->nLife <= 0)
								{
									//ES�{�X
									if (GetMode() == MODE_ES_STAGE03)
									{
										if (g_nLevel == 0)
										{
											g_nLevel = 1;
										}
										if (g_nLevel < 2)
										{
											//�t�@�C���J��
											pFile = fopen("stat.bin", "wb");
											//�Ȃ񂩓����Ă���
											if (pFile != NULL)
											{
												//�����L���O�ۑ�
												fprintf(pFile, "%d", 1);
												//����
												fclose(pFile);
											}
											else
											{
												printf("�ǂݎ��Ȃ���");
											}
										}
										AddScore(200);						//�X�R�A���Z
									}
									else if (GetMode() == MODE_NO_STAGE04)
									{
										if (g_nLevel < 2)
										{
											g_nLevel = 2;
										}
										//�t�@�C���J��
										pFile = fopen("stat.bin", "wb");
										//�Ȃ񂩓����Ă���
										if (pFile != NULL)
										{
											//�����L���O�ۑ�
											fprintf(pFile, "%d", 2);
											//����
											fclose(pFile);
										}
										else
										{
											printf("�ǂݎ��Ȃ���");
										}
										AddScore(400);						//�X�R�A���Z
									}
									else if (GetMode() == MODE_HD_STAGE04)
									{
										AddScore(500);						//�X�R�A���Z
									}
									else if (GetMode() == MODE_HD_STAGE05)
									{
										AddScore(700);						//�X�R�A���Z
									}
									g_Bullet[nCntBullet].bUse = false;	//�g���ĂȂ�
									pEnemy->bUse = false;				//�g���ĂȂ�
									if (GetFade() == FADE_NONE && GetMode() != MODE_HD_STAGE04)
									{
										SetFade(MODE_RESULT);
									}
									else if (GetFade() == FADE_NONE && GetMode() == MODE_HD_STAGE04)
									{
										SetFade(MODE_HD_STAGE05);
									}
								}
							}
							//�G�̃^�C�v��2�ȊO
							else if (pEnemy->nType != 2)
							{
								g_Bullet[nCntBullet].bUse = false;	//�g���ĂȂ�
								pEnemy->bUse = false;				//�g���ĂȂ�
							}
						}
					}
				}
				//��������������
				pEnemy -= MAX_ENEMY;
				//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				pVtx[0].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);

				//�ړ���+
				g_Bullet[nCntBullet].pos.x += g_Bullet[nCntBullet].move.x;

				//��ʊO�ɏo����
				if (g_Bullet[nCntBullet].pos.x - BULLET_SIZE_X >= SCREEN_WIDTH)
				{
					g_Bullet[nCntBullet].bUse = false;
				}
				//�ǂɂԂ�����
				else if (CollisionBlock(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posold, &g_Bullet[nCntBullet].move, g_Bullet[nCntBullet].fWidth, g_Bullet[nCntBullet].fHeight, 3) == true)
				{
					g_Bullet[nCntBullet].bUse = false;
				}
			}
			//�G�̒e
			if (g_Bullet[nCntBullet].nType == 1)
			{
				//�v���C���[�ɓ���������
				if (g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2 >= pPlayer->pos.x - pPlayer->fWidth / 2 &&
					g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2 <= pPlayer->pos.x + pPlayer->fWidth / 2 &&
					g_Bullet[nCntBullet].pos.y >= pPlayer->pos.y - pPlayer->fHeight &&
					g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight <= pPlayer->pos.y &&
					pPlayer->bUse == true)
				{
					PlaySound(SOUND_LABEL_SE002);
					pPlayer->bUse = false;
					AddLife(-1);
					g_Bullet[nCntBullet].bUse = false;	//�g���ĂȂ�
					if (GetMode() == MODE_ES_STAGE03)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE05)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.2f, SCREEN_HEIGHT - 11.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
				}
				//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				pVtx[0].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);

				//�ړ���+
				g_Bullet[nCntBullet].pos += g_Bullet[nCntBullet].move;

				//��ʊO�ɏo����
				if (g_Bullet[nCntBullet].pos.x - BULLET_SIZE_X >= SCREEN_WIDTH)
				{
					g_Bullet[nCntBullet].bUse = false;
				}
				//�ǂɂԂ�����
				else if (CollisionBlock(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posold, &g_Bullet[nCntBullet].move, g_Bullet[nCntBullet].fWidth, g_Bullet[nCntBullet].fHeight, 3) == true)
				{
					g_Bullet[nCntBullet].bUse = false;
				}
			}
			//�G�̒e
			if (g_Bullet[nCntBullet].nType == 2)
			{
				//�e�ƃv���C���[�̍��������
				g_Bullet[nCntBullet].posdfrc = pPlayer->posold - g_Bullet[nCntBullet].pos;

				//�v���C���[�ɓ���������
				if (g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2 >= pPlayer->pos.x - pPlayer->fWidth / 2 &&
					g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2 <= pPlayer->pos.x + pPlayer->fWidth / 2 &&
					g_Bullet[nCntBullet].pos.y >= pPlayer->pos.y - pPlayer->fHeight &&
					g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight <= pPlayer->pos.y &&
					pPlayer->bUse == true)
				{
					PlaySound(SOUND_LABEL_SE002);
					pPlayer->bUse = false;
					AddLife(-1);
					g_Bullet[nCntBullet].bUse = false;	//�g���ĂȂ�
					if (GetMode() == MODE_ES_STAGE03)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_NO_STAGE04)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE01)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE04)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.2f, SCREEN_HEIGHT - 11.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE05)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.2f, SCREEN_HEIGHT - 11.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
				}
				//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				pVtx[0].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);

				if (GetMode() == MODE_NO_STAGE04)
				{
					if (g_Bullet[nCntBullet].posdfrc.x >= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = 1.0f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.x <= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = -1.0f;
					}
					if (g_Bullet[nCntBullet].posdfrc.y >= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = 1.0f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.y <= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = -1.0f;
					}
				}
				else if (GetMode() == MODE_HD_STAGE01)
				{
					if (g_Bullet[nCntBullet].posdfrc.x >= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = 2.0f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.x <= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = -2.0f;
					}
					if (g_Bullet[nCntBullet].posdfrc.y >= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = 2.0f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.y <= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = -2.0f;
					}
				}
				else if (GetMode() == MODE_HD_STAGE04)
				{
					if (g_Bullet[nCntBullet].posdfrc.x >= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = 1.0f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.x <= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = -1.0f;
					}
					if (g_Bullet[nCntBullet].posdfrc.y >= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = 1.0f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.y <= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = -1.0f;
					}
				}
				else if (GetMode() == MODE_HD_STAGE05)
				{
					if (g_Bullet[nCntBullet].posdfrc.x >= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = 1.2f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.x <= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = -1.2f;
					}
					if (g_Bullet[nCntBullet].posdfrc.y >= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = 1.2f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.y <= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = -1.2f;
					}
				}
				//�ړ���+
				g_Bullet[nCntBullet].pos += g_Bullet[nCntBullet].move;

				//��ʊO�ɏo����
				if (g_Bullet[nCntBullet].pos.x - BULLET_SIZE_X >= SCREEN_WIDTH)
				{
					g_Bullet[nCntBullet].bUse = false;
				}
				//�ǂɂԂ�����
				else if (CollisionBlock(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posold, &g_Bullet[nCntBullet].move, g_Bullet[nCntBullet].fWidth, g_Bullet[nCntBullet].fHeight, 3) == true)
				{
					g_Bullet[nCntBullet].bUse = false;
				}
			}
			//�G�̒e
			if (g_Bullet[nCntBullet].nType == 3)
			{
				//�v���C���[�ɓ���������
				if (g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2 >= pPlayer->pos.x - pPlayer->fWidth / 2 &&
					g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2 <= pPlayer->pos.x + pPlayer->fWidth / 2 &&
					g_Bullet[nCntBullet].pos.y >= pPlayer->pos.y - pPlayer->fHeight &&
					g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight <= pPlayer->pos.y &&
					pPlayer->bUse == true)
				{
					PlaySound(SOUND_LABEL_SE002);
					pPlayer->bUse = false;
					AddLife(-1);
					g_Bullet[nCntBullet].bUse = false;	//�g���ĂȂ�
					if (GetMode() == MODE_ES_STAGE03)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_NO_STAGE04)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE05)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.2f, SCREEN_HEIGHT - 11.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
				}
				//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				pVtx[0].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);

				//�ړ���+
				g_Bullet[nCntBullet].pos += g_Bullet[nCntBullet].move;

				//��ʊO�ɏo����
				if (g_Bullet[nCntBullet].pos.x - BULLET_SIZE_X >= SCREEN_WIDTH)
				{
					g_Bullet[nCntBullet].bUse = false;
				}
				//�ǂɂԂ�����
				else if (CollisionBlock(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posold, &g_Bullet[nCntBullet].move, g_Bullet[nCntBullet].fWidth, g_Bullet[nCntBullet].fHeight, 3) == true)
				{
					//�����͂񂵂�
					if (g_Bullet[nCntBullet].bRft == true)
					{
						g_Bullet[nCntBullet].move.y *= -1;
						g_Bullet[nCntBullet].bRft = false;
					}
					//���˂�����
					else if (g_Bullet[nCntBullet].bRft == false)
					{
						g_Bullet[nCntBullet].bUse = false;
					}
				}
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//---------------------------
//�`�揈��
//---------------------------
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffBullet,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);				//���_�t�H�[�}�b�g�̐ݒ�
	//�|���S���̕`��
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//�g���Ă���
		if (g_Bullet[nCntBullet].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureBullet[g_Bullet[nCntBullet].nType]);	//�e�N�X�`���̐ݒ�
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
									nCntBullet * 4,
									2);
		}
	}
}

//---------------------------
//�e�̃Z�b�g
//---------------------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, int nType)
{
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == false)
		{
			if (move.x == 0.0f)
			{
				move.x = 6.0f;
			}
			g_Bullet[nCntBullet].pos = pos;				//�����Ă����ʒu����
			g_Bullet[nCntBullet].move = move;			//�����Ă����ړ��ʂ���
			g_Bullet[nCntBullet].fWidth = fWidth;		//�����Ă���������
			g_Bullet[nCntBullet].fHeight = fHeight;		//�����Ă�����������
			g_Bullet[nCntBullet].nType = nType;			//�����Ă�����ނ���
				
			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			pVtx[0].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);

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

			g_Bullet[nCntBullet].bUse = true;
			g_Bullet[nCntBullet].bRft = true;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//---------------------------
//�e�̏����擾
//---------------------------
BULLET *GetBullet(void)
{
	return &g_Bullet[0];
}