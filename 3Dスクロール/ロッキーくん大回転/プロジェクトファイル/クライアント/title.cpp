//=============================================================================
//
// トロフィールー処理 [trophy.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "title.h"
#include "manager.h"
#include "object2D.h"
#include "play_data.h"
#include "input_mouse.h"
#include "fade.h"
#include "sound.h"
#include "letter.h"
#include "trophy.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TITLE_TO_RESULT_COUNT		(1000)				//リザルトに行くまでの時間
#define TITLE_LOGO_SIZE_X			(366.0f)			//タイトルロゴのサイズX
#define TITLE_LOGO_SIZE_Y			(420.0f)			//タイトルロゴのサイズY
#define TITLE_PRESS_START_SIZE_X	(594.0f)			//PRESS START UIのサイズX
#define TITLE_PRESS_START_SIZE_Y	(84.0f)				//PRESS START UIのサイズY
#define TITLE_PRESS_START_POS_Y		(600.0f)			//PRESS START UIの位置Y

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTitle::CTitle(CObject::PRIORITY Priority):CObject(Priority)
{
	FILE *file;	// ファイルのポインタ

	// ファイルを開く
	file = fopen("data/keyconfig.txt", "r");

	// ファイルが開けていたら
	if (file != NULL)
	{
		// キー数分のループ
		for (int nCntKey = 1; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			char name_buf[1][64];
			string name;

			fscanf(file, "%s", name_buf[0]);
			name = name_buf[0];
			m_letter_single.push_back(name);

			// SJIS → wstring
			int iBufferSize = MultiByteToWideChar(	CP_ACP,
													0,
													name.c_str(),
													-1,
													(wchar_t*)NULL,
													0);

			// バッファの取得
			wchar_t* cpUCS2 = new wchar_t[iBufferSize];

			// SJIS → wstring
			MultiByteToWideChar(	CP_ACP,
									0,
									name.c_str(),
									-1,
									cpUCS2,
									iBufferSize);

			// stringの生成
			wstring utextbuf(cpUCS2, cpUCS2 + iBufferSize - 1);

			// バッファの破棄
			delete[] cpUCS2;

			// キーコンの名前を保存
			m_key_name.push_back(utextbuf);
		}
	}

	// ファイルを閉じる
	fclose(file);
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	// パスワードを初期化
	CManager::GetInstance()->GetPlayData()->SetPasword("");

	CObject2D *object_2D[3];
	CSound *sound;	// サウンドのポインタ
	sound = CManager::GetInstance()->GetSound();	// サウンドの取得

	sound->Stop();	// 停止
	sound->Play(CSound::SOUND_LABEL::TITLE_BGM);	// 再生
	sound->ControllVoice(CSound::SOUND_LABEL::TITLE_BGM, 1.4f);	// 音量調整

	object_2D[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	object_2D[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Bg.png"));
	object_2D[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 0.0f + 200.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.3f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	object_2D[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Title.png"));
	m_click = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 3.0f) / 2.0f, SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.10f) / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT * 0.10f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	m_click->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Click.png"));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(0.0f + 300.0f, SCREEN_HEIGHT - 300.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2f, SCREEN_HEIGHT * 0.15f, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT - 300.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2f, SCREEN_HEIGHT * 0.15f, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 150.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2f, SCREEN_HEIGHT * 0.15f, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(0.0f + 300.0f, SCREEN_HEIGHT - 300.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2f, SCREEN_HEIGHT * 0.15f, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT - 300.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2f, SCREEN_HEIGHT * 0.15f, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button.push_back(CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 150.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2.2f, SCREEN_HEIGHT * 0.15f, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
	m_button[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame.png"));
	m_button[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame.png"));
	m_button[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("frame.png"));
	m_button[3]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("start.png"));
	m_button[4]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("Trophy.png"));
	m_button[5]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial.png"));
	object_2D[2]= CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 0.0f + 75.0f, 0.0f), D3DXVECTOR3(600.0f, 150.0f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	object_2D[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("password_frame.png"));
	m_pas_word = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 0.0f + 95.0f, 0.0f), D3DXVECTOR3(480.0f, 50.0f, 0.0f), static_cast<int>(CObject::PRIORITY::UI));
	m_pas_word->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("password_wordbox.png"));
	m_fade_flag = true;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	SeletMode();
	Tutorial();
	ColUpdate();
	ResultTimer();
	PasWord();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{
	
}

//=============================================================================
// 選択処理
//=============================================================================
void CTitle::SeletMode(void)
{
	CFade *fade;	// フェードクラスのポインタ
	CInputMouse *mouse;	// マウスクラスのポインタ
	D3DXVECTOR3 pos[3];	// 位置
	D3DXVECTOR3 size[3];	// サイズ
	POINT point;	// マウス座標	
	HWND hwnd;	// ウィンドウハンドル
	CSound *sound;	// サウンドクラスのポインタ
	sound = CManager::GetInstance()->GetSound();	// サウンドの取得
	pos[0] = m_button[0]->GetPos();	// ボタンの位置を取得
	size[0] = m_button[0]->GetSize();	// ボタンのサイズを取得
	pos[1] = m_button[1]->GetPos();	// ボタンの位置を取得
	size[1] = m_button[1]->GetSize();	// ボタンのサイズを取得
	pos[2] = m_button[2]->GetPos();	// ボタンの位置を取得
	size[2] = m_button[2]->GetSize();	// ボタンのサイズを取得
	hwnd = CManager::GetInstance()->GetWindowHandle();	// ウィンドウハンドルを取得
	fade = CManager::GetInstance()->GetFade();	// フェード取得
	mouse = CManager::GetInstance()->GetInputMouse();	// マウスクラスの取得
	GetCursorPos(&point);	// マウス座標取得
	ScreenToClient(hwnd, &point);	// クライアント座標に変換

	// ボタンに触れていたら
	if (pos[0].x - size[0].x / 2.0f <= point.x &&
		pos[0].x + size[0].x / 2.0f >= point.x &&
		pos[0].y - size[0].y / 2.0f <= point.y &&
		pos[0].y + size[0].y / 2.0f >= point.y &&
		m_tutorial_flag == false)
	{
		// カラーを変える
		m_button[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_button[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		// 左クリックを押してたら && フェードしていなかったら
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true && fade->GetFade() == CFade::FADE_NONE)
		{
			// パスワードの検索
			if (strncmp("ENDROLL", m_pasword.c_str(), 8) == 0)
			{
				sound->ControllVoice(CSound::SOUND_LABEL::DECISION_SE, 1.2f);	// 音量調整
				sound->Play(CSound::SOUND_LABEL::DECISION_SE);	// 再生
				fade->SetFade(CManager::MODE::ENDING);	// エンドロールに遷移
			}
			// それ以外
			else
			{
				// パスワードを打ち込んでいたら
				if (m_pas_drop == true)
				{
					CManager::GetInstance()->GetPlayData()->SetPasword(m_pasword);	// パスワードを設定
					sound->ControllVoice(CSound::SOUND_LABEL::DECISION_SE, 1.2f);	// 音量調整
					sound->Play(CSound::SOUND_LABEL::DECISION_SE);	// 再生
					fade->SetFade(CManager::MODE::GAME01);	// ゲーム画面に遷移
				}
				// それ以外
				else
				{
					sound->ControllVoice(CSound::SOUND_LABEL::DECISION_SE, 1.2f);	// 音量調整
					sound->Play(CSound::SOUND_LABEL::DECISION_SE);	// 再生
					fade->SetFade(CManager::MODE::GAME01);	// ゲーム画面に遷移
				}
			}
		}
	}
	// それ以外
	else
	{
		// カラーを設定
		m_button[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_button[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// ボタンに触れていたら
	if (pos[1].x - size[1].x / 2.0f <= point.x &&
		pos[1].x + size[1].x / 2.0f >= point.x &&
		pos[1].y - size[1].y / 2.0f <= point.y &&
		pos[1].y + size[1].y / 2.0f >= point.y &&
		m_tutorial_flag == false)
	{
		// カラーを設定
		m_button[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_button[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		// 左クリックを押してたら && フェードしていなかったら
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true && fade->GetFade() == CFade::FADE_NONE)
		{
			sound->ControllVoice(CSound::SOUND_LABEL::DECISION_SE, 1.2f);	// 音量調整
			sound->Play(CSound::SOUND_LABEL::DECISION_SE);	// 再生
			fade->SetFade(CManager::MODE::TROPHY);	// トロフィー画面に遷移
		}
	}
	// それ以外
	else
	{
		// カラーを設定
		m_button[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_button[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// ボタンに触れていたら
	if (pos[2].x - size[2].x / 2.0f <= point.x &&
		pos[2].x + size[2].x / 2.0f >= point.x &&
		pos[2].y - size[2].y / 2.0f <= point.y &&
		pos[2].y + size[2].y / 2.0f >= point.y &&
		m_tutorial_flag == false)
	{
		// カラーを設定
		m_button[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_button[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		// 左クリックを押してたら
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			sound->ControllVoice(CSound::SOUND_LABEL::DECISION_SE, 1.2f);	// 音量調整
			sound->Play(CSound::SOUND_LABEL::DECISION_SE);	// 再生

			for (int count_tutorial = 0; count_tutorial < 5; count_tutorial++)
			{
				m_tutorial.push_back(CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), static_cast<int>(CObject::PRIORITY::UI)));
			}
			m_tutorial.push_back(CObject2D::Create(D3DXVECTOR3(0.0f + 80.0f, 0.0f + 50.0f, 0.0f), D3DXVECTOR3(80.0f, 80.0f, 70.0f), static_cast<int>(CObject::PRIORITY::UI)));
			m_tutorial[0]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial_up.png"));
			m_tutorial[1]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial_arrow.png"));
			m_tutorial[2]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial_picture_left.png"));
			m_tutorial[3]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial_picture_light.png"));
			m_tutorial[4]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("tutorial_under.png"));
			m_tutorial[5]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("arrow.png"));
			m_tutorial_flag = true;
		}
	}
	else
	{
		// カラーを設定
		m_button[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_button[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

//=============================================================================
// チュートリアル
//=============================================================================
void CTitle::Tutorial(void)
{
	CInputMouse *mouse;	// マウスクラスのポインタ
	POINT point;	// マウス座標
	HWND hwnd;	// ウィンドウハンドル
	CSound *sound;	// サウンドクラスのポインタ
	sound = CManager::GetInstance()->GetSound();	// サウンドの取得
	hwnd = CManager::GetInstance()->GetWindowHandle();	// ウィンドウハンドルの取得
	mouse = CManager::GetInstance()->GetInputMouse();	// マウスクラスの取得
	GetCursorPos(&point);	// マウス座標の取得
	ScreenToClient(hwnd, &point);	// クライアント座標に変換

	// チュートリアルフラグ立ってたら
	if (m_tutorial_flag == true)
	{
		D3DXVECTOR3 pos_buck;	// 位置
		D3DXVECTOR3 size_buck;	// サイズ

		// 位置とサイズを取得
		pos_buck = m_tutorial[5]->GetPos();
		size_buck = m_tutorial[5]->GetSize();

		// マウスが触れていたら
		if (pos_buck.x - size_buck.x / 2.0f <= point.x &&
			pos_buck.x + size_buck.x / 2.0f >= point.x &&
			pos_buck.y - size_buck.y / 2.0f <= point.y &&
			pos_buck.y + size_buck.y / 2.0f >= point.y)
		{
			// カラーを設定
			m_tutorial[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			// 左クリックを押していたら
			if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
			{
				sound->ControllVoice(CSound::SOUND_LABEL::CANSEL_SE, 1.2f);	// 音量調整
				sound->Play(CSound::SOUND_LABEL::CANSEL_SE);	// 再生

				// サイズを取得
				int tutorial_size = m_tutorial.size();

				// サイズ分のループ
				for (int count_tutorial = tutorial_size - 1; count_tutorial >= 0; count_tutorial--)
				{
					// 破棄
					m_tutorial[count_tutorial]->Uninit();
					m_tutorial[count_tutorial] = nullptr;
					m_tutorial.pop_back();
				}
				m_tutorial_flag = false;
			}
		}
		// それ以外
		else
		{
			// カラーを設定
			m_tutorial[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

//=============================================================================
// カラー変更
//=============================================================================
void CTitle::ColUpdate(void)
{
	D3DXCOLOR col_click = m_click->GetCol();	// カラーを取得

	// α値を条件によって変える
	if (col_click.a >= 1.0f)
	{
		m_fade_flag = true;
	}
	else if (col_click.a <= 0.0f)
	{
		m_fade_flag = false;
	}

	if (m_fade_flag == true)
	{
		col_click.a -= 0.01f;
		m_click->SetCol(col_click);
	}
	else
	{
		col_click.a += 0.01f;
		m_click->SetCol(col_click);
	}
}

//=============================================================================
// リザルトタイマー
//=============================================================================
void CTitle::ResultTimer(void)
{
	CFade *fade;	// フェードクラス
	CInputMouse *mouse;	// マウスクラス
	fade = CManager::GetInstance()->GetFade();	// フェードクラスを取得
	mouse = CManager::GetInstance()->GetInputMouse();	// マウスクラスの取得

	// タイマー加算
	m_result_timer++;

	// 一定時間がたったら && マウスクラスが移動していなかったら
	if (m_result_timer >= TITLE_TO_RESULT_COUNT &&
		mouse->GetMouseState().lX == 0 &&
		mouse->GetMouseState().lY == 0)
	{
		// タイマー初期化
		m_result_timer = 0;

		// フェードしてなかったら && チュートリアルフラグが立ってなかったら && パスワードを入力してなかったら
		if (fade->GetFade() == CFade::FADE_NONE &&
			m_tutorial_flag == false && m_pas_drop == false)
		{
			// リザルト画面に遷移
			fade->SetFade(CManager::MODE::RESULT);
		}
	}
}

//=============================================================================
// パスワード入力
//=============================================================================
void CTitle::PasWord(void)
{
	CInputKeyboard *key;	// キーボードクラスのポインタ
	CInputMouse *mouse;	// マウスクラスのポインタ
	POINT point;	// マウス座標
	HWND hwnd;	// ウィンドウハンドル
	string text_buf;	// テキストのバッファ
	pair<int, bool> key_update;	// キーバインドのペア
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 size;	// サイズ
	key = CManager::GetInstance()->GetInputKeyboard();	// キーボードクラスの取得
	hwnd = CManager::GetInstance()->GetWindowHandle();	// ウィンドウハンドルの取得
	mouse = CManager::GetInstance()->GetInputMouse();	// マウスクラスの取得
	GetCursorPos(&point);	// マウス座標の取得
	ScreenToClient(hwnd, &point);	// クライアント座標に変換

	pos = m_pas_word->GetPos();	// 入力欄の位置
	size = m_pas_word->GetSize();	// 入力欄のサイズ

	// マウスが触れていたら
	if (pos.x - size.x / 2.0f <= point.x &&
		pos.x + size.x / 2.0f >= point.x &&
		pos.y - size.y / 2.0f <= point.y &&
		pos.y + size.y / 2.0f >= point.y)
	{
		// 左クリックを押していたら
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			m_pas_drop = true;
		}
	}
	// それ以外
	else
	{
		// 左クリックを押していたら
		if (mouse->GetTrigger(CInputMouse::MOUSE_TYPE_LEFT) == true)
		{
			// パスワードを設定
			CManager::GetInstance()->GetPlayData()->SetPasword(m_pasword);
			m_pas_drop = false;
		}
	}

	// 入力していたら
	if(m_pas_drop == true)
	{
		// カラーの設定
		m_pas_word->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		// 何かキーを押していたら
		key_update = key->GetAllKeyUpdate();

		// キーを押していたら
		if (key_update.second == true)
		{
			// エンター以外で && バックスペース以外
			if (key_update.first != DIK_RETURN && key_update.first != DIK_BACK)
			{
				// 文字制限いないなら
				if (m_letter_limitl < 15)
				{
					// 名前の取得
					int name_size = m_key_name[key_update.first].size();

					// 名前分のループ
					for (int count_name = 0; count_name < name_size; count_name++)
					{
						// 文字を生成
						m_pas_font.push_back(new CLetter);

						m_pas_font[m_count_letter]->SetPos(D3DXVECTOR3((((SCREEN_WIDTH - 300.0f) - (480.0f / 2.0f)) + 32.5f) + (30.0f * m_count_letter), (((0.0f + 95.f) - (50.0f / 2.0f)) + 25.0f), 0.0f));
						m_pas_font[m_count_letter]->SetSize(D3DXVECTOR3(15.0f, 15.0f, 0.0f));
						m_pas_font[m_count_letter]->SetText(m_key_name[key_update.first][count_name]);
						m_pas_font[m_count_letter]->SetFontSize(300);
						m_pas_font[m_count_letter]->SetFontWeight(500);
						m_pas_font[m_count_letter]->Init();
						m_count_letter++;
						m_pasword.push_back(m_letter_single[key_update.first][count_name]);
						m_letter_limitl++;
					}
				}
			}
			// バックスペースなら
			else if(key_update.first == DIK_BACK)
			{
				CManager::GetInstance()->GetPlayData()->SetPasword("");	//パスワードを空に

				// サイズを取得
				int font_size = m_pas_font.size();

				// サイズ分のループ
				for (int count_font = 0; count_font < font_size; count_font++)
				{
					// 破棄
					m_pas_font[count_font]->Uninit();
					m_pas_font.erase(m_pas_font.begin());
					font_size = m_pas_font.size();
					count_font--;
					m_count_letter = 0;
					m_letter_limitl = 0;
				}
				// サイズを取得
				int pas_size = m_pasword.size();

				// サイズ分のループ
				for (int count_pas = 0; count_pas < pas_size; count_pas++)
				{
					// 破棄
					m_pasword.pop_back();
				}
			}
			// エンターなら
			else if (key_update.first == DIK_RETURN)
			{
				// パスワードを設定
				CManager::GetInstance()->GetPlayData()->SetPasword(m_pasword);
				m_pas_drop = false;
			}
		}
	}
	// それ以外
	else
	{
		m_pas_word->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}