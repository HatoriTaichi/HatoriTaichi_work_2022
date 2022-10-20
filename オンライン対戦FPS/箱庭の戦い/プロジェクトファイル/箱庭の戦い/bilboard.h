//=============================================================================
//
// ビルボード処理 [bilboard.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _BILBOARD_H_
#define _BILBOARD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//3Dの柔軟な頂点フォーマット

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_3D;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBilboard : public CScene
{
public:
	CBilboard(LAYER_TYPE Layer = LAYER_TYPE::LAYER_02);		// デフォルトコンストラクタ
	~CBilboard();	// デストラクタ
	virtual HRESULT Init(void);	// 初期化処理
	virtual void Uninit(void);	// 終了処理
	virtual void Update(void);	// 更新処理
	virtual void Draw(void);	// 描画処理
	static CBilboard* Create(void);	// 生成
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }	// 位置の設定
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }	// 向きの設定
	void SetScale(D3DXVECTOR3 scale) { m_Scale = scale; }	// スケールの設定
	void SetMatrix(D3DXMATRIX mtx) { m_mtxWorld = mtx; }	// マトリッックスの設定
	void SetNumVtx(int nNumVtx) { m_nNumVtx = nNumVtx; }	// 頂点数の設定
	void SetNumIdx(int nNumIdx) { m_nNumIdx = nNumIdx; }	// インデックス数の設定
	void SetTexture(string type) { m_pTexture = CTexture::GetTexture(type); }	// テクスチャの設定
	D3DXVECTOR3 GetPos(void) { return m_Pos; }	// 位置の取得
	D3DXVECTOR3 GetRot(void) { return m_Rot; }	// 向きの取得
	D3DXVECTOR3 GetScale(void) { return m_Scale; }	// スケールの取得
	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }	// マトリッックスの取得
	LPDIRECT3DVERTEXBUFFER9* GetVtxBuff(void) { return &m_pVtxBuff; }	// 頂点バッファの取得
	LPDIRECT3DINDEXBUFFER9* GetIdxBuff(void) { return &m_pIdxBuff; }	// インデックスバッファの取得
	int GetNumVtx(void) { return m_nNumVtx; }	// 頂上数の取得
	int GetNumIdx(void) { return m_nNumIdx; }	// インデックス数の取得

private:
	D3DXVECTOR3	m_Pos;	// 位置
	D3DXVECTOR3 m_Rot;	// ポリゴンの角度
	D3DXVECTOR3 m_Scale;	// スケール
	D3DXMATRIX m_mtxView;	// ビューマトリックス
	D3DXMATRIX m_mtxWorld;// ワールドマトリックス
	LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff; // インデックスバッファへのポインタ
	int m_nNumVtx;	// 頂点数
	int m_nNumIdx;	// インデックス数
};

#endif // !_SCENE3D_H_