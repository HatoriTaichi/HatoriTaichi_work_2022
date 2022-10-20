//=============================================================================
//
// ���͏��� [input.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "matching.h"
#include "manager.h"
#include "textureobj.h"
#include "tcp_client.h"
#include "fade.h"
#include "communicationdata.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
bool CMatching::m_bConnect = false;
bool CMatching::m_bEnemyConnect = false;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMatching::CMatching()
{
	m_bEnemyConnect = false;
	m_bConnect = false;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CMatching::~CMatching()
{
	
}

//=============================================================================
// ������
//=============================================================================
HRESULT CMatching::Init(void)
{
	CTcpClient *pClient = CManager::GetTcpClient();	// �ʐM�N���X�̎擾

	// �擾�o���Ă�����
	if (pClient != NULL)
	{
		// ������
		pClient->Init();
	}

	// �X���b�h�𐶐�
	thread th(ConnectTh);

	// �X���b�h��؂藣��
	th.detach();

	// ����
	CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(250.0f, 50.0f, 0.0f), "MATCHING");

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CMatching::Uninit(void)
{
	CSound *pSound = CManager::GetSound();	// �T�E���h�̎擾

	// �j��
	CScene::ReleaseAll();

	// �Đ�
	pSound->StopSound(CSound::X2SOUND_LABEL::TITLE);
}

//=============================================================================
// �X�V����
//=============================================================================
void CMatching::Update(void)
{
	CFade *pFade = CManager::GetFade();	// �t�F�[�h�N���X�̎擾

	// �G���Ȃ����Ă��� && �t�F�[�h���Ă��Ȃ�������
	if (m_bEnemyConnect == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
	{
		// �Q�[����ʂɑJ��
		pFade->SetFade(CManager::MODE::GAME);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMatching::Draw(void)
{

}

//=============================================================================
// �ʐM�X���b�h
//=============================================================================
void CMatching::ConnectTh(void)
{
	CTcpClient *pClient = CManager::GetTcpClient();	// �ʐM�N���X�̎擾
	char aRecvData[MAX_CHARDATA];	// ��M�f�[�^

	// �Ȃ���܂Ń��[�v
	while (!m_bConnect)
	{
		m_bConnect = pClient->Connect();
	}
	// �G���Ȃ���܂Ń��[�v
	while (!m_bEnemyConnect)
	{
		pClient->Recv(&aRecvData[0], sizeof(bool));
		memcpy(&m_bEnemyConnect, &aRecvData[0], sizeof(bool));
	}
}