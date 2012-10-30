/////////////////////////////////////////////////////
// MainFrame.cpp

#include "stdafx.h"

#include "MainFrame.h"
#include <animation/DoubleAnimation.h>
#include <animation/StoryBoard.h>

MainFrame::MainFrame()
{ 
    _bDefault = true;
}

MainFrame::~MainFrame()
{
}

void MainFrame::OnInitialized()
{
    __super::OnInitialized();

    ui::ButtonPtr pBtn = ui::ButtonPtr::cast(FindName(_T("TestAni")));

    if (pBtn)
    {
        // 注册按钮的点击事件
        pBtn->Click += ui::ClickEventHandler(this, &MainFrame::OnTestAni);
    }

    pBtn = ui::ButtonPtr::cast(FindName(_T("TestWndAni")));

    if (pBtn)
    {
        pBtn->Click += ui::ClickEventHandler(this, &MainFrame::OnTestWndAni);
    }

    pBtn = ui::ButtonPtr::cast(FindName(_T("SkinBtn")));

    if (pBtn)
    {
        pBtn->Click += ui::ClickEventHandler(this, &MainFrame::OnChangeSkin);
    }
    
    ui::SliderPtr pSld = FindName(_T("sld"));

    if (pSld)
    {
        pSld->ValueChanged += ui::ValueChangedEventHandler(this, &MainFrame::OnValueChanged);
    }

    ui::TreeViewPtr treePtr(FindName(_T("Tree01")));

    if (treePtr)
    {
        treePtr->ItemSelected += ui::SelectTreeItemHandler(this, &MainFrame::OnTreeItemSelect);
    }

    // TabItem选择事件
    ui::TabControlPtr tab(FindName(_T("TestTab")));

    if (tab)
    {
        tab->ItemSelected += ui::ItemSelectedHandler(this, &MainFrame::SelectTabItem);
    }

    pBtn = ui::ButtonPtr::cast(FindName(_T("SwitchLayered")));

    if (pBtn)
    {
        pBtn->Click += ui::ClickEventHandler(this, &MainFrame::OnSwitchLayered);
    }

    // 启动和停止动画
    pBtn = ui::ButtonPtr::cast(FindName(_T("StartAni")));

    if (pBtn)
    {
        pBtn->Click += ui::ClickEventHandler(this, &MainFrame::OnStartAni);
    }

    pBtn = ui::ButtonPtr::cast(FindName(_T("StopAni")));

    if (pBtn)
    {
        pBtn->Click += ui::ClickEventHandler(this, &MainFrame::OnStopAni);
    }
    
    ui::ListViewPtr listPtr(FindName(_T("ListView01")));

    if (listPtr)
    {
        listPtr->Columns()->Add(_T("歌曲"), 100);
        listPtr->Columns()->Add(_T("演唱者"), 80);

        int index = listPtr->AddChild(new ui::ListViewItem());
        ui::ListViewItemPtr item(listPtr->GetItem(index));

        item->AddColumn(_T("真心英雄"));
        item->AddColumn(_T("周华健"));

        // 使用资源文件定义样式动态设置ListViewItem
        item->SetStyle(FindResource(_T("SelfDefStyle")));

        index = listPtr->AddChild(new ui::ListViewItem());
        item = listPtr->GetItem(index);

        item->AddColumn(_T("动态样式"));
        item->AddColumn(_T("周华健"));

        // 单独设置ListViewItem样式
        // 动态增加的样式自动使用共享资源
        // 这里copy一个新的样式
        item->SetStyle(item->GetStyle()->Clone());
        item->SetValue(suic::BACKGROUND, new suic::SolidColorBrush(ARGB(255,22,88,200)));
    }
}

void MainFrame::SelectTabItem(suic::Element* sender)
{
    ui::TabItemPtr tab(sender);
    suic::FrameworkElementPtr cont(tab->GetTabContent());

    if (cont)
    {
        suic::StoryBoardPtr pSb = new suic::StoryBoard();
        suic::Animation* pAni = new ui::DoubleAnimation(suic::OPACITY, 0, 1);

        // 设置为True，动画正向和方向各执行一次
        //pAni->SetAutoReverse(true);
        pAni->SetSpeedRatio(60);
        pAni->SetDuration(0.5);
        pSb->Add(pAni);
        pSb->Start(cont.get());
    }
}

void MainFrame::OnValueChanged(suic::Element* sender, double o, double n)
{
    ui::ProgressBarPtr pb = FindName(_T("pb"));

    if (pb)
    {
        pb->SetValue(n);
    }
}

void MainFrame::OnTreeItemSelect(ui::TreeViewItem* pItem)
{
    suic::String text = pItem->GetText();

    ui::MsgBox::Show(_T("Info"), text);
}

void MainFrame::OnTestAni(suic::ElementPtr pElem)
{
    suic::FrameworkElementPtr frame(pElem.get());

    suic::ResourceDictionaryPtr resPtr(suic::Application::LoadComponent(NULL, _T("主界面/resource1.xml")));

    if (resPtr)
    {
        suic::ApplicationPtr pApp(suic::Application::Current());

        pApp->SetResources(resPtr);
    }

    suic::StoryBoard::StopAnimation(frame.get());

    suic::StoryBoardPtr pSb = new suic::StoryBoard();
    suic::AnimationPtr widPtr(new ui::DoubleAnimation(suic::WIDTH, 20, frame->GetWidth(), true));
    
    widPtr->SetDuration(0.4);

    pSb->Add(widPtr.get());
    pSb->Add(new ui::DoubleAnimation(suic::OPACITY, 0, 1));
    pSb->Start(frame.get());
}

void MainFrame::OnChangeSkin(suic::ElementPtr pElem)
{
    // 下面切换系统资源，进行动态换肤
    if (_bDefault)
    {
        CoreApp::Current()->SetResources(_T("res/black_res.xml"));
    }
    else
    {
        CoreApp::Current()->SetResources(_T("res/default.xml"));
    }

    _bDefault = !_bDefault;
}

void MainFrame::OnSwitchLayered(suic::ElementPtr pElem)
{
    bool bLayered = ReadFlag(CoreFlags::IsLayeredWindow);

    if (bLayered)
    {
        SetValue(suic::ISLAYEREDWINDOW, new suic::UString(_T("False")));
        SetText(_T("Sharpui界面引擎演示(普通)"));

        suic::ImageBrushPtr bk(GetValue(_T("Background")));

        if (bk)
        {
            bk->SetOpacity(1.0);
        }
    }
    else
    {
        SetValue(suic::ISLAYEREDWINDOW, new suic::UString(_T("True")));

        suic::ImageBrushPtr bk(GetValue(_T("Background")));

        if (bk)
        {
            bk->SetOpacity(0.8);
        }
        //SetOpacity(0.8);
        SetText(_T("Sharpui界面引擎演示(分层)"));
    }

    InvalidateVisual();
}

void MainFrame::OnStartAni(suic::ElementPtr pElem)
{
    ui::AnimateBoxPtr aniPtr(FindName(_T("ani")));

    if (aniPtr)
    {
        aniPtr->Start();
    }
}

void MainFrame::OnStopAni(suic::ElementPtr pElem)
{
    ui::AnimateBoxPtr aniPtr(FindName(_T("ani")));

    if (aniPtr)
    {
        aniPtr->Stop();
    }
}

void MainFrame::OnTestWndAni(suic::ElementPtr pElem)
{
    suic::StoryBoardPtr pSb = new suic::StoryBoard();
    suic::Animation* pAni = new ui::DoubleAnimation(suic::OPACITY, 1, 0);
    
    // 从主窗口开始查找Name为MainContainer的元素
    // 这里所有呈现在界面上的元素都必须派生至FrameworkElement
    suic::FrameworkElementPtr pSln = FindName(_T("MainContainer"));

    // 设置为True，动画正向和方向各执行一次
    pAni->SetAutoReverse(true);
    pAni->SetSpeedRatio(60);
    pAni->SetDuration(0.5);
    pSb->Add(pAni);
    pSb->Start(pSln.get());

    // 下面切换系统资源，进行动态换肤
    suic::ResourceDictionaryPtr resPtr(CoreApp::LoadComponent(NULL, _T("主界面/resource.xml")));

    if (resPtr)
    {
        suic::ApplicationPtr pApp(CoreApp::Current());

        pApp->SetResources(resPtr);
    }
}

void MainFrame::OnLoaded(suic::LoadedEventArg& e)
{
    __super::OnLoaded(e);

    // 窗口居中显示
    CenterWindow();

    // 设置窗体支持层样式，这样，才可以对其进行透明度动画
    SetValue(suic::ISLAYEREDWINDOW, new suic::UString(_T("True")));

    // 创建动画显示板
    suic::StoryBoardPtr pSb = new suic::StoryBoard();
    // 创建一个Double渐变动画
    suic::Animation* pAni = new ui::DoubleAnimation(suic::OPACITY, 0, 1);

    // 设置速率为60毫秒
    pAni->SetSpeedRatio(60);
    // 设置执行时间段为2秒
    pAni->SetDuration(2);
    // 把动画加到动画演示版
    pSb->Add(pAni);

    // 启动动画，加入到演示版的每个动画都会启动
    // 一个独立的定时器
    pSb->Start(this);
}