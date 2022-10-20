//====================================================
//
// �R�~���j�P�[�V�����f�[�^�̃w�b�_�[�t�@�C��(communicationdata.h)
// Author : �H�� ����
//
//====================================================
#ifndef _COMUNICASION_DATA_H_
#define _COMUNICASION_DATA_H_

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "main.h"
#include "d3dx9.h"

//-------------------------------
// �}�N����`
//-------------------------------
#define MAX_BULLET (30)

//-------------------------------
// Class�̒�`
//-------------------------------
class CCommunicationData
{
public:
	//---------------------------
	// �񋓌^
	//---------------------------
	enum class MOSTION
	{
		NEUTRAL = 0,	// �j���[�g�������[�V����
		WORK,			// ����
		BUCK_WORK,		// ������
		ATTACK,			// �U��
		MAX				// ���X�g�̐�
	};

	//---------------------------
	// �\����
	//---------------------------
	typedef struct
	{
		int nNumber;	// �v���C���[�̃C���f�b�N�X
		int nStock;	// �v���C���[�̎c�C
		bool bPushKey;	// �v���C���[���L�[����������
		D3DXVECTOR3 Pos;	// �v���C���[�̈ʒu
		D3DXVECTOR3 Rot;	// �p�x
		MOSTION Motion;	// ���[�V�����̎��
	} PLAYUER_DATA;

	typedef struct
	{
		D3DXVECTOR3 Rot;	// �e�̊p�x
		bool bUse;	// ��������
	} BULLET_DATA;

	typedef struct
	{
		PLAYUER_DATA Player;	// �v���C���[�f�[�^
		BULLET_DATA Bullet[MAX_BULLET];	// �e�f�[�^
		bool bConnect = false;	// �ڑ��m�F
	} COMMUNICATION_DATA;
	CCommunicationData();	// �f�t�H���g�R���X�g���N�^
	~CCommunicationData();	// �f�t�H���g�f�X�g���N�^
	COMMUNICATION_DATA *GetCmmuData(void) { return &m_CommuData; }	// �f�[�^�̃Z�b�^�[
	void SetCmmuData(COMMUNICATION_DATA Data) { m_CommuData = Data; }	// �f�[�^�̃Q�b�_�[
private:
	SOCKET m_socket;	// �\�P�b�g
	COMMUNICATION_DATA m_CommuData;	// �f�[�^
};

#endif // _TCP_CLIENT_H_