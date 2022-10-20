//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "trap.h"
#include "player.h"
#include "life.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureTrap[MAX_TEX_TRAP] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTrap = NULL;			//���_�o�b�t�@�ւ̃|�C���^
TRAP					g_trap[MAX_TRAP];				//�u���b�N�̍\����

//---------------------------
//����������
//---------------------------
HRESULT InitTrap(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D			*pVtx;		//���_���ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	for (int nCntTrap = 0; nCntTrap < MAX_TRAP; nCntTrap++)
	{
		g_trap[nCntTrap].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		g_trap[nCntTrap].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
		g_trap[nCntTrap].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
		g_trap[nCntTrap].fWidth = 0.0f;								//��
		g_trap[nCntTrap].fHeight = 0.0f;							//����
		g_trap[nCntTrap].fTexwidth = 0.0f;							//�e�N�X�`���̕�
		g_trap[nCntTrap].fTexheigth = 0.0f;							//�e�N�X�`���̍���
		g_trap[nCntTrap].bUse = false;								//�g���Ă邩�ǂ���
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/trap.png",	//�������e�N�X�`��
								&g_pTextureTrap[0]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/trap01.png",	//�E�����e�N�X�`��
								&g_pTextureTrap[1]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/trap02.png",	//�������e�N�X�`��
								&g_pTextureTrap[2]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/trap03.png",	//������e�N�X�`��
								&g_pTextureTrap[3]);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_TRAP,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffTrap,
									NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTrap->Lock(0, 0, (void**)&pVtx, 0);

	//�u���b�N�̐����[�v
	for (int nCntTrap = 0; nCntTrap < MAX_TRAP; nCntTrap++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);

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
	g_pVtxBuffTrap->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitTrap(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEX_TRAP; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTrap[nCntTex] != NULL)
		{
			g_pTextureTrap[nCntTex]->Release();
			g_pTextureTrap[nCntTex] = NULL;
		}

	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTrap != NULL)
	{
		g_pVtxBuffTrap->Release();
		g_pVtxBuffTrap = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateTrap(void)
{
	VERTEX_2D			*pVtx;		//���_���ւ̃|�C���^
	PLAYER				*pPlayer;	//�v���C���[�̍\����

	pPlayer = GetPlayer();			//�v���C���[�̏����擾

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTrap->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTrap = 0; nCntTrap < MAX_TRAP; nCntTrap++)
	{
		if (g_trap[nCntTrap].bUse == true)
		{
			if (GetMode() == MODE_NO_STAGE03)
			{
				g_trap[nCntTrap].pos += g_trap[nCntTrap].move;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);

				if (g_trap[nCntTrap].pos.x <= 375)
				{
					g_trap[nCntTrap].bUse = false;
				}
			}
			else if (GetMode() == MODE_HD_STAGE01)
			{
				g_trap[nCntTrap].pos += g_trap[nCntTrap].move;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);

				if (pPlayer->pos.y >= 570 &&
					pPlayer->pos.x <= 750 &&
					pPlayer->pos.x >= 550)
				{
					g_trap[nCntTrap].move.x = 7.0f;
				}
			}
			if (GetMode() == MODE_HD_STAGE02)
			{
				g_trap[nCntTrap].pos += g_trap[nCntTrap].move;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);

				if (g_trap[nCntTrap].pos.x >= SCREEN_WIDTH)
				{
					g_trap[nCntTrap].bUse = false;
				}
			}
			if (pPlayer->bUse == true)
			{
				//�v���C���[�ɂ��M������
				if (pPlayer->pos.y >= g_trap[nCntTrap].pos.y &&
					pPlayer->pos.y - pPlayer->fHeight <= g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight &&
					pPlayer->pos.x + pPlayer->fWidth / 2 >= g_trap[nCntTrap].pos.x &&
					pPlayer->pos.x - pPlayer->fWidth / 2 <= g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth)
				{
					if (GetMode() == MODE_NO_STAGE01)
					{
						pPlayer->bUse = false;
						AddLife(-1);
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 300.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_NO_STAGE02)
					{
						pPlayer->bUse = false;
						AddLife(-1);
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 400.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_NO_STAGE03)
					{
						g_trap[nCntTrap].move.x = 0.0f;
						pPlayer->bUse = false;
						AddLife(-1);
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 650.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE01)
					{
						pPlayer->bUse = false;
						AddLife(-1);
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE02)
					{
						pPlayer->bUse = false;
						AddLife(-1);
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 670.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE03)
					{
						pPlayer->bUse = false;
						AddLife(-1);
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 650.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
				}
			}
			if (g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth <= 0)
			{
				g_trap[nCntTrap].bUse = false;
			}
			else if (g_trap[nCntTrap].pos.x >= SCREEN_WIDTH)
			{
				g_trap[nCntTrap].bUse = false;
			}
		}
		pVtx += 4;	//���_��i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTrap->Unlock();
}

//---------------------------
//�`�揈��
//---------------------------
void DrawTrap(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X���擾����

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffTrap,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//���_�t�H�[�}�b�g�̐ݒ�

	//�u���b�N�̐����[�v
	for (int nCntTrap = 0; nCntTrap < MAX_TRAP; nCntTrap++)
	{
		//�g���Ă���
		if (g_trap[nCntTrap].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureTrap[g_trap[nCntTrap].nType]);		//�e�N�X�`���̐ݒ�
			//�|���S���̕`��
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
									nCntTrap * 4,
									2);
		}
	}
}

//---------------------------
//�g���b�v�̃Z�b�g
//---------------------------
void SetTrap(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, float fTexwidth, float fTexheight, int nType)
{
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTrap->Lock(0, 0, (void**)&pVtx, 0);

	//�u���b�N�̐����[�v
	for (int nCntTrap = 0; nCntTrap < MAX_TRAP; nCntTrap++)
	{
		//�g���ĂȂ�������
		if (g_trap[nCntTrap].bUse == false)
		{
			g_trap[nCntTrap].pos = pos;					//�����Ă����ʒu����
			g_trap[nCntTrap].move = move;				//�����Ă����ړ��ʂ���
			g_trap[nCntTrap].fWidth = fWidth;			//�����Ă�����������
			g_trap[nCntTrap].fHeight = fHeight;			//�����Ă����c������
			g_trap[nCntTrap].fTexwidth = fTexwidth;		//�����Ă����e�N�X�`���̉�������
			g_trap[nCntTrap].fTexheigth = fTexheight;	//�����Ă����e�N�X�`���̏c������
			g_trap[nCntTrap].nType = nType;				//�����Ă����ړ��ʂ���

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_trap[nCntTrap].fTexwidth, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, g_trap[nCntTrap].fTexheigth);
			pVtx[3].tex = D3DXVECTOR2(g_trap[nCntTrap].fTexwidth, g_trap[nCntTrap].fTexheigth);

			g_trap[nCntTrap].bUse = true;	//�g���Ă���
			break;
		}
		pVtx += 4;	//���_��i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTrap->Unlock();
}

//---------------------------
//�g���b�v�̏����擾
//---------------------------
TRAP *GetTrap(void)
{
	return &g_trap[0];
}