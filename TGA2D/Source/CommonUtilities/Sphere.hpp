#pragma once
#include "Vector.hpp"

namespace CommonUtilities
{
	template <class T>
	class Sphere
	{
	public:
		Sphere();
		Sphere(const Sphere<T>& aSphere);
		Sphere(const Vector3<T>& aCenter, T aRadius);

		void InitWithCenterAndRadius(const Vector3<T>& aCenter, T aRadius);
		bool IsInside(const Vector3<T>& aPosition) const;
		Vector3<T> GetPosition() const;
		T GetRadius() const;
	private:
		Vector3<T> myPosition;
		T myRadius;
	};

	template <class T>
	Sphere<T>::Sphere()
	{
		myPosition = {0, 0, 0};
		myRadius = 0;
	}

	template <class T>
	Sphere<T>::Sphere(const Sphere<T>& aSphere)
	{
		myPosition = aSphere.myPosition;
		myRadius = aSphere.myRadius;
	}

	template <class T>
	Sphere<T>::Sphere(const Vector3<T>& aCenter, T aRadius)
	{
		myPosition = aCenter;
		myRadius = aRadius;
	}

	template <class T>
	void Sphere<T>::InitWithCenterAndRadius(const Vector3<T>& aCenter, T aRadius)
	{
		myPosition = aCenter;
		myRadius = aRadius;
	}

	template <class T>
	bool Sphere<T>::IsInside(const Vector3<T>& aPosition) const
	{
		Vector3<T> distance = aPosition - myPosition;
		if (distance.LengthSqr() > (myRadius * myRadius))
		{
			return false;
		}
		return true;
	}

	template <class T>
	Vector3<T> Sphere<T>::GetPosition() const
	{
		return myPosition;
	}

	template <class T>
	T Sphere<T>::GetRadius() const
	{
		return myRadius;
	}
}
