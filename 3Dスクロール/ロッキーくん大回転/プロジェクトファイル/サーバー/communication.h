//====================================================
//
// �ʐM�N���X(communication.h)
// Author : �H�� ����
//
//====================================================
#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "main.h"
#include "d3dx9.h"

//-------------------------------
// Class�̒�`
//-------------------------------
class CCommunication
{
public:
	CCommunication();	// �f�t�H���g�R���X�g���N�^
	~CCommunication();	// �f�t�H���g�f�X�g���N�^
	bool Init(SOCKET sock);	// �I�[�o�[���[�hInit(�ڑ��ς݃\�P�b�g)
	int Send(char *pSendData, int nSendDataSize);	// ���M
	int Recv(char *pRecvData, int nRecvDataSize);	// ��M
	void Uninit(void);	// �I��
	SOCKET GetSocket(void) { return m_socket; }	// �\�P�b�g�̓���
private:
	SOCKET m_socket;	// �\�P�b�g
};

#endif // _TCP_CLIENT_H_