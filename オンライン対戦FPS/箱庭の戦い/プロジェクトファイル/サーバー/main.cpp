//==================================================
//
// ���C��CPP(main.cpp)
// Author�F�H������
//
//==================================================
//------------------------
// �C���N���[�h
//------------------------
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include <iostream>
#include <utility>
#include "main.h"
#include "tcp_listener.h"
#include "communication.h"
#include "communicationdata.h"

//------------------------
// �O���[�o���ϐ�
//------------------------
int g_nRoomCount = 0;

//------------------------
// ���C���֐�
//------------------------
void main(void)
{
	int n = sizeof(CCommunicationData::COMMUNICATION_DATA);
	//------------------------
	// ������
	//------------------------
	WSADATA  wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);

	if (nErr != 0)
	{
		cout << "�������Ɏ��s���܂���" << endl;
	}

	CTcpListener *pListenner = new CTcpListener;

	if (pListenner != NULL && pListenner->Init() == true)
	{
		while (pListenner != NULL)
		{
			CCommunication *pCommunication;

			// �ڑ��҂�
			pCommunication = pListenner->Accept();
			g_nRoomCount++;

			// �X���b�h����
			thread th(RoomCreate, pCommunication, pListenner);

			// ���������I����܂Ńu���b�N
			th.join();
		}
	}
	if (pListenner != NULL)
	{
		pListenner->Uninit();
		delete pListenner;
		pListenner = NULL;
	}

	//------------------------
	// �I��
	//------------------------
	cout << "�I�����܂��B"<< endl;
	cout << "�����L�[�������Ă��������B"<< endl;
	KeyWait();
	WSACleanup();
}

//--------------------------
// 1�������̃}���`�X���b�h
//--------------------------
void CommuniCationClient(CCommunication *pSendRecvP1, CCommunication *pSendRecvP2, CTcpListener *pServer)
{
	fd_set fds, readfds;
	SOCKET maxfd, sock[MAX_PLAYER];
	CCommunicationData CommmuData[MAX_PLAYER];
	CCommunicationData::COMMUNICATION_DATA *pCommuData[MAX_PLAYER];
	int nRecv = 1;
	char aRecvData[MAX_COMMUDATA];

	FD_ZERO(&readfds);

	cout << "������ : " << g_nRoomCount << endl;

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		pCommuData[nCnt] = CommmuData[nCnt].GetCmmuData();
		pCommuData[nCnt]->bConnect = true;
	}

	// �\�P�b�g�̓���
	sock[0] = pSendRecvP1->GetSocket();
	sock[1] = pSendRecvP2->GetSocket();

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		 // �Ď��\�P�b�g�̓o�^
		FD_SET(sock[nCnt], &readfds);
	}
	// �ő�\�P�b�g�̔���
	if (sock[0] > sock[1])
	{
		maxfd = sock[0];
	}
	else if (sock[1] > sock[0])
	{
		maxfd = sock[1];
	}
	while (nRecv != -1)
	{
		memcpy(&fds, &readfds, sizeof(fd_set));

		// �\�P�b�g�̊Ď�
		select(maxfd + 1, &fds, NULL, NULL, NULL);

		// �v���C���[1��send����Ă�����
		if (FD_ISSET(sock[0], &fds))
		{
			nRecv = pSendRecvP1->Recv(&aRecvData[0], sizeof(CCommunicationData::COMMUNICATION_DATA));

			CommmuData[0].SetCmmuData(*(CCommunicationData::COMMUNICATION_DATA*)&aRecvData[0]);

			pSendRecvP2->Send(&aRecvData[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
		}
		// �v���C���[2��send����Ă�����
		if (FD_ISSET(sock[1], &fds))
		{
			nRecv = pSendRecvP2->Recv(&aRecvData[0], sizeof(CCommunicationData::COMMUNICATION_DATA));

			CommmuData[1].SetCmmuData(*(CCommunicationData::COMMUNICATION_DATA*)&aRecvData[0]);

			pSendRecvP1->Send(&aRecvData[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
		}
	}
	// �ڑ��t���O�̐ؑ�
	pCommuData[0]->bConnect = false;
	pCommuData[1]->bConnect = false;

	// �ؒf����Ă��邱�Ƃ�send
	pSendRecvP1->Send(&aRecvData[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
	pSendRecvP2->Send(&aRecvData[0], sizeof(CCommunicationData::COMMUNICATION_DATA));

	pSendRecvP1->Uninit();
	pSendRecvP2->Uninit();
	delete pSendRecvP1;
	delete pSendRecvP2;

	g_nRoomCount--;
	cout << "���������U����܂����B" << endl;
	cout << "������ : " << g_nRoomCount << endl;
}

//------------------------
// ���������
//------------------------
void RoomCreate(CCommunication *pSendRecvP1, CTcpListener *pServer)
{
	CCommunication *pSendRecvP2;
	CCommunicationData::COMMUNICATION_DATA pCommuData[MAX_PLAYER];
	bool bConnect = false;
	char SendData[MAX_COMMUDATA];

	// �ڑ��҂�
	pSendRecvP2 = pServer->Accept();

	bConnect = true;

	// �v���C���[1��send
	memcpy(&SendData[0], &bConnect, sizeof(bool));
	pSendRecvP1->Send(&SendData[0], sizeof(bool));

	// �v���C���[2��send
	memcpy(&SendData[0], &bConnect, sizeof(bool));
	pSendRecvP2->Send(&SendData[0], sizeof(bool));

	// �v���C���[�ԍ��̐ݒ�
	pCommuData[0].Player.nNumber = 1;
	pCommuData[1].Player.nNumber = 2;

	// �v���C���[1��send
	memcpy(&SendData[0], &pCommuData[0].Player.nNumber, sizeof(int));
	pSendRecvP1->Send(&SendData[0], sizeof(int));

	// �v���C���[2��send
	memcpy(&SendData[0], &pCommuData[1].Player.nNumber, sizeof(int));
	pSendRecvP2->Send(&SendData[0], sizeof(int));

	// �X���b�h����
	thread th(CommuniCationClient, pSendRecvP1, pSendRecvP2, pServer);

	// �X���b�h��؂藣��
	th.detach();
}

//------------------------
// �L�[���͑҂�
//------------------------
void KeyWait(void)
{
	rewind(stdin);
	getchar();
}