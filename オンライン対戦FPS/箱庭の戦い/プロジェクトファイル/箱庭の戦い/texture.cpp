//=============================================================================
//
// テクスチャ処理 [texture.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
vector<LPDIRECT3DTEXTURE9>	CTexture::m_pTexture;	//テクスチャ
int CTexture::m_nTextureMax;	// 読み込むテクスチャの最大数
vector<string> CTexture::m_FilePas;	// ファイルのパス
vector<string> CTexture::m_Enum;	// 文字列の保存
map<string, int> CTexture::m_TexType;	// 文字列とintのmap

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTexture::CTexture()
{
	m_nTextureMax = NULL;
	m_TexType.clear();
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスを取得する
	FILE *pFile;	// ファイルのポインタ
	char aFile[64];	// ファイルの文字列バッファ

	// ファイルを開く
	pFile = fopen("data/Txtdata/texturedata.txt", "r");

	// ファイルが開けていたら
	if (pFile != NULL)
	{
		// 無限ループ
		while (true)
		{
			// ファイルの文字列を取得
			fscanf(pFile, "%s", &aFile[0]);

			// TEX_NUMの文字列を見つけたら
			if (strcmp(&aFile[0], "TEX_NUM") == 0)
			{
				fscanf(pFile, "%s", &aFile[0]);	// =
				fscanf(pFile, "%d", &m_nTextureMax);	// テクスチャ総数
			}
			// ENUM_NAMEの文字列を見つけたら
			else if (strcmp(&aFile[0], "ENUM_NAME") == 0)
			{
				// テクスチャ総数分のループ
				for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
				{
					int nNumber;	// 列挙番号
					char aEnumBuf[1][64];	// 取得してくる為のバッファ
					string Enum;	// string型にする為のバッファ

					// 文字と数字を取得
					fscanf(pFile, "%s%s%d%*s%*s", aEnumBuf[0], &aFile[0], &nNumber);

					// stringへ変換
					Enum = aEnumBuf[0];

					// 配列にプッシュ
					m_Enum.push_back(Enum);

					// 疑似列挙型の生成
					m_TexType[Enum] = nNumber;
				}
			}
			// TEXTURE_PASの文字列を見つけたら
			else if (strcmp(&aFile[0], "TEXTURE_PAS") == 0)
			{
				// テクスチャ総数分のループ
				for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
				{
					char aPasBuf[1][64];	// 取得してくる為のバッファ
					string Pas;	// string型にする為のバッファ

					// パスを取得
					fscanf(pFile, "%s", aPasBuf[0]);

					// stringへ変換
					Pas = aPasBuf[0];

					// 配列に保存
					m_FilePas.push_back(Pas);
				}
			}
			//ENDの文字列を見つけたら
			else if (strcmp(&aFile[0], "END") == 0)
			{
				// ループ抜け
				break;
			}
		}
	}
	else
	{
		printf("テクスチャデータが読み取れませんでした。");
	}

	// ファイルを閉じる
	fclose(pFile);

	// テクスチャ総数分のループ
	for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
	{
		LPDIRECT3DTEXTURE9 pTex = NULL;	// テクスチャのバッファ

		D3DXCreateTextureFromFile(	pDevice,
									m_FilePas[nCnt].c_str(),	// テクスチャパス
									&pTex);
		// テクスチャの保存
		m_pTexture.push_back(pTex);
	}
}

//=============================================================================
// 終了
//=============================================================================
void CTexture::Uniinit(void)
{
	// テクスチャ総数分のループ
	for (int nCntTexture = 0; nCntTexture < m_nTextureMax; nCntTexture++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCntTexture] != NULL)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture] = NULL;
		}
	}
}