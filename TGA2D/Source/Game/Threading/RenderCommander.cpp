#include "stdafx.h"
#include "RenderCommander.h"

RenderCommander::RenderCommander() : myLogicdataPointer(nullptr)
{
}

RenderCommander::RenderCommander(std::vector<Logic>* aLogicDataContainer) : myLogicdataPointer(
	aLogicDataContainer)
{
}

void RenderCommander::InitCommander(std::vector<Logic>* aLogicDataContainer)
{
	myLogicdataPointer = aLogicDataContainer;
}

void RenderCommander::AddRenderCommand(const Logic& aLogicData) const
{
	myLogicdataPointer->emplace_back(aLogicData);
}

void RenderCommander::AddRenderCommand(const std::vector<LogicData<DataType::Sprite>>& aLogicContainer) const
{
	for (auto data : aLogicContainer)
	{
		myLogicdataPointer->emplace_back(data);
	}
}

void RenderCommander::AddRenderCommand(const std::vector<LogicData<DataType::Text>>& aLogicContainer) const
{
	for (auto data : aLogicContainer)
	{
		myLogicdataPointer->emplace_back(data);
	}
}
