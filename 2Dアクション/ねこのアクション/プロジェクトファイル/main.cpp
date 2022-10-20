//=============================================================================
//
// ���C������ [main.cpp]
// Author : KAZUTO SAKAI
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "home.h"
#include "fade.h"
#include "esystage01.h"
#include "esystage02.h"
#include "esystage03.h"
#include "title.h"
#include "result.h"
#include "operation.h"
#include "gameover.h"
#include "nostage01.h"
#include "nostage02.h"
#include "nostage03.h"
#include "nostage04.h"
#include "hard01.h"
#include "hard02.h"
#include "herd03.h"
#include "herd04.h"
#include "herd05.h"
#include "sound.h"

#ifdef _DEBUG
#include "score.h"
#include "timer.h"
#include"life.h"
#endif  _DEBUG


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"								// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"�˂��̃A�N�V����"	// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
#ifdef _DEBUG
void DrawFPS(void);
#endif

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D �I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
#ifdef _DEBUG
LPD3DXFONT			g_pFont = NULL;			// �t�H���g�ւ̃|�C���^
#endif
int					g_nCountFPS;			// FPS�J�E���^
MODE				g_mode = MODE_TITLE;	//���݂̃��[�h
MODE				g_mode2;

//=============================================================================
// ���C���֐�
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(	CLASS_NAME,
							WINDOW_NAME,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							(rect.right - rect.left),
							(rect.bottom - rect.top),
							NULL,
							NULL,
							hInstance,
							NULL);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	// �t���[���J�E���g������
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();
	dwCurrentTime =
		dwFrameCount = 0;

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b���ƂɎ��s
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 144))
			{// 1/144�b�o��
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}

	// �I������
	Uninit();

	// ����\��߂�
	timeEndPeriod(1);

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));					// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;							// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = TRUE;								// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

																// �f�o�C�X�̐���
																// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
																// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// �J�����O���s��Ȃ�
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

																			// �T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

																			// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g��ݒ�
	D3DXCreateFont(g_pD3DDevice, 50, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);
#endif

	InitKeyboard(hInstance, hWnd);

	InitSound(hWnd);

#ifdef _DEBUG
	InitScore();

	InitTimer();

	InitLife();
#endif _DEBUG

	SetMode(g_mode);

	InitFade(g_mode);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
#ifdef _DEBUG
	if (g_pFont != NULL)
	{// �f�o�b�O���\���p�t�H���g��ݒ�
		g_pFont->Release();
		g_pFont = NULL;
	}
#endif
	//�ȗ������F�e��I�u�W�F�N�g�̏I������
	UninitKeyboard();

	UninitTitle();

	UninitOperation();

	UninitResult();

	UninitGameover();

	UninitHome();

	UninitEsStage01();

	UninitEsStage02();

	UninitEsStage03();

	UninitNoStage01();

	UninitNoStage02();

	UninitNoStage03();

	UninitNoStage04();

	UninitHdStage01();

	UninitHdStage02();

	UninitHdStage03();

	UninitHdStage04();

	UninitHdStage05();

	UninitFade();
	if (g_pD3DDevice != NULL)
	{// �f�o�C�X�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	//�ȗ������F�e��I�u�W�F�N�g�̍X�V����
	UpdateKeyboard();
	
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_OPERATION:
		UpdateOperation();
		break;
	case MODE_HOME:
		UpdateHome();
		break;
	case MODE_ES_STAGE01:
		UpdateEsStage01();
		break;
	case MODE_ES_STAGE02:
		UpdateEsStage02();
		break;
	case MODE_ES_STAGE03:
		UpdateEsStage03();
		break;
	case MODE_NO_STAGE01:
		UpdateNoStage01();
		break;
	case MODE_NO_STAGE02:
		UpdateNoStage02();
		break;
	case MODE_NO_STAGE03:
		UpdateNoStage03();
		break;
	case MODE_NO_STAGE04:
		UpdateNoStage04();
		break;
	case MODE_HD_STAGE01:
		UpdateHdStage01();
		break;
	case MODE_HD_STAGE02:
		UpdateHdStage02();
		break;
	case MODE_HD_STAGE03:
		UpdateHdStage03();
		break;
	case MODE_HD_STAGE04:
		UpdateHdStage04();
		break;
	case MODE_HD_STAGE05:
		UpdateHdStage05();
		break;
	case MODE_GAMEOVER:
		UpdateGameover();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	}
	UpdateFade();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{

		//�ȗ������F�e��I�u�W�F�N�g�̕`�揈��
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		case MODE_OPERATION:
			DrawOperation();
			break;
		case MODE_HOME:
			DrawHome();
			break;
		case MODE_ES_STAGE01:
			DrawEsStage01();
			break;
		case MODE_ES_STAGE02:
			DrawEsStage02();
			break;
		case MODE_ES_STAGE03:
			DrawEsStage03();
			break;
		case MODE_NO_STAGE01:
			DrawNoStage01();
			break;
		case MODE_NO_STAGE02:
			DrawNoStage02();
			break;
		case MODE_NO_STAGE03:
			DrawNoStage03();
			break;
		case MODE_NO_STAGE04:
			DrawNoStage04();
			break;
		case MODE_HD_STAGE01:
			DrawHdStage01();
			break;
		case MODE_HD_STAGE02:
			DrawHdStage02();
			break;
		case MODE_HD_STAGE03:
			DrawHdStage03();
			break;
		case MODE_HD_STAGE04:
			DrawHdStage04();
			break;
		case MODE_HD_STAGE05:
			DrawHdStage05();
			break;
		case MODE_GAMEOVER:
			DrawGameover();
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		}
		DrawFade();
#ifdef _DEBUG
		DrawFPS();
#endif
		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X���擾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=============================================================================
// ���[�h�̐؂�ւ�
//=============================================================================
void SetMode(MODE mode)
{
	g_mode2 = g_mode;

	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_OPERATION:
		UninitOperation();
		break;
	case MODE_HOME:
		UninitHome();
		break;
	case MODE_ES_STAGE01:
		UninitEsStage01();
		break;
	case MODE_ES_STAGE02:
		UninitEsStage02();
		break;
	case MODE_ES_STAGE03:
		UninitEsStage03();
		break;
	case MODE_NO_STAGE01:
		UninitNoStage01();
		break;
	case MODE_NO_STAGE02:
		UninitNoStage02();
		break;
	case MODE_NO_STAGE03:
		UninitNoStage03();
		break;
	case MODE_NO_STAGE04:
		UninitNoStage04();
		break;
	case MODE_HD_STAGE01:
		UninitHdStage01();
		break;
	case MODE_HD_STAGE02:
		UninitHdStage02();
		break;
	case MODE_HD_STAGE03:
		UninitHdStage03();
		break;
	case MODE_HD_STAGE04:
		UninitHdStage04();
		break;
	case MODE_HD_STAGE05:
		UninitHdStage05();
		break;
	case MODE_GAMEOVER:
		UninitGameover();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_OPERATION:
		InitOperation();
		break;
	case MODE_HOME:
		InitHome();
		break;
	case MODE_ES_STAGE01:
		InitEsStage01();
		break;
	case MODE_ES_STAGE02:
		InitEsStage02();
		break;
	case MODE_ES_STAGE03:
		InitEsStage03();
		break;
	case MODE_NO_STAGE01:
		InitNoStage01();
		break;
	case MODE_NO_STAGE02:
		InitNoStage02();
		break;
	case MODE_NO_STAGE03:
		InitNoStage03();
		break;
	case MODE_NO_STAGE04:
		InitNoStage04();
		break;
	case MODE_HD_STAGE01:
		InitHdStage01();
		break;
	case MODE_HD_STAGE02:
		InitHdStage02();
		break;
	case MODE_HD_STAGE03:
		InitHdStage03();
		break;
	case MODE_HD_STAGE04:
		InitHdStage04();
		break;
	case MODE_HD_STAGE05:
		InitHdStage05();
		break;
	case MODE_GAMEOVER:
		InitGameover();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	}

	g_mode = mode;

}

//=============================================================================
// ���[�h���̎擾
//=============================================================================
MODE GetMode(void)
{
	return g_mode;
}

//=============================================================================
// �O��̃��[�h���̎擾
//=============================================================================
MODE GetMode2(void)
{
	return g_mode2;
}

//=============================================================================
// FPS�\������
//=============================================================================
#ifdef _DEBUG
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", g_nCountFPS);

	// �e�L�X�g�`��
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x0, 0x0));
}
#endif