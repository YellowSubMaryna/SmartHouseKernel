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

    // ������� ������������ ������ ������ � ��������� �������
    // ���� ������ ������� �� ������� ������� ��������� - ������� ��������� ������
    bool DrawText(short x, short y,
                  const char* sText, UINT length = UINT_MAX /*- use strlen*/,
                  enmColors crBackColor = enmColors::black,
                  enmColors crForeColor = enmColors::white);

    CConsoleManip(const CConsoleManip&) = delete;
    void operator=(const CConsoleManip&) = delete;
public:
    CConsoleManip();
    ~CConsoleManip();
    // ������������������� ������� ���� ������� (���������� ������� �� ��������� �� �����)
    bool InitConsole();
    // �������� ������� ����������� ���� � ��������� ����� ��������� � ������� ����� ������
    bool ReinitConsoleSize();
    // ������� ������ � ��������� ������� ������� ���������
    // ������ ����� ��������� ��������� ����� ������
    // ���� ������ ������� �� ������� ��������� - ����� �������� ��������� ������
    bool DrawTextMultiline(short x, short y,
                           stringEx sText,
                           enmColors crBackColor = enmColors::black,
                           enmColors crForeColor = enmColors::white);
    bool SetConsolePos(short x, short y);
    bool SetConsolePos(const COORD& pos);
    COORD GetConsolePos() const;
    bool SetTextColor(enmColors crBackColor = enmColors::black,
                      enmColors crForeColor = enmColors::light_gray);
    COORD DrawSpaceSize() const; // ������ ������������ ��� ���������
    COORD DrawSpacePos() const; // ������� ������� ��� ������������ �����
    void ClearDrawSpace(); // �������� ������� ����������� �����

    COORD CommandLogOutputPos() const; // ������� �� ������, � ������� ��������� ��������� ������

    CConsoleManip& operator>>(int& val);
    template <class T>
    CConsoleManip& operator<<(T val)
    {
        cout << val;
        return *this;
    }
    // ��� �������� � ��������� ������������ � ��������� cp1251
    // ��� ����� ��� ������ �������������� � ��, � ��� ������ �������������� � DOS ��������� cp866
    CConsoleManip& operator<<(const char* str);

    // ����������� ����������� ��������� ���������� �� �������� ������ ����� ������ ��� ������
    CConsoleManip& operator<<(stringEx&& str);

    // ��������� ���������� � ���� ����� ������������ ��� cout
    CConsoleManip& operator<<(ostream& (*manipulyator)(ostream&))
    {
        cout << manipulyator;
        return *this;
    }

    // ��������� ���������� � ���� ����� ������������ ��� cin
    CConsoleManip& operator>>(istream& (*manipulyator)(istream&))
    {
        cin >> manipulyator;
        return *this;
    }
    // �������� ���� ������ �����
    // � �������� ����� �����
    void ClearErrorFlag();

    // �������� �� ������ �����
    explicit operator bool() const
    {
        return (bool)cin;
    }
};

// ��� �������� � ��������� ������������ � ��������� cp1251
// ��� ����� ��� ������ �������������� � ��, � ��� ������ �������������� � DOS ��������� cp866
CConsoleManip& getline(CConsoleManip& console, OUT stringEx& str);
