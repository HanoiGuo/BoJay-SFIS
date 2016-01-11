// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files\\Teklynx\\CODESOFT 2012\\Lppx2.tlb" no_namespace
// CVariables wrapper class

class CVariables : public COleDispatchDriver
{
public:
	CVariables(){} // Calls COleDispatchDriver default constructor
	CVariables(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVariables(const CVariables& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// Variables methods
public:
	LPDISPATCH Item(VARIANT& Key)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Key);
		return result;
	}
	LPDISPATCH _Item(VARIANT& Key)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Key);
		return result;
	}
	LPDISPATCH Add(VARIANT& Item1, VARIANT& Item2)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Item1, &Item2);
		return result;
	}
	void Remove(VARIANT& Key)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Key);
	}
	void Refresh()
	{
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// Variables properties
public:
	FreeVariables * GetFreeVariables()
	{
		FreeVariables * result;
		GetProperty(0x1, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetFreeVariables(FreeVariables * propVal)
	{
		SetProperty(0x1, VT_DISPATCH, propVal);
	}
	FormVariables * GetFormVariables()
	{
		FormVariables * result;
		GetProperty(0x2, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetFormVariables(FormVariables * propVal)
	{
		SetProperty(0x2, VT_DISPATCH, propVal);
	}
	DatabaseVariables * GetDatabaseVariables()
	{
		DatabaseVariables * result;
		GetProperty(0x3, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetDatabaseVariables(DatabaseVariables * propVal)
	{
		SetProperty(0x3, VT_DISPATCH, propVal);
	}
	Counters * GetCounters()
	{
		Counters * result;
		GetProperty(0x4, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetCounters(Counters * propVal)
	{
		SetProperty(0x4, VT_DISPATCH, propVal);
	}
	Formulas * GetFormulas()
	{
		Formulas * result;
		GetProperty(0x5, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetFormulas(Formulas * propVal)
	{
		SetProperty(0x5, VT_DISPATCH, propVal);
	}
	TableLookups * GetTableLookups()
	{
		TableLookups * result;
		GetProperty(0x6, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetTableLookups(TableLookups * propVal)
	{
		SetProperty(0x6, VT_DISPATCH, propVal);
	}
	Dates * GetDates()
	{
		Dates * result;
		GetProperty(0x7, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetDates(Dates * propVal)
	{
		SetProperty(0x7, VT_DISPATCH, propVal);
	}
	short GetCount()
	{
		short result;
		GetProperty(0x8, VT_I2, (void*)&result);
		return result;
	}
	void SetCount(short propVal)
	{
		SetProperty(0x8, VT_I2, propVal);
	}
	LPDISPATCH GetParent()
	{
		LPDISPATCH result;
		GetProperty(0x9, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetParent(LPDISPATCH propVal)
	{
		SetProperty(0x9, VT_DISPATCH, propVal);
	}
	IApplication * GetApplication()
	{
		IApplication * result;
		GetProperty(0xa, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetApplication(IApplication * propVal)
	{
		SetProperty(0xa, VT_DISPATCH, propVal);
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
