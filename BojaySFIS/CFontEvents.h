// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Windows\\System32\\stdole2.tlb" no_namespace
// CFontEvents wrapper class

class CFontEvents : public COleDispatchDriver
{
public:
	CFontEvents(){} // Calls COleDispatchDriver default constructor
	CFontEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFontEvents(const CFontEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// FontEvents methods
public:
	void FontChanged(LPCTSTR PropertyName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PropertyName);
	}

	// FontEvents properties
public:

};
