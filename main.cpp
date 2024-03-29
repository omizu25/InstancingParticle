//**************************************************
//
// main.cpp
// Author : katsuki mizuki
//
//**************************************************

//==================================================
// ライブラリーリンク
//==================================================
#pragma comment(lib,"winmm.lib")

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "application.h"
#include "imgui_property.h"
#include <Windows.h>
#include <tchar.h> // _T

//==================================================
// 定義
//==================================================
namespace
{
// ウインドウのキャプション名
LPCTSTR WINDOW_NAME = _T("ポリゴンの描画");
}

//==================================================
// 変数
//==================================================
namespace
{
#ifdef _DEBUG
// FPSカウンタ
int s_nCountFPS;
#endif // _DEBUG
}

//==================================================
// プロトタイプ宣言
//==================================================
namespace
{
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}

//--------------------------------------------------
// メイン関数
//--------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	WNDCLASSEX wcex =
	{// ウインドウクラスの構造体
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	RECT rect = { 0, 0, CApplication::SCREEN_WIDTH, CApplication::SCREEN_HEIGHT };

	// 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// ウィンドウの作成
	HWND hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	// 分解能を設定
	timeBeginPeriod(1);

	CApplication* pApplication = CApplication::GetInstanse();

	if (pApplication != nullptr)
	{// nullチェック
		if (FAILED(pApplication->Init(hInstance, hWnd)))
		{// 初期化
			return -1;
		}
	}

	// フレームカウント初期化
	DWORD dwCurrentTime = 0;
	DWORD dwExecLastTime = timeGetTime();

	// ウインドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	while (true)
	{// メッセージループ
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{ // PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	// 現在の時間を取得

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60秒経過
				// 現在の時間を保存
				dwExecLastTime = dwCurrentTime;

				if (pApplication != nullptr)
				{// nullチェック
					// 更新
					pApplication->Update();

					// 描画
					pApplication->Draw();
				}
			}
		}
	}

	if (pApplication != nullptr)
	{// nullチェック
		// 終了処理
		pApplication->Uninit(wcex);

		delete pApplication;
		pApplication = nullptr;
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;
}

namespace
{
//--------------------------------------------------
// ウインドウプロシージャ
//--------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		return true;
	}

	switch (uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE: // [ESC]キーが押された
			// ウィンドウを破棄
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
}
