//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "round.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureRound = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRound = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Round					g_aRound[MAX_ROUNDDIGIT];	//BG�̍\����
int						g_nCntRound;

//---------------------------
//����������
//---------------------------
HRESULT InitRound(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D			*pVtx;		//���_���ւ̃|�C���^
	int			aNumber[MAX_ROUNDDIGIT];	//�X�R�A�v�Z

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	for (int nCntRound = 0; nCntRound < MAX_ROUNDDIGIT; nCntRound++)
	{
		g_aRound[nCntRound].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	}

	g_nCntRound = 0;

	//�X�R�A�v�Z
	aNumber[0] = g_nCntRound % 100 / 10;
	aNumber[1] = g_nCntRound % 10 / 1;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/guninfo_00.png",			//�e�N�X�`��
								&g_pTextureRound);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_ROUNDDIGIT,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffRound,
									NULL);
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRound->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRound = 0; nCntRound < MAX_ROUNDDIGIT; nCntRound++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound - ROUND_X, g_aRound[nCntRound].pos.y - ROUND_Y, g_aRound[nCntRound].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound + ROUND_X, g_aRound[nCntRound].pos.y - ROUND_Y, g_aRound[nCntRound].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound - ROUND_X, g_aRound[nCntRound].pos.y + ROUND_Y, g_aRound[nCntRound].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound + ROUND_X, g_aRound[nCntRound].pos.y + ROUND_Y, g_aRound[nCntRound].pos.z);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2((aNumber[nCntRound] * 0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aNumber[nCntRound] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aNumber[nCntRound] * 0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aNumber[nCntRound] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRound->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitRound(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRound != NULL)
	{
		g_pTextureRound->Release();
		g_pTextureRound = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRound != NULL)
	{
		g_pVtxBuffRound->Release();
		g_pVtxBuffRound = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateRound(void)
{
	VERTEX_2D	*pVtx;		//���_���ւ̃|�C���^
	int			nHeith = 0;	//����

							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRound->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRound = 0; nCntRound < MAX_ROUNDDIGIT; nCntRound++, nHeith + 10.0f)
	{
		g_aRound[nCntRound].pos = D3DXVECTOR3(60 + ROUND_X, SCREEN_HEIGHT - (ROUND_Y / 1.0f), 0.0f);

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound - ROUND_X, g_aRound[nCntRound].pos.y - ROUND_Y, g_aRound[nCntRound].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound + ROUND_X, g_aRound[nCntRound].pos.y - ROUND_Y, g_aRound[nCntRound].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound - ROUND_X, g_aRound[nCntRound].pos.y + ROUND_Y, g_aRound[nCntRound].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound + ROUND_X, g_aRound[nCntRound].pos.y + ROUND_Y, g_aRound[nCntRound].pos.z);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRound->Unlock();
}

//---------------------------
//�`�揈��
//---------------------------
void DrawRound(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();		//�f�o�C�X���擾����

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffRound,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//���_�t�H�[�}�b�g�̐ݒ�

	for (int nCntGun = 0; nCntGun < MAX_ROUNDDIGIT; nCntGun++)
	{
		pDevice->SetTexture(0, g_pTextureRound);		//�e�N�X�`���̐ݒ�

		//�|���S���̕`��
		pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
								nCntGun * 4,
								2);
	}
}

//---------------------------
//�c�i���v�Z
//---------------------------
void AddRound(int nShoot)
{
	VERTEX_2D	*pVtx;						//���_���ւ̃|�C���^
	int			aNumber[MAX_ROUNDDIGIT];	//�X�R�A�v�Z

	//�X�R�A���Z
	g_nCntRound += nShoot;

	//�X�R�A�v�Z
	aNumber[0] = g_nCntRound % 100 / 10;
	aNumber[1] = g_nCntRound % 10 / 1;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRound->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGun = 0; nCntGun < MAX_ROUNDDIGIT; nCntGun++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRound->Unlock();
}

//---------------------------
//���̃��^�[��
//---------------------------
int GetRound(void)
{
	return g_nCntRound;
}