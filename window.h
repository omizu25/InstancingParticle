//**************************************************
// 
// window.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _WINDOW_H_	//このマクロ定義がされてなかったら
#define _WINDOW_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// クラス
//==================================================
class CWindow
{
	/* 定義 */
public:

	/* ↓メンバ関数↓ */
public:
	CWindow();	// デフォルトコンストラクタ
	~CWindow();	// デストラクタ

public:
	HRESULT Init(HINSTANCE hInstance);	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画

public:
	LPDIRECT3DDEVICE9 GetDevice();	// デバイスの取得
	HWND GetWnd();					// ウインドウの取得
	
	/* ↓メンバ変数↓ */
private:
	HWND m_hWnd;					// ウインドウ情報
	LPDIRECT3D9 m_pD3D;				// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Deviceオブジェクト
};

#endif // !_WINDOW_H_
