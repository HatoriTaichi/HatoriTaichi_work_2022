//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "life.h"
#include "fade.h"
#include "sound.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_apTextureLife = NULL;		//�e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LIFE					g_aLife;					//�̗͂̍\����
int						g_nLife;					//�̗�

//---------------------------
//����������
//---------------------------
HRESULT InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_aLife.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_nLife = MAX_LIFE;	//�̗͂̍ő吔
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/life.png",
								&g_apTextureLife);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffLife,
									NULL);
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_aLife.pos.x - LIFE_X, g_aLife.pos.y - LIFE_Y, g_aLife.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_aLife.pos.x + LIFE_X, g_aLife.pos.y - LIFE_Y, g_aLife.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_aLife.pos.x - LIFE_X, g_aLife.pos.y + LIFE_Y, g_aLife.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_aLife.pos.x + LIFE_X, g_aLife.pos.y + LIFE_Y, g_aLife.pos.z);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
	pVtx[1].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
	pVtx[2].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
	pVtx[3].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.1f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.1f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitLife(void)
{
	g_nLife = MAX_LIFE;	//�̗͂̍ő吔
	//�e�N�X�`���̔j��
	if (g_apTextureLife != NULL)
	{
		g_apTextureLife->Release();
		g_apTextureLife = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateLife(void)
{
	VERTEX_2D	 *pVtx;
	int			 nCntLife;

	//�ő傢���傤�ɂȂ�����	
	if (g_nLife >= MAX_LIFE)
	{
		//�ő�ɍ��킹��
		g_nLife = MAX_LIFE;
	}

	g_aLife.pos = D3DXVECTOR3(0.0f + LIFE_X, 0.0f + LIFE_Y, 0.0f);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_aLife.pos.x - LIFE_X, g_aLife.pos.y - LIFE_Y, g_aLife.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_aLife.pos.x + LIFE_X, g_aLife.pos.y - LIFE_Y, g_aLife.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_aLife.pos.x - LIFE_X, g_aLife.pos.y + LIFE_Y, g_aLife.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_aLife.pos.x + LIFE_X, g_aLife.pos.y + LIFE_Y, g_aLife.pos.z);

	//�̗͂���ꂽ��
	if (g_nLife <= MAX_LIFE)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.1f * g_nLife - 0.1);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.1f * g_nLife - 0.1);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.1f * g_nLife);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.1f * g_nLife);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();

	//�̗͂��Ȃ��Ȃ�����
	if (g_nLife <= 0 && GetFade() == FADE_NONE)
	{
		g_nLife = 0;
		SetFade(MODE_GAMEOVER);
		if (GetMode() == MODE_ES_STAGE03 || GetMode() == MODE_NO_STAGE04 || GetMode() == MODE_HD_STAGE05)
		{
			StopSound(SOUND_LABEL_BGM004);
		}
		else if (GetMode() != MODE_ES_STAGE03 || GetMode() != MODE_NO_STAGE04 || GetMode() != MODE_HD_STAGE05)
		{
			StopSound(SOUND_LABEL_BGM001);
		}
	}
}

//---------------------------
//�`�揈��
//---------------------------
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X���擾����

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffLife,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D); //���_�t�H�[�}�b�g�̐ݒ�
	//�e�N�X�`��
	pDevice->SetTexture(0, g_apTextureLife);
	//�|���S���̕`��
	pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
							0,
							2);
}

//---------------------------
//�̗͌v�Z
//---------------------------
void AddLife(int nMinus)
{
	g_nLife += nMinus;
}