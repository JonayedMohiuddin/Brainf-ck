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
		
    if(filepath == "" || filepath == " " || filepath == "\n")
		{
			this->filepath += "codes/";
    	cout << "Enter brainfuck code (or filename adding ~ before it):\n";
    	cin >> source;
    	
    	if(source[0] == '~')
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
    if(sourceFile)
    {
      getline(sourceFile, source, '\0');
    }
    else
    {
      cout << "~ ! No such file ("+filepath+") in codes directory. Please add one first! " << endl;
      cout << "~ ! Exiting now !" << endl;
      exit(EXIT_FAILURE);
    }
    sourceFile.close();
    
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!
    // ! BUG     								 !
    // ! Try running hello.bf    !
    // ! Reads ascii of % as 239 !
    // ! Reads A as 187					 !
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!
    cout<<"\nSource:"<<source << endl;
    cout<<(int)source[0] << endl;
    cout<<(int)source[1] << endl;
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
	
	// D=Decimal, A=ASCII, Default: D
	char getOutputMode()
	{
		if(getChar() == '$')
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

class Interpreter
{
	private:
  int memory[1000];
	int pointer;
	Reader reader;
	char outputMode;
	
	public:
	Interpreter(Reader reader)
	{
		this->reader = reader;
		pointer = 0;
		resetMem();
		outputMode = reader.getOutputMode();
		interpret();
	}
	
	void resetMem()
	{
		for(int i = 0; i <= 1000; i++)
		  memory[i] = 0;
	}
	
	// Brainfuck memory cells are 8bit or 1byte width so they cant be 
	// bigger or lesser than that.
	int convertToByte()
	{
		if(memory[pointer] > 127)
		  return memory[pointer] = 127;
	  else if(memory[pointer] < 0)
		  return memory[pointer] = 0;
	  
	  return memory[pointer];
	}
	
	void interpret()
	{
		while(reader.getChar() != '\0')
		{
	  	if(reader.getChar() == '<')
	  	{
	  		pointer--;
	  		memory[pointer] = convertToByte();
	  	}
	  	else if(reader.getChar() == '>')
	  	{
		  	pointer++;
		  	memory[pointer] = convertToByte();
		  }
		  else if(reader.getChar() == '+')
	  	{
		  	memory[pointer]++;
		  	memory[pointer] = convertToByte();
		  }
		  else if(reader.getChar() == '-')
	  	{
		  	memory[pointer]--;
		  	memory[pointer] = convertToByte();
		  }
		  else if(reader.getChar() == '.')
	  	{
	  		// %D means decimal output, %A means ASCII output
	  		if(outputMode == 'D')
		  	{
		  	  cout << "VALUE OF " << pointer << " IS " << to_string(memory[pointer]) << endl;
		  	}
		  	else if(outputMode == 'A')
		  	{
		  		char output = (char)memory[pointer];
		  		cout << output;
		  	}
		  }
		  else if(reader.getChar() == ',')
	  	{
	  	  cout << "Input : ";
	  		cin >> memory[pointer];
	  		memory[pointer] = convertToByte();
		  }
		  // If memory currently pointing at is zero goto next ]
		  else if(reader.getChar() == '[')
	  	{
	  		if(memory[pointer] == 0)
	  		{
	  			while(reader.getChar() != ']')
	  			  reader.nextChar();
	  		}
		  }
		  // If memory currently pointing at is non-zero then goto preceding [
		  else if(reader.getChar() == ']')
	  	{
	  		if(memory[pointer] != 0)
	  		{
	  			while(reader.getChar() != '[')
	  			  reader.previousChar();
	  		}
		  }
		  else
		  {
		  	// Just do nothing if encountered un-recognised charecters
		  }
		  
		  reader.nextChar();
		}
	}
};

int main(int argc, char *argv[])
{
	string filepath = "codes/";
  if(argc >= 2)
    filepath += argv[1];
  else
    filepath = "";
  
	Reader reader(filepath);
	Interpreter	interpreter(reader);
	
	return 0;
}
