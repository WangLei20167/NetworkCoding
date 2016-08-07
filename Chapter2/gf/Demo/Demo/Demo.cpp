// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include "gf.c"
using namespace std;


int main()
{
	int a = 7, b = 5;
	gf_init(8, 0x00000187);
	int result;
	result = gf_add(a, b);
	cout << result << endl;
	getchar();
	return 0;
}

