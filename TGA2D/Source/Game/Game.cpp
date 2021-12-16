#include "stdafx.h"
#include <tga2d/engine.h>
#include "Game.h"

#include <tga2d/error/error_manager.h>

#include "Utility/ColliderManager.h"


using namespace std::placeholders;

#ifdef _DEBUG
#pragma comment(lib,"tga2dcore_Debug.lib")
#pragma comment(lib,"External_Debug.lib")
std::wstring BUILD_NAME = L"Debug";
#endif // DEBUG
#ifdef _RELEASE
#pragma comment(lib,"tga2dcore_Release.lib")
#pragma comment(lib,"External_Release.lib")
std::wstring BUILD_NAME = L"Release";
#endif // DEBUG
#ifdef _RETAIL
#pragma comment(lib,"tga2dcore_Retail.lib")
#pragma comment(lib,"External_Retail.lib")
std::wstring BUILD_NAME = L"Retail";
#endif // DEBUG

CGame::CGame()
{
}


CGame::~CGame()
{
}

LRESULT CGame::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (myInputHandler.UpdateEvents(message, wParam, lParam))
	{
		return 0;
	}
	lParam;
	wParam;
	hWnd;
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	}
	}

	return 0;
}


bool CGame::Init(const std::wstring& aVersion, HWND /*aHWND*/)
{
	Tga2D::SEngineCreateParameters createParameters;
	createParameters.myInitFunctionToCall = [this] {InitCallBack(); };
	createParameters.myWinProcCallback = [this](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {return WinProc(hWnd, message, wParam, lParam); };
	createParameters.myUpdateFunctionToCall = [this] {UpdateCallBack(); };
	createParameters.myApplicationName = L"TGA 2D " + BUILD_NAME + L"[" + aVersion + L"] ";
	createParameters.myClearColor = { 0, 0, 0, 0 };
	//createParameters.myPreferedMultiSamplingQuality = Tga2D::EMultiSamplingQuality::High;
	createParameters.myActivateDebugSystems = Tga2D::EDebugFeature::Fps |
		Tga2D::EDebugFeature::Mem |
		Tga2D::EDebugFeature::Drawcalls |
		Tga2D::EDebugFeature::Cpu |
		Tga2D::EDebugFeature::Filewatcher |
		Tga2D::EDebugFeature::OptimizeWarnings |
		Tga2D::EDebugFeature::FpsGraph;

	if (!Tga2D::CEngine::Start(createParameters))
	{
		ERROR_PRINT("Fatal error! Engine could not start!");
		system("pause");
		return false;
	}

	// End of program
	myTimer.Update();
	return true;
}

void CGame::InitCallBack()
{
	myGameWorld.Init();
}

void CGame::UpdateCallBack()
{
	myTimer.Update();
	myInputHandler.UpdateInput();
	myGameWorld.Update(myTimer.GetDeltaTime(), static_cast<float>(myTimer.GetTotalTime()), myInputHandler);
	myGameWorld.Render();
	ColliderManager::GetInstance()->UpdateCollision();

}
