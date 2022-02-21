#pragma once
#include <..\..\Source\CommonUtilities\InputHandler.hpp>
#include "Character.h"
#include "Threading/RenderData.hpp"

#define PI 3.14159265358979323846f
#define RAD_TO_DEG(a) ((180/PI) * a)
#define DEG_TO_RAD(a) ((PI/180) * a)

namespace Tga2D
{
	class CTexture;
}

class RenderCommander;
class LogicData;

class CGameWorld
{
public:
	CGameWorld(); 
	void Init();
	void Update(float aTimeDelta, float aTotalTime, CommonUtilities::InputHandler& aInputHandler); 
	void Render(RenderCommander* aRenderCommander);
	~CGameWorld();
private:
	
	LogicData myLogicData;
	char myValue;

};