//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �H������
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DX3D_SOUND_DISTANCE (10.0f)	// 1M�̒�`

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();
	enum class X2SOUND_LABEL
	{
		TITLE = 0,	// �^�C�g��
		GONEXT,	// ����
		WIN,	// �����{�C�X
		LOSE,	// �����{�C�X
		RELOAD,	// �����[�h
		SHOOT,	// �e��
		FOOT_STEP,	// ����
		LABEL_MAX,	// �T�E���h���v
	};
	HRESULT InitSound(HWND hWnd);	// ������
	void UninitSound(void);	// �I��
	HRESULT PlaySound(X2SOUND_LABEL label);	// �Đ�
	void StopSound(X2SOUND_LABEL label);		// ���߂��̃X�g�b�v
	void StopSound(void);	// �S���X�g�b�v
	void ControllVolume(X2SOUND_LABEL label, float fVolume) { m_apSourceVoice[(int)label]->SetVolume(fVolume); }	// ���ʒ���
	void InitDxlibSound(void);	// dxlib�̏�����
	void UninitDxlibSound(void);	// dxlib�̏I��
private:
	typedef struct
	{
		char *filename;	// �t�@�C����
		int nCntLoop;	// ���[�v�J�E���g
	} PARAM;
	static PARAM m_aParam[(int)X2SOUND_LABEL::LABEL_MAX];	// �e���f�ނ̃p�����[�^
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2 *m_pXAudio2 = NULL;	// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;	// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[(int)X2SOUND_LABEL::LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[(int)X2SOUND_LABEL::LABEL_MAX] = {};	// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[(int)X2SOUND_LABEL::LABEL_MAX] = {};	// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif