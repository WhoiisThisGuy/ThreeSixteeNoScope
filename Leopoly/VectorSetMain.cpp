#include "VectorSet.h"
#include <iostream>
#include <cmath>

using namespace std;

bool testPassed = true;

void check(bool condition, const char* msg)
{
	if (!condition)
	{
		cout << "Condition not fulfilled, testcase failed: " << msg << endl;
		testPassed = false;
	}
}

const float PI = 3.1415926535897932384626433832795f;

static const float DegToRad(float deg)
{
	return deg * PI / 180.0f;
}


int main()
{
	for (float ae = 0.1f; ae < 25.0f; ae += 0.1f)
	{
		float angleEps = DegToRad(ae);
		
		VectorSet vs(angleEps);

		int k1 = 0;
		for (float phi = 0.0f; phi < PI; phi += angleEps * 2.0f)
		{
			++k1;
			if (!vs.addVector(Vec3(3.0f * cosf(phi), 3.0f * sinf(phi), 0.0f)))
			{
				cout << "XXOUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUPS!!!!\n";
			}
		}
		
		check(k1 == vs.getSize(), "addVector problem");
		if (!testPassed)
			break;
		int k = k1;
		for (float phi = angleEps / 2.0f; phi < PI; phi += angleEps * 4.0f)
		{
			--k;
			vs.removeVector(Vec3(3.0f * cosf(phi), 3.0f * sinf(phi), 0.0f))<<'\n';
		}
		check(k == vs.getSize(), "removeVector problem");
		if (!testPassed)
			break;
		for (float phi = 0.0f; phi < PI; phi += angleEps * 2.0f)
		{
			vs.addVector(Vec3(3.0f * cosf(phi), 3.0f * sinf(phi), 0.0f));
		}
		check(vs.getSize() == k1, "addVector problem");
		if (!testPassed) {
			cout << "xxxxxxxxxxxoooooooooo k1 is: " << k1 << '\t' << " vs.getSize(): " << vs.getSize() << '\n';
			break;
		}
	}

    VectorSet vs(DegToRad(1.0f));
	Vec3 closest(0.0f, 0.0f, 0.0f);
	bool found = vs.findClosest(Vec3(1.0f, 2.0f, 3.0f), &closest);
	check(!found, "findClosest problem");
	
	vs.addVector(Vec3(0.0f, 1.0f, 0.0f));
	vs.addVector(Vec3(0.0f, 0.0f, 1.0f));
	found = vs.findClosest(Vec3(1.0f, 0.1f, 0.0f), &closest);
	check(found && 
		closest.x == 0.0f && 
		closest.y == 1.0f && 
		closest.z == 0.0f, 
		"findClosest problem");
	
	if (testPassed)
	{
		cout << "Test passed." << endl;
	}
	else
	{
		cout << "Test failed." << endl;
	}

	return 0;
}
