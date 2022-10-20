#pragma once
//�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{
// �T�E���h���� [sound.h]
// Author : SAKAI KAZUTO
//�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=================================
// �T�E���h�t�@�C��
//=================================
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// �^�C�g��
	SOUND_LABEL_BGM001,			// �Q�[��
	SOUND_LABEL_BGM002,			// ���U���g
	SOUND_LABEL_BGM003,			// �Q�[���I�[�o
	SOUND_LABEL_BGM004,			// �{�X
	SOUND_LABEL_SE000,			// ok
	SOUND_LABEL_SE001,			// �V���b�g
	SOUND_LABEL_SE002,			// ��������
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif