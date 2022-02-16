#pragma once
#include <../CommonUtilities/Vector.hpp>
#include <tga2d/sprite/sprite.h>
#include <memory>

namespace Tga2D
{
	class CTexture;
}

class RenderData;
class LogicData
{
	friend RenderData;
public:
	int myRenderOrder = 1;
	const Tga2D::CTexture* myTexture = nullptr;
	CommonUtilities::Vector2<float> myPosition = {500, 500};
	CommonUtilities::Vector2<float> myPivot = {0.5f, 0.5f};
	CommonUtilities::Vector2<float> mySizeMultiplier = {1.0f, 1.0f};
	CommonUtilities::Vector2<float> myUV = { 0.0f, 0.0f };
	CommonUtilities::Vector2<float> myUVScale = { 1.0f, 1.0f };
	CommonUtilities::Vector4<float> myColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	Tga2D::STextureRext myTextureRect = { 0.0f, 0.0f, 1.0f, 1.0f };
	float myRotation = 0.f;
	bool myIsHidden = false;
private:
	CommonUtilities::Vector2<float> mySize = {200, 200};

};

class RenderData
{
	friend LogicData;
public:
	Tga2D::SSpriteInstanceData myInstanceData;
	Tga2D::SSpriteSharedData mySharedData;
};