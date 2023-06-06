#include "../stdafx.h"
#include "LampObject.h"
#include "../Storage/_Storer.h"
#include "../Storage/_Loader.h"
#include <iostream>
#include <sstream>
using namespace std;

CLampObject::CLampObject(const char* psName, int x, int y, bool isOn)
    : CBaseObject(psName),
      m_X(x),
      m_Y(y),
      m_isOn(isOn)
{
}


CLampObject::~CLampObject()
{
}

bool CLampObject::InputParams(CConsoleManip& console)
{
    console << "������� ��������� ����������� X Y ������������ ������ �������� ���� �������: ";
    console >> m_X >> m_Y;
    if (!console)
    {
        console.ClearErrorFlag();
        console << "������� ������������ ���������" << endl;
        return false;
    }
    if (m_X < 0 || m_X >= console.DrawSpaceSize().X ||
        m_Y < 0 || m_Y >= console.DrawSpaceSize().Y)
    {
        console << "�������� ���������� ��������� ��� �������" << endl;
        console << "������ ������������ ��� �����������:";
        console << console.DrawSpaceSize().X << " " <<
                   console.DrawSpaceSize().Y << endl;
        return false;
    }
    m_isOn = false;
    return true;
}

bool CLampObject::Draw(CConsoleManip& console) const
{
    if (!m_isOn)
        return console.DrawTextMultiline(m_X, m_Y, "o");
    else
        return console.DrawTextMultiline(m_X - 2, m_Y - 1, "\\ | /\n"
                                                            "--O--\n"
                                                            "/ | \\",
                                   enmColors::light_yellow, enmColors::dark_yellow);
}
bool CLampObject::Store(IStorer* pStorer) const
{
    if (!CBaseObject::Store(pStorer))
        return false;
    return pStorer->Store(m_X) &&
        pStorer->Store(m_Y) &&
        pStorer->Store(m_isOn);
}
bool CLampObject::Load(ILoader* pLoader)
{
    if (!CBaseObject::Load(pLoader) ||
        !pLoader->Load(OUT m_X) ||
        !pLoader->Load(OUT m_Y) ||
        !pLoader->Load(OUT m_isOn))
        return false;
    return true;
}

void CLampObject::SwitchOn()
{
    m_isOn = true;
}
void CLampObject::SwitchOff()
{
    m_isOn = false;
}

void CLampObject::PrintProperties(CConsoleManip& console) const
{
    CBaseObject::PrintProperties(console);
    console << "X: " << m_X << ", Y: " << m_Y << endl;
    console << "���������: " << (m_isOn ? "���� �������" : "���� ��������") << endl;
}
