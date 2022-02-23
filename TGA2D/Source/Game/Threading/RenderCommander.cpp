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

void RenderCommander::AddRenderCommand(Logic aLogicData) const
{
	myLogicdataPointer->emplace_back(aLogicData);
}

RenderCommander::~RenderCommander()
{
	//delete myLogicdataPointer;
}
