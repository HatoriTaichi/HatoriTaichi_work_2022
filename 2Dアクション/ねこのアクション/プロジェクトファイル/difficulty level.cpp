//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "difficulty level.h"
#include "bullet.h"
#include "fade.h"
#include "sound.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureLetter[MAX_LEVEL] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLetter = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LETTER					g_aLetter[MAX_LEVEL];			//���x�������̍\����

//---------------------------
//����������
//---------------------------
HRESULT InitLetter(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D			*pVtx;		//���_���ւ̃|�C���^
	pDevice = GetDevice();			//�f�o�C�X�̎擾

	//���x���������[�v
	for (int nCntLevel = 0; nCntLevel < MAX_LEVEL; nCntLevel++)
	{
		g_aLetter[nCntLevel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���x�������̈ʒu
		g_aLetter[nCntLevel].nType = 0;								//���x�������̎��		
		g_aLetter[nCntLevel].nUse = false;							//�g�������
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/easy.png",	//�e�N�X�`��
								&g_pTextureLetter[0]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/normal.png",	//�e�N�X�`��
								&g_pTextureLetter[1]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/hard.png",	//�e�N�X�`��
								&g_pTextureLetter[2]);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_LEVEL,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffLetter,
									NULL);
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLetter->Lock(0, 0, (void**)&pVtx, 0);

	//���x������
	for (int nCntLevel = 0; nCntLevel < MAX_LEVEL; nCntLevel++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x - TETTER_X, g_aLetter[nCntLevel].pos.y - TETTER_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x + TETTER_X, g_aLetter[nCntLevel].pos.y - TETTER_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x - TETTER_X, g_aLetter[nCntLevel].pos.y + TETTER_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x + TETTER_X, g_aLetter[nCntLevel].pos.y + TETTER_Y, 0.0f);

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

		pVtx += 4;		//���_�����i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLetter->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitLetter(void)
{
	//���x������
	for (int nCntLevel = 0; nCntLevel < MAX_LEVEL; nCntLevel++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureLetter[nCntLevel] != NULL)
		{
			g_pTextureLetter[nCntLevel]->Release();
			g_pTextureLetter[nCntLevel] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLetter != NULL)
	{
		g_pVtxBuffLetter->Release();
		g_pVtxBuffLetter = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateLetter(void)
{
	BULLET			*pbullet;

	pbullet = GetBullet();
	//���x���������[�v
	for (int nCntLevel = 0; nCntLevel < MAX_LEVEL; nCntLevel++)
	{
		//�g���Ă���
		if (g_aLetter[nCntLevel].nUse == true)
		{
			//�^�C�v0
			if (g_aLetter[nCntLevel].nType == 0)
			{
				for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pbullet++)
				{
					//����������
					if (pbullet->pos.x + BULLET_SIZE_X >= g_aLetter[nCntLevel].pos.x - TETTER_X &&
						pbullet->pos.x - BULLET_SIZE_X <= g_aLetter[nCntLevel].pos.x + TETTER_X &&
						pbullet->pos.y + BULLET_SIZE_Y >= g_aLetter[nCntLevel].pos.y - TETTER_Y &&
						pbullet->pos.y - BULLET_SIZE_Y <= g_aLetter[nCntLevel].pos.y + TETTER_Y &&
						GetFade() == FADE_NONE)
					{
						pbullet->bUse = false;
						g_aLetter[nCntLevel].nUse = false;
						PlaySound(SOUND_LABEL_SE000);
						SetFade(MODE_ES_STAGE01);
					}
				}
				pbullet -= MAX_BULLET;
			}
			//�^�C�v1
			else if (g_aLetter[nCntLevel].nType == 1)
			{
				for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pbullet++)
				{
					//����������
					if (pbullet->pos.x + BULLET_SIZE_X >= g_aLetter[nCntLevel].pos.x - TETTER_X &&
						pbullet->pos.x - BULLET_SIZE_X <= g_aLetter[nCntLevel].pos.x + TETTER_X &&
						pbullet->pos.y + BULLET_SIZE_Y >= g_aLetter[nCntLevel].pos.y - TETTER_Y &&
						pbullet->pos.y - BULLET_SIZE_Y <= g_aLetter[nCntLevel].pos.y + TETTER_Y &&
						GetFade() == FADE_NONE)
					{
						pbullet->bUse = false;
						g_aLetter[nCntLevel].nUse = false;
						PlaySound(SOUND_LABEL_SE000);
						SetFade(MODE_NO_STAGE01);
					}
				}
				pbullet -= MAX_BULLET;
			}
			//�^�C�v2
			else if (g_aLetter[nCntLevel].nType == 2)
			{
				for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pbullet++)
				{
					//����������
					if (pbullet->pos.x + BULLET_SIZE_X >= g_aLetter[nCntLevel].pos.x - TETTER_X &&
						pbullet->pos.x - BULLET_SIZE_X <= g_aLetter[nCntLevel].pos.x + TETTER_X &&
						pbullet->pos.y + BULLET_SIZE_Y >= g_aLetter[nCntLevel].pos.y - TETTER_Y &&
						pbullet->pos.y - BULLET_SIZE_Y <= g_aLetter[nCntLevel].pos.y + TETTER_Y &&
						GetFade() == FADE_NONE)
					{
						pbullet->bUse = false;
						g_aLetter[nCntLevel].nUse = false;
						PlaySound(SOUND_LABEL_SE000);
						SetFade(MODE_HD_STAGE01);
					}
				}
				pbullet -= MAX_BULLET;
			}
		}
	}
}

//---------------------------
//�`�揈��
//---------------------------
void DrawLetter(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();		//�f�o�C�X���擾����

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffLetter,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//���_�t�H�[�}�b�g�̐ݒ�

	//���x���������[�v
	for (int nCntLevel = 0; nCntLevel < MAX_LEVEL; nCntLevel++)
	{
		//�g���Ă���
		if (g_aLetter[nCntLevel].nUse == true)
		{
			pDevice->SetTexture(0, g_pTextureLetter[g_aLetter[nCntLevel].nType]);		//�e�N�X�`���̐ݒ�
			//�|���S���̕`��
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
									nCntLevel * 4,
									2);
		}
	}
}

//---------------------------
//�u���b�N�̃Z�b�g
//---------------------------

void SetLetter(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLetter->Lock(0, 0, (void**)&pVtx, 0);
	//���x������
	for (int nCntLevel = 0; nCntLevel < MAX_LEVEL; nCntLevel++)
	{
		if (g_aLetter[nCntLevel].nUse == false)
		{
			g_aLetter[nCntLevel].pos = pos;			//�����Ă����ʒu����
			g_aLetter[nCntLevel].nType = nType;		//�����Ă�����ނ���
													//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x - TETTER_X, g_aLetter[nCntLevel].pos.y - TETTER_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x + TETTER_X, g_aLetter[nCntLevel].pos.y - TETTER_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x - TETTER_X, g_aLetter[nCntLevel].pos.y + TETTER_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x + TETTER_X, g_aLetter[nCntLevel].pos.y + TETTER_Y, 0.0f);

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
			
			g_aLetter[nCntLevel].nUse = true;
			break;
		}
		pVtx += 4;	//���_�̐���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLetter->Unlock();
}

//---------------------------
//�u���b�N�̃Z�b�g
//---------------------------

LETTER *GetLetter(void)
{
	return &g_aLetter[0];
}