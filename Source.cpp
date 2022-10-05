/*
Project: Program 2
Names: Emmanuel and Peter
Date: 5/11/2022
Description: Uses either postfix or infix for a users equation with numbers less then 10.
			 Validates the data, if it is valid it returns the output in postfix form, or just the value.
*/



#include <iostream>
#include <iomanip>
#include <string>
#include <iomanip>
#include "Stack.h"
using namespace std;
bool isOperator(char userIndex); // Done with this function 
bool isBalanced(string userEquation);  // Done with this function 
bool isOperand(char userIndex); // This needs help somewhat
string toPostfix(string userEquation);
int compute(char _Opeator, int a, int b);
int evalPostfix(string userEquation);
int priority(char);
int main() {
	string userGuess;
	Stack<char> Infix;
	string userEquation;
	char stringIndex;
	bool balanced = false;

	//Runs the main program until the user presses q to quit the program
	do {
		cout << "\nPlease enter the option you would like to Enter: " << endl;
		cout << "(Q)uit " << endl;
		cout << "(I)nfix Equation " << endl;
		cout << "(P)ostfix Equation" << endl;
		getline(cin, userGuess);

		if (userGuess == "P") {
			//Calls algorithm for Postfix to compute and return userEquation
			cout << "Please enter your equation." << endl;
			getline(cin, userEquation);
			balanced = isBalanced(userEquation);
			cout << "Your answer is: ";
			cout << evalPostfix(userEquation) << endl;

			//If equation is infix, converts to postfix and checks balance, else gives error  
		}
		else if (userGuess == "I") {
			//Asks user for information, and returns the value if valid and an error message if it isn't (expected to be in Infix form)
			cout << "Please enter your equation." << endl;
			getline(cin, userEquation);
			balanced = isBalanced(userEquation);
			while (balanced != true) {
				cout << "Please enter a balanced equation. " << endl;
				getline(cin, userEquation);
				balanced = isBalanced(userEquation);
			}

			string newPostFix = toPostfix(userEquation);
			cout << "Your answer is : ";
			cout << evalPostfix(newPostFix) << endl;


		}
	

	} while (userGuess != "Q");

	return 0;
}
bool isOperator(char userIndex) {
	//Bool to check if the operator for the equation is a possible character
	if ((userIndex == '+') || (userIndex == '/') || (userIndex == '*') || (userIndex == '-')) {
		return true;
	}
	else {
		return false;
	}
}

//Function to check if the amount of parantheses is balanced
bool isBalanced(string userEquation) {
	int num = 0;
	bool balanced;
	int indexNum;
	for (int i = 0; i < userEquation.length(); ++i) {
		//Looping function until it reaches the end of the equation, and if end parenthesis comes before open parenthesis its imbalanced
		if (userEquation.at(i) == ')') {
			for (int j = 0; j < userEquation.length(); ++j) {
				if (userEquation.at(j) == '(') {

					//If it finds that a close paranthesis is before an open on, or one is broken, it will return not balanced
					if (j > i) {
						return false;
					}
				}
			}
			num += 1;
		}
		else if (userEquation.at(i) == '(') {
			num -= 1;
		}
	}
	if (num == 0) {
		return true;
	}
	else {
		return false;
	}
}


bool isOperand(char userIndex) {
	//Checks if a character is a numeric operator
	if ((userIndex == '0') || (userIndex == '1') || (userIndex == '2') || (userIndex == '3') || (userIndex == '4') || (userIndex == '5') || (userIndex == '6') || (userIndex == '7') || (userIndex == '8') || (userIndex == '9')) {
		return true;
	}
	else {
		return false;
	}
}

int compute(char _Operator, int a, int b) {
	//Computer function for mathematical formulas in Postfix/Infix
	int c;
	if (_Operator == '+') {
		c = a + b;
	}
	else if (_Operator == '-') {
		c = a - b;

	}
	else if (_Operator == '/') {
		c = a / b;
	}
	else if (_Operator == '*') {
		c = a * b;
	}
	return c;
}
//Computes the values of the userEquation in a postfix equation
int evalPostfix(string userEquation) {
	char stringIndex;
	bool computable = false;
	bool validation = false;
	Stack<int> functionStack;
	char _Opeator;
	int result = 0;
	int charToNum; // gets the conversion from char to int 
	int num1;
	int num2; // the 2 numbers popped from the stack
	int num = 0;

	//Checks if the user has valid data and then pops, computes and returns the result
	for (int i = 0; i < userEquation.length(); ++i) {
		stringIndex = userEquation.at(i);
		computable = isOperator(stringIndex);

		//Uses ASCII values to determine if the operator is valid, if it is, pushes it back onto the stack
		validation = isOperand(stringIndex);
		if (validation == true) {
			charToNum = stringIndex - 48;
			functionStack.push(charToNum);
		}

		//If the numbers are proven to be computable it computes and pushes the function on the stack
		if (computable == true) {
			num2 = functionStack.pop();
			num1 = functionStack.pop();
			result = compute(stringIndex, num1, num2);
			functionStack.push(result);
		}
	}
	result = functionStack.pop();
	return result;
}

//Passed an Infix expression and returns the postfix equivalent
string toPostfix(string userEquation) {
	int length = userEquation.size();
	string postFix;
	bool validNum;
	bool validOperator;
	char stringIndex;
	char temp; //Add pop from stack
	char tempPop2; //Second pop from stack
	Stack<char> newString;
	newString.push('#');
	for (int i = 0; i < length; ++i) {
		//Repeats until there is nothing else to compute, checks if number or operator
		validNum = isOperand(userEquation.at(i));
		stringIndex = userEquation.at(i);
		validOperator = isOperator(stringIndex);
		if (validNum == true) {
			postFix.append(1, stringIndex);
		}
		else if (stringIndex == '(') {
			newString.push(stringIndex);
		}
		if (validOperator == true) { // checks operator
			temp = newString.pop();
			if (temp == '(') {

				newString.push('(');
				newString.push(stringIndex);

			}
			else {
				//Checks if operator has higher priority then char, then pushes both onto the stack
				if (priority(stringIndex) > priority(temp)) {
					newString.push(temp);
					newString.push(stringIndex);
				}
				else {
					//Checks if priority of char is greater or equal to the operator, appends it to postfix and pops the next char from the stack
					while (priority(temp) >= priority(stringIndex)) {
						postFix.append(1, temp);

						temp = newString.pop();
					}
					newString.push(temp);
					newString.push(stringIndex);
				}
			}
		}

		if (userEquation.at(i) == ')') {
			tempPop2 = newString.pop();

			while (tempPop2 != '(') {
				postFix.append(1, tempPop2);
				tempPop2 = newString.pop();
			}
		}
	}
	//Pops any operator and stops at numbers
	char tempPop3 = newString.pop();  // step 6 
	while (tempPop3 != '#') {
		postFix.append(1, tempPop3);
		tempPop3 = newString.pop();
	}
	return postFix;

}

//Function to have mathematical priority given to multiplication and division
int priority(char stringIndex) {
	int result;
	if ((stringIndex == '*') || (stringIndex == '/')) {
		result = 3;
	}
	else if ((stringIndex == '+') || (stringIndex == '-')) {
		result = 2;
	}
	else {
		result = 1;
	}
	return result;
}