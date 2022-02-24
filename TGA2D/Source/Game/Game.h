#pragma once
#include <fstream>
#include <mutex>
#include <../CommonUtilities/InputHandler.hpp>
#include <../CommonUtilities/Timer.hpp>
#include "GameWorld.h"
#include "Threading/RenderCommander.h"
#include "Threading/RenderData.hpp"

class CGame
{
public:
	CGame();
	~CGame();
	bool Init(const std::wstring& aVersion = L"", HWND aHWND = nullptr);
	void SetCloseThreadBool(const bool& aFlag);
private:
	void InitCallBack();
	void RenderCallBack();
	Tga2D::SSpriteInstanceData SwapLogicDataToRenderData(const RenderData& aRenderData);
	void LoaderThread();
	void LogicThread();
	LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	CGameWorld myGameWorld;
	CommonUtilities::InputHandler myInputHandler;
	CommonUtilities::Timer myTimer;
	Tga2D::CText* myLogicFpsText;

	//Threading Data
	RenderCommander myRenderCommander;
	std::thread* myLoaderThread;
	std::thread* myLogicThread;
	std::condition_variable myConditionRender;
	std::condition_variable myConditionLogic;
	bool myCloseBool;
	std::mutex myLogicTransferMutex;
	std::mutex myRenderTransferMutex;
	std::vector<Logic> myLogicData;
	std::vector<Logic> myTempLogicData;
	std::vector<RenderData> myRenderData;
};
