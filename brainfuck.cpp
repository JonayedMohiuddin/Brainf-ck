#include <iostream>
using namespace std;

class Reader
{
	private:
	int curPos;
	char curChar;
	string input;
	
	public:
	Reader(string input = "")
	{
		this->input = input;
		curPos = 0;
		curChar = input[curPos];
	}
  
	char getChar()
	{
		return curChar;
	}
	
	void nextChar()
	{
		curChar = input[++curPos];
	}
	
	void previousChar()
	{
		curChar = input[--curPos];
	}
};

class Interpreter
{
	private:
  int memory[1000];
	int pointer;
	Reader reader;
	
	public:
	Interpreter(Reader reader)
	{
		this->reader = reader;
		pointer = 0;
		resetMem();
		interpret();
	}
	
	void resetMem()
	{
		for(int i = 0; i <= 1000; i++)
		  memory[i] = 0;
	}
	
	void interpret()
	{
		while(reader.getChar() != '\0')
		{
	  	if(reader.getChar() == '<')
	  	{
	  		pointer--;
	  	}
	  	else if(reader.getChar() == '>')
	  	{
		  	pointer++;
		  }
		  else if(reader.getChar() == '+')
	  	{
		  	memory[pointer]++;
		  }
		  else if(reader.getChar() == '-')
	  	{
		  	memory[pointer]--;
		  }
		  else if(reader.getChar() == '.')
	  	{
		  	cout << "VALUE OF " << pointer << " IS " << to_string(memory[pointer]) << endl;
		  }
		  else if(reader.getChar() == ',')
	  	{
	  	  cout << "INPUT : ";
	  		cin >> memory[pointer];
		  }
		  else if(reader.getChar() == '[')
	  	{
	  		if(memory[pointer] == 0)
	  		{
	  			while(reader.getChar() != ']')
	  			  reader.nextChar();
	  		}
		  }
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
		  	// Just skip unknown charecters
		  }
		  
		  reader.nextChar();
		}
	}
};

int main()
{
	string input;
	cout << "INPUT Brainfuck : ";
	cin >> input;
	cout << '\n';
	Reader reader(input);
	Interpreter	interpreter(reader);
	return 0;
}
