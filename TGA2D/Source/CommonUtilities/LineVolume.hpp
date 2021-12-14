#pragma once
#include <vector>

#include "Line.hpp"

namespace CommonUtilities
{
	template <class T>
	class LineVolume
	{
	public:
		// Default constructor: empty LineVolume.
		LineVolume();
		// Constructor taking a list of Line that makes up the LineVolume.
		LineVolume(const std::vector<Line<T>>& aLineList);
		// Add a Line to the LineVolume.
		void AddLine(const Line<T>& aLine);
		void UpdateLines(const Line<T>& aLine, const int& aAt);
		// Returns whether a point is inside the LineVolume: it is inside when the point is
		// on the line or on the side the normal is pointing away from for all the lines in
		// the LineVolume.
		bool IsInside(const Vector2<T>& aPosition);

	private:
		std::vector<Line<T>> myLines;
	};

	template <class T>
	LineVolume<T>::LineVolume()
	{
		//?
	}

	template <class T>
	LineVolume<T>::LineVolume(const std::vector<Line<T>>& aLineList)
	{
		myLines = aLineList;
	}

	template <class T>
	void LineVolume<T>::AddLine(const Line<T>& aLine)
	{
		myLines.push_back(aLine);
	}

	template <class T>
	void LineVolume<T>::UpdateLines(const Line<T>& aLine, const int& aAt)
	{
		myLines[aAt] = aLine;
	}


	template <class T>
	bool LineVolume<T>::IsInside(const Vector2<T>& aPosition)
	{
		for (Line<T> line : myLines)
		{
			if (!line.IsInside(aPosition))
			{
				return false;
			}
		}

		return true;
	}
}
