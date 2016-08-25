/* gf.c 
 * Yang Yuwang, Zhao Wei, Wang Lei 
 * June, 2012

Fast Galois Field Arithmetic in C/C++
Copright (C) 2012 Yang Yuwang, Zhao Wei, Wang Lei 

These files are free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

These files are distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

Yang Yuwang, Zhao Wei, Wang Lei 
Department of Computer Science
Nanjing University of Science and Technology

yuwangyang@mail.njust.edu.cn
http://www.sensor608.com/gf.html
 */

#include "gf.h"
#include "stdio.h"
#include <stdlib.h> 
#include <malloc.h>

//
GFType gfmul(GFType a, GFType b);
GFType gfdiv(GFType a, GFType b);
//

GFType prim_poly[13] = 
{ 
/*	0 */	0x00000000,
/*  1 */    0x00000001, 
/*  2 */    0x00000007,
/*  3 */    0x0000000b,
/*  4 */    0x00000013,
/*  5 */    0x00000025,
/*  6 */    0x00000043,
/*  7 */    0x00000089,
/*  8 */    0x00000187,
/*  9 */    0x00000211,
/* 10 */    0x00000409,
/* 11 */    0x00000805,
/* 12 */    0x00001053,
 }; 

int gFieldSize;
//
GFType* table_alpha;
GFType* table_index;
GFType** table_mul;
GFType** table_div;

void gf_init(unsigned int m, unsigned int prim)// GF(2^m), primitive polymonial
{
	int i=0,j=0;
	
	if (m > 12)	// the field size is supported from GF(2^1) to GF(2^12). 
		return;

	gFieldSize = 1<<m;

	if (0 == prim)
		prim = prim_poly[m];


	table_alpha = (GFType*)malloc(sizeof(GFType)*gFieldSize);
	table_index = (GFType*)malloc(sizeof(GFType)*gFieldSize);
	table_mul = (GFType**)malloc(sizeof(GFType*)*gFieldSize);
	table_div = (GFType**)malloc(sizeof(GFType*)*gFieldSize);
	for(i=0; i<gFieldSize; i++)
	{
		table_mul[i] = (GFType *)malloc(sizeof(GFType) * gFieldSize);
		table_div[i] = (GFType *)malloc(sizeof(GFType) * gFieldSize);
	}
	

	table_alpha[0]=1;
	table_index[0]=-1;

	for (i=1; i<gFieldSize; i++)
	{
		table_alpha[i] = table_alpha[i-1]<<1;
		if (table_alpha[i]>=gFieldSize)
		{
			table_alpha[i]^=prim;
		}

		table_index[table_alpha[i]]=i;
	}
	
	table_index[1]=0;

	// create the tables of mul and div
	for (i=0; i<gFieldSize; i++)
		for (j=0; j<gFieldSize; j++)
		{
			table_mul[i][j]=gfmul(i,j);
			table_div[i][j]=gfdiv(i,j);

		}


}
void gf_uninit(){
	int i = 0;

	free(table_alpha);
	free(table_index);

	for(i=0; i<gFieldSize; i++)
	{
		free(table_mul[i]);
		free(table_div[i]);
	}
	free(table_mul);
	free(table_div);


}
// show  the contents of the array
void gf_print()
{
	int i;
	for (i=0; i<gFieldSize; i++)
	{
		printf("%d\t %d\t %d\n", i, table_alpha[i], table_index[i]);
	}
}


GFType gfmul(GFType a, GFType b)
{
	if (0==a || 0==b)
		return 0;

	return table_alpha[(table_index[a]+table_index[b])%(gFieldSize-1)];
}

GFType gfdiv(GFType a, GFType b)
{
	if (0==a || 0==b)
		return 0;

	return table_alpha[(table_index[a]-table_index[b]+(gFieldSize-1))%(gFieldSize-1)];
}


GFType gf_exp(GFType a, GFType n)
{
	if (a==0 && n==0)
	{
		return 1;
	}
	if (a==0 && n!=0)
	{
		return 0;
	}
	return table_alpha[table_index[a]*n%(gFieldSize-1)];
}

