#pragma once
#include <memory>
#include <vector>
#include "RenderData.hpp"


class RenderCommander
{
public:
	RenderCommander();
	RenderCommander(std::vector<LogicData>* aLogicDataContainer);
	void InitCommander(std::vector<LogicData>* aLogicDataContainer);
	void AddRenderCommand(LogicData aLogicData) const;
	~RenderCommander();
private:
	std::vector<LogicData>* myLogicdataPointer;
};
