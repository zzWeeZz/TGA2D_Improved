#pragma once
#include <../CommonUtilities/Vector.hpp>
#include <tga2d/sprite/sprite.h>
#include <memory>
#include <vector>
#include "tga2d/text/text.h"
#include "tga2d/texture/Texture.h"

namespace Tga2D
{
	class CTexture;
	class CTexture;
}

class RenderData;
enum class DataType
{
	Sprite,
	Text
};

class Logic
{
public:
	int myRenderOrder = 1;
	Tga2D::CTexture* myTexture = nullptr;
	Tga2D::CText* myText = nullptr;
	CommonUtilities::Vector2<float> myPosition = { 500, 500 };
	CommonUtilities::Vector2<float> myPivot = { 0.5f, 0.5f };
	CommonUtilities::Vector2<float> mySizeMultiplier = { 1.0f, 1.0f };
	CommonUtilities::Vector2<float> myUV = { 0.0f, 0.0f };
	CommonUtilities::Vector2<float> myUVScale = { 1.0f, 1.0f };
	CommonUtilities::Vector4<float> myColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	Tga2D::STextureRext myTextureRect = { 0.0f, 0.0f, 1.0f, 1.0f };
	float myRotation = 0.f;
	bool myIsHidden = false;
	DataType myDataType;
};

template<DataType aDataType>
class LogicData : public Logic
{
public:
	LogicData()
	{
		myDataType = aDataType;
	}
};

typedef LogicData<DataType::Sprite> SpriteData;
typedef LogicData<DataType::Text> TextData;
class RenderData
{
public:
	std::vector<Tga2D::SSpriteInstanceData> myInstanceData;
	Tga2D::SSpriteSharedData mySharedData;
	Tga2D::CText* myText;
	DataType myDataType;
};