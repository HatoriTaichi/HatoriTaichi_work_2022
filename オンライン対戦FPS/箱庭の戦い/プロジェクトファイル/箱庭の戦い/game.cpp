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
#include "meshfloo.h"
#include "enemy.h"
#include "player.h"
#include "model.h"
#include "tcp_client.h"
#include "singlemodel.h"
#include "sound.h"
#include "meshsphere.h"
#include "camera.h"
#include "manager.h"
#include "counter.h"
#include "textureobj.h"
#include "sound.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	bool m_bDoOnece = false;
	bool m_bShow = false;
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
	CTcpClient *pClient = CManager::GetTcpClient();	// �ʐM�N���X�̎擾
	FILE *pFile;	// �t�@�C���̃|�C���^
	D3DXVECTOR3 Pos;	// �ʒu
	D3DXVECTOR3 Rot;	// ����
	D3DXVECTOR3 Scale;	// �X�P�[��
	char aFile[MAX_CHARDATA][MAX_CHARDATA * 2];	// �t�@�C���̕����o�b�t�@
	char RecvData[MAX_CHARDATA];	// ��M�f�[�^
	int nNumber;	// �ԍ�

	// ��M
	pClient->Recv(&RecvData[0], sizeof(int));
	memcpy(&nNumber, &RecvData[0], sizeof(int));

	// �t�@�C�����J��
	pFile = fopen("data/Txtdata/stagedata.txt", "r");

	// �t�@�C�����J���Ă�����
	if (pFile != NULL)
	{
		// �������[�v
		while (true)
		{
			// �������擾
			fscanf(pFile, "%s", &aFile[0]);

			// MODEL_NUM�̕��������������
			if (strcmp(aFile[0], "MODEL_NUM") == 0)
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nMaxModel);
			}
			// SET_MODEL�̕��������������
			if (strcmp(aFile[0], "SET_MODEL") == 0)
			{
				// �������[�v
				while (true)
				{
					// �������擾
					fscanf(pFile, "%s", &aFile[0]);

					// MODEL_INDX�̕��������������
					if (strcmp(aFile[0], "MODEL_INDX") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &m_nType);
					}
					// POS�̕��������������
					else if (strcmp(aFile[0], "POS") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f%f%f", &Pos.x, &Pos.y, &Pos.z);
					}
					// ROT�̕��������������
					else if (strcmp(aFile[0], "ROT") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f%f%f", &Rot.x, &Rot.y, &Rot.z);
					}
					// RSCALE�̕��������������
					else if (strcmp(aFile[0], "RSCALE") == 0)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f%f%f", &Scale.x, &Scale.y, &Scale.z);
					}
					// END_MODELSET�̕��������������
					else if (strcmp(aFile[0], "END_MODELSET") == 0)
					{
						// �擾�������Ő���
						m_pSingleModel.push_back(CSingleModel::Create(Pos, Rot, Scale, (CModel::TYPE)m_nType));
						break;
					}
				}
			}
			//END�̕��������������
			else if (strcmp(aFile[0], "END") == 0)
			{
				break;
			}
		}
	}
	else
	{
		printf("�e�N�X�`���f�[�^���ǂݎ��܂���ł����B");
	}

	// �t�@�C�������
	fclose(pFile);

	// �X�e�[�W�̗v�f�̐���
	CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 32, 8, 3200.0f, "SKY");
	CMeshFloo::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20, 20, 4100.0, 4100.0f, "SEE");
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f + 50.0f, 0.0f), D3DXVECTOR3(250.0f, 175.0f, 0.0f), "PLAYER_DIVIDE");
	CUiObj::Create(D3DXVECTOR3(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT - 100.0f, 0.0f), D3DXVECTOR3(150.0f, 100.0f, 0.0f), "WEAPONFRAME");
	CUiObj::Create(D3DXVECTOR3((SCREEN_WIDTH - 150.0f), (SCREEN_HEIGHT - 100.0f) - 45.0f, 0.0f), D3DXVECTOR3(100.0f, 45.0f, 0.0f), "WEAPON_VECTOR");
	CUiObj::Create(D3DXVECTOR3((SCREEN_WIDTH - 150.0f) + 50.0f, (SCREEN_HEIGHT - 100.0f) + 50.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "AMMOFRAME");
	CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), "BULLET");
	m_pMaxAmmo = CCounter::Create(D3DXVECTOR3(((SCREEN_WIDTH - 150.0f) + 50.0f) + 20.0f, ((SCREEN_HEIGHT - 100.0f) + 50.0f) + 15.0f, 0.0f), D3DXVECTOR3(15.0f, 25.0f, 0.0f), 2, "NUMBER_00");
	m_pMaxAmmo->AddCounter(30);
	m_pAmmo = CCounter::Create(D3DXVECTOR3(((SCREEN_WIDTH - 150.0f) + 50.0f) - 60.0f, ((SCREEN_HEIGHT - 100.0f) + 50.0f) - 15.0f, 0.0f), D3DXVECTOR3(15.0f, 25.0f, 0.0f), 2, "NUMBER_00");
	m_pAmmo->AddCounter(30);
	m_pKiilCount.push_back(CCounter::Create(D3DXVECTOR3(SCREEN_CENTER_X + 70.0f, 0.0f + 50.0f, 0.0f), D3DXVECTOR3(45.0f, 50.0f, 0.0f), 2, "NUMBER_P1"));
	m_pKiilCount.push_back(CCounter::Create(D3DXVECTOR3(SCREEN_CENTER_X - 170.0f, 0.0f + 50.0f, 0.0f), D3DXVECTOR3(45.0f, 50.0f, 0.0f), 2, "NUMBER_P2"));

	// �v���C���[�ԍ��ŃX�|�[���ʒu��ς���
	if (nNumber == 1)
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(-650.0f, 100.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else if (nNumber == 2)
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(650.0f, 100.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	m_pPlayer->SetIndex(nNumber);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CGame::Uninit(void)
{
	// �j��
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	// �}�E�X�̏���
	MouseProcess();

	// ���s����
	WinOrLoss();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// ���s
//=============================================================================
void CGame::WinOrLoss(void)
{
	CSound *pSound = CManager::GetSound();	// �T�E���h�̎擾
	CCommunicationData::COMMUNICATION_DATA *pData = m_pEnemy->GetCommuData();	// �ʐM�f�[�^�̎擾
	int nStock[MAX_PLAYER];	// �X�g�b�N

	// �X�g�b�N���擾
	nStock[0] = m_pPlayer->GetStock();
	nStock[1] = m_pEnemy->GetStock();

	// ��������
	if (nStock[0] <= 0 && m_bDoOnece == false)
	{
		// �Đ�
		pSound->PlaySound(CSound::X2SOUND_LABEL::LOSE);

		// �����̐���
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f + 250.0f, 0.0f), D3DXVECTOR3(150.0f, 75.0f, 0.0f), "LOSE");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f + 475.0f, 0.0f), D3DXVECTOR3(250.0f, 60.0f, 0.0f), "RESTART");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X - 200.0f, 0.0f + 760.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "YES");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X + 200.0f, 0.0f + 760.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "NO");
		pData->Player.bPushKey = false;
		for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
		{
			pData->Bullet[nCnt].bUse = false;
		}
		m_pPlayer->SetEndBattle(true);
		m_bDoOnece = true;
	}
	// ��������
	else if (nStock[1] <= 0 && m_bDoOnece == false)
	{
		// �Đ�
		pSound->PlaySound(CSound::X2SOUND_LABEL::WIN);

		// �����̐���
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f + 250.0f, 0.0f), D3DXVECTOR3(150.0f, 75.0f, 0.0f), "WIN");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f + 475.0f, 0.0f), D3DXVECTOR3(250.0f, 60.0f, 0.0f), "RESTART");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X - 200.0f, 0.0f + 760.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "YES");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X + 200.0f, 0.0f + 760.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "NO");
		pData->Player.bPushKey = false;
		for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
		{
			pData->Bullet[nCnt].bUse = false;
		}
		m_pPlayer->SetEndBattle(true);
		m_bDoOnece = true;
	}
}

//=============================================================================
// �}�E�X�֘A
//=============================================================================
void CGame::MouseProcess(void)
{
	CTcpClient *pClient = CManager::GetTcpClient();	// �ʐM�N���X�̎擾

	// �o�g�����I����ĂȂ�������
	if (m_pPlayer->GetEndBattle() == false)
	{
		// ���S�Ƀ}�E�X���Œ�
		SetCursorPos(SCREEN_CENTER_X, SCREEN_CENTER_Y);

		// �J�[�\��������
		if (m_bShow == false)
		{
			ShowCursor(FALSE);
			m_bShow = true;
		}
	}
	else
	{
		// �J�[�\�����o��
		if (m_bShow == true)
		{
			pClient->Uninit();

			ShowCursor(TRUE);
			m_bShow = false;
		}
	}
}