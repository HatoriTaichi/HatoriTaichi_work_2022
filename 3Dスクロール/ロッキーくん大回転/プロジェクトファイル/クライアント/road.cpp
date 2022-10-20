//=============================================================================
//
// road処理 [road.cpp]
// Author : 羽鳥太一 & 加藤瑞葵
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include <random>
#include "road.h"
#include "floor.h"
#include "model_single.h"
#include "manager.h"
#include "starring.h"
#include "trampoline.h"
#include "fan.h"
#include "redbull.h"
#include "airplane.h"
#include "thorn.h"
#include "banana.h"
#include "play_data.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ROAD_GROUND_HAPPEN_PROBABILITY	(9)			// 設置モデルの確率
#define ROAD_SKY_HAPPEN_PROBABILITY		(6)			// 設置モデルの確率
#define ROAD_AIRPLANE_PROBABILITY		(7)			// 飛行機の確率
#define GRONUD_CANDIDATES_POSX_00		(-550)		// 地面モデルX候補位置
#define GRONUD_CANDIDATES_POSX_01		(400)		// 地面モデルX候補位置
#define GRONUD_CANDIDATES_POSX_02		(700)		// 地面モデルX候補位置
#define SKY_CANDIDATES_POS_X_00			(550)		// 空モデルX候補位置
#define SKY_CANDIDATES_POS_Y_00			(350)		// 空モデルY候補位置
#define SKY_CANDIDATES_POS_X_01			(-400)		// 空モデルX候補位置
#define SKY_CANDIDATES_POS_Y_01			(350)		// 空モデルY候補位置
#define SKY_CANDIDATES_POS_X_02			(0)			// 空モデルX候補位置
#define SKY_CANDIDATES_POS_Y_02			(250)		// 空モデルY候補位置

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CRoad::CRoad(CObject::PRIORITY priorty) : CObject(priorty)
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CRoad::~CRoad()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRoad::Init(void)
{
	m_floor = CFloor::Create(m_pos, m_size, D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 床の生成
	m_floor->SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.0f));	// 床のカラーの設定

	// パスワードによってモデルを変える
	if (strncmp("GROUND", CManager::GetInstance()->GetPlayData()->GetPasword().c_str(), 7) == 0)
	{
		
		m_cloud = CModelSingle::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 1500.0f, m_pos.z + 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			                           CXload::X_TYPE_GROUND, NULL, false);
	}
	else if (strncmp("HARD", CManager::GetInstance()->GetPlayData()->GetPasword().c_str(), 5) == 0)
	{
		m_cloud = CModelSingle::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 1500.0f, m_pos.z + 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			                           CXload::X_TYPE_CLOUD_GRAY, NULL, false);
	}
	else
	{
		m_cloud = CModelSingle::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 1500.0f, m_pos.z + 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			                           CXload::X_TYPE_CLOUD, NULL, false);
	}

	// 候補地分のループ
	for (int count_candidate = 0; count_candidate < static_cast<int>(CANDIDATES_PLACE::MAX); count_candidate++)
	{
		// 乱数を生成
		random_device ground_randomdev;
		mt19937 ground_mt(ground_randomdev());
		uniform_int_distribution<> ground_randomangle(0, ROAD_GROUND_HAPPEN_PROBABILITY);
		int groind_happening_type = ground_randomangle(ground_mt);

		// 乱数を生成
		random_device sky_randomdev;
		mt19937 sky_mt(sky_randomdev());
		uniform_int_distribution<> sky_randomangle(0, ROAD_SKY_HAPPEN_PROBABILITY);
		int sky_happening_type = sky_randomangle(sky_mt);

		// 乱数によって位置を変える
		switch ((CANDIDATES_PLACE)count_candidate)
		{
		case CANDIDATES_PLACE::CANDIDATES_00:
			GroundInstallation(groind_happening_type, GRONUD_CANDIDATES_POSX_00);
			break;
		case CANDIDATES_PLACE::CANDIDATES_01:
			GroundInstallation(groind_happening_type, GRONUD_CANDIDATES_POSX_01);
			break;
		case CANDIDATES_PLACE::CANDIDATES_02:
			GroundInstallation(groind_happening_type, GRONUD_CANDIDATES_POSX_02);
			break;
		case CANDIDATES_PLACE::CANDIDATES_03:
			SkyInstallation(sky_happening_type, SKY_CANDIDATES_POS_X_00, SKY_CANDIDATES_POS_Y_00);
			break;
		case CANDIDATES_PLACE::CANDIDATES_04:
			SkyInstallation(sky_happening_type, SKY_CANDIDATES_POS_X_01, SKY_CANDIDATES_POS_Y_01);
			break;
		case CANDIDATES_PLACE::CANDIDATES_05:
			SkyInstallation(sky_happening_type, SKY_CANDIDATES_POS_X_02, SKY_CANDIDATES_POS_Y_02);
			break;
		default:
			break;
		}
	}

	// 位置の設定
	SetPos(m_pos);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRoad::Uninit(void)
{
	// 破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CRoad::Update(void)
{
	// モデルのサイズ取得
	int model_size = m_happening_model.size();

	// 位置とサイズを取得
	m_pos = m_floor->GetPos();
	m_size = m_floor->GetSize();

	// 移動させる
	m_pos.x += m_move_speed;
	
	// 位置を設定
	m_floor->SetPos(m_pos, m_size);

	// 位置を設定
	SetPos(m_pos);

	D3DXVECTOR3 cloudPos = m_cloud->GetPos();	// 位置を取得
	cloudPos.x += m_move_speed;	// 位置を移動
	m_cloud->SetPos(cloudPos);	// 位置を設定
	
	// モデル数分のループ
	for (int model_count = 0; model_count < model_size; model_count++)
	{

		//オブジェクトタイプが飛行機の時
		if (m_happening_model[model_count]->GetObjType() == CObject::OBJTYPE::AIR_PLANE)
		{
			//飛行機型にキャスト
			CAirplane *pAirplane = (CAirplane*)m_happening_model[model_count];

			//プレイヤーに当たっていない状態なら
			if (pAirplane->GetHitPlayer() == false)
			{
				// 位置を取得
				D3DXVECTOR3 pos = m_happening_model[model_count]->GetModel()->GetPos();

				// 移動させる
				pos.x += m_move_speed;

				// 位置を設定
				m_happening_model[model_count]->GetModel()->SetPos(pos);
			}
		}
		// それ以外
		else
		{
			// 位置を取得
			D3DXVECTOR3 pos = m_happening_model[model_count]->GetModel()->GetPos();

			// 移動させる
			pos.x += m_move_speed;

			// 位置を設定
			m_happening_model[model_count]->GetModel()->SetPos(pos);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CRoad::Draw(void)
{

}

//================================================
// 生成
//================================================
CRoad *CRoad::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const float &move_speed)
{
	CRoad *load = nullptr;	// 道のポインタ

	// nullptrなら
	if (load == nullptr)
	{
		// 生成
		load = new CRoad();

		// 生成されていたら
		if (load != nullptr)
		{
			// 引数の代入
			load->m_pos = pos;
			load->m_size = size;
			load->m_move_speed = move_speed;

			// 初期化
			load->Init();
		}
	}
	return load;
}

//================================================
// 道削除処理
//================================================
void CRoad::DeleteRoad(void)
{
	// モデル数を取得
	int model_size = m_happening_model.size();

	// 生成されていたら破棄
	if (m_floor != nullptr)
	{
		m_floor->Uninit();
	}
	if (m_cloud != nullptr)
	{
		m_cloud->Uninit();
	}

	// モデル数分のループ
	for (int model_count = 0; model_count < model_size; model_count++)
	{
		// 生成されていたら
		if (m_happening_model[model_count] != nullptr)
		{
			//オブジェクトタイプが飛行機の時
			if (m_happening_model[model_count]->GetObjType() == CObject::OBJTYPE::AIR_PLANE)
			{
				//飛行機型にキャスト
				CAirplane *pAirplane = (CAirplane*)m_happening_model[model_count];

				//プレイヤーに当たっていない状態なら
				if (pAirplane->GetHitPlayer() == false)
				{
					m_happening_model[model_count]->DeleteModel();
					m_happening_model[model_count]->Uninit();
					m_happening_model[model_count] = NULL;
					m_happening_model.erase(m_happening_model.begin() + model_count);
					model_size = m_happening_model.size();
					model_count--;
				}
			}
			// それ以外
			else
			{
				m_happening_model[model_count]->DeleteModel();
				m_happening_model[model_count]->Uninit();
				m_happening_model[model_count] = NULL;
				m_happening_model.erase(m_happening_model.begin() + model_count);
				model_size = m_happening_model.size();
				model_count--;
			}
		}
	}
}

//================================================
//設置処理
//================================================
void CRoad::SkyInstallation(const int &happening_type, const int &installation_position_x, const int &installation_position_y)
{
	// 乱数を生成
	random_device sky_randomdev;
	mt19937 sky_mt(sky_randomdev());
	uniform_int_distribution<> sky_randomangle(0, ROAD_AIRPLANE_PROBABILITY);
	int airplane_probability = sky_randomangle(sky_mt);

	// モデルの種類
	switch ((CHappenig::HAPPENING_TYPE)happening_type)
	{
	case CHappenig::HAPPENING_TYPE::STARRING:
		m_happening_model.push_back(CStarring::Create(D3DXVECTOR3(m_pos.x + installation_position_x, m_pos.y + installation_position_y, m_pos.z),
													  D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
		break;
	case CHappenig::HAPPENING_TYPE::AIRPLANE:
		switch (airplane_probability)
		{
		case 0:
			m_happening_model.push_back(CAirplane::Create(D3DXVECTOR3(m_pos.x + installation_position_x, m_pos.y + installation_position_y, m_pos.z),
														  D3DXVECTOR3(0.0f, AIRPLANE_INIT_ROT_Y, 0.0f)));
		case 1:
			m_happening_model.push_back(CAirplane::Create(D3DXVECTOR3(m_pos.x + installation_position_x, m_pos.y + installation_position_y, m_pos.z),
														  D3DXVECTOR3(0.0f, AIRPLANE_INIT_ROT_Y, 0.0f)));
		default:
			break;
		}
		break;
	case CHappenig::HAPPENING_TYPE::THORN:
		m_happening_model.push_back(CThorn::Create(D3DXVECTOR3(m_pos.x + installation_position_x, m_pos.y + installation_position_y, m_pos.z),
			                        D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
		break;
	default:
		if (strncmp("HARD", CManager::GetInstance()->GetPlayData()->GetPasword().c_str(), 5) == 0)
		{

			m_happening_model.push_back(CThorn::Create(D3DXVECTOR3(m_pos.x + installation_position_x, m_pos.y + installation_position_y, m_pos.z),
			                        D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
		}
		break;
	}
}

void CRoad::GroundInstallation(const int &happening_type, const int &installation_position)
{
	// モデルの種類
	switch ((CHappenig::HAPPENING_TYPE)happening_type)
	{
	case CHappenig::HAPPENING_TYPE::TRAMPOLINE:
		m_happening_model.push_back(CTrampoline::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y - 1.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
		break;
	case CHappenig::HAPPENING_TYPE::FAN:
		m_happening_model.push_back(CFan::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y - 1.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
		break;
	case CHappenig::HAPPENING_TYPE::REDBULL:
		m_happening_model.push_back(CRedbull::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y - 1.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
		break;
	case CHappenig::HAPPENING_TYPE::BANANA:
		m_happening_model.push_back(CBanana::Create(D3DXVECTOR3(m_pos.x + installation_position, m_pos.y - 1.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
		break;
	default:
		break;
	}
}