#include "bank.h"
#ifdef max
#undef max //! redefine max()
#endif
using namespace std;

int col, cen, consoleLine = 0;
bool repeat = false, menuRepeat = false,
     repeatForgot = false, sound = true;

//* Console function

void GoTo(int posX, int posY)
{
    COORD c;
    c.X = posX;
    c.Y = posY;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;
    SetConsoleCursorInfo(handle, &ConCurInf);
}

int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}

void drawFirstFrame(int vertical)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    col = columns;
    int width = getConsoleWidth();
    int center = width / 2;
    cen = center;
    GoTo((columns - 100) / 2, 3);
    for (int i = 0; i < 100; ++i)
    {
        cout << "*";
    }
    cout << endl;
    int startX = (columns - 100) / 2;
    int endX = startX + 99;
    for (int i = 4; i < vertical; ++i)
    {
        GoTo(startX, i);
        cout << "*";
        GoTo(endX, i);
        cout << "*";
    }
    GoTo((columns - 100) / 2, vertical);
    for (int i = 0; i < 100; ++i)
    {
        cout << "*";
    }
}

void drawSecondFrame(int value, int width)
{
    int startX = (col - width) / 2;
    int endX = startX + width - 1;

    // Draw the top border
    GoTo(startX, 3);
    for (int i = 0; i < width; ++i)
    {
        cout << "*";
    }
    cout << endl;

    // Draw the side borders
    for (int i = 4; i < value; ++i)
    {
        GoTo(startX, i);
        cout << "*";
        GoTo(endX, i);
        cout << "*";
    }

    // Draw the bottom border
    GoTo(startX, value);
    for (int i = 0; i < width; ++i)
    {
        cout << "*";
    }
}

void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void DisableResizeWindow()
{
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void DisableSelection()
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}

//* Menu function
void menu()
{
    if (!menuRepeat)
    {
        drawFirstFrame(22);
    }
    else
    {
        GoTo(cen - 14, 17);
        for (int i = 0; i < 45; ++i)
        {
            cout << " ";
        }
        drawSecondFrame(22, 100);
    }
    GoTo(cen - 13, 5);
    cout << "WELCOME TO CONSOLE BANKING";
    GoTo(cen - 15, 6);
    cout << "==============================";
    GoTo(cen - 10, 7);
    cout << "Developer - Gia Bao";
    GoTo(cen - 40, 9);
    cout << "1. SIGN UP FOR FREE";
    GoTo(cen - 40, 11);
    cout << "2. SIGN IN";
    GoTo(cen - 40, 13);
    cout << "3. FORGOT PASSWORD";
    GoTo(cen - 40, 15);
    cout << "4. EXIT";
    GoTo(cen - 40, 17);
    cout << "==> Enter your option: ";
    GoTo(cen - 40, 19);
    cout << "==> Press T to turn on/off sound";
    GoTo(cen + 30, 19);
    if (sound)
    {
        cout << "SOUND: ON";
    }
    else
    {
        cout << "SOUND :OFF";
    }
    while (1)
    {
        GoTo(cen - 17, 17);
        string opt;
        if (cin.peek() == '\n')
        {
            if (sound)
                PlaySound(TEXT("error.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            GoTo(cen - 14, 17);
            cout << "* The option is invalid. Please try again!!!";
        }
        else
        {
            cin >> opt;
            if (opt == "1")
            {
                if (sound)
                    PlaySound(TEXT("select.wav"), NULL, SND_FILENAME | SND_ASYNC);
                system("cls");
                account();
                break;
            }
            else if (opt == "2")
            {
                if (sound)
                    PlaySound(TEXT("select.wav"), NULL, SND_FILENAME | SND_ASYNC);
                system("cls");
                cin.ignore();
                repeat = false;
                login();
                break;
            }
            else if (opt == "3")
            {
                if (sound)
                    PlaySound(TEXT("select.wav"), NULL, SND_FILENAME | SND_ASYNC);
                repeatForgot = false;
                cin.ignore();
                forgotPass();
                break;
            }
            else if (opt == "4")
            {
                if (sound)
                    PlaySound(TEXT("select.wav"), NULL, SND_FILENAME | SND_ASYNC);
                exitApp();
            }
            else if (opt == "T")
            {
                if (sound)
                    PlaySound(TEXT("select.wav"), NULL, SND_FILENAME | SND_ASYNC);
                if (sound)
                {
                    sound = false;
                }
                else
                {
                    sound = true;
                }
                GoTo(cen + 30, 19);
                if (sound)
                {
                    cout << "SOUND: ON";
                    GoTo(cen + 39, 19);
                    cout << " ";
                }
                else
                {
                    cout << "SOUND: OFF";
                }
                cin.ignore();
                GoTo(cen - 17, 17);
                for (int i = 0; i < opt.length(); ++i)
                {
                    cout << " ";
                }
                GoTo(cen - 14, 17);
                for (int i = 0; i < 44; ++i)
                {
                    cout << " ";
                }
            }
            else
            {
                if (sound)
                    PlaySound(TEXT("error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                GoTo(cen - 14, 17);
                cout << "* The option is invalid. Please try again!!!";
                GoTo(cen - 17, 17);
                for (int i = 0; i < opt.length(); ++i)
                {
                    cout << " ";
                }
            }
        }
    }
}

//* Forgot Password function
void forgotPass()
{
    system("cls");
    string name, id;
    drawSecondFrame(30, 51);
    GoTo(cen - 11, 5);
    cout << "== FORGOT PASSWORD ==";
    GoTo(cen - 22, 9);
    cout << "Enter your username: ";
    GoTo(cen - 22, 11);
    cout << "Enter your card number: ";
    if (repeatForgot)
    {
        GoTo(cen - 22, 13);
        cout << "* Account does not exist!!!";
    }
    bool invalidName = false, invalidPass = false;
    while (1)
    {

        GoTo(cen - 1, 9);
        if (cin.peek() == '\n')
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            GoTo(cen - 22, 13);
            for (int i = 0; i < 27; ++i)
            {
                cout << " ";
            }
            GoTo(cen - 22, 13);
            invalidName = true;
            cout << "* Invalid input!!!";
        }
        else
        {
            getline(cin, name);
            if (invalidName)
            {
                GoTo(cen - 22, 13);
                for (int i = 0; i < 18; i++)
                {
                    cout << " ";
                }
            }
            break;
        }
    }
    while (1)
    {
        GoTo(cen + 2, 11);
        if (cin.peek() == '\n')
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            GoTo(cen - 22, 13);
            for (int i = 0; i < 27; ++i)
            {
                cout << " ";
            }
            GoTo(cen - 22, 13);
            invalidPass = true;
            cout << "* Invalid input!!!";
        }
        else
        {
            cin >> id;
            if (invalidPass)
            {
                GoTo(cen - 22, 13);
                for (int i = 0; i < 18; i++)
                {
                    cout << " ";
                }
            }
            break;
        }
    }
    ifstream in("C:/Users/Admin/Desktop/cppProject/data/userInfo.txt");
    string info, password;
    bool check = false;
    while (getline(in, info))
    {
        int pos = info.find('-');
        string fileUsername = info.substr(0, pos);
        if (fileUsername != name)
        {
            continue;
        }
        info = info.substr(pos + 1);
        pos = info.find('-');
        password = info.substr(0, pos);
        info = info.substr(pos + 1);
        pos = info.find('-');
        string fileID = info.substr(0, pos);
        if (fileID != id)
        {
            continue;
        }
        check = true;
    }
    if (check)
    {
        if (sound)
            PlaySound(TEXT("success.wav"), NULL, SND_FILENAME | SND_ASYNC);
        GoTo(cen - 22, 13);
        for (int i = 0; i < 27; ++i)
        {
            cout << " ";
        }
        GoTo(cen - 22, 13);
        cout << "==> Your password: " << password;
    }
    else
    {
        if (sound)
            PlaySound(TEXT("error.wav"), NULL, SND_FILENAME | SND_ASYNC);
        repeatForgot = true;
        cin.ignore();
        forgotPass();
    }
    in.close();
    GoTo(cen - 11, 17);
    cout << "Press Enter to log in ";
    GoTo(cen - 15, 18);
    cout << "or Esc to come back the menu ";
    char wait;
    wait = getch();
    if (wait == 13)
    {
        repeat = false;
        cin.ignore();
        login();
    }
    else if (wait == 27)
    {
        menuRepeat = true;
        system("cls");
        cin.ignore();
        menu();
    }
}

//* App exit function
void exitApp()
{
    ShowCur(0);
    system("cls");
    drawSecondFrame(18, 100);
    GoTo(cen - 30, 10);
    cout << "Thanks for your visit. The program will exit in   second";
    if (sound)
        PlaySound(TEXT("end.wav"), NULL, SND_FILENAME | SND_ASYNC);
    for (int i = 5; i >= 0; --i)
    {
        GoTo(cen + 18, 10);
        cout << i;
        Sleep(1000);
    }
    system("cls");
    exit(0);
}

//* Create account function
void account()
{
    people user;
    char pass;
    ofstream out("C:/Users/Admin/Desktop/cppProject/data/userInfo.txt", ios::app);
    drawSecondFrame(31, 100);
    GoTo(cen - 13, 5);
    cout << "== CREATE NEW ACCOUNT ==";
    cin.ignore();
    GoTo(cen - 45, 7);
    cout << "Full name: ";
    while (1)
    {
        GoTo(cen - 34, 7);
        getline(cin, user.fullname);
        if (user.fullname.empty())
        {
            GoTo(cen - 45, 9);
            cout << "* Invalid input!!!";
            GoTo(cen - 34, 7);
            for (int i = 0; i < user.fullname.length(); ++i)
            {
                cout << " ";
            }
        }
        else
        {
            GoTo(cen - 45, 9);
            for (int i = 0; i < 18; ++i)
            {
                cout << " ";
            }
            break;
        }
    }
    user.fullname = standardName(user.fullname);
    GoTo(cen - 45, 9);
    cout << "Address: ";
    while (1)
    {
        GoTo(cen - 36, 9);
        getline(cin, user.address);
        if (user.address.empty())
        {
            GoTo(cen - 45, 11);
            cout << "* Invalid input!!!";
            GoTo(cen - 36, 9);
            for (int i = 0; i < user.address.length(); ++i)
            {
                cout << " ";
            }
        }
        else
        {
            GoTo(cen - 45, 11);
            for (int i = 0; i < 18; ++i)
            {
                cout << " ";
            }
            break;
        }
    }
    GoTo(cen - 45, 11);
    cout << "Phone number: ";
    while (1)
    {
        GoTo(cen - 31, 11);
        getline(cin, user.phoneNumber);
        if (user.phoneNumber.empty() || !checkDigit(user.phoneNumber))
        {
            GoTo(cen - 45, 13);
            cout << "* Invalid input!!!";
            GoTo(cen - 31, 11);
            for (int i = 0; i < user.phoneNumber.length(); ++i)
            {
                cout << " ";
            }
        }
        else if (user.phoneNumber.length() > 20)
        {
            GoTo(cen - 45, 13);
            cout << "* Phone number must be less than 20 characters!!!";
            GoTo(cen - 31, 11);
            for (int i = 0; i < user.phoneNumber.length(); ++i)
            {
                cout << " ";
            }
        }
        else
        {
            GoTo(cen - 45, 13);
            for (int i = 0; i < 50; ++i)
            {
                cout << " ";
            }
            break;
        }
    }
    GoTo(cen - 45, 13);
    cout << "Date of birth:";
    while (1)
    {
        GoTo(cen - 45, 15);
        cout << "- Date: ";
        while (1)
        {
            GoTo(cen - 37, 15);
            if (cin.peek() == '\n')
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                GoTo(cen - 33, 15);
                cout << "* Invalid input!!!";
                GoTo(cen - 37, 15);
            }
            else
            {
                cin >> user.date;
                GoTo(cen - 33, 15);
                for (int i = 0; i < 18; ++i)
                {
                    cout << " ";
                }
                cin.ignore();
                break;
            }
        }
        GoTo(cen - 45, 17);
        cout << "- Month: ";
        while (1)
        {
            GoTo(cen - 36, 17);
            if (cin.peek() == '\n')
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                GoTo(cen - 32, 17);
                cout << "* Invalid input!!!";
                GoTo(cen - 36, 17);
            }
            else
            {
                cin >> user.month;
                GoTo(cen - 32, 17);
                for (int i = 0; i < 18; ++i)
                {
                    cout << " ";
                }
                cin.ignore();
                break;
            }
        }
        GoTo(cen - 45, 19);
        cout << "- Year: ";
        while (1)
        {
            GoTo(cen - 37, 19);
            if (cin.peek() == '\n')
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                GoTo(cen - 33, 19);
                cout << "* Invalid input!!!";
                GoTo(cen - 37, 19);
            }
            else
            {
                cin >> user.year;
                GoTo(cen - 33, 19);
                for (int i = 0; i < 18; ++i)
                {
                    cout << " ";
                }
                cin.ignore();
                break;
            }
        }
        if (!process(user.date, user.month, user.year))
        {
            GoTo(cen - 45, 21);
            cout << "* Invalid input!!!";
            GoTo(cen - 37, 15);
            for (int i = 0; i < user.date.length(); ++i)
            {
                cout << " ";
            }
            GoTo(cen - 36, 17);
            for (int i = 0; i < user.month.length(); ++i)
            {
                cout << " ";
            }
            GoTo(cen - 37, 19);
            for (int i = 0; i < user.year.length(); ++i)
            {
                cout << " ";
            }
        }
        else
        {
            GoTo(cen - 45, 21);
            for (int i = 0; i < 19; ++i)
            {
                cout << " ";
            }
            break;
        }
    }
    user.year = to_string(stoi(user.year));
    user.date = standard(user.date);
    user.month = standard(user.month);
    GoTo(cen - 45, 21);
    cout << "Money deposit: $ ";
    while (1)
    {
        GoTo(cen - 28, 21);
        if (cin.peek() == '\n')
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            GoTo(cen - 28, 21);
            for (int i = 0; i < 20; ++i)
            {
                cout << " ";
            }
            GoTo(cen - 45, 23);
            cout << "* Invalid input!!!";
        }
        else
        {
            GoTo(cen - 45, 23);
            for (int i = 0; i < 19; ++i)
            {
                cout << " ";
            }
            cin >> user.money;
            string temp = to_string(user.money);
            if (user.money <= 0 || user.money > LLONG_MAX || !checkDigit(temp) || cin.eof())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                GoTo(cen - 28, 21);
                for (int i = 0; i < 20; ++i)
                {
                    cout << " ";
                }
                GoTo(cen - 45, 23);
                cout << "* Invalid input!!!";
            }
            else
            {
                GoTo(cen - 45, 23);
                for (int i = 0; i < 19; ++i)
                {
                    cout << " ";
                }
                break;
            }
        }
    }
    GoTo(cen - 45, 23);
    bool repeatName = false;
    cin.ignore();
    while (1)
    {
        if (!repeatName)
        {
            cout << "Username: ";
            while (1)
            {
                if (cin.peek() == '\n')
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    GoTo(cen - 45, 25);
                    cout << "* Invalid input!!!";
                    repeatName = true;
                    GoTo(cen - 35, 23);
                }
                else
                {
                    GoTo(cen - 35, 23);
                    getline(cin, user.username);
                    break;
                }
            }
        }
        if (!checkExistUser(user.username) && user.username.length() <= 20 && !containSpace(user.username))
        {
            GoTo(cen - 45, 25);
            for (int i = 0; i < 46; ++i)
            {
                cout << " ";
            }
            break;
        }
        else
        {
            GoTo(cen - 45, 25);
            for (int i = 0; i < 46; ++i)
            {
                cout << " ";
            }
            if (user.username.length() > 20)
            {
                GoTo(cen - 45, 25);
                cout << "* Username must be less than 20 characters!!!";
                repeatName = true;
                GoTo(cen - 35, 23);
                for (int i = 0; i < user.username.length(); ++i)
                {
                    cout << " ";
                }
                GoTo(cen - 35, 23);
                getline(cin, user.username);
            }
            else if (containSpace(user.username))
            {
                GoTo(cen - 45, 25);
                cout << "* Username must not be contain space!!!";
                repeatName = true;
                GoTo(cen - 35, 23);
                for (int i = 0; i < user.username.length(); ++i)
                {
                    cout << " ";
                }
                GoTo(cen - 35, 23);
                getline(cin, user.username);
            }
            else
            {
                GoTo(cen - 45, 25);
                cout << "* Username already exists!!!";
                repeatName = true;
                GoTo(cen - 35, 23);
                for (int i = 0; i < user.username.length(); ++i)
                {
                    cout << " ";
                }
                GoTo(cen - 35, 23);
                getline(cin, user.username);
            }
        }
    }
    GoTo(cen - 45, 25);
    cout << "Password: ";
    int i = 0;
    while (1)
    {
        while (1)
        {
            pass = getch();
            if (pass != 13 && pass != 8)
            {
                user.password[i] = pass;
                ++i;
                cout << "*";
            }
            else if (pass == 8)
            {
                if (i > 0)
                {
                    --i;
                    cout << "\b \b";
                }
            }
            else
            {
                break;
            }
        }
        user.password[i] = '\0';
        if (strlen(user.password) > 20)
        {
            GoTo(cen - 45, 27);
            cout << "* Password must be less than 20 characters!!!";
            GoTo(cen - 35, 25);
            for (int i = 0; i <= strlen(user.password); ++i)
            {
                cout << " ";
            }
            GoTo(cen - 35, 25);
            i = 0;
        }
        else if (strlen(user.password) == 0)
        {
            GoTo(cen - 45, 27);
            for (int i = 0; i < 45; ++i)
            {
                cout << " ";
            }
            GoTo(cen - 45, 27);
            cout << "* Invalid input!!!";
            GoTo(cen - 35, 25);
            for (int i = 0; i <= strlen(user.password); ++i)
            {
                cout << " ";
            }
            GoTo(cen - 35, 25);
            i = 0;
        }
        else
        {
            GoTo(cen - 45, 27);
            for (int i = 0; i < 45; ++i)
            {
                cout << " ";
            }
            break;
        }
    }
    user.id = IDcard();
    GoTo(cen - 45, 27);
    cout << "Your card number: " << user.id;
    out << user.username << "-" << user.password << "-" << user.id << "-" << user.fullname
        << "-" << user.address << "-" << user.phoneNumber << "-" << user.date << "-"
        << user.month << "-" << user.year << "-" << user.money << endl;
    out.close();
    GoTo(cen - 17, 29);
    cout << "PLEASE WAIT FOR A FEW SECOND...";

    Sleep(5000);
    system("cls");
    drawSecondFrame(31, 100);
    if (sound)
        PlaySound(TEXT("success.wav"), NULL, SND_FILENAME | SND_ASYNC);
    GoTo(cen - 22, 5);
    cout << "YOUR ACCOUNT HAS BEEN CREATED SUCCESSFULLY";
    Sleep(1500);
    GoTo(cen - 15, 10);
    system("pause");
    repeat = false;
    login();
}

//* Log in function
void login()
{
    ifstream in("C:/Users/Admin/Desktop/cppProject/data/userInfo.txt");
    string name, idCard;
    char pass[50];
    system("cls");
    drawSecondFrame(30, 50);
    GoTo(cen - 6, 5);
    cout << "== LOG IN ==";
    GoTo(cen - 20, 9);
    cout << "Username: ";
    GoTo(cen - 20, 11);
    cout << "Password: ";
    if (repeat)
    {
        GoTo(cen - 22, 15);
        cout << "Invalid login or password. Please try again.";
        GoTo(cen - 20, 17);
        cout << "If you forgot password. Please press Esc.";
        GoTo(cen - 13, 19);
        cout << "Or press Enter to try again.";
        char ch = getch();
        if (ch == 27)
        {
            forgotPass();
        }
    }
    GoTo(cen - 10, 9);
    getline(cin, name);
    GoTo(cen - 10, 11);
    int i = 0;
    char temp;
    while (1)
    {
        temp = getch();
        if (temp != 13 && temp != 8)
        {
            pass[i] = temp;
            ++i;
            cout << "*";
        }
        else if (temp == 8)
        {
            if (i > 0)
            {
                --i;
                cout << "\b \b";
            }
        }
        else
        {
            break;
        }
    }
    pass[i] = '\0';
    string info;
    bool check = false;
    while (getline(in, info))
    {
        int pos = info.find('-');
        string fileUsername = info.substr(0, pos);
        if (fileUsername != name)
        {
            continue;
        }
        info = info.substr(pos + 1);
        pos = info.find('-');
        string filePassword = info.substr(0, pos);
        if (filePassword != string(pass))
        {
            continue;
        }
        info = info.substr(pos + 1);
        pos = info.find('-');
        idCard = info.substr(0, pos);
        check = true;
        break;
    }
    in.close();
    if (check)
    {
        GoTo(cen - 22, 15);
        for (int i = 0; i < 44; ++i)
        {
            cout << " ";
        }
        GoTo(cen - 20, 17);
        for (int i = 0; i < 41; ++i)
        {
            cout << " ";
        }
        GoTo(cen - 13, 19);
        for (int i = 0; i < 28; ++i)
        {
            cout << " ";
        }
        GoTo(cen - 10, 15);
        if (sound)
            PlaySound(TEXT("success.wav"), NULL, SND_FILENAME | SND_ASYNC);
        cout << "LOG IN SUCCESSFULLY";
        GoTo(cen - 15, 17);
        system("pause");
        display(name);
        return;
    }
    else
    {
        if (sound)
            PlaySound(TEXT("error.wav"), NULL, SND_FILENAME | SND_ASYNC);
        repeat = true;
        login();
    }
}

//* Display user information
void display(string username)
{
    system("cls");
    ifstream in("C:/Users/Admin/Desktop/cppProject/data/userInfo.txt");
    string info, d, m, y, dateOfBirth;
    people user;
    bool check = false;
    while (getline(in, info))
    {
        int pos = info.find('-');
        string fileUsername = info.substr(0, pos);
        if (fileUsername != username)
        {
            continue;
        }
        info = info.substr(pos + 1);
        pos = info.find('-');
        info = info.substr(pos + 1);
        pos = info.find('-');
        user.id = stoi(info.substr(0, pos));
        info = info.substr(pos + 1);
        pos = info.find('-');
        user.fullname = info.substr(0, pos);
        info = info.substr(pos + 1);
        pos = info.find('-');
        user.address = info.substr(0, pos);
        info = info.substr(pos + 1);
        pos = info.find('-');
        user.phoneNumber = info.substr(0, pos);
        info = info.substr(pos + 1);
        pos = info.find('-');
        d = info.substr(0, pos);
        info = info.substr(pos + 1);
        pos = info.find('-');
        m = info.substr(0, pos);
        info = info.substr(pos + 1);
        pos = info.find('-');
        y = info.substr(0, pos);
        info = info.substr(pos + 1);
        pos = info.find('-');
        user.money = stoi(info.substr(0, pos));
        dateOfBirth = d + "/" + m + "/" + y;
    }
    drawSecondFrame(31, 100);
    int horizontal = user.fullname.length() - 13;
    GoTo(cen - 11 - horizontal, 5);
    cout << "WELCOME, " << user.fullname;
    GoTo(cen - 15 - horizontal, 6);
    for (int i = 0; i < 30 + horizontal; ++i)
    {
        cout << "=";
    }
    GoTo(cen + 21, 9);
    cout << "YOUR ACCOUNT INFO";
    GoTo(cen + 20, 10);
    cout << "===================";
    GoTo(cen + 20, 12);
    cout << "Card number: " << user.id;
    GoTo(cen + 20, 14);
    cout << "Full name: ";
    GoTo(cen + 31, 14);
    int nLine = 0;
    for (int i = 0; i < user.fullname.length(); ++i)
    {
        if (i < 16)
        {
            cout << user.fullname[i];
        }
        else if (i >= 16 && i < 40)
        {
            nLine = 1;
            GoTo(cen + 20 + i - 16, 15);
            cout << user.fullname[i];
        }
    }
    GoTo(cen + 20, 16 + nLine);
    cout << "Address: ";
    GoTo(cen + 29, 16 + nLine);
    int newline = 0;
    for (int i = 0; i < user.address.length(); ++i)
    {
        if (i < 16)
        {
            cout << user.address[i];
        }
        else if (i >= 16 && i < 40)
        {
            newline = 1;
            GoTo(cen + 20 + i - 16, 17 + nLine);
            cout << user.address[i];
        }
        else if (i >= 40 && i < 64)
        {
            newline = 2;
            GoTo(cen + 20 + i - 40, 18 + nLine);
            cout << user.address[i];
        }
        else if (i >= 64 && i < 88)
        {
            newline = 3;
            GoTo(cen + 20 + i - 64, 19 + nLine);
            cout << user.address[i];
        }
        else if (i >= 88 && i < 112)
        {
            newline = 4;
            GoTo(cen + 20 + i - 88, 20 + nLine);
            cout << user.address[i];
        }
    }
    GoTo(cen + 20, 18 + newline + nLine);
    cout << "Phone number: " << user.phoneNumber;
    GoTo(cen + 20, 20 + newline + nLine);
    cout << "Date of birth: " << dateOfBirth;
    GoTo(cen - 44, 9);
    cout << "HOME";
    GoTo(cen - 45, 10);
    cout << "======";
    GoTo(cen - 45, 12);
    cout << "1. AVAILABLE BALANCE";
    GoTo(cen - 45, 14);
    cout << "2. TRANSFER";
    GoTo(cen - 45, 16);
    cout << "3. LOG OUT";
    GoTo(cen - 45, 18);
    cout << "4. MENU";
    GoTo(cen - 45, 20);
    cout << "5. EXIT";
    GoTo(cen - 45, 22);
    cout << "==> Enter your option: ";
    while (1)
    {
        GoTo(cen - 22, 22);
        string opt;
        if (cin.peek() == '\n')
        {
            if (sound)
                PlaySound(TEXT("error.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            GoTo(cen - 45, 24);
            cout << "* The option is invalid. Please try again!!!";
        }
        else
        {
            cin >> opt;
            if (opt == "1")
            {
                if (sound)
                    PlaySound(TEXT("select.wav"), NULL, SND_FILENAME | SND_ASYNC);
                checkBalance(username);
                return;
            }
            else if (opt == "2")
            {
                if (sound)
                    PlaySound(TEXT("select.wav"), NULL, SND_FILENAME | SND_ASYNC);
                cin.ignore();
                transfer(username);
                return;
            }
            else if (opt == "3")
            {
                if (sound)
                    PlaySound(TEXT("select.wav"), NULL, SND_FILENAME | SND_ASYNC);
                system("cls");
                logout();
                return;
            }
            else if (opt == "4")
            {
                if (sound)
                    PlaySound(TEXT("select.wav"), NULL, SND_FILENAME | SND_ASYNC);
                menuRepeat = true;
                system("cls");
                cin.ignore();
                menu();
                return;
            }
            else if (opt == "5")
            {
                if (sound)
                    PlaySound(TEXT("select.wav"), NULL, SND_FILENAME | SND_ASYNC);
                exitApp();
            }
            else
            {
                if (sound)
                    PlaySound(TEXT("error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                GoTo(cen - 45, 24);
                cout << "* The option is invalid. Please try again!!!";
                GoTo(cen - 22, 22);
                for (int i = 0; i < opt.length(); ++i)
                {
                    cout << " ";
                }
            }
        }
    }
}

//* Log out function
void logout()
{
    drawSecondFrame(30, 50);
    GoTo(cen - 6, 5);
    cout << "== LOG OUT ==";
    GoTo(cen - 13, 13);
    cout << "Please wait, logging out...";
    Sleep(2000);
    if (sound)
        PlaySound(TEXT("success.wav"), NULL, SND_FILENAME | SND_ASYNC);
    GoTo(cen - 10, 15);
    cout << "LOG OUT SUCCESSFULLY";
    GoTo(cen - 15, 17);
    system("pause");
    repeat = false;
    cin.ignore();
    login();
}
long long getMoney(string user)
{
    ifstream in("C:/Users/Admin/Desktop/cppProject/data/userInfo.txt");
    string info, mon;
    while (getline(in, info))
    {
        int pos = info.find("-");
        string fileUsername = info.substr(0, pos);
        if (fileUsername != user)
        {
            continue;
        }
        int t = info.rfind("-");
        mon = info.substr(t + 1);
    }
    in.close();
    return stoll(mon);
}

//* Transfer money function
void transfer(string send)
{
    string receive;
    long long moneyHave = getMoney(send);
    long long moneySend;
    system("cls");
    drawSecondFrame(30, 60);
    GoTo(cen - 10, 5);
    cout << "--- TRANSFER MONEY ---";
    GoTo(cen - 10, 6);
    cout << "======================";
    GoTo(cen - 20, 9);
    cout << "Beneficiary (username): ";
    while (1)
    {
        GoTo(cen + 4, 9);
        getline(cin, receive);
        if (!checkExistUser(receive) || (receive == send))
        {
            GoTo(cen + 4, 9);
            for (int i = 0; i < receive.length(); ++i)
            {
                cout << " ";
            }
            GoTo(cen - 20, 11);
            cout << "* The user is invalid!!!";
        }
        else
        {
            GoTo(cen - 20, 11);
            for (int i = 0; i < 24; ++i)
            {
                cout << " ";
            }
            break;
        }
    }
    GoTo(cen - 20, 11);
    cout << "Amount: $ ";
    while (1)
    {
        GoTo(cen - 10, 11);
        cin >> moneySend;
        if (moneySend > moneyHave)
        {
            GoTo(cen - 10, 11);
            for (int i = 0; i < 25; ++i)
            {
                cout << " ";
            }
            if (sound)
                PlaySound(TEXT("error.wav"), NULL, SND_FILENAME | SND_ASYNC);
            GoTo(cen - 20, 13);
            cout << "* You do not have enough money!!!";
            GoTo(cen - 20, 14);
            cout << "* Press Esc to come back or Enter to continue";
            char ch = getch();
            if (ch == 27)
            {
                cin.ignore();
                display(send);
            }
            else if (ch == 13)
            {
                GoTo(cen - 10, 11);
                for (int i = 0; i < 25; ++i)
                {
                    cout << " ";
                }
            }
        }
        else if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            GoTo(cen - 20, 13);
            for (int i = 0; i < 45; ++i)
            {
                cout << " ";
            }
            GoTo(cen - 20, 14);
            for (int i = 0; i < 45; ++i)
            {
                cout << " ";
            }
            GoTo(cen - 10, 11);
            for (int i = 0; i < 25; ++i)
            {
                cout << " ";
            }
            GoTo(cen - 20, 13);
            cout << "* Invalid input!!!";
        }
        else if (moneySend <= 0)
        {
            GoTo(cen - 20, 13);
            for (int i = 0; i < 45; ++i)
            {
                cout << " ";
            }
            GoTo(cen - 20, 14);
            for (int i = 0; i < 45; ++i)
            {
                cout << " ";
            }
            GoTo(cen - 20, 13);
            cout << "* Invalid amount!!!";
            GoTo(cen - 10, 11);
            for (int i = 0; i < 25; ++i)
            {
                cout << " ";
            }
        }
        else
        {
            GoTo(cen - 20, 13);
            for (int i = 0; i < 45; ++i)
            {
                cout << " ";
            }
            GoTo(cen - 20, 14);
            for (int i = 0; i < 45; ++i)
            {
                cout << " ";
            }
            break;
        }
    }
    GoTo(cen - 10, 14);
    cout << "----------------------";
    GoTo(cen - 10, 15);
    cout << "|";
    GoTo(cen - 10, 16);
    cout << "----------------------";
    GoTo(cen + 11, 15);
    cout << "|";
    GoTo(cen - 9, 15);
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 15000000; j++)
        {
            j++;
            j--;
        }
        cout << "*";
    }
    if (sound)
        PlaySound(TEXT("success.wav"), NULL, SND_FILENAME | SND_ASYNC);
    GoTo(cen - 15, 19);
    cout << "AMOUNT SUCCESSFULLY TRANSFERRED";
    moneyProcess(moneySend, send, receive);
    transaction(moneySend, send, receive);
    GoTo(cen - 15, 21);
    system("pause");
    cin.ignore();
    display(send);
}

void moneyProcess(long long money, string sent, string received)
{
    ifstream file("C:/Users/Admin/Desktop/cppProject/data/userInfo.txt");
    vector<string> lines;
    string info;
    while (getline(file, info))
    {
        lines.push_back(info);
    }
    file.close();
    for (string &line : lines)
    {
        int pos = line.find("-");
        string fileUser = line.substr(0, pos);
        if (fileUser == sent)
        {
            int lastDashPos = line.rfind("-");
            string currentMoneyStr = line.substr(lastDashPos + 1);
            long long currentMoney = stoll(currentMoneyStr);
            currentMoney -= money;
            line = line.substr(0, lastDashPos + 1) + to_string(currentMoney);
        }
        if (fileUser == received)
        {
            int lastDashPos = line.rfind("-");
            string currentMoneyStr = line.substr(lastDashPos + 1);
            long long currentMoney = stoll(currentMoneyStr);
            currentMoney += money;
            line = line.substr(0, lastDashPos + 1) + to_string(currentMoney);
        }
    }
    ofstream outFile("C:/Users/Admin/Desktop/cppProject/data/userInfo.txt");
    for (const string &line : lines)
    {
        outFile << line << "\n";
    }
    outFile.close();
}

string printCurrentTime()
{
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &currentTime);
    return buffer;
}

//* Check balance available and transaction history
void checkBalance(string user)
{
    system("cls");
    GoTo(cen - 14, 5);
    cout << "--- CHECK BALANCE ---";
    GoTo(cen - 14, 6);
    cout << "=====================";
    GoTo(cen - 48, 8);
    cout << "AVAILABLE BALANCE: $ " << getMoney(user);
    GoTo(cen - 48, 10);
    cout << "NO.";
    GoTo(cen - 41, 10);
    cout << "FROM";
    GoTo(cen - 20, 10);
    cout << "TO";
    GoTo(cen + 1, 10);
    cout << "AMOUNT";
    GoTo(cen + 24, 10);
    cout << "TIME";
    ifstream in("C:/Users/Admin/Desktop/cppProject/data/transaction.txt");
    string temp;
    int cnt = 0, newline = 0;
    while (getline(in, temp))
    {
        int pos = temp.find("-");
        string fileUser = temp.substr(0, pos);
        temp = temp.substr(pos + 1);
        pos = temp.find("-");
        string fileReceive = temp.substr(0, pos);
        temp = temp.substr(pos + 1);
        pos = temp.find("-");
        string fileMoney = temp.substr(0, pos);
        string fileDate = temp.substr(pos + 1);
        if (fileUser != user && fileReceive != user)
        {
            continue;
        }
        else if (fileReceive == user)
        {
            ++cnt;
            GoTo(cen - 48, 11 + newline);
            cout << cnt;
            GoTo(cen - 41, 11 + newline);
            cout << fileUser;
            GoTo(cen - 20, 11 + newline);
            cout << "You";
            GoTo(cen + 1, 11 + newline);
            cout << "$ " << fileMoney;
            GoTo(cen + 24, 11 + newline);
            cout << fileDate;
            ++newline;
        }
        else if (fileUser == user)
        {
            ++cnt;
            GoTo(cen - 48, 11 + newline);
            cout << cnt;
            GoTo(cen - 41, 11 + newline);
            cout << "You";
            GoTo(cen - 20, 11 + newline);
            cout << fileReceive;
            GoTo(cen + 1, 11 + newline);
            cout << "$ " << fileMoney;
            GoTo(cen + 24, 11 + newline);
            cout << fileDate;
            ++newline;
        }
    }
    in.close();
    if (cnt - 11 >= 0)
    {
        consoleLine = cnt - 11;
    }
    drawSecondFrame(30 + consoleLine, 104);
    GoTo(cen - 20, 25 + consoleLine);
    system("pause");
    cin.ignore();
    display(user);
}

void transaction(long long money, string sent, string received)
{
    ofstream out("C:/Users/Admin/Desktop/cppProject/data/transaction.txt", ios::app);
    out << sent << "-" << received << "-" << money << "-" << printCurrentTime();
    out.close();
}

//* Additional function
int IDcard()
{
    srand(time(0));
    int random = 0;
    for (int i = 0; i < 10; ++i)
    {
        random = random + rand() % 1000 + 789;
    }
    return random;
}

bool checkExistUser(string user)
{
    ifstream in("C:/Users/Admin/Desktop/cppProject/data/userInfo.txt");
    string info;
    while (getline(in, info))
    {
        int pos = info.find('-');
        string fileUsername = info.substr(0, pos);
        if (fileUsername == user)
        {
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}

bool isLeapYear(int year)
{
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
    {
        return true;
    }
    return false;
}

bool standardDigit(string check)
{
    for (int i = 0; i < check.length(); ++i)
    {
        if (!isdigit(check[i]))
        {
            return false;
        }
    }
    return true;
}

bool process(string day, string month, string year)
{
    if (!(standardDigit(day) && standardDigit(month) && standardDigit(year)))
    {
        return false;
    }
    int d = stoi(day), m = stoi(month), y = stoi(year);
    if (d <= 0 || m <= 0 || y <= 0 || m > 12 || d > 31)
    {
        return false;
    }
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
    {
        if (d > 31)
        {
            return false;
        }
    }
    else if (m == 4 || m == 6 || m == 9 || m == 11)
    {
        if (d > 30)
        {
            return false;
        }
    }
    else if (m == 2)
    {
        if (!isLeapYear(y))
        {
            if (d > 28)
            {
                return false;
            }
        }
        else
        {
            if (d > 29)
            {
                return false;
            }
        }
    }
    return true;
}

string standard(string type)
{
    if (stoi(type) < 10)
    {
        return "0" + type;
    }
    return type;
}

string standardName(string name)
{
    stringstream ss(name);
    string temp;
    vector<string> v;
    while (ss >> temp)
    {
        temp[0] = toupper(temp[0]);
        v.push_back(temp);
    }
    temp = "";
    for (int i = 0; i < v.size(); ++i)
    {
        if (i != v.size() - 1)
        {
            temp = temp + v[i] + " ";
        }
        else
        {
            temp = temp + v[i];
        }
    }
    return temp;
}

bool checkDigit(string str)
{
    for (int i = 0; i < str.length(); ++i)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

bool containSpace(string input)
{
    return input.find(' ') != string::npos;
}