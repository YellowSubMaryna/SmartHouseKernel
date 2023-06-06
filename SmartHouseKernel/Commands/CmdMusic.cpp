#include "../stdafx.h"
#include "CmdMusic.h"
#include <iostream>
#include "../Context.h"
using namespace std;

std::string CCmdMusic::Help(CContext* pContext, const vector<stringEx>& vParameters)
{
    if (!vParameters.size())
        return "�������������:\n"
               "music play\n"
               "music stop\n"
               "music next\n"
               "music rewind\n"
               "music reload\n"
               "music list\n";
    if (vParameters.size() == 1)
    {
        stringEx par(vParameters[0]);
        par.strlwr(); // ���������� ��������� ��� ����� ��������
        if (par == "play")
            return "�������� ��������������� ������������ �����.\n"
                   "�������������:\n"
                   "music play\n";
        if (par == "stop")
            return "��������� ��������������� ������������ �����.\n"
                   "�������������:\n"
                   "music stop\n";
        if (par == "next")
            return "������� � ��������������� ���������� ������������ �����.\n"
                   "�������������:\n"
                   "music next\n";
        if (par == "rewind")
            return "������ ��������������� �������� ����� � ������.\n"
                   "�������������:\n"
                   "music rewind\n";
        if (par == "reload")
            return "���������� ������ ����������� ������ � �����.\n"
                   "�������������:\n"
                   "music reload\n";
        if (par == "list")
            return "������� ������ ��������� ����������� ������.\n"
                   "�������������:\n"
                   "music list\n";
    }
    return ICommand::Help(pContext, vParameters); // ����������� ��������� �� ��������� �������� ��� ����������� ������ ����������
}

bool CCmdMusic::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() == 0)
    {
        // ���� ��������� �� ������� - ��������� ���������
        Help(pContext, vector<stringEx>());
        return false;
    }
    stringEx par(vParameters[0]);
    par.strlwr(); // ���������� ��������� ��� ����� ��������
    if (par == "play")
    {
        // ��� ������� ������������ ������ ��������� ������ (���-�� � ���������� SDL)
        // ������� � �������, ���� ��� �����
        pContext->m_Console.SetTextColor(enmColors::black, enmColors::dark_red);
        pContext->m_ActiveModel.m_MusicContext.Play();
        return true;
    }
    if (par == "stop")
    {
        pContext->m_ActiveModel.m_MusicContext.Stop();
        return true;
    }
    if (par == "next")
    {
        if (!pContext->m_ActiveModel.m_MusicContext.SelectNextFile())
        {
            pContext->m_Console.SetTextColor(enmColors::black, enmColors::dark_red); // ������� ������ �������
            pContext->m_Console << "������ ��� ������� ������������� ����" << endl;
            return false;
        }
        return true;
    }
    if (par == "rewind")
    {
        pContext->m_ActiveModel.m_MusicContext.Position(0);
        return true;
    }
    if (par == "reload")
    {
        pContext->m_ActiveModel.m_MusicContext.ReloadMusicList();
        pContext->m_ActiveModel.m_MusicContext.PrintAvailableMusics(pContext->m_Console);
        return true;
    }
    if (par == "list")
    {
        pContext->m_ActiveModel.m_MusicContext.PrintAvailableMusics(pContext->m_Console);
        return true;
    }

    // ������ ������������ �������� �������
    pContext->m_Console << "���������������� �������� �������" << endl;
    return false;
}