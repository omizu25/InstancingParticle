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
	/* 定義 */
public:
	static const int MIN_INTERVAL;	// 間隔の最小値
	static const int MAX_INTERVAL;	// 間隔の最大値
	static const int MIN_QUANTITY;	// 量の最小値
	static const float MIN_WIDTH;	// 幅の最小値
	static const float MAX_WIDTH;	// 幅の最大値
	static const float MIN_HEIGHT;	// 高さの最小値
	static const float MAX_HEIGHT;	// 高さの最大値
	static const float MIN_MOVE;	// 移動量の最小値
	static const float MAX_MOVE;	// 移動量の最大値
	
private:
	static const int STD_INTERVAL;	// 間隔の標準値
	static const int STD_QUANTITY;	// 量の標準値
	static const float STD_MOVE;	// 移動量の標準値

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
	void Reset();	// リセット
	void ParticleCreate();	// パーティクル生成

public:
	void SetInterval(const int interval);	// 間隔の設定
	const int GetInterval() const;			// 間隔の取得
	void SetQuantity(const int quantity);	// 量の設定
	const int GetQuantity() const;			// 量の取得
	void SetWidth(const float width);		// 幅の設定
	const float GetWidth() const;			// 幅の取得
	void SetHeight(const float height);		// 高さの設定
	const float GetHeight() const;			// 高さの取得
	void SetMinMove(const float move);		// 移動量の最小値の設定
	const float GetMinMove() const;			// 移動量の最小値の取得
	void SetMaxMove(const float move);		// 移動量の最大値の設定
	const float GetMaxMove() const;			// 移動量の最大値の取得

private:
	void Particle(const D3DXVECTOR3& pos, const D3DXCOLOR& col);	// パーティクル

	/* ↓メンバ変数↓ */
private:
	int m_time;			// タイム
	int m_interval;		// 間隔
	int m_quantity;		// 量
	float m_width;		// 幅
	float m_height;		// 高さ
	float m_minMove;	// 移動量の最小値
	float m_maxMove;	// 移動量の最大値
};

#endif // !_EFFECT_MANAGER_H_
