/* 

Copyright (c) 2002 O'ksi'D
Copyright 1985, 1986, 1987, 1991, 1998  The Open Group

All Rights Reserved.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/

#ifndef XLIB_H
#define XLIB_H

#include <sys/time.h>
#include <stdlib.h>

#define Bool char
#define Status int
#define True 1
#define False 0
#define None 0

#define RootWindow(dpy, scr) (0)
#define DefaultScreen(dpy) (0)
#define ConnectionNumber(dpy) (*dpy)
#define DefaultVisual(dpy, scr) (0)
#define DisplayHeight(dpy, scr) (480)
#define DisplayWidth(dpy, scr) (640)
#define DefaultColormap(dpy, scr) (0)
#define XVisualIDFromVisual(vis) (0)
#define XGetVisualInfo(dpy, mask, temp, num) (0)
#define XRefreshKeyboardMapping(e)
#define ImageByteOrder(dpy) 0

typedef long Time;
typedef struct _XRegion *Region;
typedef int Display;
typedef int XComposeStatus;
typedef int Window; 
typedef int Drawable; 
typedef char Colormap;
typedef char Visual;
typedef void * XIM;
typedef void * XIC;
typedef long Atom;
typedef unsigned long XIMStyle; 
typedef long KeySym;
typedef long KeyCode;
typedef int Screen;
typedef int Cursor;
typedef int Pixmap;
typedef int VisualID;
typedef unsigned int Font;
typedef void * XPointer;
typedef struct {
    Atom name;
    unsigned long card32;
} XFontProp;

typedef struct _XGC {
	int function;		/* logical operation */
	unsigned long plane_mask;/* plane mask */
	unsigned long foreground;/* foreground pixel */
	unsigned long background;/* background pixel */
	int line_width;		/* line width */
	int line_style;	 	/* LineSolid, LineOnOffDash, LineDoubleDash */
	int cap_style;	  	/* CapNotLast, CapButt, 
				   CapRound, CapProjecting */
	int join_style;	 	/* JoinMiter, JoinRound, JoinBevel */
	int fill_style;	 	/* FillSolid, FillTiled, 
				   FillStippled, FillOpaeueStippled */
	int fill_rule;	  	/* EvenOddRule, WindingRule */
	int arc_mode;		/* ArcChord, ArcPieSlice */
	Pixmap tile;		/* tile pixmap for tiling operations */
	Pixmap stipple;		/* stipple 1 plane pixmap for stipping */
	int ts_x_origin;	/* offset for tile or stipple operations */
	int ts_y_origin;
        Font font;	        /* default text font for text operations */
	int subwindow_mode;     /* ClipByChildren, IncludeInferiors */
	Bool graphics_exposures;/* boolean, should exposures be generated */
	int clip_x_origin;	/* origin for clipping */
	int clip_y_origin;
	Pixmap clip_mask;	/* bitmap clipping; other calls for rects */
	int dash_offset;	/* patterned/dashed line information */
	char dashes;
} *GC, XGCValues;

typedef struct {
    short	lbearing;	/* origin to left edge of raster */
    short	rbearing;	/* origin to right edge of raster */
    short	width;		/* advance to next char's origin */
    short	ascent;		/* baseline to top edge of raster */
    short	descent;	/* baseline to bottom edge of raster */
    unsigned short attributes;	/* per char flags (not predefined) */
} XCharStruct;

typedef struct {
    void	*ext_data;	/* hook for extension to hang data */
    Font        fid;            /* Font id for this font */
    unsigned	direction;	/* hint about direction the font is painted */
    unsigned	min_char_or_byte2;/* first character */
    unsigned	max_char_or_byte2;/* last character */
    unsigned	min_byte1;	/* first row that exists */
    unsigned	max_byte1;	/* last row that exists */
    Bool	all_chars_exist;/* flag if all characters have non-zero size*/
    unsigned	default_char;	/* char to print for undefined character */
    int         n_properties;   /* how many properties there are */
    XFontProp	*properties;	/* pointer to array of additional properties*/
    XCharStruct	min_bounds;	/* minimum bounds over all existing char*/
    XCharStruct	max_bounds;	/* maximum bounds over all existing char*/
    XCharStruct	*per_char;	/* first_char to last_char information */
    int		ascent;		/* log. extent above baseline for spacing */
    int		descent;	/* log. descent below baseline for spacing */
} XFontStruct;

typedef struct {
	int nb_font;
	char **font_name_list;
	int *encodings;
	XFontStruct **fonts;
	Font fid;
	int ascent;
	int descent;
	int *ranges;
} XUtf8FontStruct;

typedef struct {
	unsigned short count_styles;
	XIMStyle *supported_styles;
} XIMStyles;

typedef struct {
	short x, y;
	unsigned short width, height;
} XRectangle;

typedef struct {
    short x, y;
} XPoint;

typedef struct fd_set {
	long fds_bits[4];
} fd_set;

typedef struct {
	unsigned long pixel;
	unsigned short red, green, blue;
	char flags;  /* do_red, do_green, do_blue */
	char pad;
} XColor;

typedef struct {
  Visual *visual;
  VisualID visualid;
  int screen;
  int depth;
#if defined(__cplusplus) || defined(c_plusplus)
  int c_class;					/* C++ */
#else
  int class;
#endif
  unsigned long red_mask;
  unsigned long green_mask;
  unsigned long blue_mask;
  int colormap_size;
  int bits_per_rgb;
} XVisualInfo;

#define FD_SET(n, p) ((p)->fds_bits[(n)/32] |= ((long)1 << ((n) % 32)))
#define FD_CLR(n, p) ((p)->fds_bits[(n)/32] &= ((long)1 << ((n) % 32)))
#define FD_ISSET(n, p) ((p)->fds_bits[(n)/32] & ((long)1 << ((n) % 32)))

typedef int XID;
typedef struct {
    int x, y;			/* location of window */
    int width, height;		/* width and height of window */
    int border_width;		/* border width of window */
    int depth;          	/* depth of window */
    Visual *visual;		/* the associated visual structure */
    Window root;        	/* root of screen containing window */
#if defined(__cplusplus) || defined(c_plusplus)
    int c_class;		/* C++ InputOutput, InputOnly*/
#else
    int class;			/* InputOutput, InputOnly*/
#endif
    int bit_gravity;		/* one of bit gravity values */
    int win_gravity;		/* one of the window gravity values */
    int backing_store;		/* NotUseful, WhenMapped, Always */
    unsigned long backing_planes;/* planes to be preserved if possible */
    unsigned long backing_pixel;/* value to be used when restoring planes */
    Bool save_under;		/* boolean, should bits under be saved? */
    char colormap;		/* color map to be associated with window */
    Bool map_installed;		/* boolean, is color map currently installed*/
    int map_state;		/* IsUnmapped, IsUnviewable, IsViewable */
    long all_event_masks;	/* set of events all people have interest in*/
    long your_event_mask;	/* my event mask */
    long do_not_propagate_mask; /* set of events that should not propagate */
    Bool override_redirect;	/* boolean value for override-redirect */
    Screen *screen;		/* back pointer to correct screen */
} XWindowAttributes;

typedef struct {
	int type;
	unsigned long serial;
	char send_event;
	Display *display;
	Window window;
} XAnyEvent;

typedef struct {
	int type;
	Display *display;
	XID resourceid;
	unsigned long serial;
	unsigned char error_code;
	unsigned char request_code;
	unsigned char minor_code;
} XErrorEvent;

typedef struct {
	int type;
	unsigned long serial;
	char send_event;
	Display *display;
	Window window;
	Window root;
	Window subwindow;
	Time time;
	int x, y;
	int x_root, y_root;
	unsigned int state;
	unsigned int button;
	char same_screen;
} XButtonEvent;
typedef XButtonEvent XButtonPressedEvent;
typedef XButtonEvent XButtonReleasedEvent;

typedef struct {
	int type;
	unsigned long serial;
	char send_event;
	Display *display;
	Window window;
	char key_vector[32];
} XKeymapEvent;

typedef struct {
	int type;
	unsigned long serial;
	char send_event;
	Display *display;
	Window requestor;
	Atom selection;
	Atom target;
	Atom property;
	Time time;
} XSelectionEvent;

typedef struct {
	int type;
	unsigned long serial;
	char send_event;
	Display *display;
	Window window;
	Atom message_type;
	int format;
	union {
		char b[20];
		short s[10];
		long l[5];
	} data;
} XClientMessageEvent;

typedef struct {
	int type;
	unsigned long serial;
	char send_event;
	Display *display;
	Window owner;
	Window requestor;
	Atom selection;
	Atom target;
	Atom property;
	Time time;
} XSelectionRequestEvent;


typedef struct {
	int type;
	unsigned long serial;
	char send_event;
	Display *display;
	Window window;
	Atom selection;
	Time time;
} XSelectionClearEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window parent;
	Window window;
} XMapRequestEvent;

typedef struct {
	int type;
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;
	int x, y;
	int width, height;
	int count;		/* if non-zero, at least this many more */
} XExposeEvent;
typedef struct {
	int type;		/* of event */
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;	        /* "event" window reported relative to */
	Window root;	        /* root window that the event occurred on */
	Window subwindow;	/* child window */
	Time time;		/* milliseconds */
	int x, y;		/* pointer x, y coordinates in event window */
	int x_root, y_root;	/* coordinates relative to root */
	int mode;		/* NotifyNormal, NotifyGrab, NotifyUngrab */
	int detail;
	/*
	 * NotifyAncestor, NotifyVirtual, NotifyInferior, 
	 * NotifyNonlinear,NotifyNonlinearVirtual
	 */
	Bool same_screen;	/* same screen flag */
	Bool focus;		/* boolean focus */
	unsigned int state;	/* key or button mask */
} XCrossingEvent;
typedef XCrossingEvent XEnterWindowEvent;
typedef XCrossingEvent XLeaveWindowEvent;

typedef struct {
	int type;		/* of event */
	unsigned long serial;	/* # of last request processed by server */
	Bool send_event;	/* true if this came from a SendEvent request */
	Display *display;	/* Display the event was read from */
	Window window;	        /* "event" window it is reported relative to */
	Window root;	        /* root window that the event occurred on */
	Window subwindow;	/* child window */
	Time time;		/* milliseconds */
	int x, y;		/* pointer x, y coordinates in event window */
	int x_root, y_root;	/* coordinates relative to root */
	unsigned int state;	/* key or button mask */
	unsigned int keycode;	/* detail */
	Bool same_screen;	/* same screen flag */
} XKeyEvent;
typedef XKeyEvent XKeyPressedEvent;
typedef XKeyEvent XKeyReleasedEvent;

typedef union _XEvent {
	int type;
	XAnyEvent xany;
	XButtonEvent xbutton;
	XClientMessageEvent xclient;
	XKeymapEvent xkeymap;
	XSelectionEvent xselection;
	XSelectionClearEvent xselectionclear;
	XSelectionRequestEvent xselectionrequest;
	XMapRequestEvent xmaprequest;
	XExposeEvent xexpose;
	XKeyEvent xkey;
	XCrossingEvent xcrossing;
	
	long pad[24];
} XEvent;

typedef struct {
    Pixmap background_pixmap;	/* background or None or ParentRelative */
    unsigned long background_pixel;	/* background pixel */
    Pixmap border_pixmap;	/* border of the window */
    unsigned long border_pixel;	/* border pixel value */
    int bit_gravity;		/* one of bit gravity values */
    int win_gravity;		/* one of the window gravity values */
    int backing_store;		/* NotUseful, WhenMapped, Always */
    unsigned long backing_planes;/* planes to be preseved if possible */
    unsigned long backing_pixel;/* value to use in restoring planes */
    Bool save_under;		/* should bits under be saved? (popups) */
    long event_mask;		/* set of events that should be saved */
    long do_not_propagate_mask;	/* set of events that should not propagate */
    Bool override_redirect;	/* boolean value for override-redirect */
    Colormap colormap;		/* color map to be associated with window */
    Cursor cursor;		/* cursor to be displayed (or None) */
} XSetWindowAttributes;

typedef struct {
	long flags;	/* marks which fields in this structure are defined */
	Bool input;	/* does this application rely on the window manager to
			get keyboard input? */
	int initial_state;	/* see below */
	Pixmap icon_pixmap;	/* pixmap to be used as icon */
	Window icon_window; 	/* window to be used as icon */
	int icon_x, icon_y; 	/* initial position of icon */
	Pixmap icon_mask;	/* icon mask bitmap */
	XID window_group;	/* id of related window group */
	/* this structure may be extended in the future */
} XWMHints;
typedef struct {
    	long flags;	/* marks which fields in this structure are defined */
	int x, y;		/* obsolete for new window mgrs, but clients */
	int width, height;	/* should set so old wm's don't mess up */
	int min_width, min_height;
	int max_width, max_height;
    	int width_inc, height_inc;
	struct {
		int x;	/* numerator */
		int y;	/* denominator */
	} min_aspect, max_aspect;
	int base_width, base_height;		/* added by ICCCM version 1 */
	int win_gravity;			/* added by ICCCM version 1 */
} XSizeHints;
/*
 * Data structure for "image" data, used by image manipulation routines.
 */
typedef struct _XImage {
    int width, height;		/* size of image */
    int xoffset;		/* number of pixels offset in X direction */
    int format;			/* XYBitmap, XYPixmap, ZPixmap */
    char *data;			/* pointer to image data */
    int byte_order;		/* data byte order, LSBFirst, MSBFirst */
    int bitmap_unit;		/* quant. of scanline 8, 16, 32 */
    int bitmap_bit_order;	/* LSBFirst, MSBFirst */
    int bitmap_pad;		/* 8, 16, 32 either XY or ZPixmap */
    int depth;			/* depth of image */
    int bytes_per_line;		/* accelarator to next line */
    int bits_per_pixel;		/* bits per pixel (ZPixmap) */
    unsigned long red_mask;	/* bits in z arrangment */
    unsigned long green_mask;
    unsigned long blue_mask;
    XPointer obdata;		/* hook for the object routines to hang on */
    struct funcs {		/* image manipulation routines */
	struct _XImage *(*create_image)(
		struct _XDisplay* /* display */,
		Visual*		/* visual */,
		unsigned int	/* depth */,
		int		/* format */,
		int		/* offset */,
		char*		/* data */,
		unsigned int	/* width */,
		unsigned int	/* height */,
		int		/* bitmap_pad */,
		int		/* bytes_per_line */);
	int (*destroy_image)        (struct _XImage *);
	unsigned long (*get_pixel)  (struct _XImage *, int, int);
	int (*put_pixel)            (struct _XImage *, int, int, unsigned long);
	struct _XImage *(*sub_image)(struct _XImage *, int, int, unsigned int, unsigned int);
	int (*add_pixel)            (struct _XImage *, long);
	} f;
} XImage;

typedef struct {
    int depth;
    int bits_per_pixel;
    int scanline_pad;
} XPixmapFormatValues;
#define XYBitmap		0	/* depth 1, XYFormat */
#define XYPixmap		1	/* depth == drawable depth */
#define ZPixmap			2	/* depth == drawable depth */

#define QueuedAfterReading 1
#define XNQueryInputStyle "queryInputStyle"
#define XNInputStyle "InputStyle"
#define XNClientWindow "clientWindow"
#define XNFocusWindow "focusWindow"
#define XIMStatusNone 0x0800
#define XIMPreeditNone 0x0010
#define XIMStatusNothing 0x0400
#define XIMPreeditNothing 0x0008
#define XA_PRIMARY 1
#define XA_SECONDARY 2
#define XA_ATOM 3
#define XA_WM_CLASS 4
#define XA_STRING 5
#define XA_WM_NAME 6
#define XA_WM_ICON_NAME 7
#define XA_WM_COMMAND 8

#define NoEventMask			0L
#define KeyPressMask			(1L<<0)  
#define KeyReleaseMask			(1L<<1)  
#define ButtonPressMask			(1L<<2)  
#define ButtonReleaseMask		(1L<<3)  
#define EnterWindowMask			(1L<<4)  
#define LeaveWindowMask			(1L<<5)  
#define PointerMotionMask		(1L<<6)  
#define PointerMotionHintMask		(1L<<7)  
#define Button1MotionMask		(1L<<8)  
#define Button2MotionMask		(1L<<9)  
#define Button3MotionMask		(1L<<10) 
#define Button4MotionMask		(1L<<11) 
#define Button5MotionMask		(1L<<12) 
#define ButtonMotionMask		(1L<<13) 
#define KeymapStateMask			(1L<<14)
#define ExposureMask			(1L<<15) 
#define VisibilityChangeMask		(1L<<16) 
#define StructureNotifyMask		(1L<<17) 
#define ResizeRedirectMask		(1L<<18) 
#define SubstructureNotifyMask		(1L<<19) 
#define SubstructureRedirectMask	(1L<<20) 
#define FocusChangeMask			(1L<<21) 
#define PropertyChangeMask		(1L<<22) 
#define ColormapChangeMask		(1L<<23) 
#define OwnerGrabButtonMask		(1L<<24) 
#define KeyPress		2
#define KeyRelease		3
#define ButtonPress		4
#define ButtonRelease		5
#define MotionNotify		6
#define EnterNotify		7
#define LeaveNotify		8
#define FocusIn			9
#define FocusOut		10
#define KeymapNotify		11
#define Expose			12
#define GraphicsExpose		13
#define NoExpose		14
#define VisibilityNotify	15
#define CreateNotify		16
#define DestroyNotify		17
#define UnmapNotify		18
#define MapNotify		19
#define MapRequest		20
#define ReparentNotify		21
#define ConfigureNotify		22
#define ConfigureRequest	23
#define GravityNotify		24
#define ResizeRequest		25
#define CirculateNotify		26
#define CirculateRequest	27
#define PropertyNotify		28
#define SelectionClear		29
#define SelectionRequest	30
#define SelectionNotify		31
#define ColormapNotify		32
#define ClientMessage		33
#define MappingNotify		34
#define LASTEvent		35
#define ShiftMask		(1<<0)
#define LockMask		(1<<1)
#define ControlMask		(1<<2)
#define Mod1Mask		(1<<3)
#define Mod2Mask		(1<<4)
#define Mod3Mask		(1<<5)
#define Mod4Mask		(1<<6)
#define Mod5Mask		(1<<7)
#define Button1Mask		(1<<8)
#define Button2Mask		(1<<9)
#define Button3Mask		(1<<10)
#define Button4Mask		(1<<11)
#define Button5Mask		(1<<12)
#define Button1			1
#define Button2			2
#define Button3			3
#define Button4			4
#define Button5			5
#define CWBackPixmap		(1L<<0)
#define CWBackPixel		(1L<<1)
#define CWBorderPixmap		(1L<<2)
#define CWBorderPixel           (1L<<3)
#define CWBitGravity		(1L<<4)
#define CWWinGravity		(1L<<5)
#define CWBackingStore          (1L<<6)
#define CWBackingPlanes	        (1L<<7)
#define CWBackingPixel	        (1L<<8)
#define CWOverrideRedirect	(1L<<9)
#define CWSaveUnder		(1L<<10)
#define CWEventMask		(1L<<11)
#define CWDontPropagate	        (1L<<12)
#define CWColormap		(1L<<13)
#define CWCursor	        (1L<<14)
#define USPosition	(1L << 0) /* user specified x, y */
#define USSize		(1L << 1) /* user specified width, height */

#define PPosition	(1L << 2) /* program specified position */
#define PSize		(1L << 3) /* program specified size */
#define PMinSize	(1L << 4) /* program specified minimum size */
#define PMaxSize	(1L << 5) /* program specified maximum size */
#define PResizeInc	(1L << 6) /* program specified resize increments */
#define PAspect		(1L << 7) /* program specified min and max aspect ratios */
#define PBaseSize	(1L << 8) /* program specified base for incrementing */
#define PWinGravity	(1L << 9) /* program specified window gravity */
#define NotifyAncestor		0
#define NotifyVirtual		1
#define NotifyInferior		2
#define NotifyNonlinear		3
#define NotifyNonlinearVirtual	4
#define NotifyPointer		5
#define NotifyPointerRoot	6
#define NotifyDetailNone	7
#define InputOutput		1
#define InputOnly		2
#define InputHint 		(1L << 0)
#define StateHint 		(1L << 1)
#define IconPixmapHint		(1L << 2)
#define IconWindowHint		(1L << 3)
#define IconPositionHint 	(1L << 4)
#define IconMaskHint		(1L << 5)
#define WindowGroupHint		(1L << 6)
#define AllHints (InputHint|StateHint|IconPixmapHint|IconWindowHint| \
IconPositionHint|IconMaskHint|WindowGroupHint)
#define XUrgencyHint		(1L << 8)
#define WithdrawnState 0	/* for windows that are not mapped */
#define NormalState 1	/* most applications want to start this way */
#define IconicState 3	/* application wants to start as an icon */

#define ForgetGravity		0
#define NorthWestGravity	1
#define NorthGravity		2
#define NorthEastGravity	3
#define WestGravity		4
#define CenterGravity		5
#define EastGravity		6
#define SouthWestGravity	7
#define SouthGravity		8
#define SouthEastGravity	9
#define StaticGravity		10
/* LineStyle */

#define LineSolid		0
#define LineOnOffDash		1
#define LineDoubleDash		2

/* capStyle */

#define CapNotLast		0
#define CapButt			1
#define CapRound		2
#define CapProjecting		3

/* joinStyle */

#define JoinMiter		0
#define JoinRound		1
#define JoinBevel		2

/* fillStyle */

#define FillSolid		0
#define FillTiled		1
#define FillStippled		2
#define FillOpaqueStippled	3

/* fillRule */

#define EvenOddRule		0
#define WindingRule		1
#define Complex			0	/* paths may intersect */
#define Nonconvex		1	/* no paths intersect, but not convex */
#define Convex			2	/* wholly convex */
#define NoValue		0x0000
#define XValue  	0x0001
#define YValue		0x0002
#define WidthValue  	0x0004
#define HeightValue  	0x0008
#define AllValues 	0x000F
#define XNegative 	0x0010
#define YNegative 	0x0020
#define StaticGray		0
#define GrayScale		1
#define StaticColor		2
#define PseudoColor		3
#define TrueColor		4
#define DirectColor		5
#define AllocNone		0	/* create map with no entries */
#define AllocAll		1	/* allocate entire map writeable */

void XCloseDisplay(Display *display);
void XDestroyRegion(Region r);
void XFlush(Display *display);
int XEventsQueued(Display *display, int mode);
int XQLength(Display *display);
void XNextEvent(Display *display, XEvent *event_return);
void XDestroyWindow(Display *d, Window w);
void XMapWindow(Display *d, Window w);
void XMapRaised(Display *d, Window w);
void XUnmapWindow(Display *d, Window w);
void XUnionRectWithRegion(XRectangle *rectangle, 
	Region src_region, Region dest_region_return);
void XGetErrorText(Display *display, int code, char *buffer_return, int length);
void XGetErrorDatabaseText(Display *display, char *name, char *message,
	char *default_string, char *buffer_return, int length);
XIM XOpenIM(Display *dpy, void *rdb, char *res_name, char *res_class);
Status XCloseIM(XIM im);
char *XGetIMValues(XIM im, ...);
XIC XCreateIC(XIM im, ...);
void XDestroyIC(XIC ic);
#define XFree free
typedef int (*XIOErrorHandler) (Display* display);
typedef int (*XErrorHandler) (Display* display, XErrorEvent *error_event);
XIOErrorHandler XSetIOErrorHandler(XIOErrorHandler handler);
XErrorHandler XSetErrorHandler(XErrorHandler handler);
Display *XOpenDisplay(const char* display_name);
#define XDisplayName(str) ":0.0"
Atom XInternAtom(Display *display, const char* atom_name, char only_if_exists);
Window XCreateSimpleWindow(Display* display, Window parent, int x, int y,
	unsigned int width, unsigned int height, unsigned int border_width,
	unsigned long border, unsigned long background);

char XQueryPointer(Display *display, Window w, Window *root_return,
	Window* child_return, int *root_x_return, int *root_y_return,
	int * win_x_return, int *win_y_return, unsigned int *mask_return);
void XConvertSelection(Display *display, Atom selection, Atom target,
	Atom property, Window requestor, Time time);
char XFilterEvent(XEvent *event, Window w);
Status XSendEvent( Display* display , Window w, char propagate,
	long event_maks, XEvent* event_send);
int XSetSelectionOwner(Display *display, Atom selection, 
	Window owner, Time time);
char *XSetLocaleModifiers(const char* modifier_list);
int XGetWindowProperty (Display *display, Window w, Atom property,
	long long_offset, long long_length, char delete_, Atom req_type,
	Atom* actual_type_return, int* actual_format_return,
	unsigned long *nitems_return, unsigned long *bytes_after_return,
	unsigned char **prop_return);
int XChangeProperty( Display *display, Window w, Atom property,
	Atom type, int format, int mode, const unsigned char *data,
	int nelements);
void XSetICFocus(XIC ic);
void XUnsetICFocus(XIC ic);
KeySym XKeycodeToKeysym (Display *display, KeyCode keycode, int index);
char XTranslateCoordinates(Display* display, Window src_w, Window dest_w,
	int src_x, int src_y, int* dest_x_return, int *dest_y_return,
	Window* child_return);
int XMoveWindow(Display *display, Window w, int x, int y);
int XMoveResizeWindow(Display *display, Window w, int x, int y,
	unsigned int width, unsigned int height);
int XSetTransientForHint(Display *display, Window w, Window prop_window);
int XLookupString(XKeyEvent *event_struct, char * buffer_return,
	int byte_buffer, KeySym * keysym_return, XComposeStatus *status_in_out);

Status XGetWindowAttributes(Display *display, Window w,
	XWindowAttributes * window_attributes);
Window XCreateWindow(Display *display, Window parent, int x, int y,
	unsigned int width, unsigned int height, unsigned int border_width,
	int depth, unsigned int class_, Visual * visual, 
	unsigned long valuemask, XSetWindowAttributes *attributes);

int XSetWMHints(Display *display, Window w, XWMHints* wm_hints);
void XSetWMNormalHints(Display *display, Window w, XSizeHints *hints);
int XSetForeground(Display *display, GC gc, unsigned long foreground);
int XSetLineAttributes(Display *display, GC gc, unsigned int line_width,
	int line_style, int cap_style, int joint_style);
int XSetDashes(Display* display, GC gc, int dash_offset, 
	const char *dash_list, int n);
int XFreeFontNames(char **list);
int XUtf8LookupString( XIC ic, XKeyPressedEvent* event, char* buffer_return,
    	int bytes_buffer, KeySym*  keysym, Status* status_return);
XUtf8FontStruct * XCreateUtf8FontStruct (Display *dpy, 
	const char *base_font_name_list); 

void XUtf8DrawString( Display *display, Drawable d, XUtf8FontStruct *font_set,
        GC gc, int x, int y, const char *string, int num_bytes);

void XUtf8DrawRtlString( Display *display, Drawable d, 
	XUtf8FontStruct  *font_set, GC 	gc, int	x, int 	y,
        const char *string, int  num_bytes);

void XFreeUtf8FontStruct( Display *dpy, XUtf8FontStruct *font_set);
int XUtf8TextWidth( XUtf8FontStruct  *font_set, const char *string,
        int num_bytes);
int XUtf8UcsWidth( XUtf8FontStruct  *font_set, unsigned int ucs);
long XKeysymToUcs(KeySym keysym);
char **XListFonts(Display *display, const char *pattern, int maxnames,
	int *actual_count_return);
int XDrawLine(Display *display, Drawable d, GC gc, 
	int x1, int y1, int x2, int y2);
int XFillRectangle(Display *display, Drawable d, GC gc, int x, int y,
	unsigned int width, unsigned int height);
int XDrawRectangle(Display *display, Drawable d, GC gc, int x, int y,
	unsigned int width, unsigned int height);
int XDrawArc(Display *display, Drawable d, GC gc, int x, int y,
	unsigned int width, unsigned int height, int angle1, int angle2);
int XFillArc(Display *display, Drawable d, GC gc, int x, int y,
	unsigned int width, unsigned int height, int angle1, int angle2);

int XFillPolygon(Display *display, Drawable d, GC gc, XPoint* points,
	int npoints, int shape, int mode);
int XDrawLines(Display *display, Drawable d, GC gc, XPoint* points,
	int npoints, int mode);
int XDrawPoints(Display *display, Drawable d, GC gc, XPoint* points,
	int npoints, int mode);
int XDrawPoint(Display *display, Drawable d, GC gc, int x, int y);
Pixmap XCreatePixmap(Display *display, Drawable d, unsigned int width,
	unsigned int height, unsigned int depth);
int XCopyArea(Display *display, Drawable src, Drawable dest, GC gc,
	int src_x, int src_y, int width, int height, int dest_x, int dest_y);
int XSetClipOrigin(Display *display, GC gc, int x, int y);
Region XCreateRegion(void);
int XSetRegion(Display* display, GC gc, Region r);
int XIntersectRegion(Region sra, Region srb, Region dr_return);
int XRectInRegion(Region r, int x, int y, unsigned int width, 
	unsigned int height);
int XSetClipMask(Display* display, GC gc, Pixmap pixmap);
int XClipBox(Region r, XRectangle *rect_return);
char *XGetDefault(Display *display, const char* program,
	const char *option);
char XParseGeometry(const char * parsestring, int* x_return, int* y_return,
	unsigned int *width_return, unsigned int *height_return);
int XFreePixmap(Display* display, Pixmap pixmap);
int XImageByteOrder(Display *display);
XPixmapFormatValues *XListPixmapFormats(Display *display, int *count_return);
Status XParseColor(Display *display, char colormap, const char *spec,
	XColor *exact_def_return);
int XPutImage(Display *display, Drawable d, GC gc, XImage *image,
	int src_x, int src_y, int dest_x, int dest_y, unsigned int width,
	unsigned int height);
Colormap XCreateColormap(Display *display, Window w, Visual* visual,
	int alloc);
Pixmap XCreateBitmapFromData(Display* display, Drawable d, 
	const char *data, unsigned int width, unsigned int height);
int XSetStipple(Display *display, GC gc, Pixmap stipple);
int XSetTSOrigin(Display *display, GC gc, int x, int y);
int XSetFillStyle(Display *display, GC gc, int fill_style);
char *XKeysymToString(KeySym keysym);
GC XCreateGC(Display *dpy, Drawable d, unsigned long valuemaks, 
	XGCValues* values); 
/*
XFontStruct *XLoadQueryFont(Display *display, const char * name);
int XFreeFont(Display *display, XFontStruct * font_struct);
int XSetFont(Display *display, GC gc, Font font);
*/

/* unistd.h */
char *getcwd(char* buf, int size);
int mkdir(const char *pathname, int mode);
int select(int n, fd_set *readfs, fd_set *writefds, 
	fd_set *exceptfds, struct timeval *timeout);
int strcasecmp(const char *str1, const char *str2);
int rint(int r);

#endif
