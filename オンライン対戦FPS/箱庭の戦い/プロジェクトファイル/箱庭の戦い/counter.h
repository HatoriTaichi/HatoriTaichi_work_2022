//=============================================================================
//
// カウンター処理 [counter.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCounter : public CScene
{
public:
	CCounter();	// デフォルトコンストラクタ
	~CCounter();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void AddCounter(int nValue) { m_nCounter += nValue; }	// スコア加算
	int GetCounter(void) { return m_nCounter; }	// スコアの取得
	void SetCounter(int nCounter);	// スコアの設定
	void SetCol(D3DCOLORVALUE col);	// カラーの設定
	void SetCounterNum(int nCounter) { m_nCounter = nCounter; }	// スコアの設定
	int GetCounterNum(void) { return m_nCounter; }	// スコアの取得
	static CCounter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumbderLength, string type);	// 生成
private:
	vector<CNumber*> m_pNumber;	// 桁
	D3DXVECTOR3 m_Pos;	// 位置
	D3DXVECTOR3 m_Size;	// サイズ
	string m_Type;	// テクスチャ
	int m_nNumberMax;	// 桁数
	int m_nCounter;	// スコア
};

#endif