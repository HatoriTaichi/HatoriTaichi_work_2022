//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "rule.h"
#include "manager.h"
#include "textureobj.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CRule::CRule()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CRule::~CRule()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CRule::Init(void)
{
	FILE *pFile;	// ファイルのポインタ
	D3DXVECTOR3 Pos;	// 位置
	D3DXVECTOR3 Size;	// サイズ
	char aFile[1][128];	// ファイルの文字バッファ

	// ファイルを開く
	pFile = fopen("data/Txtdata/ruledata.txt", "r");

	// ファイルが開けていたら
	if (pFile != NULL)
	{
		int nCnt = 0;	// UIカウント

		// 無限ループ
		while (true)
		{
			// 文字を取得
			fscanf(pFile, "%s", aFile[0]);

			// UI_NUMの文字列を見つけたら
			if (strcmp(aFile[0], "UI_NUM") == 0)
			{
				fscanf(pFile, "%*s%d", &m_nUiNum);
			}
			// SET_UIの文字列を見つけたら
			if (strcmp(aFile[0], "SET_UI") == 0)
			{
				// 無限ループ
				while (true)
				{
					// 文字を取得
					fscanf(pFile, "%s", aFile[0]);

					// TEX_TYPEの文字列を見つけたら
					if (strcmp(aFile[0], "TEX_TYPE") == 0)
					{
						char aTypeBuf[1][64];	// 文字を取得する為のバッファ
						string Type;	// ストリング配列に入れる為のバッファ

						// 文字を取得
						fscanf(pFile, "%*s%s", aTypeBuf[0]);

						// ストリングへ変換
						Type = aTypeBuf[0];

						// 配列に保存
						m_Type.push_back(Type);
					}
					// POSの文字列を見つけたら
					else if (strcmp(aFile[0], "POS") == 0)
					{
						// 位置情報を保存
						fscanf(pFile, "%*s%f%f%f", &Pos.x, &Pos.y, &Pos.z);
					}
					// SIZEの文字列を見つけたら
					else if (strcmp(aFile[0], "SIZE") == 0)
					{
						// サイズ情報を保存
						fscanf(pFile, "%*s%f%f%f", &Size.x, &Size.y, &Size.z);
					}
					// END_UISETの文字列を見つけたら
					else if (strcmp(aFile[0], "END_UISET") == 0)
					{
						// 取得した情報で生成
						m_Ui.push_back(CUiObj::Create(Pos, Size, m_Type[nCnt]));

						// UIカウントアップ
						nCnt++;

						// ループをぬける
						break;
					}
				}
			}
			// ENDの文字列を見つけたら
			else if (strcmp(aFile[0], "END") == 0)
			{
				// ループをぬける
				break;
			}
		}
	}
	else
	{
		cout << "テキストファイルがひらけませんでした。";
	}

	// ファイルを閉じる
	fclose(pFile);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CRule::Uninit(void)
{
	// 破棄
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CRule::Update(void)
{
	// 選択処理
	SelectInfo();
}

//=============================================================================
// 描画処理
//=============================================================================
void CRule::Draw(void)
{

}

//=============================================================================
// 選択処理
//=============================================================================
void CRule::SelectInfo(void)
{
	// UI数分のループ
	for (int nCntUi = 0; nCntUi < m_nUiNum; nCntUi++)
	{
		string Type = m_Ui[nCntUi]->GetType();	// テクスチャの種類を取得
		POINT MousePos;	// マウスの位置を取得
		D3DXVECTOR3 Pos = m_Ui[nCntUi]->GetPos();	// 位置を取得
		D3DXVECTOR2 Size = m_Ui[nCntUi]->GetSize();	// サイズの取得
		bool bSelect = m_Ui[nCntUi]->GetSelect();	// 選んでるかフラグの取得
		GetCursorPos(&MousePos);	// マウスの位置を取得
		ScreenToClient(CManager::GetHandle(), &MousePos);	// クライアント座標に変換

		// テクスチャの種類で処理を変える
		if (Type == "MANUAL")
		{
			// 選んでいたら
			if (bSelect == true)
			{
				// UI数分のループ
				for (int nCntUi = 0; nCntUi < m_nUiNum; nCntUi++)
				{
					// テクスチャの種類を取得
					string UseType = m_Ui[nCntUi]->GetType();

					// 種類によってα値を変える
					if (UseType == "OPERATIONMANUAL" || UseType == "DESCRIPTION")
					{
						m_Ui[nCntUi]->SetAlpha(0.0f);
					}
					else
					{
						m_Ui[nCntUi]->SetAlpha(1.0f);
					}
				}
			}
		}
		else if (Type == "WEAPON_LETTER")
		{
			// 選んでいたら
			if (bSelect == true)
			{
				// UI数分のループ
				for (int nCntUi = 0; nCntUi < m_nUiNum; nCntUi++)
				{
					// テクスチャの種類を取得
					string UseType = m_Ui[nCntUi]->GetType();

					// 種類によってα値を変える
					if (UseType == "WEAPONMANUAL" || UseType == "DESCRIPTION")
					{
						m_Ui[nCntUi]->SetAlpha(0.0f);
					}
					else
					{
						m_Ui[nCntUi]->SetAlpha(1.0f);
					}
				}
			}
		}
		else if (Type == "WINCONDITION")
		{
			// 選んでいたら
			if (bSelect == true)
			{
				// UI数分のループ
				for (int nCntUi = 0; nCntUi < m_nUiNum; nCntUi++)
				{
					// テクスチャの種類を取得
					string UseType = m_Ui[nCntUi]->GetType();

					// 種類によってα値を変える
					if (UseType == "WEAPONMANUAL" || UseType == "OPERATIONMANUAL")
					{
						m_Ui[nCntUi]->SetAlpha(0.0f);
					}
					else
					{
						m_Ui[nCntUi]->SetAlpha(1.0f);
					}
				}
			}
		}
	}
}