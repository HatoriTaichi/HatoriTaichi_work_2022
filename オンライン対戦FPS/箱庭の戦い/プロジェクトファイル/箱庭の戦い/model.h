//=============================================================================
//
// X�t�@�C�����f������ [sceneX.h]
// Author : �H������&�ߊԏr��
//
//=============================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BOXVTX_MAX (8)	// ���̒��_��
#define BOX_SURFACE (6)	// ���̖ʂ̐�
#define PLAYER_WIDTH (20.0f)	// �v���C���[�̕�

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CModel
{
public:
	//---------------------------
	// �񋓌^
	//---------------------------
	enum class MOSTION
	{
		NEUTRAL = 0,	// �j���[�g�������[�V����
		WORK,			// ����
		BUCK_WORK,		// ������
		ATTACK,			// �U��
		MAX				// ���X�g�̐�
	};

	//---------------------------
	// �\����
	//---------------------------
	typedef struct
	{
		float fPosX;	// �ʒuX
		float fPosY;	// �ʒuY
		float fPosZ;	// �ʒuZ
		float fRotX;	// ����X
		float fRotY;	// ����Y
		float fRotZ;	// ����Z
	} KEY;

	typedef struct
	{
		float fFrame;	// �Đ��t���[��
		KEY aKey;		// ���f�����̃L�[�v�f
	} KEYINFO;

	typedef struct
	{
		bool bLoop;			// ���[�v���邩
		int nNumKey;		// �L�[�̑���
		int nKeyCnt;		// �L�[�J�E���g
		float fFrameCnt;	// ���[�V�����J�E���g
		vector<KEYINFO*> aKeyinfo;	// �L�[�̏��(�L�[�̑�����)
	} MOTIONINFO;

	typedef struct
	{
		LPD3DXMESH pMesh;		// ���b�V���i���_���j�ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;	// �}�e���A���ւ̃|�C���^
		DWORD nNumMat;			// �}�e���A���̐�
		D3DXVECTOR3 vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	// ���_�̒[���
		D3DXVECTOR3	vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	// ���_�̒[���
	}MODEL_DATA;

	//---------------------------
	// �񋓌^
	//---------------------------
	enum class TYPE
	{
		PLAYER_BODY = 0,	// ��
		PLAYER_HEAD,		// ��
		PLAYER_RIGHTARM,	// �E�r
		PLAYER_RIGHTHAND,	// �E��
		PLAYER_LEFTARM,		// ���r
		PLAYER_LEFTHAND,	// ����
		PLAYER_RIGHTFOOT,	// �E������
		PLAYER_RIGHTLEG,	// �E��
		PLAYER_LEFTFOOT,	// ��������
		PLAYER_LEFTLEG,		// ����
		PLAYER_GUN,			// �e
		TRANSPARENT_BOX,	// �����Ȕ�
		CONTAINER,			// �R���e�i
		PORT_FLOOR,			// �C�X�e�[�W��
		MAX,
	};

	CModel();	// �f�t�H���g�R���X�g���N�^
	~CModel();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(void);	// �|���S���̏�����
	HRESULT Init(int *nPreants, FILE *pFile);	// �|���S���̏�����
	void Uninit(void);	// �|���S���̏I��
	void Update(void);	// �|���S���̍X�V
	void Draw(void);	// �|���S���̕`��
	bool BoxCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 posold);	// �����蔻��
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }	// �ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }	// �����̐ݒ�
	void SetScale(D3DXVECTOR3 scale) { m_Scale = scale; }	// �X�P�[���̐ݒ�
	void SetMatrix(D3DXMATRIX mtx) { m_MtxWold = mtx; }	// �}�g���b�N�X�̐ݒ�
	void SetPrent(CModel *pModel) { m_pPrent = pModel; }	// �e�̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_Pos; }	// �ʒu�̎擾
	D3DXVECTOR3 GetRot(void) { return m_Rot; }	// �����̎擾
	D3DXVECTOR3 GetScale(void) { return m_Scale; }	// �X�P�[���̎擾
	D3DXMATRIX GetMatrix(void) { return m_MtxWold; }	// �}�g���b�N�X�̎擾
	MODEL_DATA *GetModelData(void) { return m_aModelData; }	// ���f���̎擾
	D3DXVECTOR3 GetVMin(TYPE type) { return m_aModelData[(int)type].vtxMin; }	// ���f���̍ő咸�_�̎擾
	D3DXVECTOR3 GetVMax(TYPE type) { return m_aModelData[(int)type].vtxMax; }	// ���f���̍ŏ����_�̎擾
	MOTIONINFO *GetMotion(int nMotion) { return &m_Motion[nMotion]; }	// ���[�V�����̎擾
	static HRESULT Load(void);	// ���f���f�[�^�̓ǂݍ���
	static void UnLoad(void);	// ���f���f�[�^�̔j��
	static CModel *Create(TYPE type);	// ����
	static CModel *Create(TYPE type, D3DXVECTOR3 scale, int *nPreants, FILE *pFile);	// ����
private:
	void UpdateColliSion(void);	// �����蔻��̍X�V
	static MODEL_DATA *m_aModelData;	// �S���f���̏��
	vector<LPDIRECT3DTEXTURE9> m_pTexture;	// �e�N�X�`��
	TYPE m_Type;	// ���f���̎��
	MOTIONINFO m_Motion[(int)MOSTION::MAX];	// ���[�V����
	CModel *m_pPrent;	// �e�̃��f��
	D3DXMATRIX m_MtxWold;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_Pos;	// �ʒu
	D3DXVECTOR3 m_Scale;	// �X�P�[��
	D3DXVECTOR3 m_Rot;	// ����
	D3DXVECTOR3 m_vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	// ���_�̒[���
	D3DXVECTOR3	m_vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	// ���_�̒[���
	D3DXVECTOR3 m_BoxVtx[BOXVTX_MAX];	// ���̒��_
	D3DXVECTOR3 m_Nor[BOX_SURFACE];	// ���̖ʂ̖@��
	D3DXVECTOR3 m_CenterVtx[BOX_SURFACE];	// ���̖ʂ̒��S�_
};

#endif
