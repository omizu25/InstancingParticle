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
const float CEffectManager::MIN_WIDTH = 0.0f;
const float CEffectManager::MAX_WIDTH = 600.0f;
const float CEffectManager::MIN_HEIGHT = 0.0f;
const float CEffectManager::MAX_HEIGHT = 400.0f;
const float CEffectManager::MIN_MOVE = 0.0f;
const float CEffectManager::MAX_MOVE = 100.0f;
const float CEffectManager::STD_MOVE = 20.0f;

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
	m_quantity(0),
	m_width(0.0f),
	m_height(0.0f),
	m_minMove(0.0f),
	m_maxMove(0.0f)
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
	m_width = MAX_WIDTH;
	m_height = MAX_HEIGHT;
	m_minMove = MIN_MOVE;
	m_maxMove = STD_MOVE;
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

	pos.x = FloatRandam(m_width, -m_width);
	pos.y = FloatRandam(m_height, -m_height);

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
// 幅の設定
//--------------------------------------------------
void CEffectManager::SetWidth(const float width)
{
	m_width = width;
}

//--------------------------------------------------
// 幅の取得
//--------------------------------------------------
const float CEffectManager::GetWidth() const
{
	return m_width;
}

//--------------------------------------------------
// 高さの設定
//--------------------------------------------------
void CEffectManager::SetHeight(const float height)
{
	m_height = height;
}

//--------------------------------------------------
// 高さの取得
//--------------------------------------------------
const float CEffectManager::GetHeight() const
{
	return m_height;
}

//--------------------------------------------------
// 移動量の最小値の設定
//--------------------------------------------------
void CEffectManager::SetMinMove(const float move)
{
	m_minMove = move;
}

//--------------------------------------------------
// 移動量の最小値の取得
//--------------------------------------------------
const float CEffectManager::GetMinMove() const
{
	return m_minMove;
}

//--------------------------------------------------
// 移動量の最大値の設定
//--------------------------------------------------
void CEffectManager::SetMaxMove(const float move)
{
	m_maxMove = move;
}

//--------------------------------------------------
// 移動量の最大値の取得
//--------------------------------------------------
const float CEffectManager::GetMaxMove() const
{
	return m_maxMove;
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

		float random = FloatRandam(m_maxMove, m_minMove);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		randomCol.r = col.r + FloatRandam(0.25f, -0.25f);
		randomCol.g = col.g + FloatRandam(0.25f, -0.25f);
		randomCol.b = col.b + FloatRandam(0.25f, -0.25f);

		// 生成
		CEffect::Create(pos, move, randomCol);
	}
}
