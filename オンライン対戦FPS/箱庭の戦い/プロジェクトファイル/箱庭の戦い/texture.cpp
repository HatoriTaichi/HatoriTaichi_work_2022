//=============================================================================
//
// �e�N�X�`������ [texture.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
vector<LPDIRECT3DTEXTURE9>	CTexture::m_pTexture;	//�e�N�X�`��
int CTexture::m_nTextureMax;	// �ǂݍ��ރe�N�X�`���̍ő吔
vector<string> CTexture::m_FilePas;	// �t�@�C���̃p�X
vector<string> CTexture::m_Enum;	// ������̕ۑ�
map<string, int> CTexture::m_TexType;	// �������int��map

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	m_nTextureMax = NULL;
	m_TexType.clear();
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X���擾����
	FILE *pFile;	// �t�@�C���̃|�C���^
	char aFile[64];	// �t�@�C���̕�����o�b�t�@

	// �t�@�C�����J��
	pFile = fopen("data/Txtdata/texturedata.txt", "r");

	// �t�@�C�����J���Ă�����
	if (pFile != NULL)
	{
		// �������[�v
		while (true)
		{
			// �t�@�C���̕�������擾
			fscanf(pFile, "%s", &aFile[0]);

			// TEX_NUM�̕��������������
			if (strcmp(&aFile[0], "TEX_NUM") == 0)
			{
				fscanf(pFile, "%s", &aFile[0]);	// =
				fscanf(pFile, "%d", &m_nTextureMax);	// �e�N�X�`������
			}
			// ENUM_NAME�̕��������������
			else if (strcmp(&aFile[0], "ENUM_NAME") == 0)
			{
				// �e�N�X�`���������̃��[�v
				for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
				{
					int nNumber;	// �񋓔ԍ�
					char aEnumBuf[1][64];	// �擾���Ă���ׂ̃o�b�t�@
					string Enum;	// string�^�ɂ���ׂ̃o�b�t�@

					// �����Ɛ������擾
					fscanf(pFile, "%s%s%d%*s%*s", aEnumBuf[0], &aFile[0], &nNumber);

					// string�֕ϊ�
					Enum = aEnumBuf[0];

					// �z��Ƀv�b�V��
					m_Enum.push_back(Enum);

					// �^���񋓌^�̐���
					m_TexType[Enum] = nNumber;
				}
			}
			// TEXTURE_PAS�̕��������������
			else if (strcmp(&aFile[0], "TEXTURE_PAS") == 0)
			{
				// �e�N�X�`���������̃��[�v
				for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
				{
					char aPasBuf[1][64];	// �擾���Ă���ׂ̃o�b�t�@
					string Pas;	// string�^�ɂ���ׂ̃o�b�t�@

					// �p�X���擾
					fscanf(pFile, "%s", aPasBuf[0]);

					// string�֕ϊ�
					Pas = aPasBuf[0];

					// �z��ɕۑ�
					m_FilePas.push_back(Pas);
				}
			}
			//END�̕��������������
			else if (strcmp(&aFile[0], "END") == 0)
			{
				// ���[�v����
				break;
			}
		}
	}
	else
	{
		printf("�e�N�X�`���f�[�^���ǂݎ��܂���ł����B");
	}

	// �t�@�C�������
	fclose(pFile);

	// �e�N�X�`���������̃��[�v
	for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
	{
		LPDIRECT3DTEXTURE9 pTex = NULL;	// �e�N�X�`���̃o�b�t�@

		D3DXCreateTextureFromFile(	pDevice,
									m_FilePas[nCnt].c_str(),	// �e�N�X�`���p�X
									&pTex);
		// �e�N�X�`���̕ۑ�
		m_pTexture.push_back(pTex);
	}
}

//=============================================================================
// �I��
//=============================================================================
void CTexture::Uniinit(void)
{
	// �e�N�X�`���������̃��[�v
	for (int nCntTexture = 0; nCntTexture < m_nTextureMax; nCntTexture++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCntTexture] != NULL)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture] = NULL;
		}
	}
}