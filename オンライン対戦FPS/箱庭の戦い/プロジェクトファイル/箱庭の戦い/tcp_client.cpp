//====================================================
//
// �ʐM����(tcp_client.cpp)
// Author : �H�� ����
//
//====================================================
//-------------------------------
// �C���N���[�h
//-------------------------------
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include "tcp_client.h"

//-------------------------------
// �f�t�H���g�R���X�g���N�^
//-------------------------------
CTcpClient::CTcpClient()
{
	m_socket = INVALID_SOCKET;
}

//-------------------------------
// �f�t�H���g�f�X�g���N�^
//-------------------------------
CTcpClient::~CTcpClient()
{

}

//-------------------------------
// ������
//-------------------------------
bool CTcpClient::Init(void)
{
	FILE *pFile;	// �t�@�C���̃|�C���^
	char aFile[1][64];	// �t�@�C���̕�����o�b�t�@

	//------------------------
	// ������
	//------------------------
	WSADATA  wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);

	// ���s���Ă���
	if (nErr != 0)
	{
		cout << "�������Ɏ��s���܂���" << endl;
	}

	// �t�@�C�����J��
	pFile = fopen("data/Txtdata/severdata.txt", "r");

	// �t�@�C�����J���Ă�����
	if (pFile != NULL)
	{
		// �������[�v
		while (true)
		{
			// �t�@�C���̕�������擾
			fscanf(pFile, "%s", &aFile[0]);

			// PORT_NUM�̕��������������
			if (strcmp(aFile[0], "PORT_NUM") == 0)
			{
				fscanf(pFile, "%s", &aFile[1]);
				fscanf(pFile, "%d", &m_nPort);
			}
			// MAX_WAIT�̕��������������
			if (strcmp(aFile[0], "IP_NUM") == 0)
			{
				fscanf(pFile, "%s", &aFile[1]);
				fscanf(pFile, "%s", m_Ip.c_str());
			}
			//END_SCRIPT�̕��������������
			if (strcmp(aFile[0], "END_SCRIPT") == 0)
			{
				// ���[�v����
				break;
			}
		}
	}
	else
	{
		printf("�T�[�o�[�f�[�^���ǂݎ��܂���ł����B");
	}

	// �t�@�C�������
	fclose(pFile);

	//------------------------
	// �\�P�b�g�쐬
	//------------------------
	m_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_socket == INVALID_SOCKET)
	{
		printf("�ڑ��҂��\�P�b�g�����܂���ł����B");
		return false;
	}

	return true;
}

//-------------------------------
// �ʐM
//-------------------------------
bool CTcpClient::Connect(void)
{
	//------------------------
	// �ڑ��ݒ�
	//------------------------
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;	// �ǂ̒ʐM��
	addr.sin_port = htons(m_nPort);	// �|�[�g�ԍ�
	addr.sin_addr.S_un.S_addr = inet_addr(m_Ip.c_str());

	//------------------------
	// �ڑ�
	//------------------------
	if (connect(m_socket, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{
		printf("�ڑ��ł��܂���ł����B\n");
		return false;
	}
	else
	{
		printf("�ڑ��o���܂����B\n");
		return true;
	}
}

//-------------------------------
// ���M
//-------------------------------
int CTcpClient::Send(char *pSendData, int nSendDataSize)
{
	int nRecvSize = send(m_socket, pSendData, nSendDataSize, 0);	// �ǂ̃\�P�b�g, ����, ���o�C�g, �ʐM�̎��
	if (nRecvSize < 0)
	{
		Uninit();
	}

	return nRecvSize;
}

//-------------------------------
// ��M
//-------------------------------
int CTcpClient::Recv(char *pRecvData, int nRecvDataSize)
{
	memset(pRecvData, 0, sizeof(pRecvData));
	int nRecvSize = recv(m_socket, pRecvData, nRecvDataSize, 0);	// �ǂ̃\�P�b�g, �ǂ���, �ő�e��, �ʐM�̎��

	return nRecvSize;
}

//-------------------------------
// �I��
//-------------------------------
void CTcpClient::Uninit(void)
{
	if (m_socket == INVALID_SOCKET)
	{
		return;
	}

	//------------------------
	// �ڑ��ؒf
	//------------------------
	// ��ʏ���
	system("cls");

	printf("�ڑ���ؒf���܂��B\n");
	closesocket(m_socket);	// �ڑ���t�p�\�P�b�g
	m_socket = INVALID_SOCKET;
}