//=============================================================================
//
// テクスチャ処理 [texture.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "fileload.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTexture
{
public:
	CTexture();	//コンストラクタ
	~CTexture();	//デストラクタ
	static void Init(void);	// テクスチャの生成
	static void Uninit(void);	// 終了
	static LPDIRECT3DTEXTURE9 GetTexture(const string &texType) { return m_texture[m_file_data.tex_type[texType]]; }	// テクスチャの取得
	static LPDIRECT3DTEXTURE9 GetTexture(const int &nCnt) { return m_texture[nCnt]; }	// テクスチャの取得
	static string GetPas(const int &nCntTex) { return m_file_data.pas[nCntTex]; }	// テクスチャのパス取得処理
	static int GetNum(void) { return m_num_tex; }	// テクスチャの総数取得処理

private:
	static vector<LPDIRECT3DTEXTURE9> m_texture;	// テクスチャ
	static CFileLoad::FILE_LOAD_DATA m_file_data;	// テクスチャデータ
	static int m_num_tex;	// テクスチャの総数
};

#endif