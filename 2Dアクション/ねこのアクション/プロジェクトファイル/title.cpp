//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "title.h"
#include "bg.h"
#include "input.h"
#include "fade.h"
#include "timer.h"
#include "score.h"
#include "life.h"
#include "sound.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------


//---------------------------
//����������
//---------------------------
HRESULT InitTitle(void)
{
	PlaySound(SOUND_LABEL_BGM000);

	InitBg();
	SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 2);
	SetBg(D3DXVECTOR3(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 25, 0.0f), 300.0f, 50.0f, 5);

	InitScore();

	InitLife();
	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitTitle(void)
{
	UninitBg();
}

//---------------------------
//�X�V����
//---------------------------
void UpdateTitle(void)
{
	static int nCnt;	//�����@�ۃ^�C�}�[

	nCnt++;				//�^�C�}�[���Z

	UpdateBg();

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		PlaySound(SOUND_LABEL_SE000);
		SetFade(MODE_OPERATION);
	}
	//10�b�Ń����L���O���
	else if (nCnt >= 1440 && GetFade() == FADE_NONE)
	{
		SetFade(MODE_RESULT);
		nCnt = 0;
	}
}

//---------------------------
//�`�揈��
//---------------------------
void DrawTitle(void)
{
	DrawBg();
}