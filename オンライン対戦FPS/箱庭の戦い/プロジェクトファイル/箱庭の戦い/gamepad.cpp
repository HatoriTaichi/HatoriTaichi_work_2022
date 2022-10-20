//=============================================================================
//
// �L�[�{�[�h���͏��� [keyinput.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "gamepad.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGamepad::CGamepad()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CGamepad::~CGamepad()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CGamepad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	m_pInput->EnumDevices(	DI8DEVCLASS_GAMECTRL, 
							EnumJoysticksCallback,
							NULL,
							DIEDFL_ATTACHEDONLY);

	if (m_pJoystick != NULL)
	{
		// �������[�h��ݒ�
		if (FAILED(m_pJoystick->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		{
			return E_FAIL;
		}

		m_pJoystick->GetCapabilities(&m_diDevCaps);

		m_pJoystick->EnumObjects(EnumAxesCallback, (VOID*)hWnd, DIDFT_AXIS);

		m_pJoystick->Poll();

		// �A�N�Z�X�����l��(���͐���J�n)
		m_pJoystick->Acquire();
	}

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CGamepad::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CGamepad::Update(void)
{
	DIJOYSTATE state;

	if (m_pJoystick != NULL)
	{
		//���̓f�o�C�X����f�[�^�擾
		if (SUCCEEDED(m_pJoystick->GetDeviceState(sizeof(state), &state)))
		{
			for (int nCntKey = 0; nCntKey < BUTTON_MAX; nCntKey++)
			{
				m_aStateTrigger.rgbButtons[nCntKey] = (m_aState.rgbButtons[nCntKey] ^ state.rgbButtons[nCntKey]) & state.rgbButtons[nCntKey];
				m_aStateRelease.rgbButtons[nCntKey] = (m_aState.rgbButtons[nCntKey] ^ state.rgbButtons[nCntKey]) & ~state.rgbButtons[nCntKey];
			}
			m_aState = state;
		}
		else
		{
			m_pJoystick->Acquire();
		}
	}
}

//=============================================================================
// �{�^�����̎擾
//=============================================================================
bool CGamepad::GetPress(int Botton_Type)
{
	return (m_aState.rgbButtons[Botton_Type] & 0x80) ? true : false;
}

bool CGamepad::GetTrigger(int Botton_Type)
{
	return (m_aStateTrigger.rgbButtons[Botton_Type] & 0x80) ? true : false;
}

bool CGamepad::GetRelease(int Botton_Type)
{
	return (m_aStateRelease.rgbButtons[Botton_Type] & 0x80) ? true : false;
}

DIJOYSTATE CGamepad::GetGamepad(void)
{
	return m_aState;
}

//=============================================================================
// �R�[���o�b�N�֐�
//=============================================================================
BOOL CALLBACK CGamepad::EnumJoysticksCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	// �W���C�X�e�B�b�N�f�o�C�X�̍쐬
	HRESULT ret = m_pInput->CreateDevice(lpddi->guidInstance, &m_pJoystick, NULL);
	if (FAILED(ret)) 
	{
		return DIENUM_STOP;
	}

	// ���̓f�[�^�`���̃Z�b�g
	ret = m_pJoystick->SetDataFormat(&c_dfDIJoystick);
	if (FAILED(ret)) 
	{
		m_pJoystick->Release();
		return DIENUM_STOP;
	}

	return DIENUM_STOP;
}

BOOL CALLBACK CGamepad::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext)
{
	DIPROPRANGE diprg;

	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	diprg.lMin = -STICK_POW;
	diprg.lMax = STICK_POW;

	if (FAILED(m_pJoystick->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}