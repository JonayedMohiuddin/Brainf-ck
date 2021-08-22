#include <iostream>
#include <fstream>
using namespace std;

class Reader
{
private:
	int curPos;
	char curChar;
	string source;
	string filepath;

public:
	Reader()
	{
		source = " ";
		curPos = -1;
		nextChar();
	}

	Reader(string filepath)
	{
		this->filepath = filepath;

		if (filepath == "" || filepath == " " || filepath == "\n")
		{
			this->filepath += "codes/";
			cout << "Enter brainfuck code (or filename adding ~ before it):\n";
			cin >> source;

			if (source[0] == '~')
			{
				this->filepath += source.substr(1, source.length());
				readFile();
			}
		}
		else
		{
			readFile();
		}

		curPos = -1;
		nextChar();
	}

	void readFile()
	{
		ifstream sourceFile;
		sourceFile.open(filepath);
		if (sourceFile)
		{
		  getline(sourceFile, source, '\0');
		}
		else
		{
			cout << "~ ! No such file (" + filepath + ") in codes directory. Please add one first! \n";
			cout << "~ ! Exiting now !\n";
			exit(EXIT_FAILURE);
		}
		sourceFile.close();
		source += '\n';
	}

	char getChar()
	{
		return curChar;
	}

	void nextChar()
	{
		curChar = source[++curPos];
	}

	void previousChar()
	{
		curChar = source[--curPos];
	}
	
	int getCurPos()
	{
		return curPos;
	}

	// $D=Decimal, $A=ASCII, Default: D
	char getOutputMode()
	{
		while (getChar() != '$' && getChar() != '>' && getChar() != '<' && getChar() != '+' && getChar() != '-' && getChar() != '.' && getChar() != ',' && getChar() != '[' && getChar() != ']')
		{
			nextChar();
		}

		if (getChar() == '$')
		{
			nextChar();
			return getChar();
		}
		
		else
		{
			return 'D';
		}
	}
};

// This is the Brainfuck interpreter which runs Brainfuck codes from files or manual input.

class Interpreter
{
private:
	char mem[3000] = {0};
	int memSize; 
	char *ptr;
	char outputMode; // $A = ASCII or $D = DECIMAL
	int loopDepth;   // 0 [ 1 [ 2 [ 3 ] 2 ] 1 ] 0
	Reader reader;

public:
	Interpreter(Reader reader)
	{
		this->reader = reader;; 
		ptr = mem;
		memSize = 3000;
		outputMode = reader.getOutputMode();
		interpret();
	}
	
	void interpret()
	{
		while (reader.getChar() != '\0')
		{
			if (reader.getChar() == '<')
			{
				--ptr;
				if (ptr < mem)
				{
					ptr = &mem[memSize];
				}
			}
			else if (reader.getChar() == '>')
			{
				++ptr;
				if (ptr > &mem[3000])
				{
					ptr = mem;
				}
			}
			else if (reader.getChar() == '+')
			{
				++*ptr;
			}
			else if (reader.getChar() == '-')
			{
				--*ptr;
			}
			else if (reader.getChar() == '.')
			{
				// $D means decimal output, $A means ASCII output
				if (outputMode == 'D')
				{
					cout << "MEM[" << ptr - mem << "] = " << to_string((int)*ptr) << '\n';
				}
				else if (outputMode == 'A')
				{
					cout << *ptr;
				}
			}
			else if (reader.getChar() == ',')
			{
				cout << "Input : ";
				cin >> *ptr;
			}
			// If memory currently pointing at is zero goto next same depths ']'
			else if (reader.getChar() == '[')
			{
				if ((int)*ptr == 0)
				{
					loopDepth = 1;
					reader.nextChar();
					
					while (loopDepth != 0)
					{
						if(reader.getChar() == '[')
							++loopDepth;
						else if(reader.getChar() == ']')
							--loopDepth;
						
						reader.nextChar();
						
						if(!reader.getChar() == '\0') // If EOF
						{
						  cout << "Error no matching closing ']' braces!";
						  exit(EXIT_SUCCESS);
						} 
					} 
				}
			}
			// If memory currently pointing at is non-zero then goto goto next same depths preceding '['
			else if (reader.getChar() == ']')
			{
				if ((int)*ptr != 0)
				{
					loopDepth = 1;
					reader.previousChar();
					
					while (loopDepth != 0) 
					{
						if(reader.getChar() == ']')
							++loopDepth;
						else if(reader.getChar() == '[')
							--loopDepth;
						
						reader.previousChar();
						
						if(reader.getChar() == '\0') // If EOF
						{
						  cout << "Error no matching opening '[' braces!";
						  exit(EXIT_FAILURE);
						} 
					}
				}
			}
			// Just skip comments starting with # (Not a brainfuck directive)
			else if (reader.getChar() == '#')
			{
				while (reader.getChar() != '\n')
					reader.nextChar();
			}
		  
			reader.nextChar();
		}
	}
};

void printHelp()
{
	cout << "=========================\n";
	cout << "= BRAINFUCK INTERPRETER =\n";
	cout << "=========================\n";
	cout << "# This interpreter can directly run codes from your input or filename given.\n";
	cout << "# This interpreter searches for brainfuck files (*.bf) in codes directory.\n";
	cout << "# If inputting filenames it must be followed by a ~ sign.\n";
	cout << "# For inputting code just type it directly.\n";
	cout << "# $ is output mode controller.\n";
	cout << "# Write $ASCII or $A at the start of line for ASCII output.\n";
	cout << "# Write $DECIMAl or $D at the start of line forDECIMAL output.\n";
	cout << "\n";
}

int main(int argc, char *argv[])
{
	string filepath = "codes/";
	if (argc >= 2)
		filepath += argv[1];
	else
	{
	  printHelp();
		filepath = "";
	}

	Reader reader(filepath);
	Interpreter interpreter(reader);
	cout << '\n';

	return 0;
}
