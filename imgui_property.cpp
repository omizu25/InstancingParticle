//**************************************************
//
// Hackathon ( imgui_property.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
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
// ��`
//==================================================
const char* CImguiProperty::FontPath = "c:\\Windows\\Fonts\\meiryo.ttc";				// �g�p����t�H���g
const float CImguiProperty::FontSize = 18.0f;											// �t�H���g�T�C�Y
const ImVec4 CImguiProperty::TitleBarColor = ImVec4(0.615f, 0.215f, 0.341f, 1.0f);		// �^�C�g���o�[�̐F
const ImVec4 CImguiProperty::SliderBarColor = ImVec4(0.615f, 0.215f, 0.341f, 1.0f);		// �X���C�_�[�o�[�̐F
const ImVec4 CImguiProperty::CheckMarkColor = ImVec4(0.615f, 0.215f, 0.341f, 1.0f);		// �`�F�b�N�}�[�N�̐F
const ImVec4 CImguiProperty::ScrollBarColor = ImVec4(0.0f, 0.7f, 0.2f, 1.0f);			// �X�N���[���o�[�̐F
const ImVec4 CImguiProperty::HeaderColor = ImVec4(1.0f, 1.0f, 1.0f, 0.309f);			// �w�b�_�[�̊�{�F
const ImVec4 CImguiProperty::HeaderHoveredColor = ImVec4(1.0f, 1.0f, 1.0f, 0.75f);		// �w�b�_�[�Ƀ}�E�X�J�[�\�������킹�����̐F
const ImVec4 CImguiProperty::HeaderActiveColor = ImVec4(1.0f, 1.0f, 1.0f, 0.85f);		// �w�b�_�[�N���b�N���̐F
const char* CImguiProperty::WINDOW_NAME = "test";

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CImguiProperty::CImguiProperty() :
	m_window(true),
	m_instancing(true)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CImguiProperty::~CImguiProperty()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HWND CImguiProperty::Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
{
#ifdef _DEBUG

	m_window = true;
	m_instancing = true;

	// �E�C���h�E�̕\��
	::ShowWindow(hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(hWnd);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// �����̐ݒ�
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF(FontPath, FontSize, nullptr, io.Fonts->GetGlyphRangesJapanese());

	// �X�^�C���̐ݒ�
	ImGui::StyleColorsDark();

	// �^�C�g���o�[�̐F�ݒ�
	ImGui::PushStyleColor(ImGuiCol_TitleBg, TitleBarColor);
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, TitleBarColor);
	ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, TitleBarColor);

	// �X���C�h�̐F�ݒ�
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, SliderBarColor);
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, SliderBarColor);

	// �`�F�b�N�}�[�N�̐F�ݒ�
	ImGui::PushStyleColor(ImGuiCol_CheckMark, CheckMarkColor);

	// �X�N���[���̐F�ݒ�
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ScrollBarColor);

	// �w�b�_�[�̐F�ݒ�
	ImGui::PushStyleColor(ImGuiCol_Header, HeaderColor);
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, HeaderHoveredColor);
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, HeaderActiveColor);

	// �v���b�g�t�H�[���̐ݒ�/Renderer backends
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	return S_OK;
#endif // _DEBUG
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CImguiProperty::Uninit(HWND hWnd, WNDCLASSEX wcex)
{
#ifdef _DEBUG

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// �E�C���h�E�̔j��
	::DestroyWindow(hWnd);

	// �E�C���h�E�N���X�̓o�^������
	::UnregisterClass(wcex.lpszClassName, wcex.hInstance);

#endif // _DEBUG
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CImguiProperty::Update()
{
#ifdef _DEBUG

	if (!m_window)
	{// �E�C���h�E���g�p���Ȃ�
		return;
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// �E�C���h�E�̋N�����̏ꏊ
	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(350, 300), ImGuiCond_Once);

	// �E�C���h�E�̖���
	ImGui::Begin(WINDOW_NAME, nullptr, ImGuiWindowFlags_MenuBar);

	// FPS�̕\��
	ImGui::Text("FPS  : %.2f", ImGui::GetIO().Framerate);

	// �I�u�W�F�N�g�̑����̕\��
	ImGui::Text("Object  : %5d", CObject::GetNumAll());

	// �G�t�F�N�g�̑����̕\��
	ImGui::Text("Effect  : %5d", CEffect::GetNumAll());
	ImGui::Separator();	// ��؂��

	ImGui::Checkbox("instancing", &m_instancing);
	ImGui::Separator();	// ��؂��

	CEffectManager* pEffect = CEffectManager::GetInstanse();

	{// �Ԋu
		int interval = pEffect->GetInterval();
		ImGui::DragInt("interval", &interval, 0.5f, CEffectManager::MIN_INTERVAL, CEffectManager::MAX_INTERVAL);
		pEffect->SetInterval(interval);
	}

	{// ��
		int quantity = pEffect->GetQuantity();
		ImGui::DragInt("quantity", &quantity, 10.0f, CEffectManager::MIN_QUANTITY, CObject::MAX_OBJECT);
		pEffect->SetQuantity(quantity);
	}

	ImGui::End();

#endif // _DEBUG
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CImguiProperty::Draw()
{
#ifdef _DEBUG

	if (!m_window)
	{// �E�C���h�E���g�p���Ȃ�
		return;
	}

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

#endif // _DEBUG
}

//--------------------------------------------------
// �C���X�^���V���O���g�p���邩�ǂ���
//--------------------------------------------------
bool CImguiProperty::GetInstancing()
{
	return m_instancing;
}

//--------------------------------------------------
// �J���[�p���b�g4
//--------------------------------------------------
void CImguiProperty::ColorPalette4(const char * label, float col[4])
{
	//�J���[�p���b�g
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
// �J���[�p���b�g
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
// �J���[����x�N�g���ɕϊ�
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
// �x�N�g������J���[�ɕϊ�
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
