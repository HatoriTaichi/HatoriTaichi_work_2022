//=============================================================================
//
// 文字出力処理 [letter.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "letter.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CLetter::CLetter(CObject::PRIORITY Layer) : CObject(Layer)
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CLetter::~CLetter()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CLetter::Init(void)
{
	LPDIRECT3DDEVICE9 device;	// デバイスのポインタ
	device = CManager::GetRenderer()->GetDevice();	// デバイスを取得する

	// フォントの生成
	LOGFONT log_font = { m_font_size, 0, 0, 0, m_font_weight, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("Mochiy Pop One") };
	HFONT font = CreateFontIndirect(&log_font);

	// デバイスにフォントを持たせないとGetGlyphOutline関数はエラーとなる
	HDC hdc = GetDC(NULL);
	HFONT old_font = (HFONT)SelectObject(hdc, font);

	// フォントビットマップ取得
	UINT code = (UINT)m_text;
	const int gradFlag = GGO_GRAY4_BITMAP;
	int grad = 0; // 階調の最大値
	switch (gradFlag) 
	{
	case GGO_GRAY2_BITMAP: 
		grad = 4;
		break;
	case GGO_GRAY4_BITMAP:
		grad = 16;
		break;
	case GGO_GRAY8_BITMAP:
		grad = 64;
		break;
	}

	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	GLYPHMETRICS gm;
	CONST MAT2 mat = { { 0,1 },{ 0,0 },{ 0,0 },{ 0,1 } };
	DWORD size = GetGlyphOutlineW(hdc, code, gradFlag, &gm, 0, NULL, &mat);
	BYTE *mono = new BYTE[size];
	GetGlyphOutlineW(hdc, code, gradFlag, &gm, size, mono, &mat);

	// デバイスコンテキストとフォントハンドルはもういらないので解放
	SelectObject(hdc, old_font);
	ReleaseDC(NULL, hdc);

	// テクスチャ作成
	int font_width = (gm.gmBlackBoxX + 3) / 4 * 4;
	int font_height = gm.gmBlackBoxY;

	device->CreateTexture(	font_width,
							font_height,
							1,
							0,
							D3DFMT_A8R8G8B8,
							D3DPOOL_MANAGED, 
							&m_texture,
							NULL);

	// テクスチャにフォントビットマップ情報を書き込み
	D3DLOCKED_RECT lockedRect;
	m_texture->LockRect(0, &lockedRect, NULL, 0);	// ロック
	DWORD *pTexBuf = (DWORD*)lockedRect.pBits;	// テクスチャメモリへのポインタ

	for (int y = 0; y < font_height; y++)
	{
		for (int x = 0; x < font_width; x++)
		{
			DWORD alpha = mono[y * font_width + x] * 255 / grad;
			pTexBuf[y * font_width + x] = (alpha << 24) | 0x00ffffff;
		}
	}

	m_texture->UnlockRect(0);  // アンロック
	delete[] mono;

	VERTEX_2D *pVtx;	// 頂点情報

	//頂点バッファの生成
	device->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUM,
								D3DUSAGE_WRITEONLY,
								FVF_CUSTOM,
								D3DPOOL_MANAGED,
								&m_vtx_buff,
								NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_vtx_buff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (font_width / m_size.x), m_pos.y - (font_height / m_size.y), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (font_width / m_size.x), m_pos.y - (font_height / m_size.y), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (font_width / m_size.x), m_pos.y + (font_height / m_size.y), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (font_width / m_size.x), m_pos.y + (font_height / m_size.y), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_vtx_buff->Unlock();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CLetter::Uninit(void)
{
	//頂点バッファの破棄
	if (m_vtx_buff != NULL)
	{
		m_vtx_buff->Release();
		m_vtx_buff = NULL;
	}
	if (m_texture != NULL)
	{
		m_texture->Release();
		m_texture = NULL;
	}
	Release();	// 自分の破棄
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CLetter::Update(void)
{

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CLetter::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	// デバイスを取得する

	// 描画
	pDevice->SetStreamSource(	0,
								m_vtx_buff,
								0,
								sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_CUSTOM);

	pDevice->SetTexture(0, m_texture);

	pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,
							0,
							2);
}

//=============================================================================
// フォントのロード
//=============================================================================
void CLetter::Load(void)
{
	AddFontResourceEx("data/MochiyPopOne-Regular.ttf", FR_PRIVATE, NULL);	// モチイpopワン
}