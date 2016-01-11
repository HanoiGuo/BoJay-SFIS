// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files\\Teklynx\\CODESOFT 2012\\Lppx2.tlb" no_namespace
// CFormVariables wrapper class

class CFormVariables : public COleDispatchDriver
{
public:
	CFormVariables(){} // Calls COleDispatchDriver default constructor
	CFormVariables(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFormVariables(const CFormVariables& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// FormVariables methods
public:
	LPDISPATCH Item(VARIANT& Key)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Key);
		return result;
	}
	LPDISPATCH _Item(VARIANT& Key)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Key);
		return result;
	}
	LPDISPATCH Add(VARIANT& Key)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Key);
		return result;
	}
	void Remove(VARIANT& Key)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Key);
	}

	// FormVariables properties
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
	LPDISPATCH GetParent()
	{
		LPDISPATCH result;
		GetProperty(0x2, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetParent(LPDISPATCH propVal)
	{
		SetProperty(0x2, VT_DISPATCH, propVal);
	}
	IApplication * GetApplication()
	{
		IApplication * result;
		GetProperty(0x3, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetApplication(IApplication * propVal)
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

};
