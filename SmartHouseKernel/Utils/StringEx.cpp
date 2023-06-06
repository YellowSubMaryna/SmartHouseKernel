#include "../stdafx.h"
#include "StringEx.h"
#include <windows.h>
#include <ctype.h>

// ������� ������ psText �� �����
// psSeparators - ������ ������������
// skipEmpty - �� ��������� ������ �������
// ���������� ���������� ���������� ����
vector<stringEx> stringEx::Split(const char* psSeparators, bool skipEmpty /*= true*/)
{
    vector<stringEx> res;
    if (!length())
        return res;
    stringEx str; // �� ������������ ����� ��� ������ ������ ��� - ���������� ���� � ��� ��(������������� ���������� ������ ���� ����� ������ �� ���������� � ���������� ����� �����)
    const char* psText = c_str();
    while (*psText)
    {
        const char* psNext = strpbrk(psText, psSeparators);
        if (!psNext)
        { // ������ ������������ � ������ ���, ����� ���� ��������� ����� ����� �� ������, ����� �� �� ����� � ��������� �������� �����
            res.push_back(psText);  // ��� ��������� ����� ������
            break;
        }
        if (!skipEmpty || psNext - psText)
        {
            str.assign(psText, psNext - psText);
            res.push_back(str);
        }
        psText = psNext + 1;
    }
    return res;
}

// �������� ������� ���� ���� �� ������
stringEx& stringEx::strlwr()
{
    // ������� strlwr - ������ ��� ����� � ������ ����������
    // �� �������� ������ ��������� �++, ������� ����������� � ����������� GCC, � ������ � � CodeBlocks
    // ������� ��� CodeBlocks ��������� � �������
    // �� Microsoft VisualStudio ���� ���������� ���� ������� � ������������: ��������� �� ����� ������ - ������� ��� ����� ������������ ��� ������������ �������

    // �������� � ������� ������ ������ ���� ������� �������������� ������

    if (!length())
        return *this;
    char* psStr = &(*this)[0];// �����, ��� ����� ������� ������
    #ifdef _MSC_VER
        // microsoft VC
        _strlwr_s(psStr, length() + 1); // ���� ������� ���� ���������� ������ ������ � �������� ����
    #else
        // CodeBlocks + GCC
        while (*psStr)
        {
            *psStr = tolower(*psStr);
            psStr++;
        }
    #endif
    return *this;
}
// �������� ������� ���� ���� �� �������
stringEx& stringEx::strupr()
{
    // �������� � ������� ������ ������ ���� ������� �������������� ������
    if (!length())
        return *this;
    char* psStr = &(*this)[0];// �����, ��� ����� ������� ������
    #ifdef _MSC_VER
        // microsoft VC
        _strupr_s(psStr, length() + 1); // ���� ������� ���� ���������� ������ ������ � �������� ����
    #else
        // CodeBlocks + GCC
        while (*psStr)
        {
            *psStr = toupper(*psStr);
            psStr++;
        }
    #endif
    return *this;
}

// ��������������� ������ �� ��������� cp1251 (���������� � IDE ��� ������ ����������)
// � cp866 (��������� �������)
stringEx& stringEx::ConvertToDos()
{
    if (!length())
        return *this;
    char* psStr = &(*this)[0];// �����, ��� ����� ������� ������
    ::AnsiToOem(psStr, OUT psStr);
    return *this;
}
// ��������������� ������ �� ��������� cp866 (��������� �������)
// � cp1251(���������� � IDE ��� ������ ����������)
stringEx& stringEx::ConvertToWin()
{
    if (!length())
        return *this;;
    char* psStr = &(*this)[0];// �����, ��� ����� ������� ������
    ::OemToAnsi(psStr, OUT psStr);
    return *this;
}
