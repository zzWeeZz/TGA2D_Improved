#include "stdafx.h"
#include "RenderCommander.h"

RenderCommander::RenderCommander()
{
	myLogicdataPointer = nullptr;
}

RenderCommander::RenderCommander(std::vector<std::shared_ptr<LogicData>>* aLogicDataContainer) : myLogicdataPointer(
	aLogicDataContainer)
{
}

void RenderCommander::InitCommander(std::vector<std::shared_ptr<LogicData>>* aLogicDataContainer)
{
	myLogicdataPointer = aLogicDataContainer;
}

void RenderCommander::AddRenderCommand(std::shared_ptr<LogicData> aLogicData) const
{
	myLogicdataPointer->emplace_back(aLogicData);
}

RenderCommander::~RenderCommander()
{
	delete myLogicdataPointer;
}
