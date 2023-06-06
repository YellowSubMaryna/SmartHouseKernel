#include "../stdafx.h"
#include "CmdDemo.h"
#include "../Context.h"
#include "../SmartObjects/RoomObject.h"
#include "../SmartObjects/DoorObject.h"
#include "../SmartObjects/LampObject.h"

bool CCmdDemo::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() > 0)
    {
        pContext->m_Console << "���������������� �������� �������" << endl;
        return false;
    }
    pContext->m_ActiveModel.DestroyAll();
    pContext->m_Console.ReinitConsoleSize(); // ���������� ������ ����������� ����
    COORD size = pContext->m_Console.DrawSpaceSize();
    // ������ ������� ������� - ������������� ���������� �� ������ �������
    CRoomObject* pBigRoom = nullptr;
    bool res = true;
    if (size.X < 10 || size.Y < 10) // ���� ����� ���� - ������ ������ �� ���������
    {
        pBigRoom = new CRoomObject("room", 0, 0, size.X - 1, size.Y - 1);
        return pContext->m_ActiveModel.AddObject(pBigRoom);
    }
    pBigRoom = new CRoomObject("room", 2, 2, size.X - 5, size.Y - 5); // ��������� ������ ��� ������ ������������� ������
    res &= pContext->m_ActiveModel.AddObject(pBigRoom);
    // ��������� ������� ������� ����� ������ (���� ���������� ��� �� �����)
    CRoomObject* pSmallRoom = nullptr;
    if (pBigRoom->Width() > 23 && size.Y > 18)
    {
        pSmallRoom = new CRoomObject("roomsmall", pBigRoom->X() + pBigRoom->Width() - 19,
                                                  pBigRoom->Y() + pBigRoom->Height() - 8,
                                                  19, 8);
        res &= pContext->m_ActiveModel.AddObject(pSmallRoom);
    }

    // ��������� ����� ( ���� ���������� ��� ��� ����� )
    if (pBigRoom->Height() >= 8) // ����� ������
        res &= pContext->m_ActiveModel.AddObject(new CDoorObject("door1", pBigRoom->X(), pBigRoom->Y() + 5, enmDirection::left, false));

    if (pBigRoom->Width() >= 13) // ������� ������
        res &= pContext->m_ActiveModel.AddObject(new CDoorObject("door2", pBigRoom->X() + (pBigRoom->Width() - 4) / 2, 2, enmDirection::up, false));

    if (pBigRoom->Height() - (pSmallRoom ? pSmallRoom->Height() : 0) >= 9) // ������ ������
        res &= pContext->m_ActiveModel.AddObject(new CDoorObject("door3", pBigRoom->X() + pBigRoom->Width(), pBigRoom->Y() + 5, enmDirection::right, false));

    if (pSmallRoom)
    {
        // ���������� ����� � ������� (���� ���� ��������� �������)
        res &= pContext->m_ActiveModel.AddObject(new CDoorObject("door4", pBigRoom->X() + pBigRoom->Width() - 6, pSmallRoom->Y(), enmDirection::up, false));
        // ����� �� ���������� ������� ������
        res &= pContext->m_ActiveModel.AddObject(new CDoorObject("door5", pBigRoom->X() + pBigRoom->Width() - 6, pSmallRoom->Y() + pSmallRoom->Height(), enmDirection::up, false));
    }
    // �����������
    // ��� � ������� �������
    if (size.X >= 13)
        res &= pContext->m_ActiveModel.AddObject(new CLampObject("lamp1", pBigRoom->X() + 4, pBigRoom->Y() + 2, false));
    if (size.X >= 17)
        res &= pContext->m_ActiveModel.AddObject(new CLampObject("lamp2", pBigRoom->X() + pBigRoom->Width() - 4, pBigRoom->Y() + 2, false));
    // ���� � ���������
    if (pSmallRoom)
        res &= pContext->m_ActiveModel.AddObject(new CLampObject("lamp3", pSmallRoom->X() + 4, pSmallRoom->Y() + 2, false));
    pContext->m_ActiveModel.m_MusicContext.ReloadMusicList();
    pContext->m_ActiveModel.m_MusicContext.SelectFirstFile();
    pContext->m_ActiveModel.m_MusicContext.Stop();
    pContext->m_Console << "��������������� ����� �������" << endl;
    return res;
}