//=============================================================================
//
// �����o�͏��� [letter.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "letter.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CLetter::CLetter(CObject::PRIORITY Layer) : CObject(Layer)
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CLetter::~CLetter()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CLetter::Init(void)
{
	LPDIRECT3DDEVICE9 device;	// �f�o�C�X�̃|�C���^
	device = CManager::GetRenderer()->GetDevice();	// �f�o�C�X���擾����

	// �t�H���g�̐���
	LOGFONT log_font = { m_font_size, 0, 0, 0, m_font_weight, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("Mochiy Pop One") };
	HFONT font = CreateFontIndirect(&log_font);

	// �f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐��̓G���[�ƂȂ�
	HDC hdc = GetDC(NULL);
	HFONT old_font = (HFONT)SelectObject(hdc, font);

	// �t�H���g�r�b�g�}�b�v�擾
	UINT code = (UINT)m_text;
	const int gradFlag = GGO_GRAY4_BITMAP;
	int grad = 0; // �K���̍ő�l
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

	// �f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���͂�������Ȃ��̂ŉ��
	SelectObject(hdc, old_font);
	ReleaseDC(NULL, hdc);

	// �e�N�X�`���쐬
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

	// �e�N�X�`���Ƀt�H���g�r�b�g�}�b�v������������
	D3DLOCKED_RECT lockedRect;
	m_texture->LockRect(0, &lockedRect, NULL, 0);	// ���b�N
	DWORD *pTexBuf = (DWORD*)lockedRect.pBits;	// �e�N�X�`���������ւ̃|�C���^

	for (int y = 0; y < font_height; y++)
	{
		for (int x = 0; x < font_width; x++)
		{
			DWORD alpha = mono[y * font_width + x] * 255 / grad;
			pTexBuf[y * font_width + x] = (alpha << 24) | 0x00ffffff;
		}
	}

	m_texture->UnlockRect(0);  // �A�����b�N
	delete[] mono;

	VERTEX_2D *pVtx;	// ���_���

	//���_�o�b�t�@�̐���
	device->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUM,
								D3DUSAGE_WRITEONLY,
								FVF_CUSTOM,
								D3DPOOL_MANAGED,
								&m_vtx_buff,
								NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_vtx_buff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
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

	//���_�o�b�t�@���A�����b�N����
	m_vtx_buff->Unlock();

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CLetter::Uninit(void)
{
	//���_�o�b�t�@�̔j��
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
	Release();	// �����̔j��
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CLetter::Update(void)
{

}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CLetter::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X���擾����

	// �`��
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
// �t�H���g�̃��[�h
//=============================================================================
void CLetter::Load(void)
{
	AddFontResourceEx("data/MochiyPopOne-Regular.ttf", FR_PRIVATE, NULL);	// ���`�Cpop����
}