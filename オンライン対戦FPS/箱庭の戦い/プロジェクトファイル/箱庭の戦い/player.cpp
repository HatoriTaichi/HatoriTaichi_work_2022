//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player.h"
#include "model.h"
#include "tcp_client.h"
#include "renderer.h"
#include "manager.h"
#include "motion.h"
#include "texture.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "playerbullet.h"
#include "camera.h"
#include "singlemodel.h"
#include "manager.h"
#include "game.h"
#include "textureobj.h"
#include "counter.h"
#include "gunfire.h"
#include "sound.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(LAYER_TYPE Layer) : CScene(Layer)
{
	m_Boold.push_back(CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), "BLOOD_00"));
	m_Boold.push_back(CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), "BLOOD_01"));
	m_Boold.push_back(CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), "BLOODMASK"));
	m_Boold[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_Boold[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	D3DXVECTOR3 m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int m_nParts = 0;
	int m_nDamageTime = 0;
	int m_nStock = MAX_STOCK;
	int m_nRateTime = 0;
	int m_nReloadCnt = 0;
	float m_fMoveSpeed = 0;
	float m_fLife = MAX_LIFE;
	bool m_bRespawn = false;
	bool m_bDamageTime = false;
	bool m_bHitDamage = false;
	bool m_bAttack = false;
	bool m_bEndBattle = false;
	bool m_bShoot = true;
	bool m_bReload = false;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ���f���̏���������
//=============================================================================
HRESULT CPlayer::Init(void)
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

	return S_OK;
}

//=============================================================================
// ���f���̏I������
//=============================================================================
void CPlayer::Uninit(void)
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
void CPlayer::Update(void)
{
	CTcpClient *pTcp = CManager::GetTcpClient();	// �ʐM�N���X�̎擾
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// �ʐM�f�[�^�N���X�̎擾
	int nMaxModel = CManager::GetGame()->GetMaxModel();	// ���f���̑������擾

	// �O��̈ʒu��ۑ�
	m_PosOld = m_Pos;

	// �ړ�����
	Move();

	// ���[�V��������
	Motion();

	// �_���[�W����
	Damage();

	// �X�g�b�N����
	CntStock();

	// �U������
	Attack();

	// ���X�|�[�����ĂȂ�������
	if (m_bRespawn == false)
	{
		// ���f���̑������̃��[�v
		for (int nCnt = 0; nCnt < nMaxModel; nCnt++)
		{
			// ���f�����擾
			CModel *pModel = CManager::GetGame()->GetModel(nCnt)->GetModel();

			// �����蔻��
			pModel->BoxCollision(&m_Pos, m_PosOld);
		}
	}
	// ����ȊO
	else
	{
		m_bRespawn = false;
	}

	// �T�[�o�[��send
	pTcp->Send((char*)pData, sizeof(CCommunicationData::COMMUNICATION_DATA));
	pData->Player.bPushKey = false;
}

//=============================================================================
// ���f���̕`�揈��
//=============================================================================
void CPlayer::Draw(void)
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
bool CPlayer::ToBulletCollision(D3DXVECTOR3 pos, float fwigth, float fheight)
{
	D3DXVECTOR3 posdfrc;	// ����
	int nMyR = PLAYER_RADIUS;	// ���a
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
		m_Pos.y + PLAYER_HEIGHT >= pos.y - fheight / 2 &&
		fposdfrcX < nMyR)
	{
		// ���G���Ԃ���Ȃ�������
		if (m_bInvincible == false)
		{
			m_fLife -= 3.0f;
			m_nDamageTime = 0;
			m_bDamageTime = true;
			m_bHitDamage = true;
			bHit = true;
		}
	}
	return bHit;
}

//=============================================================================
// ���f���̐���
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = NULL;	// �v���C���[�̃|�C���^

	// NULL��������
	if (pPlayer == NULL)
	{
		// ����
		pPlayer = new CPlayer;
	}

	// �����̑��
	pPlayer->m_Pos = pos;
	pPlayer->m_Rot = rot;

	// ��������Ă�����
	if (pPlayer != NULL)
	{
		// ������
		pPlayer->Init();
	}
	return pPlayer;
}

//=============================================================================
// �ړ�
//=============================================================================
void CPlayer::Move(void)
{
	CCamera *pCamera = CManager::GetCamera();	// �J�����̎擾
	CKeyboard *pKey = CManager::GetKeyboard();	// �L�[�{�[�h�̎擾
	CMouse *pMouse = CManager::GetMouse();	// �}�E�X�̎擾
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// �ʐM�f�[�^�N���X�̎擾
	D3DXVECTOR3 Rot = pCamera->GetRot();	// �J�����̌����̎擾
	float fLong = pCamera->GetDestance();	// �J�����̒����̎擾
	float fMoveRot;	// �ړ�����
	m_Rot.y = Rot.x;	// �J�����̌����̑��
	m_Rot.y += D3DXToRadian(180.0f);	// 180�x��]
	fMoveRot = m_Rot.y - D3DXToRadian(180.0f);	// �ړ������̑��

	if (m_bEndBattle == false)
	{
#if _DEBUG
		if (pKey->GetPress(pKey->LSHIFT) == true)
		{
			m_fMoveSpeed = DUSH_SPEED;
			m_Pos.y -= 1.0f;
		}
		else if (pKey->GetPress(pKey->LSHIFT) == false)
		{
			m_fMoveSpeed = NORMAL_SPEED;
		}
#endif
		// �L�[�ɂ���Ĉړ�
		if (pKey->GetPress(pKey->W) == true)
		{
			m_Pos.x = m_Pos.x + sinf(fMoveRot) * m_fMoveSpeed;
			m_Pos.z = m_Pos.z + cosf(fMoveRot) * m_fMoveSpeed;
		}
		else if (pKey->GetPress(pKey->S) == true)
		{
			m_Pos.x = m_Pos.x - sinf(fMoveRot) * m_fMoveSpeed;
			m_Pos.z = m_Pos.z - cosf(fMoveRot) * m_fMoveSpeed;
		}
		if (pKey->GetPress(pKey->A) == true)
		{
			m_Pos.x = m_Pos.x - cosf(fMoveRot) * m_fMoveSpeed;
			m_Pos.z = m_Pos.z + sinf(fMoveRot) * m_fMoveSpeed;
		}
		else if (pKey->GetPress(pKey->D) == true)
		{
			m_Pos.x = m_Pos.x + cosf(fMoveRot) * m_fMoveSpeed;
			m_Pos.z = m_Pos.z - sinf(fMoveRot) * m_fMoveSpeed;
		}
		// �d�͂����Z
		m_Pos.y -= 1.0f;

		// ���ɍs����������
		if (m_Pos.y <= -50.0f)
		{
			m_bRespawn = true;
			m_nStock -= 1;
			if (pData->Player.nNumber == 1)
			{
				m_Pos = D3DXVECTOR3(-650.0f, 100.0f, -600.0f);
			}
			else
			{
				m_Pos = D3DXVECTOR3(650.0f, 100.0f, 600.0f);
			}
		}
	}

	// �ʐM�f�[�^�N���X�ɑ��
	pData->Player.Pos = m_Pos;
	pData->Player.Rot = m_Rot;
}

//=============================================================================
// �U��
//=============================================================================
void CPlayer::Attack(void)
{
	CSound *pSound = CManager::GetSound();	// �T�E���h�̎擾
	CKeyboard *pKey = CManager::GetKeyboard();	// �L�[�{�[�h�̎擾
	CMouse *pMouse = CManager::GetMouse();	// �}�E�X�̎擾
	CCamera *pCamera = CManager::GetCamera();	// �J�����̎擾
	CCounter *pCounter = CManager::GetGame()->GetAmmo();	// �c�i���̎擾
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// �ʐM�f�[�^�N���X�̎擾
	D3DXVECTOR3 Rot = pCamera->GetRot();	// �J�����̌����̎擾
	D3DXMATRIX WorldPos = m_pModel[11]->GetMatrix();	// ���f���̃}�g���b�b�N�X�̎擾
	float fNorRot = m_Rot.y - D3DXToRadian(180.0f);	// �������v�Z

	// �o�g�����I����ĂȂ�������
	if (m_bEndBattle == false)
	{
		// �e�̑������̃��[�v
		for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
		{
			// ���N���b�N && �e���g���Ė��������� && �c�i������������
			if (pMouse->GetPress(pMouse->LEFT_BOTTON) == true && pData->Bullet[nCnt].bUse == false && pCounter->GetCounterNum() != 0)
			{
				// �����Ă���
				if (m_bShoot == true)
				{
					// �Đ�
					pSound->PlaySound(CSound::X2SOUND_LABEL::SHOOT);
					Rot.y = Rot.y - 0.01f;
					pCamera->SetRot(Rot);
					pCounter->AddCounter(-1);
					m_bAttack = true;

					// �e�𐶐�
					CPlayerBullet::Create(D3DXVECTOR3(WorldPos._41, WorldPos._42, WorldPos._43), Rot, D3DXVECTOR3(5.0f, 5.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "BULLET", 1.0f);
					
					// �}�Y���t���b�V���̐���
					CGunFire::Create(D3DXVECTOR3(WorldPos._41, WorldPos._42, WorldPos._43), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "MASLE_FLASH");
					pData->Bullet[nCnt].Rot = Rot;
					m_bShoot = false;
					if (pData->Bullet[nCnt].bUse == false)
					{
						pData->Bullet[nCnt].bUse = true;
						break;
					}
				}
			}
		}
	}
	// �����Ė���������
	if (m_bShoot == false)
	{
		m_nRateTime++;
	}
	if (m_nRateTime >= (FPS / 15))
	{
		m_bShoot = true;
		m_nRateTime = 0;
	}
	// R����������
	if (pKey->GetTrigger(pKey->R) == true)
	{
		// �Đ�
		pSound->PlaySound(CSound::X2SOUND_LABEL::RELOAD);

		// �����[�h
		m_bReload = true;
	}
	// �����[�h���Ă���
	if (m_bReload == true)
	{
		m_nReloadCnt++;
		if (m_nReloadCnt >= (FPS * 1.5f))
		{
			pCounter->SetCounterNum(30);
			for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
			{
				pData->Bullet[nCnt].bUse = false;
			}
			m_bReload = false;
			m_nReloadCnt = 0;
		}
	}
	// ���N���b�N���ĂȂ�������
	if (pMouse->GetPress(pMouse->LEFT_BOTTON) == false)
	{
		pData->Player.bPushKey = false;
	}
	// ���N���b�N���Ă���
	else if (pMouse->GetPress(pMouse->LEFT_BOTTON) == true)
	{
		pData->Player.bPushKey = true;
	}
#if _DEBUG
	if (pKey->GetTrigger(pKey->J) == true)
	{
		m_nStock -= 1;
	}
#endif // _DEBUG

}

//=============================================================================
// ���[�V����
//=============================================================================
void CPlayer::Motion(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// �ʐM�f�[�^�̎擾
	CKeyboard *pKey = CManager::GetKeyboard();	// �L�[�{�[�h�̎擾

	// �U�����ĂȂ�������
	if (m_bAttack == false)
	{
		// �����Ė���������
		if (pKey->GetPress(pKey->W) == false &&
			pKey->GetPress(pKey->A) == false &&
			pKey->GetPress(pKey->S) == false &&
			pKey->GetPress(pKey->D) == false)
		{
			// ���[�V������ݒ�
			m_Motion = CModel::MOSTION::NEUTRAL;
			pData->Player.Motion = CCommunicationData::MOSTION::NEUTRAL;

			// �p�[�c�����̃��[�v
			for (int nCnt = 0; nCnt < m_nParts; nCnt++)
			{
				// ���[�V��������
				CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)m_Motion);
				D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
				D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

				CMotion::PlayMotin(Motion, &Pos, &Rot);
				m_pModel[nCnt]->SetPos(Pos);
				m_pModel[nCnt]->SetRot(Rot);
			}
		}
		// �O�i�����E�ړ����Ă���
		else if (pKey->GetPress(pKey->W) == true ||
				 pKey->GetPress(pKey->A) == true ||
				 pKey->GetPress(pKey->D) == true)
		{
			// ���[�V������ݒ�
			m_Motion = CModel::MOSTION::WORK;
			pData->Player.Motion = CCommunicationData::MOSTION::WORK;

			// �p�[�c�����̃��[�v
			for (int nCnt = 0; nCnt < m_nParts; nCnt++)
			{
				// ���[�V��������
				CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)m_Motion);
				D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
				D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

				CMotion::PlayMotin(Motion, &Pos, &Rot);
				m_pModel[nCnt]->SetPos(Pos);
				m_pModel[nCnt]->SetRot(Rot);
			}
		}
		// ��ނ��Ă�����
		else if (pKey->GetPress(pKey->S) == true)
		{
			// ���[�V������ݒ�
			m_Motion = CModel::MOSTION::BUCK_WORK;
			pData->Player.Motion = CCommunicationData::MOSTION::BUCK_WORK;

			// �p�[�c�����̃��[�v
			for (int nCnt = 0; nCnt < m_nParts; nCnt++)
			{
				// ���[�V��������
				CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)m_Motion);
				D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
				D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

				CMotion::PlayMotin(Motion, &Pos, &Rot);
				m_pModel[nCnt]->SetPos(Pos);
				m_pModel[nCnt]->SetRot(Rot);
			}
		}
	}
	// �����Ă�����
	else if (m_bShoot == true)
	{
		// ���[�V������ݒ�
		m_Motion = CModel::MOSTION::ATTACK;
		pData->Player.Motion = CCommunicationData::MOSTION::ATTACK;

		// �p�[�c�����̃��[�v
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			// ���[�V��������
			CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)m_Motion);
			D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
			D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

			if (CMotion::PlayMotin(Motion, &Pos, &Rot) == false)
			{
				m_pModel[nCnt]->SetPos(Pos);
				m_pModel[nCnt]->SetRot(Rot);
			}
			else
			{
				m_bAttack = false;
			}
		}
	}
}

//=============================================================================
// �_���[�W
//=============================================================================
void CPlayer::Damage(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// �ʐM�f�[�^�̎擾

	// ���G�Ȃ�
	if (m_bInvincible == true)
	{
		m_nIvbTime++;
	}
	// ���Ԃ܂Ŗ��G
	if (m_nIvbTime >= (FPS * 1.5))
	{
		m_bInvincible = false;
	}
	// ���C�t�����Ă��� && �_���[�W���󂯂Ă�����
	if (m_fLife < MAX_LIFE && m_bDamageTime == true)
	{
		m_nDamageTime++;
	}

	// ���ԂɂȂ�����
	if (m_nDamageTime >= RECOVERY_TIME)
	{
		// �_���[�W���󂯂ĂȂ�
		m_nDamageTime = 0;
		m_bDamageTime = false;
	}

	// �_���[�W���󂯂ĂȂ�������
	if (m_bDamageTime == false)
	{
		// ��
		m_fLife += 0.1f;
	}

	// �񕜐��ɉ����ĉ�ʂ�ς���
	if (m_fLife >= 80.0f)
	{
		m_Boold[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
	}
	if (m_fLife >= MAX_LIFE)
	{
		m_Boold[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	if (m_fLife >= MAX_LIFE)
	{
		m_fLife = MAX_LIFE;
	}

	if (m_fLife < MAX_LIFE && m_fLife >= 80.0f && m_bHitDamage == true)
	{
		m_Boold[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
		m_bHitDamage = false;
	}
	else if (m_fLife < 80.0f && m_bHitDamage == true)
	{
		m_Boold[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
		m_bHitDamage = false;
	}

	// ���񂾂�
	if (m_fLife <= 0.0f)
	{
		m_fLife = MAX_LIFE;
		m_bRespawn = true;
		m_bHitDamage = false;
		m_bDamageTime = false;
		m_bInvincible = true;
		m_nStock -= 1;
		m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		if (pData->Player.nNumber == 1)
		{
			m_Pos = D3DXVECTOR3(-650.0f, 100.0f, -600.0f);
		}
		else
		{
			m_Pos = D3DXVECTOR3(650.0f, 100.0f, 600.0f);
		}
	}

	// �X�g�b�N��ʐM�f�[�^�ɑ��
	pData->Player.nStock = m_nStock;
}

//=============================================================================
// �X�g�b�N�J�E���^
//=============================================================================
void CPlayer::CntStock(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();	// �ʐM�f�[�^�̎擾

	if (pData->Player.nNumber != 0)
	{
		CCounter *pCounter = CManager::GetGame()->GetCounter(pData->Player.nNumber - 1);
		pCounter->SetCounterNum(m_nStock);
	}
}