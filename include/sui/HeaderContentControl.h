// 华勤科技版权所有 2010-2011
// 
// 文件名：HeaderContentContro.h
// 功  能：带有标题和内容的控件
// 
// 作  者：汪荣
// 时  间：2011-12-25
// 
// ============================================================================

# ifndef _UIHEADERCONTENTCONTROL_H_
# define _UIHEADERCONTENTCONTROL_H_

#include <sui/ItemContainer.h>

namespace ui
{

// ============================================================
// HeaderContentControl所有标题类基类。
// ============================================================
class SHARPUI_API HeaderedContentControl : public suic::ContentControl
{
public:

    HeaderedContentControl();
    virtual ~HeaderedContentControl();

    suic::ElementPtr GetHeader();
    void SetHeader(suic::ElementPtr val);

    int GetIndent() const;
    void SetIndent(int val);

public:

    void OnHeaderChanged(suic::Element* oldHeader, suic::Element* newHeader);
    void OnHeaderClicked(suic::Element* header);

    int AddChild(suic::ObjectPtr child);

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnInitialized();
    void OnRender(suic::DrawingContext * drawing);

    void OnTextInput(suic::KeyEventArg& e);
    void OnKeyDown(suic::KeyEventArg& e);

    void OnPreviewMouseLeftButtonDown(suic::MouseEventArg& e);

protected:

    suic::ElementPtr _header;
    int _indent;
};

typedef suic::shared<HeaderedContentControl> HeaderContentControlPtr;

inline int HeaderedContentControl::GetIndent() const
{
    return _indent;
}

inline void HeaderedContentControl::SetIndent(int val)
{
    _indent = val;
}

};

# endif
