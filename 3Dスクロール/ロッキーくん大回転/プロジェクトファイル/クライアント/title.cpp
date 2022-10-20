//=============================================================================
//
// �g���t�B�[���[���� [trophy.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "title.h"
#include "manager.h"
#include "object2D.h"
#include "play_data.h"
#include "input_mouse.h"
#include "fade.h"
#include "sound.h"
#include "letter.h"
#include "trophy.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TITLE_TO_RESULT_COUNT		(1000)				//���U���g�ɍs���܂ł̎���
#define TITLE_LOGO_SIZE_X			(366.0f)			//�^�C�g�����S�̃T�C�YX
#define TITLE_LOGO_SIZE_Y			(420.0f)			//�^�C�g�����S�̃T�C�YY
#define TITLE_PRESS_START_SIZE_X	(594.0f)			//PRESS START UI�̃T�C�YX
#define TITLE_PRESS_START_SIZE_Y	(84.0f)				//PRESS START UI�̃T�C�YY
#define TITLE_PRESS_START_POS_Y		(600.0f)			//PRESS START UI�̈ʒuY

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTitle::CTitle(CObject::PRIORITY Priority):CObject(Priority)
{
	FILE *file;	// �t�@�C���̃|�C���^

	// �t�@�C�����J��
	file = fopen("data/keyconfig.txt", "r");

	// �t�@�C�����J���Ă�����
	if (file != NULL)
	{
		// �L�[�����̃��[�v
		for (int nCntKey = 1; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			char name_buf[1][64];
			string name;

			fscanf(file, "%s", name_buf[0]);
			name = name_buf[0];
			m_letter_single.push_back(name);

			// SJIS �� wstring
			int iBufferSize = MultiByteToWideChar(	CP_ACP,
													0,
													name.c_str(),
													-1,
													(wchar_t*)NULL,
													0);

			// �o�b�t�@�̎擾
			wchar_t* cpUCS2 = new wchar_t[iBufferSize];

			// SJIS �� wstring
			MultiByteToWideChar(	CP_ACP,
									0,
									name.c_str(),
									-1,
									cpUCS2,
									iBufferSize);

			// string�̐���
			wstring utextbuf(cpUCS2, cpUCS2 + iBufferSize - 1);

			// �o�b�t�@�̔j��
			delete[] cpUCS2;

			// �L�[�R���̖��O��ۑ�
			m_key_name.push_back(utextbuf);
		}
	}

	// �t�@�C�������
	fclose(file);
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	// �p�X���[�h��������
	CManager::GetInstance()->GetPlayData()->SetPasword("");

	CObject2D *object_2D[3];
	CSound *sound;	// �T�E���h�̃|�C���^
	sound = CManager::GetInstance()->GetSound();	// �T�E���h�̎擾

	sound->Stop();	// ��~
	sound->Play(CSound::SOUND_LABEL::TITLE_BGM);	// �Đ�
	sound->ControllVoice(CSound::SOUND_LABEL::TITLE_BGM, 1.4f);	// ���ʒ���

	object_2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	object_2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Bg.png"));
	object_2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 0.0f + 200.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.3f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	object_2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Title.png"));
	m_click = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 3.0f) / 2.0f, SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.10f) / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT * 0.10f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	m_click->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Click.png"));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(0.0f + 300.0f, SCREEN_HEIGHT - 300.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2f, SCREEN_HEIGHT * 0.15f, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT - 300.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2f, SCREEN_HEIGHT * 0.15f, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 150.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2f, SCREEN_HEIGHT * 0.15f, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(0.0f + 300.0f, SCREEN_HEIGHT - 300.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2f, SCREEN_HEIGHT * 0.15f, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT - 300.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2f, SCREEN_HEIGHT * 0.15f, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 150.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2f, SCREEN_HEIGHT * 0.15f, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame.png"));
	m_button[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame.png"));
	m_button[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame.png"));
	m_button[3]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("start.png"));
	m_button[4]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy.png"));
	m_button[5]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial.png"));
	object_2D[2]= CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 0.0f + 75.0f, 0.0f), D3DXVECTOR3(600.0f, 150.0f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	object_2D[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("password_frame.png"));
	m_pas_word = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 0.0f + 95.0f, 0.0f), D3DXVECTOR3(480.0f, 50.0f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	m_pas_word->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("password_wordbox.png"));
	m_fade_flag = true;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	SeletMode();
	Tutorial();
	ColUpdate();
	ResultTimer();
	PasWord();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{
	
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::SeletMode(void)
{
	CFade *fade;	// �t�F�[�h�N���X�̃|�C���^
	CInputMouse *mouse;	// �}�E�X�N���X�̃|�C���^
	D3DXVECTOR3 pos[3];	// �ʒu
	D3DXVECTOR3 size[3];	// �T�C�Y
	POINT point;	// �}�E�X���W	
	HWND hwnd;	// �E�B���h�E�n���h��
	CSound *sound;	// �T�E���h�N���X�̃|�C���^
	sound = CManager::GetInstance()->GetSound();	// �T�E���h�̎擾
	pos[0] = m_button[0]->GetPos();	// �{�^���̈ʒu���擾
	size[0] = m_button[0]->GetSize();	// �{�^���̃T�C�Y���擾
	pos[1] = m_button[1]->GetPos();	// �{�^���̈ʒu���擾
	size[1] = m_button[1]->GetSize();	// �{�^���̃T�C�Y���擾
	pos[2] = m_button[2]->GetPos();	// �{�^���̈ʒu���擾
	size[2] = m_button[2]->GetSize();	// �{�^���̃T�C�Y���擾
	hwnd = CManager::GetInstance()->GetWindowHandle();	// �E�B���h�E�n���h�����擾
	fade = CManager::GetInstance()->GetFade();	// �t�F�[�h�擾
	mouse = CManager::GetInstance()->GetInputMouse();	// �}�E�X�N���X�̎擾
	GetCursorPos(&point);	// �}�E�X���W�擾
	ScreenToClient(hwnd, &point);	// �N���C�A���g���W�ɕϊ�

	// �{�^���ɐG��Ă�����
	if (pos[0].x - size[0].x / 2.0f <= point.x &&
		pos[0].x + size[0].x / 2.0f >= point.x &&
		pos[0].y - size[0].y / 2.0f <= point.y &&
		pos[0].y + size[0].y / 2.0f >= point.y &&
		m_tutorial_flag == false)
	{
		// �J���[��ς���
		m_button[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_button[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		// ���N���b�N�������Ă��� && �t�F�[�h���Ă��Ȃ�������
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true && fade->GetFade() == CFade::FADE_NONE)
		{
			// �p�X���[�h�̌���
			if (strncmp("ENDROLL", m_pasword.c_str(), 8) == 0)
			{
				sound->ControllVoice(CSound::SOUND_LABEL::DECISION_SE, 1.2f);	// ���ʒ���
				sound->Play(CSound::SOUND_LABEL::DECISION_SE);	// �Đ�
				fade->SetFade(CManager::MODE::ENDING);	// �G���h���[���ɑJ��
			}
			// ����ȊO
			else
			{
				// �p�X���[�h��ł�����ł�����
				if (m_pas_drop == true)
				{
					CManager::GetInstance()->GetPlayData()->SetPasword(m_pasword);	// �p�X���[�h��ݒ�
					sound->ControllVoice(CSound::SOUND_LABEL::DECISION_SE, 1.2f);	// ���ʒ���
					sound->Play(CSound::SOUND_LABEL::DECISION_SE);	// �Đ�
					fade->SetFade(CManager::MODE::GAME01);	// �Q�[����ʂɑJ��
				}
				// ����ȊO
				else
				{
					sound->ControllVoice(CSound::SOUND_LABEL::DECISION_SE, 1.2f);	// ���ʒ���
					sound->Play(CSound::SOUND_LABEL::DECISION_SE);	// �Đ�
					fade->SetFade(CManager::MODE::GAME01);	// �Q�[����ʂɑJ��
				}
			}
		}
	}
	// ����ȊO
	else
	{
		// �J���[��ݒ�
		m_button[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_button[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// �{�^���ɐG��Ă�����
	if (pos[1].x - size[1].x / 2.0f <= point.x &&
		pos[1].x + size[1].x / 2.0f >= point.x &&
		pos[1].y - size[1].y / 2.0f <= point.y &&
		pos[1].y + size[1].y / 2.0f >= point.y &&
		m_tutorial_flag == false)
	{
		// �J���[��ݒ�
		m_button[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_button[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		// ���N���b�N�������Ă��� && �t�F�[�h���Ă��Ȃ�������
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true && fade->GetFade() == CFade::FADE_NONE)
		{
			sound->ControllVoice(CSound::SOUND_LABEL::DECISION_SE, 1.2f);	// ���ʒ���
			sound->Play(CSound::SOUND_LABEL::DECISION_SE);	// �Đ�
			fade->SetFade(CManager::MODE::TROPHY);	// �g���t�B�[��ʂɑJ��
		}
	}
	// ����ȊO
	else
	{
		// �J���[��ݒ�
		m_button[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_button[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// �{�^���ɐG��Ă�����
	if (pos[2].x - size[2].x / 2.0f <= point.x &&
		pos[2].x + size[2].x / 2.0f >= point.x &&
		pos[2].y - size[2].y / 2.0f <= point.y &&
		pos[2].y + size[2].y / 2.0f >= point.y &&
		m_tutorial_flag == false)
	{
		// �J���[��ݒ�
		m_button[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_button[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		// ���N���b�N�������Ă���
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			sound->ControllVoice(CSound::SOUND_LABEL::DECISION_SE, 1.2f);	// ���ʒ���
			sound->Play(CSound::SOUND_LABEL::DECISION_SE);	// �Đ�

			for (int count_tutorial = 0; count_tutorial < 5; count_tutorial++)
			{
				m_tutorial.push_back(CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
			}
			m_tutorial.push_back(CObject2D::Create(D3DXVECTOR3(0.0f + 80.0f, 0.0f + 50.0f, 0.0f), D3DXVECTOR3(80.0f, 80.0f, 70.0f), static_cast<int>(CObject::PRIORITY::UI)));
			m_tutorial[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial_up.png"));
			m_tutorial[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial_arrow.png"));
			m_tutorial[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial_picture_left.png"));
			m_tutorial[3]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial_picture_light.png"));
			m_tutorial[4]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial_under.png"));
			m_tutorial[5]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("arrow.png"));
			m_tutorial_flag = true;
		}
	}
	else
	{
		// �J���[��ݒ�
		m_button[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_button[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

//=============================================================================
// �`���[�g���A��
//=============================================================================
void CTitle::Tutorial(void)
{
	CInputMouse *mouse;	// �}�E�X�N���X�̃|�C���^
	POINT point;	// �}�E�X���W
	HWND hwnd;	// �E�B���h�E�n���h��
	CSound *sound;	// �T�E���h�N���X�̃|�C���^
	sound = CManager::GetInstance()->GetSound();	// �T�E���h�̎擾
	hwnd = CManager::GetInstance()->GetWindowHandle();	// �E�B���h�E�n���h���̎擾
	mouse = CManager::GetInstance()->GetInputMouse();	// �}�E�X�N���X�̎擾
	GetCursorPos(&point);	// �}�E�X���W�̎擾
	ScreenToClient(hwnd, &point);	// �N���C�A���g���W�ɕϊ�

	// �`���[�g���A���t���O�����Ă���
	if (m_tutorial_flag == true)
	{
		D3DXVECTOR3 pos_buck;	// �ʒu
		D3DXVECTOR3 size_buck;	// �T�C�Y

		// �ʒu�ƃT�C�Y���擾
		pos_buck = m_tutorial[5]->GetPos();
		size_buck = m_tutorial[5]->GetSize();

		// �}�E�X���G��Ă�����
		if (pos_buck.x - size_buck.x / 2.0f <= point.x &&
			pos_buck.x + size_buck.x / 2.0f >= point.x &&
			pos_buck.y - size_buck.y / 2.0f <= point.y &&
			pos_buck.y + size_buck.y / 2.0f >= point.y)
		{
			// �J���[��ݒ�
			m_tutorial[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			// ���N���b�N�������Ă�����
			if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
			{
				sound->ControllVoice(CSound::SOUND_LABEL::CANSEL_SE, 1.2f);	// ���ʒ���
				sound->Play(CSound::SOUND_LABEL::CANSEL_SE);	// �Đ�

				// �T�C�Y���擾
				int tutorial_size = m_tutorial.size();

				// �T�C�Y���̃��[�v
				for (int count_tutorial = tutorial_size - 1; count_tutorial >= 0; count_tutorial--)
				{
					// �j��
					m_tutorial[count_tutorial]->Uninit();
					m_tutorial[count_tutorial] = nullptr;
					m_tutorial.pop_back();
				}
				m_tutorial_flag = false;
			}
		}
		// ����ȊO
		else
		{
			// �J���[��ݒ�
			m_tutorial[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

//=============================================================================
// �J���[�ύX
//=============================================================================
void CTitle::ColUpdate(void)
{
	D3DXCOLOR col_click = m_click->GetCol();	// �J���[���擾

	// ���l�������ɂ���ĕς���
	if (col_click.a >= 1.0f)
	{
		m_fade_flag = true;
	}
	else if (col_click.a <= 0.0f)
	{
		m_fade_flag = false;
	}

	if (m_fade_flag == true)
	{
		col_click.a -= 0.01f;
		m_click->SetCol(col_click);
	}
	else
	{
		col_click.a += 0.01f;
		m_click->SetCol(col_click);
	}
}

//=============================================================================
// ���U���g�^�C�}�[
//=============================================================================
void CTitle::ResultTimer(void)
{
	CFade *fade;	// �t�F�[�h�N���X
	CInputMouse *mouse;	// �}�E�X�N���X
	fade = CManager::GetInstance()->GetFade();	// �t�F�[�h�N���X���擾
	mouse = CManager::GetInstance()->GetInputMouse();	// �}�E�X�N���X�̎擾

	// �^�C�}�[���Z
	m_result_timer++;

	// ��莞�Ԃ��������� && �}�E�X�N���X���ړ����Ă��Ȃ�������
	if (m_result_timer >= TITLE_TO_RESULT_COUNT &&
		mouse->GetMouseState().lX == 0 &&
		mouse->GetMouseState().lY == 0)
	{
		// �^�C�}�[������
		m_result_timer = 0;

		// �t�F�[�h���ĂȂ������� && �`���[�g���A���t���O�������ĂȂ������� && �p�X���[�h����͂��ĂȂ�������
		if (fade->GetFade() == CFade::FADE_NONE &&
			m_tutorial_flag == false && m_pas_drop == false)
		{
			// ���U���g��ʂɑJ��
			fade->SetFade(CManager::MODE::RESULT);
		}
	}
}

//=============================================================================
// �p�X���[�h����
//=============================================================================
void CTitle::PasWord(void)
{
	CInputKeyboard *key;	// �L�[�{�[�h�N���X�̃|�C���^
	CInputMouse *mouse;	// �}�E�X�N���X�̃|�C���^
	POINT point;	// �}�E�X���W
	HWND hwnd;	// �E�B���h�E�n���h��
	string text_buf;	// �e�L�X�g�̃o�b�t�@
	pair<int, bool> key_update;	// �L�[�o�C���h�̃y�A
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 size;	// �T�C�Y
	key = CManager::GetInstance()->GetInputKeyboard();	// �L�[�{�[�h�N���X�̎擾
	hwnd = CManager::GetInstance()->GetWindowHandle();	// �E�B���h�E�n���h���̎擾
	mouse = CManager::GetInstance()->GetInputMouse();	// �}�E�X�N���X�̎擾
	GetCursorPos(&point);	// �}�E�X���W�̎擾
	ScreenToClient(hwnd, &point);	// �N���C�A���g���W�ɕϊ�

	pos = m_pas_word->GetPos();	// ���͗��̈ʒu
	size = m_pas_word->GetSize();	// ���͗��̃T�C�Y

	// �}�E�X���G��Ă�����
	if (pos.x - size.x / 2.0f <= point.x &&
		pos.x + size.x / 2.0f >= point.x &&
		pos.y - size.y / 2.0f <= point.y &&
		pos.y + size.y / 2.0f >= point.y)
	{
		// ���N���b�N�������Ă�����
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			m_pas_drop = true;
		}
	}
	// ����ȊO
	else
	{
		// ���N���b�N�������Ă�����
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			// �p�X���[�h��ݒ�
			CManager::GetInstance()->GetPlayData()->SetPasword(m_pasword);
			m_pas_drop = false;
		}
	}

	// ���͂��Ă�����
	if(m_pas_drop == true)
	{
		// �J���[�̐ݒ�
		m_pas_word->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		// �����L�[�������Ă�����
		key_update = key->GetAllKeyUpdate();

		// �L�[�������Ă�����
		if (key_update.second == true)
		{
			// �G���^�[�ȊO�� && �o�b�N�X�y�[�X�ȊO
			if (key_update.first != DIK_RETURN && key_update.first != DIK_BACK)
			{
				// �����������Ȃ��Ȃ�
				if (m_letter_limitl < 15)
				{
					// ���O�̎擾
					int name_size = m_key_name[key_update.first].size();

					// ���O���̃��[�v
					for (int count_name = 0; count_name < name_size; count_name++)
					{
						// �����𐶐�
						m_pas_font.push_back(new CLetter);

						m_pas_font[m_count_letter]->SetPos(D3DXVECTOR3((((SCREEN_WIDTH - 300.0f) - (480.0f / 2.0f)) + 32.5f) + (30.0f * m_count_letter), (((0.0f + 95.f) - (50.0f / 2.0f)) + 25.0f), 0.0f));
						m_pas_font[m_count_letter]->SetSize(D3DXVECTOR3(15.0f, 15.0f, 0.0f));
						m_pas_font[m_count_letter]->SetText(m_key_name[key_update.first][count_name]);
						m_pas_font[m_count_letter]->SetFontSize(300);
						m_pas_font[m_count_letter]->SetFontWeight(500);
						m_pas_font[m_count_letter]->Init();
						m_count_letter++;
						m_pasword.push_back(m_letter_single[key_update.first][count_name]);
						m_letter_limitl++;
					}
				}
			}
			// �o�b�N�X�y�[�X�Ȃ�
			else if(key_update.first == DIK_BACK)
			{
				CManager::GetInstance()->GetPlayData()->SetPasword("");	//�p�X���[�h�����

				// �T�C�Y���擾
				int font_size = m_pas_font.size();

				// �T�C�Y���̃��[�v
				for (int count_font = 0; count_font < font_size; count_font++)
				{
					// �j��
					m_pas_font[count_font]->Uninit();
					m_pas_font.erase(m_pas_font.begin());
					font_size = m_pas_font.size();
					count_font--;
					m_count_letter = 0;
					m_letter_limitl = 0;
				}
				// �T�C�Y���擾
				int pas_size = m_pasword.size();

				// �T�C�Y���̃��[�v
				for (int count_pas = 0; count_pas < pas_size; count_pas++)
				{
					// �j��
					m_pasword.pop_back();
				}
			}
			// �G���^�[�Ȃ�
			else if (key_update.first == DIK_RETURN)
			{
				// �p�X���[�h��ݒ�
				CManager::GetInstance()->GetPlayData()->SetPasword(m_pasword);
				m_pas_drop = false;
			}
		}
	}
	// ����ȊO
	else
	{
		m_pas_word->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}