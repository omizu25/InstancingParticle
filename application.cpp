//**************************************************
// 
// application.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "object.h"
#include "texture.h"
#include "camera.h"
#include "effect.h"
#include "instancing.h"
#include "imgui_property.h"
#include "window.h"
#include <time.h>
#include <assert.h>

//==================================================
// 定義
//==================================================
const bool CApplication::FULL_SCREEN = true;

//==================================================
// 静的メンバ変数
//==================================================
CApplication* CApplication::m_pApplication = nullptr;

//--------------------------------------------------
// インスタンスの取得
//--------------------------------------------------
CApplication* CApplication::GetInstanse()
{
	if (m_pApplication == nullptr)
	{// nullチェック
		m_pApplication = new CApplication;
	}

	return m_pApplication;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CApplication::CApplication() :
	m_pRenderer(nullptr),
	m_pInput(nullptr),
	m_pTexture(nullptr),
	m_pCamera(nullptr),
	m_pInstancing(nullptr),
	m_pImguiProperty(nullptr),
	m_pWindow(nullptr)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CApplication::~CApplication()
{
	assert(m_pWindow == nullptr);
	assert(m_pImguiProperty == nullptr);
	assert(m_pInstancing == nullptr);
	assert(m_pCamera == nullptr);
	assert(m_pTexture == nullptr);
	assert(m_pInput == nullptr);
	assert(m_pRenderer == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pRenderer == nullptr)
	{// nullチェック
		m_pRenderer = new CRenderer;
	}

	if (m_pRenderer != nullptr)
	{// nullチェック
		if (FAILED(m_pRenderer->Init(hWnd, FULL_SCREEN)))
		{// 初期化
			return S_FALSE;
		}
	}

	if (m_pInput == nullptr)
	{// nullチェック
		m_pInput = CInput::Create();
	}

	if (m_pInput != nullptr)
	{// nullチェック
		if (FAILED(m_pInput->Init(hInstance, hWnd)))
		{// 初期化
			return E_FAIL;
		}
	}

	if (m_pTexture == nullptr)
	{// nullチェック
		m_pTexture = new CTexture;
	}

	if (m_pCamera == nullptr)
	{// nullチェック
		m_pCamera = new CCamera;
	}

	if (m_pCamera != nullptr)
	{// nullチェック
		m_pCamera->Init();
	}

	// ランダムの初期化
	srand((unsigned int)time(NULL));

	if (m_pInstancing == nullptr)
	{// nullチェック
		m_pInstancing = CInstancing::Create();
	}

	if (m_pWindow == nullptr)
	{// nullチェック
		m_pWindow = new CWindow;
	}

	if (m_pWindow != nullptr)
	{// nullチェック
		m_pWindow->Init(hInstance);
	}

	if (m_pImguiProperty == nullptr)
	{// nullチェック
		m_pImguiProperty = new CImguiProperty;
	}

	if (m_pImguiProperty != nullptr)
	{// nullチェック
		m_pImguiProperty->Init(m_pWindow->GetWnd(), m_pWindow->GetDevice());
	}

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CApplication::Uninit(WNDCLASSEX wcex)
{
	// 破棄
	CObject::ReleaseAll();

	if (m_pImguiProperty != nullptr)
	{// nullチェック
		m_pImguiProperty->Uninit(m_pWindow->GetWnd(), wcex);
		delete m_pImguiProperty;
		m_pImguiProperty = nullptr;
	}

	if (m_pWindow != nullptr)
	{// nullチェック
		m_pWindow->Uninit();
		delete m_pWindow;
		m_pWindow = nullptr;
	}

	if (m_pInstancing != nullptr)
	{// nullチェック
		m_pInstancing->Uninit();
		delete m_pInstancing;
		m_pInstancing = nullptr;
	}

	if (m_pCamera != nullptr)
	{// nullチェック
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pTexture != nullptr)
	{// nullチェック
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pInput != nullptr)
	{// nullチェック
		// 終了
		m_pInput->Uninit();
		m_pInput = nullptr;
	}

	if (m_pRenderer != nullptr)
	{// nullチェック
		// 終了
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CApplication::Update()
{
	if (m_pInput != nullptr)
	{// nullチェック
		// 更新
		m_pInput->Update();
	}

	if (m_pRenderer != nullptr)
	{// nullチェック
		// 更新処理
		m_pRenderer->Update();
	}

	if (m_pWindow != nullptr)
	{// nullチェック
		// 更新処理
		m_pWindow->Update();
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{// nullチェック
		// 描画処理
		m_pRenderer->Draw();
	}

	if (m_pWindow != nullptr)
	{// nullチェック
		// 描画処理
		m_pWindow->Draw();
	}
}

//--------------------------------------------------
// デバイスの取得
//--------------------------------------------------
LPDIRECT3DDEVICE9 CApplication::GetDevice()
{
	return m_pRenderer->GetDevice();
}

//--------------------------------------------------
// テクスチャの情報の取得
//--------------------------------------------------
CTexture* CApplication::GetTexture()
{
	return m_pTexture;
}

//--------------------------------------------------
// カメラの情報の取得
//--------------------------------------------------
CCamera* CApplication::GetCamera()
{
	return m_pCamera;
}

//--------------------------------------------------
// インスタンシングの情報の取得
//--------------------------------------------------
CInstancing* CApplication::GetInstancing()
{
	return m_pInstancing;
}

//--------------------------------------------------
// imguiの情報の取得
//--------------------------------------------------
CImguiProperty* CApplication::GetImguiProperty()
{
	return m_pImguiProperty;
}
