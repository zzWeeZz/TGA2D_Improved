#pragma once
#include <math.h>
#include <cassert>
#include <stdint.h>

namespace CommonUtilities
{
	template <class T>
	class Vector3
	{
	public:
		T x;
		T y;
		T z;
		//Creates a null-vector
		Vector3<T>();
		//Creates a vector (aX, aY, aZ)
		Vector3<T>(const T& aX, const T& aY, const T& aZ);
		//Copy constructor (compiler generated)
		Vector3<T>(const Vector3<T>& aVector) = default;
		//Assignment operator (compiler generated)
		Vector3<T>& operator=(const Vector3<T>& aVector3) = default;

		//Returns the squared length of the vector
		T LengthSqr() const;
		//Returns the length of the vector
		T Length() const;
		//Returns a normalized copy of this
		Vector3<T> GetNormalized() const;
		//Normalizes the vector
		void Normalize();
		//Normalize but fast
		void FastNormalize();
		//Returns the dot product of this and aVector
		T Dot(const Vector3<T>& aVector) const;
		//Returns the cross product of this and aVector
		Vector3<T> Cross(const Vector3<T>& aVector) const;
	};

	//f�r dig tommie :D
	/*float Q_rsqrt(float number)
	{
		const float x2 = number * 0.5F;
		const float threehalfs = 1.5F;

		union 
		{
			float    f;
			uint32_t i;
		} conv = { .f = number };
		conv.i = 0x5f3759df - (conv.i >> 1);
		conv.f *= threehalfs - (x2 * conv.f * conv.f);
		return conv.f;
	}*/

	template<class T>
	Vector3<T>::Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	
	template<class T>
	Vector3<T>::Vector3(const T& aX, const T& aY, const T& aZ)
	{
		x = aX;
		y = aY;
		z = aZ;
	}
	
	template<class T>
	T Vector3<T>::LengthSqr() const
	{
		return (x*x) + (y * y) + (z *z);
	}

	template<class T>
	T Vector3<T>::Length() const
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

	template<class T>
	Vector3<T> Vector3<T>::GetNormalized() const
	{
		assert(x != 0 || y != 0 || z != 0 && "You can't devide by zero");
		T magnitude = 1 / Length();
		return Vector3<T>(x * magnitude, y * magnitude, z * magnitude);
	}

	
	template<class T>
	void Vector3<T>::Normalize()
	{
		assert(x != 0 || y != 0 || z != 0 && "You can't devide by zero");
		T magnitude =  1 / Length();
		x *= magnitude;
		y *= magnitude;
		z *= magnitude;
	}

	template<class T>
	void Vector3<T>::FastNormalize()
	{
		assert(x != 0 || y != 0 || z != 0 && "You can't devide by zero");
		T magnitude = Q_rsqrt(LengthSqr());
		x *= magnitude;
		y *= magnitude;
		z *= magnitude;
	}

	template<class T>
	T Vector3<T>::Dot(const Vector3<T>& aVector) const
	{
		return (x * aVector.x) + (y * aVector.y) + (z * aVector.z);
	}

	// y z z y
	// z x x z
	// x y y x

	template<class T>
	Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
	{
		return Vector3<T>((y * aVector.z) - (z * aVector.y), (z * aVector.x) - (x * aVector.z), (x * aVector.y) - (y * aVector.x));
	}
	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>&aVector1) 
	{
		return Vector3<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y, aVector0.z + aVector1.z);
	}
	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>&aVector1)
	{
		return Vector3<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y, aVector0.z - aVector1.z);
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
	{
		return Vector3<T>(aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar);
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{
		return Vector3<T>(aScalar*aVector.x, aScalar * aVector.y, aScalar * aVector.z);

	}
	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVectormultiplied by 1 / aScalar)
	template <class T> Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
	{
		assert(aScalar != 0 && "You can't devide by zero");
		return Vector3<T>(aVector.x * (1/aScalar), aVector.y * (1 / aScalar), aVector.z * (1 / aScalar));
	}
	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		 aVector0 = aVector0 + aVector1;
	}
	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0 = aVector0 - aVector1;
	}
	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector3<T>& aVector, const T& aScalar) 
	{
		aVector = aVector * aScalar;
	}
	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector3<T>& aVector, const T& aScalar)
	{
		assert(aScalar != 0 && "You can't devide by zero");
		aVector = aVector / aScalar;
	}
}