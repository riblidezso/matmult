#include <iostream>
#include "Matrix.h"
#include "Vector.h"

#define BSIZE 50 //for my bay-trail 
//#define BSIZE 100 //for my core i7 

//miminal checker
int main(int argc, char** argv){

//args
	if(argc!=2){
		std::cout<<"Please give matrix size\n"; 	
		return 1;
	}

	int N=atoi(argv[1]);
	std::cout<<"\n"; 
	std::cout<<"Matrix dimension= "<<N<<"\n"; 
	std::cout<<"buffer size= "<<BSIZE<<"\n\n"; 

//contruct matrices
	//empty matrix constructor	
	Matrix<double> myMatrix = Matrix<double>(N);
	Matrix<double> myMatrix2 = Matrix<double>(N);

	myMatrix.randomize();
	myMatrix2.randomize();


//different multiplications
/*
	//matmult naive
	//std::cout<<"Naive matmult\n";
	//Matrix<double> myMatrixN=matMultNaive(myMatrix,myMatrix2);
*/


/*
	//matmult transpon
	//std::cout<<"Naive matmult with transpon\n";
	Matrix<double> myMatrixNB=matMultNaiveTranspon(myMatrix,myMatrix2);

	//equality check
	//std::cout<<"multplication method equality check\nthe results are ";
	std::cout<<(myMatrixNB.equals(myMatrixN) ?  "equal" : "different")<<std::endl;
	std::cout<<"the maximum elementwise difference is  ";
	std::cout<<myMatrixNB.maxDiff(myMatrixN)<<"\n\n";
*/



	//matmult block 
	//std::cout<<"Block matmult\n";
	Matrix<double> myMatrixB=matMultBlock0<BSIZE>(myMatrix,myMatrix2);
/*
	//equality check
	//std::cout<<"multplication method equality check\nthe results are ";
	std::cout<<(myMatrixNB.equals(myMatrixB) ?  "equal" : "different")<<std::endl;
	std::cout<<"the maximum elementwise difference is  ";
	std::cout<<myMatrixNB.maxDiff(myMatrixB)<<"\n\n";

*/


// BLOCK Multithreading test

	//matmult not naive 
	//std::cout<<"BLOCK Multithreaded matmult \n";
	Matrix<double> myMatrixMTB=matMultMultiThreadBlock0<BSIZE>(myMatrix,myMatrix2);

	//equality check
	//std::cout<<"multplication method equality check\nthe results are ";
	std::cout<<(myMatrixB.equals(myMatrixMTB) ?  "equal" : "different")<<std::endl;
	std::cout<<"the maximum elementwise difference is  ";
	std::cout<<myMatrixB.maxDiff(myMatrixB)<<"\n\n";



//Strassen test
	std::cout<<"Strassen matmult\n";
	Matrix<double> myMatrixS=matMultStrassen0<BSIZE>(myMatrix,myMatrix2);

	//equality check
	//std::cout<<"multplication method equality check\nthe results are ";
	std::cout<<(myMatrixB.equals(myMatrixS) ?  "equal" : "different")<<std::endl;
	std::cout<<"the maximum elementwise difference is  ";
	std::cout<<myMatrixB.maxDiff(myMatrixS)<<"\n\n";

	}
