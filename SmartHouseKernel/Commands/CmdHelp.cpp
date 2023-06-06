#include "../stdafx.h"
#include "CmdHelp.h"
#include <iomanip>
#include "../Context.h"
using namespace std;

bool CCmdHelp::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() == 0)
    { // ������ ������ ��������� ������
        // ����������� �����, ����� ��� �������� ���������� � ������ � ���� �� �������
        unsigned int maxleng = 0; // ������������ ����� ����� �������
        map<string, ICommand*>* pvCmds = &pContext->m_Commands.m_Commands;
        for (map<string, ICommand*>::iterator p = pvCmds->begin(); p != pvCmds->end(); ++p)
        {
            unsigned int curLeng = strlen(p->second->Name());
            maxleng = max(maxleng, curLeng);
        }
        pContext->m_Console << "�������� �������:" << endl;
        for (map<string, ICommand*>::iterator p = pvCmds->begin(); p != pvCmds->end(); ++p)
        {
            pContext->m_Console << "   "
                                << setw(maxleng) << resetiosflags(ios::adjustfield) << setiosflags(ios::left)
                                << p->second->Name() << " -  "
                                << p->second->Hint() << endl;
        }
        return true;
    }
    ICommand* pCmd = pContext->m_Commands.FindCommand(vParameters[0].c_str());
    if (!pCmd)
    {
        pContext->m_Console << "������� ����������� �������" << endl;
        return false;
    }
    vParameters.erase(vParameters.begin()); // ���� ���� �������������� ��������� � ������� ����� help <��� �������>, �� �������� �� �����
    string hint = pCmd->Hint();
    string help = pCmd->Help(pContext, vParameters);
    pContext->m_Console << hint.c_str() << endl
                        << help.c_str();
    return true;
}