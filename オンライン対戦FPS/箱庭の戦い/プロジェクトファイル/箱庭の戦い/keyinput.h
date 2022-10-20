//=============================================================================
//
// �L�[�{�[�h���� [keyinput.h]
// Author : �H������
//
//=============================================================================
#ifndef _KEYINPUT_H_
#define _KEYINPUT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_KEY_MAX (256)//�L�[�̍ő吔

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CKeyboard : public CInput
{
public:
	//---------------------------
	// �񋓌^
	//---------------------------
	typedef enum
	{
		NUM_1,	// 1
		NUM_2,	// 2
		W,	// W
		A,	// A
		S,	// S
		D,	// D
		J,	// J
		R,	// R
		SPACE,	// SPACE
		LSHIFT,	// LEFTSHIFT
		CTRL,	// CTRL
		KEYBINDMAX,
	} KEYBIND;

	CKeyboard();	// �f�t�H���g�R���X�g���N�^
	~CKeyboard();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void GetAllKeyUpdate(KEYBIND key);	// �ǂ̃L�[�������ꂽ��
	void BindKey(KEYBIND key, int keycode);	// �L�[�o�C���h
	bool GetPress(KEYBIND nKey);	// ����
	bool GetTrigger(KEYBIND nKey);	// ��񉟂�
	bool GetRelease(KEYBIND nKey);	// ������
private:
	BYTE	m_aState[NUM_KEY_MAX];				//�L�[�{�[�h�̓��͏��i�v���X���j
	BYTE	m_aStateTrigger[NUM_KEY_MAX];		//�L�[�{�[�h�̓��͏�� (�g���K�[)
	BYTE	m_aStateRelease[NUM_KEY_MAX];		//�L�[�{�[�h�̓��͏�� (�����[�X)
	int Bind[KEYBINDMAX];// �L�[�o�C���h���
};

#endif