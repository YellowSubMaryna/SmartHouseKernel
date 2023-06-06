#include "../stdafx.h"
#include "CmdLoad.h"
#include <iostream>
#include <memory>
#include "../Context.h"
#include "../Storage/BinLoader.h"
#include "../Storage/TxtLoader.h"
using namespace std;

bool CCmdLoad::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() == 0 ||
        (vParameters[0] != "bin" && vParameters[0] != "txt"))
    {
        pContext->m_Console << "�� ������ ������ �����: bin - �������� ��� txt - ���������" << endl;
        return false;
    }
    if (vParameters.size() == 1)
    {
        pContext->m_Console << "�� ������� ��� �����" << endl;
        return false;
    }
    if (vParameters.size() > 2)
    {
        pContext->m_Console << "���������������� �������� �������" << endl;
        return false;
    }

    // ���������� ����� ���������, ����� �� �������������� ������� ����� �����, ����� delete �������� �������������
    unique_ptr<ILoader> pLoader;
    
    if (vParameters[0] == "bin")
        pLoader.reset(new CBinLoader(vParameters[1].c_str()));
    else
        pLoader.reset(new CTxtLoader(vParameters[1].c_str()));
    if (!*pLoader)
    {
        pContext->m_Console << "��������� ���� �� ������" << endl;
        return false;
    }
	// �������: � ������� ���������� SDL ��� ������� ������� �� ��������������� ����� ���������� ������
	// ��������� � �������, �� ��������������� ��� �� ������
	// �������� ��� CModel �� ������ ������ �������� �� ����� ��� ��������������� (��������� �� ��������������� � ��������, � ������ ���������� ������)
	// �� ��������� ����� ���������� ������ ��� ����� ������ ������ �� ����� ������ � SDL
	pContext->m_Console.SetTextColor(enmColors::black, enmColors::dark_red);
	bool bOk = pContext->m_ActiveModel.Load(pLoader.get(), &pContext->m_ObjFactory);
	pContext->m_Console.SetTextColor(); // ���� ������ �� ���������
    if (!bOk)
    {
        pContext->m_Console.SetTextColor(enmColors::black, enmColors::dark_red);
        pContext->m_Console << "�� ������� ��������� �������� �������� �� ���������� �����" << endl <<
                               "�� �������� ��� ������� � ������ �������" << endl <<
                               "��������: ��� �������� ������� ����� ������������ �������� ���� �������" << endl;
        pContext->m_ActiveModel.DestroyAll(); // ������� �������� ����������� ����� ������������ ��������
        return false;
    }
    pContext->m_Console << "���� ������� ��������" << endl;
    return true;
}