// 华勤科技版权所有 2010-2011
// 
// 文件名：ImageBox.h
// 功  能：实现图像控件。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _IMAGEBOX_H_
# define _IMAGEBOX_H_

#include <sui/sharpuiconfig.h>
#include <suicore/uiframeworkelement.h>

namespace ui
{

class SHARPUI_API ImageBox : public suic::FrameworkElement
{
public:

    ImageBox();
    ImageBox(suic::String source);

    virtual ~ImageBox();

    DECLAREBUILD(ImageBox)

    //Uri GetBaseUri();
    //void GetBaseUri(Uri);
    /// <summary>
    ///     设置图像控件显示的图像路径
    /// </summary>
    /// <param name="source">图像路径</param>
    /// <returns>true:设置成功；false:设置失败</returns>
    bool SetSource(suic::String source);

    bool SetSourceFromMemory(const suic::Byte* pData, suic::Uint64 len);

    /// <summary>
    ///     取得图像控件源，其是一个图像对象
    /// </summary>
    /// <returns>图像对象</returns>
    suic::ImagePtr GetSource() const;

    bool IsValid() const;

protected:

    suic::Size MeasureOverride(const suic::Size& availableSize);

    void OnInitialized();
 
    void OnRender(suic::DrawingContext * drawing);
    void OnLoaded(suic::LoadedEventArg& e);

protected:

    // 图像源对象
    suic::ImagePtr _source;

};

typedef suic::shared<ImageBox> ImageBoxPtr;

};

# endif
