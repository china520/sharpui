// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// RadioButton.cpp

#include <sui/RadioButton.h>
#include <suic/render/uirender.h>
#include <internal/RadioGroupManager.h>

namespace ui
{

ImplementTypeofInfo(RadioButton, CheckButton)

RadioButton::RadioButton()
{
    SetClassName(_T("RadioButton"));
}

RadioButton::~RadioButton()
{
}

static suic::String g_sr_key = _T("sharpui.radiogrp");

static RadioGroupManager* GetRadioGroupManager(suic::Element* pElem)
{
    suic::VisualHostPtr hostObj = suic::HwndHelper::GetVisualHost(pElem);

    if (!hostObj)
    {
        return NULL;
    }
    else
    {
        suic::ObjectPtr objGrp = hostObj->GetValue(g_sr_key);

        if (!objGrp)
        {
            return NULL;
        }
        else
        {
            return dynamic_cast<RadioGroupManager*>(objGrp.get());
        }
    }
}

void RadioButton::SetGroup(suic::String name)
{
    if (!_sGrpName.Equals(name))
    {
        RadioButtonPtr thisPtr(this);
        RadioGroupManager * radioGrp = GetRadioGroupManager(this);

        if (radioGrp)
        {
            radioGrp->RemoveRadioFromGroup(thisPtr);
            _sGrpName = name;
            radioGrp->CheckGroupElement(thisPtr);
        }
        else
        {
            _sGrpName = name;
        }
    }
}

suic::String RadioButton::GetGroup() const
{
    return _sGrpName;
}

void RadioButton::SetCheck()
{
    // 没有初始化，直接返回
    if (!IsInitialized())
    {
        return;
    }

    if (!_bChecked)
    {
        bool bAuto = SetAutoDelete(false);

        RadioGroupManager * radioGrp = GetRadioGroupManager(this);
        RadioButtonPtr rdPtr;

        if (radioGrp)
        {
            rdPtr = radioGrp->LookupCheckedRadioFromGroup(_sGrpName);

            suic::SystemHelper::suiTrace(_T("radioGrp->LookupCheckedRadioFromGroup(_sGrpName)\n"));
        }

        // 取消组里已经被选中的控件
        if (NULL != rdPtr)
        {
            rdPtr->SetUncheck();
        }

        _bChecked = true;

        // 触发一次绘制
        InvalidateVisual();

        CheckedEventArg evt(_bChecked);

        if (NULL != Checked)
        {
            //TriggerEvent(Checked,evt);
        }

        SetAutoDelete(bAuto);
    }
    else
    {
        InvalidateVisual();
    }
}

void RadioButton::SetUncheck()
{
    // 没有初始化，直接返回
    if (!IsInitialized())
    {
        return;
    }

    if (_bChecked)
    {
        bool bAuto = SetAutoDelete(false);

        _bChecked = false;

        // 触发一次绘制
        InvalidateVisual();

        CheckedEventArg evt(_bChecked);

        if (NULL != Checked)
        {
            //TriggerEvent(Checked,evt);
        }

        SetAutoDelete(bAuto);
    }
}

//////////////////////////////////////////////////////////////////////////////
// RadioButton
//
void RadioButton::OnPropertyChanged(suic::PropertyChangedEventArg& e)
{
    //
    // 初始化控件本身资源
    //
    if (e.GetName().Equals(_T("Group")))
    {
        SetGroup(e.GetSetter()->ToString());
    }
    else
    {
        //
        // 必须先调用基类初始化基本数据
        //
        __super::OnPropertyChanged(e);
    }
}

void RadioButton::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

void RadioButton::OnLoaded(suic::LoadedEventArg& e)
{
    suic::VisualHostPtr hostObj = suic::VisualHostPtr::cast(e.GetTarget());
    suic::ObjectPtr objGrp = hostObj->GetValue(g_sr_key);

    if (!objGrp)
    {
        objGrp = new RadioGroupManager();
        hostObj->SetValue(g_sr_key, objGrp);
    }

    RadioGroupManager * radioGrp = dynamic_cast<RadioGroupManager*>(objGrp.get());

    if (radioGrp)
    {
        ui::RadioButtonPtr thisPtr(this);

        radioGrp->CheckGroupElement(thisPtr);
    }

    __super::OnLoaded(e);
}

void RadioButton::OnKeyDown(suic::KeyboardEventArg& e)
{
    if (e.IsSpacePress())
    {
        if (IsFocused())
        {
            SetCheck();

            e.SetHandled(true);
        }
    }
}


void RadioButton::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    ButtonBase::OnMouseLeftButtonUp(e);

    if (IsMouseOver())
    {
        SetCheck();
    }
    else
    {
        InvalidateVisual();
    }
}

void RadioButton::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    OnMouseLeftButtonDown(e);
}

void RadioButton::OnGotFocus(suic::FocusEventArg& e)
{
    __super::OnGotFocus(e);
}

void RadioButton::OnLostFocus(suic::FocusEventArg& e)
{
}

};