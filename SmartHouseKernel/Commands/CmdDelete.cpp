#include "../stdafx.h"
#include "CmdDelete.h"
#include <iostream>
#include "../Context.h"
using namespace std;

std::string CCmdDelete::Help(CContext* pContext, const vector<stringEx>& vParameters)
{
    if (!vParameters.size())
        return "�������������:\n    delete <��� �������>\n";
    return ICommand::Help(pContext, vParameters);
}

bool CCmdDelete::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() == 0)
    {
        pContext->m_Console << "�� ������� ��� �������" << endl;
        return false;
    }
    if (vParameters.size() != 1)
    {
        pContext->m_Console << "������� ������� ����� ���������� ��� ���� �������" << endl;
        return false;
    }
    if (!pContext->m_ActiveModel.DeleteObject(vParameters[0].c_str()))
    {
        pContext->m_Console << "������ ������� �� ����������" << endl;
        return false;
    }
    pContext->m_Console << "������ �����" << endl;
    return true;
}