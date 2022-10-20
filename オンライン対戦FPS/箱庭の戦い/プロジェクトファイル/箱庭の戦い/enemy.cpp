//=============================================================================
//
// ���f���e�X�g���� [modeltester.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy.h"
#include "enemybullet.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "camera.h"
#include "tcp_client.h"
#include "singlemodel.h"
#include "game.h"
#include "counter.h"
#include "motion.h"
#include "sound.h"
#include "gunfire.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CCommunicationData CEnemy::m_CommuData;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(LAYER_TYPE Layer) : CScene(Layer)
{
	D3DXVECTOR3 m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int m_nParts = 0;
	int m_nStock = MAX_STOCK;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
	
}

//=============================================================================
// ���f���̏���������
//=============================================================================
HRESULT CEnemy::Init(void)
{
	FILE *pFile;	// �t�@�C���̃|�C���^
	D3DXVECTOR3 Pos;	// �ʒu
	D3DXVECTOR3 Rot;	// ����
	char aFile[128];	// �t�@�C���̕�����o�b�t�@
	vector<int> Parent;	// �e�̃C���f�b�N�X
	int nKey = 0;	// �L�[
	int nCntKey = 0;	// �L�[�J�E���g
	int nFrame = 0;	// �t���[��
	int nCntModel = 0;	// ���f���J�E���g
	int nCntMosion = 0;	// ���[�V�����J�E���g
	bool bLoop;	// ���[�v

	// �t�@�C�����J��
	pFile = fopen("data/Txtdata/player.txt", "r");
	
	// �t�@�C�����J���Ă�����
	if (pFile != NULL)
	{
		// �������[�v
		while (true)
		{
			// �t�@�C���̕�������擾
			fscanf(pFile, "%s", &aFile[0]);

			// NUM_MODEL�̕��������������
			if (strcmp(&aFile[0], "NUM_MODEL") == 0)
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nParts);
				for (int nCnt = 0; nCnt < m_nParts; nCnt++)
				{
					Parent.push_back(0);
				}
				break;
			}
		}
		// �p�[�c�����̃��[�v
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			// ���f���𐶐�
			m_pModel.push_back(CModel::Create((CModel::TYPE)nCnt, D3DXVECTOR3(1.0f, 1.0f, 1.0f), &Parent[nCnt], pFile));
		}
		// �p�[�c�����̃��[�v
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			// �e�̐ݒ�
			if (Parent[nCnt] == -1)
			{
				m_pModel[nCnt]->SetPrent(NULL);
			}
			else
			{
				m_pModel[nCnt]->SetPrent(m_pModel[Parent[nCnt]]);
			}
		}
		// �������[�v
		while (true)
		{
			// �t�@�C���̕�������擾
			fscanf(pFile, "%s", &aFile[0]);

			// MOTIONSET�̕��������������
			if (strcmp(&aFile[0], "MOTIONSET") == 0)
			{
				int nLoop;
				fscanf(pFile, "%*s%*s%d", &nLoop);
				fscanf(pFile, "%*s%*s%*s%*s");
				fscanf(pFile, "%*s%*s%d", &nKey);
				bLoop = nLoop;

				for (int nCnt = 0; nCnt < m_nParts; nCnt++)
				{
					CModel::MOTIONINFO *pMosion = m_pModel[nCnt]->GetMotion(nCntMosion);
					for (int nCntKey = 0; nCntKey < nKey; nCntKey++)
					{
						pMosion->aKeyinfo.push_back(new CModel::KEYINFO);
					}
				}
			}
			// KEYSET�̕��������������
			if (strcmp(&aFile[0], "KEYSET") == 0)
			{
				fscanf(pFile, "%*s%*s%*s%*s%*s%*s%*s%*s%*s%*s");
				fscanf(pFile, "%*s%*s%d", &nFrame);
				while (true)
				{
					fscanf(pFile, "%s", &aFile[0]);
					// KEY�̕��������������
					if (strcmp(&aFile[0], "KEY") == 0)
					{
						fscanf(pFile, "%*s%*s%*s%*s%*s%*s");
						fscanf(pFile, "%*s%*s%f%f%f", &Pos.x, &Pos.y, &Pos.z);
						fscanf(pFile, "%*s%*s%f%f%f", &Rot.x, &Rot.y, &Rot.z);
					}
					// END_KEY�̕��������������
					if (strcmp(&aFile[0], "END_KEY") == 0)
					{
						CModel::MOTIONINFO *pMosion = m_pModel[nCntModel]->GetMotion(nCntMosion);

						pMosion->bLoop = bLoop;
						pMosion->nNumKey = nKey;
						pMosion->aKeyinfo[nCntKey]->fFrame = nFrame;

						pMosion->aKeyinfo[nCntKey]->aKey.fPosX = m_pModel[nCntModel]->GetPos().x + Pos.x;
						pMosion->aKeyinfo[nCntKey]->aKey.fPosY = m_pModel[nCntModel]->GetPos().y + Pos.y;
						pMosion->aKeyinfo[nCntKey]->aKey.fPosZ = m_pModel[nCntModel]->GetPos().z + Pos.z;

						pMosion->aKeyinfo[nCntKey]->aKey.fRotX = m_pModel[nCntModel]->GetRot().x + Rot.x;
						pMosion->aKeyinfo[nCntKey]->aKey.fRotY = m_pModel[nCntModel]->GetRot().y + Rot.y;
						pMosion->aKeyinfo[nCntKey]->aKey.fRotZ = m_pModel[nCntModel]->GetRot().z + Rot.z;

						nCntModel++;
					}
					// END_KEYSET�̕��������������
					if (strcmp(&aFile[0], "END_KEYSET") == 0)
					{
						nCntModel = 0;
						nCntKey++;
						break;
					}
				}
			}
			// END_MOTIONSET�̕��������������
			if (strcmp(&aFile[0], "END_MOTIONSET") == 0)
			{
				nCntModel = 0;
				nCntKey = 0;
				nCntMosion++;
			}
			// END_SCRIPT�̕��������������
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
	}
	else
	{
		printf("���f���f�[�^���ǂݎ��܂���ł����B");
	}

	// �t�@�C�������
	fclose(pFile);

	// �X���b�h�𐶐�
	std::thread th(Recv);

	// �X���b�h��؂藣��
	th.detach();

	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CEnemy::Uninit(void)
{
	// �p�[�c�����̃��[�v
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		// �j��
		m_pModel[nCnt]->Uninit();
		delete m_pModel[nCnt];
		m_pModel[nCnt] = NULL;
	}
}

//=============================================================================
// ���f���̍X�V����
//=============================================================================
void CEnemy::Update(void)
{
	// �ړ�����
	Move();

	// �U������
	Attack();

	// ���[�V����
	Motion();

	// �X�g�b�N
	StockCnt();
}

//=============================================================================
// ���f���̕`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; // �f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X���擾����

	//--------------------------------------
	//�v���C���[(���_)�̃}�g���b�N�X�̐ݒ�
	//--------------------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&m_MtxWold);	//�}�g���b�N�X������

	//�����̐ݒ�
	D3DXMatrixRotationYawPitchRoll(	&mtxRot,
									m_Rot.y,
									m_Rot.x,
									m_Rot.z);

	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxRot);
	//�ʒu
	D3DXMatrixTranslation(	&mtxTrans,
							m_Pos.x,
							m_Pos.y,
							m_Pos.z);

	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxTrans);
	//�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(	D3DTS_WORLD,
							&m_MtxWold);

	// �p�[�c�����̃��[�v
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		// �`��
		m_pModel[nCnt]->Draw();
	}
}

//=============================================================================
// �e�Ƃ̓����蔻��
//=============================================================================
bool CEnemy::ToBulletCollision(D3DXVECTOR3 pos, float fwigth, float fheight)
{
	D3DXVECTOR3 posdfrc;	// ����
	int nMyR = ENEMY_RADIUS;	// ���a
	float fposdfrcX;	// �����̔��a
	bool bHit = false;	// ����������

	// ����
	posdfrc.x = m_Pos.x - pos.x;
	posdfrc.z = m_Pos.z - pos.z;

	posdfrc.x = posdfrc.x * posdfrc.x;

	fposdfrcX = posdfrc.x + posdfrc.z;

	fposdfrcX = sqrtf(fposdfrcX);

	// ���a�̒���������
	if (m_Pos.y <= pos.y + fheight / 2 &&
		m_Pos.y + ENEMY_HEIGHT >= pos.y - fheight / 2 &&
		fposdfrcX < nMyR)
	{
		bHit = true;
	}
	return bHit;
}

//=============================================================================
// ���f���̐���
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pEnemy = NULL;	// �G�̃|�C���^

	// NULL��������
	if (pEnemy == NULL)
	{
		// ����
		pEnemy = new CEnemy;
	}

	// �����̑��s
	pEnemy->m_Pos = pos;
	pEnemy->m_Rot = rot;

	// ��������Ă�����
	if (pEnemy != NULL)
	{
		// ������
		pEnemy->Init();
	}
	return pEnemy;
}

//=============================================================================
// ���V�[�u�X���b�h
//=============================================================================
void CEnemy::Recv(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// �ʐM�f�[�^�̎擾

	// �q�����Ă���Ԃ̓��[�v
	while (pData->bConnect == false)
	{
		CTcpClient *pTcp = CManager::GetTcpClient();	// �ʐM�N���X�̎擾
		char aRecv[MAX_COMMUDATA];	// ��M�f�[�^

		// ��M
		int nRecvSize = pTcp->Recv(&aRecv[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
		
		// ��M�f�[�^������������
		if (nRecvSize < 0)
		{
			if (pTcp != NULL)
			{
				pTcp->Uninit();
				pTcp = NULL;
				break;
			}
		}
		// �R�s�[
		memcpy(pData, &aRecv[0], (int)sizeof(CCommunicationData::COMMUNICATION_DATA));
	}
}

//=============================================================================
// �U��
//=============================================================================
void CEnemy::Attack(void)
{
	CSound *pSound = CManager::GetSound();	// �T�E���h�̎擾
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// �ʐM�f�[�^�̎擾
	D3DXMATRIX WorldPos = m_pModel[11]->GetMatrix();	// ���f���̃}�g���b�b�N�X�̎擾

	// �e�̑������̃��[�v
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		// �L�[�������Ă� && �g���Ă�����
		if (pData->Player.bPushKey == true && pData->Bullet[nCnt].bUse == true)
		{
			// �Đ�
			pSound->PlaySound(CSound::X2SOUND_LABEL::SHOOT);

			// �e�̐���
			CEnemyBullet::Create(D3DXVECTOR3(WorldPos._41, WorldPos._42, WorldPos._43), pData->Bullet[nCnt].Rot, D3DXVECTOR3(5.0f, 5.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "BULLET", 1.0f);

			// �}�Y���t���b�V���̐���
			CGunFire::Create(D3DXVECTOR3(WorldPos._41, WorldPos._42, WorldPos._43), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "MASLE_FLASH");
			pData->Bullet[nCnt].bUse = false;
			break;
		}
	}
}

//=============================================================================
// �ړ�
//=============================================================================
void CEnemy::Move(void)
{
	CSound *pSound = CManager::GetSound();	// �T�E���h�̎擾
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// �ʐM�f�[�^�̎擾
	int nMaxModel = CManager::GetGame()->GetMaxModel();	// ���f���̑������擾

	// �ʒu���ς���Ă�����
	if (m_PosOld != m_Pos)
	{
		// �Đ�
		pSound->PlaySound(CSound::X2SOUND_LABEL::FOOT_STEP);
	}

	// �O��̈ʒu��ۑ�
	m_PosOld = m_Pos;

	// �ʐM�f�[�^�ɑ��
	m_Pos = pData->Player.Pos;
	m_Rot = pData->Player.Rot;
}

//=============================================================================
// ���[�V����
//=============================================================================
void CEnemy::Motion(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// �ʐM�f�[�^�̎擾

	// ���[�V�����ɑΉ��������[�V�������Đ�
	switch (pData->Player.Motion)
	{
	case CCommunicationData::MOSTION::NEUTRAL:
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)CModel::MOSTION::NEUTRAL);
			D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
			D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

			CMotion::PlayMotin(Motion, &Pos, &Rot);
			m_pModel[nCnt]->SetPos(Pos);
			m_pModel[nCnt]->SetRot(Rot);
		}
		break;
	case CCommunicationData::MOSTION::WORK:
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)CModel::MOSTION::WORK);
			D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
			D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

			CMotion::PlayMotin(Motion, &Pos, &Rot);
			m_pModel[nCnt]->SetPos(Pos);
			m_pModel[nCnt]->SetRot(Rot);
		}
		break;
	case CCommunicationData::MOSTION::BUCK_WORK:
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)CModel::MOSTION::BUCK_WORK);
			D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
			D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

			CMotion::PlayMotin(Motion, &Pos, &Rot);
			m_pModel[nCnt]->SetPos(Pos);
			m_pModel[nCnt]->SetRot(Rot);
		}
		break;
	case CCommunicationData::MOSTION::ATTACK:
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)CModel::MOSTION::ATTACK);
			D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
			D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

			CMotion::PlayMotin(Motion, &Pos, &Rot);
			m_pModel[nCnt]->SetPos(Pos);
			m_pModel[nCnt]->SetRot(Rot);
		}
		break;
	}
}

//=============================================================================
// �X�g�b�N�J�E���^
//=============================================================================
void CEnemy::StockCnt(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// �ʐM�f�[�^�̎擾

	if (pData->Player.nNumber != 0)
	{
		CCounter *pCounter = CManager::GetGame()->GetCounter(pData->Player.nNumber - 1);
		m_nStock = pData->Player.nStock;

		pCounter->SetCounterNum(m_nStock);
	}
}