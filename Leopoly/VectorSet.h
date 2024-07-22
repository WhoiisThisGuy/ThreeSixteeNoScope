/*

Keszitsunk 3 dimenzios iranyvektorok halmazat reprezentalo osztalyt! 
A halmazban ket ugyanolyan iranyvektor nem szerepelhet. 
Ket vektort akkor tekintunk egyenlonek, ha a ket vektor altal bezart szog 
kisebb, mint valamely epsilon. Ez az epsilon a halmaz parametere lesz 
(a konstruktorban kapja meg az osztaly peldanya).

Az alabbiakban megadjuk az osztaly feluletet, a feladat az implementacio.
A lenti interface-eket egeszitsuk ki az implementaciohoz szukseges 
adattagokkal es fuggvenyekkel.

A hatekonysag most nem szempont, a lenyeg, hogy mukodjon jol.

Bonusz: nem kell implementalni,csak otletelni. Milyen modszereket lehetne 
alkalmazni ahhoz, hogy az osztalyban levo addVector, removeVector es findClosest 
muveletek a leheto leghatekonyabbak legyenek (minel kevesebb osszehasonlitast 
kelljen vegezni a halmazban levo meglevo elemekkel)?
*/


#ifndef VECTORSET_H
#define VECTORSET_H

#include <set>
#include <unordered_set>
#include <memory>
#include <vector>
#include <iostream>

// 3D vektorokat reprezentalo struktura, 
// a VectorSet felulete ilyeneket var es ad vissza
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


// iranyvektorokat tarolo halmaz
class VectorSet
{
public:
	// a konstruktor parametere az epsilon szog radianban megadva
	explicit VectorSet(float angleEps);
	
	~VectorSet();
	
	// Vektor hozzaadasa a halmazhoz. 
	// Igazzal ter vissza, ha a halmazban meg nem volt ilyen iranyu vektor.
	bool addVector(const Vec3& v);
	
	// Vektor(ok) kivetele a halmazbol. 
	// A v-vel megegyezo iranyu vektorokat kiveszi a halmazbol 
    // (vegyuk eszre, hogy ez egynel tobb is lehet). 
	// A visszateresi ertek a kivett vektorok szama.
	unsigned removeVector(const Vec3& v);
	
	// Kiuriti a halmazt.
	void clear();
	
	// A halmazban levo elemek szamat adja vissza.
	unsigned getSize() const;
	
	// Megkeresi a halmazban azt a vektort, mely v-vel a legkisebb szoget zarja be.
	// Ha a halmaz ures, akkor false-ot ad vissza,
	// kulonben true-t es a closest altal mutatott Vec3-ba tolti be az eredmenyt.
	bool findClosest(const Vec3& v,Vec3* closest) const;
	
private:
	std::vector<Vec3> m_vectorSet;
	double m_epsilon;
};

#endif
