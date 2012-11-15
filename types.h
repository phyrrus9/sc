/* The Simple C programming language. Copygight © 2012 the contributors
 * The Simple C (SC) programming language, is a basic attempt at making
 * an easy to learn language with powerful capabilities. This language
 * will translate to c++ code and then call the native c++ compiler on
 * your machine. Each individual file should have a block to explain
 * what the code in that file is used for.
 * This code is open source under the GPL version 3 lisence (look it up)
 * Contributors:
 * Ethan Laur (phyrrus9) © 2012
 * types.h
 * Definitions for custom sc data types.
 */
#include <cstring>
class scstr
{
private:
	char *str;
public:
	int size;
	scstr(int in);
	void set(const char *in);
	char *get(void);
};
