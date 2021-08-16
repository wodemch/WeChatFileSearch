#pragma once

#include<vector>
#include<string>
#include ".\Everything-SDK\include\Everything.h"

#ifdef _WIN64
#pragma comment(lib, "./Everything-SDK/lib/Everything64.lib")
#else
#pragma comment(lib, "./Everything-SDK/lib/Everything32.lib")
#endif

using namespace std;

#define MAX_SEARCH_LENGHT 256
struct SearchParams
{
	char searchStr[MAX_SEARCH_LENGHT];
	char excludeStr[MAX_SEARCH_LENGHT];
};

struct PathInfo
{
	string FileName;
	string Path;
	string Date;
};

struct WeChatResult
{
	string UserName;
	// userName/FileStorage
	string RootPath;
	vector<PathInfo> vFilePath;
	vector<PathInfo> vImagePath;
	vector<PathInfo> vVideoPath;
};

struct SearchResult
{
	std::string Path;
	std::string Name;
	LARGE_INTEGER size;
	bool IsFile;
};

class Search
{
public:
	Search();
	~Search();	

	bool InitSearch();
	std::vector<SearchResult> SearchExe(SearchParams Params);
	std::vector<WeChatResult> SearchExe();

private:
	//����rootPath�ļ����� ����subPathName�������ļ���·��
	void LoadAllUserPath(const char* rootPath, const char* subPathName, std::vector<string>& vresult);
	//��ȡrootPath·���µ�ȫ���ļ�
	void LoadAllFile(const char* rootPath,std::vector<PathInfo>& vresult);
	//���Ұ���subPathName�ļ��� ����PathName�������ļ���·��
	std::vector<string> GetPath(string PathName, string subPathName);
	//�ж� DirĿ¼���Ƿ����FolderName�ļ���
	bool IsDirHaveFolder(string Dir, string FolderName);
};

