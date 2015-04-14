//#include <iostream>
//#include <sstream>

#include "Matrix3.h"

/*
	Constructor
*/
Matrix3::Matrix3(){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			data[i][j]=0;
			}
		}
	}

/*
	Constructor from array
*/
Matrix3::Matrix3(const double (&inputData)[3][3]){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			data[i][j]=inputData[i][j];
			}
		}
	}

/*
	Copy constructor
*/
Matrix3::Matrix3(const Matrix3 &matrix3toCopy){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			data[i][j]=matrix3toCopy.get(i,j);
			}
		}
	}

/*
	Assignement operator
*/
void Matrix3::operator=(const Matrix3 &matrix3toCopy){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			data[i][j]=matrix3toCopy.get(i,j);
			}
		}
	}

/*
	Get element method
*/
double Matrix3::get(int i, int j) const {
	return data[i][j];
	}

/*
	Get row method
*/
Vector3 Matrix3::getRow(int i){
	Vector3 result=Vector3();
	for(int j=0;j<3;j++){
		result.set(j,data[i][j]);
		}
	return result;
	}

/*
	Get col  method
*/
Vector3 Matrix3::getCol(int j){
	Vector3 result=Vector3();
	for(int i=0;i<3;i++){
		result.set(i,data[i][j]);
		}
	return result;
	}

/*
	Set element method
*/
void Matrix3::set(int i, int j,double value){
	data[i][j]=value;
	}

/*
	Set row method
*/
void Matrix3::setRow(int i, const Vector3& inputRow) {
	for(int j=0;j<3;j++){
		data[i][j]=inputRow.get(j);
		}
	}

/*
	Set column method
*/
void Matrix3::setCol(int j, const Vector3& inputRow) {
	for(int i=0;i<3;i++){
		data[i][j]=inputRow.get(i);
		}
	}

/*
	toString method
*/
std::string Matrix3::toString(){
	std::stringstream sstr;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			sstr<<data[i][j]<<"\t";
			}
		sstr<<"\n";
		}
	return sstr.str();
	}

/*
	trace method
*/
double Matrix3::trace(){
	double trace=0;
	for(int i=0;i<3;i++){
		trace+=data[i][i];
		}
	return trace;
	}

/*
	determinant method
*/
double Matrix3::det(){
	double det=data[0][0]*data[1][1]*data[2][2];
	det+=data[0][1]*data[1][2]*data[2][0];
	det+=data[0][2]*data[1][0]*data[2][1];

	det-=data[0][0]*data[1][2]*data[2][1];
	det-=data[0][1]*data[1][0]*data[2][2];
	det-=data[0][2]*data[1][1]*data[2][0];

	return det;
	}

/*
	inversion method
*/
void Matrix3::invert(){
	double determ=det();
	double inverseData[3][3];

	inverseData[0][0] = (data[1][1]*data[2][2] - data[1][2]*data[2][1])/determ;
	inverseData[0][1] = (data[0][2]*data[2][1] - data[0][1]*data[2][2])/determ;
	inverseData[0][2] = (data[0][1]*data[1][2] - data[0][2]*data[1][1])/determ;
	inverseData[1][0] = (data[1][2]*data[2][0] - data[1][0]*data[2][2])/determ;
	inverseData[1][1] = (data[0][0]*data[2][2] - data[0][2]*data[2][0])/determ;
	inverseData[1][2] = (data[0][2]*data[1][0] - data[0][0]*data[1][2])/determ;
	inverseData[2][0] = (data[1][0]*data[2][1] - data[1][1]*data[2][0])/determ;
	inverseData[2][1] = (data[0][1]*data[2][0] - data[0][0]*data[2][1])/determ;
	inverseData[2][2] = (data[0][0]*data[1][1] - data[0][1]*data[1][0])/determ;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			data[i][j]=inverseData[i][j];
			}
		}
	}

/*
	transponation method
*/
void Matrix3::transpon(){
	double temp=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<i;j++){
			temp=data[i][j];
			data[i][j]=data[j][i];
			data[j][i]=temp;
			}
		}
	}
		
/*
	matrix addition method
*/
Matrix3 operator+(Matrix3 lMat, const Matrix3& rMat){
	Matrix3 sumMat=Matrix3();
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			sumMat.set(i,j,lMat.get(i,j)+rMat.get(i,j));
			}
		}
	return sumMat;
	}

/*
	left scalar addition method
*/
Matrix3 operator+(double scalar, const Matrix3& rMat){
	Matrix3 sumMat=Matrix3();
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			sumMat.set(i,j,scalar+rMat.get(i,j));
			}
		}
	return sumMat;
	}
		
/*
	left scalar multiplication method
*/
Matrix3 operator*(double scalar, const Matrix3& rMat){
	Matrix3 sumMat=Matrix3();
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			sumMat.set(i,j,scalar*rMat.get(i,j));
			}
		}
	return sumMat;
	}

/*
	matrix substraction method
*/
Matrix3 operator-(Matrix3 lMat, const Matrix3& rMat){
	return lMat+(-1*rMat);
	}

/*
	right scalar addition method
*/
Matrix3 operator+( const Matrix3& lMat, double scalar){
	return scalar+lMat;
	}
	
/*
	right scalar multiplication method
*/
Matrix3 operator*( const Matrix3& lMat, double scalar){
	return scalar*lMat;
	}

/*
	right scalar substraction method
	!!note there is no left scalar method
*/
Matrix3 operator-( const Matrix3& lMat, double scalar){
	return -scalar+lMat;
	}
	
/*
	right scalar division method
	!!note there is no left scalar method
*/
Matrix3 operator/( const Matrix3& lMat, double scalar){
	return (1/scalar)*lMat;
	}
	
/*
	matrix multiplication method
*/
Matrix3 operator*( Matrix3 lMat,const Matrix3& rMat ){
	Matrix3 mulMat=Matrix3();
	double temp;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			temp=0;
			for(int k=0;k<3;k++){
				temp+=lMat.get(i,k)*rMat.get(k,j);
				}
			mulMat.set(i,j,temp);
			}
		}
	return mulMat;
	}

/*
	Vector multiplication M*v
*/
Vector3 operator*(const Matrix3& lMat,const Vector3& rVec ){
	Vector3 result=Vector3();
	double temp;
	for(int i=0;i<3;i++){
		temp=0;
		for(int j=0;j<3;j++){
			temp+=lMat.get(i,j)*rVec.get(j);
			}
		result.set(i,temp);
		}
	return result;
	}


/*
	Vector multiplication v*M 
*/
Vector3 operator*(const Vector3& lVec,const Matrix3& rMat){
	Vector3 result=Vector3();
	double temp;
	for(int j=0;j<3;j++){
		temp=0;
		for(int i=0;i<3;i++){
			temp+=rMat.get(i,j)*lVec.get(j);
			}
		result.set(j,temp);
		}
	return result;
	}


/*
	Vector multiplication v*M 
*/
Matrix3 diad(const Vector3& lVec,const Vector3& rVec){
	Matrix3 result=Matrix3();
	for(int j=0;j<3;j++){
		for(int i=0;i<3;i++){
			result.set(i,j,lVec.get(i)*rVec.get(j));
			}
		}
	return result;
	}

