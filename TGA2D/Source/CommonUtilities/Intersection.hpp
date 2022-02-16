#pragma once
#include "AABB3D.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "UtilityFunctions.hpp"

namespace CommonUtilities
{
	template <class T>
	bool IntersectionPlaneRay(const Plane<T>& aPlane, Ray<T>& aRay, Vector3<T>& aOutIntersectionPoint)
	{
		T denom = aPlane.GetNormal().Dot(aRay.GetDirection().GetNormalized());
		if (std::abs(denom) > 0)
		{
			Vector3<T> pointFromOrigin = aPlane.GetOrigin() - aRay.GetOrigin();
			T t = pointFromOrigin.Dot(aPlane.GetNormal());
			if (t >= 0)
			{
				aOutIntersectionPoint = pointFromOrigin;
				return true;
			}
		}
		return false;
	}

	template <class T>
	bool IntersectionAABBRay(AABB3D<T>& aAABB, Ray<T>& aRay)
	{
		T tMin = (aAABB.GetMin().x - aRay.GetOrigin().x) / aRay.GetDirection().x;
		T tMax = (aAABB.GetMax().x - aRay.GetOrigin().x) / aRay.GetDirection().x;

		if (tMin > tMax)
		{
			Swap(tMin, tMax);
		}

		T tyMin = (aAABB.GetMin().y - aRay.GetOrigin().y) / aRay.GetDirection().y;
		T tyMax = (aAABB.GetMax().y - aRay.GetOrigin().y) / aRay.GetDirection().y;

		if (tyMin > tyMax)
		{
			Swap(tyMin, tyMax);
		}

		if (tyMin > tMin)
		{
			tMin = tyMin;
		}

		if (tyMax < tMax)
		{
			tMax = tyMax;
		}

		T tzMin = (aAABB.GetMin().z - aRay.GetOrigin().z) / aRay.GetDirection().z;
		T tzMax = (aAABB.GetMax().z - aRay.GetOrigin().z) / aRay.GetDirection().z;

		if (tzMin > tyMax)
		{
			Swap(tzMin, tzMax);
		}

		if ((tMin >= tzMax) || (tzMin >= tMax))
		{
			return false;
		}

		if (tzMax > tMin)
		{
			tMin = tzMin;
		}

		if (tzMax < tMax)
		{
			tMax = tzMax;
		}

		return true;
	}

	template <class T>
	bool IntersectionAABBtoAABB(AABB3D<T>& aAABB1, AABB3D<T>& aAABB2)
	{
		if (aAABB1.GetMin().x <= aAABB2.GetMax().x && aAABB1.GetMax().x <= aAABB2.GetMin().x) { return false; }
		if (aAABB1.GetMin().y <= aAABB2.GetMax().y && aAABB1.GetMax().y <= aAABB2.GetMin().y) { return false; }
		if (aAABB1.GetMin().z <= aAABB2.GetMax().z && aAABB1.GetMax().z <= aAABB2.GetMin().z) { return false; }
		return true;
	}

	template <class T>
	bool IntersectionSphereRay(Sphere<T>& aSphere, Ray<T>& aRay)
	{
		T t0, t1;
		const Vector3<T> L = aSphere.GetPosition() - aRay.GetOrigin();
		Vector3<T> norm = aRay.GetDirection().GetNormalized();
		T tca = (L.x * norm.x) + (L.y * norm.y) + (L.z * norm.z);
		T d2 = L.Dot(L) - tca * tca;
		if (d2 > (aSphere.GetRadius() * aSphere.GetRadius()))
		{
			return false;
		}
		T thc = sqrt((aSphere.GetRadius() * aSphere.GetRadius()) - d2);
		t0 = tca - thc;
		t1 = tca + thc;

		if (t0 > t1)
		{
			Swap(t0, t1);
		}
		if (t0 > 0)
		{
			t0 = t1;
			if (t0 < 0) return false;
		}

		return true;
	}

	template <class T>
	bool IntersectionSphereToSphere(Sphere<T>& aSphere1, Sphere<T>& aSphere2)
	{
		Vector3 tempVec = aSphere2.GetPosition() - aSphere1.GetPosition();
		return (tempVec.LengthSqr() <= aSphere1.GetRadius() * aSphere1.GetRadius() + aSphere2.GetRadius() * aSphere2.GetRadius());
	}
}