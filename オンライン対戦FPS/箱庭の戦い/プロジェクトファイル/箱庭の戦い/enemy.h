//=============================================================================
//
// �G���� [enemy.h]
// Author : �H������
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "communicationdata.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_HEIGHT (80.0f)	// �����̍���
#define ENEMY_RADIUS (25.0f)	// �����̔��a
#define MAX_LIFE (100.0f)	// �̗�
#define MAX_STOCK (10)	// �c�C��

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemy : public CScene
{
public:
	CEnemy(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);	// �f�t�H���g�R���X�g���N�^
	~CEnemy();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	int GetStock(void) { return m_nStock; }	// �X�g�b�N�̎擾
	CCommunicationData::COMMUNICATION_DATA *GetCommuData(void) { return m_CommuData.GetCmmuData(); }	// �ʐM�f�[�^�̎擾
	bool ToBulletCollision(D3DXVECTOR3 pos, float fwigth, float fheight);	// �e�Ƃ̓����蔻��
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ����
	static void Recv(void);	// ���V�[�u�X���b�h
private:
	void Attack(void);	// �U��
	void Move(void);	// �ړ�
	void Motion(void);	// ���[�V����
	void StockCnt(void);	// �X�g�b�N�J�E���^
	static CCommunicationData m_CommuData;	// �ʐM�f�[�^
	vector<CModel*> m_pModel;	// ���f��
	D3DXVECTOR3 m_Pos;	// �ʒu
	D3DXVECTOR3 m_PosOld;	// �O��̈ʒu
	D3DXVECTOR3 m_Rot;	// ����
	D3DXMATRIX m_MtxWold;	// ���[���h�}�g���b�N�X
	int m_nParts;	// �p�[�c��
	int m_nStock = MAX_STOCK;	// �c�C
};

#endif