//=============================================================================
//
// オブジェクト処理 [object.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "texture.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CObject
{
public:
	//---------------------------
	// 列挙型
	//---------------------------
	enum class PRIORITY
	{
		NONE = 0,			// なし
		PLAYER,				// プレイヤー
		HAPPENING,			// ハプニング
		MODEL,				// モデル
		POLYGON_3D,			// 3Dポリゴン
		SHADOW,				// 影
		MESH_FIELD,			// メッシュフィールド
		EFFECT3D,			// パーティクル
		EFFECT2D,			// パーティクル
		UI,					// UI
		DIALOG,				// セリフ
		NEXT_DIALOG_UI,		// 次のセリフに進むUI
		SCORE,				// Score
		RANKING,			// ランキング
		MASK,				// マスク
		PAUSE,				// ポーズ
		GAME,				// ゲーム
		ROAD,				// ステージ
		FADE,				// フェード
		HISTORY_LETTER,		// 実績解除文字
		CLICK_EFFECT,		// クリックエフェクト
		MAX
	};

	enum class OBJTYPE
	{
		NONE = 0,			// なし
		POLYGON_3D,			// 3Dポリゴン
		FLOOR,				// 床
		BG,					// 背景
		EFFECT_3D,			// 3Dエフェクト
		EFFECT_2D,			// 2Dエフェクト
		SPARKLE,			// キラキラエフェクト
		MODEL,				// モデル
		PLAYER,				// プレイヤー
		HAPPENING,			// ハプニング
		STAR_RING,			// スターリング
		FAN,				// 扇風機
		TRAMPOLINE,			// トランポリン
		AIR_PLANE,			// 飛行機
		REDBULL,			// redbull
		UI,					// UI
		TROPHY,				// トロフィー
		SHADOW,				// 影
		GAUGE,				// ゲージ
		SMOKE,				// 煙
		WIND,				// 風
		AIRPLANE_CLOUD,		// 飛行機雲
		THORN,				// 棘
		BANANA,				// バナナ
		MAX
	};

	CObject(PRIORITY priorty = PRIORITY::NONE);	// デフォルトコンストラクタ
	virtual ~CObject();	// デフォルトデストラクタ
	virtual HRESULT Init(void) = 0;	// 初期化
	virtual void Uninit(void) = 0;	// 終了
	virtual void Update(void) = 0;	// 更新
	virtual void Draw(void) = 0;	// 描画
	static void ReleaseAll(void);	// 全破棄
	static void UpdateAll(void);	// 全更新
	static void DrawAll(void);		// 全描画
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// 位置の取得
	D3DXVECTOR3 GetSize(void) { return m_size; }	// サイズの取得
	bool GetDeath(void) { return m_deth; }	// 破棄フラグの取得
	D3DXVECTOR3 GetPosOld(void) { return m_pos_old; }	// 前回の位置の取得
	OBJTYPE GetObjType(void) { return m_obj_type; }	// オブジェクトタイプの取得
	static vector<CObject*> GetObject(const int &priority) { return m_object[priority]; }	// オブジェクト配列の取得
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }	// 位置の設定
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }	// サイズの設定
	void SetObjType(const OBJTYPE &obj_type) { m_obj_type = obj_type; }	// オブジェクトタイプの設定
	void SetPriority(const int &nPriority);	// プライオリティ設定処理
	void SetPosOld(const D3DXVECTOR3 &pos_old) { m_pos_old = pos_old; }	// 前回の位置の設定
private:
	static vector<CObject*> m_object[static_cast<int>(PRIORITY::MAX)];	// オブジェクト配列
	D3DXVECTOR3	m_pos;		// 位置
	D3DXVECTOR3 m_pos_old;	// 1フレーム前の位置
	D3DXVECTOR3 m_size;		// サイズ
	OBJTYPE m_obj_type;		// オブジェクトの種類
	int m_priority;	// 描画順
	bool m_deth;	// 死亡フラグ
protected:
	void Release(void) { m_deth = true; }		// 死亡フラグ立てる
};

#endif