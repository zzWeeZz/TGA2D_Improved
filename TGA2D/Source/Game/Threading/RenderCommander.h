#pragma once
#include <memory>
#include <vector>
#include "RenderData.hpp"


class RenderCommander
{
public:
	RenderCommander();
	RenderCommander(std::vector<Logic>* aLogicDataContainer);
	void InitCommander(std::vector<Logic>* aLogicDataContainer);
	void AddRenderCommand(const Logic& aLogicData) const;
	void AddRenderCommand(const std::vector<LogicData<DataType::Sprite>>& aLogicContainer) const;
	void AddRenderCommand(const std::vector<LogicData<DataType::Text>>& aLogicContainer) const;
private:
	std::vector<Logic>* myLogicdataPointer;
};
