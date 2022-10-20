//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "enemy.h"
#include "block.h"
#include "player.h"
#include "life.h"
#include "bullet.h"
#include "sound.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureEnemy[MAX_ENEMY_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					//���_�o�b�t�@�ւ̃|�C���^
ENEMY					g_enemy[MAX_ENEMY];						//�u���b�N�̍\����
int						g_nAnim;
int						g_nPatn;

//---------------------------
//����������
//---------------------------
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D			*pVtx;		//���_���ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	//�G�̐����[�v
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_enemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�G�̈ʒu
		g_enemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�G�̈ʒu
		g_enemy[nCntEnemy].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�G�̈ʒu
		g_enemy[nCntEnemy].fWidth = 0.0f;							//�G�̉���
		g_enemy[nCntEnemy].fHeight = 0.0f;							//�G�̏c��
		g_enemy[nCntEnemy].bJump = false;							//�W�����v�̏��
		g_enemy[nCntEnemy].bUse = false;							//�G�̏��
		g_enemy[nCntEnemy].bDamage = true;							//�G�̏��
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/enemy00.png",	//�e�N�X�`��
								&g_pTextureEnemy[0]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/enemy01.png",	//�e�N�X�`��
								&g_pTextureEnemy[1]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/enemy02.png",	//�e�N�X�`��
								&g_pTextureEnemy[2]);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//�G�̐����[�v
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

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
	g_pVtxBuffEnemy->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitEnemy(void)
{
	//�G�̐����[�v
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY_TEX; nCntEnemy++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureEnemy[nCntEnemy] != NULL)
		{
			g_pTextureEnemy[nCntEnemy]->Release();
			g_pTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateEnemy(void)
{
	VERTEX_2D			*pVtx;		//���_���ւ̃|�C���^
	PLAYER				*pPlayer;	//�v���C���[�\����
	static int			nBullet = 0;//�e�̊Ԋu
	static int			nTimer;		//�^�C�}�[
	static int			nTimer2;	//�_��
	static int			nTimer3;	//�_��
	static int			nCol = 255;	//�`�J�`�J

	pPlayer = GetPlayer();			//�v���C���[�\����

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_enemy[nCntEnemy].posold = g_enemy[nCntEnemy].pos;	//�O��̈ʒu��ۑ�
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//�G�̐����[�v
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//�g���Ă���
		if (g_enemy[nCntEnemy].bUse == true)
		{
			//�G�^�C�v0
			if (g_enemy[nCntEnemy].nType == 0)
			{
				if (GetMode() == MODE_ES_STAGE01 || GetMode() == MODE_NO_STAGE02 || GetMode() == MODE_HD_STAGE02)
				{
					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					//���t���[���d�͂��{
					g_enemy[nCntEnemy].pos.y += G_POW;
					//�ړ��ʂ��{
					g_enemy[nCntEnemy].pos.y += g_enemy[nCntEnemy].move.y;

					CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 1);

					g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].move.x;

					g_nAnim++;
					if (g_nAnim >= 150)
					{
						g_nPatn++;
						if (g_nPatn > 1)
						{
							g_nPatn = 0;
						}
						g_nAnim = 0;
					}
					if (g_enemy[nCntEnemy].move.x >= 0.0f)
					{
						pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5 * g_nPatn, 0.5f);
						pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5 * g_nPatn, 0.5f);
						pVtx[2].tex = D3DXVECTOR2(0.0f + 0.5 * g_nPatn, 1.0f);
						pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5 * g_nPatn, 1.0f);
					}
					else if (g_enemy[nCntEnemy].move.x <= 0.0f)
					{
						pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5 * g_nPatn, 0.0f);
						pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5 * g_nPatn, 0.0f);
						pVtx[2].tex = D3DXVECTOR2(0.0f + 0.5 * g_nPatn, 0.5f);
						pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5 * g_nPatn, 0.5f);
					}
				}
			}
			//�G�^�C�v1
			if (g_enemy[nCntEnemy].nType == 1)
			{
				if (GetMode() == MODE_ES_STAGE01)
				{
					g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].move.x;

					if (g_enemy[nCntEnemy].bJump == false)
					{
						g_enemy[nCntEnemy].move.y = -10.0f;
						g_enemy[nCntEnemy].bJump = true;
					}

					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					//���t���[���d�͂��{
					g_enemy[nCntEnemy].move.y += G_POW;
					//�ړ��ʂ��{
					g_enemy[nCntEnemy].pos.y += g_enemy[nCntEnemy].move.y;

					if (CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 2) == true)
					{
						g_enemy[nCntEnemy].bJump = false;
					}
					//��ʍ��[�ɏo����
					if (g_enemy[nCntEnemy].pos.x - ENEMY_X_SIZE <= 0)
					{
						//���[�ɃZ�b�g
						g_enemy[nCntEnemy].pos.x = 0.0f + ENEMY_X_SIZE;
						g_enemy[nCntEnemy].move.x *= -1;
					}
				}
				else if (GetMode() == MODE_HD_STAGE01)
				{
					g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].move.x;

					if (g_enemy[nCntEnemy].bJump == false)
					{
						g_enemy[nCntEnemy].move.y = -10.0f;
						g_enemy[nCntEnemy].bJump = true;
					}

					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					//���t���[���d�͂��{
					g_enemy[nCntEnemy].move.y += G_POW;
					//�ړ��ʂ��{
					g_enemy[nCntEnemy].pos.y += g_enemy[nCntEnemy].move.y;

					if (CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 2) == true)
					{
						g_enemy[nCntEnemy].bJump = false;
					}
				}
				else if (GetMode() == MODE_HD_STAGE03)
				{
					g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].move.x;

					if (g_enemy[nCntEnemy].bJump == false)
					{
						g_enemy[nCntEnemy].move.y = -10.0f;
						g_enemy[nCntEnemy].bJump = true;
					}

					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					//���t���[���d�͂��{
					g_enemy[nCntEnemy].move.y += G_POW;
					//�ړ��ʂ��{
					g_enemy[nCntEnemy].pos.y += g_enemy[nCntEnemy].move.y;

					if (CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 2) == true)
					{
						g_enemy[nCntEnemy].bJump = false;
					}
					if (g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2 <= 400)
					{
						g_enemy[nCntEnemy].move.x *= -1;
					}
				}
				if (g_enemy[nCntEnemy].move.x >= 0.0f)
				{
					pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				}
				else if (g_enemy[nCntEnemy].move.x <= 0.0f)
				{
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
				}
			}
			//�G�^�C�v2
			if (g_enemy[nCntEnemy].nType == 2)
			{
				if (GetMode() == MODE_ES_STAGE03)
				{
					g_enemy[nCntEnemy].pos.y += g_enemy[nCntEnemy].move.y;

					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					if (CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 4) == true)
					{

					}

					nBullet++;
					if (nBullet >= ENEMY_BULLET_SPAN)
					{
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-4.0f, 0.0f, 0.0f), BULLET_SIZE_X * 10, BULLET_SIZE_Y * 10, 1);
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-2.0f, -2.0f, 0.0f), BULLET_SIZE_X * 10, BULLET_SIZE_Y * 10, 1);
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-2.0f, +2.0f, 0.0f), BULLET_SIZE_X * 10, BULLET_SIZE_Y * 10, 1);
						PlaySound(SOUND_LABEL_SE001);
						nBullet = 0;
					}
				}
				else if (GetMode() == MODE_NO_STAGE04)
				{
					g_enemy[nCntEnemy].pos += g_enemy[nCntEnemy].move;

					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					if (CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 4) == true)
					{
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-4.0f, 4.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 3);
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-4.0f, -4.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 3);
						PlaySound(SOUND_LABEL_SE001);
					}

					nBullet++;
					if (nBullet >= ENEMY_BULLET_SPAN)
					{
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-2.0f, 2.0f, 0.0f), BULLET_SIZE_X * 10, BULLET_SIZE_Y * 10, 1);
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-2.0f, -2.0f, 0.0f), BULLET_SIZE_X * 10, BULLET_SIZE_Y * 10, 1);
						PlaySound(SOUND_LABEL_SE001);
						nBullet = 0;
					}
				}
				else if (GetMode() == MODE_HD_STAGE04)
				{
					g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].move.x;

					if (g_enemy[nCntEnemy].bJump == false)
					{
						g_enemy[nCntEnemy].move.y = -20.0f;
						g_enemy[nCntEnemy].bJump = true;
					}

					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					//���t���[���d�͂��{
					g_enemy[nCntEnemy].move.y += G_POW;
					//�ړ��ʂ��{
					g_enemy[nCntEnemy].pos.y += g_enemy[nCntEnemy].move.y;

					if (CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 2) == true)
					{
						g_enemy[nCntEnemy].bJump = false;
					}
				}
				else if (GetMode() == MODE_HD_STAGE05)
				{
					g_enemy[nCntEnemy].pos += g_enemy[nCntEnemy].move;

					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					if (CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 4) == true)
					{
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 2);
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 2);
						PlaySound(SOUND_LABEL_SE001);
					}

					nBullet++;
					if (nBullet >= ENEMY_BULLET_SPAN)
					{
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-3.0f, 0.0f, 0.0f), BULLET_SIZE_X * 10, BULLET_SIZE_Y * 10, 1);
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-1.4f, -2.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 3);
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-1.4f, -2.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 3);
						PlaySound(SOUND_LABEL_SE001);
						nBullet = 0;
					}
					if (g_enemy[nCntEnemy].pos.x <= SCREEN_WIDTH / 2)
					{
						g_enemy[nCntEnemy].move.x *= -1;
					}
				}
			}
			//�v���C���[�ɐG�ꂽ��
			if (pPlayer->pos.x - pPlayer->fWidth / 2 <= g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2 &&
				pPlayer->pos.x + pPlayer->fWidth / 2 >= g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2 &&
				pPlayer->pos.y - pPlayer->fWidth <= g_enemy[nCntEnemy].pos.y &&
				pPlayer->pos.y >= g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fWidth &&
				pPlayer->bUse == true)
			{
				pPlayer->bUse = false;
				AddLife(-1);
				if (GetMode() == MODE_ES_STAGE01)
				{
					SetPlayer(D3DXVECTOR3(0.0f + pPlayer->fWidth / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_ES_STAGE03)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_NO_STAGE02)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 400.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_NO_STAGE04)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_HD_STAGE01)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_HD_STAGE02)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 670.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_HD_STAGE03)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 650.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_HD_STAGE04)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.2f, SCREEN_HEIGHT - 11.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
			}
			if (g_enemy[nCntEnemy].bDamage == false)
			{
				nTimer2++;	//�_�Ń^�C�~���O
				nTimer3++;	//�_�Ń^�C�~���O
				//�_�Ń^�C�~���O�ɂȂ���
				if (nTimer3 == 10)
				{
					nTimer2 = nTimer3;	//�^�C�~���O��n����
					nTimer3 = 0;		//0�ɂȂ�
				}
				//R��255�� && �^�C�~���O�����Ă���
				if (nCol == 255 && nTimer2 == 10)
				{
					nCol = 0;		//����
					nTimer2 = 0;	//�^�C�~���O������
					if (nCol == 0)
					{
						g_enemy[nCntEnemy].bDamage = true;
					}
				}
				//A��0�� && �^�C�~���O�����Ă�
				else if (nCol == 0 && nTimer2 == 10)
				{
					nCol = 255;		//������
					nTimer2 = 0;	//�^�C�~���O������
				}
				pVtx[0].col = D3DCOLOR_RGBA(nCol, 0, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(nCol, 0, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(nCol, 0, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(nCol, 0, 0, 255);
				if (nCol == 0)
				{
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
			}
			//���ɗ�������
			if (g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight >= SCREEN_HEIGHT)
			{
				g_enemy[nCntEnemy].bUse = false;
			}
		}
		pVtx += 4;	//���_��i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//---------------------------
//�`�揈��
//---------------------------
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffEnemy,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//���_�t�H�[�}�b�g�̐ݒ�
	//�G�̐����[�v
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//�g���Ă���
		if (g_enemy[nCntEnemy].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureEnemy[g_enemy[nCntEnemy].nType]);		//�e�N�X�`���̐ݒ�
			//�|���S���̕`��
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
									nCntEnemy * 4,
									2);
		}
	}
}

//---------------------------
//�G�̃Z�b�g
//---------------------------
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, int nType, int nLife)
{
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//�G�̐����[�v
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//�g���ĂȂ�������
		if (g_enemy[nCntEnemy].bUse == false)
		{
			g_enemy[nCntEnemy].pos = pos;			//�����Ă����ʒu����
			g_enemy[nCntEnemy].move = move;			//�����Ă����ړ��ʂ���
			g_enemy[nCntEnemy].fWidth = fWidth;		//�����Ă�����������
			g_enemy[nCntEnemy].fHeight = fHeight;	//�����Ă����c������
			g_enemy[nCntEnemy].nType = nType;		//�����Ă�����ނ���
			g_enemy[nCntEnemy].nLife = nLife;		//�����Ă����̗͂���

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

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

			g_enemy[nCntEnemy].bUse = true;	//�g���Ă���
			break;
		}
		pVtx += 4;	//���_��i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//---------------------------
//�G�̏��
//---------------------------
ENEMY *GetEnemy(void)
{
	return &g_enemy[0];
}