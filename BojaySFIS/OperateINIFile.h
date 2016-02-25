#pragma once
#include <string>
#include <vector>
using namespace std;
class COperateINIFile
{
public:
	COperateINIFile(void);
	~COperateINIFile(void);
public:
	bool GetAllSerialNum(char *filePath,vector<string>&allItem,CString &cErrorMessage);
	bool GetTestItem(char *filePath,string *itemName,CString &cErrorMessage);
	bool GetPassword(char *filePath,CString &password,CString &cErrorMessage);
	bool CreateTestItemToServer(const char *filePath,vector<CString>strItem, CString &cErrorMessage);
	bool CheckAuthority(int caseNum, CString name, CString serialNum,bool isRoot=false);
	bool CheckDataisBusy(char *filePath,int mode,CString &message);
	bool CheckCustomer(char *filePath ,vector<CString>&customer);
	bool GetAllDataBaseName(char *filePath ,vector<string>&files);
	bool CheckDeliveryLocation(char *filePath ,vector<CString>&deliveryLocation);
	bool CheckIsBindSoundTestTool(char *filePath,string &result);
	bool CheckName(char *filePath,string id,CString &name);
	bool GetProductName(char *filePath,vector<CString>&productName);
	bool GetWhatYouNeed(char *filePath,CString productname,char *keyWord,vector<CString>&result);
};

