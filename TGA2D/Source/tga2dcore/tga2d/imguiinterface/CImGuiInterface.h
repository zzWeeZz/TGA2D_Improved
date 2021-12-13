#pragma once
#include <..\External\imgui\imgui.h>
#include <..\External\imgui/imgui_impl_dx11.h>
#include <..\External\imgui/imgui_impl_win32.h>
namespace Tga2D
{
	class CImGuiInterfaceImpl;
	class CImGuiInterface
	{
	public:
		CImGuiInterface();
		~CImGuiInterface();
		void Init();
		void PreFrame();
		void Render();

	private:
		std::unique_ptr<CImGuiInterfaceImpl> myImpl;
	};


}
