// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// StackPanel.cpp

#include <sui/StackPanel.h>
#include <suic/tools/vector.h>

namespace ui
{

ImplementTypeofInfo(StackPanel, suic::Panel)

StackPanel::StackPanel()
{
    SetClassName(_T("StackPanel"));
}

StackPanel::StackPanel(bool bHorz)
{
    SetOrientation(CoreFlags::Horizontal);;

    SetClassName(_T("StackPanel"));
}

StackPanel::~StackPanel()
{
}

void StackPanel::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

suic::Size StackPanel::MeasureOverride(const suic::Size& availableSize)
{
    int iCount = GetChildrenCount();
    suic::Size childSize;

    if (GetOrientation() == CoreFlags::Horizontal)
    {
        for (int i = 0; i < iCount; ++i)
        {
            suic::FrameworkElementPtr child(GetChild(i));

            if (child->IsVisible())
            {
                // 
                // 递归计算子界面元素的大小
                //
                child->Measure(availableSize);

                childSize.cx += child->GetDesiredSize().cx;            
                childSize.cx += child->GetMargin().left; 
                childSize.cx += child->GetMargin().right; 

                int mgrcy = child->GetMargin().top + child->GetMargin().bottom;

                mgrcy += child->GetDesiredSize().cy;

                if (mgrcy > childSize.cy)
                {
                    childSize.cy = mgrcy;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < iCount; ++i)
        {
            suic::FrameworkElementPtr child(GetChild(i));

            if (child->IsVisible())
            {
                // 
                // 递归计算子界面元素的大小
                //
                child->Measure(availableSize);

                int mgrcx = child->GetMargin().left + child->GetMargin().right;

                mgrcx += child->GetDesiredSize().cx;

                if (mgrcx > childSize.cx)
                {
                    childSize.cx = mgrcx;
                }

                childSize.cy += child->GetDesiredSize().cy; 
                childSize.cy += child->GetMargin().top; 
                childSize.cy += child->GetMargin().bottom; 
            }
        }
    }

    WriteFlag(CoreFlags::IsMeasureDirty, false);

    childSize.cx += GetPadding().SumLR();
    childSize.cy += GetPadding().SumTB();

    return childSize;    
}

suic::Size StackPanel::ArrangeOverride(const suic::Size& size)
{
    ClearVisualChildren();

    // 
    // 水平方向
    //
    if (GetOrientation() == CoreFlags::Horizontal)
    {
        RelayoutHorizontal(size);
    }
    else
    {
        RelayoutVertical(size);
    }

    return size;
}

void StackPanel::
CalcHorzElement(suic::FrameworkElement* ePtr, suic::Rect& rcLay, suic::Rect& rc)
{
	// 取得其离父窗口边距
	suic::Rect rcmgr = ePtr->GetMargin();
    const suic::Size & szelem = ePtr->GetDesiredSize();
	
	rc = rcLay;

	// 垂直对齐方式
	int iVert = ePtr->GetVerticalAlignment();

    ARRANGEVERTICALCHILDREN(iVert, rcLay, rcmgr, rc);

	rc.left = rcLay.left + rcmgr.left;
	rc.right = rc.left + szelem.cx;

	rcLay.left = rc.right + rcmgr.right;
}

typedef struct tagCalcuItem
{
public:

    suic::Rect rect;
    int index;

    tagCalcuItem() {}
    ~tagCalcuItem() {}
}CalcuItem;

void StackPanel::RelayoutHorizontal(const suic::Size& size)
{
    suic::Rect rcLay(0, 0, size.cx, size.cy);

    rcLay.Deflate(GetPadding());
    //rcLay.left += GetPadding().left;

    int i = 0;
    int iLeft = rcLay.left + _horizontalOffset;
    int iWid = 0;
    
    int iCount = GetChildrenCount();

    for (i = 0; i < iCount; ++i)
    {
        suic::FrameworkElementPtr ePtr(GetChild(i));

        if (ePtr->IsVisible())
        {
            const suic::Rect & rcMgr = ePtr->GetMargin();
            int iTm = rcMgr.left + rcMgr.right + ePtr->GetDesiredSize().cx;

            iWid += iTm;

            if (iWid >= _horizontalOffset)
            {
                rcLay.left += iWid - iTm;
                rcLay.right = size.cx;
                break;
            }
        }
    }

    rcLay.top -= _verticalOffset;
    //rcLay.bottom = size.cy;

    for (i = 0; i < iCount; ++i)
    {
        suic::FrameworkElementPtr ePtr(GetChild(i));

        if (ePtr->IsVisible())
        {
            suic::Rect rc;
  
            //rcLay.bottom = rcLay.top + ePtr->GetDesiredSize().cy;
            CalcHorzElement(ePtr, rcLay, rc);

            // 
            // 加入到可视树
            //
            AddVisualChild(suic::VisualPtr::cast(ePtr));
            ePtr->Arrange(rc);

            if (rcLay.left >= rcLay.right)
            {
                break;
            }
        }
    }
}

void StackPanel::
CalcVertElement(suic::FrameworkElement* ePtr, suic::Rect& rcLay, suic::Rect& rc)
{
	// 
    // 取得其离父窗口边距
    //
	suic::Rect rcmgr = ePtr->GetMargin();
	suic::Size szelem = ePtr->GetDesiredSize();

	rc = rcLay;

	// 
    // 水平对齐方式
    //
	int iHorz = ePtr->GetHorizontalAlignment();

    ARRANGEHORIZONTALCHILDREN(iHorz, rcLay, rcmgr, rc);

	rc.top = rcLay.top + rcmgr.top;
	rc.bottom = rc.top + szelem.cy;

	rcLay.top = rc.bottom + rcmgr.bottom;
}

void StackPanel::RelayoutVertical(const suic::Size& size)
{
    suic::Rect rcLay(0, 0, size.cx, size.cy);

    rcLay.Deflate(GetBorderThickness());
    rcLay.top += GetPadding().top;

    int i = 0;
    int iTop = rcLay.top + _verticalOffset;
    int iCount = GetChildrenCount();
    int iHei = 0;

    for (i = 0; i < iCount; ++i)
    {
        suic::FrameworkElementPtr ePtr(GetChild(i));

        if (ePtr->IsVisible())
        {
            const suic::Rect & rcMgr = ePtr->GetMargin();
            int iTm = rcMgr.top + rcMgr.bottom + ePtr->GetDesiredSize().cy;

            iHei += iTm;

            if (iHei >= iTop)
            {
                rcLay.top = iHei - iTop - iTm;
                rcLay.bottom = size.cy;
                break;
            }
        }
    }

    //rcLay.left -= _horizontalOffset;

    for (; i < iCount; ++i)
    {
        suic::FrameworkElementPtr ePtr(GetChild(i));

        if (ePtr->IsVisible())
        {
            suic::Rect rc;

            CalcVertElement(ePtr, rcLay, rc);

            rc.left -= _horizontalOffset;
            rc.right -= _horizontalOffset;

            // 
            // 加入到可视树
            //
            AddVisualChild(suic::VisualPtr::cast(ePtr));
            ePtr->Arrange(rc);

            if (rcLay.top >= rcLay.bottom)
            {
                break;
            }
        }
    }
}

};
