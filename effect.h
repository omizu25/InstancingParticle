//**************************************************
// 
// effect.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _EFFECT_H_	//このマクロ定義がされてなかったら
#define _EFFECT_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CEffect : public CObject3D
{
	/* 定義 */
public:
	static const float MAX_WIDTH;	// 幅の最大値
	static const float MIN_WIDTH;	// 幅の最小値
	static const float STD_WIDTH;	// 幅の標準値
	static const float MAX_HEIGHT;	// 高さの最大値
	static const float MIN_HEIGHT;	// 高さの最小値
	static const float STD_HEIGHT;	// 高さの標準値

private:
	static const int MAX_LIFE;		// 寿命の最大値

	/* ↓静的メンバ関数↓ */
public:
	static CEffect* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXCOLOR& col);	// 生成
	static int GetNumAll();	// 総数の取得
	static void SetScale(const D3DXVECTOR2& scale);	// スケールの設定
	static const D3DXVECTOR2& GetScale();			// スケールの取得

	/* ↓静的メンバ変数↓ */
private:
	static int m_numAll;		// 総数
	static D3DXVECTOR2 m_scale;	// スケール

	/* ↓メンバ関数↓ */
public:
	CEffect();				// デフォルトコンストラクタ
	~CEffect() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

	/* ↓メンバ変数↓ */
private:
	D3DXVECTOR3 m_move;	// 移動量
	int m_life;			// 寿命
};

#endif // !_EFFECT_H_
