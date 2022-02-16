#pragma once
#include <memory>
#include <vector>

class LogicData;

class RenderCommander
{
public:
	RenderCommander();
	RenderCommander(std::vector<std::shared_ptr<LogicData>>* aLogicDataContainer);
	void InitCommander(std::vector<std::shared_ptr<LogicData>>* aLogicDataContainer);
	void AddRenderCommand(std::shared_ptr<LogicData> aLogicData) const;
	~RenderCommander();
private:
	std::vector<std::shared_ptr<LogicData>>* myLogicdataPointer;
};
