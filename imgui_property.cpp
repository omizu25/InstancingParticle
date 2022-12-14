//**************************************************
//
// Hackathon ( imgui_property.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui_property.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

#include "main.h"
#include "application.h"
#include "texture.h"
#include "object.h"
#include "effect.h"
#include "effect_manager.h"

//==================================================
// 定義
//==================================================
const char* CImguiProperty::FontPath = "data/FONT/GenShinGothic-Bold.ttf";				// 使用するフォント
const float CImguiProperty::FontSize = 18.0f;											// フォントサイズ
const ImVec4 CImguiProperty::TitleBarColor = ImVec4(0.615f, 0.215f, 0.341f, 1.0f);		// タイトルバーの色
const ImVec4 CImguiProperty::SliderBarColor = ImVec4(0.615f, 0.215f, 0.341f, 1.0f);		// スライダーバーの色
const ImVec4 CImguiProperty::CheckMarkColor = ImVec4(0.615f, 0.215f, 0.341f, 1.0f);		// チェックマークの色
const ImVec4 CImguiProperty::ScrollBarColor = ImVec4(0.0f, 0.7f, 0.2f, 1.0f);			// スクロールバーの色
const ImVec4 CImguiProperty::HeaderColor = ImVec4(1.0f, 1.0f, 1.0f, 0.309f);			// ヘッダーの基本色
const ImVec4 CImguiProperty::HeaderHoveredColor = ImVec4(1.0f, 1.0f, 1.0f, 0.75f);		// ヘッダーにマウスカーソルを合わせた時の色
const ImVec4 CImguiProperty::HeaderActiveColor = ImVec4(1.0f, 1.0f, 1.0f, 0.85f);		// ヘッダークリック時の色
const char* CImguiProperty::WINDOW_NAME = "test";

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CImguiProperty::CImguiProperty() :
	m_window(true),
	m_instancing(true)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CImguiProperty::~CImguiProperty()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HWND CImguiProperty::Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
{
#ifdef _DEBUG

	m_window = true;
	m_instancing = true;

	// ウインドウの表示
	::ShowWindow(hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(hWnd);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// 文字の設定
	ImGuiIO& io = ImGui::GetIO();

	// スタイルの設定
	ImGui::StyleColorsDark();

	// タイトルバーの色設定
	ImGui::PushStyleColor(ImGuiCol_TitleBg, TitleBarColor);
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, TitleBarColor);
	ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, TitleBarColor);

	// スライドの色設定
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, SliderBarColor);
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, SliderBarColor);

	// チェックマークの色設定
	ImGui::PushStyleColor(ImGuiCol_CheckMark, CheckMarkColor);

	// スクロールの色設定
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ScrollBarColor);

	// ヘッダーの色設定
	ImGui::PushStyleColor(ImGuiCol_Header, HeaderColor);
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, HeaderHoveredColor);
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, HeaderActiveColor);

	// プラットフォームの設定/Renderer backends
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	//io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF(FontPath, FontSize, nullptr, io.Fonts->GetGlyphRangesJapanese());
	return S_OK;
#endif // _DEBUG
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CImguiProperty::Uninit(HWND hWnd, WNDCLASSEX wcex)
{
#ifdef _DEBUG

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// ウインドウの破壊
	::DestroyWindow(hWnd);

	// ウインドウクラスの登録を解除
	::UnregisterClass(wcex.lpszClassName, wcex.hInstance);

#endif // _DEBUG
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CImguiProperty::Update()
{
#ifdef _DEBUG

	if (!m_window)
	{// ウインドウを使用しない
		return;
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// ウインドウの起動時の場所
	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(350, 400), ImGuiCond_Once);

	// ウインドウの命名
	ImGui::Begin(WINDOW_NAME, nullptr, ImGuiWindowFlags_MenuBar);

	// FPSの表示
	ImGui::Text(u8"FPS  : %.2f", ImGui::GetIO().Framerate);

	// オブジェクトの総数の表示
	ImGui::Text(u8"オブジェクト  : %5d", CObject::GetNumAll());

	// エフェクトの総数の表示
	ImGui::Text(u8"エフェクト  : %5d", CEffect::GetNumAll());
	ImGui::Separator();	// 区切り線

	ImGui::Checkbox(u8"インスタンシング", &m_instancing);
	ImGui::Separator();	// 区切り線

	{// サイズ
		D3DXVECTOR2 scale = CEffect::GetScale();
		ImGui::DragFloat("scale.x", &scale.x, 0.1f, CEffect::MIN_WIDTH, CEffect::MAX_WIDTH);
		ImGui::DragFloat("scale.y", &scale.y, 0.1f, CEffect::MIN_HEIGHT, CEffect::MAX_HEIGHT);
		CEffect::SetScale(scale);
	}

	CEffectManager* pEffect = CEffectManager::GetInstanse();

	{// 間隔
		int interval = pEffect->GetInterval();
		ImGui::DragInt("interval", &interval, 0.5f, CEffectManager::MIN_INTERVAL, CEffectManager::MAX_INTERVAL);
		pEffect->SetInterval(interval);
	}

	{// 量
		int quantity = pEffect->GetQuantity();
		ImGui::DragInt("quantity", &quantity, 10.0f, CEffectManager::MIN_QUANTITY, CObject::MAX_OBJECT);
		pEffect->SetQuantity(quantity);
	}

	{// 幅
		float width = pEffect->GetWidth();
		ImGui::DragFloat("width", &width, 5.0f, CEffectManager::MIN_WIDTH, CEffectManager::MAX_WIDTH);
		pEffect->SetWidth(width);
	}

	{// 高さ
		float height = pEffect->GetHeight();
		ImGui::DragFloat("height", &height, 5.0f, CEffectManager::MIN_HEIGHT, CEffectManager::MAX_HEIGHT);
		pEffect->SetHeight(height);
	}

	{// 移動量
		float minMove = pEffect->GetMinMove();
		float maxMove = pEffect->GetMaxMove();

		ImGui::DragFloat("minMove", &minMove, 5.0f, CEffectManager::MIN_MOVE, CEffectManager::MAX_MOVE);
		
		if (minMove > maxMove)
		{// 指定の値より大きい
			maxMove = minMove;
		}

		ImGui::DragFloat("maxMove", &maxMove, 5.0f, CEffectManager::MIN_MOVE, CEffectManager::MAX_MOVE);

		if (maxMove < minMove)
		{// 指定の値より小さい
			minMove = maxMove;
		}
		
		pEffect->SetMinMove(minMove);
		pEffect->SetMaxMove(maxMove);
	}

	{// 色のランダムするかどうか
		if (ImGui::CollapsingHeader("Color"))
		{
			bool random = pEffect->GetColRandom();
			ImGui::Checkbox("random", &random);
			pEffect->SetColRandom(random);

			if (random)
			{// ランダムする
				int timing = pEffect->GetChangeTiming();
				ImGui::DragInt("timing", &timing, 1.0f, CEffectManager::MIN_CHANGE_TIMING, CEffectManager::MAX_CHANGE_TIMING);
				pEffect->SetChangeTiming(timing);
			}
			else
			{// ランダムしない
				D3DXCOLOR col = pEffect->GetCol();
				ColorPalette4("color", (float*)&col);
				pEffect->SetCol(col);
			}
		}
	}

	ImGui::End();

#endif // _DEBUG
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CImguiProperty::Draw()
{
#ifdef _DEBUG

	if (!m_window)
	{// ウインドウを使用しない
		return;
	}

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

#endif // _DEBUG
}

//--------------------------------------------------
// インスタンシングを使用するかどうか
//--------------------------------------------------
bool CImguiProperty::GetInstancing()
{
	return m_instancing;
}

//--------------------------------------------------
// カラーパレット4
//--------------------------------------------------
void CImguiProperty::ColorPalette4(const char * label, float col[4])
{
	//カラーパレット
	ImGuiColorEditFlags misc_flags = ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoOptions;

	static const char* ids[4] = { "##X", "##Y", "##Z", "##W" };
	static const char* fmt_table_float[4] = { "R:%0.3f", "G:%0.3f", "B:%0.3f", "A:%0.3f" };
	const float square_sz = ImGui::GetFrameHeight();
	const float w_full = ImGui::CalcItemWidth();
	const float w_button = square_sz + ImGui::GetStyle().ItemInnerSpacing.x;
	const float w_inputs = w_full - w_button;
	const float w_item_one = ImMax(1.0f, IM_FLOOR((w_inputs - (ImGui::GetStyle().ItemInnerSpacing.x) * (4 - 1)) / 4.0f));
	const float w_item_last = ImMax(1.0f, IM_FLOOR(w_inputs - (w_item_one + ImGui::GetStyle().ItemInnerSpacing.x) * (4 - 1)));

	for (int i = 0; i < 4; i++)
	{
		if (i > 0)
			ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
		ImGui::SetNextItemWidth((i + 1 < 4) ? w_item_one : w_item_last);
		ImGui::DragFloat(ids[i], &col[i], 1.0f / 255.0f, 0.0f, 1.0f, fmt_table_float[i]);
	}

	ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);

	ImVec4 color_vec = ImVec4(col[0], col[1], col[2], col[3]);
	bool open_popup = ImGui::ColorButton(label, color_vec, misc_flags);
	ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
	open_popup |= ImGui::Button("!");
	ImGui::SameLine();
	ImGui::Text(label);

	static D3DXCOLOR backup_color;

	if (open_popup)
	{
		ImGui::OpenPopup(label);
		backup_color = D3DXCOLOR(col[0], col[1], col[2], col[3]);
	}
	if (ImGui::BeginPopup(label))
	{
		ImGuiColorEditFlags flags = ImGuiColorEditFlags_AlphaBar;
		flags |= ImGuiColorEditFlags_AlphaPreview;
		flags |= ImGuiColorEditFlags_Float;

		ColorPalette(col, (float*)&backup_color, flags);
		ImGui::EndPopup();
	}
}

//--------------------------------------------------
// カラーパレット
//--------------------------------------------------
void CImguiProperty::ColorPalette(float color[4], float backup_color[4], ImGuiColorEditFlags flags)
{
	ImGui::ColorPicker4("##picker", color, flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
	ImGui::SameLine();

	ImGui::BeginGroup(); // Lock X position
	ImGui::Text("Current");
	ImGui::ColorButton("##current", ImVec4(color[0], color[1], color[2], color[3]), ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreview, ImVec2(60, 40));
	ImGui::Text("Original");
	if (ImGui::ColorButton("##original", ImVec4(backup_color[0], backup_color[1], backup_color[2], backup_color[3]), ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreview, ImVec2(60, 40)))
	{
		color[0] = backup_color[0];
		color[1] = backup_color[1];
		color[2] = backup_color[2];
		color[3] = backup_color[3];
	}

	ImGui::Separator();
	ImGui::Text("Palette");

	static bool saved_palette_init = true;
	static ImVec4 saved_palette[32] = {};
	if (saved_palette_init)
	{
		for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
		{
			ImGui::ColorConvertHSVtoRGB(n / 31.0f, 0.8f, 0.8f,
				saved_palette[n].x, saved_palette[n].y, saved_palette[n].z);
			saved_palette[n].w = 1.0f; // Alpha
		}
		saved_palette_init = false;
	}

	for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
	{
		ImGui::PushID(n);
		if ((n % 8) != 0)
			ImGui::SameLine(0.0f, ImGui::GetStyle().ItemSpacing.y);

		ImGuiColorEditFlags palette_button_flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip;
		if (ImGui::ColorButton("##palette", saved_palette[n], palette_button_flags, ImVec2(20, 20)))
		{
			color[0] = saved_palette[n].x;
			color[1] = saved_palette[n].y;
			color[2] = saved_palette[n].z;
		}

		// Allow user to drop colors into each palette entry. Note that ColorButton() is already a
		// drag source by default, unless specifying the ImGuiColorEditFlags_NoDragDrop flag.
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
				memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 3);
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
				memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 4);
			ImGui::EndDragDropTarget();
		}

		ImGui::PopID();
	}
	ImGui::EndGroup();
}

//--------------------------------------------------
// カラーからベクトルに変換
//--------------------------------------------------
ImVec4 CImguiProperty::ColorToImVec4(const D3DXCOLOR & color)
{
	ImVec4 vec;

	vec.x = color.r;
	vec.y = color.g;
	vec.z = color.b;
	vec.w = color.a;

	return vec;
}

//--------------------------------------------------
// ベクトルからカラーに変換
//--------------------------------------------------
D3DXCOLOR CImguiProperty::ImVec4ToColor(const ImVec4 & vec)
{
	D3DXCOLOR color;

	color.r = vec.x;
	color.g = vec.y;
	color.b = vec.z;
	color.a = vec.w;

	return color;
}
