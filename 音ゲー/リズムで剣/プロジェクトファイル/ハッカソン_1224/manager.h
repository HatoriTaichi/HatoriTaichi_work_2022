//=============================================================================
//
// �}�l�[�W���[�Ǘ����� [namager.h]
// Author : �H������
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "main.h"

#pragma comment(lib, "ws2_32.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIGHT (3)	//���C�g�̐�

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;
class CTexture;
class CKeyboard;
class CMouse;
class CFade;
class CTitle;
class CGame;
class CManual;
class CResult;
class CSound;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CManager
{
public:
	//---------------------------
	// �񋓌^
	//---------------------------
	enum class MODE
	{
		TITLE = 0,	// �^�C�g���V�[��
		MANUAL,	// ������ʃV�[��
		GAME,	// �Q�[���V�[��
		RESULT,	// ���U���g�V�[��
		MAX,	// �S�̐�
	};

	CManager();	// �f�t�H���g�R���X�g���N�^
	~CManager();// �f�t�H���g�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	// �X�N���[���̏�����
	void Uninit(void);	// �X�N���[���̏I��
	void Update(void);	// �X�N���[���̍X�V
	void Draw(void);	// �X�N���[���̕`��
	static void SetMode(MODE mode);	// ���[�h�`�F���W
	static MODE GetMode(void) { return m_Mode; }	// ���[�h����
	static MODE GetModeOld(void) { return m_ModeOld; }	// �O��̃��[�h����
	static CRenderer *GetRenderer(void) { return m_pRenderer; }	// �����_�����O�N���X�̎擾
	static CTexture *GetTexture(void) { return m_pTexture; }	// �e�N�X�`���N���X�̎擾
	static CKeyboard *GetKeyboard(void) { return m_pKeyboard; }	// �L�[�{�[�h�N���X�̎擾
	static CMouse *GetMouse(void) { return m_pMouse; }	// �}�E�X�N���X�̎擾
	static CFade *GetFade(void) { return m_pFade; }	// �t�F�[�h�N���X�̎擾
	static CTitle *GetTitle(void) { return m_pTitle; }	// �^�C�g���N���X�̎擾
	static CGame *GetGame(void) { return m_pGame; }	// �Q�[���N���X�̎擾
	static HWND GetHandle(void) { return m_hwnd; }	// �n���h���̎擾
	static CSound *GetSound()	{ return m_pSound; }	// �T�E���h�N���X�̎擾

private:
	static MODE	m_Mode;		// �V�[�����[�h
	static MODE	m_ModeOld;	// �V�[�����[�h
	static CRenderer	*m_pRenderer;	// �����_�����O�N���X
	static CTexture	*m_pTexture;	// �e�N�X�`���N���X
	static CKeyboard	*m_pKeyboard;	// �L�[�{�[�h�N���X
	static CMouse	*m_pMouse;		// �}�E�X�N���X
	static CFade	*m_pFade;	// �t�F�[�h
	static CTitle	*m_pTitle;	// �^�C�g���N���X
	static CManual	*m_pManual;	// ������ʃN���X
	static CGame	*m_pGame;	// �Q�[���N���X
	static CResult	*m_pResult;	// ���U���g�N���X
	static CSound	*m_pSound;	// �T�E���h�N���X
	static HWND	m_hwnd;	// �E�B���h�E�n���h��
};

#endif