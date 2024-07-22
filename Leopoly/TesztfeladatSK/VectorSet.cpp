#include "VectorSet.h"


Vec3::Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{
}


VectorSet::VectorSet(float angleEps) : m_epsilon(angleEps)
{
}


VectorSet::~VectorSet()
{
}

int inline dotproduct(const Vec3& v1, const Vec3& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vec3 inline crossProduct(const Vec3& a, const Vec3& b)
{
	return Vec3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x));
}

bool inline isEqualDirection(const Vec3& a, const Vec3& b,double eps)
{
	
	return (dotproduct(a, b) / (a.magnitude() * b.magnitude())) < eps;
}

bool inline isEqualDirectionB(const Vec3& a, const Vec3& b, double eps)
{
	float x = a.x > b.x ? a.x - b.x : b.x - a.x;
	float y = a.y > b.y ? a.y - b.y : b.y - a.y;
	float z = a.z > b.z ? a.z - b.z : b.z - a.z;

	return x <= eps && y <= eps && z <= eps;
}

bool VectorSet::addVector(const Vec3& v)
{
	//check if we can add it
	Vec3* closest = nullptr;
	
	if (findClosest(v, closest) && closest)
	{
		int dotProduct = dotproduct(v, *closest);
		if ((dotProduct / (v.magnitude() * closest->magnitude())) < m_epsilon)
		{
			return false;
		}
		
	}
	m_vectorSet.emplace_back(v);
	return false;
}


unsigned VectorSet::removeVector(const Vec3& v)
{
	int n = 0;
	for (auto it = m_vectorSet.begin();it!=m_vectorSet.end();)
	{
		auto& a = *it;
		auto tempVec = crossProduct(a, v);
		if (isEqualDirection(tempVec,v,m_epsilon))
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

bool VectorSet::findClosest(const Vec3& v, Vec3* closest) const
{
	if (m_vectorSet.empty())
	{
		return false;
	}
	double closestCosAlph = 0.0;
	closest = new Vec3( *m_vectorSet.begin()); //assume first one is the closest

	//Dot product
	int dotProduct = 0;
	for (auto &a : m_vectorSet)
	{
		dotProduct = dotproduct(a,v);
		double tempCosAlph = dotProduct / (a.magnitude() * v.magnitude());
		
		if (tempCosAlph<closestCosAlph)
		{
			closestCosAlph = tempCosAlph;
			*closest = a;
		}
	}
	
	return true;
}
