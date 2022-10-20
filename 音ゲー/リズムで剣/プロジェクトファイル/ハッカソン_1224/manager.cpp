//=============================================================================
//
// �}�l�[�W���[�Ǘ����� [manager.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include <winsock2.h>
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "fade.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "sound.h"
#include "manual.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CManager::MODE CManager::m_Mode;
CManager::MODE CManager::m_ModeOld;
CRenderer *CManager::m_pRenderer = NULL;
CTexture *CManager::m_pTexture = NULL;
CKeyboard *CManager::m_pKeyboard = NULL;
CMouse *CManager::m_pMouse = NULL;
CFade *CManager::m_pFade = NULL;
CTitle *CManager::m_pTitle = NULL;
CManual *CManager::m_pManual = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
HWND CManager::m_hwnd = NULL;
CSound *CManager::m_pSound = NULL;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �E�B���h�E�n���h���̕ۑ�
	m_hwnd = hWnd;

	// �S��NULL�Ȃ�
	if (m_pTexture == NULL &&
		m_pRenderer == NULL &&
		m_pKeyboard == NULL &&
		m_pMouse == NULL &&
		m_pFade == NULL &&
		m_pTitle == NULL &&
		m_pSound == NULL)
	{
		// ����
		m_pTexture = new CTexture;
		m_pRenderer = new CRenderer;
		m_pKeyboard = new CKeyboard;
		m_pMouse = new CMouse;
		m_pFade = new CFade;
		m_pTitle = new CTitle;
		m_pSound = new CSound;

		// ��������Ă�����
		if (m_pTexture != NULL &&
			m_pRenderer != NULL &&
			m_pKeyboard != NULL &&
			m_pMouse != NULL &&
			m_pFade != NULL &&
			m_pTitle != NULL &&
			m_pSound != NULL)
		{
			// ������
			m_pRenderer->Init(hWnd, bWindow);
			m_pFade->Init();
			m_pKeyboard->Init(hInstance, hWnd);
			m_pMouse->Init(hInstance, hWnd);
			m_pKeyboard->BindKey(CKeyboard::UP, DIK_UP);
			m_pKeyboard->BindKey(CKeyboard::LEFT, DIK_LEFT);
			m_pKeyboard->BindKey(CKeyboard::DOWN, DIK_DOWN);
			m_pKeyboard->BindKey(CKeyboard::RIGHT, DIK_RIGHT);
			m_pKeyboard->BindKey(CKeyboard::ENTER, DIK_RETURN);
			m_pSound->Init(hWnd);
			CTexture::Init();
		}
	}

	// �^�C�g���V�[��
	SetMode(MODE::TITLE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	// �I�u�W�F�N�g�̑S�j��
	CScene::ReleaseAll();
	CTexture::Uniinit();
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}
	if (m_pMouse != NULL)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = NULL;
	}
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}
	if (m_pTitle != NULL)
	{
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = NULL;
	}
	if (m_pManual != NULL)
	{
		m_pManual->Uninit();
		delete m_pManual;
		m_pManual = NULL;
	}
	if (m_pGame != NULL)
	{
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = NULL;
	}
	if (m_pResult != NULL)
	{
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = NULL;
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	// �Y���V�[���̍X�V
	switch (m_Mode)
	{
	case MODE::TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;
	case MODE::MANUAL:
		if (m_pManual != NULL)
		{
			m_pManual->Update();
		}
		break;
	case MODE::GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;
	case MODE::RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;
	default:
		break;
	}
	// �S�I�u�W�F�N�g�̍X�V
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}
	if (m_pMouse != NULL)
	{
		m_pMouse->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	// �Y���V�[���̕`��
	switch (m_Mode)
	{
	case MODE::TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Draw();
		}
		break;
	case MODE::MANUAL:
		if (m_pManual != NULL)
		{
			m_pManual->Draw();
		}
		break;
	case MODE::GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Draw();
		}
		break;
	case MODE::RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Draw();
		}
		break;
	default:
		break;
	}
	// �S�I�u�W�F�N�g�̕`��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// ���[�h�`�����W
//=============================================================================
void CManager::SetMode(MODE mode)
{
	m_ModeOld = m_Mode;	// �O��̃V�[����ۑ�
	m_Mode = mode;	// �V�[���̕ύX

	// �O��̃V�[����j��
	switch (m_ModeOld)
	{
	case MODE::TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;
	case MODE::MANUAL:
		if (m_pManual != NULL)
		{
			m_pManual->Uninit();
			m_pManual = NULL;
		}
		break;
	case MODE::GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;
	case MODE::RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;
	default:
		break;
	}

	// �V�[���𐶐�
	switch (m_Mode)
	{
	case MODE::TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = new CTitle;
			m_pTitle->Init();
		}
		break;
	case MODE::MANUAL:
		if (m_pManual == NULL)
		{
			m_pManual = new CManual;
			m_pManual->Init();
		}
		break;
	case MODE::GAME:
		if (m_pGame == NULL)
		{
			m_pGame = new CGame;
			m_pGame->Init();
		}
		break;
	case MODE::RESULT:
		if (m_pResult == NULL)
		{
			m_pResult = new CResult;
			m_pResult->Init();
		}
		break;
	default:
		break;
	}
}