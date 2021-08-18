#pragma once

#ifdef _DLL_EXPORTS
#define DLL_API _declspec(dllexport)
#else
#define DLL_API _declspec(dllimport)
#endif

#include<vector>
#include<string>
using namespace std;

#pragma region file and folder operation

/*
*����Dir·�����Ƿ����FolderName�ļ���
*params
*Dir ��Ŀ¼
*FolderName ָ���ļ�������
*/
DLL_API bool MT_IsDirHaveFolder(string Dir, string FolderName);

/*
*����rootPath�ļ����� ����subPathName�������ļ���·��,������vresult��,��subPathName����Ϊ0ʱ������ҵ������ļ���
*params
*rootPath ��Ŀ¼
*vresult ���ؽ��
*bSub �Ƿ�������ļ���
*subPathName ɸѡĿ¼ ���ִ�Сд
*/
DLL_API void MT_LoadAllPath(const char* rootPath, std::vector<string>& vresult,bool bSub=true, const char* subPathName="");

/*
*����rootPath�ļ����������ļ�,������vresult��
*params
*rootPath ��Ŀ¼
*vresult ���ؽ��
*bSub �Ƿ�������ļ���
*suffix �ļ����˺�׺ �����'|'��� "jpg|png|bmp",�����ļ�ʱ��Ч
*/
DLL_API void MT_LoadAllFile(const char* rootPath, std::vector<string>& vresult, bool bSub = true, const char* suffix = "");


/*
*�ж��ļ����ļ����Ƿ����
*params
*path ·������
*bCreate ������ʱ�Ƿ񴴽�
*/
DLL_API bool MT_IsExist(const char* path, bool bCreate = false);

/*
*�޸��ļ���
*params
*return 0 �ɹ���-1 ʧ��
*/
DLL_API int MT_Rename(const char* oldFile, const char* newFile);

/*
*ɾ���ļ� �ļ���
*params
*return 0 ʧ�ܣ����� �ɹ�
*/
DLL_API int MT_Delete(const char* File);

/*
*ͬ���ļ����ļ���
*params
*bFailIfExists true ���ڻ�ʧ�ܣ�false �������޸�
*return 0 ʧ�ܣ����� �ɹ�
*/
DLL_API int MT_CopyFile(const char* oldF, const char* newF,bool bFailIfExists=false);

/*
*ѡ���ļ���
*params
*path ����·�� 
*/
DLL_API bool MT_SelectFolder(string& path);

/*
*ѡ���ļ�
*params
*path ����·��
*lpszFilter �ļ����� BMP Files (*.bmp)|*.bmp|JPG Files (*.jpg)
*all_sel_files ����vectorʱ  ��ѡ����
*/
DLL_API bool MT_SelectFile(string& path, const char* lpszFilter = NULL);
DLL_API bool MT_SelectFile(vector<string>& all_sel_files, const char*  lpszFilter = NULL);

#pragma endregion

#pragma region exe operation

enum EM_StartFlag
{
	SF_NO=0,//��
	SF_RESTART,//����
	SF_OPENMORE,//�࿪
};

enum EM_CmdType
{
	CT_KillExe = 0,	//��������
	CT_Mkdir,		//����Ŀ¼
	CT_OPEN,		//��Ŀ¼���ļ�		
};

/*
*����exe
*params
*exePath exe·��
*Flag ������־
*cmdParam �����в���
*workDir ����Ŀ¼
*/
DLL_API bool MT_StartExe(string exePath, EM_StartFlag Flag = SF_NO, string cmdParam = "", string workDir = "");

/*
*�رս���
*params
*exeName exe����
*/
DLL_API bool MT_KillExe(string exeName);

/*
*ִ��cmd����
*params
*type EM_CmdType
*params exe����
*/
DLL_API bool MT_CmdOrder(EM_CmdType type, string params);

#pragma endregion

/*
*
*params
*/
//DLL_API