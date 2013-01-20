// 华勤科技版权所有 2010-2011
// 
// 文件名：MainWindow.h
// 功  能：管理界面工程。
// 
// 作  者：汪荣
// 时  间：2012-02-02
// 
// ============================================================================

# ifndef _UIMAINWINDOW_H_
# define _UIMAINWINDOW_H_

class MainFrame : public suic::Window
{
public:

    MainFrame();
    ~MainFrame();

    void OnInitialized();

    void OnTreeItemSelect(ui::TreeViewItem* pItem);

    void OnTestAni(suic::Element* pElem);
    void OnTestWndAni(suic::Element* pElem);
    void OnChangeSkin(suic::Element* pElem);

    void OnSwitchLayered(suic::Element* pElem);

    void OnStartAni(suic::Element* pElem);
    void OnStopAni(suic::Element* pElem);

    void OnOpenUri(suic::Element* pElem);

    void SelectTabItem(suic::Element* sender);
    void OnValueChanged(suic::Element* sender, double o, double n);

    void OnLoaded(suic::LoadedEventArg& e);

    void OnFinishAni(suic::FrameworkElement* pElem);

protected:

    bool _bDefault;

};

#endif

