#include "StdAfx.h"
#include "OperateINIFile.h"
#include <fstream>
#include <iostream>
#include <io.h>
#include <string>
#include <vector>

using namespace std;
COperateINIFile::COperateINIFile(void)
{
}


COperateINIFile::~COperateINIFile(void)
{
}


bool COperateINIFile::GetTestItem(char *filePath,string *itemName,CString &cErrorMessage)
{
	if(access(filePath,0))
	{
		cErrorMessage = "û�в�����Ŀ�ļ�";
		return false;
	}

	ifstream itemFile(filePath);
	
	int i=0;
	while(getline(itemFile,itemName[i]))
	{
		i++;
	}
	cErrorMessage = "�ɹ�";
	itemFile.close();
	return true;
}

bool COperateINIFile::GetPassword(char *filePath,CString &password,CString &cErrorMessage)
{
	if(access(filePath,0))
	{
		cErrorMessage = "û�������ļ�";
		return false;
	}

	ifstream passwordFile(filePath);
	string tempPassword,sumStr;
	while(getline(passwordFile,tempPassword))
	{
		sumStr += tempPassword;
	}
	password = sumStr.c_str();
	cErrorMessage = "�ɹ�";
	passwordFile.close();
	return true;
}


bool COperateINIFile::CreateTestItemToServer(const char *filePath,vector<CString>strItem, CString &cErrorMessage)
{
	fstream testItemOut(filePath,ios::out);
	if (testItemOut.is_open())
	{
		for (int i=0; i<strItem.size(); i++)
		{
			string test = CStringA(strItem.at(i));
			testItemOut << test << endl;
		}
	}
	else
	{
		cErrorMessage = "����������Ŀ�ļ�ʧ�ܣ�����ϵ����ʦ";
		return false;
	}
	return true;
}


bool COperateINIFile::GetAllSerialNum(char *filePath,vector<string>&allItem,CString &cErrorMessage)
{
	if(access(filePath,0))
	{
		cErrorMessage = "û�����������ļ�";
		return false;
	}
	ifstream allwordFile(filePath);
	string temp;
	while(getline(allwordFile,temp))
	{
		if (temp.length() > 3)
		{
			allItem.push_back(temp);
		}
	}
	cErrorMessage = "�ɹ�";
	allwordFile.close();
	return true;
}

bool COperateINIFile::CheckAuthority(int caseNum, CString name, CString serialNum,bool isRoot)
{
	string checkStr = CStringA(name +  L"-"+ serialNum);
	char path[256] = {0};
	if (isRoot)
	{
		switch(caseNum)
		{
		case 0: //�������
			strcpy(path,"\\\\172.20.0.8\\1.��˾��������\\���������������\\����Ȩ��\\ActiveAuthority.dat");
			break;
		case 1://��ӡ��ά��
			strcpy(path,"\\\\172.20.0.8\\1.��˾��������\\���������������\\����Ȩ��\\QRAuthority.dat");
			break;
		case 2://���ܲ���
			strcpy(path,"\\\\172.20.0.8\\1.��˾��������\\���������������\\����Ȩ��\\SoundAuthority.dat");
			break;
		case 3://palletid
			strcpy(path,"\\\\172.20.0.8\\1.��˾��������\\���������������\\����Ȩ��\\PalletIDAuthority.dat");
			break;
		case 4://����
			strcpy(path,"\\\\172.20.0.8\\1.��˾��������\\���������������\\����Ȩ��\\ShipAuthority.dat");
			break;
		case 5://OQC
			strcpy(path,"\\\\172.20.0.8\\1.��˾��������\\���������������\\����Ȩ��\\OQCAuthority.dat");
			break;
		case 6://PCBA
			strcpy(path,"\\\\172.20.0.8\\1.��˾��������\\���������������\\����Ȩ��\\PCBAAuthority.dat");
			break;
		}
	}
	else
	{
		switch(caseNum)
		{
		case 0: //�������
			strcpy(path,"\\\\172.20.0.8\\1.��˾��������\\���������������\\Ȩ��\\ActiveAuthority.dat");
			break;
		case 1://��ӡ��ά��
			strcpy(path,"\\\\172.20.0.8\\1.��˾��������\\���������������\\Ȩ��\\QRAuthority.dat");
			break;
		case 2://���ܲ���
			strcpy(path,"\\\\172.20.0.8\\1.��˾��������\\���������������\\Ȩ��\\SoundAuthority.dat");
			break;
		case 3://palletid
			strcpy(path,"\\\\172.20.0.8\\1.��˾��������\\���������������\\Ȩ��\\PalletIDAuthority.dat");
			break;
		case 4://����
			strcpy(path,"\\\\172.20.0.8\\1.��˾��������\\���������������\\Ȩ��\\ShipAuthority.dat");
			break;
		case 5://OQC
			strcpy(path,"\\\\172.20.0.8\\1.��˾��������\\���������������\\Ȩ��\\OQCAuthority.dat");
			break;
		case 6://PCBA
			strcpy(path,"\\\\172.20.0.8\\1.��˾��������\\���������������\\Ȩ��\\PCBAAuthority.dat");
			break;
		}
	}
	if(access(path,0))
	{
		return false;
	}
	fstream fileAuthority(path,ios::in);
	string temp;
	vector<string>tempStr;
	while(getline(fileAuthority,temp))
	{
		tempStr.push_back(temp);
	}
	bool isOK = false;
	for (int i=0; i<tempStr.size(); i++)
	{
		if (strstr(tempStr.at(i).c_str(),checkStr.c_str()))
		{
			isOK = true;
			break;
		}
	}
	if (!isOK)
	{
		return false;
	}
	return true;
}


bool COperateINIFile::CheckDataisBusy(char *filePath,int mode,CString &message)
{
	CString temp;
	switch(mode)
	{
	case 0:
		temp = L"�������";
		break;
	case 1:
		temp = L"��ӡ����";
		break;
	case 2:
		temp = L"���ܲ���";
		break;
	case 3:
		temp = L"OQC����";
		break;
	case 4:
		temp = L"PalletID����";
		break;
	case 5:
		temp = L"��������";
		break;
	case 6:
		temp = L"PCBA����";
		break;
	case 7:
		temp = L"��ѯ����";
		break;
	}
	if(access(filePath,0))
	{
		fstream out(filePath,ios::out);
		if (out.is_open())
		{
			string str;
			str = CStringA(temp);
			out << str;
		}
		else
		{
			message = L"�����ļ�ʧ��";
			return false;
		}
	}
	else
	{
		message.Format(L"%s���ݿ��������ڹ���",temp);
		return false;
	}

	return true;
}

bool COperateINIFile::CheckCustomer(char *filePath ,vector<CString>&customer)
{
	if(access(filePath,0))
	{
		return false;
	}
	fstream customerFile(filePath,ios::in);
	string temp;
	CString csTemp;
	while(getline(customerFile,temp))
	{
		csTemp = temp.c_str();
		customer.push_back(csTemp);
	}
	customerFile.close();
	return true;
}

bool COperateINIFile::GetAllDataBaseName(char *path ,vector<string>&files)
{
	//�ļ����
	long   hFile   =   0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
	{
		do
		{
			//�����Ŀ¼,����֮
			//�������,�����б�
			if((fileinfo.attrib &  _A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
				{
					char filePath[256] = {0};
					strcpy(filePath,p.assign(path).append("\\").append(fileinfo.name).c_str());
					GetAllDataBaseName(filePath,files );
				}
			}
			else
			{
				string temp = p.assign(path).append("\\").append(fileinfo.name);
				int nPos = temp.find_last_of("\\");
				temp = temp.substr(nPos+1);
				if (strstr(temp.c_str(),"mdb"))
				{
					files.push_back(temp);
				}
			}
		}while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}

	return true;
}

bool COperateINIFile::CheckDeliveryLocation(char *filePath ,vector<CString>&deliveryLocation)
{
	if(access(filePath,0))
	{
		return false;
	}
	fstream customerFile(filePath,ios::in);
	string temp;
	CString csTemp;
	while(getline(customerFile,temp))
	{
		if (strstr(temp.c_str(),"APG") || strstr(temp.c_str(),"FT") || strstr(temp.c_str(),"MS"))
		{
			csTemp = temp.c_str();
			deliveryLocation.push_back(csTemp);
		}
	}
	customerFile.close();
	return true;
}

bool COperateINIFile::CheckIsBindSoundTestTool(char *filePath,string &result)
{
	if(access(filePath,0))
	{
		return false;
	}
	fstream customerFile(filePath,ios::in);
	string temp;
	CString csTemp;
	while(getline(customerFile,temp))
	{
		csTemp = temp.c_str();
		csTemp.MakeUpper();
		if (_tcsstr(csTemp,L"TRUE") || _tcsstr(csTemp,L"FALSE"))
		{
			result += temp;
		}
	}
	return true;
}

bool COperateINIFile::CheckName(char *filePath,string id,CString &name)
{
	if(access(filePath,0))
	{
		return false;
	}
	fstream nameFile(filePath,ios::in);
	string temp;
	string tempID;
	int index = 0;
	if (nameFile.is_open())
	{
		while(getline(nameFile,temp))
		{
			index = temp.find("-");
			tempID = temp.substr(index+1,temp.length());
			if (tempID == id)
			{
				name = temp.substr(0,index).c_str();
				return true;
			}
		}
	}
	else
	{
		return false;
	}
	return false;
}


bool COperateINIFile::GetProductName(char *filePath,vector<CString>&productName)
{
	if(access(filePath,0))
	{
		return false;
	}
	fstream nameFile(filePath,ios::in);
	string str;
	CString csStr;
	if (nameFile.is_open())
	{
		while(getline(nameFile,str))
		{
			csStr = str.c_str();
			productName.push_back(csStr);
		}
	}
	else
	{
		nameFile.close();
		return false;
	}
	nameFile.close();
	return true;
}

bool COperateINIFile::GetWhatYouNeed(char *filePath,CString productname,char *keyWord,vector<CString>&result)
{
	if(access(filePath,0))
	{
		return false;
	}
	fstream nameFile(filePath,ios::in);
	string strProductNmae = CStringA(productname);
	string str;
	CString csStr;
	string temp;
	int index = 0;
	string tempProducdname;
	if (nameFile.is_open())
	{
		while(getline(nameFile,str))
		{
			int index = str.find(":");
			tempProducdname = str.substr(0,index);
			if (tempProducdname == strProductNmae)
			{
				if (strstr(str.c_str(),keyWord))
				{
					index = str.find("=");
					temp = str.substr(index+1,str.length());
					csStr = temp.c_str();
					result.push_back(csStr);
				}
			}
		}
	}
	else
	{
		nameFile.close();
		false;
	}
	nameFile.close();
	return true;
}