
inline void FrameworkElement::SetOwner(FrameworkElementPtr elemPtr)
{
	_owerElem = elemPtr;
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


