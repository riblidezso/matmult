#include <iostream>
#include "Matrix.h"
#include "Vector.h"

//miminal checker
int main(){

	//empty constructor	
	std::cout<<"empty constr\n"; //print it
	Matrix<double> myMatrix = Matrix<double>(3);
	std::cout<<myMatrix.toString()<<"\n"; //print it

	//init list constr
	std::cout<<"std::initializer_list constr\n"; //print it
	Matrix<double> myMatrix2 = {{1,2,9},{0,5,6},{7,3,9}};
	std::cout<<myMatrix2.toString()<<"\n"; //print it


	//copy constr
	std::cout<<"copy constr\n"; //print it
	Matrix<double> myMatrix3 = Matrix<double>(myMatrix2);
	std::cout<<myMatrix3.toString()<<"\n"; //print it

	//assignement
	std::cout<<"assignement\n"; //print it
	myMatrix3=myMatrix;
	std::cout<<myMatrix3.toString()<<"\n"; //print it

	//minimal vector
	std::cout<<"template vector\n"; //print it
	Vector<double> myVec = Vector<double>(3);	
	std::cout<<myVec.toString()<<"\n\n"; //print it

	//getRow
	std::cout<<"getRow\n"; //print it
	myVec = myMatrix2.getRow(0);	
	std::cout<<myVec.toString()<<"\n\n"; //print it
	
	//getCol
	std::cout<<"getCol\n"; //print it
	myVec = myMatrix2.getCol(0);	
	std::cout<<myVec.toString()<<"\n\n"; //print it

	//setRow
	std::cout<<"setRow\n"; //print it
	myMatrix.setRow(0,myVec);	
	std::cout<<myMatrix.toString()<<"\n\n"; //print it
	
	//setCol
	std::cout<<"setCol\n"; //print it
	myMatrix.setCol(0,myVec);	
	std::cout<<myMatrix.toString()<<"\n\n"; //print it

	//trace
	std::cout<<"trace = "<<myMatrix.trace()<<"\n\n"; //print it


	//traspon
	std::cout<<"transpon\n"; //print it
	std::cout<<myMatrix2.toString()<<"\n\n"; //print it
	std::cout<<myMatrix2.transpon().toString()<<"\n\n"; //print it

	//gauss invert
	std::cout<<"invert with gauss elimination\n"; //print it
	std::cout<<myMatrix2.gauInv().toString()<<"\n\n"; //print it
	
	//det
	std::cout<<"det= "<<myMatrix2.det()<<"\n\n"; //print it

	//diad
	std::cout<<"\ndiad:\n";//print it 
	std::cout<<diad(myVec,myVec).toString()<<"\n";//print it

	//arithm
	std::cout<<"full arithmetic\n"; //print it
	std::cout<<(((9.0*(myMatrix2*2.0)*myMatrix2.gauInv()))/2.0+(myMatrix2-myMatrix)).toString()<<"\n";//print it
	
	//vector arithmetic
	std::cout<<"vector multip:\n";//print it 
	std::cout<<(myMatrix2*myVec).toString()<<"\n";//print it
	std::cout<<(myVec*myMatrix2).toString()<<"\n";//print it


	}

