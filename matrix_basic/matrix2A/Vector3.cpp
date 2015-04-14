#include "Vector3.h"

/*
	Minimal vector class
*/

/*
	 Zero constructor
*/
Vector3::Vector3(){
	for(int i=0;i<3;i++){
		data[i]=0;
		}
	}
	
/*
	Get element
*/
double Vector3::get(int i) const{
	return data[i];
	}
	
/*
	Set element
*/
void Vector3::set(int i,double value){
	data[i]=value;
	}


/*
	Assignement with operator
*/
void Vector3::operator=(const Vector3& Vector3ToCopy){
	for(int i=0;i<3;i++){
		data[i]=Vector3ToCopy.get(i);
		}
	}

/*
	toString method
*/
std::string Vector3::toString(){
	std::stringstream sstr;
	for(int i=0;i<3;i++){
		sstr<<data[i]<<"\t";
		}
	return sstr.str();
	}
