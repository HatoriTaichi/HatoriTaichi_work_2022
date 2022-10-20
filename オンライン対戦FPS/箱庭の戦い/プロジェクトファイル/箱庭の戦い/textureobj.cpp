//=============================================================================
//
// 2D�|���S������ [textureobj.cpp]
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
#include "sound.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CUiObj::CUiObj(LAYER_TYPE Layer) : CScene2D(Layer)
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
	D3DXVECTOR3 Pos = CScene2D::GetPos();	// �ʒu�擾
	D3DXVECTOR2 Size = CScene2D::GetSize();	// �T�C�Y�̎擾
	CMouse *pMouse = CManager::GetMouse();	// �}�E�X�̎擾
	CFade *pFade = CManager::GetFade();	// �t�F�[�h�̎擾
	POINT MousePos;	// �}�E�X�̈ʒu
	GetCursorPos(&MousePos);	// �}�E�X�̈ʒu�̎擾
	ScreenToClient(CManager::GetHandle(), &MousePos);	// �N���C�A���g���W�ɕϊ�

	// �e�N�X�`���̎�ނɂ���ď�����ς���
	if (m_TexType == "MATCHING")
	{
		// ���l�̔��]
		if (m_bAlpha == false)
		{
			m_Color.a -= 0.01f;
			CScene2D::SetCol(m_Color);
			if (m_Color.a <= 0.0f)
			{
				m_bAlpha = true;
			}
		}
		else if (m_bAlpha == true)
		{
			m_Color.a += 0.01f;
			CScene2D::SetCol(m_Color);
			if (m_Color.a >= 1.0f)
			{
				m_bAlpha = false;
			}
		}
	}
	else if (m_TexType == "YES")
	{
		// �}�E�X�ŐG��Ă�����
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			// ���l�𔖂�
			m_Color.a = 0.5f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);

			// ���N���b�N && �t�F�[�h���Ă��Ȃ�������
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
			{
				// �Đ�
				pSound->PlaySound(CSound::X2SOUND_LABEL::GONEXT);

				// �}�b�`���O��ʂɑJ��
				pFade->SetFade(CManager::MODE::MATCHING);
			}
		}
		else
		{
			// ���l���ő��
			m_Color.a = 1.0f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "NO")
	{
		// �}�E�X�ŐG��Ă�����
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			// ���l�𔖂�
			m_Color.a = 0.5f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);

			// ���N���b�N && �t�F�[�h���Ă��Ȃ�������
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
			{
				// �Đ�
				pSound->PlaySound(CSound::X2SOUND_LABEL::GONEXT);

				// �^�C�g����ʂɑJ��
				pFade->SetFade(CManager::MODE::TITLE);
			}
		}
		else
		{
			// ���l���ő��
			m_Color.a = 1.0f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "GAMESTART")
	{
		// �}�E�X�ŐG��Ă�����
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			// ���l�𔖂�
			m_Color.a = 0.5f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);

			// ���N���b�N && �t�F�[�h���Ă��Ȃ�������
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
			{
				// �Đ�
				pSound->PlaySound(CSound::X2SOUND_LABEL::GONEXT);

				// �}�b�`���O��ʂɑJ��
				pFade->SetFade(CManager::MODE::MATCHING);
			}
		}
		else
		{
			// ���l���ő��
			m_Color.a = 1.0f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "RELE")
	{
		// �}�E�X�ŐG��Ă�����
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			// ���l�𔖂�
			m_Color.a = 0.5f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);

			// ���N���b�N && �t�F�[�h���Ă��Ȃ�������
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
			{
				// �Đ�
				pSound->PlaySound(CSound::X2SOUND_LABEL::GONEXT);

				// ���[����ʂɑJ��
				pFade->SetFade(CManager::MODE::RULE);
			}
		}
		else
		{
			// ���l���ő��
			m_Color.a = 1.0f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "MANUAL")
	{
		// �}�E�X�ŐG��Ă�����
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			m_bSelect = true;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);
		}
		else
		{
			m_bSelect = false;
			m_Color.a = 1.0f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "WEAPON_LETTER")
	{
		// �}�E�X�ŐG��Ă�����
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			m_bSelect = true;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);
		}
		else
		{
			m_bSelect = false;
			m_Color.a = 1.0f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "WINCONDITION")
	{
		// �}�E�X�ŐG��Ă�����
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			m_bSelect = true;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);
		}
		else
		{
			m_bSelect = false;
			m_Color.a = 1.0f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "BUCK")
	{
		// �}�E�X�ŐG��Ă�����
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			// ���l�𔖂�
			m_Color.a = 0.5f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);

			// ���N���b�N && �t�F�[�h���Ă��Ȃ�������
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
			{
				// �Đ�
				pSound->PlaySound(CSound::X2SOUND_LABEL::GONEXT);

				// �^�C�g����ʂɑJ��
				pFade->SetFade(CManager::MODE::TITLE);
			}
		}
		else
		{
			// ���l���ő��
			m_Color.a = 1.0f;

			// �J���[�̐ݒ�
			CScene2D::SetCol(m_Color);
		}
	}

	// �X�V
	CScene2D::Update();
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CUiObj::Draw(void)
{
	// �`��
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