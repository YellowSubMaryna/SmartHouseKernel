// SmartHouseKernel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include "context.h"
#include "Utils/StringEx.h"
#include "Storage/BinLoader.h"
#include "Storage/BinStorer.h"
#include "SmartObjects/RoomObject.h"
#include "Commands/_Command.h"
using namespace std;

int main(void)
{
    CContext context;
    {// ������������ ���� ������������� ������� loader
        CBinLoader loader("myroom.bin");
        // �������: � ������� ���������� SDL ��� ������� ������� �� ��������������� ����� ���������� ������
        // ��������� � �������, �� ��������������� ��� �� ������
        // �������� ��� CModel �� ������ ������ �������� �� ����� ��� ��������������� (��������� �� ��������������� � ��������, � ������ ���������� ������),
        // �� ��������� ����� ���������� ������ ��� ����� ������ ������ �� ����� ������ � SDL
        context.m_Console.SetTextColor(enmColors::black, enmColors::dark_red);
        bool bOk = context.m_ActiveModel.Load(&loader, &context.m_ObjFactory);
        context.m_Console.SetTextColor(); // ���� ������ �� ���������
        if (!bOk)
        { // �������� �� ������� - ������ ����� �� ���������
            context.m_Console.SetTextColor(enmColors::black, enmColors::dark_red);
            context.m_Console << "�� ������� ��������� ���������� ����� ��������" << endl;
            context.m_Console.SetTextColor(); // ����� ������� �� ���������
            ICommand* pCmd = context.m_Commands.FindCommand("demo");
            if (pCmd)
            {
                vector<stringEx> dummy;
                pCmd->Execute(&context, dummy);
            }
        }
    }
    context.m_Console << "������� ������� (��������, help)" << endl;
    while (!context.IsExiting())
    {
        context.m_ActiveModel.DrawAll(context.m_Console);
        if (!context.m_Console.SetConsolePos(context.m_Console.CommandLogOutputPos()))
            return false;
        if (!context.m_Console.SetTextColor()) // use default output color
            return false;
        context.m_Console << "> "; // ����������� ������ ��������� �������
        stringEx cmd;
        getline(context.m_Console, OUT cmd);
        vector<stringEx> vWords = cmd.Split(" ", true);
        if (!vWords.size())
            continue;
        // ��������� �������� �������
        ICommand* pCmd = context.m_Commands.FindCommand(vWords[0].c_str());
        if (!pCmd)
        {
            context.m_Console << "����������� �������" << endl;
            continue;
        }
        vWords.erase(vWords.begin());
        pCmd->Execute(&context, vWords);
    }
    CBinStorer storer("myroom.bin");
    if (!context.m_ActiveModel.Store(&storer))
    {
        context.m_Console.SetTextColor(enmColors::black, enmColors::dark_red);
        context.m_Console << "��������: �� ������� ��������� ������������ �������� � ����" << endl;
        context.m_Console.SetTextColor(); // ����� ������� �� ���������
        _getch();
    }
    return 0;
}





