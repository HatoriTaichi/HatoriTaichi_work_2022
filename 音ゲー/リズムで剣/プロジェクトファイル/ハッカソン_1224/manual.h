//=============================================================================
//
// 説明画面 [manual.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _MANUAL_H_
#define _MANUAL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUiObj;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CManual
{
public:
	CManual();	// デフォルトコンストラクタ
	~CManual();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);		// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
private:

};

#endif