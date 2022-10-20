//=============================================================================
//
// �J�E���^�[���� [counter.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "counter.h"
#include "number.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CCounter::CCounter()
{
	D3DXVECTOR3 m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int m_nNumberMax = 0;	// ����
	int m_nCounter = 0;	// �X�R�A
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CCounter::~CCounter()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CCounter::Init(void)
{
	// �������̃��[�v
	for (int nNumber = 0; nNumber < m_nNumberMax; nNumber++)
	{
		// ���̐���
		m_pNumber.push_back(CNumber::Create(D3DXVECTOR3(m_Pos.x + (m_Size.x * 2) * nNumber, m_Pos.y, 0.0f), m_Size, m_Type));
	}
	m_nCounter = 0;

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CCounter::Uninit(void)
{
	// �������̃��[�v
	for (int nNumber = 0; nNumber < m_nNumberMax; nNumber++)
	{
		// �j��
		m_pNumber[0]->Uninit();
		m_pNumber[0] = NULL;
		m_pNumber.erase(m_pNumber.begin());
	}
	// �j��
	Release();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CCounter::Update(void)
{
	// �X�R�A�̐ݒ�
	SetCounter(m_nCounter);
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CCounter::Draw(void)
{
	// �������̃��[�v
	for (int nNumber = 0; nNumber < m_nNumberMax; nNumber++)
	{
		m_pNumber[nNumber]->Draw();
	}
}

//=============================================================================
// ����
//=============================================================================
CCounter *CCounter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumbderLength, string type)
{
	CCounter *pCount = NULL;	// �J�E���^�[�̃|�C���^

	// NULL��������
	if (pCount == NULL)
	{
		// ����
		pCount = new CCounter;
	}

	// �����̑��
	pCount->m_Pos = pos;
	pCount->m_Size = size;
	pCount->m_Type = type;
	pCount->m_nNumberMax = nNumbderLength;

	// ��������Ă�����
	if (pCount != NULL)
	{
		// ������
		pCount->Init();
	}
	return pCount;
}

//=============================================================================
// �X�R�A�̐ݒ�
//=============================================================================
void CCounter::SetCounter(int nCounter)
{
	int *aNumber = new int[m_nNumberMax];	// ��
	int nDivide = 10;	// �������
	int nBreak = 1;	// �����

	for (int nCnt = 0; nCnt < m_nNumberMax - 1; nCnt++)
	{
		nDivide *= 10;
		nBreak *= 10;
	}

	for (int nCnt = 0; nCnt < m_nNumberMax; nCnt++)
	{
		aNumber[nCnt] = m_nCounter % nDivide / nBreak;
		nDivide /= 10;
		nBreak /= 10;
	}

	// �������̃��[�v
	for (int nNumber = 0; nNumber < m_nNumberMax; nNumber++)
	{
		// �X�R�A�̐ݒ�
		m_pNumber[nNumber]->SetScore(aNumber[nNumber]);
	}
}

//=============================================================================
// �J���[�̐ݒ�
//=============================================================================
void CCounter::SetCol(D3DCOLORVALUE col)
{
	// �������̃��[�v
	for (int nCntNumber = 0; nCntNumber < m_nNumberMax; nCntNumber++)
	{
		// �J���[�̐ݒ�
		m_pNumber[nCntNumber]->SetCol(col);
	}
}