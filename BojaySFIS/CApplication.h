// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files\\Teklynx\\CODESOFT 2012\\Lppx2.tlb" no_namespace rename("IDocument","IDocumentStr") rename("EOF","rsEOF")
// CApplication wrapper class

class CApplication : public COleDispatchDriver
{
public:
	CApplication(){} // Calls COleDispatchDriver default constructor
	CApplication(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CApplication(const CApplication& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IApplication methods
public:
	void Quit()
	{
		InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH PrinterSystem()
	{
		LPDISPATCH result;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void Resize(long Width, long Height)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Width, Height);
	}
	void Move(long Left, long Top)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Left, Top);
	}
	void ShowHelp(LPCTSTR strHelpFile, long HelpContextID)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strHelpFile, HelpContextID);
	}
	short GetLastError()
	{
		short result;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	CString ErrorMessage(short ErrorCode)
	{
		CString result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ErrorCode);
		return result;
	}
	BOOL Lock(LPCTSTR Key)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Key);
		return result;
	}
	BOOL Unlock(LPCTSTR Key)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Key);
		return result;
	}
	LPDISPATCH VisualManager()
	{
		LPDISPATCH result;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH LabelArchive()
	{
		LPDISPATCH result;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	VARIANT DocumentStatus(LPCTSTR docName)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, docName);
		return result;
	}
	LPDISPATCH FormatSystem()
	{
		LPDISPATCH result;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetDocumentProperties(LPCTSTR docName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x36, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, docName);
		return result;
	}

	// IApplication properties
public:
	BOOL GetVisible()
	{
		BOOL result;
		GetProperty(0x1, VT_BOOL, (void*)&result);
		return result;
	}
	void SetVisible(BOOL propVal)
	{
		SetProperty(0x1, VT_BOOL, propVal);
	}
	BOOL GetUserControl()
	{
		BOOL result;
		GetProperty(0x2, VT_BOOL, (void*)&result);
		return result;
	}
	void SetUserControl(BOOL propVal)
	{
		SetProperty(0x2, VT_BOOL, propVal);
	}
	Documents * GetDocuments()
	{
		Documents * result;
		GetProperty(0x3, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetDocuments(Documents * propVal)
	{
		SetProperty(0x3, VT_DISPATCH, propVal);
	}
	Dialogs * GetDialogs()
	{
		Dialogs * result;
		GetProperty(0x4, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetDialogs(Dialogs * propVal)
	{
		SetProperty(0x4, VT_DISPATCH, propVal);
	}
	LPDISPATCH GetParent()
	{
		LPDISPATCH result;
		GetProperty(0x5, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetParent(LPDISPATCH propVal)
	{
		SetProperty(0x5, VT_DISPATCH, propVal);
	}
	CString GetCaption()
	{
		CString result;
		GetProperty(0x6, VT_BSTR, (void*)&result);
		return result;
	}
	void SetCaption(CString propVal)
	{
		SetProperty(0x6, VT_BSTR, propVal);
	}
	CString GetDefaultFilePath()
	{
		CString result;
		GetProperty(0x7, VT_BSTR, (void*)&result);
		return result;
	}
	void SetDefaultFilePath(CString propVal)
	{
		SetProperty(0x7, VT_BSTR, propVal);
	}
	CString GetFullName()
	{
		CString result;
		GetProperty(0x8, VT_BSTR, (void*)&result);
		return result;
	}
	void SetFullName(CString propVal)
	{
		SetProperty(0x8, VT_BSTR, propVal);
	}
	CString GetName()
	{
		CString result;
		GetProperty(0x9, VT_BSTR, (void*)&result);
		return result;
	}
	void SetName(CString propVal)
	{
		SetProperty(0x9, VT_BSTR, propVal);
	}
	CString Get_Name()
	{
		CString result;
		GetProperty(0x0, VT_BSTR, (void*)&result);
		return result;
	}
	void Set_Name(CString propVal)
	{
		SetProperty(0x0, VT_BSTR, propVal);
	}
	CString GetPath()
	{
		CString result;
		GetProperty(0xa, VT_BSTR, (void*)&result);
		return result;
	}
	void SetPath(CString propVal)
	{
		SetProperty(0xa, VT_BSTR, propVal);
	}
	IApplication * GetApplication()
	{
		IApplication * result;
		GetProperty(0xb, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetApplication(IApplication * propVal)
	{
		SetProperty(0xb, VT_DISPATCH, propVal);
	}
	Options * GetOptions()
	{
		Options * result;
		GetProperty(0xc, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetOptions(Options * propVal)
	{
		SetProperty(0xc, VT_DISPATCH, propVal);
	}
	CString GetVersion()
	{
		CString result;
		GetProperty(0xd, VT_BSTR, (void*)&result);
		return result;
	}
	void SetVersion(CString propVal)
	{
		SetProperty(0xd, VT_BSTR, propVal);
	}
	long GetWidth()
	{
		long result;
		GetProperty(0xe, VT_I4, (void*)&result);
		return result;
	}
	void SetWidth(long propVal)
	{
		SetProperty(0xe, VT_I4, propVal);
	}
	long GetHeight()
	{
		long result;
		GetProperty(0xf, VT_I4, (void*)&result);
		return result;
	}
	void SetHeight(long propVal)
	{
		SetProperty(0xf, VT_I4, propVal);
	}
	long GetLeft()
	{
		long result;
		GetProperty(0x10, VT_I4, (void*)&result);
		return result;
	}
	void SetLeft(long propVal)
	{
		SetProperty(0x10, VT_I4, propVal);
	}
	long GetTop()
	{
		long result;
		GetProperty(0x11, VT_I4, (void*)&result);
		return result;
	}
	void SetTop(long propVal)
	{
		SetProperty(0x11, VT_I4, propVal);
	}
	IDocument * GetActiveDocument()
	{
		IDocument * result;
		GetProperty(0x12, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetActiveDocument(IDocument * propVal)
	{
		SetProperty(0x12, VT_DISPATCH, propVal);
	}
	BOOL GetLocked()
	{
		BOOL result;
		GetProperty(0x13, VT_BOOL, (void*)&result);
		return result;
	}
	void SetLocked(BOOL propVal)
	{
		SetProperty(0x13, VT_BOOL, propVal);
	}
	RecentFiles * GetRecentFiles()
	{
		RecentFiles * result;
		GetProperty(0x14, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetRecentFiles(RecentFiles * propVal)
	{
		SetProperty(0x14, VT_DISPATCH, propVal);
	}
	BOOL GetEnableEvents()
	{
		BOOL result;
		GetProperty(0x15, VT_BOOL, (void*)&result);
		return result;
	}
	void SetEnableEvents(BOOL propVal)
	{
		SetProperty(0x15, VT_BOOL, propVal);
	}
	CString GetActivePrinterName()
	{
		CString result;
		GetProperty(0x16, VT_BSTR, (void*)&result);
		return result;
	}
	void SetActivePrinterName(CString propVal)
	{
		SetProperty(0x16, VT_BSTR, propVal);
	}
	SharedOwner * GetSharedOwner()
	{
		SharedOwner * result;
		GetProperty(0x1e, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetSharedOwner(SharedOwner * propVal)
	{
		SetProperty(0x1e, VT_DISPATCH, propVal);
	}
	long GetMainWndHandle()
	{
		long result;
		GetProperty(0x1f, VT_I4, (void*)&result);
		return result;
	}
	void SetMainWndHandle(long propVal)
	{
		SetProperty(0x1f, VT_I4, propVal);
	}
	BOOL GetIsEval()
	{
		BOOL result;
		GetProperty(0x20, VT_BOOL, (void*)&result);
		return result;
	}
	void SetIsEval(BOOL propVal)
	{
		SetProperty(0x20, VT_BOOL, propVal);
	}
	long GetPID()
	{
		long result;
		GetProperty(0x21, VT_I4, (void*)&result);
		return result;
	}
	void SetPID(long propVal)
	{
		SetProperty(0x21, VT_I4, propVal);
	}
	long GetProgramCode()
	{
		long result;
		GetProperty(0x22, VT_I4, (void*)&result);
		return result;
	}
	void SetProgramCode(long propVal)
	{
		SetProperty(0x22, VT_I4, propVal);
	}
	long GetPrintMode()
	{
		long result;
		GetProperty(0x23, VT_I4, (void*)&result);
		return result;
	}
	void SetPrintMode(long propVal)
	{
		SetProperty(0x23, VT_I4, propVal);
	}
	long GetDisplayPrintMode()
	{
		long result;
		GetProperty(0x24, VT_I4, (void*)&result);
		return result;
	}
	void SetDisplayPrintMode(long propVal)
	{
		SetProperty(0x24, VT_I4, propVal);
	}
	BOOL GetUseUserInterface()
	{
		BOOL result;
		GetProperty(0x25, VT_BOOL, (void*)&result);
		return result;
	}
	void SetUseUserInterface(BOOL propVal)
	{
		SetProperty(0x25, VT_BOOL, propVal);
	}
	ProductInfos * GetProductInfos()
	{
		ProductInfos * result;
		GetProperty(0x26, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetProductInfos(ProductInfos * propVal)
	{
		SetProperty(0x26, VT_DISPATCH, propVal);
	}
	long GetCategory()
	{
		long result;
		GetProperty(0x29, VT_I4, (void*)&result);
		return result;
	}
	void SetCategory(long propVal)
	{
		SetProperty(0x29, VT_I4, propVal);
	}
	long GetSerializationVersion()
	{
		long result;
		GetProperty(0x37, VT_I4, (void*)&result);
		return result;
	}
	void SetSerializationVersion(long propVal)
	{
		SetProperty(0x37, VT_I4, propVal);
	}
	long GetClientWindow()
	{
		long result;
		GetProperty(0x38, VT_I4, (void*)&result);
		return result;
	}
	void SetClientWindow(long propVal)
	{
		SetProperty(0x38, VT_I4, propVal);
	}
	CString GetTxtSettingsCharsStart()
	{
		CString result;
		GetProperty(0x39, VT_BSTR, (void*)&result);
		return result;
	}
	void SetTxtSettingsCharsStart(CString propVal)
	{
		SetProperty(0x39, VT_BSTR, propVal);
	}
	CString GetTxtSettingsCharsEnd()
	{
		CString result;
		GetProperty(0x3a, VT_BSTR, (void*)&result);
		return result;
	}
	void SetTxtSettingsCharsEnd(CString propVal)
	{
		SetProperty(0x3a, VT_BSTR, propVal);
	}
	LogFile * GetLogFile()
	{
		LogFile * result;
		GetProperty(0x3b, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetLogFile(LogFile * propVal)
	{
		SetProperty(0x3b, VT_DISPATCH, propVal);
	}

};
