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
	void AddRenderCommand(Logic aLogicData) const;
	~RenderCommander();
private:
	std::vector<Logic>* myLogicdataPointer;
};
