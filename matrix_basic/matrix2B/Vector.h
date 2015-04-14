#ifndef VECTOR_H 
#define VECTOR_H

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
template<typename T,size_t d>
class Vector{
	//constructors
	public:
	Vector();//zeroes
	
	//data
	private:
	T data[d];

	//methods	
	public:
	T get(int i) const;
	void set(int i,T value);
	void operator=(const Vector<T,d>& VectorToCopy);
	std::string toString(); //toString

	};

/*
	 Zero constructor
*/
template<typename T,size_t d>
Vector<T,d>::Vector(){
	for(int i=0;i<d;i++){
		data[i]=0;
		}
	}
	
/*
	Get element
*/
template<typename T,size_t d>
T Vector<T,d>::get(int i) const{
	return data[i];
	}
	
/*
	Set element
*/
template<typename T,size_t d>
void Vector<T,d>::set(int i,T value){
	data[i]=value;
	}


/*
	Assignement with operator
*/
template<typename T,size_t d>
void Vector<T,d>::operator=(const Vector<T,d>& VectorToCopy){
	for(int i=0;i<d;i++){
		data[i]=VectorToCopy.get(i);
		}
	}

/*
	toString method
*/
template<typename T,size_t d>
std::string Vector<T,d>::toString(){
	std::stringstream sstr;
	for(int i=0;i<d;i++){
		sstr<<data[i]<<"\t";
		}
	return sstr.str();
	}
#endif
