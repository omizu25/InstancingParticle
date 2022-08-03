//**************************************************
// 
// effect_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _EFFECT_MANAGER_H_	//このマクロ定義がされてなかったら
#define _EFFECT_MANAGER_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CEffectManager
{
	/* ↓静的メンバ関数↓ */
public:
	static CEffectManager* GetInstanse();	// インスタンスの取得

	/* ↓静的メンバ変数↓ */
private:
	static CEffectManager* m_pEffectManager;	// 自分のクラス

	/* ↓メンバ関数↓ */
private:
	CEffectManager();	// デフォルトコンストラクタ

public:
	~CEffectManager();	// デストラクタ

public:
	void ParticleCreate();	// パーティクル生成
	void Particle(const D3DXVECTOR3& pos, const D3DXCOLOR& col);	// パーティクル

	/* ↓メンバ変数↓ */
private:
	int m_time;	// タイム
};

#endif // !_EFFECT_MANAGER_H_
