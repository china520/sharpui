// 华勤科技版权所有 2010-2012
// 
// 文件名：Timeline.h
// 功  能：定义动画的时间线类，任何动画将从这个类继承。
// 
// 作  者：汪荣
// 时  间：2012-02-01
// 
// ============================================================================

# ifndef _UITIMELINE_H_
# define _UITIMELINE_H_

#include <suic/core/uiobject.h>

namespace suic
{

class SUICORE_API Timeline : public RefObject
{
public:

    Timeline();
    virtual ~Timeline();

    /// <summary>
    ///     设置正反序运行属性。
    /// </summary>
    /// <remarks>
    ///     该属性如果为True，指定动画将正序运行后，反序运行一次。
    /// </remarks>
    /// <returns>true: 正序运行后，反序运行一次</returns>
    bool GetAutoReverse() const;
    void SetAutoReverse(bool val);

    double GetAccelerationRatio() const;
    void SetAccelerationRatio(double val);

    /// <summary>
    ///     动画运行开始时间。
    /// </summary>
    /// <remarks>
    ///     相对于Duration的动画开始时间。
    /// </remarks>
    /// <returns>动画开始时间</returns>
    double GetBeginTime() const;
    void SetBeginTime(double val);

    double GetDuration() const;
    void SetDuration(double val);

    /// <summary>
    ///     设置和获取播放动画的方式。
    /// </summary>
    /// <returns>播放动画的方式</returns>
    int GetPlayMode() const;
    void SetPlayMode(int val);

    /// <summary>
    ///     设置和获取动画的重复类型。
    /// </summary>
    /// <returns>动画的重复类型</returns>
    int GetRepeatMode() const;
    void SetRepeatMode(int val);
    
    /// <summary>
    ///     设置和获取动画的播放速率。
    /// </summary>
    /// <returns>动画的播放速率</returns>
    double GetSpeedRatio() const;
    void SetSpeedRatio(double val);
    
protected:

    bool _autoReverse;
    double _beginTime;
    double _accRatio;
    int _fillMode;
    int _repeatMode;
    double _speedRatio;
    double _duration;
};

typedef shared<Timeline> TimelinePtr;

};

# endif
