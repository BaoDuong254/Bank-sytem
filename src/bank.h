// Library declare
#pragma once
#include <conio.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits.h>
#include <math.h>
#include <chrono>
#include <ctime>
#include <Windows.h>
#include <mmsystem.h>
using namespace std;

// Function declare
void SetWindowSize(SHORT, SHORT);
void DisableResizeWindow();
void DisableSelection();
void transaction(long long, string, string);
void checkBalance(string);
void transfer(string);
void moneyProcess(long long, string, string);
void logout();
void exitApp();
void display(string);
void login();
void account();
void drawFirstFrame(int);
void menu();
void GoTo(int, int);
void ShowCur(bool);
void drawSecondFrame(int, int);
void forgotPass();
string printCurrentTime();
string standard(string);
string standardName(string);
int IDcard();
int getConsoleWidth();
long long getMoney(string);
bool checkExistUser(string);
bool checkDigit(string);
bool isLeapYear(int);
bool standardDigit(string);
bool process(string, string, string);
bool containSpace(string);

// Struct declare
struct people
{
	string username, address, phoneNumber, fullname,
		date, month, year;
	char password[100];
	long long money;
	int id;
};