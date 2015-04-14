#ifndef MATRIX_H 
#define MATRIX_H

#include <iostream>
#include <string>
//#include <fstream>
//#include <vector>
#include <sstream>
//#include <random>
//#include <map>
//#include <float.h>

#include "Vector3.h"

class Matrix3{
	//constructors
	public:
	Matrix3();//zeroes
	Matrix3(const Matrix3 &matrix3toCopy);//copies
	Matrix3(const double (&inputData)[3][3]);//from array

	//data
	private:
	double data[3][3];

	//methods	
	public:
	void operator=(const Matrix3& matrix3ToCopy);
	double get(int i, int j) const;//getters
	Vector3 getRow(int i);
	Vector3 getCol(int j);
	void set(int i, int j,double value);//setters
	void setRow(int i, const Vector3& inputRow); 
	void setCol(int j, const Vector3& inputCol);

	std::string toString(); //toString

	//math stuff
	double trace();
	double det();
	void transpon();
	void invert();

	

	};
	
	//matrix algebra as non-member operators
	//core
	Matrix3 operator+(Matrix3 lMat, const Matrix3& rMat);
	Matrix3 operator+(double scalar, const Matrix3& rMat);
	Matrix3 operator*(double scalar, const Matrix3& rMat);

	//combinations (rigths, + inverses)
	Matrix3 operator-(Matrix3 lMat, const Matrix3& rMat);
	Matrix3 operator+( const Matrix3& lMat, double scalar);
	Matrix3 operator*( const Matrix3& lMat, double scalar);
	Matrix3 operator-( const Matrix3& lMat, double scalar);
	Matrix3 operator/( const Matrix3& lMat, double scalar);
	//matmult
	Matrix3 operator*( Matrix3 lMat,const Matrix3& rMat );
	
	//vector arithmetics
	Vector3 operator*(const Vector3& lVec,const Matrix3& rMat);
	Vector3 operator*(const Matrix3& lMat,const Vector3& rVec );
	
	//diad
	Matrix3 diad(const Vector3& lVec,const Vector3& rVec);

#endif
