//**************************************************
// 
// effect_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "effect_manager.h"
#include "utility.h"
#include "effect.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CEffectManager::MIN_INTERVAL = 1;
const int CEffectManager::STD_INTERVAL = 5;
const int CEffectManager::MAX_INTERVAL = 120;
const int CEffectManager::MIN_QUANTITY = 0;
const int CEffectManager::STD_QUANTITY = 300;

//==================================================
// 静的メンバ変数
//==================================================
CEffectManager* CEffectManager::m_pEffectManager = nullptr;

//--------------------------------------------------
// インスタンスの取得
//--------------------------------------------------
CEffectManager* CEffectManager::GetInstanse()
{
	if (m_pEffectManager == nullptr)
	{// nullチェック
		m_pEffectManager = new CEffectManager;
		m_pEffectManager->Reset();
	}

	return m_pEffectManager;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEffectManager::CEffectManager() : 
	m_time(0),
	m_interval(0),
	m_quantity(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEffectManager::~CEffectManager()
{
}

//--------------------------------------------------
// リセット
//--------------------------------------------------
void CEffectManager::Reset()
{
	m_time = 0;
	m_interval = STD_INTERVAL;
	m_quantity = STD_QUANTITY;
}

//--------------------------------------------------
// パーティクル生成
//--------------------------------------------------
void CEffectManager::ParticleCreate()
{
	m_time++;

	if ((m_time % m_interval) != 0)
	{// 一定間隔待ち
		return;
	}

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float width = 600.0f;
	float height = 400.0f;

	//pos.x = FloatRandam(width, -width);
	//pos.y = FloatRandam(height, -height);

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	col.r = FloatRandam(1.0f, 0.0f);
	col.g = FloatRandam(1.0f, 0.0f);
	col.b = FloatRandam(1.0f, 0.0f);

	// パーティクル
	Particle(pos, col);
}

//--------------------------------------------------
// 間隔の設定
//--------------------------------------------------
void CEffectManager::SetInterval(const int interval)
{
	m_interval = interval;
}

//--------------------------------------------------
// 間隔の取得
//--------------------------------------------------
const int CEffectManager::GetInterval() const
{
	return m_interval;
}

//--------------------------------------------------
// 量の設定
//--------------------------------------------------
void CEffectManager::SetQuantity(const int quantity)
{
	m_quantity = quantity;
}

//--------------------------------------------------
// 量の取得
//--------------------------------------------------
const int CEffectManager::GetQuantity() const
{
	return m_quantity;
}

//--------------------------------------------------
// パーティクル
//--------------------------------------------------
void CEffectManager::Particle(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	D3DXCOLOR randomCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;

	for (int i = 0; i < m_quantity; i++)
	{
		rot = (D3DX_PI * 2.0f) / m_quantity * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		float random = FloatRandam(20.0f, 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		randomCol.r = col.r + FloatRandam(0.25f, -0.25f);
		randomCol.g = col.g + FloatRandam(0.25f, -0.25f);
		randomCol.b = col.b + FloatRandam(0.25f, -0.25f);

		// 生成
		CEffect::Create(pos, move, randomCol);
	}
}
