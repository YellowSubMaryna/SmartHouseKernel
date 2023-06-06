#include "../stdafx.h"
#include "CmdVolume.h"
#include <iostream>
#include "../Context.h"
using namespace std;

bool CCmdVolume::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() > 1)
    {
        pContext->m_Console << "���������������� �������� �������" << endl;
        return false;
    }
    if (vParameters.size() == 0) // ���������� ������� ���������
    {
        pContext->m_Console << "������� ���������:" << endl
                            << pContext->m_ActiveModel.m_MusicContext.Volume() << endl;
        return true;
    }
    int volume = atoi(vParameters[0].c_str());
    if (volume < 0 || volume > MIN_MAX_VOLUME)
    {
        pContext->m_Console << "������������ ������� ���������. ���������� �������: 0 - 128" << endl;
        return false;
    }
    pContext->m_ActiveModel.m_MusicContext.Volume(volume);
    return true;
}
