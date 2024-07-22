#ifndef VECTORSET_H
#define VECTORSET_H

#include <set>
#include <unordered_set>
#include <memory>
#include <vector>
#include <iostream>

struct Vec3
{
	double x, y, z;

	Vec3(float x, float y, float z);
	
	bool operator<(const Vec3& rhs) const noexcept
	{
		return magnitude() < rhs.magnitude();
	}
	double magnitude() const { return sqrt(x * x + y * y + z * z); }

	void operator=(const Vec3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
};



class VectorSet
{
public:

	explicit VectorSet(float angleEps);
	
	~VectorSet();

	bool addVector(const Vec3& v);
	
	unsigned removeVector(const Vec3& v);

	void clear();

	unsigned getSize() const;

	bool findClosest(const Vec3& v,Vec3* closest) const;
	
private:
	std::vector<Vec3> m_vectorSet;
	double m_epsilon;
};

#endif
