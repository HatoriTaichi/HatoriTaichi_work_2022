//=============================================================================
//
// ���͏��� [input.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "game.h"
#include "manager.h"
#include "textureobj.h"
#include "notes.h"
#include "enemy.h"
#include "fade.h"
#include "player.h"
#include "sound.h"
#include "counter.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGame::CGame()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CGame::Init(void)
{
	FILE *pFile;	// �t�@�C���̃|�C���^
	string FileString;	// �t�@�C���̕�����
	D3DXVECTOR3 Pos;	// �ʒu
	D3DXVECTOR3 Size;	// �T�C�Y
	char aFile[1][128];	// �����擾

	CSound *pSound;	// �T�E���h�̃|�C���^
	pSound = CManager::GetSound();	// �T�E���h�̎擾
	pSound->Play(CSound::SOUND_LABEL_BGM_GAME);	// �T�E���h�̍Đ�

	// �t�@�C�����J��
	pFile = fopen("data/Txtdata/gameuidata.txt", "r");

	// �J���Ă�����
	if (pFile != NULL)
	{
		int nCnt = 0;	// UI�J�E���g

		// �������[�v
		while (true)
		{
			// �������擾
			fscanf(pFile, "%s", aFile[0]);

			// UI_NUM�̕��������������
			if (strcmp(aFile[0], "UI_NUM") == 0)
			{
				// UI����ۑ�
				fscanf(pFile, "%*s%d", &m_nUiNum);
			}
			// SET_UI�̕��������������
			if (strcmp(aFile[0], "SET_UI") == 0)
			{
				// �������[�v
				while (true)
				{
					// �������擾
					fscanf(pFile, "%s", aFile[0]);

					// TEX_TYPE�̕��������������
					if (strcmp(aFile[0], "TEX_TYPE") == 0)
					{
						char aTypeBuf[1][64];	// �������擾����ׂ̃o�b�t�@
						string Type;	// �X�g�����O�z��ɓ����ׂ̃o�b�t�@

						// �������擾
						fscanf(pFile, "%*s%s", aTypeBuf[0]);

						// �X�g�����O�֕ϊ�
						Type = aTypeBuf[0];

						// �z��ɕۑ�
						m_Type.push_back(Type);
					}
					// POS�̕��������������
					else if (strcmp(aFile[0], "POS") == 0)
					{
						// �ʒu����ۑ�
						fscanf(pFile, "%*s%f%f%f", &Pos.x, &Pos.y, &Pos.z);
					}
					// SIZE�̕��������������
					else if (strcmp(aFile[0], "SIZE") == 0)
					{
						// �T�C�Y����ۑ�
						fscanf(pFile, "%*s%f%f%f", &Size.x, &Size.y, &Size.z);
					}
					// END_UISET�̕��������������
					else if (strcmp(aFile[0], "END_UISET") == 0)
					{
						// �擾�������Ő���
						CUiObj::Create(Pos, Size, m_Type[nCnt]);

						// UI�J�E���g�A�b�v
						nCnt++;

						// ���[�v���ʂ���
						break;
					}
				}
			}
			// END�̕��������������
			else if (strcmp(aFile[0], "END") == 0)
			{
				// ���[�v���ʂ���
				break;
			}
		}
	}
	else
	{
		cout << "�e�L�X�g�t�@�C�����Ђ炯�܂���ł����B";
	}

	// �t�@�C�������
	fclose(pFile);

	// �t�@�C�����J��
	pFile = fopen("data/Txtdata/gamedata.txt", "r");

	// �J���Ă�����
	if (pFile != NULL)
	{
		// �������[�v
		while (true)
		{
			// �������擾
			fscanf(pFile, "%s", aFile[0]);

			// NORTS_NUM�̕��������������
			if (strcmp(aFile[0], "NORTS_NUM") == 0)
			{
				// �m�[�c�̍ő吔��ۑ�
				fscanf(pFile, "%*s%d", &m_nNotesNum);
			}
			// SET_NORTS�̕��������������
			if (strcmp(aFile[0], "SET_NORTS") == 0)
			{
				// �������[�v
				while (true)
				{
					// �������擾
					fscanf(pFile, "%s", aFile[0]);

					// TEX_TYPE�̕��������������
					if (strcmp(aFile[0], "TEX_TYPE") == 0)
					{
						char aTypeBuf[1][64];	// �������擾����ׂ̃o�b�t�@
						string Type;	// �X�g�����O�z��ɓ����ׂ̃o�b�t�@

						// �������擾
						fscanf(pFile, "%*s%s", aTypeBuf[0]);

						// �X�g�����O�֕ϊ�
						Type = aTypeBuf[0];

						// �z��ɕۑ�
						m_Type.push_back(Type);
					}
					// SECOND�̕��������������
					else if (strcmp(aFile[0], "SECOND") == 0)
					{
						float nSecond;	// �z��ɓ����ׂ̃o�b�t�@

						// �����擾
						fscanf(pFile, "%*s%f", &nSecond);

						// �z��ɕۑ�
						m_nSecond.push_back(nSecond);
					}
					// END_NOERTSSET�̕��������������
					else if (strcmp(aFile[0], "END_NOERTSSET") == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(aFile[0], "END") == 0)
			{
				break;
			}
		}
	}
	else
	{
		cout << "�e�L�X�g�t�@�C�����Ђ炯�܂���ł����B";
	}

	// �t�@�C�������
	fclose(pFile);

	// ����
	CPlayer::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), "PLAYER");
	m_pCombo = CCounter::Create(D3DXVECTOR3(0.0f + 250.0f, 177.0f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 0.0f), 3, "NUMBER");
	m_pScore = CCounter::Create(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, 177.0f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 0.0f), 8, "NUMBER");

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CGame::Uninit(void)
{
	CSound *pSound;	// �T�E���h�̃|�C���^
	pSound = CManager::GetSound();	// �T�E���h�̎擾
	pSound->Stop();	// ��~
	
	// �S�Ĕj��
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	CFade *pFade = CManager::GetFade();	// �t�F�[�h�̎擾
	m_nLimit++;	// �J�E���g�A�b�v

	// �^�C�}�[������ɍs������ && �t�F�[�h���ĂȂ�������
	if (m_nTimer >= (FPS * 5) && pFade->GetFade() == CFade::FADE_NONE)
	{
		// ���U���g�֑J��
		pFade->SetFade(CManager::MODE::RESULT);
		m_nNotes = 0;
	}

	// �Ō�܂ł�������
	if (m_nNotes == m_nNotesNum)
	{
		// �t�F�[�h
		m_bFade = true;
		m_nTimer++;
	}

	// �ۑ�����Ă���^�C�~���O && �t�F�[�h���ĂȂ�
	if (m_nLimit >= (FPS * m_nSecond[m_nNotes]) && m_bFade == false)
	{
		// �����ɂ������m�[�c�̐���
		if (m_NotesType[m_nNotes] == "RIGHT_ARROW")
		{
			CNotes::Create(D3DXVECTOR3(SCREEN_CENTER_X, 100.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), m_NotesType[m_nNotes]);
		}
		else if (m_NotesType[m_nNotes] == "LEFT_ARROW")
		{
			CNotes::Create(D3DXVECTOR3(SCREEN_CENTER_X, 100.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), m_NotesType[m_nNotes]);
		}
		else if (m_NotesType[m_nNotes] == "UP_ARROW")
		{
			CNotes::Create(D3DXVECTOR3(SCREEN_CENTER_X, 100.0f, 0.0f), D3DXVECTOR2(50.0f, 100.0f), m_NotesType[m_nNotes]);
		}
		else if (m_NotesType[m_nNotes] == "DOWN_ARROW")
		{
			CNotes::Create(D3DXVECTOR3(SCREEN_CENTER_X, 100.0f, 0.0f), D3DXVECTOR2(50.0f, 100.0f), m_NotesType[m_nNotes]);
		}
		if (m_nNotes <= (m_nNotesNum - 1))
		{
			m_nNotes++;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}