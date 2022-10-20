//*****************************************************************************
//
// �T�E���h���� [sound.h]
// Author : �O���B
//
//*****************************************************************************
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();

	// �T�E���h�t�@�C��
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE,		// BGM�^�C�g��
		SOUND_LABEL_BGM_GAME,		// BGM�Q�[��

		SOUND_LABEL_SE_TAP,
		SOUND_LABEL_SE_START,

		SOUND_LABEL_MAX
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

	void ControllVoice(SOUND_LABEL label, float fVolume) { m_apSourceVoice[label]->SetVolume(fVolume); }	//���ʒ���

private:
	// �p�����[�^�\����
	typedef struct
	{
		char *m_filename;			// �t�@�C����
		int m_nCntLoop;				// ���[�v�J�E���g
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y
																
	static PARAM m_aParam[SOUND_LABEL_MAX];						// �e�����f�ނ̃p�����[�^
};

#endif