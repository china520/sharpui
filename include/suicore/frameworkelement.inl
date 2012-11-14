
inline void FrameworkElement::SetOwner(FrameworkElementPtr elemPtr)
{
	_owerElem = elemPtr;
}

inline CursorPtr FrameworkElement::GetCursor() const
{
    return _cursor;
}

inline FrameworkElementPtr& FrameworkElement::GetOwner()
{
	return _owerElem;
}

inline Uint16 FrameworkElement::GetCommand() const
{
    return _iCommand;
}

inline void FrameworkElement::SetCommand(Uint16 iCmd)
{
    _iCommand = iCmd;
}

inline suic::Int32 FrameworkElement::GetWidth() const
{
    return _width;
}

inline void FrameworkElement::SetWidth(suic::Int32 value)
{
    if (value < 0)
    {
        _width = NonInt;
    }
    else if (value <= GetMinWidth())
    {
        _width = GetMinWidth();
    }
	else
    {
        _width = value;
    }
}

inline suic::Int32 FrameworkElement::GetHeight() const
{
    return _height;
}

inline void FrameworkElement::SetHeight(suic::Int32 value)
{
    if (value < 0)
    {
        _height = NonInt;
    }
    else if (value <= GetMinHeight())
    {
        _height = GetMinHeight();
    }
    else
    {
        _height = value;
    }
}

inline int FrameworkElement::GetActrualWidth() const
{
    return _size.cx;
}

inline void FrameworkElement::SetActrualWidth(int value)
{
    if (value >= 0)
    {
	    _size.cx = value;
    }
}

inline int FrameworkElement::GetActrualHeight() const
{
    return _size.cy;
}

inline void FrameworkElement::SetActrualHeight(int value)
{
    if (value >= 0)
    {
        _size.cy = value;
    }
}

inline Rect FrameworkElement::GetPadding() const
{
    return _rectPadding;
}

inline void FrameworkElement::SetPadding(Rect rc)
{
	_rectPadding = rc;
}

inline Rect FrameworkElement::GetMargin() const
{
    return _rectMargin;
}

inline void FrameworkElement::SetMargin(Rect rc)
{
	_rectMargin = rc;
}

inline Int32 FrameworkElement::GetMaxWidth() const
{
    return _sizeMax.cx;
}

inline void FrameworkElement::SetMaxWidth(Int32 value)
{
    if (value < 0)
    {
        _sizeMax.cx = NonInt;
    }
    else
    {
        _sizeMax.cx = value;
    }
}

inline Int32 FrameworkElement:: GetMaxHeight() const
{
    return _sizeMax.cy;
}

inline void FrameworkElement::SetMaxHeight(Int32 value)
{
    if (value < 0)
    {
        _sizeMax.cy = NonInt;
    }
    else
    {
        _sizeMax.cy = value;
    }
}

inline Int32 FrameworkElement::GetMinWidth() const
{
    return _sizeMin.cx;
}

inline void FrameworkElement::SetMinWidth(Int32 value)
{
    _sizeMin.cx = (LONG)value;
}

inline Int32 FrameworkElement::GetMinHeight() const
{
    return _sizeMin.cy;
}

inline void FrameworkElement::SetMinHeight(Int32 value)
{
    _sizeMin.cy = (LONG)value;
}

inline Rect FrameworkElement::GetBorderThickness() const
{
    return _thickness;
}

inline void FrameworkElement::SetText(const String & text)
{
    _text = text;
}

inline String FrameworkElement::GetText()
{
    return _text;
}