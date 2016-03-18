// test for module [Net]
// t_net.cpp
#include "net.hpp"
#include <cmath>

const int DIV_NUM = 360; 
const double PI = 3.1415926535897932384626;

int main()
{
	Net net1;
	double x[DIV_NUM];
	for(int i=0; i<DIV_NUM; i++)
		x[i] = sin(1.0*i*PI/DIV_NUM);
	net1.drive(x, DIV_NUM);
	return 0;
}

