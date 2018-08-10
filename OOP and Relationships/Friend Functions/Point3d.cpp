#include "stdafx.h"
#include <iostream>
#include "Point3d.h"		//for Point3d class definitions
#include "Vector3d.h"		//for the moveByVector parameter


void Point3d::print()
{
	std::cout << "Point(" << m_x << " , " << m_y << " , " << m_z << ")\n";
}

void Point3d::moveByVector(const Vector3d &v)	//needs to have seen a full declaration of Vector3d
{
	m_x += v.m_x;
	m_y += v.m_y;
	m_z += v.m_z;
	// implement this function as a friend of class Vector3d
}