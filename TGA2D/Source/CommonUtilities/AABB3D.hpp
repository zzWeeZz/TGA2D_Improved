#pragma once
#include "Vector.hpp"

namespace CommonUtilities
{
	template <class T>
	class AABB3D
	{
	public:
		AABB3D();
		AABB3D(const AABB3D<T>& aAABB3D);
		AABB3D(const Vector3<T>& aMin, const Vector3<T>& aMax);
		Vector3<T> GetMin() const;
		Vector3<T> GetMax() const;
		void InitWithMinAndMax(const Vector3<T>& aMin, const Vector3<T>& aMax);
		bool IsInside(const Vector3<T>& aPosition) const;
	private:
		Vector3<T> myMin;
		Vector3<T> myMax;
	};

	template <class T>
	AABB3D<T>::AABB3D() : myMin(0, 0, 0), myMax(0, 0, 0)
	{
	}

	template <class T>
	AABB3D<T>::AABB3D(const AABB3D<T>& aAABB3D)
	{
		myMin = aAABB3D.myMin;
		myMax = aAABB3D.myMax;
	}

	template <class T>
	AABB3D<T>::AABB3D(const Vector3<T>& aMin, const Vector3<T>& aMax)
	{
		myMin = aMin;
		myMax = aMax;
	}

	template <class T>
	Vector3<T> AABB3D<T>::GetMin() const
	{
		return myMin;
	}

	template <class T>
	Vector3<T> AABB3D<T>::GetMax() const
	{
		return myMax;
	}

	template <class T>
	void AABB3D<T>::InitWithMinAndMax(const Vector3<T>& aMin, const Vector3<T>& aMax)
	{
		myMin = aMin;
		myMax = aMax;
	}

	template <class T>
	bool AABB3D<T>::IsInside(const Vector3<T>& aPosition) const
	{
		if (myMax.x < aPosition.x) { return false; };
		if (myMin.x > aPosition.x) { return false; };
		if (myMax.y < aPosition.y) { return false; };
		if (myMin.y > aPosition.y) { return false; };
		if (myMax.z < aPosition.z) { return false; };
		if (myMin.z > aPosition.z) { return false; };

		return true;
	}
}
