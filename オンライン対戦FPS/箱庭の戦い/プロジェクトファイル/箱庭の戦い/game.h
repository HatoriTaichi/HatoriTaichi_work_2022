//=============================================================================
//
// �Q�[�� [game.h]
// Author : �H������
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYER (2)	// �v���C���[�̐�

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
class CEnemy;
class CSingleModel;
class CSound;
class CCounter;
class CUiObj;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGame
{
public:
	CGame();	// �f�t�H���g�R���X�g���N�^
	~CGame();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);		// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	CPlayer *GetPlayer(void) { return m_pPlayer; }	// �v���C���[�̎擾
	CEnemy *GetEnemy(void) { return m_pEnemy; }	// �G�̎擾
	CSingleModel *GetModel(int nCnt) {return m_pSingleModel[nCnt]; }	// ���f���̎擾
	int GetMaxModel(void) { return m_nMaxModel; }	// ���f���ő吔�̎擾
	CCounter *GetCounter(int nIndex) { return m_pKiilCount[nIndex]; }	// �J�E���^�[�̎擾
	CCounter *GetAmmo(void) { return m_pAmmo; }	// �e���̎擾
private:
	void WinOrLoss(void);	// ���s
	void MouseProcess(void);	// �}�E�X�֘A
	vector<CSingleModel*> m_pSingleModel;	// �X�e�[�W
	CPlayer *m_pPlayer;	// �v���C���[
	CEnemy *m_pEnemy;	// �G
	vector<CCounter*> m_pKiilCount;	// �L���J�E���g
	CCounter *m_pMaxAmmo;	// �ő�e��
	CCounter *m_pAmmo;	// �e��
	int m_nMaxModel;	// ���f���ő吔
	int m_nType;	// ���f���^�C�v
	bool m_bDoOnece = false;	// ��񂾂�
	bool m_bShow = false;	// �}�E�X�̕\��
};

#endif