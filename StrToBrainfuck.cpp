#include <iostream>
#include <fstream>
using namespace std;

/* 
When appending code by this method, this method must be called in a empty memory and another 
empty memory must follow it. If you are overriding this shouldnt be a concern.
Example: if called when pointing to mem[X] then mem[X] and mem[X+1] must be empty.
*/

string toBrainfuck(string str, bool append=false)
{
    string brainfuck;
    char curChar;
    int mul;
    int rem;

    if(!append)
    {
        brainfuck += "$ASCII\n"; 
    }

    brainfuck += "#CURRENTLY PTR AT MEM[X]"; 

    for (int i = 0; i < str.length(); i++)
    {
        curChar = (char)str[i];
        mul = (int)curChar / 10;  // 65(A) -> 6, 72(H) -> 7
        rem = (int)curChar % 10;  // 65(A) -> 5, 72(H) -> 2

        brainfuck += "\n++++++++++[>"; // Boilerplate code: first part of loop. i=10

        // Loops until successfully written char in memory
        for (int i = 0; i < mul; i++)
        {
            brainfuck += "+";
        }

        brainfuck += "<-]>";

        for (int i = 0; i < rem; i++)
        {
            brainfuck += "+";
        }

        brainfuck += ".<    ";
        // Comments
        brainfuck = brainfuck + "#STORE "+to_string((int)str[i])+"(";
        
        if(str[i] != '\n')  // printing \n breaks comments
          brainfuck += str[i];
        
        brainfuck = brainfuck + ") IN MEM[X+1] AND PRINT IT";

        // Clear the memory. So that it can be used later.

        brainfuck += "\n++++++++++[>"; 

        for (int i = 0; i < mul; i++)
        {
            brainfuck += "-";
        }

        brainfuck += "<-]>";

        for (int i = 0; i < rem; i++)
        {
            brainfuck += "-";
        }

        brainfuck += "<     ";
        brainfuck += "#CLEAR MEM[X+1] AND SET PTR AT MEM[X]\n";
    }
    
    return brainfuck;
}

void writeToFile(string text, string filepath="temp.bf", bool append=false)
{
    filepath = "codes/" + filepath;
    ofstream file;
    file.open(filepath);
    file << text;
    file.close();
}

void readFile(string filepath, string *str)
{
  ifstream sourceFile;
	sourceFile.open(filepath);
	if(sourceFile)
	{
	  getline(sourceFile, *str, '\0');
	}
	else
	{
		cout << "~ ! No such file (" + filepath + ") in codes directory. Please add one first! \n";
		cout << "~ ! Exiting now !\n";
		exit(EXIT_FAILURE);
	}
	sourceFile.close();
	*str += '\n';
}

int main(int argc, char const *argv[])
{
    string str, filename, brainfuck;
    cout << "Input String:";
    getline(cin, str, '\n');
    cout << "Input filename(will be stored in codes dir. Default filename is temp.bf):\n";
    getline(cin, filename);
    
    //readFile("codes/NewFile.txt", &str);
    
    brainfuck = toBrainfuck(str);
    
    cout << "\n\n";
    cout << brainfuck;
    cout << "\n\n";
    writeToFile(brainfuck, filename);

    return 0;
}
// 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz
