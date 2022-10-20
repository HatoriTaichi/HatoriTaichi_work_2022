//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "bg.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureBg[MAX_BG_TEX] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;				//���_�o�b�t�@�ւ̃|�C���^
BG						g_bg[MAX_BG];						//BG�̍\����
static float			g_fCol = 255.0f;					//�_��

//---------------------------
//����������
//---------------------------
HRESULT InitBg(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D			*pVtx;		//���_���ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		g_bg[nCntBg].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
		g_bg[nCntBg].nType = 0;			//���
		g_bg[nCntBg].bUse = false;		//�g���Ă邩�ǂ���
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,	
								"data/Texture/bg.00.png",				//�e�N�X�`��
								&g_pTextureBg[0]);	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/worter.jpg",				//�e�N�X�`��
								&g_pTextureBg[1]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/title.png",				//�e�N�X�`��
								&g_pTextureBg[2]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/description.png",			//�e�N�X�`��
								&g_pTextureBg[3]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/result.png",				//�e�N�X�`��
								&g_pTextureBg[4]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/push to neter 00.png",	//�e�N�X�`��
								&g_pTextureBg[5]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/gameover.png",			//�e�N�X�`��
								&g_pTextureBg[6]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/1st.png",					//�e�N�X�`��
								&g_pTextureBg[7]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/2nd.png",					//�e�N�X�`��
								&g_pTextureBg[8]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/3rd.png",					//�e�N�X�`��
								&g_pTextureBg[9]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/you.png",					//�e�N�X�`��
								&g_pTextureBg[10]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/cat01.png",				//�e�N�X�`��
								&g_pTextureBg[11]);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_BG,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffBg,
									NULL);
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitBg(void)
{
	for (int nCnTex = 0; nCnTex < MAX_BG_TEX; nCnTex++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBg[nCnTex] != NULL)
		{
			g_pTextureBg[nCnTex]->Release();
			g_pTextureBg[nCnTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateBg(void)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	static int nCnt;

	nCnt++;
	//��b��������
	if (nCnt >= 144)
	{
		//�����x0
		if (g_fCol == 0.0f)
		{
			//�����x255
			g_fCol = 255.0f;
		}
		//�����x255
		else if (g_fCol == 255.0f)
		{
			//�����x0
			g_fCol = 0.0f;
		}
		nCnt = 0;
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntP = 0; nCntP < MAX_BG; nCntP++)
	{
		if (g_bg[nCntP].bUse == true)
		{
			if (g_bg[nCntP].nType == 5)
			{
				pVtx[0].col = D3DXCOLOR(255, 255, 255, g_fCol);
				pVtx[1].col = D3DXCOLOR(255, 255, 255, g_fCol);
				pVtx[2].col = D3DXCOLOR(255, 255, 255, g_fCol);
				pVtx[3].col = D3DXCOLOR(255, 255, 255, g_fCol);
			}
		}
		pVtx += 4;	//���_��i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg->Unlock();
}

//---------------------------
//�`�揈��
//---------------------------
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();		//�f�o�C�X���擾����
								//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffBg,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//���_�t�H�[�}�b�g�̐ݒ�

	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		if (g_bg[nCntBg].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureBg[g_bg[nCntBg].nType]);		//�e�N�X�`���̐ݒ�
			//�|���S���̕`��
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
									nCntBg * 4,
									2);
		}
	}
}

//---------------------------
//BG�̃Z�b�g
//---------------------------
void SetBg(D3DXVECTOR3 pos, float fWigth, float fHeight, int nType)
{
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		if (g_bg[nCntBg].bUse == false)
		{
			g_bg[nCntBg].pos = pos;				//�����Ă����ʒu����
			g_bg[nCntBg].fWidth = fWigth;		//�����Ă�����
			g_bg[nCntBg].fHeight = fHeight;		//�����Ă�������
			g_bg[nCntBg].nType = nType;			//�����Ă������

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_bg[nCntBg].pos.x, g_bg[nCntBg].pos.y, g_bg[nCntBg].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_bg[nCntBg].pos.x + g_bg[nCntBg].fWidth, g_bg[nCntBg].pos.y, g_bg[nCntBg].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_bg[nCntBg].pos.x, g_bg[nCntBg].pos.y + g_bg[nCntBg].fHeight, g_bg[nCntBg].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_bg[nCntBg].pos.x + g_bg[nCntBg].fWidth, g_bg[nCntBg].pos.y + g_bg[nCntBg].fHeight, g_bg[nCntBg].pos.z);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			if (nType == 1)
			{
				//�C�[�W�[
				if (GetMode() == MODE_ES_STAGE01 || GetMode() == MODE_ES_STAGE02 || GetMode() == MODE_ES_STAGE03)
				{
					pVtx[0].col = D3DXCOLOR(200, 200, 200, 255);
					pVtx[1].col = D3DXCOLOR(200, 200, 200, 255);
					pVtx[2].col = D3DXCOLOR(200, 200, 200, 255);
					pVtx[3].col = D3DXCOLOR(200, 200, 200, 255);
				}
				//�m�[�}��
				else if (GetMode() == MODE_NO_STAGE01 || GetMode() == MODE_NO_STAGE02 || GetMode() == MODE_NO_STAGE03 || GetMode() == MODE_NO_STAGE04)
				{
					pVtx[0].col = D3DXCOLOR(255, 200, 200, 255);
					pVtx[1].col = D3DXCOLOR(255, 200, 200, 255);
					pVtx[2].col = D3DXCOLOR(255, 200, 200, 255);
					pVtx[3].col = D3DXCOLOR(255, 200, 200, 255);
				}
				//�n�[�h
				else if (GetMode() == MODE_HD_STAGE01 || GetMode() == MODE_HD_STAGE02 || GetMode() == MODE_HD_STAGE03 || GetMode() == MODE_HD_STAGE04 || GetMode() == MODE_HD_STAGE05)
				{
					pVtx[0].col = D3DXCOLOR(255, 100, 100, 255);
					pVtx[1].col = D3DXCOLOR(255, 100, 100, 255);
					pVtx[2].col = D3DXCOLOR(255, 100, 100, 255);
					pVtx[3].col = D3DXCOLOR(255, 100, 100, 255);
				}
			}
			//����ȊO
			else
			{
				pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
				pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
				pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
				pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);
			}

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_bg[nCntBg].bUse = true;
			break;
		}
		pVtx += 4;	//���_��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg->Unlock();
}