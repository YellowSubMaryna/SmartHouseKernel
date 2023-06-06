#include "../stdafx.h"
#include "CmdMusicPosition.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "../Context.h"
using namespace std;

bool CCmdMusicPosition::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() > 1)
    {
        pContext->m_Console << "���������������� �������� �������" << endl;
        return false;
    }
    if (vParameters.size() == 0) // ������ �������
    {
        pContext->m_Console << "������� ������� ��������������:" << endl;
        double position = round(pContext->m_ActiveModel.m_MusicContext.Position() / 100.0) / 10;
        pContext->m_Console << position << endl;
        return true;
    }
    // ������ �������
    stringstream str(vParameters[0]);
    double pos = 0;
    str >> pos;
    if (!str || str.rdbuf()->in_avail())
    {
        pContext->m_Console.SetTextColor(enmColors::black, enmColors::dark_red);
        pContext->m_Console << "�� ������� ���������� �������� ������� ���������������" << endl;
        return false;
    }
    pContext->m_ActiveModel.m_MusicContext.Position((int)round(pos * 1000));
    return true;
}
