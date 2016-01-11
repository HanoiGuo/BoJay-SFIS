// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files\\Teklynx\\CODESOFT 2012\\Lppx2.tlb" no_namespace
// CDocuments wrapper class

class CDocuments : public COleDispatchDriver
{
public:
	CDocuments(){} // Calls COleDispatchDriver default constructor
	CDocuments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDocuments(const CDocuments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// Documents methods
public:
	LPDISPATCH Add(LPCTSTR Key)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Key);
		return result;
	}
	LPDISPATCH Item(VARIANT& Key)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Key);
		return result;
	}
	LPDISPATCH _Item(VARIANT& Key)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Key);
		return result;
	}
	LPDISPATCH Open(LPCTSTR strDocName, BOOL ReadOnly)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BOOL ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strDocName, ReadOnly);
		return result;
	}
	void SaveAll(BOOL AlwaysPrompt)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, AlwaysPrompt);
	}
	void CloseAll(BOOL Save)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Save);
	}
	LPDISPATCH Import(LPCTSTR strDocName, LPCTSTR strFileExt)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strDocName, strFileExt);
		return result;
	}
	LPDISPATCH SelectOpen(LPCTSTR strDocName, long hParent)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strDocName, hParent);
		return result;
	}
	LPDISPATCH OpenFromStream(LPUNKNOWN Stream, LPCTSTR strDocName, BOOL ReadOnly)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_UNKNOWN VTS_BSTR VTS_BOOL ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Stream, strDocName, ReadOnly);
		return result;
	}

	// Documents properties
public:
	short GetCount()
	{
		short result;
		GetProperty(0x1, VT_I2, (void*)&result);
		return result;
	}
	void SetCount(short propVal)
	{
		SetProperty(0x1, VT_I2, propVal);
	}
	IApplication * GetApplication()
	{
		IApplication * result;
		GetProperty(0x2, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetApplication(IApplication * propVal)
	{
		SetProperty(0x2, VT_DISPATCH, propVal);
	}
	LPDISPATCH GetParent()
	{
		LPDISPATCH result;
		GetProperty(0x3, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetParent(LPDISPATCH propVal)
	{
		SetProperty(0x3, VT_DISPATCH, propVal);
	}
	LPUNKNOWN Get_NewEnum()
	{
		LPUNKNOWN result;
		GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&result);
		return result;
	}
	void Set_NewEnum(LPUNKNOWN propVal)
	{
		SetProperty(0xfffffffc, VT_UNKNOWN, propVal);
	}
	CString GetDefaultExt()
	{
		CString result;
		GetProperty(0x4, VT_BSTR, (void*)&result);
		return result;
	}
	void SetDefaultExt(CString propVal)
	{
		SetProperty(0x4, VT_BSTR, propVal);
	}

};
