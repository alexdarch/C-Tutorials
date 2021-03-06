// 7.8_Function_pointers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <functional>

struct arithmeticStruct
{
	char mathOperator;
	std::function<int(int, int)> mathFunction;
};

int getInteger();
char getOperator();
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

static arithmeticStruct arithmeticArray[]{
	{'+',	add			},
	{'-',	subtract	},
	{'*',	multiply	},
	{'/',	divide		}
};


//pass by value where return type is a funtion pointer (probably easier to put typedef as global and then just use arithmeticFcn getArithmeticFcn(char op);
std::function<int(int,int)> getArithmeticFcn(char op)		
{
	for (auto operation : arithmeticArray)
		if (operation.mathOperator == op)
			return operation.mathFunction;

	return add; //default is to return add.
}


int main()
{
	int a = getInteger();
	char op = getOperator();
	int b = getInteger();

	std::function<int(int, int)>operation = getArithmeticFcn(op);
	std::cout << a << ' ' << op << ' ' << b << " = " << operation(a, b) << '\n';


	//Method A: create a typedef for the a function pointer of that "type" (in this case, returns an int and takes two int parameters)
	typedef int(*arithmeticFcnA)(int, int);
	arithmeticFcnA fcnPtrA;
	fcnPtrA = add;
	//the function definition would look like: someFunction(arithmeticFcnA fcn);
	//and we pass arguments normally someFunction(fcnPtrA);


	//Method B: use a type alias
	using arithmeticFcnB = int(*)(int, int);
	arithmeticFcnB fcnPtrB;
	fcnPtrB = add;
	//the function definition would look like: someFunction(arithmeticFcnB fcn);
	//and we pass arguments normally someFunction(fcnPtrB);


	//Method C: Use the standard library std::function. Note that fcnPtr is the same
	std::function<int(int, int)> fcnPtrC;
	fcnPtrC = add;
	//the function definition would look like: someFunction(std::function<int(int,int)> fcn);
	//and we pass arguments normally someFunction(fcnPtrC);


	//Method D: The standard notation.
	int(*fcnPtrD)(int, int) = add;
	//the function definition would look like: someFunction(int (*operation)(int, int));
	//and we pass arguments normally someFunction(add);


	//for all of them we can do things like this:
	//fcnPtrC(3, 5);			//this also works and would give output 8.	
	//when passing a function pointer as an argument, we dont put the arguments in the argument, like calculate(4, 4, add(3, 4))....




    return 0;
}



int getInteger()
{
	int integer;
	bool valid = false;

	do {
		std::cout << "Enter an Integer: ";
		std::cin >> integer;

		if (std::cin.fail())		//deals with overflows and extraneous inputs
		{
			std::cin.clear();
			std::cout << "Not a valid integer.\n";
		}
		else
			valid = true;

		std::cin.ignore(32767, '\n');

	} while (!valid);

	return integer;
}

char getOperator()
{
	char op;
	int count = 0;

	do {
		++count;
		if (count > 1)
			std::cout << "Not a valid operator.\n";	//if weve been through this before then they didnt enter +,-,* or /

		std::cout << "Enter an operation: ";
		std::cin >> op;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "Incorrect data type.\n";
		}

		std::cin.ignore(32767, '\n');


	} while (op != '+' && op != '-' &&  op != '*' && op != '/');

	return op;
}