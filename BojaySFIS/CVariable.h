// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files\\Teklynx\\CODESOFT 2012\\Lppx2.tlb" no_namespace
// CVariable wrapper class

class CVariable : public COleDispatchDriver
{
public:
	CVariable(){} // Calls COleDispatchDriver default constructor
	CVariable(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVariable(const CVariable& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// Variable methods
public:
	long ShowDialog(long hParent)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hParent);
		return result;
	}

	// Variable properties
public:
	CString GetName()
	{
		CString result;
		GetProperty(0x1, VT_BSTR, (void*)&result);
		return result;
	}
	void SetName(CString propVal)
	{
		SetProperty(0x1, VT_BSTR, propVal);
	}
	CString GetValue()
	{
		CString result;
		GetProperty(0x2, VT_BSTR, (void*)&result);
		return result;
	}
	void SetValue(CString propVal)
	{
		SetProperty(0x2, VT_BSTR, propVal);
	}
	CString Get_Value()
	{
		CString result;
		GetProperty(0x0, VT_BSTR, (void*)&result);
		return result;
	}
	void Set_Value(CString propVal)
	{
		SetProperty(0x0, VT_BSTR, propVal);
	}
	long GetDataSource()
	{
		long result;
		GetProperty(0x3, VT_I4, (void*)&result);
		return result;
	}
	void SetDataSource(long propVal)
	{
		SetProperty(0x3, VT_I4, propVal);
	}
	LPDISPATCH GetParent()
	{
		LPDISPATCH result;
		GetProperty(0x4, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetParent(LPDISPATCH propVal)
	{
		SetProperty(0x4, VT_DISPATCH, propVal);
	}
	IApplication * GetApplication()
	{
		IApplication * result;
		GetProperty(0x5, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetApplication(IApplication * propVal)
	{
		SetProperty(0x5, VT_DISPATCH, propVal);
	}
	CString GetDisplayValue()
	{
		CString result;
		GetProperty(0x7, VT_BSTR, (void*)&result);
		return result;
	}
	void SetDisplayValue(CString propVal)
	{
		SetProperty(0x7, VT_BSTR, propVal);
	}
	long GetIncludeInLogFile()
	{
		long result;
		GetProperty(0x8, VT_I4, (void*)&result);
		return result;
	}
	void SetIncludeInLogFile(long propVal)
	{
		SetProperty(0x8, VT_I4, propVal);
	}
	long GetLength()
	{
		long result;
		GetProperty(0x9, VT_I4, (void*)&result);
		return result;
	}
	void SetLength(long propVal)
	{
		SetProperty(0x9, VT_I4, propVal);
	}
	long GetAutoLength()
	{
		long result;
		GetProperty(0xa, VT_I4, (void*)&result);
		return result;
	}
	void SetAutoLength(long propVal)
	{
		SetProperty(0xa, VT_I4, propVal);
	}

};
