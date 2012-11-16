/* The Simple C programming language. Copygight © 2012 the contributors
 * The Simple C (SC) programming language, is a basic attempt at making
 * an easy to learn language with powerful capabilities. This language
 * will translate to c++ code and then call the native c++ compiler on
 * your machine. Each individual file should have a block to explain
 * what the code in that file is used for.
 * This code is open source under the GPL version 3 lisence (look it up)
 * Contributors:
 * Ethan Laur (phyrrus9) © 2012
 * parse.cpp
 * The parser is responsible for translating sc into c++ code. Most of
 * what you actually see here is the language itself. This interprets
 * what the user types in (using any text editor, like phyrrus9's td)
 * and puts it into whatever file is passed to it (or out.cpp if none)
 */
#include <stdio.h>
#include <cstring>
#include <cstdlib>
enum type { STRING, INTEGER, CHARACTER };
typedef struct
{
    char *name;
    type t;
    int size;
} variable;
void initstrarray(char * * array, int elements, int width)
{
    array = new char*[elements];
    for(int i = 0; i < 5; ++i)
        array[i] = new char[30];
}
void tab(FILE *of, int tabbing)
{
    for (int i = 0; i < tabbing; i++)
    {
        fprintf(of, "\t");
    }
}
void parse(FILE *inf, FILE *of)
{
    if (inf == NULL)
        return;
    char *opcode = new char[30];
    char *second_param = new char[50];
    char* third_param = new char[40];
    char** functions;
    int function_number = 0;
    bool code = false;
    int tabbing = 0;
    variable *variable_list;
    //initstrarray(list, 5, 30);
    initstrarray(functions, 2, 30);
    //print includes
    fprintf(of, "#include <iostream>\n#include <cstdio>\n#include <string.h>\n#include <cstring>\n#include \"types.h\"\nusing namespace std;\n");
    while (fscanf(inf, "%s", opcode) != EOF)
    {
        //printf("op: %s\n", opcode);
#define opc(a) if (strcmp(opcode, a) == 0)
#define sif(a,b) if (strcmp(a,b) == 0)
#define nsif(a,b) if (strcmp(a,b) != 0)
#define rp(a) fscanf(inf, " : %s", a)
        if (strcmp(opcode, "->include") == 0 && !code)
        {
            FILE *iof;
            iof = fopen(".includes", "w");
            rp(second_param);
            FILE *inc;
            inc = fopen(second_param, "r");
            if (inc != NULL)
            {
                char ic;
                while (fscanf(inc, "%c", &ic) != EOF)
                {
                    fprintf(iof, "%c", ic);
                }
            }
            //parse(inc, of);
            continue;
        }
        code = true;
        opc(".")
        {
            continue;
        }
        opc("funcdef")
        {
            rp(second_param);
            rp(third_param);
            sif(third_param, "none")
                fprintf(of, "void %s(); //function prototype\n", second_param);
            continue;
        }
        //if : type : param1 : op : param2
        //code
        //endif
        opc("if")
        {
            tabbing++;
            tab(of, tabbing);
            char *fourth_param = new char[4];
            char *fifth_param = new char[30];
            rp(second_param); //type
            rp(third_param); //var name 1
            rp(fourth_param); //op
            rp(fifth_param); //var name 2
            sif(second_param, "string") //strings are always =
            {
                sif(fourth_param, "=")
                {
                    fprintf(of, "if (strcmp(%s.get(), %s.get()) == 0)\n", third_param, fifth_param);
                }
                else
                {
                    fprintf(of, "if (strcmp(%s.get(), %s.get()) != 0)\n", third_param, fifth_param);
                }
                tab(of, tabbing);
                fprintf(of, "{\n");
            }
            if (strcmp(second_param, "integer") == 0 || strcmp(second_param, "character") == 0)
            {
                char *op = new char[4];
                sif(fourth_param, "=")
                {
                    strcpy(op, "==");
                }
                else
                {
                    strcpy(op, fourth_param);
                }
                fprintf(of, "if (%s %s %s) //autogen if statement\n", third_param, op, fifth_param);
                tab(of, tabbing);
                fprintf(of, "{\n");
                delete[] op;
            }
            delete[] fourth_param;
            delete[] fifth_param;
        }
        opc("endif")
        {
            //tabbing--;
            tab(of, tabbing);
            fprintf(of, "}\n");
            tabbing--;
        }
        opc("adds")
        {
            rp(second_param); //var1
            rp(third_param); //str
            int len = strlen(third_param);
            for (int i = 0; i < len; i++)
            {
                if (third_param[i] == '~')
                {
                    if (third_param[i + 1] == 'n')
                    {
                        third_param[i] = '\\';
                        third_param[i + 1] = 'n';
                    }
                    else
                    {
                        third_param[i] = ' ';
                    }
                }
            }
            fprintf(of, "char *addstmp = new char[%s.size + strlen(\"%s\") + 5];\n", second_param, third_param);
            fprintf(of, "strcpy(addstmp, %s.get());\n", second_param);
            fprintf(of, "strcat(addstmp, \"%s\"); //add string opcode\n", third_param);
            fprintf(of, "%s.set(addstmp);\n", second_param);
            fprintf(of, "delete[] addstmp;\n");
            continue;
        }
        opc("addsvar")
        {
            rp(second_param); //var1
            rp(third_param); //var2
            fprintf(of, "char *addstmp = new char[%s.size + strlen(%s.get()) + 5];\n", second_param, third_param);
            fprintf(of, "strcpy(addstmp, %s.get());\n", second_param);
            fprintf(of, "strcat(addstmp, %s.get()); //add string opcode\n", third_param);
            fprintf(of, "%s.set(addstmp);\n", second_param);
            fprintf(of, "delete[] addstmp;\n");
        }
        opc("add")
        {
            rp(second_param); //var1
            rp(third_param); //var2
            fprintf(of, "%s += %s; //add opcode\n", second_param, third_param);
        }
        opc("subtract")
        {
            rp(second_param); //var1
            rp(third_param); //var2
            fprintf(of, "%s -= %s; //sub opcode\n", second_param, third_param);
        }
        opc("multiply")
        {
            rp(second_param); //var1
            rp(third_param); //var2
            fprintf(of, "%s += %s; //mul opcode\n", second_param, third_param);
        }
        opc("divide")
        {
            rp(second_param); //var1
            rp(third_param); //var2
            fprintf(of, "%s /= %s; //div opcode\n", second_param, third_param);
        }
        opc("modulus")
        {
            rp(second_param); //var1
            rp(third_param); //var2
            fprintf(of, "%s %%= %s; //mod opcode\n", second_param, third_param);
        }
        opc("call")
        {
            rp(second_param);
                fprintf(of, "%s(); //function call to %s\n", second_param, second_param);
        }
        opc("var")
        {
            bool string = false;
            rp(second_param);
            rp(third_param);
            sif(second_param, "string")
            {
                char *vname = new char[30];
                rp(vname);
                fprintf(of, "scstr %s(%d); //string variable\n", third_param, atoi(vname));
                string = true;
                continue;
            }
            sif(second_param, "integer")
            {
                fprintf(of, "int %s; //integeral variable\n", third_param);
                continue;
            }
            sif(second_param, "character")
            {
                fprintf(of, "char %s; //character variable\n", third_param);
                continue;
            }
        }
        opc("set")
        {
            char *value = new char[40];
            rp(second_param); //name
            rp(third_param); //type
            rp(value); //value
            sif(third_param, "string")
            {
                int len = strlen(value);
                for (int i = 0; i < len; i++)
                {
                    if (value[i] == '~')
                    {
                        if (value[i + 1] == 'n')
                        {
                            value[i] = '\\';
                            value[i + 1] = 'n';
                        }
                        else
                        {
                            value[i] = ' ';
                        }
                    }
                }
                fprintf(of, "%s.set(\"%s\"); //set string variable \n", second_param, value);
            }
            sif(third_param, "integer")
            {
                fprintf(of, "%s = %d; //set an integer\n", second_param, atoi(value));
            }
            sif(third_param, "character")
            {
                fprintf(of, "%s = '%c'; //set character variable\n", second_param, value[0]);
            }
            continue;
        }
        opc("function")
        {
            rp(second_param);
            rp(third_param);
            sif(third_param, "none")
                fprintf(of, "void %s() {\n", second_param);
            fprintf(of, "/**************begin function %s*************/\n", second_param);
            //strcpy(functions[function_number], second_param);
        }
        opc("print")
        {
            rp(second_param);
            int len = strlen(second_param);
            for (int i = 0; i < len; i++)
            {
                if (second_param[i] == '~')
                {
                    if (second_param[i + 1] == 'n')
                    {
                        second_param[i] = '\\';
                        second_param[i + 1] = 'n';
                    }
                    else
                    {
                        second_param[i] = ' ';
                    }
                }
            }
            fprintf(of, "printf(\"%s\"); //print text to screen \n", second_param);
        }
        opc("prints") //print string variable
        {
            rp(second_param);
            fprintf(of, "printf(\"%%s\", %s.get()); //print a string variable \n", second_param);
        }
        opc("printi")
        {
            rp(second_param);
            fprintf(of, "printf(\"%%d\", %s);//printi\n",second_param);
        }
        opc("printc")
        {
            rp(second_param);
            fprintf(of, "printf(\"%%c\", %s);//printc\n",second_param);
        }
        opc("end")
        {
            rp(second_param);
            fprintf(of, "/**************end function %s*************/\n}\n", second_param);
            /*for (int i = 0; i < function_number; i++)
            {
                sif(functions[i], second_param)
                {
                    fprintf(of, "\n//end function %s\n}\n", second_param);
                }
            }*/
        }
    }
}

int main(int argc, char * * argv)
{
    if (argc < 2)
    {
        printf("Error! No input files!\n");
        exit(-1);
    }
    char filename[15];
    char outfile[15];
    strcpy(filename, argv[1]);
    strcpy(outfile, "out.cpp");
    if (argc > 2)
    {
        strcpy(outfile, argv[2]);
    }
    FILE *inf;
    FILE *of;
    inf = fopen(filename, "r");
    of = fopen(outfile, "w");
    parse(inf, of);
    fclose(inf);
    fprintf(of,
            "int main(int argc, char * * argv)\n"
            "{\n"
            "\tstart();\n"
            "\treturn 0;\n"
            "}\n");
    fclose(of);
}