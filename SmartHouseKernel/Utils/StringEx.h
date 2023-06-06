#pragma once

using namespace std;
#define OUT

class stringEx : public string
{
public:
    stringEx()
    {}
    stringEx(const stringEx& str) : string(str)
    {}
    using string::string; // ����������� �� ������������� ������ ������������ �� const char* � �� const string&
    stringEx(string&& str) : string(str)
    {}
    stringEx(stringEx&& str) noexcept : string(str)
    {}
    using string::operator=;
    stringEx& operator=(const stringEx& str)
    {
        this->string::operator=(str);
        return *this;
    }
    // ������� ������ psText �� �����
    // psSeparators - ������ ������������
    // skipEmpty - �� ��������� ������ �������
    vector<stringEx> Split(const char* psSeparators, bool skipEmpty = true);
    // �������� ������� ���� ���� �� ������
    stringEx& strlwr();
    // �������� ������� ���� ���� �� �������
    stringEx& strupr();

    // ��������������� ������ �� ��������� cp1251 (���������� � IDE ��� ������ ����������)
    // � cp866 (��������� �������)
    stringEx& ConvertToDos();
    // ��������������� ������ �� ��������� cp866 (��������� �������)
    // � cp1251(���������� � IDE ��� ������ ����������)
    stringEx& ConvertToWin();
};
