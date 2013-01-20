// 华勤科技版权所有 2010-2011
// 
// 文件名：TextBlock.h
// 功  能：实现文本块绘制。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UITEXTBLOCK_H_
# define _UITEXTBLOCK_H_

#include <sui/sharpuiconfig.h>
#include <suic/framework/uicontrol.h>

namespace ui
{

class SHARPUI_API TextBlock : public suic::FrameworkElement
{
public:

    TextBlock();
    TextBlock(suic::String text);
    virtual ~TextBlock();

    DeclareTypeofInfo(TextBlock, suic::FrameworkElement)

    bool IsSingle() const;
    void SetSingle(bool val);

protected:

    suic::Size MeasureOverride(const suic::Size& availableSize);

    void OnInitialized();
    void OnRender(suic::DrawingContext * drawing);

    void OnPropertyChanged(suic::PropertyChangedEventArg& e);

protected:

    bool _single;
};

typedef suic::shared<TextBlock> TextBlockPtr;

inline bool TextBlock::IsSingle() const
{
    return _single;
}

inline void TextBlock::SetSingle(bool val)
{
    _single = val;
}

};

# endif
