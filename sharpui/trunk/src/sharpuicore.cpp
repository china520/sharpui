// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// SharpuiCore.cpp

#include <sui/sharpuicore.h>

#include <sui/button.h>
#include <sui/repeatedbutton.h>
#include <sui/captionbar.h>
#include <sui/scrollviewer.h>
#include <sui/wrappanel.h>
#include <sui/stacklayout.h>
#include <sui/tabpanel.h>
#include <sui/progressbar.h>
#include <sui/checkbutton.h>
#include <sui/radiobutton.h>
#include <sui/scrollbar.h>
#include <sui/slider.h>
#include <sui/textblock.h>
#include <sui/label.h>
#include <sui/itemscontrol.h>
#include <sui/combobox.h>
#include <sui/textbox.h>
#include <sui/listbox.h>
#include <sui/imagebox.h>
#include <sui/listview.h>
#include <sui/treeview.h>
#include <sui/menuitem.h>
#include <sui/menu.h>
#include <sui/separator.h>
#include <sui/tabcontrol.h>
#include <sui/tabitem.h>
#include <sui/Splitter.h>

#include <sui/activexhost.h>
#include <sui/webbrowser.h>
#include <sui/richtextbox.h>
#include <sui/PasswordBox.h>
#include <sui/AnimateBox.h>

#include <sui/MessageBox.h>

namespace ui
{

////////////////////////////////////////////////////////////
// UIBuilder
}

suic::ObjectPtr __CreateContent(suic::ObjectPtr val)
{
    suic::ElementPtr pElem(val);
    
    if (!pElem)
    {
        pElem = new ui::TextBlock(val->ToString());
    }

    return pElem;
}

void SHARPUI_API CoreInitialize(const suic::String& resPath)
{
    suic::SystemHelper::suiInitialize();

    suic::Builder::RegisterElement(suic::BUTTON, &ui::Button::Create);
    suic::Builder::RegisterElement(_T("RepeatedButton"), &ui::RepeatedButton::Create);

    suic::Builder::RegisterElement(_T("SystemMinButton"), &ui::SystemMinButton::Create);
    suic::Builder::RegisterElement(_T("SystemMaxButton"), &ui::SystemMaxButton::Create);
    suic::Builder::RegisterElement(_T("SystemCloseButton"), &ui::SystemCloseButton::Create);

    suic::Builder::RegisterElement(suic::STACKPANEL, &ui::StackPanel::Create);
    suic::Builder::RegisterElement(_T("StackLayout"), &ui::StackLayout::Create);
    suic::Builder::RegisterElement(_T("WrapPanel"), &ui::WrapPanel::Create);

    suic::Builder::RegisterElement(_T("ProgressBar"), &ui::ProgressBar::Create);
    suic::Builder::RegisterElement(_T("PasswordBox"), &ui::PasswordBox::Create);
    suic::Builder::RegisterElement(suic::COMBOBOX, &ui::ComboBox::Create);
    suic::Builder::RegisterElement(suic::CHECKBUTTON, &ui::CheckButton::Create);
    suic::Builder::RegisterElement(suic::RADIOBUTTON, &ui::RadioButton::Create);
    suic::Builder::RegisterElement(suic::SCROLLBAR, &ui::ScrollBar::Create);

    suic::Builder::RegisterElement(_T("AnimateBox"), &ui::AnimateBox::Create);
    suic::Builder::RegisterElement(suic::LISTBOX, &ui::ListBox::Create);   
    suic::Builder::RegisterElement(_T("ListBoxItem"), &ui::ListBoxItem::Create);

    suic::Builder::RegisterElement(_T("ListView"), &ui::ListView::Create);
    suic::Builder::RegisterElement(_T("ListViewItem"), &ui::ListViewItem::Create);

    suic::Builder::RegisterElement(_T("ScrollViewer"), &ui::ScrollViewer::Create);

    suic::Builder::RegisterElement(_T("Label"), &ui::Label::Create);

    suic::Builder::RegisterElement(_T("TreeView"), &ui::TreeView::Create);
    suic::Builder::RegisterElement(_T("TreeViewItem"), &ui::TreeViewItem::Create);
    suic::Builder::RegisterElement(_T("ComboBoxItem"), &ui::ComboBoxItem::Create);
    suic::Builder::RegisterElement(_T("CaptionBar"), &ui::CaptionBar::Create);
    suic::Builder::RegisterElement(suic::TEXTBOX, &ui::TextBox::Create);
    suic::Builder::RegisterElement(_T("TextBlock"), &ui::TextBlock::Create);
    suic::Builder::RegisterElement(_T("TabControl"), &ui::TabControl::Create);
    suic::Builder::RegisterElement(_T("TabItem"), &ui::TabItem::Create);
    suic::Builder::RegisterElement(_T("Menu"), &ui::Menu::Create);
    suic::Builder::RegisterElement(_T("MenuItem"), &ui::MenuItem::Create);
    suic::Builder::RegisterElement(_T("Separator"), &ui::Separator::Create);
    suic::Builder::RegisterElement(_T("Slider"), &ui::Slider::Create);
    suic::Builder::RegisterElement(_T("ImageBox"), &ui::ImageBox::Create);

    suic::Builder::RegisterElement(_T("MessageBox"), &ui::MsgBox::Create);

    suic::Builder::RegisterElement(_T("Splitter"), &ui::Splitter::Create);

    suic::Builder::RegisterElement(_T("WebBrowser"), &ui::WebBrowser::Create);
    suic::Builder::RegisterElement(_T("RichTextBox"), &ui::RichTextBox::Create);
    suic::Builder::RegisterElement(_T("ActiveXHost"), &ui::ActiveXHost::Create);

    suic::SystemHelper::ReadResource(resPath);
    //suic::SystemHelper::RegisterContent(__CreateContent);
}
