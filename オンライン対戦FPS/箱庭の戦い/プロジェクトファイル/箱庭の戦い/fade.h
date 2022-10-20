//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : �H������
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "scene2D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFade
{
public:
	//---------------------------
	//�񋓌^
	//---------------------------
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	} FADE;
	CFade();	// �f�t�H���g�R���X�g���N�^
	~CFade();	// �f�X�g���N�^
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	void SetFade(CManager::MODE mode);	// �t�F�[�h�̐ݒ�
	FADE GetFade(void) { return m_Fade; }	// �t�F�[�h�����ǂ������擾
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	CManager::MODE m_nextMode;	// ���̃��[�h
	FADE m_Fade;	// �t�F�[�h
	float m_colA;	// �J���[�̃A���t�@�l
};

#endif // !_FADE_H_