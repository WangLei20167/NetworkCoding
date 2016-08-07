1 Introduction
This is a fast Galois field library, and all the source files are free software; This labrary has some significant differences compared with previous Galios field labraries.

1)  This labrary can be employed in both Windows plateform and Linux plateform, and both C and C++ are supported.
2)  Compared with previous studies, the codes in this one is very concise, the amount of codes is less than 150 lines which is 1/3-1/5 of previous works.
3)  All the function operations on Galois field are implemented with macro, so the computation speed is very fast.

2 How to use it.
1) Copy the two files (gf.h and gf.c) in your project, and include them in your project.
2) Use the function to initial your field: gf_init(int nOrder, int nPrim) in which the first parameter is the order of Galois field, and the the second parameter is the primitive polynomial. 
For example, gf_init(8, 0x187); The Galois field GF(2^8) is created, and the primitive ploynomial is 0x187.

0x187 = 110000111 (1*X^0+1*X^1+1*X^6+1*X^7+1*X^8+1*X^9)

In the gf.c file, we list some primitive ploynomial.

3) Now, you can use the other functions such as gf_add(a,b), gf_sub(a,b), gf_mul(a,b), gf_div(a,b), gf_neg(a), gf_inv(a). 
gf_neg(a): Return a's complement element b, a+b = 0;
gf_inv(a): Return a's inverse element b, a*b =1;

Notice: This library is based on look-up table. We need to create a 2-dimentional multiplication talbe and a 2-dimentional logarithm table, so the storage overhead is very high when the field size becomes large. When the field size is GF(2^12), 128MBytes are required to store the two tables.

3 If you have any question on this library, you can send e-mail to us.
yuwangyang@mail.njust.edu.cn
http://www.sensor608.com/gf.html
Download url  http://www.sensor608.com/gf.zip
