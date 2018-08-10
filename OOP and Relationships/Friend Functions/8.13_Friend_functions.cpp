// 8.13_Friend_functions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vector3d.h"
//#include "Point3d.h"			//dont need this because it is already included in vector3d

int main()
{
	Point3d p(1.0, 2.0, 3.0);
	Vector3d v(2.0, 2.0, -3.0);

	p.print();
	p.moveByVector(v);
	p.print();

	return 0;
}