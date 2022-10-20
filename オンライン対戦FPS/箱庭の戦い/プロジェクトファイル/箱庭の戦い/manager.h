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
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIGHT (3)	//���C�g�̐�

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;
class CCamera;
class CLight;
class CTexture;
class CKeyboard;
class CMouse;
class CGamepad;
class CSound;
class CTcpClient;
class CGame;
class CTitle;
class CRule;
class CMatching;
class CFade;

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
		RULE,	// ���[���V�[��
		MATCHING,	// �}�b�`���O���V�[��
		GAME,	// �Q�[���V�[��
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
	static CCamera *GetCamera(void) { return m_pCamera; }	// �J�����N���X�̎擾
	static CLight *GetLight(int nLightNum) { return m_pLight[nLightNum]; }	// ���C�g�N���X�̎擾
	static CTexture *GetTexture(void) { return m_pTexture; }	// �e�N�X�`���N���X�̎擾
	static CKeyboard *GetKeyboard(void) { return m_pKeyboard; }	// �L�[�{�[�h�N���X�̎擾
	static CMouse *GetMouse(void) { return m_pMouse; }	// �}�E�X�N���X�̎擾
	static CGamepad *GetGemepad(void) { return m_pGamepad; }	// �p�b�h�N���X�̎擾
	static CSound  *GetSound(void) { return m_pSound; }	// �T�E���h�N���X�̎擾
	static CTcpClient *GetTcpClient(void) { return m_pTcpClient; }	// �ʐM�N���X�̎擾
	static CFade *GetFade(void) { return m_pFade; }	// �t�F�[�h�N���X�̎擾
	static CTitle *GetTitle(void) { return m_pTitle; }	// �^�C�g���N���X�̎擾
	static CRule *GetRule(void) { return m_pRule; }	// ���[���N���X�̎擾
	static CMatching *GetMatching(void) { return m_pMatchibg; }	// �}�b�`���O�N���X�̎擾
	static CGame *GetGame(void) { return m_pGame; }	// �Q�[���N���X�̎擾
	static HWND GetHandle(void) { return m_hwnd; }	// �n���h���̎擾
private:
	static MODE m_Mode;	// �V�[�����[�h
	static MODE m_ModeOld;	// �V�[�����[�h
	static CRenderer *m_pRenderer;	// �����_�����O�N���X
	static CCamera *m_pCamera;	// �J�����N���X
	static CLight *m_pLight[MAX_LIGHT];	// ���C�g�N���X
	static CTexture *m_pTexture;	// �e�N�X�`���N���X
	static CKeyboard *m_pKeyboard;	// �L�[�{�[�h�N���X
	static CMouse *m_pMouse;	// �}�E�X�N���X
	static CGamepad *m_pGamepad;	// �p�b�h�N���X
	static CSound *m_pSound;	// �T�E���h�N���X
	static CTcpClient *m_pTcpClient;	// �ʐM�N���X
	static CFade *m_pFade;	// �t�F�[�h
	static CTitle *m_pTitle;	// �^�C�g���N���X
	static CRule *m_pRule;	// ���[���N���X
	static CMatching *m_pMatchibg;	// �}�b�`���O�N���X
	static CGame *m_pGame;	// �Q�[���N���X
	static HWND m_hwnd;	// �E�B���h�E�n���h��
};

#endif