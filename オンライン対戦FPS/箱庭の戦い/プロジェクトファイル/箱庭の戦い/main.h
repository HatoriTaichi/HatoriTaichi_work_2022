//=============================================================================
//
// ���C������ [main.h]
// Author : �H������
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION (0x0800) //�r���h���̌x���Ώ��p�}�N��
#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <thread>
#include <map>
#include <fstream>
#include <mutex>
#include <iomanip>
#include <iostream>
#include "d3dx9.h"
#include "dinput.h"	//���͏����ɕK�v
#include "xaudio2.h"
using namespace std;

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")		//�`��ɕK�v
#pragma comment(lib,"d3dx9.lib")	//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	//DirectX�R���|�[�l���g�i���i�j�g�p�ɕK�v
#pragma comment (lib, "winmm.lib")
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH (1920) //�E�B���h�E�̕�
#define SCREEN_HEIGHT (1080) //�E�B���h�E�̍���
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)	// �X�N���[���̐^��
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)	// �X�N���[���̐^��
#define FPS (144)		// FPS�̒l
#define MAX_CHARDATA (128)
#define MAX_COMMUDATA (524)

//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************
int GetFPS(void);		// FPS�̎擾

#endif