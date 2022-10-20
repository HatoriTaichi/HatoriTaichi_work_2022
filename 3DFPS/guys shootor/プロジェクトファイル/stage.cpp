//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "stage.h"
#include "shadow.h"
#include "camara.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
LPDIRECT3DTEXTURE9	g_apTextureStage[MAX_STAGE_MODEL][MAX_STAGE_TEX] = {};	//�e�N�X�`���̃|�C���^
Stage				g_aStage[MAX_STAGE_MODEL];	//�����̍\����
int					g_nModel;

//---------------------------
//����������
//---------------------------
HRESULT InitStage(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	for (int nCntStageModel = 0; nCntStageModel < MAX_STAGE_MODEL; nCntStageModel++)
	{
		//�ʒu����������
		g_aStage[nCntStageModel].pos = (D3DXVECTOR3(-500.0f, 0.0f, 0.0f));
		g_aStage[nCntStageModel].rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aStage[nCntStageModel].move = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aStage[nCntStageModel].vtxMaxModel = (D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f));
		g_aStage[nCntStageModel].vtxMinModel = (D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f));
		g_aStage[nCntStageModel].pMesh = {};
		g_aStage[nCntStageModel].pBuffMat = {};
		g_aStage[nCntStageModel].nIdex = 0;
		g_aStage[nCntStageModel].bUse = false;
	}
	g_nModel = 0;

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitStage(void)
{
	for (int nCntStageModel = 0; nCntStageModel < MAX_STAGE_MODEL; nCntStageModel++)
	{
		//---------------------------
		//���b�V���j��
		//---------------------------
		if (g_aStage[nCntStageModel].pMesh != NULL)
		{
			g_aStage[nCntStageModel].pMesh->Release();
			g_aStage[nCntStageModel].pMesh = NULL;
		}

		//---------------------------
		//�}�e���A���j��
		//---------------------------
		if (g_aStage[nCntStageModel].pBuffMat != NULL)
		{
			g_aStage[nCntStageModel].pBuffMat->Release();
			g_aStage[nCntStageModel].pBuffMat = NULL;
		}
	}
}

//---------------------------
//�X�V����
//---------------------------
void UpdateStage(void)
{
	for (int nCntStage = 0; nCntStage < MAX_STAGE_MODEL; nCntStage++)
	{
		if (g_aStage[nCntStage].bUse == true)
		{
			if (g_aStage[nCntStage].aType == STAGE_MOVEFLOO_00)
			{
				g_aStage[nCntStage].pos += g_aStage[nCntStage].move;
				if (g_aStage[nCntStage].pos.z >= 490.0f)
				{
					g_aStage[nCntStage].move *= -1;
				}
				else if (g_aStage[nCntStage].pos.z <= 210.0f)
				{
					g_aStage[nCntStage].move *= -1;
				}
			}
		}
	}
}

//---------------------------
//�`�揈��
//---------------------------
void DrawStage(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();					//�f�o�C�X���擾����

	//---------------------------
	//�}�g���b�N�X�̐ݒ�
	//---------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int nCntStageModel = 0; nCntStageModel < MAX_STAGE_MODEL; nCntStageModel++)
	{
		if (g_aStage[nCntStageModel].bUse == true)
		{
			//�J�����O�L��
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

			D3DXMatrixIdentity(&g_aStage[nCntStageModel].mtxWold);	//�}�g���b�N�X������

			//�����̐ݒ�
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,	
											g_aStage[nCntStageModel].rot.y,
											g_aStage[nCntStageModel].rot.x,
											g_aStage[nCntStageModel].rot.z);

			D3DXMatrixMultiply(	&g_aStage[nCntStageModel].mtxWold,
								&g_aStage[nCntStageModel].mtxWold,
								&mtxRot);
			//�ʒu
			D3DXMatrixTranslation(	&mtxTrans,
									g_aStage[nCntStageModel].pos.x,
									g_aStage[nCntStageModel].pos.y,
									g_aStage[nCntStageModel].pos.z);

			D3DXMatrixMultiply(	&g_aStage[nCntStageModel].mtxWold,
								&g_aStage[nCntStageModel].mtxWold,
								&mtxTrans);
			//�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aStage[nCntStageModel].mtxWold);
			//---------------------------
			//�`�揈��
			//---------------------------
			D3DMATERIAL9		matDef;				//�}�e���A���̈ꎞ�ۑ�
			D3DXMATERIAL		*pMat;				//�}�e���A���f�[�^�̃|�C���^

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�̃|�C���^
			pMat = (D3DXMATERIAL*)g_aStage[nCntStageModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aStage[nCntStageModel].pnNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(	0,
										g_apTextureStage[nCntStageModel][nCntMat]);

				//���f���p�[�c�̕`��
				g_aStage[nCntStageModel].pMesh->DrawSubset(nCntMat);
			}
			//�ꎞ�ۑ����Ă�������ǂ�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------
//�Z�b�g
//---------------------------
void SetStage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, MODEL_TYPE Type)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	for (int nCntStageModel = 0; nCntStageModel < MAX_STAGE_MODEL; nCntStageModel++)
	{
		if (g_aStage[nCntStageModel].bUse == false)
		{
			g_aStage[nCntStageModel].pos = pos;		//�ʒu�̑��
			g_aStage[nCntStageModel].rot = rot;		//�����̑��
			g_aStage[nCntStageModel].aType = Type;	//��ނ̑��
			g_aStage[nCntStageModel].move = move;	//�ړ��ʂ̑��

			if (g_aStage[nCntStageModel].aType == STAGE_FLOO_00 || g_aStage[nCntStageModel].aType == STAGE_MOVEFLOO_00)
			{
				//---------------------------
				//X�t�@�C���̓ǂݍ���
				//---------------------------
				D3DXLoadMeshFromX(	"data/Model/Stage/stage_floo_00.x",
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_aStage[nCntStageModel].pBuffMat,
									NULL,
									&g_aStage[nCntStageModel].pnNumMat,
									&g_aStage[nCntStageModel].pMesh);
			}
			else if (g_aStage[nCntStageModel].aType == STAGE_FENCE_00)
			{
				//---------------------------
				//X�t�@�C���̓ǂݍ���
				//---------------------------
				D3DXLoadMeshFromX(	"data/Model/Stage/stage_fence_01.x",
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_aStage[nCntStageModel].pBuffMat,
									NULL,
									&g_aStage[nCntStageModel].pnNumMat,
									&g_aStage[nCntStageModel].pMesh);
			}
			//---------------------------
			//�e�N�X�`���̔����o��
			//---------------------------
			D3DXMATERIAL *pMat;	//�}�e���A���̃|�C���^

			//�}�e���A�����̃|�C���^
			pMat = (D3DXMATERIAL*)g_aStage[nCntStageModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aStage[nCntStageModel].pnNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(	pDevice,
												pMat[nCntMat].pTextureFilename,			//�e�N�X�`��
												&g_apTextureStage[nCntStageModel][nCntMat]);
				}
			}

			//���_�o�b�t�@���A�����b�N
			g_aStage[nCntStageModel].pMesh->UnlockVertexBuffer();
			g_aStage[nCntStageModel].bUse = true;	//�g���Ă�
			break;
		}
	}
	//---------------------------
	//���_���W�̔����o��
	//---------------------------
	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^

	//���_�����擾
	nNumVtx = g_aStage[g_nModel].pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_aStage[g_nModel].pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_aStage[g_nModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

		//���_�����r���čŏ��l�A�ő�l�𔲂�
		//X
		if (g_aStage[g_nModel].vtxMaxModel.x <= vtx.x)
		{
			g_aStage[g_nModel].vtxMaxModel.x = vtx.x;
		}
		if (g_aStage[g_nModel].vtxMinModel.x >= vtx.x)
		{
			g_aStage[g_nModel].vtxMinModel.x = vtx.x;
		}
		//Y
		if (g_aStage[g_nModel].vtxMaxModel.y <= vtx.y)
		{
			g_aStage[g_nModel].vtxMaxModel.y = vtx.y;
		}
		if (g_aStage[g_nModel].vtxMinModel.y >= vtx.y)
		{
			g_aStage[g_nModel].vtxMinModel.y = vtx.y;
		}
		//Z
		if (g_aStage[g_nModel].vtxMaxModel.z <= vtx.z)
		{
			g_aStage[g_nModel].vtxMaxModel.z = vtx.z;
		}
		if (g_aStage[g_nModel].vtxMinModel.z >= vtx.z)
		{
			g_aStage[g_nModel].vtxMinModel.z = vtx.z;
		}
		pVtxBuff += sizeFVF;	//���_��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_aStage[g_nModel].pMesh->UnlockVertexBuffer();

	//���a���o��
	g_aStage[g_nModel].fWidth = g_aStage[g_nModel].vtxMaxModel.x - g_aStage[g_nModel].vtxMinModel.x;
	g_aStage[g_nModel].fHight = g_aStage[g_nModel].vtxMaxModel.y - g_aStage[g_nModel].vtxMinModel.y;
	g_aStage[g_nModel].fDepth = g_aStage[g_nModel].vtxMaxModel.z - g_aStage[g_nModel].vtxMinModel.z;

	g_nModel++;
}

//---------------------------
//�����蔻��
//---------------------------
bool CollisionStage(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType)
{
	bool bLand = false;	//�n�ʂɂ��Ă邩
	Camera *pCamera;
	Stage *pStage;

	pStage = GetStage();
	pCamera = GetCamera();

	for (int nCntModel = 0; nCntModel < MAX_STAGE_MODEL; nCntModel++, pStage++)
	{
		if (pStage->bUse == true)
		{
			if (nType == 0)
			{
				//��]0������
				if (pStage->rot.y == 0.0f || pStage->rot.y == -D3DX_PI)
				{
					//��ɍڂ��Ă���
					if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fWidth / 2.0f &&
						pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fWidth / 2.0f &&
						pos->z - fDepht / 2.0f < pStage->pos.z + pStage->fDepth / 2.0f &&
						pos->z + fDepht / 2.0f > pStage->pos.z - pStage->fDepth / 2.0f &&
						posold->y >= pStage->pos.y + pStage->vtxMaxModel.y &&
						pos->y <= pStage->pos.y + pStage->vtxMaxModel.y)
					{
						move->y = 0.0f;
						pos->y = pStage->pos.y + pStage->vtxMaxModel.y;	//�n�ʂɍ��킹��
						pCamera->PosV.x += pStage->move.x;	//�ړ����������瓮��
						pCamera->PosV.z += pStage->move.z;	//�ړ����������瓮��
						pCamera->PosR.z += pStage->move.z;
						pCamera->PosR.x += pStage->move.x;
						bLand = true;			//�n�ʂɂ��Ă�
					}
					//�t�F���X��������
					if (pStage->aType == STAGE_FENCE_00)
					{
						//�����Ă�0
						if (pStage->rot.y == 0.0f)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fWidth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fWidth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->z > pStage->pos.z - pStage->fDepth * 2)
							{
								pCamera->PosV.z = pStage->pos.z - pStage->fDepth * 2;
								bLand = false;			//�n�ʂɂ��ĂȂ�
							}
						}
						//��]������
						else if (pStage->rot.y == -D3DX_PI)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fWidth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fWidth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->z < pStage->pos.z + pStage->fDepth * 2)
							{
								pCamera->PosV.z = pStage->pos.z + pStage->fDepth * 2;
								bLand = false;			//�n�ʂɂ��ĂȂ�
							}
						}
					}
				}
				//�����Ă񂪍��E
				else if (pStage->rot.y == D3DX_PI / 2 || pStage->rot.y == -D3DX_PI / 2)
				{
					//��ɍڂ��Ă���
					if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fDepth / 2.0f &&
						pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fDepth / 2.0f &&
						pos->z - fDepht / 2.0f < pStage->pos.z + pStage->fWidth / 2.0f &&
						pos->z + fDepht / 2.0f > pStage->pos.z - pStage->fWidth / 2.0f &&
						posold->y >= pStage->pos.y + pStage->vtxMaxModel.y &&
						pos->y <= pStage->pos.y + pStage->vtxMaxModel.y)
					{
						move->y = 0.0f;
						pos->y = pStage->pos.y + pStage->vtxMaxModel.y;	//�n�ʂɍ��킹��
						pCamera->PosV.x += pStage->move.x;	//�ړ����������瓮��
						pCamera->PosV.z += pStage->move.z;	//�ړ����������瓮��
						bLand = true;			//�n�ʂɂ��Ă�
					}
					//�t�F���X��������	
					if (pStage->aType == STAGE_FENCE_00)
					{
						//�E
						if (pStage->rot.y == D3DX_PI / 2)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fDepth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fDepth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->x > pStage->pos.x - pStage->fDepth * 2)
							{
								pCamera->PosV.x = pStage->pos.x - pStage->fDepth * 2;
								bLand = false;			//�n�ʂɂ��ĂȂ�
							}
						}
						//��
						else if (pStage->rot.y == -D3DX_PI / 2)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fDepth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fDepth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->x < pStage->pos.x + pStage->fDepth * 2)
							{
								pCamera->PosV.x = pStage->pos.x + pStage->fDepth * 2;
								bLand = false;			//�n�ʂɂ��ĂȂ�
							}
						}
					}
				}
			}
			else if (nType != 0)
			{
				//��]0������
				if (pStage->rot.y == 0.0f || pStage->rot.y == -D3DX_PI)
				{
					//��ɍڂ��Ă���
					if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fWidth / 2.0f &&
						pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fWidth / 2.0f &&
						pos->z - fDepht / 2.0f < pStage->pos.z + pStage->fDepth / 2.0f &&
						pos->z + fDepht / 2.0f > pStage->pos.z - pStage->fDepth / 2.0f &&
						posold->y >= pStage->pos.y + pStage->vtxMaxModel.y &&
						pos->y <= pStage->pos.y + pStage->vtxMaxModel.y)
					{
						move->y = 0.0f;
						pos->y = pStage->pos.y + pStage->vtxMaxModel.y;	//�n�ʂɍ��킹��
						pos->x += pStage->move.x;	//�ړ����������瓮��
						pos->z += pStage->move.z;	//�ړ����������瓮��
						bLand = true;			//�n�ʂɂ��Ă�
					}
					//�t�F���X��������
					if (pStage->aType == STAGE_FENCE_00)
					{
						//�����Ă�0
						if (pStage->rot.y == 0.0f)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fWidth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fWidth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->z > pStage->pos.z - pStage->fDepth * 2)
							{
								pos->z = pStage->pos.z - pStage->fDepth * 2;
								if (nType == 1)
								{
									bLand = true;
								}
								else
								{
									bLand = false;			//�n�ʂɂ��ĂȂ�
								}
							}
						}
						//��]������
						else if (pStage->rot.y == -D3DX_PI)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fWidth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fWidth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->z < pStage->pos.z + pStage->fDepth * 2)
							{
								pos->z = pStage->pos.z + pStage->fDepth * 2;
								if (nType == 1)
								{
									bLand = true;
								}
								else
								{
									bLand = false;			//�n�ʂɂ��ĂȂ�
								}
							}
						}
					}
				}
				//�����Ă񂪍��E
				else if (pStage->rot.y == D3DX_PI / 2 || pStage->rot.y == -D3DX_PI / 2)
				{
					//��ɍڂ��Ă���
					if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fDepth / 2.0f &&
						pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fDepth / 2.0f &&
						pos->z - fDepht / 2.0f < pStage->pos.z + pStage->fWidth / 2.0f &&
						pos->z + fDepht / 2.0f > pStage->pos.z - pStage->fWidth / 2.0f &&
						posold->y >= pStage->pos.y + pStage->vtxMaxModel.y &&
						pos->y <= pStage->pos.y + pStage->vtxMaxModel.y)
					{
						move->y = 0.0f;
						pos->y = pStage->pos.y + pStage->vtxMaxModel.y;	//�n�ʂɍ��킹��
						pos->x += pStage->move.x;	//�ړ����������瓮��
						pos->z += pStage->move.z;	//�ړ����������瓮��
						bLand = true;			//�n�ʂɂ��Ă�
					}
					//�t�F���X��������	
					if (pStage->aType == STAGE_FENCE_00)
					{
						//�E
						if (pStage->rot.y == D3DX_PI / 2)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fDepth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fDepth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->x > pStage->pos.x - pStage->fDepth * 2)
							{
								pos->x = pStage->pos.x - pStage->fDepth * 2;
								if (nType == 1)
								{
									bLand = true;
								}
								else
								{
									bLand = false;			//�n�ʂɂ��ĂȂ�
								}
							}
						}
						//��
						else if (pStage->rot.y == -D3DX_PI / 2)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fDepth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fDepth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->x < pStage->pos.x + pStage->fDepth * 2)
							{
								pos->x = pStage->pos.x + pStage->fDepth * 2;
								if (nType == 1)
								{
									bLand = true;
								}
								else
								{
									bLand = false;			//�n�ʂɂ��ĂȂ�
								}
							}
						}
					}
				}
			}
		}
	}
	pStage -= MAX_STAGE_MODEL;

	return bLand;
}

//---------------------------
//�����蔻��
//---------------------------
Stage *GetStage(void)
{
	return &g_aStage[0];
}