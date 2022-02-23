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
	void LoaderThread();
	void LogicThread();
	LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	CGameWorld myGameWorld;
	CommonUtilities::InputHandler myInputHandler;
	CommonUtilities::Timer myTimer;

	//Threading Data
	RenderCommander myRenderCommander;
	std::thread* myLoaderThread;
	std::thread* myLogicThread;
	std::condition_variable myCondition;
	bool myCloseBool;
	std::mutex myLogicTransferMutex;
	std::mutex myRenderTransferMutex;
	std::vector<LogicData> myLogicData;
	std::vector<LogicData> myTempLogicData;
	std::vector<RenderData> myRenderData;
};
