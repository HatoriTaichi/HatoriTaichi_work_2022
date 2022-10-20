//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "result.h"
#include "fade.h"
#include "rank.h"
#include "Picture.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "sound.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
bool g_bUse2 = false;

//---------------------------
//����������
//---------------------------
HRESULT InitResult(void)
{
	PlaySound(SOUND_RESULT_BGN);
	InitPicture();
	SetPicture(D3DXVECTOR3((SCREEN_WIDTH / 2) - 200.0f, (SCREEN_HEIGHT / 2) - 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 50.0f, PICTURE_TYPE_1ST);
	SetPicture(D3DXVECTOR3((SCREEN_WIDTH / 2) - 200.0f, (SCREEN_HEIGHT / 2) - 180.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 50.0f, PICTURE_TYPE_2ND);
	SetPicture(D3DXVECTOR3((SCREEN_WIDTH / 2) - 200.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 50.0f, PICTURE_TYPE_3RD);

	InitRank();

	return S_OK;
}
//---------------------------
//�I������
//---------------------------
void UninitResult(void)
{
	UninitPicture();

	UninitRank();
}
//---------------------------
//�X�V����
//---------------------------
void UpdateResult(void)
{
	static int nCnt;	//�����@�ۃ^�C�}�[
	int nNum = 0;		//rando�p�̕ϐ�

	nCnt++;				//�^�C�}�[���Z

	UpdateRank();

	//�^�C�}�[��1584�ɂȂ邩 || �G���^�[�L�[�����Ă���
	if (nCnt >= 1584 && GetFade() == FADE_NONE || GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE || MouseDowan(MOUSE_WHEEL_BOTTON) == true && GetFade() == FADE_NONE)
	{
		StopSound(SOUND_RESULT_BGN);
		PlaySound(SOUND_PUSH_SE);
		SetFade(MODE_TITLE);
		nCnt = 0;		//�J�E���g���傫��
	}
	if (g_bUse2 == true)
	{
		nNum = 4;
	}
	else if (g_bUse2 == false)
	{
		nNum = rand() % 4;
	}

	g_bUse2 = UpdatePicture();

	switch (nNum)
	{
	case 0:
		g_bUse2 = SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT + 250.0f, 0.0f), D3DXVECTOR3(0.0f, -2.0f, 0.0f), 500.0f, 500.0f, PICTURE_TYPE_GUYS_00);
		break;
	case 1:
		g_bUse2 = SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, 0 - 250.0f, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 500.0f, 500.0f, PICTURE_TYPE_GUYS_01);
		break;
	case 2:
		g_bUse2 = SetPicture(D3DXVECTOR3(SCREEN_WIDTH + 250.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 500.0f, 500.0f, PICTURE_TYPE_GUYS_02);
		break;
	case 3:
		g_bUse2 = SetPicture(D3DXVECTOR3(0 - 250.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 500.0f, 500.0f, PICTURE_TYPE_GUYS_03);
		break;
	}
}
//---------------------------
//�`�揈��
//---------------------------
void DrawResult(void)
{
	DrawPicture();

	DrawRank();
}