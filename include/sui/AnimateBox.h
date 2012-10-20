// 华勤科技版权所有 2010-2011
// 
// 文件名：AnimateBox.h
// 功  能：实现动画控件
// 
// 作  者：汪荣
// 时  间：2010-07-08
// 
// ============================================================================

# ifndef _UIANIMATEBOX_H_
# define _UIANIMATEBOX_H_

#include <sui/sharpuiconfig.h>
#include <suicore/uicontrol.h>

namespace ui
{

/// <summary>
///  动画控件，能够加载关键帧和GIF动画
/// </summary>
class SHARPUI_API AnimateBox : public suic::Control
{
public:

    AnimateBox();
    virtual ~AnimateBox();

    DECLAREBUILD(AnimateBox)

    void Start();
    void Stop();

    /// <summary>
    ///     取得动画播放中所有的帧数。
    /// </summary>
    /// <param name="e">事件</param>
    /// <returns>动画帧数</returns>
    int FrameCount() const;

    /// <summary>
    ///     取得当前需要播放的帧。
    /// </summary>
    /// <param name="e">事件</param>
    /// <returns>当前播放的动画帧</returns>
    suic::ImagePtr CurrentFrame() const;
    int CurrentElapse() const;
    int CurrentTransparent() const;

    void NextFrame();
    void PrevFrame();
    void Clear();

    /// <summary>
    ///     取得动画播放中所有的帧数。
    /// </summary>
    /// <param name="bmp">帧图像</param>
    /// <param name="iElapse">下一帧的播放时间</param>
    /// <returns>无</returns>
    void AddFrame(suic::ImagePtr bmp, int iElapse, int iTransparent);
    void AddGif(const suic::String& strPath);

protected:

    suic::Size MeasureOverride(const suic::Size& size);

    void OnSetterChanged(suic::SetterChangedEventArg& e);

    void OnInitialized();
    void OnLoaded(suic::LoadedEventArg& e);
    void OnRender(suic::DrawingContext * drawing);

    void OnTimer(int id);

protected:

    suic::Vector<suic::AnimateItem> _frames;

    // 当前播放的动画帧索引
    int _curframe;
    int _anim_timer;

    int _wid;
    int _hei;

    suic::Color _bkcolor;

    suic::ImagePtr _frame;
    suic::TimerIdentityPtr _timerid;
};

typedef suic::shared<AnimateBox> AnimateBoxPtr;

inline int AnimateBox::FrameCount() const
{
    return static_cast<int>(_frames.size());
}

};

# endif