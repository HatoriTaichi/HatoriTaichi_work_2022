//=============================================================================
//
// 数処理 [number.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2D.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CNumber : public CScene2D
{
public:
	CNumber(LAYER_TYPE Layer = LAYER_TYPE::LAYER_05);	// デフォルトコンストラクタ
	~CNumber();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化(位置、サイズ、テクスチャ)
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string type);	// オブジェクトの生成(位置, サイズ、テクスチャ)
	void SetScore(int nScore) { CScene2D::SetTex(nScore); };	// スコアの設定
	void SetCol(D3DCOLORVALUE col) { CScene2D::SetCol(col); }	// カラーの設定
private:
	D3DXVECTOR3 m_Pos;	// 位置
	D3DXVECTOR3 m_Size;	// サイズ
	string m_Type;	// テクスチャ
};

#endif