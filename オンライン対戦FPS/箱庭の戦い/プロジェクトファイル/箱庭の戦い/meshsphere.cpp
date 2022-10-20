//=============================================================================
//
// 3D�|���S������ [floo.cpp]
// Author : �H������
//
//=============================================================================
#include "meshsphere.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMeshsphere::CMeshsphere()
{
	int m_nXPoly = 0;
	int m_nZPoly = 0;
	int m_nXRadius = 0;
	D3DXMatrixIdentity(&m_mtxWorld);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshsphere::~CMeshsphere()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshsphere::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X���擾����

	//�e�N�X�`���̐ݒ�
	SetTexture(m_Type);

	//���_�o�b�t�@�̎擾
	LPDIRECT3DVERTEXBUFFER9* ppVtxBuff = GetVtxBuff();

	int nNumVtx = GetNumVtx();	//���_���̎擾
	int nNumIdx = GetNumIdx();	//�C���f�b�N�X���̎擾

	//���_�o�b�t�@�̐���
	if (*ppVtxBuff == NULL)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nNumVtx,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									ppVtxBuff,
									NULL);
	}

	//���_�o�b�t�@�̐ݒ�
	if (*ppVtxBuff != NULL)
	{
		VERTEX_3D *pVtx;	//���_�o�b�t�@�̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		(*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);

		int nVtxNum = 0;
		for (int nCntY = 0; nCntY < m_nYPoly + 1; nCntY++)
		{
			for (int nCntX = 0; nCntX < m_nXPoly + 1; nCntX++, nVtxNum++)
			{
				pVtx[nVtxNum].pos = D3DXVECTOR3(cosf(D3DX_PI * 2 / m_nXPoly * nCntX) * sinf(D3DX_PI * 2 / m_nXPoly * nCntY + (D3DX_PI / 2)) * m_nRadius,
												sinf(D3DX_PI * 2 / m_nXPoly * nCntY) * m_nRadius,
												sinf(D3DX_PI * 2 / m_nXPoly * nCntX) * sinf(D3DX_PI * 2 / m_nXPoly * nCntY + (D3DX_PI / 2)) * m_nRadius);
				pVtx[nVtxNum].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
				pVtx[nVtxNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[nVtxNum].tex = D3DXVECTOR2((1.0f / m_nXPoly) * nCntX, (1.0f / m_nYPoly) * nCntY);
			}
		}
		nVtxNum = 0;
		//���_�o�b�t�@���A�����b�N����
		(*ppVtxBuff)->Unlock();
	}

	//�C���f�b�N�X�o�b�t�@�̂̎擾
	LPDIRECT3DINDEXBUFFER9* ppIdxBuff = GetIdxBuff();

	//�C���f�b�N�X�o�b�t�@�̐���
	if (*ppIdxBuff == NULL)
	{
		pDevice->CreateIndexBuffer( sizeof(WORD) * nNumIdx,
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									ppIdxBuff,
									NULL);
	}
	//�C���f�b�N�X�o�b�t�@�̐ݒ�
	if (*ppIdxBuff != NULL)
	{
		WORD *pIdx;	//�C���f�b�N�X���ւ̃|�C���^

		//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
		(*ppIdxBuff)->Lock(0, 0, (void**)&pIdx, 0);

		//�p�킳��ȊO�̒��_
		for (int nCntZ = 0; nCntZ < m_nYPoly; nCntZ++)
		{
			for (int nCntX = 0; nCntX < m_nXPoly + 1; nCntX++)
			{
				pIdx[(nCntX * 2) + 0 + ((m_nXPoly + 2) * 2) * nCntZ] = ((m_nXPoly + 1) + nCntX) + ((m_nXPoly + 1) * nCntZ);
				pIdx[(nCntX * 2) + 1 + ((m_nXPoly + 2) * 2) * nCntZ] = (0 + nCntX) + ((m_nXPoly + 1) * nCntZ);
			}
		}
		//�p�킳��̒��_
		for (int nCntZ = 0; nCntZ < m_nYPoly - 1; nCntZ++)
		{
			pIdx[(((m_nXPoly + 1) * 2 + 0) * (nCntZ + 1)) + (2 * nCntZ)] = m_nXPoly + ((m_nXPoly + 1) * nCntZ);
			pIdx[(((m_nXPoly + 1) * 2 + 1) * (nCntZ + 1)) + (1 * nCntZ)] = (m_nXPoly * 2 + 2) + ((m_nXPoly + 1) * nCntZ);
		}

		//�C���f�b�N�X�o�b�t�@���A�����b�N����
		(*ppIdxBuff)->Unlock();
	}

	// ������
	CScene3D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshsphere::Uninit(void)
{
	// �j��
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshsphere::Update(void)
{
	// �X�V
	CScene3D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshsphere::Draw(void)
{
	// �`��
	CScene3D::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CMeshsphere* CMeshsphere::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPolyX, int nPolyY, int nRadius, string type)
{
	CMeshsphere* pSphere;	// �����̃|�C���^
	pSphere = new CMeshsphere;	// ����

	// ��������Ă�����
	if (pSphere != NULL)
	{
		// �����̑��
		pSphere->m_Type = type;
		pSphere->m_nXPoly = nPolyX;
		pSphere->m_nYPoly = nPolyY;
		pSphere->m_nRadius = nRadius;
		pSphere->SetPos(pos);
		pSphere->SetRot(rot);
		pSphere->SetNumVtx((nPolyX + 1) * (nPolyY + 1));
		pSphere->SetNumIdx((nPolyX + 1) * (nPolyY + 1) + (nPolyY - 1) * (nPolyX + 3));

		// ������
		pSphere->Init();
	}

	return pSphere;
}