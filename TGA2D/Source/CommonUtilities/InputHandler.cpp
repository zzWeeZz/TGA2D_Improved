#include "pch.h"
#include "InputHandler.hpp"

namespace CommonUtilities
{

	bool InputHandler::GetKeyDown(const int aKeyCode) const
	{
		if (myKeyStrokes.test(aKeyCode) != false && myKeyStrokes.test(aKeyCode) != myPreviousKeyStroke.test(aKeyCode))
		{
			return true;
		}
		return false;
	}

	bool InputHandler::GetKeyUp(const int aKeyCode) const
	{
		if (myPreviousKeyStroke.test(aKeyCode) != false && myPreviousKeyStroke.test(aKeyCode) != myKeyStrokes.test(aKeyCode))
		{
			return true;
		}
		return false;
	}

	bool InputHandler::KeyIsPressed(const int aKeyCode) const
	{
		return myKeyStrokes.test(aKeyCode);
	}

	bool InputHandler::AnyKeyPressed() const
	{
		for (int i = 0; i < 256; i++)
		{
			if (myPreviousKeyStroke.test(i) == false && myPreviousKeyStroke.test(i) == myKeyStrokes.test(i))
			{
				return false;
			}
		}
		return true;
	}

	bool InputHandler::MouseButtonPressed(int aKeyIndex) const
	{
		return myCurrentMouseInputs.test(aKeyIndex);
	}

	bool InputHandler::GetMouseButtonDown(int aKeyIndex) const
	{
		if (myCurrentMouseInputs.test(aKeyIndex) != false && myCurrentMouseInputs.test(aKeyIndex) != myPreviousMouseInputs.test(aKeyIndex))
		{
			return true;
		}
		return false;
	}

	bool InputHandler::GetMouseButtonUp(int aKeyIndex) const
	{
		if (myPreviousMouseInputs.test(aKeyIndex) != false && myPreviousMouseInputs.test(aKeyIndex) != myMouseInputs.test(aKeyIndex))
		{
			return true;
		}
		return false;
	}

	Point InputHandler::GetMousePosition() const
	{
		return	myMousePos;
	}

	void InputHandler::UpdateInput()
	{
		for (UINT keyIndex = 0; keyIndex < myInputState.size(); keyIndex++)
		{
			myPreviousKeyStroke.set(keyIndex, myKeyStrokes.test(keyIndex));
			myKeyStrokes.set(keyIndex, myInputState.test(keyIndex));
		}

		for (UINT keyIndex = 0; keyIndex < myMouseInputs.size(); keyIndex++)
		{
			myPreviousMouseInputs.set(keyIndex, myCurrentMouseInputs.test(keyIndex));
			myCurrentMouseInputs.set(keyIndex, myMouseInputs.test(keyIndex));
		}
	}

	void InputHandler::SetMousePosition(int aX, int aY)
	{
		SetCursorPos(aX, aY);
	}

	bool InputHandler::UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_KEYDOWN:
			myInputState.set(wParam, true);
			return true;

		case WM_KEYUP:
			myInputState.set(wParam, false);
			return true;
		case WM_MOUSEMOVE:

			myMousePos.x = GET_X_LPARAM(lParam);
			myMousePos.y = GET_Y_LPARAM(lParam);
			break;
		case WM_LBUTTONDOWN:
			myMouseInputs.set(0, true);
			break;
		case WM_LBUTTONUP:
			myMouseInputs.set(0, false);
			break;
		case WM_MBUTTONDOWN:
			myMouseInputs.set(1, true);
			break;
		case WM_MBUTTONUP:
			myMouseInputs.set(1, false);
			break;
		case WM_RBUTTONDOWN:
			myMouseInputs.set(2, true);
			break;
		case WM_RBUTTONUP:
			myMouseInputs.set(2, false);
			break;
		default: break;
		}
		return false;
	}
}