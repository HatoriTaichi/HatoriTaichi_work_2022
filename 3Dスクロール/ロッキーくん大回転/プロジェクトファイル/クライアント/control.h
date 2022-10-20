//=============================================================================
// コントロール処理
// Author:加藤瑞葵
//=============================================================================
#ifndef _CONTROL_H_
#define _CONTROL_H_
#include "main.h"

//前方宣言
class CObject;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CControl
{
public:
	CControl();									// コンストラクタ
	virtual ~CControl();						// デストラクタ
	virtual HRESULT Init(const CObject *pObject) = 0;	// 初期化処理
	virtual void Uninit(void) = 0;				// 終了処理
	virtual void Update(const CObject *pObject) = 0;	// 更新処理
	D3DXVECTOR3 GetMove(void);					// 移動量の取得処理

protected:
	D3DXVECTOR3 m_move;							// 移動量
};

#endif	//_CONTROL_H_