#include "pch.h"
#include "Search.h"
#include<io.h>
Search::Search()
{
	InitSearch();
}
Search::~Search()
{

}

bool Search::InitSearch()
{
	Everything_SetRequestFlags(EVERYTHING_REQUEST_FILE_NAME | EVERYTHING_REQUEST_PATH | EVERYTHING_REQUEST_SIZE);
	Everything_SetSort(EVERYTHING_SORT_SIZE_DESCENDING);
	return true;
}
std::vector<WeChatResult> Search::SearchExe()
{
	std::vector<string> VPath = GetPath("WeChat Files","Applet");
	VPath.clear(); VPath.emplace_back("E:\\Syudy_Test\\WeChatTest\\ttt");
	std::vector<string> VAllUser, temp;
	for each(string path in VPath) 
	{
		temp.clear();
		LoadAllUserPath(path.c_str(), "FileStorage", temp);
		VAllUser.insert(VAllUser.end(),temp.begin(),temp.end());
	}
	//std::vector<string> VUserPath = GetPath("FileStorage", "Image");
	std::vector<WeChatResult> vresult;
	for each(string path in VAllUser)
	{
		WeChatResult res;
		res.RootPath = path;
		int rt = path.rfind("\\");
		res.UserName = path.substr(rt+2);
		string filepath = path + "\\FileStorage\\File";
		LoadAllFile(filepath.c_str(), res.vFilePath);
		filepath = path + "\\FileStorage\\Image";
		LoadAllFile(filepath.c_str(), res.vImagePath);
		filepath = path + "\\FileStorage\\Video";
		LoadAllFile(filepath.c_str(), res.vVideoPath);

		vresult.emplace_back(res);
	}
	return vresult;
}
std::vector<SearchResult> Search::SearchExe(SearchParams Params)
{	
	std::vector<SearchResult> vresult;
	Everything_SetSearch(Params.searchStr);
	Everything_Query(TRUE);
	UINT num = Everything_GetNumResults();
	for (DWORD i = 0; i < Everything_GetNumResults(); i++)
	{
		SearchResult res;
		res.Path =Everything_GetResultPath(i);
		res.IsFile = false;
		if (res.Path.find(Params.excludeStr) == res.Path.npos || strlen(Params.excludeStr)==0){
			if (Everything_IsFileResult(i)) {
				try {
					res.Name = Everything_GetResultFileName(i);
					Everything_GetResultSize(i, &res.size);
					res.IsFile = true;
				}
				catch (std::exception &e) {
					AfxMessageBox(e.what());					
				}
			}
			
			res.Path += "\\";
			res.Path += res.Name;
			vresult.emplace_back(res);
		}
	}
	return vresult;
}
void Search::LoadAllUserPath(const char* rootPath,const char* subPathName, std::vector<string>& vresult)
{
	string str = "";
	char TempPath[MAX_PATH];
	char path[MAX_PATH];
	sprintf_s(TempPath, "%s\\", rootPath);//mImagePathÎÄ¼þ¼ÐÂ·¾¶
	sprintf_s(path, "%s\\*.*", rootPath);
	
	WIN32_FIND_DATA FindFileData;

	HANDLE hFind = ::FindFirstFile(path, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)  return;

	while (true)
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (FindFileData.cFileName[0] != '.'/* && false*/)
			{
				str = TempPath;
				str.append(FindFileData.cFileName);
				if (strlen(subPathName) == 0) 
				{
					LoadAllUserPath(str.c_str(), "", vresult);
				}
				else if (IsDirHaveFolder(str, subPathName))
					vresult.emplace_back(str);
			}			
		}
		else if(strlen(subPathName) == 0)
		{
			str = TempPath;
			str.append(FindFileData.cFileName);
			vresult.emplace_back(str);
		}
		if (!FindNextFile(hFind, &FindFileData))  break;
	}
	FindClose(hFind);
}
void Search::LoadAllFile(const char* rootPath, std::vector<PathInfo>& vresult)
{
	std::vector<string> temp;
	LoadAllUserPath(rootPath, "", temp);
	for each(string tp in temp)
	{
		PathInfo info;
		int rt = tp.rfind("\\");
		info.FileName = tp.substr(rt + 1);

		int lt = tp.find("\\", strlen(rootPath));
		info.Date = tp.substr(lt + 1, rt-lt-1);
		
		info.Path = tp;
		vresult.emplace_back(info);
	}
}
std::vector<string> Search::GetPath(string PathName, string subPathName)
{
	std::vector<string> vresult;
	string str = "folder: ww:" + PathName;
	Everything_SetSearch(str.c_str());
	Everything_Query(TRUE);
	UINT num = Everything_GetNumResults();
	for (DWORD i = 0; i < Everything_GetNumResults(); i++)
	{
		string rootpath = Everything_GetResultPath(i);
		rootpath += "\\"+ PathName;
		if(IsDirHaveFolder(rootpath, subPathName))
			vresult.emplace_back(rootpath);		
	}
	return vresult;
}

bool Search::IsDirHaveFolder(string Dir, string FolderName)
{
	string path = Dir + "\\" + FolderName;
	if (0 == _access(path.c_str(), 00))
	{
		return true;
	}
	return false;
}