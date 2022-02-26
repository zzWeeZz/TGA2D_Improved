#include "stdafx.h"
#include <tga2d/engine.h>
#include "Game.h"

#include <tga2d/error/error_manager.h>

#include "tga2d/d3d/direct_3d.h"
#include "tga2d/drawers/sprite_drawer.h"
#include "tga2d/texture/Texture.h"
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
	delete myLogicThread;
	delete myLoaderThread;
	myLoaderThread = nullptr;
	myLoaderThread = nullptr;
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

		PostQuitMessage(0);
		// close the application entirely
		myCloseBool = true;
		myConditionRender.notify_all();
		myConditionLogic.notify_all();
		myLogicThread->join();
		myLoaderThread->join();
		return 0;
	}
	}

	return 0;
}


bool CGame::Init(const std::wstring& aVersion, HWND /*aHWND*/)
{
	if (myCloseBool)
	{
		return false;
	}
	Tga2D::SEngineCreateParameters createParameters;
	createParameters.myInitFunctionToCall = [this] {InitCallBack(); };
	createParameters.myWinProcCallback = [this](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {return WinProc(hWnd, message, wParam, lParam); };
	createParameters.myUpdateFunctionToCall = [this] {RenderCallBack(); };
	createParameters.myApplicationName = L"TGA 2D " + BUILD_NAME + L"[" + aVersion + L"] ";
	createParameters.myClearColor = { 0.4f, 0.4f, 0.4f, 1 };
	//createParameters.myPreferedMultiSamplingQuality = Tga2D::EMultiSamplingQuality::High;
	createParameters.myActivateDebugSystems = Tga2D::EDebugFeature::Fps |
		Tga2D::EDebugFeature::Mem |
		Tga2D::EDebugFeature::Drawcalls |
		Tga2D::EDebugFeature::Cpu |
		Tga2D::EDebugFeature::OptimizeWarnings |
		Tga2D::EDebugFeature::FpsGraph;

	if (!Tga2D::CEngine::Start(createParameters))
	{
		ERROR_PRINT("Fatal error! Engine could not start!");
		system("pause");
		return false;
	}
	// End of program
	return true;
}

void CGame::SetCloseThreadBool(const bool& aFlag)
{
	myCloseBool = aFlag;
}

void CGame::InitCallBack()
{
	myLoaderThread = new std::thread(&CGame::LoaderThread, std::ref(*this));
	myLogicThread = new std::thread(&CGame::LogicThread, std::ref(*this));
}

void CGame::RenderCallBack()
{
	Tga2D::CSpriteDrawer& spriteDrawer(Tga2D::CEngine::GetInstance()->GetDirect3D().GetSpriteDrawer());
	std::vector<RenderData> toRenderData;
	std::unique_lock lock(myRenderTransferMutex);
	myConditionLogic.wait(lock);
	while (!myRenderData.empty())
	{
		switch (myRenderData[0].myDataType)
		{
		case DataType::Sprite:
			for (auto& myData : myRenderData)
			{
				spriteDrawer.Draw(myData.mySharedData, &myData.myInstanceData[0], myData.myInstanceData.size());
			}
			break;
		case DataType::Text:
			for (auto& myData : myRenderData)
			{
				myData.myText->Render();
			}
			break;
		default: ;
		}
		
		
		myRenderData.erase(myRenderData.begin());
	}
	myConditionRender.notify_all();
}

Tga2D::SSpriteInstanceData CGame::SwapLogicDataToRenderData(const RenderData& aRenderData)
{
	const auto res = Tga2D::CEngine::GetInstance()->GetTargetSize();
	Tga2D::SSpriteInstanceData instanceData;
	if (!myLogicData.empty())
	{
		instanceData.myPosition = { myLogicData[0].myPosition.x / res.x, myLogicData[0].myPosition.y / res.y };
		instanceData.myPivot = { myLogicData[0].myPivot.x, myLogicData[0].myPivot.y };
		instanceData.mySize = (aRenderData.myDataType == DataType::Sprite) ? aRenderData.mySharedData.myTexture->mySize : Tga2D::Vector2<float>(0, 0);
		instanceData.mySizeMultiplier = { myLogicData[0].mySizeMultiplier.x, myLogicData[0].mySizeMultiplier.y };
		instanceData.myUV = { myLogicData[0].myUV.x, myLogicData[0].myUV.y };
		instanceData.myUVScale = { myLogicData[0].myUVScale.x, myLogicData[0].myUVScale.y };
		instanceData.myColor = {
			myLogicData[0].myColor.x, myLogicData[0].myColor.y, myLogicData[0].myColor.z,
			myLogicData[0].myColor.w
		};
		instanceData.myTextureRect = myLogicData[0].myTextureRect;
		instanceData.myRotation = myLogicData[0].myRotation;
		instanceData.myIsHidden = myLogicData[0].myIsHidden;
	}
	return instanceData;
}

void CGame::LoaderThread()
{

	while (!myCloseBool)
	{
		while (!myLogicData.empty())
		{
			RenderData newRenderData;
			newRenderData.mySharedData.myTexture = myLogicData[0].myTexture;
			newRenderData.myText = myLogicData[0].myText;
			while (!myLogicData.empty() && newRenderData.mySharedData.myTexture == myLogicData[0].myTexture)
			{
				newRenderData.myDataType = myLogicData[0].myDataType;
				Tga2D::SSpriteInstanceData instanceData = SwapLogicDataToRenderData(newRenderData);

				std::unique_lock lock(myLogicTransferMutex);
				myLogicData.erase(myLogicData.begin());
				newRenderData.myInstanceData.emplace_back(instanceData);
				lock.unlock();
			}

			std::unique_lock lock(myRenderTransferMutex);
			myRenderData.emplace_back(newRenderData);

		}
		myConditionLogic.notify_one();
		std::this_thread::yield();
	}
}

void CGame::LogicThread()
{
	// Init on thread
	   //TODO: handle Init of thread
	myRenderCommander.InitCommander(&myTempLogicData);
	myTimer.Update();
	myGameWorld.Init();
	while (!myCloseBool)
	{
		myTimer.Update();
		myInputHandler.UpdateInput();
		myGameWorld.Render(&myRenderCommander);
		myGameWorld.Update(myTimer.GetDeltaTime(), static_cast<float>(myTimer.GetTotalTime()), myInputHandler);
		std::unique_lock lock(myLogicTransferMutex);
		myConditionRender.wait(lock);
		for (auto data : myTempLogicData)
		{
			myLogicData.emplace_back(data);
		}
		myTempLogicData.clear();

		lock.unlock();
	}
	std::cout << "Closing Logic\n";
}
