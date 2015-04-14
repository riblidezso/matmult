#ifndef MATRIX_H 
#define MATRIX_H

#include <iostream>
#include <string>
#include <sstream>
#include <initializer_list>
#include <stdlib.h>
#include <stdio.h>
#include <iterator>

#include "Vector.h"

template<typename T> 
class Matrix{
//contructors and destr
public:
	Matrix(size_t ind);//empty constuctor
	Matrix(const T* inputData,size_t ind);//from array
	Matrix(std::initializer_list<std::initializer_list<T> > initVals);
	Matrix(const Matrix<T> &matrixToCopy);//copy constr
	Matrix(Matrix<T>&& matrixToCopy);//move constr
	~Matrix(); //destructor

//data
private:
	T* data;
	size_t d;

//methods	
public:
	void releaseData();
	T* getDataPointer();
	size_t getDim() const ;
	void operator=(const Matrix<T>& matrixToCopy);//copy asssignement
	void operator=(Matrix<T>&& matrixToCopy);//move asssignement
	std::string toString(); //toString

	T get(int i, int j) const;//getters
	Vector<T> getRow(int i);
	Vector<T> getCol(int j);
	void set(int i, int j,T value);//setters
	void setRow(int i, const Vector<T>& inputRow); 
	void setCol(int j, const Vector<T>& inputCol);

	//math stuff
	T trace();
	T det();
	Matrix<T> transpon();
	Matrix<T> gauInv();


/*
	Added forward iterators
	to row, col, and diagional iteration
*/
///////////////////////////////////////////////////////////////////////////
	//iterators
	//rows
	//no need to know about the  dimension of Matrix instance
	//but for symettry reasons it will require it!
	class rowIterator : public std::iterator<std::forward_iterator_tag, int>{
	public:
		typedef rowIterator self_type;
		rowIterator(T* ptr, size_t ind) : ptr_(ptr),d(ind) { }
		self_type operator++() { self_type i = *this; ptr_++; return i; }
		self_type operator++(int junk) { ptr_++; return *this; }
		T& operator*() { return *ptr_; }
		T* operator->() { return ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
	private:
	        T* ptr_;
		size_t d;
        };

	rowIterator rowBegin(int i){
		return rowIterator(data+i*d,d);
		}
	rowIterator rowEnd(int i){
		return rowIterator(data+(i+1)*d,d);
		}

	//cols
	//needs to know the dimension of Matrix instance!!
	class colIterator : public std::iterator<std::forward_iterator_tag, int>{
	public:
		typedef colIterator self_type;
		colIterator(T* ptr, size_t ind) : ptr_(ptr),d(ind) { }
		self_type operator++() { self_type i = *this; ptr_+=d; return i; }
		self_type operator++(int junk) { ptr_+=d; return *this; }
		T& operator*() { return *ptr_; }
		T* operator->() { return ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
	private:
	        T* ptr_;
		size_t d;
        };

	colIterator colBegin(int i){
		return colIterator(data+i,d);
		}
	colIterator colEnd(int i){
		return colIterator(data+i+d*d,d);
		}

	//diag
	//needs to know the dimension of Matrix instance!!
	class diagIterator : public std::iterator<std::forward_iterator_tag, int>{
	public:
		typedef diagIterator self_type;
		diagIterator(T* ptr, size_t ind) : ptr_(ptr),d(ind) { }
		self_type operator++() { self_type i = *this; ptr_+=d+1; return i; }
		self_type operator++(int junk) { ptr_+=d+1; return *this; }
		T& operator*() { return *ptr_; }
		T* operator->() { return ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
	private:
	        T* ptr_;
		size_t d;
        };

	diagIterator diagBegin(){
		return diagIterator(data,d);
		}
	diagIterator diagEnd(){
		return diagIterator(data+d*(d+1),d);
		}

///////////////////////////////////////////////////////////////////////////
};


/*Rest is not modified*/

////////////////////////////////////////////////////////////////////
//Not member

	//diad
	template<typename T> 
	Matrix<T> diad(const Vector<T>& lVec,const Vector<T>& rVec);

	//matrix algebra as non-member operators
	//core
	template<typename T> 
	Matrix<T> operator+(Matrix<T> lMat, const Matrix<T>& rMat);
	template<typename T> 
	Matrix<T> operator*(T scalar, const Matrix<T>& rMat);

	//combinations (rigths, + inverses)
	template<typename T> 
	Matrix<T> operator-(Matrix<T> lMat, const Matrix<T>& rMat);
	template<typename T> 
	Matrix<T> operator*( const Matrix<T>& lMat, T scalar);
	template<typename T> 
	Matrix<T> operator/( const Matrix<T>& lMat, T scalar);

	//matmult
	template<typename T> 
	Matrix<T> operator*( Matrix<T> lMat,const Matrix<T>& rMat );
	
	//vector arithmetics
	template<typename T> 
	Vector<T> operator*(const Vector<T>& lVec,const Matrix<T>& rMat);
	template<typename T> 
	Vector<T> operator*(const Matrix<T>& lMat,const Vector<T>& rVec );
	


////////////////////////////////////////////////////////
/*
	Empty constructor
*/
template<typename T> 
Matrix<T>::Matrix(size_t ind){
	d=ind;
	data = new T[d*d];
	}


/*
	Constructor from array
*/
template<typename T> 
Matrix<T>::Matrix(const T* inputData, size_t ind){
	d=ind;
	data = new T[d*d];
	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++){
			set(i,j,inputData[i*d+j]);
			}
		}
	}

/*
	Constructor from std::initiializer_list 
	row continuous!!!
*/
template<typename T> 
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T> > initVals){
	d=initVals.size();
	data = new T[d*d];
	int i=0;
	for(auto row : initVals){
		int j=0;
		for(auto val : row){
			set(i,j,val);
			j++;
			}
		i++;
		}
	}


/*
	Copy constructor
*/
template<typename T> 
Matrix<T>::Matrix(const Matrix<T> &matrixToCopy){
	d=matrixToCopy.getDim();
	data = new T[d*d];
	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++){
			set(i,j,matrixToCopy.get(i,j));
			}
		}
	}

/*
	Move constructor
*/
template<typename T> 
Matrix<T>::Matrix(Matrix<T>&& matrixToCopy){
	d=matrixToCopy.getDim();
	data=matrixToCopy.getDataPointer();
	matrixToCopy.releaseData();
	}


/*
	Destructor
*/
template<typename T> 
Matrix<T>::~Matrix(){
	delete[] data;
	}

/*
	Release data method
	for move semantic
*/
template<typename T> 
void Matrix<T>::releaseData(){
	data=NULL;
	}

/*
	Release data method
	for move semantic
*/
template<typename T> 
T* Matrix<T>::getDataPointer(){
	return data;
	}

/*
	Assignement operator
*/
template<typename T> 
void Matrix<T>::operator=(const Matrix<T> &matrixToCopy){
	delete[] data;
	d=matrixToCopy.getDim();
	data= new T[d*d];

	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++){
			set(i,j,matrixToCopy.get(i,j));
			}
		}
	}

/*
	Move assignement operator
*/
template<typename T> 
void Matrix<T>::operator=(Matrix<T>&& matrixToCopy){
	delete[] data;
	d=matrixToCopy.getDim();
	data=matrixToCopy.getDataPointer();
	matrixToCopy.releaseData();
	}

/*
	toString method
*/
template<typename T> 
std::string Matrix<T>::toString(){
	std::stringstream sstr;
	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++){
			sstr<<get(i,j)<<"\t";
			}
		sstr<<"\n";
		}
	return sstr.str();
	}

/*
	Get dimension method
*/
template<typename T> 
size_t Matrix<T>::getDim() const {
	return d;
	}



/*
	Get element method
*/
template<typename T> 
T Matrix<T>::get(int i, int j) const {
	return data[i*d+j];
	}

/*
	Get row method
*/
template<typename T> 
Vector<T> Matrix<T>::getRow(int i){
	Vector<T> result=Vector<T>(d);
	for(int j=0;j<d;j++){
		result.set(j,get(i,j));
		}
	return result;
	}

/*
	Get col  method
*/
template<typename T> 
Vector<T> Matrix<T>::getCol(int j){
	Vector<T> result=Vector<T>(d);
	for(int i=0;i<d;i++){
		result.set(i,get(i,j));
		}
	return result;
	}

/*
	Set element method
*/
template<typename T> 
void Matrix<T>::set(int i, int j,T value){
	data[i*d+j]=value;
	}

/*
	Set row method
*/
template<typename T> 
void Matrix<T>::setRow(int i, const Vector<T>& inputRow) {
	for(int j=0;j<d;j++){
		set(i,j,inputRow.get(j));
		}
	}

/*
	Set column method
*/
template<typename T> 
void Matrix<T>::setCol(int j, const Vector<T>& inputRow) {
	for(int i=0;i<d;i++){
		set(i,j,inputRow.get(i));
		}
	}


/*
	trace method
*/
template<typename T> 
T Matrix<T>::trace(){
	T trace=0;
	for(int i=0;i<d;i++){
		trace+=get(i,i);
		}
	return trace;
	}

/*
	transponation method
*/
template<typename T> 
Matrix<T> Matrix<T>::transpon(){
	Matrix<T> mT= Matrix<T>(data,d);
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
template<typename T> 
T Matrix<T>::det(){
	//upper triangulize matrix
	Matrix<T> uMat= Matrix<T>(data,d);
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
template<typename T> 
Matrix<T> Matrix<T>::gauInv(){
	//simplify new matrix class to C-style matrix (p,n)
	int n=d;
	T *p = new T[d*d];
	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++){
			p[n*i+j]=get(i,j);
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
	Matrix<T> invMat = Matrix<T>(inv,d);
	return invMat;
}


/* Non member stuff */
///////////////////////////////////////////////////////
/*
	diad multiplication
*/
template<typename T> 
Matrix<T> diad(const Vector<T>& lVec,const Vector<T>& rVec){
	size_t d=lVec.getDim();
	Matrix<T> result=Matrix<T>(d);
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
template<typename T> 
Matrix<T> operator+(Matrix<T> lMat, const Matrix<T>& rMat){
	size_t d=rMat.getDim();
	Matrix<T> sumMat=Matrix<T>(d);
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
template<typename T> 
Matrix<T> operator*(T scalar, const Matrix<T>& rMat){
	size_t d=rMat.getDim();
	Matrix<T> sumMat=Matrix<T>(d);
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
template<typename T> 
Matrix<T> operator-(Matrix<T> lMat, const Matrix<T>& rMat){
	return lMat+(-1.0*rMat);
	}

/*
	right scalar multiplication method
*/
template<typename T> 
Matrix<T> operator*( const Matrix<T>& lMat, T scalar){
	return scalar*lMat;
	}

/*
	right scalar division method
	!!note there is no left scalar method
*/
template<typename T> 
Matrix<T> operator/( const Matrix<T>& lMat, T scalar){
	return (1.0/scalar)*lMat;
	}
	
/*
	matrix multiplication method
*/
template<typename T> 
Matrix<T> operator*( Matrix<T> lMat,const Matrix<T>& rMat ){
	size_t d=lMat.getDim();
	Matrix<T> mulMat=Matrix<T>(d);
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
template<typename T> 
Vector<T> operator*(const Matrix<T>& lMat,const Vector<T>& rVec ){
	size_t d=lMat.getDim();
	Vector<T> result=Vector<T>(d);
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
template<typename T> 
Vector<T> operator*(const Vector<T>& lVec,const Matrix<T>& rMat){
	size_t d=rMat.getDim();
	Vector<T> result=Vector<T>(d);
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
