//=============================================================================
//
// �G���� [enemy.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CEnemy::CEnemy()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CEnemy::Init(void)
{
	CScene2D::SetTexType(m_Type);	// �e�N�X�`���̐ݒ�
	CScene2D::Init();	// ������
	CScene2D::SetPos(m_Pos);	// �ʒu�̐ݒ�
	CScene2D::SetSize(m_Size);	// �T�C�Y�̐ݒ�

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CEnemy::Uninit(void)
{
	// �j��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(void)
{
	D3DXVECTOR3 Pos = CScene2D::GetPos();	// �ʒu���擾

	// �A�j���[�V�����J�E���g�A�b�v
	m_nAnimFrame++;

	// �����Ă�Ȃ�
	if (m_bMove == true)
	{
		// ��ނɂ���Ĉړ���ς���
		if (m_Type == "ENEMY_LEFT")
		{
			Pos.x -= 10.0f;
			CScene2D::SetPos(Pos);
		}
		else if (m_Type == "ENEMY_RIGHT")
		{
			Pos.x += 10.0f;
			CScene2D::SetPos(Pos);
		}
		else if (m_Type == "ENEMY_UP")
		{
			Pos.y -= 10.0f;
			CScene2D::SetPos(Pos);
		}
		else if (m_Type == "ENEMY_DOWN")
		{
			Pos.y += 10.0f;
			CScene2D::SetPos(Pos);
		}
		
		// �A�j���[�V������؂�ւ���^�C�~���O�Ȃ�
		if (m_nAnimFrame >= (FPS / 8))
		{
			// �A�j���[�V�����e�N�X�`����ݒ�
			if (m_Type == "ENEMY_RIGHT" ||
				m_Type == "ENEMY_LEFT")
			{
				CScene2D::SetTex(m_nAnim, 8, 1);
				m_nAnimFrame = 0;
				m_nAnim++;
			}
			else if (m_Type == "ENEMY_UP" ||
					 m_Type == "ENEMY_DOWN")
			{
				CScene2D::SetTex(m_nAnim, 4, 1);
				m_nAnimFrame = 0;
				m_nAnim++;
			}
		}

		// �j�����Ă��Ȃ�
		if (m_bUse == false)
		{
			// ��ʊO�ɏo����
			if (Pos.x < 0.0f ||
				Pos.x > SCREEN_WIDTH ||
				Pos.y < 0.0f || 
				Pos.y > SCREEN_HEIGHT)
			{
				// �j��
				Uninit();
			}
		}
	}
	// ����ȊO
	else
	{
		// �_���[�W���󂯂ĂȂ�������
		if (m_Type != "ENEMY_DAMAGE")
		{
			// �A�j���[�V������؂�ւ���^�C�~���O�Ȃ�
			if (m_nAnimFrame >= (FPS / 8))
			{
				// �A�j���[�V�����e�N�X�`����ݒ�
				if (m_Type == "ENEMY_RIGHT" ||
					m_Type == "ENEMY_LEFT")
				{
					CScene2D::SetTex(m_nAnim, 8, 1);
					m_nAnimFrame = 0;
					m_nAnim++;
				}
				else if (m_Type == "ENEMY_UP" ||
						 m_Type == "ENEMY_DOWN")
				{
					CScene2D::SetTex(m_nAnim, 4, 1);
					m_nAnimFrame = 0;
					m_nAnim++;
				}
			}
		}
	}

	// �|���S���̍X�V
	CScene2D::Update();

	// �j������Ȃ�
	if (m_bUse == true)
	{
		Pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		CScene2D::SetPos(Pos);
		m_Type = "ENEMY_DAMAGE";
		CScene2D::SetTexType(m_Type);
		CScene2D::SetTex(0, 1, 1);
		m_nDeth++;
		if (m_nDeth >= (FPS * 2))
		{
			Uninit();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	// �`��
	CScene2D::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string type)
{
	CEnemy *pEnemy = NULL;	// �G�̃|�C���^

	// NULL�Ȃ�
	if (pEnemy == NULL)
	{
		// ����
		pEnemy = new CEnemy;
	}

	// �����̑��
	pEnemy->m_Pos = pos;
	pEnemy->m_Size = size;
	pEnemy->m_Type = type;

	// ��������Ă�����
	if (pEnemy != NULL)
	{
		// ������
		pEnemy->Init();
	}

	return pEnemy;
}
