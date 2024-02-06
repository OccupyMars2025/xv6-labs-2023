/*
https://blogs.oracle.com/linux/post/the-ksplice-pointer-challenge
*/


#include <stdio.h>  
int main() {
 int x[5];
 printf("%p\n", x);    // addr1
 printf("%p\n", x+1);  // addr1 + 4
 printf("%p\n", &x);   // addr1
 printf("%p\n", &x+1); // addr1 + 20
 return 0;
}