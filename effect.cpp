//**************************************************
// 
// effect.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "effect.h"
#include "application.h"
#include "camera.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CEffect::MAX_LIFE = 100;
const float CEffect::STD_WIDTH = 24.0f;
const float CEffect::STD_HEIGHT = 60.0f;

//==================================================
// 静的メンバ変数
//==================================================
int CEffect::m_numAll = 0;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CEffect* CEffect::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXCOLOR& col)
{
	if (m_numAll >= CObject::MAX_OBJECT)
	{// 最大数を越した
		return nullptr;
	}

	CEffect* pEffect = nullptr;

	pEffect = new CEffect;
	
	if (pEffect != nullptr)
	{// nullチェック
		pEffect->Init();
		pEffect->m_move = move;
		pEffect->SetPos(pos);
		pEffect->SetCol(col);
	}

	return pEffect;
}

//--------------------------------------------------
// 総数の取得
//--------------------------------------------------
int CEffect::GetNumAll()
{
	return m_numAll;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEffect::CEffect() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_life(0)
{
	m_numAll++;
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEffect::~CEffect()
{
	m_numAll--;
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEffect::Init()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_life = MAX_LIFE;

	// 初期化
	CObject3D::Init();

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f));

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_Effect);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEffect::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEffect::Update()
{
	m_life--;

	if (m_life <= 0)
	{
		CObject::Release();
		return;
	}

	D3DXVECTOR3 pos = CObject3D::GetPos();

	pos += m_move;

	//慣性・移動量を更新 (減衰させる)
	m_move.x += (0.0f - m_move.x) * 0.05f;
	m_move.y += (0.0f - m_move.y) * 0.05f;

	float size = 5.0f;
	float width = 600.0f - ((STD_WIDTH * 0.5f) + size);
	float height = 400.0f - ((STD_HEIGHT * 0.5f) + size);

	// 範囲内で反射
	InRangeReflect(&pos, &m_move, D3DXVECTOR3(width, height, 0.0f));
	
	// 位置の設定
	CObject3D::SetPos(pos);

	// 向きの設定
	CObject3D::SetRot(atan2f(m_move.x, m_move.y));

	{
		float ratio = ((float)(MAX_LIFE - m_life) / MAX_LIFE);

		D3DXCOLOR col = CObject3D::GetCol();
		col.a = 1.0f - (ratio * ratio);

		// 色の設定
		CObject3D::SetCol(col);
	}

	// 描画
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEffect::Draw()
{
	// 描画
	CObject3D::Draw();
}
