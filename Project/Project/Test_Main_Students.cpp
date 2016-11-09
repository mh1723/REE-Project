#include <stdio.h>
#include <stdlib.h>
void main_Student(int argc, char *argv[]);
char func1(char c);
char func2(char c);
char func3(char c, short n);

void main()
{
	int argc = 3;
	char *argv[3] = {"encrypt", "plaintext.txt", "password"};
	main_Student(argc, argv);
   char a = func1('a');
   char b = func1(a);
   printf("a -> %c -> %c \n", a, b);
   a = func2('a');
   b = func2(a);
   printf("a -> %c -> %c \n", a, b);
   a = func3('a', 1);
   b = func3(a, 0);
   printf("a -> %c -> %c \n", a, b);
}