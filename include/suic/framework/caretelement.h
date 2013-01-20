// 华勤科技版权所有 2010-2011
// 
// 文件名：CaretElement.h
// 功  能：处理光标逻辑。
// 
// 作  者：汪荣
// 时  间：2012-07-02
// 
// ============================================================================

# ifndef _UICARETELEMENT_H_
# define _UICARETELEMENT_H_

#include <suic/framework/uiframeworkelement.h>

namespace suic {

class SUICORE_API CaretElement : public FrameworkElement
{
public:

    CaretElement();
    virtual ~CaretElement();

    DeclareTypeofInfo(CaretElement, FrameworkElement)

    void Show();
    void Hide();

protected:

    void OnTimer(int id);
    void OnUnloaded(LoadedEventArg& e);
    void OnInitialized();
    void OnRender(DrawingContext * drawing);

protected:

    suic::Int32 _timerid;
};

}

# endif
