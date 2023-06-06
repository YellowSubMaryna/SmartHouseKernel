#pragma once

#include "../Storage/_Loader.h"
#include "../Storage/_Storer.h"
#include <vector>
#include <filesystem>
using namespace std;

#define MIN_MAX_VOLUME 128

class CConsoleManip;

class CMusicContext
{
private:
    vector<string> m_vsFiles; // ������ ��������� ��� ��������������� ������
    vector<std::filesystem::path> m_vsDirectories; 
    int m_iCurFile; // ����� �������� �������������� ����� � m_vsFiles
    void* m_pMusic; // ���������� ���������� SDL ��� ������� �������
    DWORD m_nMusicStartTime; // ������ ������� �������, ��������� ��� ���������� ���������� ����� ��������� ����������
                             // ���� ������ ������������ ��������� ��������� SDL �� ��������� �������� ������� ������� ������������ - ������� � ���� �� ������� ����� ��������� ������������
    DWORD m_nMusicPauseTime; // ������ ����� ��������� ������������ �� �����

    bool m_isPlaying; // ������� ��� ������� ���� �������� �� ���������������(��� ���� ��� ����� ������ ��� ������ �� �����)
    bool m_isPaused; // �� ������������� ���������������, � ������ �� �����, ����� ����� ������� play ���������� � ��� �� �������
    int m_Volume;

    CMusicContext(const CMusicContext&) = delete;
    void operator=(const CMusicContext&) = delete;

    // ������������� ������ ��������� �������
    // �� �������� music
    bool ReloadCurFile();
    void UnloadCurFile();
    void OnFinishMusicPlay();        // ��������� ������� ��� ����������� ������� � �������� �� ���� ��������� ����� ����� ������
    friend void OnFinishMusicPlay(); // ����������� ������� ��� �������� � �������� ����������� ������� � ���������� SDL
public:
    CMusicContext();
    ~CMusicContext();
    bool isPlaying();
    bool Play();
    bool Stop();
    int Volume() const;
    void Volume(int newVolume);
    int Position() const; // ������� ������������� ������� ������� � ������������
    void Position(int newPositionMs); // ���������� ������� �� ��������� � ������������ �������
    bool SelectNextFile(); // ������� � ������������ ���������� �����
    bool SelectFirstFile(); // ������� � ������� �����
    void PrintAvailableMusics(CConsoleManip& cons) const;
    void ReloadMusicList();
    bool AddDirectory2Playlist(string path);
    bool RemoveDirectoryPlaylist(string path);

    bool Store(IStorer* pStorer);
    bool Load(ILoader* pLoader);
};

