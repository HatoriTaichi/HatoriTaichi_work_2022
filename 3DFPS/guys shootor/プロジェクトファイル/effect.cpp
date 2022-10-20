//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "effect.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureEffect[MAX_EFFECT_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Effect					g_aEffect[MAX_EFFECT];		//�e�̍\����			

//---------------------------
//�O���[�o���ϐ�
//---------------------------
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

									//�l�̏�����
	for (int nCntShadow = 0; nCntShadow < MAX_EFFECT; nCntShadow++)
	{
		g_aEffect[nCntShadow].pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aEffect[nCntShadow].rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aEffect[nCntShadow].fHeiht = 0.0f;
		g_aEffect[nCntShadow].fWhith = EFFECT_X;
		g_aEffect[nCntShadow].fHeiht = EFFECT_Z;
		g_aEffect[nCntShadow].fDepht = EFFECT_Z;
		g_aEffect[nCntShadow].fAlpha = 255.0f;
		g_aEffect[nCntShadow].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/bullet_00.png",			//�e�N�X�`��
								&g_pTextureEffect[EFFECT_TEX_GUN]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/bullet_01.png",			//�e�N�X�`��
								&g_pTextureEffect[EFFECT_TEX_DETH]);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEffect,
									NULL);
	//---------------------------
	//���_���
	//---------------------------
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_EFFECT; nCntShadow++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntShadow].fWhith / 2, g_aEffect[nCntShadow].fHeiht / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntShadow].fWhith / 2, g_aEffect[nCntShadow].fHeiht / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntShadow].fWhith / 2, -g_aEffect[nCntShadow].fHeiht / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntShadow].fWhith / 2, -g_aEffect[nCntShadow].fHeiht / 2, 0.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(255, 255, 255, g_aEffect[nCntShadow].fAlpha);
		pVtx[1].col = D3DXCOLOR(255, 255, 255, g_aEffect[nCntShadow].fAlpha);
		pVtx[2].col = D3DXCOLOR(255, 255, 255, g_aEffect[nCntShadow].fAlpha);
		pVtx[3].col = D3DXCOLOR(255, 255, 255, g_aEffect[nCntShadow].fAlpha);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitEffect(void)
{
	//---------------------------
	//�e�N�X�`���j��
	//---------------------------
	for (int nTex = 0; nTex < MAX_EFFECT_TEX; nTex++)
	{
		if (g_pTextureEffect[nTex] != NULL)
		{
			g_pTextureEffect[nTex]->Release();
			g_pTextureEffect[nTex] = NULL;
		}
	}

	//---------------------------
	//�o�b�t�@�j��
	//---------------------------
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateEffect(void)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			g_aEffect[nCntEffect].nLife--;

			g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;

			if (g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;	
			}
		}
	}
}

//---------------------------
//�`�揈��
//---------------------------
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();					//�f�o�C�X���擾����

	//---------------------------
	//�}�g���b�N�X�̐ݒ�
	//---------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//�J�����O�L
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			//���Z�����֌W
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			// �}�g���b�N�X������
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorld);

			//�J�����̌������擾
			pDevice->GetTransform(	D3DTS_VIEW,
									&g_aEffect[nCntEffect].mtxView);

			//�J�����̏������āA�X�P�[���𔽉f
			g_aEffect[nCntEffect].mtxWorld._11 = g_aEffect[nCntEffect].mtxView._11 * g_aEffect[nCntEffect].fWhith;
			g_aEffect[nCntEffect].mtxWorld._12 = g_aEffect[nCntEffect].mtxView._21 * g_aEffect[nCntEffect].fWhith;
			g_aEffect[nCntEffect].mtxWorld._13 = g_aEffect[nCntEffect].mtxView._31 * g_aEffect[nCntEffect].fWhith;
			g_aEffect[nCntEffect].mtxWorld._21 = g_aEffect[nCntEffect].mtxView._12 * g_aEffect[nCntEffect].fHeiht;
			g_aEffect[nCntEffect].mtxWorld._22 = g_aEffect[nCntEffect].mtxView._22 * g_aEffect[nCntEffect].fHeiht;
			g_aEffect[nCntEffect].mtxWorld._23 = g_aEffect[nCntEffect].mtxView._32 * g_aEffect[nCntEffect].fHeiht;
			g_aEffect[nCntEffect].mtxWorld._31 = g_aEffect[nCntEffect].mtxView._13;
			g_aEffect[nCntEffect].mtxWorld._32 = g_aEffect[nCntEffect].mtxView._23;
			g_aEffect[nCntEffect].mtxWorld._33 = g_aEffect[nCntEffect].mtxView._33;

			//�ʒu
			D3DXMatrixTranslation(	&mtxTrans,
									g_aEffect[nCntEffect].pos.x,
									g_aEffect[nCntEffect].pos.y,
									g_aEffect[nCntEffect].pos.z);

			D3DXMatrixMultiply(	&g_aEffect[nCntEffect].mtxWorld,
								&g_aEffect[nCntEffect].mtxWorld,
								&mtxTrans);
			//�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aEffect[nCntEffect].mtxWorld);

			//---------------------------
			//�`�揈��
			//---------------------------
			//�o�b�t�@�̐ݒ���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(	0,
										g_pVtxBuffEffect,
										0,
										sizeof(VERTEX_3D));
			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(	0,
									g_pTextureEffect[g_aEffect[nCntEffect].aTex]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
									nCntEffect * 4,			//���Ԗڂ���`�悷�邩
									2);						//���̐�

			//�ʏ퍇���ɖ߂�(���Z����)
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}
	}
}

//---------------------------
//�G�t�F�N�g�̐ݒ�
//---------------------------
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWhith, float fHeight, EffectType aType, Effecttextype aTex, int nLife)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;		//�ʒu����
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].fWhith = fWhith;	//������
			g_aEffect[nCntEffect].fHeiht = fHeight;	//��������
			g_aEffect[nCntEffect].aType = aType;	//���
			g_aEffect[nCntEffect].aTex = aTex;		//�e�N�X�`�����
			g_aEffect[nCntEffect].nLife = nLife;	//���ŃJ�E���g

			g_aEffect[nCntEffect].bUse = true;
			break;
		}
	}
}