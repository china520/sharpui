// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// EditDoc.cpp

#include "stdafx.h"

#include <sui/TextBoxDoc.h>
#include <assert.h>

namespace ui
{

/////////////////////////////////////////////////////////////////
// GlyphFactory

suic::StringMapPtr GlyphFactory::_glyphs;
static HFONT DefFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);

static suic::Int32 DefTextColor = ARGB(255,0, 0, 0);
static suic::Int32 DefInactivateSelTextBkColor = ARGB(255,191,205,219);
static suic::Int32 DefSelTextBkColor = ARGB(255,51, 153, 255);
static suic::Int32 DefSelTextColor = ARGB(255,255, 255, 255);
static suic::Int32 DefInactivateSelTextColor = ARGB(255,67, 78, 84);

void GlyphFactory::Initialize()
{
    _glyphs = suic::CreateStringMap();
}

GlyphPtr GlyphFactory::GetGlyph(suic::String & key)
{
    suic::ObjectPtr value;

    _glyphs->TryGetValue(key, value);

    return GlyphPtr::cast(value);
}

int GlyphFactory::GetAveCharHei()
{
    TEXTMETRIC tm;
    ::ZeroMemory(&tm, sizeof(TEXTMETRIC));

    HDC hdc = ::GetDC(NULL);
    HFONT oldFont = (HFONT)::SelectObject(hdc, DefFont);
    
    ::GetTextMetrics(hdc, &tm);

    ::SelectObject(hdc, oldFont);
    ::ReleaseDC(NULL, hdc);

    int charHei = tm.tmHeight + 1;

    if (charHei < 12) 
    {
        charHei = 12;
    }

    return charHei;
}

GlyphPtr GlyphFactory::GetGlyph(int key)
{
    suic::String text((suic::Char)key, 1);

    return GetGlyph(text);
}

/////////////////////////////////////////////////////////////////
// TextBoxLine
TextBoxLine::TextBoxLine()
{
    _rcLine.bottom = GlyphFactory::GetAveCharHei();
}

TextBoxLine::~TextBoxLine()
{
}

void TextBoxLine::Draw(suic::DrawingContext * drawing, bool bActive
                       , suic::Rect * lprc, const suic::FormattedText* att)
{
    if (_buff.Length() > 0)
    {
        drawing->DrawText(_buff.c_str(), _buff.Length(), lprc, att);
    }
}

void TextBoxLine::DrawSel(suic::DrawingContext * drawing, bool bActive, suic::Rect * lprc
                          , suic::Uint32 beg, suic::Uint32 end, suic::FormattedText* att)
{
    if (_buff.Length() > 0)
    {
        suic::Size sz;

        if (end == -1)
        {
            att->bkcolor = !bActive ? DefInactivateSelTextBkColor : DefSelTextBkColor;
            att->color = bActive ? DefSelTextColor : DefInactivateSelTextColor;

            drawing->DrawText(_buff.c_str(), _buff.Length(), lprc, att);

            return;
        }

        if (beg > 0)
        {
            sz = drawing->CalculateText(_buff.c_str(), beg, att);

            int nRight = lprc->right;
            lprc->right = lprc->left + sz.cx;

            drawing->DrawText(_buff.c_str(), beg, lprc, att);

            lprc->left = lprc->right;
            lprc->right = nRight;
        }

        sz = drawing->CalculateText(_buff.c_str() + beg, end - beg, att);

        suic::Color oldClr = att->color;
        int nRight = lprc->right;
        lprc->right = lprc->left + sz.cx;

        att->bkcolor = (!bActive ? DefInactivateSelTextBkColor : DefSelTextBkColor);
        att->color = (bActive ? DefSelTextColor : DefInactivateSelTextColor);

        drawing->DrawText(_buff.c_str() + beg, (int)(end - beg), lprc, att);

        lprc->left = lprc->right;
        lprc->right = nRight;

        if (end < (suic::Uint32)_buff.Length())
        {
            att->bkcolor = -1;
            att->color = oldClr;

            sz = drawing->CalculateText(_buff.c_str() + end, (int)_buff.Length() - end, att);
            drawing->DrawText(_buff.c_str() + end, (int)(_buff.Length() - end), lprc, att);
        }
    }
}

void TextBoxLine::GetText(suic::String & str)
{
    str += _buff;
}

void TextBoxLine::GetSelText(suic::String & str, int beg, int len)
{
    str += _buff.Substring(beg, len);
}

void TextBoxLine::Add(suic::Char ch)
{
    _buff += suic::String(ch, 1);

    RefleshRect();
}

void TextBoxLine::Add(const suic::String & str)
{
    _buff += str;

    RefleshRect();
}

void TextBoxLine::Add(const suic::Char * str, int len)
{
    suic::String tmp(str, len);

    _buff += tmp;

    RefleshRect();
}

void TextBoxLine::AddLine(const EditLinePtr & line)
{
    _buff += line->_buff;

    RefleshRect();
}

void TextBoxLine::AddLine(const EditLinePtr & line, int beg, int end)
{
    if (end == -1)
    {
        end = (int)line->_buff.Length();
    }

    suic::String tmp(line->_buff.c_str() + beg, end - beg);

    _buff += tmp;

    RefleshRect();
}

void TextBoxLine::Insert(suic::Char ch, int pos)
{
    suic::String tmp(_buff.c_str(), pos);
    suic::String rTmp(_buff.c_str() + pos, _buff.Length() - pos);

    tmp += suic::String(ch, 1);
    tmp += rTmp;

    _buff = tmp;

    RefleshRect();
}

void TextBoxLine::Insert(const suic::String & str, int pos)
{
    suic::String tmp(_buff.c_str(), pos);
    suic::String rTmp(_buff.c_str() + pos, _buff.Length() - pos);

    tmp += str;
    tmp += rTmp;

    _buff = tmp;

    RefleshRect();
}

void TextBoxLine::Remove()
{
    _buff = suic::String();

    RefleshRect();
}

void TextBoxLine::Remove(int beg, int end)
{
    if (beg < 0) beg = 0;
    if (end < 0) end = (int)_buff.Length();
    if (beg >= end) return;

    suic::String tmp(_buff.Substring(end, _buff.Length() - end));

    _buff = _buff.Substring(0, beg);
    _buff += tmp;

    RefleshRect();
}

static int GetCharType(int ch)
{
    if (ch == '\r' || ch == '\n')
    {
        return 1;
    }
    // 空格
    else if (ch < 0x20 || ch == ' ')
    {
        return 2;
    }
    else if (ch >= 0x80 || isalnum(ch) || ch == '_')
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

void TextBoxLine::SelectWord(int & beg, int & end)
{
    int nPos = beg;
    if (nPos == (int)_buff.Length())
    {
        nPos = (int)_buff.Length() - 1;
    }

    int ch = (int)_buff[nPos];
    int npt = GetCharType(ch);

    beg = nPos;
    end = nPos + 1;

    int i = 0;
    for (i = nPos; i < (int)_buff.Length(); ++i)
    {
        ch = (int)_buff[i];
        if (GetCharType(ch) != npt)
        {
            end = i;
            break;
        }
    }
    end = i;

    for (i = nPos; i >= 0; --i)
    {
        ch = (int)_buff[i];

        if (GetCharType(ch) != npt)
        {
            beg = i + 1;
            break;
        }
    }
    if (-1 == i)
    {
        beg = 0;
    }
}

suic::Uint32 TextBoxLine::GetCount()
{
    return static_cast<suic::Uint32>(_buff.Length());
}

suic::Uint32 TextBoxLine::GetItemCount()
{
    return static_cast<suic::Uint32>(_items.size());
}

void TextBoxLine::GetItem(suic::Uint32 index, LineItem & item)
{
    item = _items[index];
}

void TextBoxLine::GetRect(suic::Rect * lprc)
{
    *lprc = _rcLine;
}

int TextBoxLine::PointIn(suic::Point * lppt)
{
    if (_buff.Length() == 0) 
    {
        return 0;
    }

    int nPos = 0;

    HDC hdc = ::GetDC(NULL);
    HFONT hOld = (HFONT)SelectObject(hdc, DefFont);

    int i = 0;
    for (i = 0; i < (int)_buff.Length(); ++i)
    {
        suic::Size sz;
        ::GetTextExtentPoint(hdc, _buff.c_str(), i + 1, &sz);
        if (sz.cx > lppt->x)
        {
            nPos = i;
            break;
        }
    }

    if (i == (int)_buff.Length())
    {
        nPos = (int)_buff.Length();
    }

    SelectObject(hdc, hOld);
    ::ReleaseDC(NULL, hdc);
    return nPos;
}

int TextBoxLine::Offset(int index)
{
    if (_buff.Length() == 0 || index <= 0) 
    {
        return 0;
    }

    HDC hdc = ::GetDC(NULL);
    HFONT hOld = (HFONT)SelectObject(hdc, DefFont);

    suic::Size sz;
    ::GetTextExtentPoint(hdc, _buff.c_str(), index, &sz);

    SelectObject(hdc, hOld);
    ::ReleaseDC(NULL, hdc);

    return sz.cx;
}

void TextBoxLine::RefleshRect()
{
    HDC hdc = ::GetDC(NULL);
    HFONT hOld = (HFONT)SelectObject(hdc, DefFont);

    RefleshRect(HdcToHandle(hdc));

    SelectObject(hdc, hOld);
    ::ReleaseDC(NULL, hdc);
}

void TextBoxLine::RefleshRect(suic::Handle hdc)
{
    _rcLine.right = 0;
    _rcLine.bottom = GlyphFactory::GetAveCharHei();
    if (_buff.Length() == 0)
    {
        return;
    }

    suic::Size sz;
    ::GetTextExtentPoint(HandleToHdc(hdc), _buff.c_str(), (int)_buff.Length(), &sz);
    _rcLine.right = sz.cx;
    _rcLine.bottom = sz.cy;
}

/////////////////////////////////////////////////////////////////
// EditDoc
//
TextBoxDoc::TextBoxDoc()
    : _horzScroll(0), _vertScroll(0)
    , _caretLine(-1), _caretOffset(0)
    , _trackLine(-1), _trackOffset(-1)
    , _bSingleLine(false)
{
    GlyphFactory::Initialize();

    TEXTMETRIC tm;
    ::ZeroMemory(&tm, sizeof(TEXTMETRIC));

    HDC hdc = ::GetDC(NULL);
    HFONT oldFont = (HFONT)::SelectObject(hdc, DefFont);
    ::GetTextMetrics(hdc, &tm);
    ::SelectObject(hdc, oldFont);
    ::ReleaseDC(NULL, hdc);

    _aveCharWid = tm.tmAveCharWidth;
    if (_aveCharWid < 5) _aveCharWid = 10;
    _aveCharHei = tm.tmHeight + 1;
    if (_aveCharHei < 17) _aveCharHei = 17;

    InsertLine();
    _caretPos.left = 0;
    _caretPos.top = 0;
    _caretPos.bottom = _aveCharHei;
}

TextBoxDoc::~TextBoxDoc()
{
}

void TextBoxDoc::SetVisualRect(suic::Rect * lprc)
{
    _rcVisual.right = lprc->Width();
    _rcVisual.bottom = lprc->Height();
}

int TextBoxDoc::GetHorzScrollPos() const
{
    return _horzScroll;
}

int TextBoxDoc::GetVertScrollPos() const
{
    return _vertScroll;
}

void TextBoxDoc::SetHorzScrollPos(int nNewPos)
{
    _horzScroll = nNewPos;
}

void TextBoxDoc::SetVertScrollPos(int nNewPos)
{
    _vertScroll = nNewPos;
}

void TextBoxDoc::GetHorzScrollInfo(int & iVisual, int & iLogic)
{
    iVisual = _rcVisual.Width();

    iLogic = 0;

    for (int i = 0; i < (int)_lines.size(); ++i)
    {
        suic::Rect rc;
        _lines[i]->GetRect(&rc);

        if (rc.Width() > iLogic)
        {
            iLogic = rc.Width();
        }
    }
}

void TextBoxDoc::GetVertScrollInfo(int & iVisual, int & iLogic)
{
    iVisual = _rcVisual.Height();

    iLogic = 0;

    for (int i = 0; i < (int)_lines.size(); ++i)
    {
        iLogic += _lines[i]->GetLineHei();
    }
}

void TextBoxDoc::Cut()
{
}

void TextBoxDoc::Copy()
{
}

void TextBoxDoc::Paste()
{
}

void TextBoxDoc::SelectAll()
{
    _caretLine = 0;
    _caretOffset = 0;
    _trackLine = (int)_lines.size() - 1;
    _trackOffset = _lines[_trackLine]->GetCount();

    RecalcCaret(false);
}

void TextBoxDoc::DrawSingleLine(suic::DrawingContext * drawing, bool bActive
                                , suic::Rect * lprc, suic::FormattedText* att)
{
    suic::Rect rc;
    int i = 0;
    rc.top = 0;
    int by = _vertScroll * _aveCharHei;
    int ey = _rcVisual.bottom + _vertScroll * _aveCharHei;

    int bline=-1, bl=0, br=0, eline=-1, el=0, er=0;
    bool bSel = CalcSelectPos(bline, bl, br, eline, el, er);

    if (_lines.size() > 0)
    {
        suic::Rect rcdr;
        _lines[i]->GetRect(&rcdr);

        rc.top += (_rcVisual.Height() - rcdr.Height()) / 2;
        rc.bottom = rc.top + rcdr.Height();

        if (rc.bottom >= by)
        {
            // 绘制一行
            suic::Rect rcdr;
            _lines[i]->GetRect(&rcdr);
            rc.right = rcdr.Width();

            rcdr = rc;
            rcdr.Offset(-_horzScroll * _aveCharWid + lprc->left, -_vertScroll * _aveCharHei + lprc->top);

            if (!bSel)
            {
                _lines[i]->Draw(drawing, bActive, &rcdr, att);
            }
            else if (bline == i)
            {
                _lines[i]->DrawSel(drawing, bActive, &rcdr, bl, br, att);
            }
            else if (eline == i)
            {
                _lines[i]->DrawSel(drawing, bActive, &rcdr, el, er, att);
            }
            else if (i > bline && i < eline)
            {
                _lines[i]->DrawSel(drawing, bActive, &rcdr, 0, -1, att);
            }
            else
            {
                _lines[i]->Draw(drawing, bActive, &rcdr, att);
            }
        }
    }
}

void TextBoxDoc::Draw(suic::DrawingContext * drawing, bool bActive
                      , suic::Rect * lprc, suic::FormattedText* att)
{
    suic::Rect rc;
    rc.top = 0;
    int by = _vertScroll * _aveCharHei;
    int ey = _rcVisual.bottom + _vertScroll * _aveCharHei;

    int bline=-1, bl=0, br=0, eline=-1, el=0, er=0;
    bool bSel = CalcSelectPos(bline, bl, br, eline, el, er);

    for (int i = 0; i < (int)_lines.size(); ++i)
    {
        if (rc.top > ey) 
        {
            break;
        }

        suic::Rect rcdr;
        _lines[i]->GetRect(&rcdr);

        rc.bottom = rc.top + rcdr.Height();
        if (rc.bottom >= by)
        {
            // 绘制一行
            suic::Rect rcdr;
            _lines[i]->GetRect(&rcdr);
            rc.right = rcdr.Width();

            rcdr = rc;
            rcdr.Offset(-_horzScroll * _aveCharWid + lprc->left, -_vertScroll * _aveCharHei + lprc->top);

            if (!bSel)
            {
                _lines[i]->Draw(drawing, bActive, &rcdr, att);
            }
            else if (bline == i)
            {
                _lines[i]->DrawSel(drawing, bActive, &rcdr, bl, br, att);
            }
            else if (eline == i)
            {
                _lines[i]->DrawSel(drawing, bActive, &rcdr, el, er, att);
            }
            else if (i > bline && i < eline)
            {
                _lines[i]->DrawSel(drawing, bActive, &rcdr, 0, -1, att);
            }
            else
            {
                _lines[i]->Draw(drawing, bActive, &rcdr, att);
            }
        }

        rc.top = rc.bottom;
    }
}

void TextBoxDoc::Add(GlyphPtr gly)
{
    DeleteSelect();

    _lines[_caretLine]->Add(gly);
}

void TextBoxDoc::Add(const suic::String & text)
{
    Add(text.c_str(), (suic::Uint32)text.Length());
}

void TextBoxDoc::Add(const suic::Char * text, suic::Uint32 len)
{
    DeleteSelect();

    typedef struct tagLineSep
    {
        const suic::Char * beg;
        int len;
    }LineSep;

    suic::Vector<LineSep> seps;

    const suic::Char * beg = text;
    suic::Char * cur = const_cast<suic::Char *>(beg);
    suic::Char * end = cur + len;

    int nAllLine = 0;

    while (cur != end)
    {
        if (*cur == L'\n' || *cur == L'\r')
        {
            LineSep sp;
            sp.beg = beg;
            sp.len = (int)(cur - beg);
            seps.push_back(sp);
            beg = cur + 1;
            if (*beg == L'\n' || 
                *beg == L'\r')
            {
                ++beg;
                ++cur;
            }
            ++nAllLine;
        }
        else if (*cur == L'\t')
        {
            int iii = 0;
            *cur = L' ';
        }

        ++cur;
    }
    if ((*end) != L'\n')
    {
        LineSep sp;
        sp.beg = beg;
        sp.len = (int)(cur - beg);
        ++nAllLine;
        seps.push_back(sp);
    }

    HDC hdc = ::GetDC(NULL);
    HFONT hOld = (HFONT)SelectObject(hdc, DefFont);

    if (seps.size() > 0)
    {
        suic::String str(seps[0].beg, seps[0].len);

        _lines[_caretLine]->Insert(str, _caretOffset);
        _caretOffset += seps[0].len;
        _lines[_caretLine]->RefleshRect(HdcToHandle(hdc));
    }

    if (seps.size() > 1 && !IsSingleLine())
    {
        _lines.insert(_lines.begin() + (_caretLine + 1), seps.size() - 1, NULL);
        int nInsertPos = _caretLine;
        for (int i = 1; i < (int)seps.size(); ++i)
        {
            ++_caretLine;
            _lines[_caretLine] = new TextBoxLine();
            _lines[_caretLine]->Add(seps[i].beg, seps[i].len);
        }

        // 记下光标所在位置行的偏移
        _caretOffset = _lines[_caretLine]->GetCount();
    }

    SelectObject(hdc, hOld);
    ::ReleaseDC(NULL, hdc);

    RecalcCaret(false);
}

bool TextBoxDoc::NormalizeScroll()
{
    int nLine = _caretLine;
    int nOffset = _caretOffset;

    if (_trackLine >= 0)
    {
        nLine = _trackLine;
        nOffset = _trackOffset;
    }

    // 调整水平滚动条
    int nHorzOld = _lines[nLine]->Offset(nOffset);
    int nHorzOffset = nHorzOld - _horzScroll * _aveCharWid;

    int nPrevHorz = _horzScroll;

    if (0 == nOffset)
    {
        _horzScroll = 0;
    }
    else if (nHorzOffset < 0)
    {
        _horzScroll = (nHorzOld / _aveCharWid);
    }
    else if (nHorzOffset > _rcVisual.Width())
    {
        _horzScroll = ((nHorzOld - _rcVisual.Width()) / _aveCharWid);
        if (((nHorzOld - _rcVisual.Width()) % _aveCharWid) != 0)
        {
            ++_horzScroll;
        }
    }

    // 调整垂直滚动条
    int nVertOffset = 0;
    int nPrevVert = _vertScroll;

    for (int i = 0; i < nLine; ++i)
    {
        nVertOffset += _lines[i]->GetLineHei();
    }

    int nVertOld = nVertOffset;
    nVertOffset -= _vertScroll * _aveCharHei;

    if (0 == nLine)
    {
        _vertScroll = 0;
    }
    else if (nVertOffset < 0)
    {
        _vertScroll = (nVertOld / _aveCharHei);
    }
    else if (nVertOffset > _rcVisual.Height() || 
        (nVertOffset + _lines[nLine]->GetLineHei()) > _rcVisual.Height())
    {
        nVertOld += _lines[nLine]->GetLineHei();
        _vertScroll = ((nVertOld - _rcVisual.Height()) / _aveCharHei);
        if (((nVertOld - _rcVisual.Height()) % _aveCharHei) != 0)
        {
            ++_vertScroll;
        }
    }

    return (nPrevHorz != _horzScroll || nPrevVert != _vertScroll);
}

void TextBoxDoc::Add(suic::Char ch)
{
    DeleteSelect();

    _lines[_caretLine]->Insert(ch, _caretOffset);
    HDC hdc = ::GetDC(NULL);
    HFONT hOld = (HFONT)SelectObject(hdc, DefFont);

    _lines[_caretLine]->RefleshRect(HdcToHandle(hdc));
    ++_caretOffset;

    SelectObject(hdc, hOld);
    ::ReleaseDC(NULL, hdc);

    RecalcCaret(false);
}

void TextBoxDoc::GetSelectText(suic::String & text)
{
    int bline=-1, bl=0, br=0, eline=-1, el=0, er=0;
    bool bSel = CalcSelectPos(bline, bl, br, eline, el, er);

    if (bSel)
    {
        _lines[bline]->GetSelText(text, bl, br - bl);
        for (int i = bline + 1; i < eline; ++i)
        {
            text += L"\n";
            _lines[i]->GetText(text);
        }
        if (eline > bline)
        {
            text += L"\n";
            _lines[eline]->GetSelText(text, el, er - el);
        }
    }
}

void TextBoxDoc::GetText(suic::String & text)
{
    for (int i = 0; i < (int)_lines.size(); ++i)
    {
        suic::String strline;

        _lines[i]->GetText(strline);
        text += strline;

        if (_lines.size() > 1)
        {
            text += _T("\n");
        }
    }
}

bool TextBoxDoc::SetCaret(suic::Point * lppt)
{
    suic::Rect rc;
    suic::Point pt(lppt);
    pt.y += _vertScroll * _aveCharHei;
    pt.x += _horzScroll * _aveCharWid;

    bool bRet = false;//
    bool bSel = IsSelectMode();

    _trackLine = -1;
    _trackOffset = -1;

    for (int i = 0; i < (int)_lines.size(); ++i)
    {
        rc.bottom = rc.top + _lines[i]->GetLineHei();
        // 找到点所在的行
        if ((pt.y <= rc.bottom && pt.y >= rc.top) || 
            i == (int)_lines.size() - 1)
        {
            // 记下当前光标所在行
            _caretLine = i;
            // 光标所在行偏移，序号从1开始，如果光标在行末尾
            // 返回当前行的元素个数，如果光标在行首，返回0
            _caretOffset = _lines[i]->PointIn(&pt);

            // 计算光标位置
            bRet = RecalcCaret(false);

            break;
        }
        rc.top = rc.bottom;
    }
    if (bSel)
    {
        return true;
    }
    return bRet;
}

bool TextBoxDoc::SelectWord(suic::Point * lppt)
{
    int beg = 0, end = 0;
    SetCaret(lppt);

    if (_lines[_caretLine]->GetCount() == 0)
    {
        return false;
    }

    beg = _caretOffset;
    _lines[_caretLine]->SelectWord(beg, end);
    _trackLine = _caretLine;
    _caretOffset = beg;
    _trackOffset = end;

    RecalcCaret(false);

    return true;
}

void TextBoxDoc::TrackCaret(suic::Point * lppt)
{
    suic::Rect rc;
    suic::Point pt(lppt);
    pt.y += _vertScroll * _aveCharHei;
    pt.x += _horzScroll * _aveCharWid;

    int i = 0;

    // 处理选中时光标位置
    for (i = 0; i < (int)_lines.size(); ++i)
    {
        rc.bottom = rc.top + _lines[i]->GetLineHei();
        if (pt.y <= rc.bottom && pt.y >= rc.top)
        {
            break;
        }
        else if (i < (int)_lines.size() - 1)
        {
            rc.top = rc.bottom;
        }
    }

    if (i == (int)_lines.size())
    {
        if (lppt->y < 0)
        {
            i = 0;
            rc.top = 0;
        }
        else
        {
            i = (int)_lines.size() - 1;
        }
    }

    // 记下选中的位置
    _trackLine = i;
    _trackOffset = _lines[i]->PointIn(&pt);

    // 计算光标位置
    RecalcCaret(false);
}

suic::Rect TextBoxDoc::GetCaret(bool bUpDown)
{
    int nLine = _caretLine;
    int nOffset = _caretOffset;

    if (IsSelectMode())
    {
        nLine = _trackLine;
        nOffset = _trackOffset;
    }

    int nxOffset = _lines[nLine]->Offset(nOffset);
    int nyOffset = 0;

    for (int i = 0; i < nLine; ++i)
    {
        nyOffset += _lines[i]->GetLineHei();
    }

    _caretPos.left = nxOffset - _horzScroll * _aveCharWid;
    _caretPos.top = nyOffset - _vertScroll * _aveCharHei;
    _caretPos.bottom = _caretPos.top + _lines[nLine]->GetLineHei();

    if (!bUpDown)
    {
        _caretPrePos = _caretPos;
    }

    return _caretPos;
}

bool TextBoxDoc::OnLineHome(bool bSel)
{
    if (_lines[_caretLine]->GetCount() == 0)
    {
        return false;
    }

    if (bSel)
    {
        if (_trackLine < 0)
        {
            _trackLine = _caretLine;
        }
        _trackOffset = 0;
    }
    else
    {
        _caretOffset = 0;
    }
    if (RecalcCaret(false) || bSel)
    {
        return true;
    }
    return false;
}

bool TextBoxDoc::OnLineEnd(bool bSel)
{
    if (_lines[_caretLine]->GetCount() == 0)
    {
        return false;
    }

    if (bSel)
    {
        if (_trackLine < 0)
        {
            _trackLine = _caretLine;
        }
        _trackOffset = _lines[_trackLine]->GetCount();
    }
    else
    {
        _caretOffset = _lines[_caretLine]->GetCount();
    }
    if (RecalcCaret(false) || bSel)
    {
        return true;
    }
    return false;
}

bool TextBoxDoc::OnPageNext(bool bSel)
{
    return RecalcCaret(false);
}

bool TextBoxDoc::OnPagePrior(bool bSel)
{
    return RecalcCaret(false);
}

bool TextBoxDoc::OnVisualHome(bool bSel)
{
    return bSel;
}

bool TextBoxDoc::OnVisualEnd(bool bSel)
{
    return bSel;
}

bool TextBoxDoc::OnDocHome(bool bSel)
{
    if (_lines[_caretLine]->GetCount() == 0 && 
        _lines.size() < 2)
    {
        return false;
    }

    if (bSel)
    {
        _trackOffset = 0;
        _trackLine = 0;
    }
    else
    {
        _caretOffset = 0;
        _caretLine = 0;
    }
    if (RecalcCaret(false) || bSel)
    {
        return true;
    }
    return false;
}

bool TextBoxDoc::OnDocEnd(bool bSel)
{
    if (_lines[_caretLine]->GetCount() == 0 && 
        _lines.size() < 2)
    {
        return false;
    }

    if (bSel)
    {
        _trackLine = (int)_lines.size() - 1;
        _trackOffset = _lines[_trackLine]->GetCount();
    }
    else
    {
        _caretLine = (int)_lines.size() - 1;
        _caretOffset = _lines[_caretLine]->GetCount();
    }
    if (RecalcCaret(false) || bSel)
    {
        return true;
    }
    return false;
}

void TextBoxDoc::SetSelInfo(bool bSel, int * & nOffset, int * & nLine)
{
    if (bSel)
    {
        if (_trackLine < 0)
        {
            _trackLine = _caretLine;
            _trackOffset = _caretOffset;
        }
        nLine = &_trackLine;
        nOffset = &_trackOffset;
    }
    else
    {
        CancelSelect();
        nOffset = &_caretOffset;
        nLine = &_caretLine;
    }
}

bool TextBoxDoc::HasContent() const
{
    if (_lines.size() > 0 && _lines[0]->GetCount() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool TextBoxDoc::OnLeftCaret(bool bSel)
{
    int * nOffset = NULL, * nLine = NULL;
    SetSelInfo(bSel, nOffset, nLine);

    if ((*nOffset) <= 0)
    {
        if (*nLine > 0)
        {
            --(*nLine);
            *nOffset = _lines[*nLine]->GetCount();
        }
    }
    else
    {
        --*nOffset;
    }

    if (RecalcCaret(false) || bSel)
    {
        return true;
    }

    return false;
}

bool TextBoxDoc::OnUpCaret(bool bSel)
{
    int * nOffset = NULL, * nLine = NULL;
    SetSelInfo(bSel, nOffset, nLine);

    if (*nLine > 0)
    {
        --(*nLine);
        suic::Point pt(_caretPrePos.left, _caretPrePos.top + 2);
        *nOffset = _lines[*nLine]->PointIn(&pt);

        if (*nOffset > (int)_lines[*nLine]->GetCount())
        {
            *nOffset = _lines[*nLine]->GetCount();
        }

        return RecalcCaret(true);
    }

    return bSel;
}

bool TextBoxDoc::OnRightCaret(bool bSel)
{
    int * nOffset = NULL, * nLine = NULL;
    SetSelInfo(bSel, nOffset, nLine);

    if (*nOffset >= (int)_lines[*nLine]->GetCount())
    {
        if (*nLine < (int)(_lines.size() - 1))
        {
            ++(*nLine);
            *nOffset = 0;
        }
        else
        {
            return false;
        }
    }
    else
    {
        ++(*nOffset);
    }

    if (RecalcCaret(false) || bSel)
    {
        return true;
    }
    return false;
}

bool TextBoxDoc::OnDownCaret(bool bSel)
{
    int * nOffset = NULL, * nLine = NULL;
    SetSelInfo(bSel, nOffset, nLine);

    if (*nLine < (int)_lines.size() - 1)
    {
        ++(*nLine);

        suic::Point pt(_caretPrePos.left, _caretPrePos.top + 2);
        *nOffset = _lines[*nLine]->PointIn(&pt);

        if (*nOffset > (int)_lines[*nLine]->GetCount())
        {
            *nOffset = _lines[*nLine]->GetCount();
        }
        return RecalcCaret(true);
    }

    return false;
}

void TextBoxDoc::CancelSelect()
{
    int bline=-1, bl=0, br=0, eline=-1, el=0, er=0;
    bool bSel = CalcSelectPos(bline, bl, br, eline, el, er);

    if (bSel)
    {
        _caretLine = _trackLine;
        _caretOffset = _trackOffset;
    }

    _trackLine = -1;
    _trackOffset = -1;
}

void TextBoxDoc::CalcTextRect(suic::Rect * lprc, int nLine)
{
}

bool TextBoxDoc::RecalcCaret(bool bUpDown)
{
    bool bRet = NormalizeScroll();

    return bRet;
}

bool TextBoxDoc::CalcSelectPos(int & bline, int & bl, int & br, int & eline, int & el, int & er)
{
    // 如果有选中部分
    if (_trackLine != -1 && -1 != _trackOffset)
    {
        // 选中一行中的一部分
        if (_trackLine == _caretLine)
        {
            bline = _trackLine;
            eline = _trackLine;
            if (_trackOffset > _caretOffset)
            {
                bl = _caretOffset;
                br = _trackOffset;
            }
            else
            {
                bl = _trackOffset;
                br = _caretOffset;
            }
        }
        else if (_trackLine > _caretLine)
        {
            bline = _caretLine;
            bl = _caretOffset;
            br = _lines[_caretLine]->GetCount();

            eline = _trackLine;
            el = 0;
            er = _trackOffset;
        }
        else
        {
            bline = _trackLine;
            bl = _trackOffset;
            br = _lines[_trackLine]->GetCount();

            eline = _caretLine;
            el = 0;
            er = _caretOffset;
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool TextBoxDoc::DeleteSelect()
{
    int bline=0, bl=0, br=0, eline=0, el=0, er=0;
    if (CalcSelectPos(bline, bl, br, eline, el, er))
    {
        if (bline == eline)
        {
            _lines[bline]->Remove(bl, br);
        }
        else
        {
            if (_lines[bline]->GetCount() > 0)
            {
                _lines[bline]->Remove(bl, br-0);
            }
            if (_lines[eline]->GetCount() == 0 || 
                (er - el == _lines[eline]->GetCount()))
            {
                _lines.erase(_lines.begin() + eline);
            }
            else
            {
                _lines[bline]->AddLine(_lines[eline], er, _lines[eline]->GetCount());
                _lines.erase(_lines.begin() + eline);
            }
            if (eline - bline > 1)
            {
                _lines.erase(_lines.begin() + (bline + 1), _lines.begin() + (eline - 0));
            }
        }

        CancelSelect();
        _caretLine = bline;
        _caretOffset = bl;

        RecalcCaret(false);

        return true;
    }
    return false;
}

void TextBoxDoc::ReplaceSelect(const suic::String & text)
{
    // 先删除选中
    DeleteSelect();

    Add(text);
}

void TextBoxDoc::ReplaceSelect(const GlyphPtr gly)
{
    // 先删除选中
    DeleteSelect();
    // 将此元素插入光标处
    Add(gly);
}

// 在光标处插入一行
void TextBoxDoc::InsertLine()
{
    DeleteSelect();

    EditLinePtr newLine(new TextBoxLine());

    if (_caretLine == -1)
    {
        _lines.push_back(newLine);
    }
    else
    {
        if (_caretOffset <= 0)
        {
            _lines.insert(_lines.begin() + _caretLine, newLine);
        }
        else
        {
            _lines.insert(_lines.begin() + _caretLine + 1, newLine);
        }
    }

    _caretLine += 1;

    // 如果光标在一行的中间，需要把这行分为两行
    if (_caretLine > 0 && _caretOffset > 0 && 
        _caretOffset < (int)_lines[_caretLine-1]->GetCount())
    {
        newLine->AddLine(_lines[_caretLine-1], _caretOffset, -1);
        _lines[_caretLine-1]->Remove(_caretOffset, -1);
    }

    _caretOffset = 0;

    RecalcCaret(false);
}

// 向左删除一个元素
void TextBoxDoc::DelLeftOne()
{
    if (DeleteSelect())
    {
        return;
    }

    // 删除一行
    if (_caretOffset <= 0)
    {
        if (_caretLine > 0)
        {
            _caretOffset = _lines[_caretLine - 1]->GetCount();

            // 把下一行合并到上一行
            _lines[_caretLine - 1]->AddLine(_lines[_caretLine]);
            _lines.erase(_lines.begin() + _caretLine);
            _caretLine -= 1;
        }
    }
    else
    {
        _lines[_caretLine]->Remove(_caretOffset-1, _caretOffset);
        --_caretOffset;
    }

    RecalcCaret(false);
}

// 向右删除一个元素
void TextBoxDoc::DelRightOne()
{
    if (DeleteSelect())
    {
        return;
    }

    // 删除一行
    if (_caretOffset == _lines[_caretLine]->GetCount())
    {
        if (_caretLine < (int)_lines.size() - 1)
        {
            // 把光标处下一行的数据合并到光标所在行
            _lines[_caretLine]->AddLine(_lines[_caretLine + 1].get());
            _lines.erase(_lines.begin() + _caretLine + 1);
        }
    }
    else
    {
        // 空行，删除
        if (_lines[_caretLine]->GetCount() == 0)
        {
            _lines.erase(_lines.begin() + _caretLine);
        }
        else
        {
            // 向右删除一个字符
            _lines[_caretLine]->Remove(_caretOffset, _caretOffset + 1);
        }
    }

    RecalcCaret(false);
}

bool TextBoxDoc::IsSelectMode()
{
    bool bRet = true;

    if (_trackLine < 0 || _trackOffset < 0)
    {
        bRet = false;
    }
    else if (_trackLine == _caretLine && _trackOffset == _caretOffset)
    {
        bRet = false;
        _trackLine = -1;
        _trackOffset = -1;
    }

    return bRet;
}

}

