//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "operation.h"
#include "bg.h"
#include "input.h"
#include "fade.h"
#include "life.h"
#include "block.h"
#include "player.h"
#include "sound.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------


//---------------------------
//����������
//---------------------------
HRESULT InitOperation(void)
{
	InitBg();
	SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 3);
	SetBg(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT - 50.0f, 0.0f), 300.0f, 50.0f, 5);

	InitBlock();
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 10.0f, 1.0f, 1.0f, 0);

	InitPlayer();
	SetPlayer(D3DXVECTOR3(SCREEN_WIDTH - (300.0f + PLAYER_X_SIZE), SCREEN_HEIGHT, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);

	return S_OK;
}

//---------------------------
//����������
//---------------------------
void UninitOperation(void)
{
	UninitBg();

	UninitBlock();

	UninitPlayer();
}

//---------------------------
//����������
//---------------------------
void UpdateOperation(void)
{
	UpdateBg();

	UpdatePlayer();

	UpdateBlock();
	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		PlaySound(SOUND_LABEL_SE000);
		SetFade(MODE_HOME);
		StopSound(SOUND_LABEL_BGM000);
	}
}

//---------------------------
//����������
//---------------------------
void DrawOperation(void)
{
	DrawBg();

	DrawBlock();

	DrawPlayer();
}