#pragma once
#include "Vector.hpp"

namespace CommonUtilities
{
	template <class T>
	class Ray
	{
	public:
		Ray();
		Ray(const Ray<T>& aRay);
		Ray(const Vector3<T>& aOrigin, const Vector3<T>& aPoint);

		void InitWith2Points(const Vector3<T>& aOrigin, const Vector3<T>& aPoint);
		void InitWithOriginAndDirection(const Vector3<T>& aOrigin, const Vector3<T>& aDirection);

		Vector3<T> GetOrigin() const;
		Vector3<T> GetDirection();

	private:
		Vector3<T> myOrigin;
		Vector3<T> myDirection;
	};

	template <class T>
	Ray<T>::Ray()
	{
		myDirection = { 0, 0, 0 };
		myOrigin = { 0, 0, 0 };
	}

	template <class T>
	Ray<T>::Ray(const Ray<T>& aRay)
	{
		myDirection = aRay.myDirection;
		myOrigin = aRay.myOrigin;
	}

	template <class T>
	Ray<T>::Ray(const Vector3<T>& aOrigin, const Vector3<T>& aPoint)
	{
		myOrigin = aOrigin;
		myDirection = aPoint - aOrigin;
	}

	template <class T>
	void Ray<T>::InitWith2Points(const Vector3<T>& aOrigin, const Vector3<T>& aPoint)
	{
		myOrigin = aOrigin;
		myDirection = aPoint - aOrigin;
	}

	template <class T>
	void Ray<T>::InitWithOriginAndDirection(const Vector3<T>& aOrigin, const Vector3<T>& aDirection)
	{
		myOrigin = aOrigin;
		myDirection = aDirection;
	}
	template<class T>
	Vector3<T> Ray<T>::GetOrigin() const
	{
		return myOrigin;
	}
	template<class T>
	Vector3<T> Ray<T>::GetDirection()
	{
		return myDirection;
	}
}
