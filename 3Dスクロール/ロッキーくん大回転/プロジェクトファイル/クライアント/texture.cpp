//=============================================================================
//
// �e�N�X�`������ [texture.h]
// Author : �H������
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
// �ÓI�����o�ϐ��錾
//=============================================================================
vector<LPDIRECT3DTEXTURE9> CTexture::m_texture = {};
CFileLoad::FILE_LOAD_DATA CTexture::m_file_data = {};
int CTexture::m_num_tex;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	m_file_data.tex_type.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 device;	// �f�o�C�X�̃|�C���^
	int element_max;	// �e�N�X�`���J�E���g�l
	device = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X���擾����

	// �t�@�C����ǂݍ���
	m_file_data.file_name_pas = CFileLoad::Load("data\\TEXTURE\\");

	// �v�f�����擾
	element_max = m_file_data.file_name_pas.second.size();

	// �v�f�����̃��[�v
	for (int count_element = 0; count_element < element_max; count_element++)
	{
		// �^���񋓌^�����
		m_file_data.tex_type[m_file_data.file_name_pas.second[count_element]] = count_element;
	}
	// �p�X�ƃT�C�Y��ۑ�
	m_file_data.pas = m_file_data.file_name_pas.first;
	m_num_tex = m_file_data.file_name_pas.first.size();

	// �T�C�Y����
	for (int nCntTex = 0; nCntTex < m_num_tex; nCntTex++)
	{
		LPDIRECT3DTEXTURE9 tex_buffer = NULL;	// �e�N�X�`���̃o�b�t�@
		//�e�N�X�`���̐���
		D3DXCreateTextureFromFile(	device,
									m_file_data.pas[nCntTex].c_str(),
									&tex_buffer);
		// �z��Ɋi�[
		m_texture.push_back(tex_buffer);
	}
}

//=============================================================================
// �I��
//=============================================================================
void CTexture::Uninit(void)
{
	// �e�N�X�`�������̃��[�v
	for (int nCntTexture = 0; nCntTexture < m_num_tex; nCntTexture++)
	{
		// �e�N�X�`���̔j��
		if (m_texture[nCntTexture] != NULL)
		{
			m_texture[nCntTexture]->Release();
			m_texture[nCntTexture] = NULL;
		}
	}
}