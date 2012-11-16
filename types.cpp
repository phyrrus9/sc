/* The Simple C programming language. Copygight © 2012 the contributors
 * The Simple C (SC) programming language, is a basic attempt at making
 * an easy to learn language with powerful capabilities. This language
 * will translate to c++ code and then call the native c++ compiler on
 * your machine. Each individual file should have a block to explain
 * what the code in that file is used for.
 * This code is open source under the GPL version 3 lisence (look it up)
 * Contributors:
 * Ethan Laur (phyrrus9) © 2012
 * types.cpp
 * Here, all of the needed data type classes live. These are used when
 * the user creates a complex data type. This file will be commented as
 * needed when updates are pushed.
 */
#include "types.h"

scstr::scstr(int in)
{
	size = in;
	str = new char[size];
}

void scstr::set(const char * in)
{
	int length = strlen(in);
	if (length > size)
	{
		size = length;
		char *tmp = new char[length];
		strcpy(tmp, str);
		delete[] str;
		str = tmp;
	}
	strcpy(str, in);
}

char * scstr::get(void)
{
	return str;
}
