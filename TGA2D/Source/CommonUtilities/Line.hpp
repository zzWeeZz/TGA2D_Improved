#pragma once
#include "Vector2.hpp"

namespace CommonUtilities
{
	template <class T>
	class Line
	{
	public:
		// Default constructor: there is no line, the normal is the zero vector.
		Line();
		// Copy constructor.
		Line(const Line <T>& aLine);
		// Constructor that takes two points that define the line, the direction is aPoint1 - aPoint0.
		Line(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1);
		// Init the line with two points, the same as the constructor above.
		void InitWith2Points(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1);
		// Init the line with a point and a direction.
		void InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection);
		// Returns whether a point is inside the line: it is inside when the point is on the line or on the side the normal is pointing away from.
		bool IsInside(const Vector2<T>& aPosition) const;
		// Returns the origin of the line
		const Vector2<T>& GetOrigin() const;
		// Returns the direction of the line.
		const Vector2<T>& GetDirection() const;
		// Returns the normal of the line, which is (-direction.y, direction.x).
		const Vector2<T> GetNormal() const;

	private:
		Vector2<T> myOrigin;
		Vector2<T> myDirection;
	};

	template <class T>
	Line<T>::Line()
	{
		myOrigin = Vector2<T>(0, 0);
		myDirection = Vector2<T>(0, 0);
	}

	template <class T>
	Line<T>::Line(const Line<T>& aLine)
	{
		myOrigin = aLine.GetOrigin();
		myDirection = aLine.GetDirection();
	}

	template <class T>
	Line<T>::Line(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
	{
		myOrigin = aPoint0;
		myDirection = aPoint1 - aPoint0;
	}

	template <class T>
	void Line<T>::InitWith2Points(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
	{
		myOrigin = aPoint0;
		myDirection = aPoint1 - aPoint0;
	}

	template <class T>
	void Line<T>::InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection)
	{
		myOrigin = aPoint;
		myDirection = aDirection;
	}

	template <class T>
	bool Line<T>::IsInside(const Vector2<T>& aPosition) const
	{
		return GetNormal().Dot(aPosition - myOrigin) <= 0;
	}

	template <class T>
	const Vector2<T>& Line<T>::GetOrigin() const
	{
		return myOrigin;
	}

	template <class T>
	const Vector2<T>& Line<T>::GetDirection() const
	{
		return myDirection;
	}

	template <class T>
	const Vector2<T> Line<T>::GetNormal() const
	{
		return Vector2<T>(-myDirection.y, myDirection.x);
	}
}
