// **********************************
// * Author: BaoDuong254
// * Project: Bank system
// * Date: 18/07/2024
// **********************************

#include "bank.h"
int main()
{
	system("cls");
	SetWindowSize(250, 250);   // Set the console size
	DisableResizeWindow();	   // Disable to resize console size
	DisableSelection();		   // Disable selection text
	SetConsoleOutputCP(65001); // Vietnamese font for console
	//ShowCur(0);								  // Hide the cursor
	SetConsoleTitle(TEXT("Bank system console")); // Set the title of the console
	menu();
}