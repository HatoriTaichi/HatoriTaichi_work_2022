//=============================================================================
//
// 敵処理 [enemy.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemy : public CScene2D
{
public:
	CEnemy();	// デフォルトコンストラクタ
	~CEnemy();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);		// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void SetbMove(bool move) { m_bMove = move; }	// 動いてるフラグの設定
	void SetUse(bool use) { m_bUse = use; }	// 使ってるかフラグの設定
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string type);	// 生成
private:
	D3DXVECTOR3 m_Pos;	// 位置
	D3DXVECTOR3 m_Size;	// サイズ
	string m_Type;	// タイプ
	int m_nAnim;	// 今のアニメーション
	int m_nAnimFrame;	// 次のアニメーション
	int m_nDeth;	// 破棄
	bool m_bMove = false;	// 動いてるか
	bool m_bUse = false;	// 破棄フラグ
};

#endif