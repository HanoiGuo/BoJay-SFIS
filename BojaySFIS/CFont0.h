// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Windows\\System32\\stdole2.tlb" no_namespace
// CFont0 wrapper class

class CFont0 : public COleDispatchDriver
{
public:
	CFont0(){} // Calls COleDispatchDriver default constructor
	CFont0(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFont0(const CFont0& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// Font methods
public:

	// Font properties
public:
	CString GetName()
	{
		CString result;
		GetProperty(0x0, VT_BSTR, (void*)&result);
		return result;
	}
	void SetName(CString propVal)
	{
		SetProperty(0x0, VT_BSTR, propVal);
	}
	CY GetSize()
	{
		CY result;
		GetProperty(0x2, VT_CY, (void*)&result);
		return result;
	}
	void SetSize(CY &propVal)
	{
		SetProperty(0x2, VT_CY, &propVal);
	}
	BOOL GetBold()
	{
		BOOL result;
		GetProperty(0x3, VT_BOOL, (void*)&result);
		return result;
	}
	void SetBold(BOOL propVal)
	{
		SetProperty(0x3, VT_BOOL, propVal);
	}
	BOOL GetItalic()
	{
		BOOL result;
		GetProperty(0x4, VT_BOOL, (void*)&result);
		return result;
	}
	void SetItalic(BOOL propVal)
	{
		SetProperty(0x4, VT_BOOL, propVal);
	}
	BOOL GetUnderline()
	{
		BOOL result;
		GetProperty(0x5, VT_BOOL, (void*)&result);
		return result;
	}
	void SetUnderline(BOOL propVal)
	{
		SetProperty(0x5, VT_BOOL, propVal);
	}
	BOOL GetStrikethrough()
	{
		BOOL result;
		GetProperty(0x6, VT_BOOL, (void*)&result);
		return result;
	}
	void SetStrikethrough(BOOL propVal)
	{
		SetProperty(0x6, VT_BOOL, propVal);
	}
	short GetWeight()
	{
		short result;
		GetProperty(0x7, VT_I2, (void*)&result);
		return result;
	}
	void SetWeight(short propVal)
	{
		SetProperty(0x7, VT_I2, propVal);
	}
	short GetCharset()
	{
		short result;
		GetProperty(0x8, VT_I2, (void*)&result);
		return result;
	}
	void SetCharset(short propVal)
	{
		SetProperty(0x8, VT_I2, propVal);
	}

};
