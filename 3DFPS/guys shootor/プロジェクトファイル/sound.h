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
	SOUND_TITLE_BGM = 0,	//�^�C�g��BGM
	SOUND_OPERAT_BGM,		//�������BGN
	SOUND_GAME_BGM,			//�Q�[��BGM
	SOUND_RESULT_BGN,		//���U���gBGN
	SOUND_PUSH_SE,			//�{�^��SE
	SOUND_SHOT_00,			//����SE
	SOUND_RELOAD_00,		//�����[�hSE
	SOUND_EXPOSION,			//����SE
	SOUND_LABEL_MAX,		//BGM.SE�̍ő吔
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