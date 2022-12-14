//=============================================================================
//
// レッドブルクラス処理 [redbull.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _REDBULL_H_
#define _REDBULL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "happening.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CRedbull : public CHappenig
{
public:
	CRedbull(CObject::PRIORITY Priority = CObject::PRIORITY::HAPPENING);	// デフォルトコンストラクタ
	~CRedbull();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	static CRedbull *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);	// 生成
private:
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 回転
	int m_nCntSlow;	//スローになる時間カウント用
	bool m_bHitPlayer;	//プレイヤーに当たったかどうか
};

#endif
