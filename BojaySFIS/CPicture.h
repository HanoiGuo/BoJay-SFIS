// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Windows\\System32\\stdole2.tlb" no_namespace
// CPicture wrapper class

class CPicture : public COleDispatchDriver
{
public:
	CPicture(){} // Calls COleDispatchDriver default constructor
	CPicture(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPicture(const CPicture& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// Picture methods
public:
	void Render(long hdc, long x, long y, long cx, long cy, long xSrc, long ySrc, long cxSrc, long cySrc, void * prcWBounds)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_UNKNOWN ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, hdc, x, y, cx, cy, xSrc, ySrc, cxSrc, cySrc, prcWBounds);
	}

	// Picture properties
public:
	OLE_HANDLE GetHandle()
	{
		OLE_HANDLE result;
		GetProperty(0x0, VT_I4, (void*)&result);
		return result;
	}
	void SetHandle(OLE_HANDLE propVal)
	{
		SetProperty(0x0, VT_I4, propVal);
	}
	OLE_HANDLE GethPal()
	{
		OLE_HANDLE result;
		GetProperty(0x2, VT_I4, (void*)&result);
		return result;
	}
	void SethPal(OLE_HANDLE propVal)
	{
		SetProperty(0x2, VT_I4, propVal);
	}
	short GetType()
	{
		short result;
		GetProperty(0x3, VT_I2, (void*)&result);
		return result;
	}
	void SetType(short propVal)
	{
		SetProperty(0x3, VT_I2, propVal);
	}
	OLE_XSIZE_HIMETRIC GetWidth()
	{
		OLE_XSIZE_HIMETRIC result;
		GetProperty(0x4, VT_I4, (void*)&result);
		return result;
	}
	void SetWidth(OLE_XSIZE_HIMETRIC propVal)
	{
		SetProperty(0x4, VT_I4, propVal);
	}
	OLE_YSIZE_HIMETRIC GetHeight()
	{
		OLE_YSIZE_HIMETRIC result;
		GetProperty(0x5, VT_I4, (void*)&result);
		return result;
	}
	void SetHeight(OLE_YSIZE_HIMETRIC propVal)
	{
		SetProperty(0x5, VT_I4, propVal);
	}

};
