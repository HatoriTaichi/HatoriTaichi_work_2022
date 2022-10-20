//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "game.h"
#include "manager.h"
#include "textureobj.h"
#include "notes.h"
#include "enemy.h"
#include "fade.h"
#include "player.h"
#include "sound.h"
#include "counter.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGame::CGame()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CGame::Init(void)
{
	FILE *pFile;	// ファイルのポインタ
	string FileString;	// ファイルの文字列
	D3DXVECTOR3 Pos;	// 位置
	D3DXVECTOR3 Size;	// サイズ
	char aFile[1][128];	// 文字取得

	CSound *pSound;	// サウンドのポインタ
	pSound = CManager::GetSound();	// サウンドの取得
	pSound->Play(CSound::SOUND_LABEL_BGM_GAME);	// サウンドの再生

	// ファイルを開く
	pFile = fopen("data/Txtdata/gameuidata.txt", "r");

	// 開けていたら
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
				// UI数を保存
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
						CUiObj::Create(Pos, Size, m_Type[nCnt]);

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

	// ファイルを開く
	pFile = fopen("data/Txtdata/gamedata.txt", "r");

	// 開けていたら
	if (pFile != NULL)
	{
		// 無限ループ
		while (true)
		{
			// 文字を取得
			fscanf(pFile, "%s", aFile[0]);

			// NORTS_NUMの文字列を見つけたら
			if (strcmp(aFile[0], "NORTS_NUM") == 0)
			{
				// ノーツの最大数を保存
				fscanf(pFile, "%*s%d", &m_nNotesNum);
			}
			// SET_NORTSの文字列を見つけたら
			if (strcmp(aFile[0], "SET_NORTS") == 0)
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
					// SECONDの文字列を見つけたら
					else if (strcmp(aFile[0], "SECOND") == 0)
					{
						float nSecond;	// 配列に入れる為のバッファ

						// 数を取得
						fscanf(pFile, "%*s%f", &nSecond);

						// 配列に保存
						m_nSecond.push_back(nSecond);
					}
					// END_NOERTSSETの文字列を見つけたら
					else if (strcmp(aFile[0], "END_NOERTSSET") == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(aFile[0], "END") == 0)
			{
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

	// 生成
	CPlayer::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), "PLAYER");
	m_pCombo = CCounter::Create(D3DXVECTOR3(0.0f + 250.0f, 177.0f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 0.0f), 3, "NUMBER");
	m_pScore = CCounter::Create(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, 177.0f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 0.0f), 8, "NUMBER");

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CGame::Uninit(void)
{
	CSound *pSound;	// サウンドのポインタ
	pSound = CManager::GetSound();	// サウンドの取得
	pSound->Stop();	// 停止
	
	// 全て破棄
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	CFade *pFade = CManager::GetFade();	// フェードの取得
	m_nLimit++;	// カウントアップ

	// タイマーが上限に行ったら && フェードしてなかったら
	if (m_nTimer >= (FPS * 5) && pFade->GetFade() == CFade::FADE_NONE)
	{
		// リザルトへ遷移
		pFade->SetFade(CManager::MODE::RESULT);
		m_nNotes = 0;
	}

	// 最後までいったら
	if (m_nNotes == m_nNotesNum)
	{
		// フェード
		m_bFade = true;
		m_nTimer++;
	}

	// 保存されているタイミング && フェードしてない
	if (m_nLimit >= (FPS * m_nSecond[m_nNotes]) && m_bFade == false)
	{
		// 条件にあったノーツの生成
		if (m_NotesType[m_nNotes] == "RIGHT_ARROW")
		{
			CNotes::Create(D3DXVECTOR3(SCREEN_CENTER_X, 100.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), m_NotesType[m_nNotes]);
		}
		else if (m_NotesType[m_nNotes] == "LEFT_ARROW")
		{
			CNotes::Create(D3DXVECTOR3(SCREEN_CENTER_X, 100.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), m_NotesType[m_nNotes]);
		}
		else if (m_NotesType[m_nNotes] == "UP_ARROW")
		{
			CNotes::Create(D3DXVECTOR3(SCREEN_CENTER_X, 100.0f, 0.0f), D3DXVECTOR2(50.0f, 100.0f), m_NotesType[m_nNotes]);
		}
		else if (m_NotesType[m_nNotes] == "DOWN_ARROW")
		{
			CNotes::Create(D3DXVECTOR3(SCREEN_CENTER_X, 100.0f, 0.0f), D3DXVECTOR2(50.0f, 100.0f), m_NotesType[m_nNotes]);
		}
		if (m_nNotes <= (m_nNotesNum - 1))
		{
			m_nNotes++;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{

}