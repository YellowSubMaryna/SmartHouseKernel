#include "../stdafx.h"
#include "ConsoleManip.h"
#include <iostream>
#include <assert.h>
using namespace std;

COORD CreateLocation(short x, short y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    return pos;
}

static const COORD g_InvalidLocation = CreateLocation(0, 0); // � ������ ������ ����� ���������� ������� ����������

CConsoleManip::CConsoleManip()
            : m_hStdout(INVALID_HANDLE_VALUE),
              m_csbiInfo()
{
    InitConsole();
}


CConsoleManip::~CConsoleManip()
{
}

// ������������������� ������� ���� �������
bool CConsoleManip::InitConsole()
{
    m_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (m_hStdout == INVALID_HANDLE_VALUE)
    {
        cout << "GetStdHandle failed with code " << GetLastError() << endl;
        return false;
    }

    // Get the screen buffer size.
    if (!GetConsoleScreenBufferInfo(m_hStdout, &m_csbiInfo))
    {
        cout << "GetConsoleScreenBufferInfoEx failed with code " << GetLastError() << endl;
        return false;
    }
    COORD maxSize = GetLargestConsoleWindowSize(m_hStdout);
    maxSize.X -= 4; // ����������� ����� �� ������ ��� ����� ���� (GetLargestConsoleWindowSize ��� � ������ � ���� ���� ���� �� ������� �� �����)
    maxSize.Y -= 2;
    m_csbiInfo.dwSize = maxSize;
    m_csbiInfo.srWindow.Top = 0;
    m_csbiInfo.srWindow.Left = 0;
    m_csbiInfo.srWindow.Bottom = m_csbiInfo.dwSize.Y - 1;
    m_csbiInfo.srWindow.Right = m_csbiInfo.dwSize.X - 1;

    if (!SetConsoleScreenBufferSize(m_hStdout, m_csbiInfo.dwSize))
    {
        cout << "SetConsoleScreenBufferSize failed with code " << GetLastError() << endl;
        return false;
    }
    if (!SetConsoleWindowInfo(m_hStdout, TRUE, &m_csbiInfo.srWindow))
    {
        cout << "SetConsoleWindowInfo failed with code " << GetLastError() << endl;
        return false;
    }
    return SetConsolePos(CommandLogOutputPos());
}

// �������� ������� ����������� ���� � ��������� ����� �������� ��������� ����� ��������� � ������� ����� ������
bool CConsoleManip::ReinitConsoleSize()
{
    if (m_hStdout == INVALID_HANDLE_VALUE)
        return false;
    if (!GetConsoleScreenBufferInfo(m_hStdout, &m_csbiInfo))
        return false;
    m_csbiInfo.dwCursorPosition = CommandLogOutputPos();
    return true;
}

// ������� ������ ������������ ��� ���������
COORD CConsoleManip::DrawSpaceSize() const
{
    COORD pos = DrawSpacePos();
    pos.X = m_csbiInfo.dwSize.X - pos.X;
    pos.Y = m_csbiInfo.dwSize.Y - pos.Y - 1; // ��������� ��������� ������� � ��� ����� �������� ������ �������
    return pos;
}

// ������� ������� ��� ������������ �����
COORD CConsoleManip::DrawSpacePos() const
{
    return CreateLocation( (short)(m_csbiInfo.dwSize.X / 2),
                           (short)0 );
}

// ������� �� ������, � ������� ��������� ��������� ������
COORD CConsoleManip::CommandLogOutputPos() const
{
    return CreateLocation( (short)0,
                           (short)((m_csbiInfo.dwSize.Y - 1)) );
}

// �������� ������� ����������� �����
void CConsoleManip::ClearDrawSpace()
{
    COORD size = DrawSpaceSize();
    stringEx spaces;
    spaces.resize(size.X, ' ');
    for (int i = 0; i < size.Y; i++)
        DrawText(0, i, spaces.c_str(), spaces.length());
}

// ������� ������������ ������ ������ � ��������� �������
// ���� ������ ������� �� ������� ������� ��������� - ������� ��������� ������
bool CConsoleManip::DrawText(short x, short y,
                             const char* sText, UINT length /* = UINT_MAX - use strlen*/,
                             enmColors crBackColor /*= enmColors::black*/,
                             enmColors crForeColor /*= enmColors::white*/)
{
    COORD spacePos = DrawSpacePos();
    COORD spaceSize = DrawSpaceSize();
    if (y < 0) // ���� ������� ��������� �� �������
        return true; // ��� ���������� ��������� - �� ������
    if (y >= spaceSize.Y) // ���� ������� ��������� �� �������
        return true; // ��� ���������� ��������� - �� ������
    if (length == UINT_MAX)
        length = strlen(sText);
    if (x < 0) // �� ������� ������ ����� ������� ���������
    {
        sText += -x;
        length -= -x;
    }
    if ((int)length + x > spaceSize.X) // ����� �� ������ ���� ������
        length = spaceSize.X - x;
    if ((int)length <= 0) // ��� ������ ��������� �� ��������� ������
        return true; // ��� ���������� ��������� - �� ������
    if (!SetTextColor(crBackColor, crForeColor) ||
        !SetConsolePos(x + spacePos.X, y + spacePos.Y))
        return false;
    cout.write(sText, length);
    return true;
}

// ������� ������ � ��������� ������� ������� ���������
// ������ ����� ��������� ��������� ����� ������
// ���� ������ ������� �� ������� ��������� - ����� �������� ��������� ������
bool CConsoleManip::DrawTextMultiline(short x, short y,
                                      stringEx sText, enmColors crBackColor /*= enmColors::black*/,
                                                      enmColors crForeColor /*= enmColors::white*/)
{
    vector<stringEx> vWords = sText.Split("\n", false);
    bool res = true;
    for (size_t i = 0; i < vWords.size(); i++)
        res &= DrawText(x, static_cast<short>(y + i), vWords[i].c_str(), vWords[i].length(), crBackColor, crForeColor);
    return res;
}

bool CConsoleManip::SetConsolePos(short x, short y)
{
    if (m_hStdout == INVALID_HANDLE_VALUE)
        return false;
    COORD pos;
    pos.X = x;
    pos.Y = y;
    return SetConsoleCursorPosition(m_hStdout, pos) != FALSE;
}

bool CConsoleManip::SetConsolePos(const COORD& pos)
{
    return SetConsolePos(pos.X, pos.Y);
}

COORD CConsoleManip::GetConsolePos() const
{
    if (m_hStdout != INVALID_HANDLE_VALUE)
        return g_InvalidLocation;
    CONSOLE_SCREEN_BUFFER_INFO inf;
    if (GetConsoleScreenBufferInfo(m_hStdout, &inf) == FALSE)
    {
        assert(false);
        return g_InvalidLocation;
    }
    return inf.dwCursorPosition;
}

bool CConsoleManip::SetTextColor(enmColors crBackColor /*= enmColors::black*/,
                                 enmColors crForeColor /*= enmColors::light_gray*/)
{
    if (m_hStdout == INVALID_HANDLE_VALUE)
        return false;
    int color_total = (static_cast<int>(crForeColor)+(static_cast<int>(crBackColor)* 16));
    return SetConsoleTextAttribute(m_hStdout, color_total) != FALSE;
}


CConsoleManip& CConsoleManip::operator>>(int& val)
{
    cin >> val;
    return *this;
}

// ��� �������� � ��������� ������������ � ��������� cp1251
// ��� ����� ��� ������ �������������� � ��, � ��� ������ �������������� � DOS ��������� cp866
CConsoleManip& CConsoleManip::operator<<(const char* str)
{
    stringEx strEx(str);
    cout << strEx.ConvertToDos();
    return *this;
}

// ����������� ����������� ��������� ���������� �� �������� ������ ����� ������ ��� ������
CConsoleManip& CConsoleManip::operator<<(stringEx&& str)
{
    cout << str.ConvertToDos();
    return *this;
}

CConsoleManip& getline(CConsoleManip& console, OUT stringEx& str)
{
    getline(cin, OUT str);
    str.ConvertToWin();
    return console;
}
// �������� ���� ������ �����
// � �������� ����� �����
void CConsoleManip::ClearErrorFlag()
{
    cin.clear();
    cin.ignore(cin.rdbuf()->in_avail());
}
