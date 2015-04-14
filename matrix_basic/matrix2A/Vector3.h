#ifndef VECTOR3_H 
#define VECTOR3_H

#include <iostream>
#include <string>
//#include <fstream>
//#include <vector>
#include <sstream>
//#include <random>
//#include <map>
//#include <float.h>

//minimal vector class
//for vector operations w matrices
class Vector3{
	//constructors
	public:
	Vector3();//zeroes
	
	//data
	private:
	double data[3];

	//methods	
	public:
	double get(int i) const;
	void set(int i,double value);
	void operator=(const Vector3& Vector3ToCopy);
	std::string toString(); //toString

	};
	
#endif
