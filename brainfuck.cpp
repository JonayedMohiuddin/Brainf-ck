#include <iostream>
using namespace std;

class Reader
{
	public:
	int curPos;
	char curChar;
	string input;
	
	Reader(string input = "")
	{
		this->input = input;
		curPos = 0;
		curChar = input[curPos];
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
	public:
  int memory[1000];
	int pointer;
	Reader reader;
	
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
		while(reader.curChar != '\0')
		{
	  	if(reader.curChar == '<')
	  	{
	  		pointer--;
		  	// cout << "LEFT " << pointer << endl;
	  	}
	  	else if(reader.curChar == '>')
	  	{
		  	pointer++;
		  	// cout << "RIGHT " << pointer << endl;
		  }
		  else if(reader.curChar == '+')
	  	{
		  	memory[pointer]++;
		  	// cout << "PLUS " << to_string(memory[pointer]) << endl;
		  }
		  else if(reader.curChar == '-')
	  	{
		  	memory[pointer]--;
		  	// cout << "MINUS " << to_string(memory[pointer]) << endl;
		  }
		  else if(reader.curChar == '.')
	  	{
		  	cout << "VALUE OF " << pointer << " IS " << to_string(memory[pointer]) << endl;
		  }
		  else if(reader.curChar == ',')
	  	{
	  	  cout << "INPUT : ";
	  		cin >> memory[pointer];
		  }
		  else if(reader.curChar == '[')
	  	{
	  		if(memory[pointer] == 0)
	  		{
	  			while(reader.curChar != ']')
	  			  reader.nextChar();
	  		}
		  }
		  else if(reader.curChar == ']')
	  	{
	  		if(memory[pointer] != 0)
	  		{
	  			while(reader.curChar != '[')
	  			  reader.previousChar();
	  		}
		  }
		  else
		  {
		  	
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
