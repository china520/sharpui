//	Copyright (c) 2008-2009, Inc, 华勤科技版权所有.
//
//	文件名 : uithread.h.h
//	描  述 : 封装线程对象，自动完成启动，挂起操作。
//
//	基  类 : no
//	
//	版  本 : 1.0
//	作  者 : 汪荣
//	日  期 : 2008-08-10

// 修改记录 ==================================================================
// 日期				名称			版本		评述
// 
// ===========================================================================

# ifndef _UITHREAD_H_
# define _UITHREAD_H_

#include <suicore/uiobject.h>
#include <util/locker.h>

namespace suic {

class ThreadControl : public RefObject
{
public:

    /*
     * 构造函数默认得到当前线程，但是不能调用join和detach
     */
    ThreadControl();

#ifdef __OS_WIN32
    ThreadControl(HANDLE, DWORD);
#else
    explicit ThreadControl(pthread_t);
#endif

    /*
     * 功  能: 判断两个线程是否相等，此函数只有在线程有效时调用才有意义
     * 参  数: 无
     * 返回值: 无
     * 异  常: 无
     */
    bool operator==(const ThreadControl&) const;
    bool operator!=(const ThreadControl&) const;

    /*
     * 功  能: 等待直到线程执行结束
     * 参  数: 无
     * 返回值: 无
     * 异  常: 无
     */
    void join();

    /*
     * 功  能: 关闭线程，此函数和join只能被调用一次，再次调用可能会引起未定义的错误
     * 参  数: 无
     * 返回值: 无
     * 异  常: 无
     */
    void detach();

    /*-
     * 线程ID
     */
#ifdef __OS_WIN32
    typedef DWORD ID;
#else
    typedef pthread_t ID;
#endif 
    ID id() const;

    static void sleep(const Int32&);
    static void yield();

private:

#ifdef __OS_WIN32
    HANDLE _handle;
    DWORD  _id;
#else
    pthread_t _thread;
    bool _detachable;
#endif
};

class Thread : virtual public RefObject
{
public:

    Thread();
    virtual ~Thread();

    virtual void Run() = 0;

    ThreadControl Start(Int32 = 0);
    ThreadControl GetThreadControl() const;

    bool operator==(const Thread&) const;
    bool operator!=(const Thread&) const;
    bool operator<(const Thread&) const;

    //
    // 检测一个线程是否在运行中
    //
    bool IsAlive() const;

    void Clear();
    void Join();

    static void Sleep(const Int32&);
    static void YieldThr();
    static Uint32 CurrentThreadId();

public:

    void _Done();

protected:

    Mutex _stateMutex;
    bool _started;
    bool _running;

#ifdef __OS_WIN32
    HANDLE _handle;
    DWORD  _id;
#else
    pthread_t _thread;
#endif

private:

    Thread(const Thread&);
    void operator=(const Thread&); 
};

typedef shared<Thread> ThreadPtr;

}

# endif