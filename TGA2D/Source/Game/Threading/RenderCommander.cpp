#include "stdafx.h"
#include "RenderCommander.h"

RenderCommander::RenderCommander() : myLogicdataPointer(nullptr)
{
}

RenderCommander::RenderCommander(std::vector<LogicData>* aLogicDataContainer) : myLogicdataPointer(
	aLogicDataContainer)
{
}

void RenderCommander::InitCommander(std::vector<LogicData>* aLogicDataContainer)
{
	myLogicdataPointer = aLogicDataContainer;
}

void RenderCommander::AddRenderCommand(LogicData aLogicData) const
{
	myLogicdataPointer->emplace_back(aLogicData);
}

RenderCommander::~RenderCommander()
{
	//delete myLogicdataPointer;
}
