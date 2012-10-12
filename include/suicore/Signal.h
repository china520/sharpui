//	Copyright (c) 2008-2009, Inc, 华勤科技版权所有.
//
//	文件名 : Signal.h
//	描  述 : 信号量
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

#ifndef __SIGNAL_H
#define __SIGNAL_H

#include <suicore/uiobject.h>

namespace suic
{

class SUICORE_API Signal
{
public:

	Signal(bool bSignal=true);
	Signal(bool bMenuReset,bool bSignal);

	~Signal();

	operator Handle() const;

	bool Wait(int iTimeout=INFINITE);

    /// <summary>
    ///     等待内部和外部事件。
    /// </summary>
    /// <param name="_Other">外部事件</param>
    /// <param name="iTimeout">超时时间</param>
    /// <returns>如果本身事件返回,返回1;如果外部事件返回,返回2;超时返回3;错误-1</returns>
    int Wait(Signal& _Other, int iTimeout=INFINITE);

	void Notify();

	void Reset();

private:

	Handle _signal;
};

}

#endif