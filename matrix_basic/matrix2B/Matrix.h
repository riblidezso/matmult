#ifndef MATRIX_H 
#define MATRIX_H

#include <iostream>
#include <string>
#include <sstream>
#include <initializer_list>
#include <stdlib.h>
#include <stdio.h>

#include "Vector.h"

template<typename T, size_t d> 
class Matrix{
	//contructors
	public:
	Matrix();//zeroes
	Matrix(const T (&inputData)[d][d]);//from array
	Matrix(std::initializer_list<T> initVals);//from array
	Matrix(std::initializer_list<std::initializer_list<T> > initVals);
	Matrix(const Matrix<T,d> &matrixToCopy);//copies

	//data
	private:
	T data[d][d];	

	//methods	
	public:
	void operator=(const Matrix<T,d>& matrixToCopy);//assign
	std::string toString(); //toString

	T get(int i, int j) const;//getters
	Vector<T,d> getRow(int i);
	Vector<T,d> getCol(int j);
	void set(int i, int j,T value);//setters
	void setRow(int i, const Vector<T,d>& inputRow); 
	void setCol(int j, const Vector<T,d>& inputCol);

	//math stuff
	T trace();
	T det();
	Matrix<T,d> transpon();
	Matrix<T,d> gauInv();
};

////////////////////////////////////////////////////////////////////
//Not member

	//diad
	template<typename T, size_t d> 
	Matrix<T,d> diad(const Vector<T,d>& lVec,const Vector<T,d>& rVec);

	//matrix algebra as non-member operators
	//core
	template<typename T, size_t d> 
	Matrix<T,d> operator+(Matrix<T,d> lMat, const Matrix<T,d>& rMat);
	template<typename T, size_t d> 
	Matrix<T,d> operator*(T scalar, const Matrix<T,d>& rMat);

	//combinations (rigths, + inverses)
	template<typename T, size_t d> 
	Matrix<T,d> operator-(Matrix<T,d> lMat, const Matrix<T,d>& rMat);
	template<typename T, size_t d> 
	Matrix<T,d> operator*( const Matrix<T,d>& lMat, T scalar);
	template<typename T, size_t d> 
	Matrix<T,d> operator/( const Matrix<T,d>& lMat, T scalar);

	//matmult
	template<typename T, size_t d> 
	Matrix<T,d> operator*( Matrix<T,d> lMat,const Matrix<T,d>& rMat );
	
	//vector arithmetics
	template<typename T, size_t d> 
	Vector<T,d> operator*(const Vector<T,d>& lVec,const Matrix<T,d>& rMat);
	template<typename T, size_t d> 
	Vector<T,d> operator*(const Matrix<T,d>& lMat,const Vector<T,d>& rVec );
	


////////////////////////////////////////////////////////
/*
	Constructor
*/
template<typename T, size_t d> 
Matrix<T,d>::Matrix(){
	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++){
			data[i][j]=0;
			}
		}
	}

/*
	Constructor from array
*/
template<typename T, size_t d> 
Matrix<T,d>::Matrix(const T (&inputData)[d][d]){
	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++){
			data[i][j]=inputData[i][j];
			}
		}
	}

/*
	Constructor from std::initiializer_list 
	row continuous!!!
*/
template<typename T, size_t d> 
Matrix<T,d>::Matrix(std::initializer_list<T> initVals){
	int i=0;
	for(auto val : initVals){
		data[i/d][i%d]=val;
		i++;
		}
	}

/*
	Constructor from std::initiializer_list 
	row continuous!!!
*/
template<typename T, size_t d> 
Matrix<T,d>::Matrix(std::initializer_list<std::initializer_list<T> > initVals){
	int i=0;
	for(auto row : initVals){
		int j=0;
		for(auto val : row){
			data[i][j]=val;
			j++;
			}
		i++;
		}
	}


/*
	Copy constructor
*/
template<typename T, size_t d> 
Matrix<T,d>::Matrix(const Matrix<T,d> &matrixtoCopy){
	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++){
			data[i][j]=matrixtoCopy.get(i,j);
			}
		}
	}

/*
	Assignement operator
*/
template<typename T, size_t d> 
void Matrix<T,d>::operator=(const Matrix<T,d> &matrixToCopy){
	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++){
			data[i][j]=matrixToCopy.get(i,j);
			}
		}
	}

/*
	toString method
*/
template<typename T, size_t d> 
std::string Matrix<T,d>::toString(){
	std::stringstream sstr;
	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++){
			sstr<<data[i][j]<<"\t";
			}
		sstr<<"\n";
		}
	return sstr.str();
	}


/*
	Get element method
*/
template<typename T, size_t d> 
T Matrix<T,d>::get(int i, int j) const {
	return data[i][j];
	}

/*
	Get row method
*/
template<typename T, size_t d> 
Vector<T,d> Matrix<T,d>::getRow(int i){
	Vector<T,d> result=Vector<T,d>();
	for(int j=0;j<d;j++){
		result.set(j,data[i][j]);
		}
	return result;
	}

/*
	Get col  method
*/
template<typename T, size_t d> 
Vector<T,d> Matrix<T,d>::getCol(int j){
	Vector<T,d> result=Vector<T,d>();
	for(int i=0;i<d;i++){
		result.set(i,data[i][j]);
		}
	return result;
	}

/*
	Set element method
*/
template<typename T, size_t d> 
void Matrix<T,d>::set(int i, int j,T value){
	data[i][j]=value;
	}

/*
	Set row method
*/
template<typename T, size_t d> 
void Matrix<T,d>::setRow(int i, const Vector<T,d>& inputRow) {
	for(int j=0;j<d;j++){
		data[i][j]=inputRow.get(j);
		}
	}

/*
	Set column method
*/
template<typename T, size_t d> 
void Matrix<T,d>::setCol(int j, const Vector<T,d>& inputRow) {
	for(int i=0;i<d;i++){
		data[i][j]=inputRow.get(i);
		}
	}


/*
	trace method
*/
template<typename T, size_t d> 
T Matrix<T,d>::trace(){
	T trace=0;
	for(int i=0;i<d;i++){
		trace+=data[i][i];
		}
	return trace;
	}

/*
	transponation method
*/
template<typename T, size_t d> 
Matrix<T,d> Matrix<T,d>::transpon(){
	Matrix<T,d> mT= Matrix<T,d>(data);
	T temp=0;
	for(int i=0;i<d;i++){
		for(int j=0;j<i;j++){
			temp=mT.get(i,j);
			mT.set(i,j,mT.get(j,i));
			mT.set(j,i,temp);
			}
		}
	return mT;
	}

/*
	Det calculating method
*/
template<typename T,size_t d> 
T Matrix<T,d>::det(){
	//upper triangulize matrix
	Matrix<T,d> uMat= Matrix<T,d>(data);
	T ratio=0;
	for(int i=0;i<d;i++){
		for(int j=0;j<i;j++){
			ratio=uMat.get(i,j)/uMat.get(j,j);
			for(int k=0;k<d;k++){
				uMat.set(i,k,uMat.get(i,k)-ratio*uMat.get(j,k));
				}
			}
		}
	//calclate det
	T determ=1;
	for(int i=0;i<d;i++){
		determ*=uMat.get(i,i);
		}
	return determ;
	}

/*
	Gaussian elimination inverter
	Actually this is copied and modified from
	old assignement, so style will be C-ish,
	and different

	Do not even think about using it on non floating point matrices!!
*/	
template<typename T,size_t d> 
Matrix<T,d> Matrix<T,d>::gauInv(){
	//simplify new matrix class to C-style matrix (p,n)
	int n=d;
	T *p = new T[d*d];
	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++){
			p[n*i+j]=data[i][j];
			}
		}
	
	//rewrite old C-style memory allocs to templates
	//long double *inv,*sormax,*ideig,*ideiginv,max,a;
	T max,a;
	int i,j,j1,holmax;
	//inv=(long double*)calloc(n*n,sizeof(long double));
	T *inv = new T[d*d];
	//sormax=(long double*)calloc(n,sizeof(long double));
	T *sormax = new T[d];
	//ideig=(long double*)calloc(n,sizeof(long double));
	T *ideig = new T[d];
	//ideiginv=(long double*)calloc(n,sizeof(long double));
	T *ideiginv = new T[d];


	//from this part it is absolutely unmodified old C code
	//////////////////////////////////////////////////////////////////


//Normálás

	for(i=0;i<n;i++)
	{
		//max keresése
		for(j=0;j<n;j++)
		{
			if (sormax[i]<p[n*i+j])
			{
				sormax[i]=p[n*i+j];
			}
		}

		if(sormax[i]==0)
		{
			printf("A mátrix szinguláris!\n");
			exit(1);
		}

		//normálás
		for(j=0;j<n;j++)
		{
			p[n*i+j]=p[n*i+j]/sormax[i];
		}

		//inverz normálása
		inv[i*n+i]=1/sormax[i];	
	}

//Invertálás
	
	//oszloponként haladva (i mindig sor, j mindig oszlop!, csak ugye ezek 0-tól mennek, nem 1-től!)
	for(j=0;j<n;j++)
	{
		//numerikus hibák minimalizálása miatt olyan sor keresése, amiben maximális a j.edik elem. persze csak j.edik sortól keresve!
		max=0;
		holmax=0;		
		for(i=j;i<n;i++)
		{
			if (max<p[n*i+j])
			{
				max=p[n*i+j];
				holmax=i;
			}
		}
		
		//sorcserék mindkét mátrixban	
		for(j1=0;j1<n;j1++)
		{
			ideig[j1]=p[n*j+j1]; //itt j sorindex, mert átlós elemekből kiindulva eliminálunk.
			ideiginv[j1]=inv[n*j+j1];
		}
		
		for(j1=0;j1<n;j1++)
		{
			p[n*j+j1]=p[n*holmax+j1]; 
			inv[n*j+j1]=inv[n*holmax+j1]; 
		}
		
		for(j1=0;j1<n;j1++)
		{
			p[n*holmax+j1]=ideig[j1]; 
			inv[n*holmax+j1]=ideiginv[j1]; 
		}
		
		//A j. sor normálása mindkét mátrixra, az átlóbeli elemmel.

		a=p[n*j+j];

		for(j1=0;j1<n;j1++)
		{
			p[n*j+j1]=p[n*j+j1]/a;
			inv[n*j+j1]=inv[n*j+j1]/a;
		}
		
		//j. oszlopok lenullázása
	
		for(i=0;i<n;i++)
		{
			a=p[n*i+j];

			if(i!=j)
			{
				for(j1=0;j1<n;j1++)
				{
					p[n*i+j1]=p[n*i+j1]-a*p[n*j+j1];// j sorindex most is!
					inv[n*i+j1]=inv[n*i+j1]-a*inv[n*j+j1];
				}
			}
		}			
	}	
	
	//////////////////////////////////////////////////////////////////
	//until now!
	
	//Now i turn old C-style matrix to new fancy matrix class and return it
	Matrix<T,d> invMat = Matrix<T,d>();
	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++){
			invMat.set(i,j,inv[i*n+j]);
			}
		}
	return invMat;
}


/* Non member stuff */
///////////////////////////////////////////////////////
/*
	diad multiplication
*/
template<typename T,size_t d> 
Matrix<T,d> diad(const Vector<T,d>& lVec,const Vector<T,d>& rVec){
	Matrix<T,d> result=Matrix<T,d>();
	for(int j=0;j<d;j++){
		for(int i=0;i<d;i++){
			result.set(i,j,lVec.get(i)*rVec.get(j));
			}
		}
	return result;
	}

/*
	matrix addition method
*/
template<typename T,size_t d> 
Matrix<T,d> operator+(Matrix<T,d> lMat, const Matrix<T,d>& rMat){
	Matrix<T,d> sumMat=Matrix<T,d>();
	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++){
			sumMat.set(i,j,lMat.get(i,j)+rMat.get(i,j));
			}
		}
	return sumMat;
	}

/*
	left scalar multiplication method
*/
template<typename T,size_t d> 
Matrix<T,d> operator*(T scalar, const Matrix<T,d>& rMat){
	Matrix<T,d> sumMat=Matrix<T,d>();
	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++){
			sumMat.set(i,j,scalar*rMat.get(i,j));
			}
		}
	return sumMat;
	}

/*
	matrix substraction method
*/
template<typename T,size_t d> 
Matrix<T,d> operator-(Matrix<T,d> lMat, const Matrix<T,d>& rMat){
	return lMat+(-1.0*rMat);
	}

/*
	right scalar multiplication method
*/
template<typename T,size_t d> 
Matrix<T,d> operator*( const Matrix<T,d>& lMat, T scalar){
	return scalar*lMat;
	}

/*
	right scalar division method
	!!note there is no left scalar method
*/
template<typename T,size_t d> 
Matrix<T,d> operator/( const Matrix<T,d>& lMat, T scalar){
	return (1.0/scalar)*lMat;
	}
	
/*
	matrix multiplication method
*/
template<typename T,size_t d> 
Matrix<T,d> operator*( Matrix<T,d> lMat,const Matrix<T,d>& rMat ){
	Matrix<T,d> mulMat=Matrix<T,d>();
	T temp;
	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++){
			temp=0;
			for(int k=0;k<d;k++){
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
template<typename T,size_t d> 
Vector<T,d> operator*(const Matrix<T,d>& lMat,const Vector<T,d>& rVec ){
	Vector<T,d> result=Vector<T,d>();
	T temp;
	for(int i=0;i<d;i++){
		temp=0;
		for(int j=0;j<d;j++){
			temp+=lMat.get(i,j)*rVec.get(j);
			}
		result.set(i,temp);
		}
	return result;
	}


/*
	Vector multiplication v*M 
*/
template<typename T,size_t d> 
Vector<T,d> operator*(const Vector<T,d>& lVec,const Matrix<T,d>& rMat){
	Vector<T,d> result=Vector<T,d>();
	T temp;
	for(int j=0;j<d;j++){
		temp=0;
		for(int i=0;i<d;i++){
			temp+=rMat.get(i,j)*lVec.get(j);
			}
		result.set(j,temp);
		}
	return result;
	}





#endif
