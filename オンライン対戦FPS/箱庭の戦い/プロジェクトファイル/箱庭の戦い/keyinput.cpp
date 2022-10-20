//=============================================================================
//
// �L�[�{�[�h���͏��� [keyinput.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "keyinput.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CKeyboard::CKeyboard()
{
	memset(&m_aState[0], 0, sizeof(m_aState));
	memset(&m_aStateTrigger[0], 0, sizeof(m_aStateTrigger));
	memset(&m_aStateRelease[0], 0, sizeof(m_aStateRelease));
	for (int nCntKey = 0; nCntKey < KEYBINDMAX; nCntKey++)
	{
		Bind[nCntKey] = -1;
	}
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CKeyboard::~CKeyboard()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�ȗ�
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CKeyboard::Update(void)
{
	BYTE aState[NUM_KEY_MAX];

	//���̓f�o�C�X����f�[�^�擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aState), &aState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aStateTrigger[nCntKey] = (m_aState[nCntKey] ^ aState[nCntKey]) & aState[nCntKey];
			m_aStateRelease[nCntKey] = (m_aState[nCntKey] ^ aState[nCntKey]) & ~aState[nCntKey];
			m_aState[nCntKey] = aState[nCntKey];	// �L�[�{�[�h�̓��͏��ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//=============================================================================
// �ǂ̃L�[�������ꂽ��
//=============================================================================
void CKeyboard::GetAllKeyUpdate(KEYBIND key)
{
	bool bTrigger = false;	// �g���K�[�łǂ���������Ă�
	bool bPress = false;	// �v���X�łǂ���������Ă�
	int nKeyCode = 0;	// �z��
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		bPress = (m_aState[nCntKey] & 0x80) ? true : false;
		bTrigger = (m_aStateTrigger[nCntKey] & 0x80) ? true : false;
		if (bPress == true)
		{
			nKeyCode = nCntKey;
			break;
		}
		else if (bTrigger == true)
		{
			nKeyCode = nCntKey;
			break;
		}
	}
	BindKey(key, nKeyCode);
}

//=============================================================================
// �L�[�o�C���h
//=============================================================================
void CKeyboard::BindKey(KEYBIND key, int keycode)
{
	Bind[key] = keycode;
}

//=============================================================================
// �L�[�{�[�[�h�̏����擾
//=============================================================================
bool CKeyboard::GetPress(KEYBIND nKey)
{
	return (m_aState[Bind[nKey]] & 0x80) ? true : false;
}

bool CKeyboard::GetTrigger(KEYBIND nKey)
{
	return (m_aStateTrigger[Bind[nKey]] & 0x80) ? true : false;
}

bool CKeyboard::GetRelease(KEYBIND nKey)
{
	return (m_aStateRelease[Bind[nKey]] & 0x80) ? true : false;
}