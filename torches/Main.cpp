#include <stdio.h>
#include <windows.h>   // WinApi header
#include <iostream>
#include <string>

int main()
{
	HANDLE  hConsole;
	int k;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// you can loop k higher to see more color choices
	for (k = 1; k < 255; k++)
	{
		SetConsoleTextAttribute(hConsole, 3);
		printf("%3d  %s\n", k, "I want to be nice today!");
		std::cout << "oekr;alskdf;lj" << std::endl;
	}
	std::string world;

	getchar();  // wait
	return 0;
}