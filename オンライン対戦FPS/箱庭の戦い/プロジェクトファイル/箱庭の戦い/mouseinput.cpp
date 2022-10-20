//=============================================================================
//
// �}�E�X���͏��� [mouseinput.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "mouseinput.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMouse::CMouse()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CMouse::~CMouse()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�ȗ�
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2)))
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
void CMouse::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CMouse::Update(void)
{
	DIMOUSESTATE2 State;

	// �ŐV�̃}�E�X�̏�Ԃ��擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(State), &State)))
	{
		for (int nCntBotton = 0; nCntBotton < BOTTON_MAX; nCntBotton++)
		{
			m_aStateTrigger.rgbButtons[nCntBotton] = (m_aState.rgbButtons[nCntBotton] ^ State.rgbButtons[nCntBotton]) & State.rgbButtons[nCntBotton];
			m_aStateRelease.rgbButtons[nCntBotton] = (m_aState.rgbButtons[nCntBotton] ^ State.rgbButtons[nCntBotton]) & ~State.rgbButtons[nCntBotton];
		}
		m_aState = State;
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//=============================================================================
// �}�E�X���̎擾
//=============================================================================
bool CMouse::GetPress(int Botton_Type)
{
	return (m_aState.rgbButtons[Botton_Type] & 0x80) ? true : false;
}

bool CMouse::GetTrigger(int Botton_Type)
{
	return (m_aStateTrigger.rgbButtons[Botton_Type] & 0x80) ? true : false;
}

bool CMouse::GetRelease(int Botton_Type)
{
	return (m_aStateRelease.rgbButtons[Botton_Type] & 0x80) ? true : false;
}

DIMOUSESTATE2 CMouse::GetMousePos(void)
{
	return m_aState;
}
