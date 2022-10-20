//=============================================================================
//
// テクスチャ処理 [texture.h]
// Author : 羽鳥太一
//
//=============================================================================
#pragma warning( disable : 4592)
#include <stdio.h>
#include "texture.h"
#include "renderer.h"
#include "manager.h"

namespace file = experimental::filesystem;
using file::recursive_directory_iterator;

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
vector<LPDIRECT3DTEXTURE9> CTexture::m_texture = {};
CFileLoad::FILE_LOAD_DATA CTexture::m_file_data = {};
int CTexture::m_num_tex;

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{
	m_file_data.tex_type.clear();
}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 device;	// デバイスのポインタ
	int element_max;	// テクスチャカウント様
	device = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスを取得する

	// ファイルを読み込む
	m_file_data.file_name_pas = CFileLoad::Load("data\\TEXTURE\\");

	// 要素数を取得
	element_max = m_file_data.file_name_pas.second.size();

	// 要素数分のループ
	for (int count_element = 0; count_element < element_max; count_element++)
	{
		// 疑似列挙型を作る
		m_file_data.tex_type[m_file_data.file_name_pas.second[count_element]] = count_element;
	}
	// パスとサイズを保存
	m_file_data.pas = m_file_data.file_name_pas.first;
	m_num_tex = m_file_data.file_name_pas.first.size();

	// サイズ分回す
	for (int nCntTex = 0; nCntTex < m_num_tex; nCntTex++)
	{
		LPDIRECT3DTEXTURE9 tex_buffer = NULL;	// テクスチャのバッファ
		//テクスチャの生成
		D3DXCreateTextureFromFile(	device,
									m_file_data.pas[nCntTex].c_str(),
									&tex_buffer);
		// 配列に格納
		m_texture.push_back(tex_buffer);
	}
}

//=============================================================================
// 終了
//=============================================================================
void CTexture::Uninit(void)
{
	// テクスチャ数分のループ
	for (int nCntTexture = 0; nCntTexture < m_num_tex; nCntTexture++)
	{
		// テクスチャの破棄
		if (m_texture[nCntTexture] != NULL)
		{
			m_texture[nCntTexture]->Release();
			m_texture[nCntTexture] = NULL;
		}
	}
}