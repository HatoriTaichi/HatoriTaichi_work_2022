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

#include <iostream>
#include <thread>
#include "main.h"
#include "tcp_listener.h"
#include "communication.h"
#include "communicationdata.h"

//------------------------
// �O���[�o���ϐ�
//------------------------
int g_accept_count = 0;
int g_stop = 1;

//------------------------
// ���C���֐�
//------------------------
void main(void)
{
#ifdef _DEBUG
	int size = sizeof(CCommunicationData::COMMUNICATION_DATA);
#endif // _DEBUG
	//------------------------
	// ������
	//------------------------
	WSADATA  wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);

	if (nErr != 0)
	{
		cout << "�������Ɏ��s���܂���" << endl;
	}

	// �T�[�o�[�̐���
	CTcpListener *pListenner = new CTcpListener;

	// �T�[�o�[����������Ă��� && ���������������Ă���
	if (pListenner != NULL && pListenner->Init() == true)
	{
		// �X���b�h�𐶐�
		thread th(StopOrSurver);

		// �X���b�h��؂藣��
		th.detach();

		// �T�[�o�[���������疳�����[�v
		while (pListenner != NULL)
		{
			// �ڑ������\�l�ȉ��Ȃ�
			if (g_accept_count <= 10)
			{
				// �X���b�h�𐶐�
				thread th(Accept, pListenner);

				// �X���b�h��؂藣��
				th.detach();
			}
			if (g_stop == 0)
			{
				break;
			}
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

//------------------------
// �ڑ��҂�
//------------------------
void Accept(CTcpListener *listener)
{
	// �ʐM�N���X
	CCommunication *communication;

	// �ڑ��J�E���g
	g_accept_count++;

	// �ڑ��҂�
	communication = listener->Accept();

	// �J�E���g���o��
	cout << "g_accept_count->" << g_accept_count << endl;

	// �X���b�h�𐶐�
	thread th(RankCommunication, communication);

	// �X���b�h��؂藣��
	th.detach();
}

//------------------------
// �����L���O���M��M
//------------------------
void RankCommunication(CCommunication *communication)
{
	CCommunicationData commu_data;	// �ʐM�f�[�^�N���X
	CCommunicationData::COMMUNICATION_DATA *data = commu_data.GetCommuData();	// �ʐM�f�[�^���擾
	char recv_data[MAX_COMMUDATA];	// ��M�f�[�^
	char send_data[MAX_COMMUDATA];	// ���M�f�[�^
	int my_score;	// �����̃X�R�A

	// ��M
	communication->Recv(&recv_data[0], sizeof(int));

	// �X�R�A���R�s�[
	memcpy(&my_score, recv_data, sizeof(int));

	// �X�R�A���\�[�g
	commu_data.RankingSort(my_score);

	// �\�[�g�����X�R�A���R�s�[
	memcpy(&send_data, &data->ranking, sizeof(CCommunicationData::COMMUNICATION_DATA::ranking));

	// �\�[�g�����X�R�A�𑗐M
	communication->Send(&send_data[0], sizeof(CCommunicationData::COMMUNICATION_DATA::ranking));

	// �����L���O���Z�[�u
	commu_data.Save();

	// �I��
	communication->Uninit();

	// �ڑ��������炷
	g_accept_count--;

	// ��ʂɏo��
	cout << "g_accept_count->" << g_accept_count << endl;
}

//------------------------
// �I������
//------------------------
void StopOrSurver(void)
{
	cin >> g_stop;
}

//------------------------
// �L�[���͑҂�
//------------------------
void KeyWait(void)
{
	rewind(stdin);
	getchar();
}