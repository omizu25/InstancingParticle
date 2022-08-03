//**************************************************
// 
// imugi_property.h
// Author  : katsuki mizuki
// Author  : Yuda Kaito
// 
//**************************************************
#ifndef _IMGUI_PROPERTY_H_	// このマクロが定義されてなかったら
#define _IMGUI_PROPERTY_H_	// 2重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "imgui.h"
#include <d3dx9.h>

//--------------------------------------------------
// 入力検知
//--------------------------------------------------
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class CImguiProperty
{
	/* 定義 */
private:
	static const char* FontPath;			// 使用するフォント
	static const float FontSize;			// フォントサイズ
	static const ImVec4 TitleBarColor;		// タイトルバーの色
	static const ImVec4 SliderBarColor;		// スライダーバーの色
	static const ImVec4 CheckMarkColor;		// チェックマークの色
	static const ImVec4 ScrollBarColor;		// スクロールバーの色
	static const ImVec4 HeaderColor;		// ヘッダーの基本色
	static const ImVec4 HeaderHoveredColor;	// ヘッダーにマウスカーソルを合わせた時の色
	static const ImVec4 HeaderActiveColor;	// ヘッダークリック時の色
	static const char*	WINDOW_NAME;		// ウインドウの名前 (キャプションに表示)

	/* メンバ関数 */
public:
	CImguiProperty();	// デフォルトコンストラクタ
	~CImguiProperty();	// デストラクタ

public:
	HWND Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice);
	void Uninit(HWND hWnd, WNDCLASSEX wcex);
	void Update();
	void Draw();

public:
	bool GetInstancing();	// インスタンシングを使用するかどうか

private:
	void ColorPalette4(const char* label, float col[4]);
	void ColorPalette(float color[4], float backup_color[4], ImGuiColorEditFlags flags);
	ImVec4 ColorToImVec4(const D3DXCOLOR& color);
	D3DXCOLOR ImVec4ToColor(const ImVec4& vec);

	/* メンバ変数 */
private:
	bool m_window;		// ウインドウを使用するかどうか
	bool m_instancing;	// インスタンシングを使用するかどうか
};

#endif // !_IMGUI_PROPERTY_H_
