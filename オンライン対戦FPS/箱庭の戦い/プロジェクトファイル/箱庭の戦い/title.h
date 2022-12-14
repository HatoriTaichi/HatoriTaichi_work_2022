//=============================================================================
//
// タイトル [title.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

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
class CTitle
{
public:
	CTitle();	// デフォルトコンストラクタ
	~CTitle();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
private:
	vector<string> m_Type;	// テクスチャタイプ
	int m_nUiNum;	// UI数
};

#endif