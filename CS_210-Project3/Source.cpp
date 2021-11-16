/////////////////////////////
// PROJECT 3 CORNER GROCER
// FRED WAHAB
// CS-210
/////////////////////////////

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

// DISPLAY MENU
void displayMenu() {
	cout << "****************************************" << endl;
	cout << "************DAILY REPORTS***************" << endl;
	cout << "** 1. Products Purchased              **" << endl;
	cout << "** 2. Item Quantity Purchased         **" << endl;
	cout << "** 3. Histogram Report                **" << endl;
	cout << "** 4. Quit                            **" << endl;
	cout << "************Make Selection**************" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

// PYTHON CALL FUNCTION
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

// PYTHON CALL WITH STRING FUNCTION
int CallWithStringProcedure(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

// USER INPUT
void userInput() {
	string item;
	int input;
	cin >> input;

	// Validates user input.
	while (input < 1 || input > 4 || isdigit(input) != false) {
		cin.clear();
		cin.ignore();
		cout << "Enter only VALID operations: ";
		cin >> input;
	}

	// Call function based on user input.
	switch (input) {
		case 1:
			CallProcedure("ProductsPurchased");
			break;
		case 2:
			cout << "Enter Item Name" << endl;
			cin >> item;
			cout << endl;
			CallWithStringProcedure("ItemQuantity", item);
			break;
		case 3:
			CallProcedure("Histogram");
			break;
		case 4:
			cout << "Goodbye!" << endl;
			exit(0);
	}
}

int main()
{
	char cont = 'y';
	while (cont == 'y') {
		system("CLS");
		displayMenu();
		userInput();

		cout << "\n\n\nDo you wish to continue?(y/n)";
		cin >> cont;
		cout << endl;
	}

	cout << "Goodbye!" << endl;
	
	return 0;
}