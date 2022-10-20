//=============================================================================
//
// �����|���S������ [textureobj.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "textureobj.h"
#include "manager.h"
#include "fade.h"
#include "mouseinput.h"
#include "fade.h"
#include "mouseinput.h"
#include "sound.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CUiObj::CUiObj()
{
	m_Color.a = 0.0f;
	m_Color.r = 0.0f;
	m_Color.b = 0.0f;
	m_Color.g = 0.0f;
	m_nChangeCnt = 0;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CUiObj::~CUiObj()
{

}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CUiObj::Init(void)
{
	CScene2D::SetTexType(m_TexType);	// �e�N�X�`���̐ݒ�
	CScene2D::Init();	// ������
	CScene2D::SetPos(m_Pos);	// �ʒu�̐ݒ�
	CScene2D::SetSize(m_Size);	// �T�C�Y�̐ݒ�

	// �J���[�̏�����
	m_Color.a = 1.0f;
	m_Color.r = 1.0f;
	m_Color.b = 1.0f;
	m_Color.g = 1.0f;

	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CUiObj::Uninit(void)
{
	// �j��
	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CUiObj::Update(void)
{
	CSound *pSound = CManager::GetSound();	// �T�E���h�̎擾
	CMouse *pMouse = CManager::GetMouse();	// �}�E�X�̎擾
	CFade *pFade = CManager::GetFade();	// �t�F�[�h�̎擾
	POINT MousePos;	// �}�E�X�̈ʒu
	D3DXVECTOR3 Pos = CScene2D::GetPos();	// �|���S���̈ʒu�擾
	D3DXVECTOR2 Size = CScene2D::GetSize();	// �|���S���̃T�C�Y�̎擾
	GetCursorPos(&MousePos);	// �}�E�X�ʒu�̎擾
	ScreenToClient(CManager::GetHandle(), &MousePos);	// �N���C�A���g���W�ɕϊ�

	// �e�N�X�`����START�Ȃ�
	if (m_TexType == "START")
	{
		// �}�E�X���G��Ă�����
		if (Pos.x + Size.x >= MousePos.x &&
			Pos.x - Size.x <= MousePos.x &&
			Pos.y + Size.y >= MousePos.y &&
			Pos.y - Size.y <= MousePos.y)
		{
			// ���l�𔖂�
			m_Color.a = 0.5f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);

			// ���N���b�N���������� && �t�F�[�h���ĂȂ�������
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == pFade->FADE_NONE)
			{
				// �T�E���h���Đ�
				pSound->Play(CSound::SOUND_LABEL_SE_START);

				// �Q�[����ʂ֑J��
				pFade->SetFade(CManager::MODE::GAME);
			}
		}
		// ����ȊO
		else
		{
			// ���l���ő��
			m_Color.a = 1.0f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);
		}
	}
	// �e�N�X�`����RULE�Ȃ�
	if (m_TexType == "RULE")
	{
		// �}�E�X���G��Ă�����
		if (Pos.x + Size.x >= MousePos.x &&
			Pos.x - Size.x <= MousePos.x &&
			Pos.y + Size.y >= MousePos.y &&
			Pos.y - Size.y <= MousePos.y)
		{
			// ���l�𔖂�
			m_Color.a = 0.5f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);

			// ���N���b�N���������� && �t�F�[�h���ĂȂ�������
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == pFade->FADE_NONE)
			{
				// �T�E���h���Đ�
				pSound->Play(CSound::SOUND_LABEL_SE_START);

				// ������ʂ֑J��
				pFade->SetFade(CManager::MODE::MANUAL);
			}
		}
		// ����ȊO
		else
		{
			// ���l���ő��
			m_Color.a = 1.0f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);
		}
	}
	// �e�N�X�`����BUCK�Ȃ�
	if (m_TexType == "BUCK")
	{
		// �}�E�X���G��Ă�����
		if (Pos.x + Size.x >= MousePos.x &&
			Pos.x - Size.x <= MousePos.x &&
			Pos.y + Size.y >= MousePos.y &&
			Pos.y - Size.y <= MousePos.y)
		{
			// ���l�𔖂�
			m_Color.a = 0.5f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);

			// ���N���b�N���������� && �t�F�[�h���ĂȂ�������
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == pFade->FADE_NONE)
			{
				// �T�E���h���Đ�
				pSound->Play(CSound::SOUND_LABEL_SE_START);

				// �^�C�g���֑J��
				pFade->SetFade(CManager::MODE::TITLE);
			}
		}
		// ����ȊO
		else
		{
			// ���l���ő��
			m_Color.a = 1.0f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);
		}
	}

	// �|���S���̍X�V
	CScene2D::Update();
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CUiObj::Draw(void)
{
	// �|���S���̕`��
	CScene2D::Draw();
}

//=============================================================================
// ����
//=============================================================================
CUiObj *CUiObj::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string Type)
{
	CUiObj *pUi = NULL;	// UI�̃|�C���^

	// NULL��������
	if (pUi == NULL)
	{
		// ����
		pUi = new CUiObj;
	}

	// �����̑��
	pUi->m_Pos = pos;
	pUi->m_Size = size;
	pUi->m_TexType = Type;

	// ��������Ă�����
	if (pUi != NULL)
	{
		// ������
		pUi->Init();
	}
	return pUi;
}