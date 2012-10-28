// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// StackLayout.cpp

#include <sui/StackLayout.h>
#include <util/vector.h>

namespace ui
{

StackLayout::StackLayout()
{
    SetClassName(_T("StackLayout"));
}

StackLayout::StackLayout(bool bHorz)
{
    SetOrientation(CoreFlags::Horizontal);;

    SetClassName(_T("StackLayout"));
}

StackLayout::~StackLayout()
{
}

void StackLayout::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

suic::Size StackLayout::MeasureOverride(const suic::Size& availableSize)
{
    return __super::MeasureOverride(availableSize);    
}

suic::Size StackLayout::ArrangeOverride(const suic::Size& size)
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

typedef struct tagCalcuItem
{
public:

    suic::Rect rect;
    int index;

    tagCalcuItem() {}
    ~tagCalcuItem() {}
}CalcuItem;

void StackLayout::RelayoutHorizontal(const suic::Size& size)
{
    suic::Rect rcLay(0, 0, size.cx, size.cy);

    rcLay.Deflate(GetPadding());

    int nLeft = rcLay.left;
    int nRight = nLeft;
    
    int iCount = GetChildrenCount();

    for (int i = 0; i < iCount; ++i)
    {
        suic::FrameworkElementPtr ePtr(GetChild(i));

        if (ePtr->IsVisible())
        {
            suic::Rect & rcpad = ePtr->GetPadding();

            if (ePtr->GetHorizontalAlignment() == CoreFlags::Stretch)
            {
                suic::FrameworkElementPtr eStretch = ePtr;

                int iBeg = rcLay.left;
                int iEnd = iBeg;
                int in = i + 1;

                suic::Vector<CalcuItem> vecrc;

                for (; in < iCount; ++in)
                {
                    CalcuItem item;
                    suic::Rect rcClip;

                    ePtr = suic::ElementPtr::cast(GetChild(in));

                    if (ePtr->IsVisible())
                    {
                        CalcHorzElement(ePtr, rcLay, item.rect);

                        item.index = in;
                        vecrc.push_back(item);

                        iEnd = rcLay.left;

                        if (rcLay.left >= rcLay.right)
                        {
                            ++in;
                            break;
                        }
                    }
                }

                int iGlue = rcLay.right - iEnd;

                if (iGlue < 0)
                {
                    iGlue = 0;
                }

                for (int j = 0; j < (int)vecrc.size(); ++j)
                {
                    ePtr = suic::ElementPtr::cast(GetChild(vecrc[j].index));

                    vecrc[j].rect.left += iGlue;
                    vecrc[j].rect.right += iGlue;

                    // 
                    // 加入到可视树
                    //
                    AddVisualChild(suic::VisualPtr::cast(ePtr));
                    ePtr->Arrange(vecrc[j].rect);
                }

                if (iGlue > 0)
                {
                    rcLay.left = iBeg;
                    rcLay.right = rcLay.left + iGlue;
                    suic::Rect rc = rcLay;
                    suic::Rect rcClip = rc;

                    suic::Rect rcmgr = eStretch->GetMargin();

                    int iVert = eStretch->GetVerticalAlignment();
                    suic::Size szelem = ePtr->GetDesiredSize();
                    ARRANGEVERTICALCHILDREN(iVert, rcLay, rcmgr, rc);

                    rc.right -= rcmgr.right;
                    rc.left += rcmgr.left;

                    // 
                    // 加入到可视树
                    //
                    AddVisualChild(suic::VisualPtr::cast(eStretch));
                    eStretch->Arrange(rc);
                }

                break;
            }

            suic::Rect rc;

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

void StackLayout::RelayoutVertical(const suic::Size& size)
{
    suic::Rect rcLay(0, 0, size.cx, size.cy);

    rcLay.Deflate(GetBorderThickness());

    int iTop = rcLay.top;
    int iBottom = iTop;

    int iCount = GetChildrenCount();

    for (int i = 0; i < iCount; ++i)
    {
        suic::FrameworkElementPtr ePtr(GetChild(i));

        if (ePtr->IsVisible())
        {
            suic::Rect & rcpad = ePtr->GetPadding();

            if (ePtr->GetVerticalAlignment() == CoreFlags::Stretch)
            {
                suic::FrameworkElementPtr eStretch = ePtr;

                int iBeg = rcLay.top;
                int iEnd = iBeg;
                int in = i + 1;

                suic::Vector<CalcuItem> vecrc;

                for (; in < iCount; ++in)
                {
                    CalcuItem item;

                    ePtr = suic::ElementPtr::cast(GetChild(in));

                    if (ePtr->IsVisible())
                    {
                        CalcVertElement(ePtr, rcLay, item.rect);

                        item.index = in;
                        vecrc.push_back(item);

                        iEnd = rcLay.top;

                        if (rcLay.top >= rcLay.bottom)
                        {
                            ++in;
                            break;
                        }
                    }
                }

                int iGlue = rcLay.bottom - iEnd;

                if (iGlue < 0)
                {
                    iGlue = 0;
                }

                for (int j = 0; j < (int)vecrc.size(); ++j)
                {
                    ePtr = GetChild(vecrc[j].index);

                    vecrc[j].rect.top += iGlue;
                    vecrc[j].rect.bottom += iGlue;

                    // 
                    // 加入到可视树
                    //
                    AddVisualChild(suic::VisualPtr::cast(ePtr));
                    ePtr->Arrange(vecrc[j].rect);
                }

                if (iGlue > 0)
                {
                    rcLay.top = iBeg;
                    rcLay.bottom = rcLay.top + iGlue;
                    suic::Rect rc = rcLay;
                    suic::Rect rcmgr = eStretch->GetMargin();

                    int iHorz = ePtr->GetHorizontalAlignment();
                    suic::Size szelem = ePtr->GetDesiredSize();
                    ARRANGEHORIZONTALCHILDREN(iHorz, rcLay, rcmgr, rc);

                    rc.bottom -= rcmgr.bottom;
                    rc.top += rcmgr.top;

                    // 
                    // 加入到可视树
                    //
                    AddVisualChild(suic::VisualPtr::cast(eStretch));
                    eStretch->Arrange(rc);
                }

                break;
            }

            suic::Rect rc;

            CalcVertElement(ePtr, rcLay, rc);

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
