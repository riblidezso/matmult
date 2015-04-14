#include <iostream>

#include "Matrix3.h"
#include "Vector3.h"

int main(){

	//empty constructor	
	Matrix3 myMatrix3 =  Matrix3();
	std::cout<<myMatrix3.toString()<<"\n"; //print it

	//set value	
	myMatrix3.set(1,2,3.14);
	std::cout<<myMatrix3.toString()<<"\n"; //print it

	//array constr
	double elements[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
	Matrix3 my2Matrix3 =  Matrix3(elements);
	std::cout<<my2Matrix3.toString()<<"\n";//print it

	//copy constr
	Matrix3 my3Matrix3 =  Matrix3(my2Matrix3);
	std::cout<<my3Matrix3.toString()<<"\n";//print it

	//get row
	Vector3 myVector3=Vector3();
	myVector3=my3Matrix3.getRow(1);
	std::cout<<"getRow\n";
	std::cout<<myVector3.toString()<<"\n\n";//print it

	//get col 
	std::cout<<"getCol\n";
	myVector3=my3Matrix3.getCol(1);
	std::cout<<myVector3.toString()<<"\n\n";//print it

	//set row 
	std::cout<<"setRow\n";
	my3Matrix3.setRow(0,myVector3);
	std::cout<<my3Matrix3.toString()<<"\n";//print it

	//set col
	std::cout<<"setCol\n";
	my3Matrix3.setCol(0,myVector3);
	std::cout<<my3Matrix3.toString()<<"\n";//print it

	//trace
	std::cout<<"trace = "<<my3Matrix3.trace()<<"\n\n";//print it
	
	//transpon
	my3Matrix3.transpon();
	std::cout<<"transpon:\n";//print it
	std::cout<<my3Matrix3.toString()<<"\n";//print it

	//determinant
	std::cout<<"det = "<<my3Matrix3.det()<<"\n\n";//print it

	//invert
	my3Matrix3.invert();
	std::cout<<"inverse:\n";//print it
	std::cout<<my3Matrix3.toString()<<"\n";//print it

	//add
	Matrix3 my4Matrix3=Matrix3(my2Matrix3);
	std::cout<<"addition:\n";//print it
	std::cout<<my3Matrix3.toString()<<"\n";//print it
	std::cout<<my4Matrix3.toString()<<"\n";//print it
	std::cout<<(my4Matrix3+my3Matrix3).toString()<<"\n";//print it

	//arithmetic
	std::cout<<"full arithmetic:\n";//print it
	std::cout<<(((((1+my3Matrix3*2)*my4Matrix3)-3)-my3Matrix3)/2).toString()<<"\n";//print it

	//vector arithmetic
	std::cout<<"vector multip:\n";//print it 
	std::cout<<(my3Matrix3*myVector3).toString()<<"\n";//print it
	std::cout<<(myVector3*my3Matrix3).toString()<<"\n";//print it

	//diad
	std::cout<<"\ndiad:\n";//print it 
	std::cout<<diad(myVector3,myVector3).toString()<<"\n";//print it
	
	}

