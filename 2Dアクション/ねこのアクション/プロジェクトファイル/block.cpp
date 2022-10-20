//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "block.h"
#include "player.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureBlock[MAX_BLOCK_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;					//���_�o�b�t�@�ւ̃|�C���^
BLOCK					g_block[MAX_BLOCK];						//�u���b�N�̍\����

//---------------------------
//����������
//---------------------------
HRESULT InitBlock(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D			*pVtx;		//���_���ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	//�u���b�N�̐����[�v
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_block[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�u���b�N�̈ʒu
		g_block[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�u���b�N�̈ړ���
		g_block[nCntBlock].fWidth = 0.0f;						//�u���b�N�̉���
		g_block[nCntBlock].fHeight = 0.0f;						//�u���b�N�̏c��
		g_block[nCntBlock].nType = 0;							//�u���b�N�̎��
		g_block[nCntBlock].bUse = false;						//�u���b�N�̏��
		g_block[nCntBlock].bPuse = false;						//�����Ԃ����

	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/marble00.jpeg",	//�e�N�X�`��
								&g_pTextureBlock[0]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/marble01.jpg",	//�e�N�X�`��
								&g_pTextureBlock[1]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/marble02.jpg",		//�e�N�X�`��
								&g_pTextureBlock[2]);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffBlock,
									NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//�u���b�N�̐����[�v
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

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
	g_pVtxBuffBlock->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitBlock(void)
{
	//�e�N�X�`���̐����[�v
	for ( int nCntBlock = 0; nCntBlock < MAX_BLOCK_TEX; nCntBlock++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBlock[nCntBlock] != NULL)
		{
			g_pTextureBlock[nCntBlock]->Release();
			g_pTextureBlock[nCntBlock] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateBlock(void)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	PLAYER    *pPlayer;	//�v���C���[�\���̂ւ̃|�C���^

	pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//�u���b�N�̐����[�v
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//�g���Ă���
		if (g_block[nCntBlock].bUse == true)
		{
			if (g_block[nCntBlock].nType == 0)
			{
				
			}
			if (g_block[nCntBlock].nType == 1)
			{
				if (GetMode() == MODE_HOME)
				{
					//���_���W�̍X�V
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//�ړ��ʂ�+
					g_block[nCntBlock].pos += g_block[nCntBlock].move;

					//�����̍����ɂȂ�����
					if (g_block[nCntBlock].pos.y <= SCREEN_HEIGHT / 2)
					{
						g_block[nCntBlock].move *= -1;	//���]
					}
					//���ɗ�����
					else if (g_block[nCntBlock].pos.y >= SCREEN_HEIGHT - BLOCK_Y_SIZE * 3 + 2.0f)
					{
						g_block[nCntBlock].move *= -1;	//���]
					}
				}
				else if (GetMode() == MODE_ES_STAGE01)
				{
					//���_���W�̍X�V
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//�ړ��ʂ�+
					g_block[nCntBlock].pos += g_block[nCntBlock].move;

					//�����̍����ɂȂ�����
					if (g_block[nCntBlock].pos.y <= 250)
					{
						g_block[nCntBlock].move *= -1;							//���]
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
					}
					//���ɗ�����
					else if (g_block[nCntBlock].pos.y >= SCREEN_HEIGHT - BLOCK_Y_SIZE * 3.5)
					{
						g_block[nCntBlock].move *= -1;							//���]
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
					}
				}
				else if (GetMode() == MODE_ES_STAGE02)
				{
					//���_���W�̍X�V
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//�ړ��ʂ�+
					g_block[nCntBlock].pos += g_block[nCntBlock].move;

					//�����̍����ɂȂ�����
					if (g_block[nCntBlock].pos.y <= 250)
					{
						g_block[nCntBlock].move *= -1;							//���]
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
					}
					//���ɗ�����
					else if (g_block[nCntBlock].pos.y >= SCREEN_HEIGHT)
					{
						g_block[nCntBlock].move *= -1;							//���]
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
					}
				}
				else if (GetMode() == MODE_ES_STAGE03)
				{
					//���_���W�̍X�V
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//�ړ��ʂ�+
					g_block[nCntBlock].pos += g_block[nCntBlock].move;

					//�����̍����ɂȂ�����
					if (g_block[nCntBlock].pos.y <= 120)
					{
						g_block[nCntBlock].move *= -1;							//���]
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
					}
					//���ɗ�����
					else if (g_block[nCntBlock].pos.y >= SCREEN_HEIGHT - 150.0f)
					{
						g_block[nCntBlock].move *= -1;							//���]
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
					}
				}
				else if (GetMode() == MODE_NO_STAGE01)
				{
					//���_���W�̍X�V
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					if (g_block[nCntBlock].move.x >= 0.0f && g_block[nCntBlock].move.y == 0.0f ||
						g_block[nCntBlock].move.x <= 0.0f && g_block[nCntBlock].move.y == 0.0f)
					{
						//�ړ�
						g_block[nCntBlock].pos.x += g_block[nCntBlock].move.x;

						//�����̍����ɂȂ�����
						if (g_block[nCntBlock].pos.x <= 350)
						{
							g_block[nCntBlock].move.x *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
						//���ɗ�����
						else if (g_block[nCntBlock].pos.x >= SCREEN_WIDTH / 2)
						{
							g_block[nCntBlock].move.x *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
					}
					else if (g_block[nCntBlock].move.y <= 0.0f && g_block[nCntBlock].move.x == 0.0f ||
							 g_block[nCntBlock].move.y >= 0.0f && g_block[nCntBlock].move.x == 0.0f)
					{
						//�ړ�
						g_block[nCntBlock].pos.y += g_block[nCntBlock].move.y;
						//�����̍����ɂȂ�����
						if (g_block[nCntBlock].pos.y <= 180)
						{
							g_block[nCntBlock].move.y *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
						//���ɗ�����
						else if (g_block[nCntBlock].pos.y >= SCREEN_HEIGHT - 50.0f)
						{
							g_block[nCntBlock].move.y *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
					}
				}
				else if (GetMode() == MODE_NO_STAGE02)
				{
					//���_���W�̍X�V
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//�ړ�
					g_block[nCntBlock].pos += g_block[nCntBlock].move;

					//�����̍����ɂȂ�����
					if (g_block[nCntBlock].pos.x >= SCREEN_WIDTH - 280.0f)
					{
						g_block[nCntBlock].move.x *= -1;							//���]
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
					}
					else if (g_block[nCntBlock].pos.x <= 330.0f)
					{
						g_block[nCntBlock].move.x *= -1;							//���]
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
					}
				}
				else if (GetMode() == MODE_NO_STAGE03)
				{
					//���_���W�̍X�V
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					if (g_block[nCntBlock].move.x >= 0.0f && g_block[nCntBlock].move.y == 0.0f ||
						g_block[nCntBlock].move.x <= 0.0f && g_block[nCntBlock].move.y == 0.0f)
					{
						//�ړ�
						g_block[nCntBlock].pos.x += g_block[nCntBlock].move.x;

						//�����̍����ɂȂ�����
						if (g_block[nCntBlock].pos.x <= 350)
						{
							g_block[nCntBlock].move.x *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
						//���ɗ�����
						else if (g_block[nCntBlock].pos.x >= SCREEN_WIDTH / 2)
						{
							g_block[nCntBlock].move.x *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
					}
					else if (g_block[nCntBlock].move.y <= 0.0f && g_block[nCntBlock].move.x == 0.0f ||
						g_block[nCntBlock].move.y >= 0.0f && g_block[nCntBlock].move.x == 0.0f)
					{
						//�ړ�
						g_block[nCntBlock].pos.y += g_block[nCntBlock].move.y;
						//�����̍����ɂȂ�����
						if (g_block[nCntBlock].pos.y <= 180)
						{
							g_block[nCntBlock].move.y *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
						//���ɗ�����
						else if (g_block[nCntBlock].pos.y >= SCREEN_HEIGHT - 50.0f)
						{
							g_block[nCntBlock].move.y *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
					}
				}
				else if (GetMode() == MODE_NO_STAGE04)
				{
					//���_���W�̍X�V
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//�ړ�
					g_block[nCntBlock].pos.x += g_block[nCntBlock].move.x;

					//�����̍����ɂȂ�����
					if (g_block[nCntBlock].pos.x >= SCREEN_WIDTH - 600.0f)
					{
						g_block[nCntBlock].move.x *= -1;							//���]
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
					}
					else if (g_block[nCntBlock].pos.x <= 150.0f)
					{
						g_block[nCntBlock].move.x *= -1;							//���]
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
					}
				}
				else if (GetMode() == MODE_HD_STAGE02)
				{
					//���_���W�̍X�V
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					if (g_block[nCntBlock].move.x >= 0.0f && g_block[nCntBlock].move.y == 0.0f ||
						g_block[nCntBlock].move.x <= 0.0f && g_block[nCntBlock].move.y == 0.0f)
					{
						//�ړ�
						g_block[nCntBlock].pos.x += g_block[nCntBlock].move.x;

						//�����̍����ɂȂ�����
						if (g_block[nCntBlock].pos.x <= 650)
						{
							g_block[nCntBlock].move.x *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
						//���ɗ�����
						else if (g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth >= 1080)
						{
							g_block[nCntBlock].move.x *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
					}
					else if (g_block[nCntBlock].move.y <= 0.0f && g_block[nCntBlock].move.x == 0.0f ||
						g_block[nCntBlock].move.y >= 0.0f && g_block[nCntBlock].move.x == 0.0f)
					{
						//�ړ�
						g_block[nCntBlock].pos.y += g_block[nCntBlock].move.y;
						//�����̍����ɂȂ�����
						if (g_block[nCntBlock].pos.y <= 100.0f)
						{
							g_block[nCntBlock].move.y *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
						//���ɗ�����
						else if (g_block[nCntBlock].pos.y >= 670)
						{
							g_block[nCntBlock].move.y *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
					}
				}
				else if (GetMode() == MODE_HD_STAGE03)
				{
					//���_���W�̍X�V
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					if (g_block[nCntBlock].move.x >= 0.0f && g_block[nCntBlock].move.y == 0.0f ||
						g_block[nCntBlock].move.x <= 0.0f && g_block[nCntBlock].move.y == 0.0f)
					{
						//�ړ�
						g_block[nCntBlock].pos.x += g_block[nCntBlock].move.x;

						//�����̍����ɂȂ�����
						if (g_block[nCntBlock].pos.x <= 250)
						{
							g_block[nCntBlock].move.x *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
						//���ɗ�����
						else if (g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth >= 1080)
						{
							g_block[nCntBlock].move.x *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
					}
					else if (g_block[nCntBlock].move.y <= 0.0f && g_block[nCntBlock].move.x == 0.0f ||
						g_block[nCntBlock].move.y >= 0.0f && g_block[nCntBlock].move.x == 0.0f)
					{
						//�ړ�
						g_block[nCntBlock].pos.y += g_block[nCntBlock].move.y;
						//�����̍����ɂȂ�����
						if (g_block[nCntBlock].pos.y <= 150.0f)
						{
							g_block[nCntBlock].move.y *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
						//���ɗ�����
						else if (g_block[nCntBlock].pos.y >= 650)
						{
							g_block[nCntBlock].move.y *= -1;							//���]
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
						}
					}
				}
				else if (GetMode() == MODE_HD_STAGE04)
				{
					//���_���W�̍X�V
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//�ړ�
					g_block[nCntBlock].pos.y += g_block[nCntBlock].move.y;

					//�����̍����ɂȂ�����
					if (g_block[nCntBlock].pos.y >= SCREEN_HEIGHT - 100.0f)
					{
						g_block[nCntBlock].move.y *= -1;							//���]
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
					}
					else if (g_block[nCntBlock].pos.y <= 300.0f)
					{
						g_block[nCntBlock].move.y *= -1;							//���]
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
					}
				}
				else if (GetMode() == MODE_HD_STAGE05)
				{
					//���_���W�̍X�V
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//�ړ�
					g_block[nCntBlock].pos.y += g_block[nCntBlock].move.y;

					//�����̍����ɂȂ�����
					if (g_block[nCntBlock].pos.y >= (SCREEN_HEIGHT - 10.0f) - 100.0f)
					{
						g_block[nCntBlock].move.y *= -1;							//���]
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
					}
					else if (g_block[nCntBlock].pos.y <= 200.0f)
					{
						g_block[nCntBlock].move.y *= -1;							//���]
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//���݂̈ړ��ʂ�ۑ�
					}
				}
			}
			if (g_block[nCntBlock].nType == 2)
			{
				//���_���W�̍X�V
				pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//---------------------------
//�`�揈��
//---------------------------
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X���擾����

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(	0,
								g_pVtxBuffBlock,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//���_�t�H�[�}�b�g�̐ݒ�

	//�u���b�N�̐����[�v
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//�g���Ă���
		if (g_block[nCntBlock].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureBlock[g_block[nCntBlock].nType]);		//�e�N�X�`���̐ݒ�
			//�|���S���̕`��
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
									nCntBlock * 4,
									2);
		}
	}
}

//---------------------------
//�u���b�N�̃Z�b�g
//---------------------------

void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, float fTexwidth, float fTexheight, int nType)
{
	VERTEX_2D *pVtx; //���_���ւ̃|�C���^
	
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//�u���b�N�̐����[�v
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//�g���ĂȂ�������
		if (g_block[nCntBlock].bUse == false)
		{
			g_block[nCntBlock].pos = pos;				//�����Ă����ʒu����
			g_block[nCntBlock].move = move;				//�����Ă����ړ��ʂ���
			g_block[nCntBlock].fWidth = fWidth;			//�����Ă�����������
			g_block[nCntBlock].fHeight = fHeight;		//�����Ă����c������
			g_block[nCntBlock].nType = nType;			//�����Ă�����ނ���
			g_block[nCntBlock].fTexwidth = fTexwidth;	//�����Ă����e�N�X�`���̉�������
			g_block[nCntBlock].fTexheigth = fTexheight;	//�����Ă����e�N�X�`���̏c������

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//�u���b�N�^�C�v��2��������2
			if (g_block[nCntBlock].nType == 2)
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
			}
			//����ȊO
			else
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}

			pVtx[0].tex = D3DXVECTOR2(0.0f							, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_block[nCntBlock].fTexwidth	, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f							, g_block[nCntBlock].fTexheigth);
			pVtx[3].tex = D3DXVECTOR2(g_block[nCntBlock].fTexwidth	, g_block[nCntBlock].fTexheigth);

			g_block[nCntBlock].bUse = true;	//�g���Ă���
			break;
		}
		pVtx += 4;	//���_��i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//---------------------------
//�u���b�N�Ƃ̓����蔻��
//---------------------------

bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove, float fWidth, float fHeight, int nType)
{
	BLOCK *pBlock;			//�u���b�N�ւ̃|�C���^
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
	bool bLand = false;		//�n�ʂɂ��Ă邩
	pBlock = &g_block[0];	//�u���b�N�̏����擾

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//�u���b�N�̐������[�v
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		//�g���Ă���
		if (pBlock->bUse == true)
		{
			if (pBlock->nType == 2 && pBlock->bPuse == false)
			{
				//�u���b�N�̉��͈͓̔�
				if (pPos->x + fWidth / 2 >= pBlock->pos.x &&
					pPos->x - fWidth / 2 <= pBlock->pos.x + pBlock->fWidth)
				{
					if (pPosold->y - fHeight >= pBlock->pos.y + pBlock->fHeight &&
						pPos->y - fHeight <= pBlock->pos.y + pBlock->fHeight)
					{
						pMove->y = 0.0f;										//�d�͂�0��
						pPos->y = pBlock->pos.y + pBlock->fHeight + fHeight;	//�u���b�N�O�ɖ߂�
						if (nType == 0)
						{
							pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
							pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
							pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
							pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

							pBlock->bPuse = true;
						}
					}
				}
			}
			else if(pBlock->nType != 2 || pBlock->bPuse == true)
			{
				//�u���b�N�̉��͈͓̔�
				if (pPos->x + fWidth / 2 >= pBlock->pos.x &&
					pPos->x - fWidth / 2 <= pBlock->pos.x + pBlock->fWidth)
				{
					//�u���b�N�ɏォ��߂荞��ł���
					if (pPosold->y <= pBlock->pos.y &&
						pPos->y >= pBlock->pos.y)
					{
						//�^�C�v4��������
						if (nType == 4)
						{
							bLand = true;
							if (GetMode() == MODE_NO_STAGE04)
							{
								pMove->y *= -1;		//���]
								pMove->x = 0.0f;
							}
							else if (GetMode() == MODE_HD_STAGE05)
							{
								pMove->y *= -1;
							}
							else if (GetMode() == MODE_ES_STAGE03)
							{
								pMove->y *= -1;		//���]
							}
						}
						else if (nType == 3)
						{
							bLand = true;
						}
						else
						{
							pMove->y = 0.0f;				//�d�͂�0��
							pPos->y = pBlock->pos.y;		//�u���b�N�O�ɖ߂�
							pPos->y += pBlock->move.y;		//�ړ���+
							pPos->x += pBlock->move.x;		//�ړ���+
							bLand = true;					//�n�ʂɂ��Ă�
						}
						//�����痎������
						if (pPosold->x - fWidth / 2 >= pBlock->pos.x &&
							pPos->x - fWidth / 2 <= pBlock->pos.x)
						{
							//�^�C�v0��������
							if (nType == 0)
							{
								bLand = false;			//�n�ʂɂ��ĂȂ�
							}
							//�^�C�v1��������
							if (nType == 2)
							{
								
							}
						}
						//�E���痎������
						else if (pPosold->x + fWidth / 2 <= pBlock->pos.x + pBlock->fWidth &&
							pPos->x + fWidth / 2 >= pBlock->pos.x + pBlock->fWidth)
						{
							//�^�C�v0��������
							if (nType == 0)
							{
								bLand = false;			//�n�ʂɂ��ĂȂ�
							}
							//�^�C�v1��������
							if (nType == 2)
							{
								
							}
						}
					}
					//�u���b�N�ɓ����Ԃ�������
					else if (pPosold->y - fHeight >= pBlock->pos.y + pBlock->fHeight &&
							pPos->y - fHeight <= pBlock->pos.y + pBlock->fHeight)
					{
						//�^�C�v0��������
						if (nType == 0)
						{
							bLand = false;			//�n�ʂɂ��ĂȂ�
						}
						//�^�C�v4��������
						if (nType == 4)
						{
							bLand = true;
							if (GetMode() == MODE_NO_STAGE04)
							{
								pMove->y *= -1;		//���]
								pMove->x = 2.0f;
							}
							else if (GetMode() == MODE_HD_STAGE05)
							{
								pMove->y *= -1;
							}
							else if (GetMode() == MODE_ES_STAGE03)
							{
								pMove->y *= -1;		//���]
							}
						}
						//�^�C�v3��������
						else if (nType == 3)
						{
							bLand = true;		//���ׂɂԂ����Ă�
						}
						else
						{
							pMove->y = 0.0f;										//�d�͂�0��
							pPos->y = pBlock->pos.y + pBlock->fHeight + fHeight;	//�u���b�N�O�ɖ߂�
						}
					}
				}
				//�u���b�N�̏c�͈͓̔���������
				if (pPos->y - fHeight <= pBlock->pos.y + pBlock->fHeight&&
					pPos->y >= pBlock->pos.y)
				{
					//�E����߂荞��ł���
					if (pPosold->x + fWidth / 2 <= pBlock->pos.x &&
						pPos->x + fWidth / 2 >= pBlock->pos.x)
					{
						//�u���b�N�O�ɖ߂�
						pPos->x = pBlock->pos.x - fWidth / 2;
						//�^�C�v0��������
						if (nType == 0)
						{
							bLand = false;		//�n�ʂɂ��ĂȂ�
						}
						//�^�C�v1��������
						if (nType == 1)
						{
							pMove->x *= -1;		//���]
						}
						//�^�C�v2��������
						if (nType == 2)
						{
							pMove->x *= -1;		//���]
						}
						//�^�C�v3��������
						if (nType == 3)
						{
							bLand = true;		//���ׂɂԂ����Ă�
						}
						//�^�C�v4
						if (nType == 4)
						{
							bLand = true;
							if (GetMode() == MODE_HD_STAGE05)
							{
								pMove->x *= -1;
							}
							else
							{
								pMove->x *= -1;		//���]
							}
						}
					}
					//������߂荞��ł���
					else if (pPosold->x - fWidth / 2 >= pBlock->pos.x + pBlock->fWidth &&
						pPos->x - fWidth / 2 <= pBlock->pos.x + pBlock->fWidth)
					{
						//�u���b�N�O�ɖ߂�
						pPos->x = pBlock->pos.x + pBlock->fWidth + fWidth / 2;
						//�^�C�v0��������
						if (nType == 0)
						{
							bLand = false;		//�n�ʂɂ��ĂȂ�
						}
						//�^�C�v1��������
						if (nType == 1)
						{
							pMove->x *= -1;		//���]
						}
						//�^�C�v2��������
						if (nType == 2)
						{
							pMove->x *= -1;		//���]
						}
						//�^�C�v3��������
						if (nType == 3)
						{
							bLand = true;		//���ׂɂԂ����Ă�
						}
					}
				}
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();

	return bLand;	//�u���b�N�ɒ��n���Ă邩��Ԃ�
}
//---------------------------
//�u���b�N�̏�Ԃ����
//---------------------------

BLOCK *GetBlock(void)
{
	return &g_block[0];
}
