// 华勤科技版权所有 2010-2011
// 
// 文件名：uilibids.h
// 功  能：定义资源用到的标识
// 
// 作  者：汪荣
// 时  间：2010-07-08
// 
// ============================================================================

# ifndef _UILIBIDS_H_
# define _UILIBIDS_H_

namespace suic
{

static String ISLAYEREDWINDOW = _T("IsLayeredWindow");

// 全局唯一资源ID
static String USID = _T("usid");
static String RESOURCES = _T("Resources");

static String WINDOW = _T("Window");

static String PANEL = _T("Panel");
static String LAYOUT = _T("Layout");
static String STACKPANEL = _T("StackPanel");
static String FLOWPANEL = _T("FlowPanel");

static String GRID = _T("Grid");
static String GRIDROW = _T("Grid.Row");
static String GRIDCOLUMN = _T("Grid.Column");

static String BUTTON = _T("Button");
static String CHECKBUTTON = _T("CheckButton");
static String RADIOBUTTON = _T("RadioButton");

static String SCROLLBAR = _T("ScrollBar");
static String TOOLBAR = _T("ToolBar");
static String MENUBAR = _T("MenuBar");

static String TEXTBOX = _T("TextBox");
static String RICHTEXTBOX = _T("RichTextBox");

static String LISTCTRL = _T("ListCtrl");
static String LISTBOX = _T("ListBox");
static String COMBOBOXLISTBOX = _T("ComboBox.ListBox");
static String TREECTRL = _T("TreeCtrl");

static String COMBOBOX = _T("ComboBox");

///////////////////////////////////////////////////////////////////////////////
// 属性定义

// 最先启动的界面窗口
static String STARTUPRRI = _T("StartupUri");

static String CLIPTOBOUNDS = _T("ClipToBounds");
static String TOPMOST = _T("TopMost");

static String WIDTH = _T("Width");
static String HEIGHT = _T("Height");

static String STRETCH = _T("Stretch");
static String CONTENT = _T("Content");

static String BACKGROUND = _T("Background");
static String FOREGROUND = _T("Foreground");

static String FONTFAMILY = _T("Family");
static String FONTSIZE = _T("Size");
static String FONTSTYLE = _T("FontStyle");
static String FONTWEIGHT = _T("Weight");
static String FONTSTRETCH = _T("Stretch");

// 圆角水平方向的长度
static String RADIUSX = _T("RadiusX");
// 圆角垂直方向的长度
static String RADIUSY = _T("RadiusY");

static String OPACITY = _T("Opacity");
static String OPACITYMASK = _T("OpacityMask");

static String TEXT = _T("Text");
static String NAME = _T("Name");
static String ISENABLED = _T("IsEnabled");
static String TOOLTIP = _T("ToolTip");
static String VISIBILITY = _T("Visibility");
static String ORIENTATION = _T("Orientation");

static String VERTICALALIGNMENT = _T("VerticalAlignment");
static String HORIZONTALALIGNMENT = _T("HorizontalAlignment");

static String VERTICALCONTENTALIGNMENT = _T("VerticalContentAlignment");
static String HORIZONTALCONTENTALIGNMENT = _T("HorizontalContentAlignment");

// 元素内容的显示方向
static String FLOWDIRECTION = _T("FlowDirection");
static String ZINDEX = _T("ZIndex");
static String LOCATION = _T("Location");

// 本界面元素和其它界面元素之间的外边距
static String MARGIN = _T("Margin");
// 本界面元素的内容和其边缘的距离
static String PADDING = _T("Padding");

static String MINWIDTH = _T("MinWidth");
static String MAXWIDTH = _T("MaxWidth");

static String MINHEIGHT = _T("MinHeight");
static String MAXHEIGHT = _T("MaxHeight");

// 边框画刷，可以是颜色、渐变画刷、图像和空画刷
static String BORDERBRUSH = _T("BorderBrush");

// 边框大小,Rect类型,left、top、right、bottom分别代表
// 四个边框的高和宽
static String BORDERTHICKNESS = _T("BorderThickness");

static String IMAGEBRUSH = _T("ImageBrush");
static String IMAGESOURCE = _T("Source");
static String VIEWBOX = _T("ViewBox");
static String VIEWBOXUNITS = _T("ViewboxUnits");
static String VIEWPORT = _T("Viewport");
static String VIEWPORTUNITS = _T("ViewportUnits");
static String ALIGNMENTX = _T("AlignmentX");
static String ALIGNMENTY = _T("AlignmentY");
static String TILEMODE = _T("TileMode");
static String IMAGECORNER = _T("ViewCorner");
static String DRAWEDGE = _T("DrawEdge");

// 渐变画刷
static String LINEARGRADIENTBRUSH = _T("LinearGradientBrush");
static String STARTPOINT = _T("StartPoint");
static String ENDPOINT = _T("EndPoint");
static String GRADIENTSTOP = _T("GradientStop");
static String COLOR = _T("Color");
static String OFFSET = _T("Offset");

///////////////////////////////////////////////////////////////////////////////
// 属性值定义
//
static String VERTICAL = _T("Vertical");
static String HORIZONTAL = _T("Horizontal");

static String True = _T("True");
static String False = _T("False");
static String LEFT = _T("Left");
static String RIGHT = _T("Right");
static String TOP = _T("Top");
static String BOTTOM = _T("Bottom");
static String CENTER = _T("Center");
static String JUSTIFY = _T("Justify");

static String NONE = _T("None");
static String Null = _T("Null");
static String XNULL = _T("x:Null");

static String VISIBLE = _T("Visible");
static String HIDDEN = _T("Hidden");
static String COLLAPSED = _T("Collapsed");

static String RELATIVETOBOUNDINGBOX = _T("RelativeToBoundingBox");
static String Absolute = _T("Absolute");
static String FLIPX = _T("FlipX");
static String FLIPY = _T("FlipY");
static String FLIPXY = _T("FlipXY");
static String TILE = _T("Tile");

static String FILL = _T("Fill");
static String UNIFORM = _T("Uniform");
static String UNIFORMTOFILL = _T("UniformToFill");

static String RIGHTTOLEFT = _T("RightToLeft");
static String LEFTTORIGHT = _T("LeftToRight");

///////////////////////////////////////////////////////////////////////////////
// 状态定义

static String STATICRESOURCE = _T("StaticResource");
static String DYNAMICRESOURCE = _T("DynamicResource"); 

static String WRAPPERTYPE = _T("Wrapper");
static String BASEDON = _T("BasedOn");
static String XKEY = _T("x:Key");
static String XTYPE = _T("x:Type");
static String PROPERTY = _T("Property");
static String VALUE = _T("Value");
static String XPREFIX = _T("x:");
static String VPREFIX = _T("v:");
static String SETTER_VALUE = _T("Setter.Value");
static String SETTER = _T("Setter");
static String TRIGGERS = _T("Triggers");
static String TRIGGER = _T("Trigger");
static String STYLE = _T("UIStyle");
static String TARGETTYPE = _T("TargetType");

static String STATE = _T("");
static String NORMAL = _T("Normal");
static Uint32 U_NORMAL = 0;

static String DEFAULT = _T("Default");
static Uint32 U_DEFAULT = 0;

static String MOUSEOVER = _T("IsMouseOver");
static Uint32 U_MOUSEOVER = 1;

static String PRESSED = _T("IsPressed");
static Uint32 U_PRESSED = 2;

static String DISABLED = _T("IsDisabled");
static Uint32 U_DISABLED = 3;

static String FOCUSED = _T("IsFocused");
static Uint32 U_FOCUSED = 4;

static String SELECTED = _T("IsSelected");
static Uint32 U_SELECTED = 5;

static String CURSOR = _T("Cursor");

};

# endif
