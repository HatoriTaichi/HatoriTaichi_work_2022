//=============================================================================
//
// 2Dポリゴン処理 [textureobj.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "textureobj.h"
#include "manager.h"
#include "fade.h"
#include "mouseinput.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CUiObj::CUiObj(LAYER_TYPE Layer) : CScene2D(Layer)
{
	m_Color.a = 0.0f;
	m_Color.r = 0.0f;
	m_Color.b = 0.0f;
	m_Color.g = 0.0f;
	m_nChangeCnt = 0;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CUiObj::~CUiObj()
{

}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CUiObj::Init(void)
{
	CScene2D::SetTexType(m_TexType);	// テクスチャの設定
	CScene2D::Init();	// 初期化
	CScene2D::SetPos(m_Pos);	// 位置の設定
	CScene2D::SetSize(m_Size);	// サイズの設定
	m_Color.a = 1.0f;
	m_Color.r = 1.0f;
	m_Color.b = 1.0f;
	m_Color.g = 1.0f;

	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void CUiObj::Uninit(void)
{
	// 破棄
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CUiObj::Update(void)
{
	CSound *pSound = CManager::GetSound();	// サウンドの取得
	D3DXVECTOR3 Pos = CScene2D::GetPos();	// 位置取得
	D3DXVECTOR2 Size = CScene2D::GetSize();	// サイズの取得
	CMouse *pMouse = CManager::GetMouse();	// マウスの取得
	CFade *pFade = CManager::GetFade();	// フェードの取得
	POINT MousePos;	// マウスの位置
	GetCursorPos(&MousePos);	// マウスの位置の取得
	ScreenToClient(CManager::GetHandle(), &MousePos);	// クライアント座標に変換

	// テクスチャの種類によって処理を変える
	if (m_TexType == "MATCHING")
	{
		// α値の反転
		if (m_bAlpha == false)
		{
			m_Color.a -= 0.01f;
			CScene2D::SetCol(m_Color);
			if (m_Color.a <= 0.0f)
			{
				m_bAlpha = true;
			}
		}
		else if (m_bAlpha == true)
		{
			m_Color.a += 0.01f;
			CScene2D::SetCol(m_Color);
			if (m_Color.a >= 1.0f)
			{
				m_bAlpha = false;
			}
		}
	}
	else if (m_TexType == "YES")
	{
		// マウスで触れていたら
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			// α値を薄く
			m_Color.a = 0.5f;

			// カラーの設定
			CScene2D::SetCol(m_Color);

			// 左クリック && フェードしていなかったら
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
			{
				// 再生
				pSound->PlaySound(CSound::X2SOUND_LABEL::GONEXT);

				// マッチング画面に遷移
				pFade->SetFade(CManager::MODE::MATCHING);
			}
		}
		else
		{
			// α値を最大に
			m_Color.a = 1.0f;

			// カラーの設定
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "NO")
	{
		// マウスで触れていたら
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			// α値を薄く
			m_Color.a = 0.5f;

			// カラーの設定
			CScene2D::SetCol(m_Color);

			// 左クリック && フェードしていなかったら
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
			{
				// 再生
				pSound->PlaySound(CSound::X2SOUND_LABEL::GONEXT);

				// タイトル画面に遷移
				pFade->SetFade(CManager::MODE::TITLE);
			}
		}
		else
		{
			// α値を最大に
			m_Color.a = 1.0f;

			// カラーの設定
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "GAMESTART")
	{
		// マウスで触れていたら
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			// α値を薄く
			m_Color.a = 0.5f;

			// カラーの設定
			CScene2D::SetCol(m_Color);

			// 左クリック && フェードしていなかったら
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
			{
				// 再生
				pSound->PlaySound(CSound::X2SOUND_LABEL::GONEXT);

				// マッチング画面に遷移
				pFade->SetFade(CManager::MODE::MATCHING);
			}
		}
		else
		{
			// α値を最大に
			m_Color.a = 1.0f;

			// カラーの設定
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "RELE")
	{
		// マウスで触れていたら
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			// α値を薄く
			m_Color.a = 0.5f;

			// カラーの設定
			CScene2D::SetCol(m_Color);

			// 左クリック && フェードしていなかったら
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
			{
				// 再生
				pSound->PlaySound(CSound::X2SOUND_LABEL::GONEXT);

				// ルール画面に遷移
				pFade->SetFade(CManager::MODE::RULE);
			}
		}
		else
		{
			// α値を最大に
			m_Color.a = 1.0f;

			// カラーの設定
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "MANUAL")
	{
		// マウスで触れていたら
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			m_bSelect = true;

			// カラーの設定
			CScene2D::SetCol(m_Color);
		}
		else
		{
			m_bSelect = false;
			m_Color.a = 1.0f;

			// カラーの設定
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "WEAPON_LETTER")
	{
		// マウスで触れていたら
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			m_bSelect = true;

			// カラーの設定
			CScene2D::SetCol(m_Color);
		}
		else
		{
			m_bSelect = false;
			m_Color.a = 1.0f;

			// カラーの設定
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "WINCONDITION")
	{
		// マウスで触れていたら
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			m_bSelect = true;

			// カラーの設定
			CScene2D::SetCol(m_Color);
		}
		else
		{
			m_bSelect = false;
			m_Color.a = 1.0f;

			// カラーの設定
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "BUCK")
	{
		// マウスで触れていたら
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			// α値を薄く
			m_Color.a = 0.5f;

			// カラーの設定
			CScene2D::SetCol(m_Color);

			// 左クリック && フェードしていなかったら
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
			{
				// 再生
				pSound->PlaySound(CSound::X2SOUND_LABEL::GONEXT);

				// タイトル画面に遷移
				pFade->SetFade(CManager::MODE::TITLE);
			}
		}
		else
		{
			// α値を最大に
			m_Color.a = 1.0f;

			// カラーの設定
			CScene2D::SetCol(m_Color);
		}
	}

	// 更新
	CScene2D::Update();
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CUiObj::Draw(void)
{
	// 描画
	CScene2D::Draw();
}

//=============================================================================
// 生成
//=============================================================================
CUiObj *CUiObj::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string Type)
{
	CUiObj *pUi = NULL;	// UIのポインタ

	// NULLだったら
	if (pUi == NULL)
	{
		// 生成
		pUi = new CUiObj;
	}

	// 引数の代入
	pUi->m_Pos = pos;
	pUi->m_Size = size;
	pUi->m_TexType = Type;

	// 生成されていたら
	if (pUi != NULL)
	{
		// 初期化
		pUi->Init();
	}
	return pUi;
}