//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CTexture
{
	/* ↓定義↓ */
public:
	enum ELabel
	{
		LABEL_NONE = -1,	// 使用しない
		LABEL_Effect = 0,	// エフェクト
		LABEL_MAX
	};

	static const char* FILE_NAME[];	// ファイルパス

	/* ↓メンバ関数↓ */
public:
	CTexture();		// デフォルトコンストラクタ
	~CTexture();	// デストラクタ

public:
	void LoadAll();				// 全ての読み込み
	void Load(ELabel label);	// 指定の読み込み
	void ReleaseAll();			// 全ての破棄
	void Release(ELabel label);	// 指定の破棄
	LPDIRECT3DTEXTURE9 Get(ELabel label);	// 情報の取得

	/* ↓メンバ変数↓ */
private:
	LPDIRECT3DTEXTURE9 s_pTexture[LABEL_MAX];	// テクスチャの情報
};

#endif // !_TEXTURE_H_
