#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_


//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include <windows.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800) //�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"//���͏����ɕK�v
#include "xaudio2.h"

//---------------------------
//���C�u�����̃����N
//---------------------------
#pragma comment(lib,"d3d9.lib") //�`��ɕK�v
#pragma comment(lib,"d3dx9.lib") //[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib") //DirectX�R���|�[�l���g�i���i�j�g�p�ɕK�v
#pragma comment (lib, "winmm.lib")
#pragma comment(lib,"dinput8.lib") //���͏����ɕK�v

//---------------------------
//�}�N����`
//---------------------------
#define SCREEN_WIDTH (1280) //�E�B���h�E�̕�
#define SCREEN_HEIGHT (720) //�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) //2D�̏_��Ȓ��_�t�H�[�}�b�g

//---------------------------
//�񋓌^.���[�h�̎��
//---------------------------
typedef enum
{
	MODE_TITLE = 0,		//�^�C�g��
	MODE_OPERATION,		//�������
	MODE_HOME,			//�z�[��
	MODE_ES_STAGE01,	//�C�[�W�[�̃X�e�[�W01
	MODE_ES_STAGE02,	//�C�[�W�[�̃X�e�[�W02
	MODE_ES_STAGE03,	//�C�[�W�[�̃X�e�[�W03
	MODE_NO_STAGE01,	//�m�[�}���̃X�e�[�W01
	MODE_NO_STAGE02,	//�m�[�}���̃X�e�[�W02
	MODE_NO_STAGE03,	//�m�[�}���̃X�e�[�W03
	MODE_NO_STAGE04,	//�m�[�}���̃X�e�[�W04
	MODE_HD_STAGE01,	//�n�[�h�̃X�e�[�W01
	MODE_HD_STAGE02,	//�́[�ǂ̃X�e�[�W02
	MODE_HD_STAGE03,	//�́[�ǂ̂��ā[��03
	MODE_HD_STAGE04,	//�́[�ǂ̂��ā[��04
	MODE_HD_STAGE05,	//�́[�ǂ̂��ā[��05
	MODE_RESULT,		//���U���g���
	MODE_GAMEOVER,		//�Q�[���I�[�o�[
	MODE_MAX			//���X�g�̐�
} MODE;

//---------------------------
//�\���̂̒�`
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//1.0f�ŌŒ�
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_2D;

//---------------------------
//�v���g�^�C�v�錾
//---------------------------
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
MODE GetMode2(void);
#endif 