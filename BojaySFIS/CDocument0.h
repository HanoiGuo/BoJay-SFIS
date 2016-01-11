// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files\\Teklynx\\CODESOFT 2012\\Lppx2.tlb" no_namespace
// CDocument0 wrapper class

class CDocument0 : public COleDispatchDriver
{
public:
	CDocument0(){} // Calls COleDispatchDriver default constructor
	CDocument0(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDocument0(const CDocument0& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IDocument methods
public:
	short Save()
	{
		short result;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	short SaveAs(LPCTSTR strPathName)
	{
		short result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_I2, (void*)&result, parms, strPathName);
		return result;
	}
	short PrintDocument(long Quantity)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Quantity);
		return result;
	}
	short PrintLabel(long Quantity, long LabelCopy, long InterCut, long PageCopy, long NoFrom, LPCTSTR FileName)
	{
		short result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Quantity, LabelCopy, InterCut, PageCopy, NoFrom, FileName);
		return result;
	}
	short GeneratePOF(LPCTSTR DestFileName, LPCTSTR ModeleFileName)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DestFileName, ModeleFileName);
		return result;
	}
	short Merge(long Quantity, long LabelCopy, long InterCut, long PageCopy, long NoFrom, LPCTSTR FileName)
	{
		short result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Quantity, LabelCopy, InterCut, PageCopy, NoFrom, FileName);
		return result;
	}
	short Insert(LPCTSTR strPathName)
	{
		short result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_I2, (void*)&result, parms, strPathName);
		return result;
	}
	BOOL CopyToClipboard()
	{
		BOOL result;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	short FormFeed()
	{
		short result;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	void Close(BOOL Save)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Save);
	}
	void Activate()
	{
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString CopyImageToFile(short Colors, LPCTSTR Extension, short Rotation, short Percent, LPCTSTR FileName)
	{
		CString result;
		static BYTE parms[] = VTS_I2 VTS_BSTR VTS_I2 VTS_I2 VTS_BSTR ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Colors, Extension, Rotation, Percent, FileName);
		return result;
	}
	short WriteVariables(VARIANT& varArray)
	{
		short result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_I2, (void*)&result, parms, &varArray);
		return result;
	}
	VARIANT ReadVariables(long iType)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, iType);
		return result;
	}
	void Passwords(LPCTSTR strOwnerPassword, LPCTSTR strPrintPassword)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strOwnerPassword, strPrintPassword);
	}
	BOOL NewRFTag( IDRfTag, long Reserved)
	{
		BOOL result;
		static BYTE parms[] = VTS_UNKNOWN VTS_I4 ;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, IDRfTag, Reserved);
		return result;
	}
	* RFTag(long Reserved)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Reserved);
	}
	BOOL SelectDatabase(LPCTSTR strName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strName);
		return result;
	}
	BOOL CopyToClipboardEx(BOOL Border, short nMethod, short Colors, short Rotation, short Percent)
	{
		BOOL result;
		static BYTE parms[] = VTS_BOOL VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Border, nMethod, Colors, Rotation, Percent);
		return result;
	}
	VARIANT GetPreview(BOOL DrawBorder, BOOL Color, long nPercent)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BOOL VTS_BOOL VTS_I4 ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, DrawBorder, Color, nPercent);
		return result;
	}
	void Rotate(long lRotate)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lRotate);
	}
	CString CopyImageToFileEx(short Colors, LPCTSTR Extension, short Rotation, short Percent, LPCTSTR FileName, BOOL Border, BOOL NonPrintableObjects)
	{
		CString result;
		static BYTE parms[] = VTS_I2 VTS_BSTR VTS_I2 VTS_I2 VTS_BSTR VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Colors, Extension, Rotation, Percent, FileName, Border, NonPrintableObjects);
		return result;
	}
	VARIANT GetMetaFilePreview(long Flags, LPCTSTR previewObjectName)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Flags, previewObjectName);
		return result;
	}
	LPDISPATCH AddWatermark(LPCTSTR strWatermark, long nFlags)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strWatermark, nFlags);
		return result;
	}
	BOOL CheckIn(BSTR * Name, long nMode, long nState, LPCTSTR Comment)
	{
		BOOL result;
		static BYTE parms[] = VTS_PBSTR VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x200, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Name, nMode, nState, Comment);
		return result;
	}
	BOOL AddHistory(long nType, LPCTSTR Comment, LPDISPATCH HistData)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_DISPATCH ;
		InvokeHelper(0x201, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nType, Comment, HistData);
		return result;
	}

	// IDocument properties
public:
	Variables * GetVariables()
	{
		Variables * result;
		GetProperty(0x1, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetVariables(Variables * propVal)
	{
		SetProperty(0x1, VT_DISPATCH, propVal);
	}
	CString GetName()
	{
		CString result;
		GetProperty(0x2, VT_BSTR, (void*)&result);
		return result;
	}
	void SetName(CString propVal)
	{
		SetProperty(0x2, VT_BSTR, propVal);
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
	DocObjects * GetDocObjects()
	{
		DocObjects * result;
		GetProperty(0x3, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetDocObjects(DocObjects * propVal)
	{
		SetProperty(0x3, VT_DISPATCH, propVal);
	}
	Printer * GetPrinter()
	{
		Printer * result;
		GetProperty(0x4, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetPrinter(Printer * propVal)
	{
		SetProperty(0x4, VT_DISPATCH, propVal);
	}
	Format * GetFormat()
	{
		Format * result;
		GetProperty(0x5, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetFormat(Format * propVal)
	{
		SetProperty(0x5, VT_DISPATCH, propVal);
	}
	Database * GetDatabase()
	{
		Database * result;
		GetProperty(0x6, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetDatabase(Database * propVal)
	{
		SetProperty(0x6, VT_DISPATCH, propVal);
	}
	IApplication * GetApplication()
	{
		IApplication * result;
		GetProperty(0x7, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetApplication(IApplication * propVal)
	{
		SetProperty(0x7, VT_DISPATCH, propVal);
	}
	LPDISPATCH GetParent()
	{
		LPDISPATCH result;
		GetProperty(0x8, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetParent(LPDISPATCH propVal)
	{
		SetProperty(0x8, VT_DISPATCH, propVal);
	}
	CString GetFullName()
	{
		CString result;
		GetProperty(0x9, VT_BSTR, (void*)&result);
		return result;
	}
	void SetFullName(CString propVal)
	{
		SetProperty(0x9, VT_BSTR, propVal);
	}
	BOOL GetReadOnly()
	{
		BOOL result;
		GetProperty(0xa, VT_BOOL, (void*)&result);
		return result;
	}
	void SetReadOnly(BOOL propVal)
	{
		SetProperty(0xa, VT_BOOL, propVal);
	}
	long GetViewMode()
	{
		long result;
		GetProperty(0xb, VT_I4, (void*)&result);
		return result;
	}
	void SetViewMode(long propVal)
	{
		SetProperty(0xb, VT_I4, propVal);
	}
	long GetWindowState()
	{
		long result;
		GetProperty(0xc, VT_I4, (void*)&result);
		return result;
	}
	void SetWindowState(long propVal)
	{
		SetProperty(0xc, VT_I4, propVal);
	}
	DocumentProperties * GetBuiltInDocumentProperties()
	{
		DocumentProperties * result;
		GetProperty(0xd, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetBuiltInDocumentProperties(DocumentProperties * propVal)
	{
		SetProperty(0xd, VT_DISPATCH, propVal);
	}
	long GetTriggerForm()
	{
		long result;
		GetProperty(0xe, VT_I4, (void*)&result);
		return result;
	}
	void SetTriggerForm(long propVal)
	{
		SetProperty(0xe, VT_I4, propVal);
	}
	long GetViewOrientation()
	{
		long result;
		GetProperty(0xf, VT_I4, (void*)&result);
		return result;
	}
	void SetViewOrientation(long propVal)
	{
		SetProperty(0xf, VT_I4, propVal);
	}
	BOOL GetIsModified()
	{
		BOOL result;
		GetProperty(0x10, VT_BOOL, (void*)&result);
		return result;
	}
	void SetIsModified(BOOL propVal)
	{
		SetProperty(0x10, VT_BOOL, propVal);
	}
	SelectedDocObjects * GetSelectedDocObjects()
	{
		SelectedDocObjects * result;
		GetProperty(0x1d, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetSelectedDocObjects(SelectedDocObjects * propVal)
	{
		SetProperty(0x1d, VT_DISPATCH, propVal);
	}
	BOOL GetAutoPageIncrement()
	{
		BOOL result;
		GetProperty(0x1e, VT_BOOL, (void*)&result);
		return result;
	}
	void SetAutoPageIncrement(BOOL propVal)
	{
		SetProperty(0x1e, VT_BOOL, propVal);
	}
	long GetHorzPrintOffset()
	{
		long result;
		GetProperty(0x22, VT_I4, (void*)&result);
		return result;
	}
	void SetHorzPrintOffset(long propVal)
	{
		SetProperty(0x22, VT_I4, propVal);
	}
	long GetVertPrintOffset()
	{
		long result;
		GetProperty(0x23, VT_I4, (void*)&result);
		return result;
	}
	void SetVertPrintOffset(long propVal)
	{
		SetProperty(0x23, VT_I4, propVal);
	}
	CString GetRFTagList()
	{
		CString result;
		GetProperty(0x24, VT_BSTR, (void*)&result);
		return result;
	}
	void SetRFTagList(CString propVal)
	{
		SetProperty(0x24, VT_BSTR, propVal);
	}
	long GetViewZoom()
	{
		long result;
		GetProperty(0x2b, VT_I4, (void*)&result);
		return result;
	}
	void SetViewZoom(long propVal)
	{
		SetProperty(0x2b, VT_I4, propVal);
	}
	BOOL GetVisible()
	{
		BOOL result;
		GetProperty(0x2c, VT_BOOL, (void*)&result);
		return result;
	}
	void SetVisible(BOOL propVal)
	{
		SetProperty(0x2c, VT_BOOL, propVal);
	}
	BOOL GetWindowsGraphicalEmulation()
	{
		BOOL result;
		GetProperty(0x2e, VT_BOOL, (void*)&result);
		return result;
	}
	void SetWindowsGraphicalEmulation(BOOL propVal)
	{
		SetProperty(0x2e, VT_BOOL, propVal);
	}
	BOOL GetKeepPrinterObjects()
	{
		BOOL result;
		GetProperty(0x2f, VT_BOOL, (void*)&result);
		return result;
	}
	void SetKeepPrinterObjects(BOOL propVal)
	{
		SetProperty(0x2f, VT_BOOL, propVal);
	}
	BOOL GetIsResolutionIndependentWysiwyg()
	{
		BOOL result;
		GetProperty(0x30, VT_BOOL, (void*)&result);
		return result;
	}
	void SetIsResolutionIndependentWysiwyg(BOOL propVal)
	{
		SetProperty(0x30, VT_BOOL, propVal);
	}
	Background * GetBackground()
	{
		Background * result;
		GetProperty(0x31, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetBackground(Background * propVal)
	{
		SetProperty(0x31, VT_DISPATCH, propVal);
	}
	BOOL GetRefreshDatabaseBeforePrinting()
	{
		BOOL result;
		GetProperty(0x32, VT_BOOL, (void*)&result);
		return result;
	}
	void SetRefreshDatabaseBeforePrinting(BOOL propVal)
	{
		SetProperty(0x32, VT_BOOL, propVal);
	}
	long GetPrintingOptimizationMode()
	{
		long result;
		GetProperty(0x34, VT_I4, (void*)&result);
		return result;
	}
	void SetPrintingOptimizationMode(long propVal)
	{
		SetProperty(0x34, VT_I4, propVal);
	}
	long GetVersion()
	{
		long result;
		GetProperty(0x35, VT_I4, (void*)&result);
		return result;
	}
	void SetVersion(long propVal)
	{
		SetProperty(0x35, VT_I4, propVal);
	}
	BOOL GetFullClippingMode()
	{
		BOOL result;
		GetProperty(0x36, VT_BOOL, (void*)&result);
		return result;
	}
	void SetFullClippingMode(BOOL propVal)
	{
		SetProperty(0x36, VT_BOOL, propVal);
	}
	long GetLayersShown()
	{
		long result;
		GetProperty(0x37, VT_I4, (void*)&result);
		return result;
	}
	void SetLayersShown(long propVal)
	{
		SetProperty(0x37, VT_I4, propVal);
	}
	long GetLayersPrinted()
	{
		long result;
		GetProperty(0x38, VT_I4, (void*)&result);
		return result;
	}
	void SetLayersPrinted(long propVal)
	{
		SetProperty(0x38, VT_I4, propVal);
	}
	BOOL GetNeedsApproval()
	{
		BOOL result;
		GetProperty(0x3a, VT_BOOL, (void*)&result);
		return result;
	}
	void SetNeedsApproval(BOOL propVal)
	{
		SetProperty(0x3a, VT_BOOL, propVal);
	}
	CString GetCauseForApproval()
	{
		CString result;
		GetProperty(0x3b, VT_BSTR, (void*)&result);
		return result;
	}
	void SetCauseForApproval(CString propVal)
	{
		SetProperty(0x3b, VT_BSTR, propVal);
	}

};
