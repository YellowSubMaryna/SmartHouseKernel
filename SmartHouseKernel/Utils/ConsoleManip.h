#pragma once

#include <windows.h>
#include "stringEx.h"
#include <functional>

enum class enmColors
{
    black,          //  0 text color - multiply by 16, for background colors
    dark_blue,      //  1
    dark_green,     //  2
    dark_cyan,      //  3
    dark_red,       //  4
    dark_magenta,   //  5
    dark_yellow,    //  6
    light_gray,     //  7
    dark_gray,      //  8
    light_blue,     //  9
    light_green,    // 10
    light_cyan,     // 11
    light_red,      // 12
    light_magenta,  // 13
    light_yellow,   // 14
    white           // 15
};

class CConsoleManip
{
private:
    HANDLE m_hStdout;
    CONSOLE_SCREEN_BUFFER_INFO m_csbiInfo;

    // вывести единственную строку текста в указанной позиции
    // если строка выходит за пределы области рисовани€ - вывести урезанную строку
    bool DrawText(short x, short y,
                  const char* sText, UINT length = UINT_MAX /*- use strlen*/,
                  enmColors crBackColor = enmColors::black,
                  enmColors crForeColor = enmColors::white);

    CConsoleManip(const CConsoleManip&) = delete;
    void operator=(const CConsoleManip&) = delete;
public:
    CConsoleManip();
    ~CConsoleManip();
    // проинициализировать размеры окна консоли (развернуть консоль по максимуму на экран)
    bool InitConsole();
    // получить размеры консольного окна и положени€ точки рисовани€ и курсора ввода команд
    bool ReinitConsoleSize();
    // вывести строку в указанной позиции области рисовани€
    // строка может содержать несколько строк текста
    // если строка выходит за область рисовани€ - будет выведена урезанна€ строка
    bool DrawTextMultiline(short x, short y,
                           stringEx sText,
                           enmColors crBackColor = enmColors::black,
                           enmColors crForeColor = enmColors::white);
    bool SetConsolePos(short x, short y);
    bool SetConsolePos(const COORD& pos);
    COORD GetConsolePos() const;
    bool SetTextColor(enmColors crBackColor = enmColors::black,
                      enmColors crForeColor = enmColors::light_gray);
    COORD DrawSpaceSize() const; // размер пространства дл€ рисовани€
    COORD DrawSpacePos() const; // вернуть позицию где отображаетс€ схема
    void ClearDrawSpace(); // очистить область отображени€ схемы

    COORD CommandLogOutputPos() const; // позици€ на экране, в которой находитс€ командна€ строка

    CConsoleManip& operator>>(int& val);
    template <class T>
    CConsoleManip& operator<<(T val)
    {
        cout << val;
        return *this;
    }
    // ¬се действи€ в программе осуществл€ем в кодировке cp1251
    // при вводе все строки конвертируютс€ в неЄ, а при выводе конвертируютс€ в DOS кодировку cp866
    CConsoleManip& operator<<(const char* str);

    // конструктор перемещени€ позвол€ет сэкономить на создании лишней копии строки при выводе
    CConsoleManip& operator<<(stringEx&& str);

    // разрешаем передавать в этот класс манипул€торы дл€ cout
    CConsoleManip& operator<<(ostream& (*manipulyator)(ostream&))
    {
        cout << manipulyator;
        return *this;
    }

    // разрешаем передавать в этот класс манипул€торы дл€ cin
    CConsoleManip& operator>>(istream& (*manipulyator)(istream&))
    {
        cin >> manipulyator;
        return *this;
    }
    // сбросить флаг ошибки ввода
    // и очистить буфер ввода
    void ClearErrorFlag();

    // проверка на ошибки ввода
    explicit operator bool() const
    {
        return (bool)cin;
    }
};

// ¬се действи€ в программе осуществл€ем в кодировке cp1251
// при вводе все строки конвертируютс€ в неЄ, а при выводе конвертируютс€ в DOS кодировку cp866
CConsoleManip& getline(CConsoleManip& console, OUT stringEx& str);
