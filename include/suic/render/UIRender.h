// 华勤科技版权所有 2010-2011
// 
// 文件名：UIRender.h
// 功  能：定义外部的回调接口
// 
// 作  者：汪荣
// 时  间：2010-07-12
// 
// ============================================================================

# ifndef _UIDRAWING_H_
# define _UIDRAWING_H_

#include <suic/graphics/uidrawing.h>
#include <suic/framework/uicontrol.h>
#include <suic/graphics/uifont.h>

namespace suic
{

class SUICORE_API Render : public RefObject
{
public:

    static ObjectPtr GetProperty(FrameworkElement* obj, Style* style, const suic::String& name);

    static void RenderBackground(DrawingContext* drawing, FrameworkElement* obj, const Rect* rc);
    static void RenderBackground(DrawingContext* drawing, FrameworkElement* obj);

    static void RenderBorder(DrawingContext* drawing, FrameworkElement* obj, const Rect* rc);
    static void RenderBorder(DrawingContext* drawing, FrameworkElement* obj);

    static void RenderText(DrawingContext* drawing, suic::FormattedText& fmtTxt, String& text, const Rect* rc, bool bSingle);
    static void RenderText(DrawingContext* drawing, FrameworkElement* obj, String& text, bool bSingle);
    static void RenderText(DrawingContext* drawing, FrameworkElement* obj, Font* pFont, String& text, const Rect* rc, bool bSingle);
    static void RenderText(DrawingContext* drawing, FrameworkElement* obj, String& text, const Rect* rc, bool bSingle);

    static void RenderControl(DrawingContext* drawing, FrameworkElement* obj, bool bSingle);
    static Size MeasureImageSize(const BrushPtr& imPtr);
    static Size MeasureTextSize(String& text, FontPtr& font);
    static Size MeasureCharSize(FontPtr& font);

protected:

    Render() {}
    virtual ~Render();
};

#define RENDER suic::Render

};

# endif

