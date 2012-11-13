
#include "WebWrapper.h"

#include <comutil.h>
#pragma comment(lib,"comsuppw.lib")

#define HRTEST_SE(f,e) f
#define NULLTEST_SE(f,e) f
#define NULLTEST(f) f
#define NULLTEST_E(f,e) f
#define HRTEST_E(f,e) f

#define RECTWIDTH(r) ((r).right - (r).left)
#define RECTHEIGHT(r) ((r).bottom - (r).top)

WebWrapper::WebWrapper(void)
    : _refNum(0),
    _bInPlaced(false),
    _bExternalPlace(false),
    _bCalledCanInPlace(false),
    _bWebWndInited(false),
    _pOleObj(NULL), 
    _pInPlaceObj(NULL), 
    _pStorage(NULL), 
    _pWB2(NULL), 
    _pHtmlDoc2(NULL), 
    _pHtmlDoc3(NULL), 
    _pHtmlWnd2(NULL), 
    _pHtmlEvent(NULL),
    _hwnd(NULL)
{
    ::memset((PVOID)&_rcWebWnd,0,sizeof(_rcWebWnd));

    HRTEST_SE(OleInitialize(0), L"Ole初始化错误");
    HRTEST_SE(StgCreateDocfile(0, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT | STGM_CREATE, 0, &_pStorage), L"StgCreateDocfile错误");
    HRTEST_SE(OleCreate(CLSID_WebBrowser, IID_IOleObject, OLERENDER_DRAW, 0, this, _pStorage, (void**)&_pOleObj), L"Ole创建失败");
    HRTEST_SE(_pOleObj->QueryInterface(IID_IOleInPlaceObject, (LPVOID*)&_pInPlaceObj), L"OleInPlaceObject创建失败");
}

WebWrapper::~WebWrapper(void)
{
}

STDMETHODIMP WebWrapper::QueryInterface(REFIID iid,void**ppvObject)
{
    *ppvObject = 0;

    if (iid == IID_IOleClientSite)
    {
        *ppvObject = (IOleClientSite*)this;
    }

    if (iid == IID_IUnknown)
    {
        *ppvObject = this;
    }

    if (iid == IID_IDispatch)
    {
        *ppvObject = (IDispatch*)this;
    }

    if (_bExternalPlace == false)
    {
        if (iid == IID_IOleInPlaceSite)
        {
            *ppvObject = (IOleInPlaceSite*)this;
        }

        if (iid == IID_IOleInPlaceFrame)
        {
            *ppvObject = (IOleInPlaceFrame*)this;
        }

        if (iid == IID_IOleInPlaceUIWindow)
        {
            *ppvObject = (IOleInPlaceUIWindow*)this;
        }
    }

    /*
    if ( iid == DIID_DWebBrowserEvents2 )
    {
        *ppvObject = (DWebBrowserEvents2 *)this;
    }

    if ( iid == IID_IDocHostUIHandler)
    {
        *ppvObject = (IDocHostUIHandler*)this;
    }
    */

    if (*ppvObject)
    {
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) WebWrapper::AddRef()
{
    return ::InterlockedIncrement(&_refNum);
}

STDMETHODIMP_(ULONG) WebWrapper::Release()
{
    return ::InterlockedDecrement(&_refNum);
}

HRESULT _stdcall WebWrapper::GetTypeInfoCount(unsigned int * pctinfo) 
{
    return E_NOTIMPL;
}

HRESULT _stdcall WebWrapper::
GetTypeInfo(unsigned int iTInfo, LCID lcid, ITypeInfo FAR* FAR* ppTInfo) 
{
    return E_NOTIMPL;
}

HRESULT _stdcall WebWrapper::
GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR* rgszNames
              , unsigned int cNames, LCID lcid, DISPID FAR* rgDispId)
{
    return E_NOTIMPL;
}

HRESULT _stdcall WebWrapper::Invoke(DISPID dispIdMember,
                                    REFIID riid,
                                    LCID lcid,
                                    WORD wFlags,
                                    DISPPARAMS* pDispParams,
                                    VARIANT* pVarResult,
                                    EXCEPINFO* pExcepInfo,
                                    unsigned int* puArgErr)
{
    /*
    // DWebBrowserEvents2
    if( dispIdMember == DISPID_DOCUMENTCOMPLETE)
    {
    DocumentComplete(pDispParams->rgvarg[1].pdispVal,pDispParams->rgvarg[0].pvarVal);
    return S_OK;
    }
    if( dispIdMember == DISPID_BEFORENAVIGATE2)
    {
    BeforeNavigate2( pDispParams->rgvarg[6].pdispVal,
    pDispParams->rgvarg[5].pvarVal,
    pDispParams->rgvarg[4].pvarVal,
    pDispParams->rgvarg[3].pvarVal,
    pDispParams->rgvarg[2].pvarVal,
    pDispParams->rgvarg[1].pvarVal,
    pDispParams->rgvarg[0].pboolVal);
    return S_OK;
    }
    */
    return E_NOTIMPL;
}

STDMETHODIMP WebWrapper::SaveObject()
{
    return S_OK;
}

STDMETHODIMP WebWrapper::GetMoniker(DWORD dwA, DWORD dwW, IMoniker**pm)
{
    *pm = 0;
    return E_NOTIMPL;
}

STDMETHODIMP WebWrapper::GetContainer(IOleContainer**pc)
{
    *pc = 0;
    return E_FAIL;
}

STDMETHODIMP WebWrapper::ShowObject()
{
    return S_OK;
}

STDMETHODIMP WebWrapper::OnShowWindow(BOOL f)
{
    return S_OK;
}

STDMETHODIMP WebWrapper::RequestNewObjectLayout()
{
    return S_OK;
}



///=========================
///IOleInPlaceSite methods|
///=========================

STDMETHODIMP WebWrapper::GetWindow(HWND *p)
{
    *p = HandleToHwnd(GetHandle());
    return S_OK;
}

STDMETHODIMP WebWrapper::ContextSensitiveHelp(BOOL)
{
    return E_NOTIMPL;
}

STDMETHODIMP WebWrapper::CanInPlaceActivate()//If this function return S_FALSE, AX cannot activate in place!
{
    if (_bInPlaced)
    {
        _bCalledCanInPlace = true;
        return S_OK;
    }

    return S_FALSE;
}

STDMETHODIMP WebWrapper::OnInPlaceActivate()
{
    return S_OK;
}

STDMETHODIMP WebWrapper::OnUIActivate()
{
    return S_OK;
}

STDMETHODIMP WebWrapper::GetWindowContext(IOleInPlaceFrame** ppFrame,IOleInPlaceUIWindow **ppDoc,LPRECT r1,LPRECT r2,LPOLEINPLACEFRAMEINFO o)
{
    *ppFrame = (IOleInPlaceFrame*)this;
    AddRef();
    *ppDoc = NULL;

    ::GetClientRect(HandleToHwnd(GetHandle()), &_rcWebWnd );
    *r1 = _rcWebWnd;
    *r2 = _rcWebWnd;

    o->cb = sizeof(OLEINPLACEFRAMEINFO);
    o->fMDIApp = false;
    o->hwndFrame = GetParent( HandleToHwnd(GetHandle()) );
    o->haccel = 0;
    o->cAccelEntries = 0;

    return S_OK;
}

STDMETHODIMP WebWrapper::Scroll(SIZE s)
{
    return E_NOTIMPL;
}

STDMETHODIMP WebWrapper::OnUIDeactivate(int)
{
    return S_OK;
}

STDMETHODIMP WebWrapper::OnInPlaceDeactivate()
{
    return S_OK;
}

STDMETHODIMP WebWrapper::DiscardUndoState()
{
    return S_OK;
}

STDMETHODIMP WebWrapper::DeactivateAndUndo()
{
    return S_OK;
}

STDMETHODIMP WebWrapper::OnPosRectChange(LPCRECT)
{
    return S_OK;
}

///==========================
///IOleInPlaceFrame methods
///==========================

STDMETHODIMP WebWrapper::GetBorder(LPRECT l)
{
    ::GetClientRect(  HandleToHwnd(GetHandle()) ,&_rcWebWnd );
    *l = _rcWebWnd;
    return S_OK;
}

STDMETHODIMP WebWrapper::RequestBorderSpace(LPCBORDERWIDTHS b)
{
    return S_OK;
}

STDMETHODIMP WebWrapper::SetBorderSpace(LPCBORDERWIDTHS b)
{
    return S_OK;
}

STDMETHODIMP WebWrapper::SetActiveObject(IOleInPlaceActiveObject*pV,LPCOLESTR s)
{
    return S_OK;
}

STDMETHODIMP WebWrapper::SetStatusText(LPCOLESTR t)
{
    return E_NOTIMPL;
}

STDMETHODIMP WebWrapper::EnableModeless(BOOL f)
{
    return E_NOTIMPL;
}

STDMETHODIMP WebWrapper::TranslateAccelerator(LPMSG,WORD)
{
    return E_NOTIMPL;
}

HRESULT _stdcall WebWrapper::RemoveMenus(HMENU h)
{
    return E_NOTIMPL;
}

HRESULT _stdcall WebWrapper::InsertMenus(HMENU h,LPOLEMENUGROUPWIDTHS x)
{
    return E_NOTIMPL;
}
HRESULT _stdcall WebWrapper::SetMenu(HMENU h,HOLEMENU hO,HWND hw)
{
    return E_NOTIMPL;
}


///========================================================
///DWebBrowserEvents2
///========================================================

///========================================================
///Other Methods
///=======================================================

IWebBrowser2* 
WebWrapper::GetWebBrowser2()
{
    if (_pWB2 != NULL)
    {
        return _pWB2;
    }

    NULLTEST_SE(_pOleObj, L"Ole对象为空");

    HRTEST_SE(_pOleObj->QueryInterface(IID_IWebBrowser2,(void**)&_pWB2),L"QueryInterface IID_IWebBrowser2 失败");
    return _pWB2;
}

IHTMLDocument2*    
WebWrapper::GetHTMLDocument2()
{
    if (_pHtmlDoc2 != NULL)
    {
        return _pHtmlDoc2;
    }

    IWebBrowser2* pWB2 = NULL;
    NULLTEST(pWB2 = GetWebBrowser2());//GetWebBrowser2已经将错误原因交给LastError.
    IDispatch* pDp =  NULL;
    HRTEST_SE(pWB2->get_Document(&pDp),L"DWebBrowser2::get_Document 错误");
    HRTEST_SE(pDp->QueryInterface(IID_IHTMLDocument2,(void**)&_pHtmlDoc2),L"QueryInterface IID_IHTMLDocument2 失败");
    return _pHtmlDoc2;
}

IHTMLDocument3*    
WebWrapper::GetHTMLDocument3()
{
    if (_pHtmlDoc3 != NULL)
    {
        return _pHtmlDoc3;
    }

    IWebBrowser2* pWB2 = NULL;
    NULLTEST(pWB2 = GetWebBrowser2());//GetWebBrowser2已经将错误原因交给LastError.
    IDispatch* pDp =  NULL;
    HRTEST_SE(pWB2->get_Document(&pDp),L"DWebBrowser2::get_Document 错误");
    HRTEST_SE(pDp->QueryInterface(IID_IHTMLDocument3,(void**)&_pHtmlDoc3),L"QueryInterface IID_IHTMLDocument3 失败");
    
    return _pHtmlDoc3;
}

IHTMLWindow2*
WebWrapper::GetHTMLWindow2()
{
    if (_pHtmlWnd2 != NULL)
    {
        return _pHtmlWnd2;
    }

    IHTMLDocument2*  pHD2 = GetHTMLDocument2();
    NULLTEST( pHD2 );
    HRTEST_SE( pHD2->get_parentWindow(&_pHtmlWnd2),L"IHTMLWindow2::get_parentWindow 错误" );
    return _pHtmlWnd2;
}

IHTMLEventObj*   
WebWrapper::GetHTMLEventObject()
{
    if (_pHtmlEvent != NULL)
    {
        return _pHtmlEvent;
    }

    IHTMLWindow2* pHW2;
    NULLTEST( pHW2 = GetHTMLWindow2() );
    HRTEST_SE( pHW2->get_event(&_pHtmlEvent),L"IHTMLWindow2::get_event 错误");
    
    return _pHtmlEvent;
}

BOOL WebWrapper::SetWebRect(LPRECT lprc)
{
    BOOL bRet = FALSE;

    if (false == _bInPlaced)//尚未OpenWebBrowser操作,直接写入_rcWebWnd
    {
        _rcWebWnd = *lprc;
    }
    else//已经打开WebWrapper,通过 IOleInPlaceObject::SetObjectRects 调整大小
    {
        SIZEL size;
        size.cx = RECTWIDTH(*lprc);
        size.cy = RECTHEIGHT(*lprc);

        IOleObject* pOleObj;
        NULLTEST(pOleObj = _GetOleObject());
        HRTEST_E(pOleObj->SetExtent(1,&size), L"SetExtent 错误");

        IOleInPlaceObject* pInPlace;
        NULLTEST(pInPlace = _GetInPlaceObject());
        HRTEST_E(pInPlace->SetObjectRects(lprc,lprc), L"SetObjectRects 错误");
        _rcWebWnd = *lprc;
    }

    bRet = TRUE;

    return bRet;
}

BOOL WebWrapper::OpenWebBrowser()
{
    BOOL bRet = FALSE;

    NULLTEST_E(_GetOleObject(), L"ActiveX对象为空");//对于本身的实现函数,其自身承担错误录入工作

    if ((RECTWIDTH(_rcWebWnd) && RECTHEIGHT(_rcWebWnd)) == 0)
    {
        ::GetClientRect(HandleToHwnd(GetHandle()) ,&_rcWebWnd);//设置WebWrapper的大小为窗口的客户区大小.
    }

    if (!_bInPlaced)// Activate In Place
    {
        _bInPlaced = true;//_bInPlaced must be set as true, before INPLACEACTIVATE, otherwise, once DoVerb, it would return error;
        _bExternalPlace = 0;//lParam;

        HRTEST_E(_GetOleObject()->DoVerb(OLEIVERB_INPLACEACTIVATE,0,this,0, HandleToHwnd(GetHandle()), &_rcWebWnd), L"关于INPLACE的DoVerb错误");
        //_bInPlaced = false;

        //* 挂接DWebBrwoser2Event
        IConnectionPointContainer* pCPC = NULL;
        IConnectionPoint* pCP  = NULL;
        HRTEST_E(GetWebBrowser2()->QueryInterface(IID_IConnectionPointContainer, (void**)&pCPC),L"枚举IConnectionPointContainer接口失败");
        HRTEST_E(pCPC->FindConnectionPoint(DIID_DWebBrowserEvents2, &pCP), L"FindConnectionPoint失败");
        DWORD dwCookie = 0;
        HRTEST_E(pCP->Advise((IUnknown*)(void*)this,&dwCookie),L"IConnectionPoint::Advise失败");
    }

    bRet = TRUE;

    return bRet;
}

BOOL WebWrapper::OpenURL(LPCTSTR pUrl)
{
    _variant_t vUri = _variant_t(pUrl);
    BOOL bRet = FALSE;
    HRTEST_E(GetWebBrowser2()->Navigate2(&vUri, 0, 0, 0, 0), L"GetWebBrowser2 失败");
    bRet = TRUE;

    return bRet;
}
