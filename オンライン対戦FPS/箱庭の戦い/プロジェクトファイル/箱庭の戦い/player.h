//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �H������
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "communicationdata.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DUSH_SPEED (5.0f)
#define NORMAL_SPEED (1.0f)
#define PLAYER_HEIGHT (60.0f)	// �����̍���
#define PLAYER_RADIUS (25.0f)	// �����̔��a
#define MAX_LIFE (100.0f)	// �̗�
#define RECOVERY_TIME (FPS * 3)	// �񕜂���܂ł̎���
#define MAX_STOCK (10)	// �c�C��

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;
class CUiObj;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CScene
{
public:
	CPlayer(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// �f�t�H���g�R���X�g���N�^
	~CPlayer();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	bool ToBulletCollision(D3DXVECTOR3 pos, float fwigth, float fheight);	// �e�Ƃ̓����蔻��
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ����
	void SetIndex(int nIndex) { CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData(); pData->Player.nNumber = nIndex; }	// �v���C���[�ԍ��̐ݒ�
	void SetEndBattle(bool bEnd) { m_bEndBattle = bEnd; }	// �o�g���I���t���O�̂̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_Pos; }	// �ʒu�̎擾
	D3DXVECTOR3 GetRot(void) { return m_Rot; }	// �����̎擾
	bool GetEndBattle(void) { return m_bEndBattle; }	// �o�g���I���t���O�̎擾
	int GetStock(void) { return m_nStock; }	// �X�g�b�N�̂̎擾
	CCommunicationData::COMMUNICATION_DATA *GetCommuData(void) { return m_CommuData.GetCmmuData(); }	// �ʐM�f�[�^�̎擾
private:
	void Move(void);	// �ړ�
	void Attack(void);	// �U��
	void Motion(void);	// ���[�V����
	void Damage(void);	// �_���[�W
	void CntStock(void);	// �X�g�b�N�J�E���^
	CCommunicationData m_CommuData;	// �ʐM�f�[�^�N���X
	CModel::MOSTION m_Motion;	// ���[�V�����̎��
	vector<CModel*> m_pModel;	// ���f��
	vector<CUiObj*> m_Boold;	// ��
	D3DXVECTOR3 m_Pos;	// �ʒu
	D3DXVECTOR3 m_PosOld;	// �O��ʒu
	D3DXVECTOR3 m_Rot;	// ����
	D3DXMATRIX m_MtxWold;	// ���[���h�}�g���b�N�X
	int m_nParts;	// �p�[�c��
	int m_nDamageTime;	// �_���[�W�̈�莞�ԃJ�E���g
	int m_nStock = MAX_STOCK;	// �c�C
	int m_nRateTime;	// ���[�g
	int m_nReloadCnt;	// �����[�h����
	int m_nIvbTime;	// ���G����
	float m_fMoveSpeed;	// �ړ��X�s�[�h
	float m_fLife = MAX_LIFE;	// �̗�
	bool m_bRespawn;	// ���X�Œ�
	bool m_bDamageTime;	// �_���[�W��莞�ԃ_���[�W
	bool m_bHitDamage;	// �_���[�W
	bool m_bAttack;	// �U�����Ă邩
	bool m_bEndBattle;	// ���s
	bool m_bShoot;	// �łĂ邩
	bool m_bReload;	// �����[�h����
	bool m_bInvincible;	// ���G��
};

#endif