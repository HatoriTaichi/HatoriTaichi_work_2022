//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "guninfo.h"
#include "keyinput.h"
#include "sound.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureGuninfo = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGuninfo = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Guninfo					g_aGuninfo[MAX_GUNDIGIT];			//BG�̍\����
GUNINFO_TYPE			g_aType;
int						g_nGunRemaining;

//---------------------------
//����������
//---------------------------
HRESULT InitGuninfo(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D			*pVtx;		//���_���ւ̃|�C���^
	int			aNumber[MAX_GUNDIGIT];	//�X�R�A�v�Z

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	for (int nCntGun = 0; nCntGun < MAX_GUNDIGIT; nCntGun++)
	{
		g_aGuninfo[nCntGun].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	}

	//�X�R�A�v�Z
	aNumber[0] = g_nGunRemaining % 100 / 10;
	aNumber[1] = g_nGunRemaining % 10 / 1;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/guninfo_00.png",			//�e�N�X�`��
								&g_pTextureGuninfo);
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_GUNDIGIT,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffGuninfo,
									NULL);
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGuninfo->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGun = 0; nCntGun < MAX_GUNDIGIT; nCntGun++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun - GUN_X, g_aGuninfo[nCntGun].pos.y - GUN_Y, g_aGuninfo[nCntGun].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun + GUN_X, g_aGuninfo[nCntGun].pos.y - GUN_Y, g_aGuninfo[nCntGun].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun - GUN_X, g_aGuninfo[nCntGun].pos.y + GUN_Y, g_aGuninfo[nCntGun].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun + GUN_X, g_aGuninfo[nCntGun].pos.y + GUN_Y, g_aGuninfo[nCntGun].pos.z);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGuninfo->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitGuninfo(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureGuninfo != NULL)
	{
		g_pTextureGuninfo->Release();
		g_pTextureGuninfo = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGuninfo != NULL)
	{
		g_pVtxBuffGuninfo->Release();
		g_pVtxBuffGuninfo = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateGuninfo(void)
{
	VERTEX_2D	*pVtx;		//���_���ւ̃|�C���^
	int			aNumber[MAX_GUNDIGIT];	//�X�R�A�v�Z
	int			nHeith = 0;	//����
	static int			nCntReloadeng;

	//�X�R�A�v�Z
	aNumber[0] = g_nGunRemaining % 100 / 10;
	aNumber[1] = g_nGunRemaining % 10 / 1;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGuninfo->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGun = 0; nCntGun < MAX_GUNDIGIT; nCntGun++, nHeith + 10.0f)
	{
		g_aGuninfo[nCntGun].pos = D3DXVECTOR3(SCREEN_WIDTH - (GUN_X * 4.5), SCREEN_HEIGHT - (GUN_Y / 0.5), 0.0f);

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun - GUN_X, g_aGuninfo[nCntGun].pos.y - GUN_Y, g_aGuninfo[nCntGun].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun + GUN_X, g_aGuninfo[nCntGun].pos.y - GUN_Y, g_aGuninfo[nCntGun].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun - GUN_X, g_aGuninfo[nCntGun].pos.y + GUN_Y, g_aGuninfo[nCntGun].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun + GUN_X, g_aGuninfo[nCntGun].pos.y + GUN_Y, g_aGuninfo[nCntGun].pos.z);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGuninfo->Unlock();

	if (g_nGunRemaining <= 0)
	{
		PlaySound(SOUND_RELOAD_00);
		nCntReloadeng++;
		if (g_aType == GUNINFO_TYPE_00)
		{
			if (nCntReloadeng > 144)
			{
				g_nGunRemaining = 10;
				nCntReloadeng = 0;
			}
		}
		else if (g_aType == GUNINFO_TYPE_01)
		{
			if (nCntReloadeng > 288)
			{
				g_nGunRemaining = 30;
				nCntReloadeng = 0;
			}
		}
	}
}

//---------------------------
//�`�揈��
//---------------------------
void DrawGuninfo(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();		//�f�o�C�X���擾����

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffGuninfo,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//���_�t�H�[�}�b�g�̐ݒ�

	for (int nCntGun = 0; nCntGun < MAX_GUNDIGIT; nCntGun++)
	{
		pDevice->SetTexture(0, g_pTextureGuninfo);		//�e�N�X�`���̐ݒ�

		//�|���S���̕`��
		pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
								nCntGun * 4,
								2);
	}
}

//---------------------------
//�c�i���v�Z
//---------------------------
void AddRemaining(int nShoot)
{
	//�X�R�A���Z
	g_nGunRemaining += nShoot;
}

//---------------------------
//�c�i���v�Z
//---------------------------
void SetGunType(GUNINFO_TYPE aType)
{
	g_aType = aType;

	if (g_aType == GUNINFO_TYPE_00)
	{
		g_nGunRemaining = 10;
	}
	else if (g_aType == GUNINFO_TYPE_01)
	{
		g_nGunRemaining = 30;
	}
}

//---------------------------
//�c�i���v�Z
//---------------------------
int GetRemaining(void)
{
	return g_nGunRemaining;
}