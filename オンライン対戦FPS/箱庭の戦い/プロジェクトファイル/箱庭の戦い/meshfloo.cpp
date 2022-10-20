//=============================================================================
//
// 3D�|���S������ [floo.cpp]
// Author : �H������
//
//=============================================================================
#include "meshfloo.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMeshFloo::CMeshFloo()
{
	int m_nXPoly = 0;
	int m_nZPoly = 0;
	int m_nXRadius = 0;
	int m_nZRadius = 0;
	D3DXMatrixIdentity(&m_mtxWorld);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshFloo::~CMeshFloo()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshFloo::Init(void)
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
		pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * nNumVtx,
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
		for (int nCntZ = 0; nCntZ < m_nZPoly + 1; nCntZ++)
		{
			for (int nCntX = 0; nCntX < m_nXPoly + 1; nCntX++, nVtxNum++)
			{
				pVtx[nVtxNum].pos = D3DXVECTOR3(-m_nXRadius + (((m_nXRadius * 2) / m_nXPoly) * nCntX), 0.0f, m_nZRadius - (((m_nZRadius * 2) / m_nZPoly) * nCntZ));
				pVtx[nVtxNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[nVtxNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[nVtxNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (1.0f * nCntZ));
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
		pDevice->CreateIndexBuffer(	sizeof(WORD) * nNumIdx,
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
		for (int nCntZ = 0; nCntZ < m_nZPoly; nCntZ++)
		{
			for (int nCntX = 0; nCntX < m_nXPoly + 1; nCntX++)
			{
				pIdx[(nCntX * 2) + 0 + ((m_nXPoly + 2) * 2) * nCntZ] = ((m_nXPoly + 1) + nCntX) + ((m_nXPoly + 1) * nCntZ);
				pIdx[(nCntX * 2) + 1 + ((m_nXPoly + 2) * 2) * nCntZ] = (0 + nCntX) + ((m_nXPoly + 1) * nCntZ);
			}
		}
		//�p�킳��̒��_
		for (int nCntZ = 0; nCntZ < m_nZPoly - 1; nCntZ++)
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
void CMeshFloo::Uninit(void)
{
	// �j��
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshFloo::Update(void)
{
	// �e�N�X�`���ŏ�����ς���
	if (m_Type == "SEE")
	{
		D3DXVECTOR3 Pos = GetPos();	// �ʒu�̎擾

		// ���]�J�E���g
		m_nMoveReversCnt++;

		// ���]�J�E���g�ɂȂ�����
		if (m_nMoveReversCnt >= (FPS * 5))
		{
			// �t���O�𔽓]
			if (m_bRevers == false)
			{
				m_bRevers = true;
			}
			else
			{
				m_bRevers = false;
			}
			m_nMoveReversCnt = 0;
		}

		// �Ή������ړ���
		if (m_bRevers == true)
		{
			Pos.x += 0.1f;
			Pos.z += 0.5f;
		}
		else if (m_bRevers == false)
		{
			Pos.x -= 0.1f;
			Pos.z -= 0.5f;
		}

		// �ʒu�̐ݒ�
		SetPos(Pos);
	}

	// �X�V
	CScene3D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshFloo::Draw(void)
{
	// �`��
	CScene3D::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CMeshFloo* CMeshFloo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPolyX, int nPolyZ, int nRadiusX, int nRadiusZ, string type)
{
	CMeshFloo* pFloo;	// ���̃��b�V���̃|�C���^
	pFloo = new CMeshFloo;	// ����

	// ��������Ă�����
	if (pFloo != NULL)
	{
		// �����̑��
		pFloo->m_Type = type;
		pFloo->m_nXPoly = nPolyX;
		pFloo->m_nZPoly = nPolyZ;
		pFloo->m_nXRadius = nRadiusX;
		pFloo->m_nZRadius = nRadiusZ;
		pFloo->SetPos(pos);
		pFloo->SetRot(rot);
		pFloo->SetNumVtx((nPolyX + 1) * (nPolyZ + 1));
		pFloo->SetNumIdx((nPolyX + 1) * (nPolyZ + 1) + (nPolyZ - 1) * (nPolyX + 3));

		// ������
		pFloo->Init();
	}

	return pFloo;
}