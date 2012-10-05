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

#include <suicore/uiobject.h>
#include <suicore/uistructure.h>

class MainFrame : public suic::Window
{
public:

    MainFrame();
    ~MainFrame();

    void OnInitialized();

    void OnTreeItemSelect(ui::TreeViewItem* pItem);

    void OnTestAni(suic::ElementPtr pElem);
    void OnTestWndAni(suic::ElementPtr pElem);
    void OnChangeSkin(suic::ElementPtr pElem);

    void OnValueChanged(suic::Element* sender, double o, double n);

    void OnLoaded(suic::LoadedEventArg& e);

protected:

    bool _bDefault;

};

#endif

