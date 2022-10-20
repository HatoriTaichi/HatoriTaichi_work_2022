//=============================================================================
//
// ���͏��� [input.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "rule.h"
#include "manager.h"
#include "textureobj.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CRule::CRule()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CRule::~CRule()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CRule::Init(void)
{
	FILE *pFile;	// �t�@�C���̃|�C���^
	D3DXVECTOR3 Pos;	// �ʒu
	D3DXVECTOR3 Size;	// �T�C�Y
	char aFile[1][128];	// �t�@�C���̕����o�b�t�@

	// �t�@�C�����J��
	pFile = fopen("data/Txtdata/ruledata.txt", "r");

	// �t�@�C�����J���Ă�����
	if (pFile != NULL)
	{
		int nCnt = 0;	// UI�J�E���g

		// �������[�v
		while (true)
		{
			// �������擾
			fscanf(pFile, "%s", aFile[0]);

			// UI_NUM�̕��������������
			if (strcmp(aFile[0], "UI_NUM") == 0)
			{
				fscanf(pFile, "%*s%d", &m_nUiNum);
			}
			// SET_UI�̕��������������
			if (strcmp(aFile[0], "SET_UI") == 0)
			{
				// �������[�v
				while (true)
				{
					// �������擾
					fscanf(pFile, "%s", aFile[0]);

					// TEX_TYPE�̕��������������
					if (strcmp(aFile[0], "TEX_TYPE") == 0)
					{
						char aTypeBuf[1][64];	// �������擾����ׂ̃o�b�t�@
						string Type;	// �X�g�����O�z��ɓ����ׂ̃o�b�t�@

						// �������擾
						fscanf(pFile, "%*s%s", aTypeBuf[0]);

						// �X�g�����O�֕ϊ�
						Type = aTypeBuf[0];

						// �z��ɕۑ�
						m_Type.push_back(Type);
					}
					// POS�̕��������������
					else if (strcmp(aFile[0], "POS") == 0)
					{
						// �ʒu����ۑ�
						fscanf(pFile, "%*s%f%f%f", &Pos.x, &Pos.y, &Pos.z);
					}
					// SIZE�̕��������������
					else if (strcmp(aFile[0], "SIZE") == 0)
					{
						// �T�C�Y����ۑ�
						fscanf(pFile, "%*s%f%f%f", &Size.x, &Size.y, &Size.z);
					}
					// END_UISET�̕��������������
					else if (strcmp(aFile[0], "END_UISET") == 0)
					{
						// �擾�������Ő���
						m_Ui.push_back(CUiObj::Create(Pos, Size, m_Type[nCnt]));

						// UI�J�E���g�A�b�v
						nCnt++;

						// ���[�v���ʂ���
						break;
					}
				}
			}
			// END�̕��������������
			else if (strcmp(aFile[0], "END") == 0)
			{
				// ���[�v���ʂ���
				break;
			}
		}
	}
	else
	{
		cout << "�e�L�X�g�t�@�C�����Ђ炯�܂���ł����B";
	}

	// �t�@�C�������
	fclose(pFile);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CRule::Uninit(void)
{
	// �j��
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CRule::Update(void)
{
	// �I������
	SelectInfo();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRule::Draw(void)
{

}

//=============================================================================
// �I������
//=============================================================================
void CRule::SelectInfo(void)
{
	// UI�����̃��[�v
	for (int nCntUi = 0; nCntUi < m_nUiNum; nCntUi++)
	{
		string Type = m_Ui[nCntUi]->GetType();	// �e�N�X�`���̎�ނ��擾
		POINT MousePos;	// �}�E�X�̈ʒu���擾
		D3DXVECTOR3 Pos = m_Ui[nCntUi]->GetPos();	// �ʒu���擾
		D3DXVECTOR2 Size = m_Ui[nCntUi]->GetSize();	// �T�C�Y�̎擾
		bool bSelect = m_Ui[nCntUi]->GetSelect();	// �I��ł邩�t���O�̎擾
		GetCursorPos(&MousePos);	// �}�E�X�̈ʒu���擾
		ScreenToClient(CManager::GetHandle(), &MousePos);	// �N���C�A���g���W�ɕϊ�

		// �e�N�X�`���̎�ނŏ�����ς���
		if (Type == "MANUAL")
		{
			// �I��ł�����
			if (bSelect == true)
			{
				// UI�����̃��[�v
				for (int nCntUi = 0; nCntUi < m_nUiNum; nCntUi++)
				{
					// �e�N�X�`���̎�ނ��擾
					string UseType = m_Ui[nCntUi]->GetType();

					// ��ނɂ���ă��l��ς���
					if (UseType == "OPERATIONMANUAL" || UseType == "DESCRIPTION")
					{
						m_Ui[nCntUi]->SetAlpha(0.0f);
					}
					else
					{
						m_Ui[nCntUi]->SetAlpha(1.0f);
					}
				}
			}
		}
		else if (Type == "WEAPON_LETTER")
		{
			// �I��ł�����
			if (bSelect == true)
			{
				// UI�����̃��[�v
				for (int nCntUi = 0; nCntUi < m_nUiNum; nCntUi++)
				{
					// �e�N�X�`���̎�ނ��擾
					string UseType = m_Ui[nCntUi]->GetType();

					// ��ނɂ���ă��l��ς���
					if (UseType == "WEAPONMANUAL" || UseType == "DESCRIPTION")
					{
						m_Ui[nCntUi]->SetAlpha(0.0f);
					}
					else
					{
						m_Ui[nCntUi]->SetAlpha(1.0f);
					}
				}
			}
		}
		else if (Type == "WINCONDITION")
		{
			// �I��ł�����
			if (bSelect == true)
			{
				// UI�����̃��[�v
				for (int nCntUi = 0; nCntUi < m_nUiNum; nCntUi++)
				{
					// �e�N�X�`���̎�ނ��擾
					string UseType = m_Ui[nCntUi]->GetType();

					// ��ނɂ���ă��l��ς���
					if (UseType == "WEAPONMANUAL" || UseType == "OPERATIONMANUAL")
					{
						m_Ui[nCntUi]->SetAlpha(0.0f);
					}
					else
					{
						m_Ui[nCntUi]->SetAlpha(1.0f);
					}
				}
			}
		}
	}
}