#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	using namespace std;

	string TextGap = " | ";
	string FancyFloorCeil = "-+-=";
	string FunkifyText;

	cout << "~~~Enter The Text You Want To Funkify~~~\n\n";
	// cin >> FunkifyText; Doesnt work because it gets up to whitespace :C
	getline(cin, FunkifyText); // This works because it reads the entire line

	if (FunkifyText.length() == 0)
	{
		cerr << "Invalid, Incorrect String" << endl;
		return 1;
	}

	for (char a : FunkifyText)
	{
		TextGap += a;
		TextGap += " | ";
	}

	for (char b : FunkifyText)
	{
		FancyFloorCeil += "-+-=";
	}

	cout << "\n" << FancyFloorCeil << endl;
	cout << TextGap << endl;
	cout << FancyFloorCeil << endl;
}