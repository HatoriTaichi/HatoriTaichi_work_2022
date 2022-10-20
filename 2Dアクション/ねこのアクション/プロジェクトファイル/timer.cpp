//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "timer.h"
#include "fade.h"
#include "score.h"
#include "enemy.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureTimer = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;		//���_�o�b�t�@�ւ̃|�C���^
TIMER					g_timer[MAX_TIMER];			//BG�̍\����
int						g_nTimer;				//�^�C�}�[
int						g_nCntRealT = 0;			//�������ԂɂȂ邽���m�킯��
bool					g_bPulse = true;			//���^�X

//---------------------------
//��������
//---------------------------
HRESULT InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̎擾
	//�^�C�}�[�̏�����
	for (int nCnttimer = 0; nCnttimer < MAX_TIMER; nCnttimer++)
	{
		g_timer[nCnttimer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_timer[nCnttimer].bUse = false;
	}

	g_nTimer = NO_TIMER_SET;

#ifdef _DEBUG
	g_nTimer = DEBUG_MAXTIMER_SET;		//�^�C�}�[
#endif
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/score00.png",
								&g_pTextureTimer);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_TIMER,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffTimer,
									NULL);
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnttimer = 0; nCnttimer < MAX_TIMER; nCnttimer++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer - TIMER_SIZE_X, g_timer[nCnttimer].pos.y - TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer + TIMER_SIZE_X, g_timer[nCnttimer].pos.y - TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer - TIMER_SIZE_X, g_timer[nCnttimer].pos.y + TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer + TIMER_SIZE_X, g_timer[nCnttimer].pos.y + TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitTimer(void)
{
	g_nTimer = 0;
	//�e�N�X�`���̔j��
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateTimer(void)
{
	ENEMY		*pEnemy;
	VERTEX_2D	*pVtx;				//���_���ւ̃|�C���^
	int			nHeith = 0;			//����
	int			aNumber[MAX_TIMER];	//�^�C�}�[�̌���

	pEnemy = GetEnemy();

	g_nCntRealT++;
	if (g_nCntRealT >= 150)
	{
		if (GetMode() != MODE_RESULT || GetMode() == MODE_TITLE)
		{
			//���Ԃ����炷
			g_nTimer += -1;
		}

		//���Ԃ̌v�Z
		aNumber[0] = g_nTimer % 1000 / 100;
		aNumber[1] = g_nTimer % 100 / 10;
		aNumber[2] = g_nTimer % 10 / 1;

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`���ړ�
		for (int nCnttimer = 0; nCnttimer < MAX_TIMER; nCnttimer++, nHeith + 50.0f)
		{
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2((aNumber[nCnttimer] * 0.1f) + 0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((aNumber[nCnttimer] * 0.1f) + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((aNumber[nCnttimer] * 0.1f) + 0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((aNumber[nCnttimer] * 0.1f) + 0.1f, 1.0f);

			pVtx += 4;
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTimer->Unlock();

		g_nCntRealT = 0;
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnttimer = 0; nCnttimer < MAX_TIMER; nCnttimer++, nHeith + 50.0f)
	{
		g_timer[nCnttimer].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - TIMER_SIZE_X * 2, 0.0f + 25.0f, 0.0f);

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer - TIMER_SIZE_X, g_timer[nCnttimer].pos.y - TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer + TIMER_SIZE_X, g_timer[nCnttimer].pos.y - TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer - TIMER_SIZE_X, g_timer[nCnttimer].pos.y + TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer + TIMER_SIZE_X, g_timer[nCnttimer].pos.y + TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();
	//�^�C�}�[��0�ɂȂ�����	
	if (g_nTimer <= 0 && GetFade() == FADE_NONE)
	{
		SetFade(MODE_GAMEOVER);
	}
	for (int inCnt = 0; inCnt < MAX_ENEMY; inCnt++)
	{
		//���U���g���
		if (GetMode() == MODE_ES_STAGE03 && GetMode() == MODE_NO_STAGE04 && GetMode() == MODE_HD_STAGE05 || pEnemy->nLife <= 0)
		{
			//�^�C�}�[���c���Ă���
			if (g_nTimer >= 0 && g_bPulse == true)
			{
				AddScore(g_nTimer);
				g_bPulse = false;
			}
		}
	}
}

//---------------------------
//�`�揈��
//---------------------------
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X���擾����

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffTimer,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D); //���_�t�H�[�}�b�g�̐ݒ�

	for (int nCnttimer = 0; nCnttimer < MAX_TIMER; nCnttimer++)
	{
		//�e�N�X�`��
		pDevice->SetTexture(0, g_pTextureTimer);
		//�|���S���̕`��
		pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
								nCnttimer * 4,
								2);
	}
}