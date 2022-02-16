#include "stdafx.h"
#include <tga2d/engine.h>
#include "Game.h"

#include <tga2d/error/error_manager.h>

#include "tga2d/d3d/direct_3d.h"
#include "tga2d/drawers/sprite_drawer.h"
#include "tga2d/texture/Texture.h"
#include "Utility/ColliderManager.h"
#define DEBUG_FPS_OF_THREADS 1

namespace Tga2D
{
	class CSpriteDrawer;
}

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
	myLogicThread->join();
	myLoaderThread->join();
	delete myLogicThread;
	delete myLoaderThread;
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
	createParameters.myUpdateFunctionToCall = [this] {RenderCallBack(&myRenderCommander); };
	createParameters.myApplicationName = L"TGA 2D " + BUILD_NAME + L"[" + aVersion + L"] ";
	createParameters.myClearColor = { 0.4f, 0.4f, 0.4f, 1 };
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
	myLoaderThread = new std::thread(&CGame::LoaderThread, std::ref(*this));
	myLogicThread = new std::thread(&CGame::LogicThread, std::ref(*this));


	
	// End of program
	return true;
}

void CGame::InitCallBack()
{
}

void CGame::RenderCallBack(RenderCommander* aRenderCommander)
{
	Tga2D::CSpriteDrawer& spriteDrawer(Tga2D::CEngine::GetInstance()->GetDirect3D().GetSpriteDrawer());
	std::vector<RenderData> toRenderData;
	while (!myRenderData.empty())
	{
		myRenderTransferMutex.lock();
		toRenderData.push_back(myRenderData[0]);
		
		myRenderData.erase(myRenderData.begin());
		myRenderTransferMutex.unlock();
	}
	myDoneRender = true;
	for (auto& [myInstanceData, mySharedData] : toRenderData)
	{
		spriteDrawer.Draw(mySharedData, myInstanceData);
	}
	myDoneRender = false;
	std::this_thread::yield();
}

void CGame::LoaderThread()
{
	auto res = Tga2D::CEngine::GetInstance()->GetTargetSize();
	while (true)
	{
		if (!myLogicData.empty())
		{
			RenderData newRenderData;
			newRenderData.mySharedData.myTexture = myLogicData[0].myTexture;
			newRenderData.myInstanceData.myPosition = { myLogicData[0].myPosition.x / res.x, myLogicData[0].myPosition.y / res.y };
			newRenderData.myInstanceData.myPivot = { myLogicData[0].myPivot.x, myLogicData[0].myPivot.y };
			newRenderData.myInstanceData.mySize = newRenderData.mySharedData.myTexture->mySize / res.y;
			newRenderData.myInstanceData.mySizeMultiplier = { myLogicData[0].mySizeMultiplier.x, myLogicData[0].mySizeMultiplier.y };
			newRenderData.myInstanceData.myUV = { myLogicData[0].myUV.x, myLogicData[0].myUV.y };
			newRenderData.myInstanceData.myUVScale = { myLogicData[0].myUVScale.x, myLogicData[0].myUVScale.y };
			newRenderData.myInstanceData.myColor = { myLogicData[0].myColor.x, myLogicData[0].myColor.y,myLogicData[0].myColor.z,myLogicData[0].myColor.w };
			newRenderData.myInstanceData.myTextureRect = myLogicData[0].myTextureRect;
			newRenderData.myInstanceData.myRotation = myLogicData[0].myRotation;
			newRenderData.myInstanceData.myIsHidden = myLogicData[0].myIsHidden;
			myLogicTransferMutex.lock();
			myLogicData.erase(myLogicData.begin());
			myLogicTransferMutex.unlock();
			std::unique_lock lock(myRenderTransferMutex);
			myRenderData.emplace_back(newRenderData);

			std::this_thread::yield();
		}
	}
}

void CGame::LogicThread()
{
	// Init on thread
	   //TODO: handle Init of thread
	myTimer.Update();
	std::vector<std::shared_ptr<LogicData>> newLogicData;
	myRenderCommander.InitCommander(&newLogicData);
	myGameWorld.Init();

	while (true)
	{
		myTimer.Update();
		myInputHandler.UpdateInput();
		// gameloop
		myGameWorld.Render(&myRenderCommander);
		myGameWorld.Update(myTimer.GetDeltaTime(), static_cast<float>(myTimer.GetTotalTime()), myInputHandler);
		std::unique_lock lock( myLogicTransferMutex);
		myCondition.wait(lock, [&] { return myDoneRender; });
		for (int i = 0; i < newLogicData.size(); ++i)
		{
			myLogicData.emplace_back(*newLogicData[i]);
		}
		newLogicData.clear();

		std::this_thread::yield();
	}
}
