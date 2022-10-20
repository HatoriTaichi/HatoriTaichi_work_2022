//=============================================================================
//
// ���[�V�������� [motion.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "motion.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMotion::CMotion()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CMotion::~CMotion()
{

}

//=============================================================================
// ���[�V�����̍Đ�
//=============================================================================
bool CMotion::PlayMotin(CModel::MOTIONINFO *motion, D3DXVECTOR3 *pos, D3DXVECTOR3 *rot)
{
	D3DXVECTOR3 PosAsk;		//���߂�l�ʒuX
	D3DXVECTOR3 RotAsk;		//���߂�l����X
	D3DXVECTOR3 PosDifference;	//�ʒu�̍���X
	D3DXVECTOR3 RotDifference;	//�����̍���X
	bool bEnd = false;	//���[�V�����I���t���O

	// �Ō�̃��[�V��������Ȃ�������
	if (motion->nKeyCnt < (motion->nNumKey - 1))
	{
		// ���������߂�
		PosDifference.x = motion->aKeyinfo[motion->nKeyCnt + 1]->aKey.fPosX - motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosX;
		PosDifference.y = motion->aKeyinfo[motion->nKeyCnt + 1]->aKey.fPosY - motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosY;
		PosDifference.z = motion->aKeyinfo[motion->nKeyCnt + 1]->aKey.fPosZ - motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosZ;

		RotDifference.x = motion->aKeyinfo[motion->nKeyCnt + 1]->aKey.fRotX - motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotX;
		RotDifference.y = motion->aKeyinfo[motion->nKeyCnt + 1]->aKey.fRotY - motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotY;
		RotDifference.z = motion->aKeyinfo[motion->nKeyCnt + 1]->aKey.fRotZ - motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotZ;

		// �ړI�̒l�����߂�
		PosAsk.x = motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosX + PosDifference.x * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		PosAsk.y = motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosY + PosDifference.y * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		PosAsk.z = motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosZ + PosDifference.z * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);

		RotAsk.x = motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotX + RotDifference.x * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		RotAsk.y = motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotY + RotDifference.y * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		RotAsk.z = motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotZ + RotDifference.z * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);

		// �ړ�������
		pos->x = PosAsk.x;
		pos->y = PosAsk.y;
		pos->z = PosAsk.z;

		rot->x = RotAsk.x;
		rot->y = RotAsk.y;
		rot->z = RotAsk.z;

		// ���[�V�����J�E���g
		motion->fFrameCnt += 1.0f;

		//���[�V�����J�E���^���t���[�����𒴂�����
		if (motion->fFrameCnt >= motion->aKeyinfo[motion->nKeyCnt]->fFrame)
		{
			//���̃L�[
			motion->nKeyCnt++;
			//���[�V�����J�E���^������
			motion->fFrameCnt = 0.0f;
			bEnd = false;
		}
	}
	else if (motion->nKeyCnt == (motion->nNumKey - 1))
	{
		// ���������߂�
		PosDifference.x = motion->aKeyinfo[motion->nKeyCnt - 1]->aKey.fPosX - motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosX;
		PosDifference.y = motion->aKeyinfo[motion->nKeyCnt - 1]->aKey.fPosY - motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosY;
		PosDifference.z = motion->aKeyinfo[motion->nKeyCnt - 1]->aKey.fPosZ - motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosZ;

		RotDifference.x = motion->aKeyinfo[motion->nKeyCnt - 1]->aKey.fRotX - motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotX;
		RotDifference.y = motion->aKeyinfo[motion->nKeyCnt - 1]->aKey.fRotY - motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotY;
		RotDifference.z = motion->aKeyinfo[motion->nKeyCnt - 1]->aKey.fRotZ - motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotZ;

		// �ړI�̒l�����߂�
		PosAsk.x = motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosX + PosDifference.x * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		PosAsk.y = motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosY + PosDifference.y * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		PosAsk.z = motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosZ + PosDifference.z * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);

		RotAsk.x = motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotX + RotDifference.x * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		RotAsk.y = motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotY + RotDifference.y * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		RotAsk.z = motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotZ + RotDifference.z * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);

		// �ړ�������
		pos->x = PosAsk.x;
		pos->y = PosAsk.y;
		pos->z = PosAsk.z;

		rot->x = RotAsk.x;
		rot->y = RotAsk.y;
		rot->z = RotAsk.z;

		// ���[�V�����J�E���g
		motion->fFrameCnt += 1.0f;

		//���[�V�����J�E���^���t���[�����𒴂�����
		if (motion->fFrameCnt >= motion->aKeyinfo[motion->nKeyCnt]->fFrame)
		{
			if (motion->bLoop == true)
			{
				//���̃L�[
				motion->nKeyCnt = 0;
			}
			else
			{
				motion->nKeyCnt = 0;
				bEnd = true;
			}
			//���[�V�����J�E���^������
			motion->fFrameCnt = 0.0f;
		}
	}

	return bEnd;
}