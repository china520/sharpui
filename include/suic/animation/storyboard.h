// 华勤科技版权所有 2010-2012
// 
// 文件名：StoryBoard.h
// 功  能：管理动画的播放。
// 
// 作  者：汪荣
// 时  间：2010-05-01
// 
// ===================================================

# ifndef _UISTORYBOARD_H_
# define _UISTORYBOARD_H_

#include <suic/animation/animation.h>
#include <suic/core/uiobject.h>
#include <suic/framework/uielement.h>
#include <suic/core/uiinterface.h>
#include <suic/tools/locker.h>

namespace suic
{

class SUICORE_API AnimationEntry : public RefObject
{
public:

    AnimationEntry();
    void OnPlaying(int id);

protected:

    FrameworkElement* owner;
    AnimationPtr ani;
    suic::Int32 timerid;

    friend class StoryBoard;
};

typedef shared<AnimationEntry> AnimationEntryPtr;

class SUICORE_API StoryBoard : public RefObject
{
public:

    StoryBoard();
    virtual ~StoryBoard();

    static bool IsRunning(FrameworkElement* pElem);
    static void StopAnimation(FrameworkElement* pElem);

    /// <summary>
    ///     启动动画
    /// </summary>
    /// <remarks>
    ///     该方法为异步启动，因此在播放期间，StoryBoard
    ///     对象地址需要保证有效，重复调用此方法会停止上
    ///     一次的动画播放，一个StoryBoard一次仅仅关联一个元素
    /// </remarks>
    /// <param name="pElem">目标元素</param>
    /// <returns>无</returns>
    void Start(FrameworkElement* pElem);

    /// <summary>
    ///     播放动画
    /// </summary>
    /// <remarks>
    ///     该方法在指定的元素上播放定义好的动画
    ///     此方法需要等所有动画播放完后才会返回
    /// </remarks>
    /// <param name="pElem">目标元素</param>
    /// <returns>无</returns>
    void Play(FrameworkElement* pElem);

    /// <summary>
    ///     暂停播放动画
    /// </summary>
    /// <remarks>
    ///     该方法将会暂停加入的所有动画播放
    /// </remarks>
    /// <returns>无</returns>
    void Pause();
    void Stop();
    void Resume();

    /// <summary>
    ///     加入动画
    /// </summary>
    /// <remarks>
    ///     加入指定类型的动画到演示版
    /// </remarks>
    /// <param name="pAni">播放的动画对象</param>
    /// <returns>无</returns>
    void Add(Animation* pAni);
    void Remove(Animation* pAni);
    
    int GetCount();
    Animation* GetAnimate(int index);
    Animation* CurrentAnimate();

    /// <summary>
    ///     清除加入的所有动画
    /// </summary>
    /// <returns>无</returns>
    void Clear();

    void OnAnimateFinished(Animation*);

protected:

    // 存放播放的动画对象
    Vector<AnimationEntryPtr> _anis;
    FrameworkElement* _owner;
    Animation* _currentAnimate;

    int _state;
    Mutex _locker;
};

typedef shared<StoryBoard> StoryBoardPtr;


class SUICORE_API StoryBoardInfo : public RefObject
{
public:

    StoryBoardPtr stb;
    AnimationPtr ani;
};

typedef shared<StoryBoardInfo> StoryBoardInfoPtr;

}

# endif
