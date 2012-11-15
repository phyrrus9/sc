/* The Simple C programming language. Copygight © 2012 the contributors
 * The Simple C (SC) programming language, is a basic attempt at making
 * an easy to learn language with powerful capabilities. This language
 * will translate to c++ code and then call the native c++ compiler on
 * your machine. Each individual file should have a block to explain
 * what the code in that file is used for.
 * This code is open source under the GPL version 3 lisence (look it up)
 * Contributors:
 * Ethan Laur (phyrrus9) © 2012
 * error.c
 * This small program will run through the g++ generated output and then
 * compile a set of error messages on the screen that are readable by the
 * user. Not much here.
 */
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
int main(int argc, char * * argv)
{
    FILE *errorf;
    char a[75];
    if (argc < 2)
    {
        printf("Error! Please provide error file");
    }
    errorf = fopen(argv[1], "r");
    if (errorf == NULL)
        return 0;
    while (fgets(a, sizeof(a), errorf))
    {
        if (strstr(a, "error: ‘start’ was not declared in this scope") != NULL)
            printf("Error! No start function defined in program\n");
	if (strstr(a, "conflicting declaration") != NULL)
	    printf("Error! Variable declaration conflict\n");
    }
}
