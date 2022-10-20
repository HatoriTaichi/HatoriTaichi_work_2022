//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "worldsky.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureSky[MAX_SKY_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSky = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffSky = NULL;				//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Sky					g_Sky[MAX_SKY];					//���b�V���t�B�[���h�̍\����

//---------------------------
//����������
//---------------------------
HRESULT InitSky(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̎擾

	for (int nCntSky = 0; nCntSky < MAX_SKY; nCntSky++)
	{
		g_Sky[nCntSky].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Sky[nCntSky].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Sky[nCntSky].fWidth = 0.5f;
		g_Sky[nCntSky].fDepht = 0.5f;
		g_Sky[nCntSky].nTex = 0;
		g_Sky[nCntSky].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/sky_00.jpg",			//�e�N�X�`��
								&g_pTextureSky[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * SKY_VTX_NUM_MAX * MAX_SKY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffSky,
									NULL);
	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(	sizeof(WORD) * SKY_IDX_NUM_MAX * MAX_SKY,
								D3DUSAGE_WRITEONLY,
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED,
								&g_pIdxBuffSky,
								NULL);
	//---------------------------
	//���_���
	//---------------------------
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSky->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntField = 0; nCntField < MAX_SKY; nCntField++)
	{
		int nVtxNum = 0;
		for (int nCntY = 0; nCntY < SKY_MAX_VTX_Y + 1; nCntY++)
		{
			for (int nCntX = 0; nCntX < SKY_MAX_VTX_X + 1; nCntX++, nVtxNum++)
			{
				pVtx[nVtxNum].pos = D3DXVECTOR3(cosf(D3DX_PI * 2 / SKY_MAX_VTX_X * nCntX) * sinf(D3DX_PI * 2 / SKY_MAX_VTX_X * nCntY + (D3DX_PI / 2)) * SKY_X,
												sinf(D3DX_PI * 2 / SKY_MAX_VTX_X * nCntY) * SKY_X,
												sinf(D3DX_PI * 2 / SKY_MAX_VTX_X * nCntX) * sinf(D3DX_PI * 2 / SKY_MAX_VTX_X * nCntY + (D3DX_PI / 2)) * SKY_X);
				pVtx[nVtxNum].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
				pVtx[nVtxNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[nVtxNum].tex = D3DXVECTOR2((1.0f / SKY_MAX_VTX_X) * nCntX, (1.0f / SKY_MAX_VTX_Y) * nCntY);
			}
		}
		nVtxNum = 0;
		pVtx += SKY_VTX_NUM_MAX;	//���_��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSky->Unlock();

	//---------------------------
	//�C���f�b�N�X���
	//---------------------------
	WORD *pIdx;		//�C���f�b�N�X���ւ̃|�C���^

					//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffSky->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntField = 0; nCntField < MAX_SKY; nCntField++)
	{
		//�p�킳��ȊO�̒��_
		for (int nCntZ = 0; nCntZ < SKY_MAX_VTX_Y; nCntZ++)
		{
			for (int nCntX = 0; nCntX < SKY_MAX_VTX_X + 1; nCntX++)
			{
				pIdx[(nCntX * 2) + 0 + ((SKY_MAX_VTX_X + 2) * 2) * nCntZ] = ((SKY_MAX_VTX_X + 1) + nCntX) + ((SKY_MAX_VTX_X + 1) * nCntZ);
				pIdx[(nCntX * 2) + 1 + ((SKY_MAX_VTX_X + 2) * 2) * nCntZ] = (0 + nCntX) + ((SKY_MAX_VTX_X + 1) * nCntZ);
			}
		}
		//�p�킳��̒��_
		for (int nCntZ = 0; nCntZ < SKY_MAX_VTX_Y - 1; nCntZ++)
		{
			pIdx[(((SKY_MAX_VTX_X + 1) * 2 + 0) * (nCntZ + 1)) + (2 * nCntZ)] = SKY_MAX_VTX_X + ((SKY_MAX_VTX_X + 1) * nCntZ);
			pIdx[(((SKY_MAX_VTX_X + 1) * 2 + 1) * (nCntZ + 1)) + (1 * nCntZ)] = (SKY_MAX_VTX_X * 2 + 2) + ((SKY_MAX_VTX_X + 1) * nCntZ);
		}
		pIdx += SKY_IDX_NUM_MAX;	//�C���f�b�N�X��i�߂�
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffSky->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitSky(void)
{
	//---------------------------
	//�e�N�X�`���j��
	//---------------------------
	for (int nCntTex = 0; nCntTex < MAX_SKY_TEX; nCntTex++)
	{
		if (g_pTextureSky[nCntTex] != NULL)
		{
			g_pTextureSky[nCntTex]->Release();
			g_pTextureSky[nCntTex] = NULL;
		}
	}

	//---------------------------
	//�o�b�t�@�j��
	//---------------------------
	if (g_pVtxBuffSky != NULL)
	{
		g_pVtxBuffSky->Release();
		g_pVtxBuffSky = NULL;
	}

	//---------------------------
	//�C���f�b�N�X�o�b�t�@�j��
	//---------------------------
	if (g_pIdxBuffSky != NULL)
	{
		g_pIdxBuffSky->Release();
		g_pIdxBuffSky = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateSky(void)
{

}

//---------------------------
//�`�揈��
//---------------------------
void DrawSky(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X���擾����

	//---------------------------
	//�}�g���b�N�X�̐ݒ�
	//---------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int nCntSky = 0; nCntSky < MAX_SKY; nCntSky++)
	{
		if (g_Sky[nCntSky].bUse == true)
		{
			//�J�����O�L
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			D3DXMatrixIdentity(&g_Sky[nCntSky].mtxWold);	//�}�g���b�N�X������

			//�X�P�[��
			g_Sky[nCntSky].mtxWold._11 = g_Sky[nCntSky].fWidth;
			g_Sky[nCntSky].mtxWold._33 = g_Sky[nCntSky].fDepht;

			//�����̐ݒ�
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_Sky[nCntSky].rot.y,
											g_Sky[nCntSky].rot.x,
											g_Sky[nCntSky].rot.z);

			D3DXMatrixMultiply(	&g_Sky[nCntSky].mtxWold,
								&g_Sky[nCntSky].mtxWold,
								&mtxRot);
			//�ʒu
			D3DXMatrixTranslation(	&mtxTrans,
									g_Sky[nCntSky].pos.x,
									g_Sky[nCntSky].pos.y,
									g_Sky[nCntSky].pos.z);

			D3DXMatrixMultiply(	&g_Sky[nCntSky].mtxWold,
								&g_Sky[nCntSky].mtxWold,
								&mtxTrans);
			//�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_Sky[nCntSky].mtxWold);
			//---------------------------
			//�`�揈��
			//---------------------------
			//�o�b�t�@�̐ݒ���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(	0,
										g_pVtxBuffSky,
										0,
										sizeof(VERTEX_3D));
			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffSky);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(	0,
									g_pTextureSky[g_Sky[nCntSky].nTex]);
			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
											0,								//�C���f�b�N�X �o�b�t�@�̊J�n�n�_����ŏ��̃C���f�b�N�X�܂ł̃I�t�Z�b�g
											nCntSky * SKY_VTX_NUM_MAX,	//�`��Ŏg�p�����ŏ��̒��_�ԍ�
											SKY_IDX_NUM_MAX,				//���_�̐�
											nCntSky * SKY_IDX_NUM_MAX,	//�C���f�b�N�X�z��̓ǂݎ����J�n����ʒu
											SKY_POLY_NUM_MAX;				//���̐�

			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}
	}
}

//---------------------------
//���̃Z�b�g
//---------------------------
void SetSky(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWidth, float fDepht, int nTex)
{
	for (int nCntSky = 0; nCntSky < MAX_SKY; nCntSky++)
	{
		if (g_Sky[nCntSky].bUse == false)
		{
			g_Sky[nCntSky].pos = pos;			//�ʒu������
			g_Sky[nCntSky].rot = rot;			//����������
			g_Sky[nCntSky].fWidth = fWidth;	//��������
			g_Sky[nCntSky].fDepht = fDepht;	//���s������
			g_Sky[nCntSky].nTex = nTex;		//�e�N�X�`���̎��

			g_Sky[nCntSky].bUse = true;		//�g���Ă�
			break;
		}
	}
}