//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CAMERA_DESTAANCE (500)		//カメラと注視点の距離
#define CAMERA_ZOOM_MAX (10)	// ズーム
#define CAMERA_ZOOM_NORMAL (90)	// ノーマル

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCamera
{
public:
	CCamera();	// デフォルトコンストラクタ
	~CCamera();	// デフォルトデストラクタ
	HRESULT Init(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR, D3DXVECTOR3 Rot);	// カメラの初期化
	void Uninit(void);	// カメラの終了
	void Update(void);	// カメラの更新
	void SetCamera(void);	// カメラの描画
	static CCamera *Create(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR, D3DXVECTOR3 Rot);	// 生成
	void SetPosV(D3DXVECTOR3 pos) { m_PosV = pos; }	// カメラ位置の設定
	void SetPosR(D3DXVECTOR3 pos) { m_PosR = pos; }	// 注視点位置の設定
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }	// 向きの設定
	D3DXVECTOR3 GetPosV(void) { return m_PosV; }	// カメラ位置の取得
	D3DXVECTOR3 GetPosR(void) { return m_PosR; }	// 注視点位置の取得
	D3DXVECTOR3 GetRot(void) { return m_Rot; }	// 向きの取得
	D3DXVECTOR3 GetVecU(void) { return m_VecU; }	// カメラの上のベクトルの取得
	D3DXMATRIX GetViewMtx(void) { return m_mtxView; }	// ビューマトリックスの取得
	D3DXMATRIX GetProjecMtx(void) { return m_mtxProjection; }	// プロジェクションマトリックスの取得
	float GetDestance(void) { return m_fLong; }	// 長さの取得
private:
	D3DXVECTOR3 m_PosV;	// 視点
	D3DXVECTOR3 m_PosR;	// 注視点
	D3DXVECTOR3 m_Rot;	// カメラの向き
	D3DXVECTOR3 m_VecU;	// 上方向ベクトル
	D3DXMATRIX m_mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;	// ビューマトリックス
	float m_fLong;	// 幅
	float m_fZoom;	// ズーム
};
#endif