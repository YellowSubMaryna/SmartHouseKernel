#pragma once
#include "_Command.h"

class CCmdMusicPosition : public ICommand
{
public:
    CCmdMusicPosition(){}

    virtual const char* Name()
    {
        return "musicposition";
    }
    virtual const char* Hint() // ������� �������� �������� �������
    {
        return "������ ��� ���������� ������� ������� ������������ ������";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "�������������:\n"
                   "musicposition\n"
                   "musicposition <������� ������������ � ��������>\n";
        return ICommand::Help(pContext, vParameters); // ����������� ��������� �� ��������� �������� ��� ����������� ������ ����������
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

