//=============================================================================
//
// 3Dオブジェクト処理 [scene3D.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

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
class CScene3D : public CScene
{
public:
	CScene3D();		// デフォルトコンストラクタ
	~CScene3D();	// デストラクタ
	virtual HRESULT Init(void);	// 初期化処理
	virtual void Uninit(void);	// 終了処理
	virtual void Update(void);	// 更新処理
	virtual void Draw(void);	// 描画処理
	static CScene3D* Create(void);	// 生成
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }	// 位置の設定
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }	// 向きのの設定
	void SetMatrix(D3DXMATRIX mtx) { m_mtxWorld = mtx; }	// マトリッックスの設定
	void SetNumVtx(int nNumVtx) { m_nNumVtx = nNumVtx; }	// 頂点数の設定
	void SetNumIdx(int nNumIdx) { m_nNumIdx = nNumIdx; }	// インデックスの設定
	void SetTexture(string type) { m_pTexture = CTexture::GetTexture(type); }	// テクスチャの設定
	D3DXVECTOR3 GetPos(void) { return m_Pos; }	// 位置の取得
	D3DXVECTOR3 GetRot(void) { return m_Rot; }	// 向きの取得
	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }	// マトリッックスの取得 
	LPDIRECT3DVERTEXBUFFER9* GetVtxBuff(void) { return &m_pVtxBuff; }	// 頂点バッファの取得
	LPDIRECT3DINDEXBUFFER9* GetIdxBuff(void) { return &m_pIdxBuff; }	// インデックスバッファの取得
	int GetNumVtx(void) { return m_nNumVtx; }	// 頂点数の取得
	int GetNumIdx(void) { return m_nNumIdx; }	// インデックス数の取得

private:
	D3DXVECTOR3	m_Pos;	// ポリゴンの中心座標
	D3DXVECTOR3 m_Rot;	// ポリゴンの角度
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// インデックスバッファへのポインタ
	int m_nNumVtx;	// 頂点数
	int m_nNumIdx;	// インデックス数
};

#endif // !_SCENE3D_H_