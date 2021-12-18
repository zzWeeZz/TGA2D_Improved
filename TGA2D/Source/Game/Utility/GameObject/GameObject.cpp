#include "GameObject.h"

GameObject::GameObject()
{
	const auto resolution = Tga2D::CEngine::GetInstance()->GetTargetSize();
	myPositon = { resolution.myX * 0.5f, resolution.myY * 0.5f };
}
