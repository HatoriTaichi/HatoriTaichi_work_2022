//=============================================================================
//
// 文字ポリゴン処理 [textureobj.cpp]
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
#include "mouseinput.h"
#include "sound.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CUiObj::CUiObj()
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

	// カラーの初期化
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
	CMouse *pMouse = CManager::GetMouse();	// マウスの取得
	CFade *pFade = CManager::GetFade();	// フェードの取得
	POINT MousePos;	// マウスの位置
	D3DXVECTOR3 Pos = CScene2D::GetPos();	// ポリゴンの位置取得
	D3DXVECTOR2 Size = CScene2D::GetSize();	// ポリゴンのサイズの取得
	GetCursorPos(&MousePos);	// マウス位置の取得
	ScreenToClient(CManager::GetHandle(), &MousePos);	// クライアント座標に変換

	// テクスチャがSTARTなら
	if (m_TexType == "START")
	{
		// マウスが触れていたら
		if (Pos.x + Size.x >= MousePos.x &&
			Pos.x - Size.x <= MousePos.x &&
			Pos.y + Size.y >= MousePos.y &&
			Pos.y - Size.y <= MousePos.y)
		{
			// α値を薄く
			m_Color.a = 0.5f;

			// カラーの設定
			CScene2D::SetCol(m_Color);

			// 左クリックを押したら && フェードしてなかったら
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == pFade->FADE_NONE)
			{
				// サウンドを再生
				pSound->Play(CSound::SOUND_LABEL_SE_START);

				// ゲーム画面へ遷移
				pFade->SetFade(CManager::MODE::GAME);
			}
		}
		// それ以外
		else
		{
			// α値を最大に
			m_Color.a = 1.0f;

			// カラーの設定
			CScene2D::SetCol(m_Color);
		}
	}
	// テクスチャがRULEなら
	if (m_TexType == "RULE")
	{
		// マウスが触れていたら
		if (Pos.x + Size.x >= MousePos.x &&
			Pos.x - Size.x <= MousePos.x &&
			Pos.y + Size.y >= MousePos.y &&
			Pos.y - Size.y <= MousePos.y)
		{
			// α値を薄く
			m_Color.a = 0.5f;

			// カラーの設定
			CScene2D::SetCol(m_Color);

			// 左クリックを押したら && フェードしてなかったら
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == pFade->FADE_NONE)
			{
				// サウンドを再生
				pSound->Play(CSound::SOUND_LABEL_SE_START);

				// 説明画面へ遷移
				pFade->SetFade(CManager::MODE::MANUAL);
			}
		}
		// それ以外
		else
		{
			// α値を最大に
			m_Color.a = 1.0f;

			// カラーの設定
			CScene2D::SetCol(m_Color);
		}
	}
	// テクスチャがBUCKなら
	if (m_TexType == "BUCK")
	{
		// マウスが触れていたら
		if (Pos.x + Size.x >= MousePos.x &&
			Pos.x - Size.x <= MousePos.x &&
			Pos.y + Size.y >= MousePos.y &&
			Pos.y - Size.y <= MousePos.y)
		{
			// α値を薄く
			m_Color.a = 0.5f;

			// カラーの設定
			CScene2D::SetCol(m_Color);

			// 左クリックを押したら && フェードしてなかったら
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == pFade->FADE_NONE)
			{
				// サウンドを再生
				pSound->Play(CSound::SOUND_LABEL_SE_START);

				// タイトルへ遷移
				pFade->SetFade(CManager::MODE::TITLE);
			}
		}
		// それ以外
		else
		{
			// α値を最大に
			m_Color.a = 1.0f;

			// カラーの設定
			CScene2D::SetCol(m_Color);
		}
	}

	// ポリゴンの更新
	CScene2D::Update();
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CUiObj::Draw(void)
{
	// ポリゴンの描画
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