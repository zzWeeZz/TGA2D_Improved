#pragma once
#include <fstream>
#include "GameWorld.h"
#include <..\CommonUtilities\InputHandler.hpp>
#include <..\CommonUtilities\Timer.hpp>

class CGame
{
public:
	CGame();
	~CGame();
	bool Init(const std::wstring& aVersion = L"", HWND aHWND = nullptr);
private:
	void InitCallBack();
	void UpdateCallBack();
	LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	CGameWorld myGameWorld;
	CommonUtilities::InputHandler myInputHandler;
	CommonUtilities::Timer myTimer;
};
