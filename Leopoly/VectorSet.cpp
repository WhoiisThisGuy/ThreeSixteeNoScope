#include "VectorSet.h"
#include <iostream> //debug only

Vec3::Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{
}


VectorSet::VectorSet(float angleEps) : m_epsilon(angleEps)
{
}

const double PI = 3.1415926535897932384626433832795f;

static const double DegToRad(double deg)
{
	return deg * PI / 180.0f;
}

double radiansToDegrees(double radians) {
	return radians * (180.0 / PI);
}

VectorSet::~VectorSet()
{
}

double inline dotproduct(const Vec3& v1, const Vec3& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

bool inline isEqual(const Vec3& a, const Vec3& b,const double eps)
{
	const double dot = dotproduct(a, b);
	const double mag1 = a.magnitude();
	const double mag2 = b.magnitude();
	double Theta = dot / (mag1 * mag2);
	// Ensure Theta is within the valid range for acos due to numerical precision issues
	if (Theta > 1.0) Theta = 1.0;
	if (Theta < -1.0) Theta = -1.0;

	const auto radcosTheta = std::acos(Theta);

	return radcosTheta < eps;
}

bool VectorSet::addVector(const Vec3& vecToAdd)
{
	//check if we can add it
	Vec3 closest(0,0,0);
	//std::cout << "xxxAAAAAAAAAAAAADdVector x, y ,z: " << vecToAdd.x << ' ' << vecToAdd.y << ' ' << vecToAdd.z << '\n';
	if (findClosest(vecToAdd, &closest))
	{
		//std::cout << "xxxxxxyyyClosest x, y ,z: " << closest.x << ' ' << closest.y << ' ' << closest.z<<'\n';
		if (isEqual(vecToAdd,closest,m_epsilon))
		{
			return false;
		}
		
	}
	m_vectorSet.emplace_back(vecToAdd);
	return true;
}


unsigned VectorSet::removeVector(const Vec3& vecToRemove)
{
	int n = 0;
	int i = 0;
	for (auto it = m_vectorSet.begin();it!=m_vectorSet.end();)
	{
		++i;
		auto& a = *it;
		
		if (isEqual(a, vecToRemove,m_epsilon))
		{
			it = m_vectorSet.erase(it);
			++n;
		}
		else
		{
			++it;
		}
	}
	
	return n;
}


void VectorSet::clear()
{
	m_vectorSet.clear();
}


unsigned VectorSet::getSize() const
{
	return static_cast<unsigned>(m_vectorSet.size());
}

bool VectorSet::findClosest(const Vec3& targetVector, Vec3* closest) const
{
	if (m_vectorSet.empty())
	{
		return false;
	}
	double degSmallestAngle = 360.0;
	for (const Vec3 &vecFromSet : m_vectorSet)
	{
		auto tempRadTheta = (dotproduct(vecFromSet, targetVector) / (vecFromSet.magnitude() * targetVector.magnitude()));
		if (tempRadTheta > 1.0)
		{
			tempRadTheta = 1.0;
		}
		else if (tempRadTheta < -1.0)
		{
			tempRadTheta = -1.0;
		}
		const auto radTheta = std::acos(tempRadTheta);
		
		const auto degTheta = radiansToDegrees(radTheta);
		if(radTheta <0)
		{
			std::cout << "radTheta is negative: "<< radTheta <<'\n';
		}
		if (degTheta <= degSmallestAngle)
		{
			degSmallestAngle = degTheta;
			if (closest)
			{
				closest->x = vecFromSet.x;
				closest->y = vecFromSet.y;
				closest->z = vecFromSet.z;
			}
		}
	}
	
	return true;
}
