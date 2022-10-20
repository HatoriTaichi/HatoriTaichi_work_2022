//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "gameover.h"
#include "bg.h"
#include "score.h"
#include "fade.h"
#include "input.h"
#include "timer.h"
#include "life.h"
#include "sound.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------


//---------------------------
//����������
//---------------------------
HRESULT InitGameover(void)
{
	PlaySound(SOUND_LABEL_BGM003);
	InitBg();
	SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 6);

	return S_OK;
}
//---------------------------
//�I������
//---------------------------
void UninitGameover(void)
{
	UninitBg();

	UninitScore();

	UninitTimer();

	UninitLife();
}
//---------------------------
//�X�V����
//---------------------------
void UpdateGameover(void)
{
	static int nCnt;	//�����@�ۃ^�C�}�[

	nCnt++;				//�^�C�}�[���Z

	UpdateBg();

	//�^�C�}�[��700�ɂȂ邩 && �G���^�[�L�[�����Ă���
	if (nCnt >= 700 && GetFade() == FADE_NONE || GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		SetFade(MODE_TITLE);
		nCnt = 0;			//�J�E���g���傫��
		StopSound(SOUND_LABEL_BGM003);
	}
}
//---------------------------
//�`�揈��
//---------------------------
void DrawGameover(void)
{
	DrawBg();
}