/* 

Copyright (c) 2002 O'ksi'D

*/

#include <X11/Xlib.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <i86.h>
#include <unistd.h>
#include <string.h>

#define NEED_REDRAW 0x0001
#define NEED_MAP 0x0002

typedef struct {
	char *title;
	int x,y;
	unsigned int width, height;
	unsigned char *data;
	Window parent;
	int flags;
} drawable;
 
static union REGS in, out;
static union REGPACK regs;
static char mouse_ = 0;
static unsigned char far* VideoRAM=(unsigned char far*)MK_FP(0xA000,0);

static drawable* drawables = NULL;
static int nb_drawables = 0;
static int gfx_state = NEED_REDRAW;
static int mouse_x, mouse_y;
static unsigned int mouse_s;
static int run = 1;

void XDestroyRegion(Region r){
}

void XFlush(Display *display){
	gfx_state |= NEED_REDRAW;
}

int XEventsQueued(Display *display, int mode){
	static off = 0;
	off = !off;
	return off;
}
int XQLength(Display *display){
	static off = 0;
	off = !off;
	return off;
}

static char get_key()
{
	in.x.ax=0x0100;
	int86(0x16,&in,&out);
	if (!(out.x.cflag & 64) && (out.x.ax & 0xff)) {
		in.x.ax=0x0000;
		int86(0x16,&in,&out);
		return 0xFF & (out.x.ax);
	}
	return 0;
}

void XNextEvent(Display *display, XEvent *event_return){
	Window root, child;
	int x, y, x1, y1, i;
	unsigned int mask;
	delay(20);
	if (get_key()) {
		XCloseDisplay(display);
		exit(0);
	}
	XQueryPointer(display, 0, &root, &child, &x, &y, &x1, &y1, &mask);
	event_return->xany.window = nb_drawables - 1;
	if (x != mouse_x || y != mouse_y) {
		event_return->xany.type = MotionNotify;
		mouse_x = x;
		mouse_y = y;
		return;
	}
	if (mask != mouse_s) {
		if (mouse_s < mask) {
			event_return->xbutton.type = ButtonPress;
		} else {
			event_return->xbutton.type = ButtonRelease;
		}
		mouse_s = mask;
		return;
	}
	if (gfx_state & NEED_REDRAW) {
		event_return->xexpose.type = Expose;
		gfx_state &= ~NEED_REDRAW;
		return;
	}
	i = nb_drawables;
	while (i > 0) {
		i--;
		if (drawables[i].flags & NEED_MAP) {
			event_return->xany.window = i;
			event_return->type = MapNotify;
			drawables[i].flags &= ~NEED_MAP; 
			return;
		}
	}
}

void XDestroyWindow(Display *d, Window w){
	free(drawables[w].data);
	free(drawables[w].title);
	drawables[w].data = NULL;
	drawables[w].title = NULL;
}

void XMapWindow(Display *d, Window w){
	drawables[w].flags |= NEED_MAP;
	if (drawables[w].data == VideoRAM) return;
	free(drawables[w].data);
	drawables[w].data = VideoRAM;
}

void XMapRaised(Display *d, Window w){
	XMapWindow(d, w);
}

void XUnmapWindow(Display *d, Window w){
}

void XUnionRectWithRegion(XRectangle *rectangle, 
	Region src_region, Region dest_region_return)
{

}

void XGetErrorText(Display *display, int code, char *buffer_return, int length){

}

void XGetErrorDatabaseText(Display *display, char *name, char *message,
	char *default_string, char *buffer_return, int length)
{
}

XIM XOpenIM(Display *dpy, void *rdb, char *res_name, char *res_class){
	return 0;
}

Status XCloseIM(XIM im){
	return 0;
}

char *XGetIMValues(XIM im, ...) {
	return 0;

}

XIC XCreateIC(XIM im, ...){
	return 0;
}

void XDestroyIC(XIC ic){
}

XIOErrorHandler XSetIOErrorHandler(XIOErrorHandler handler){
	return 0;
}

XErrorHandler XSetErrorHandler(XErrorHandler handler){
	return 0;
}

Display *XOpenDisplay(const char* display_name){
	static Display d = 1;
//return &d;
	/* init the 640x480 16 color mode */
	in.x.ax=0x12;
	int86(0x10,&in,&out);
	
	/* detect mouse*/
	in.x.ax=0;
	int86(0x33,&in,&out);
	if (out.x.ax != 0) {
		/* show mouse */
		mouse_ = 1;
		in.x.ax=1;
		int86(0x33,&in,&out);
	} else {
		mouse_ = 0;
	}
	return &d;
}
void XCloseDisplay(Display *display) {
	/* text mode*/
	in.x.ax=3;
	int86(0x10,&in,&out);
	if (mouse_) {
		/* hide mouse */
		in.x.ax=2;
		int86(0x33,&in,&out);
	}
}

Atom XInternAtom(Display *display, const char* atom_name, char only_if_exists){
	return 0;
}

Window XCreateSimpleWindow(Display* display, Window parent, int x, int y,
	unsigned int width, unsigned int height, unsigned int border_width,
	unsigned long border, unsigned long background)
{
	return 0;
}


char XQueryPointer(Display *display, Window w, Window *root_return,
	Window* child_return, int *root_x_return, int *root_y_return,
	int *win_x_return, int *win_y_return, unsigned int *mask_return)
{
	int b;
	/* get mouse state and position */
	in.x.ax=3;
	int86(0x33, &in, &out);
	*root_x_return = out.x.cx;
	*root_y_return = out.x.dx;
	*mask_return = 0;
	b = out.x.bx;
	if (b&1)  *mask_return |= Button1Mask; 
	if (b&2)  *mask_return |= Button2Mask; 
	if (b&4)  *mask_return |= Button3Mask; 
	return 0;
}

void XConvertSelection(Display *display, Atom selection, Atom target,
	Atom property, Window requestor, Time time)
{
}

char XFilterEvent(XEvent *event, Window w){
	return 0;
}

Status XSendEvent( Display* display , Window w, char propagate,
	long event_maks, XEvent* event_send)
{
	return 0;
}

int XSetSelectionOwner(Display *display, Atom selection, 
	Window owner, Time time)
{
	return 0;
}

char *XSetLocaleModifiers(const char* modifier_list){
	return 0;
}

int XGetWindowProperty (Display *display, Window w, Atom property,
	long long_offset, long long_length, char delete_, Atom req_type,
	Atom* actual_type_return, int* actual_format_return,
	unsigned long *nitems_return, unsigned long *bytes_after_return,
	unsigned char **prop_return)
{
	return 0;
}

int XChangeProperty( Display *display, Window w, Atom property,
	Atom type, int format, int mode, const unsigned char *data,
	int nelements)
{
	return 0;
}

void XSetICFocus(XIC ic){
}

void XUnsetICFocus(XIC ic){
}

KeySym XKeycodeToKeysym (Display *display, KeyCode keycode, int index){
	return 0;
}

char XTranslateCoordinates(Display* display, Window src_w, Window dest_w,
	int src_x, int src_y, int* dest_x_return, int *dest_y_return,
	Window* child_return)
{
	return 0;
}

int XMoveWindow(Display *display, Window w, int x, int y)
{
	return 0;
}

int XMoveResizeWindow(Display *display, Window w, int x, int y,
	unsigned int width, unsigned int height)
{
	return 0;
}

int XSetTransientForHint(Display *display, Window w, Window prop_window){
	return 0;
}

int XLookupString(XKeyEvent *event_struct, char * buffer_return,
	int byte_buffer, KeySym * keysym_return, XComposeStatus *status_in_out)
{
	return 0;
}


Status XGetWindowAttributes(Display *display, Window w,
	XWindowAttributes * window_attributes)
{
	return 0;
}

Window XCreateWindow(Display *display, Window parent, int x, int y,
	unsigned int width, unsigned int height, unsigned int border_width,
	int depth, unsigned int class_, Visual * visual, 
	unsigned long valuemask, XSetWindowAttributes *attributes)
{
	int i = 0;
	drawable *d = NULL;
	while(i < nb_drawables) {
		if (drawables[i].data == NULL) {
			d = drawables + i;
			break;
		}
		i++;
	}
	if (!d) {
		drawables = (drawable*) realloc(drawables, 
			sizeof(drawable) * (nb_drawables + 1));
		d = drawables + nb_drawables;
		nb_drawables++;
	}
	d->x = x = 0;
	d->y = y = 0;
	d->width = width;
	d->height = height;
	d->title = NULL;
	d->parent = parent;
	if (width & 1) width++;
	d->data = (unsigned char*) malloc((width/2) * height);
	return nb_drawables - 1;
}


int XSetWMHints(Display *display, Window w, XWMHints* wm_hints)
{
	return 0;
}

void XSetWMNormalHints(Display *display, Window w, XSizeHints *hints)
{
}

int XSetForeground(Display *display, GC gc, unsigned long foreground){
	gc->foreground = foreground;
	return 0;
}

int XSetLineAttributes(Display *display, GC gc, unsigned int line_width,
	int line_style, int cap_style, int joint_style)
{
	return 0;
}

int XSetDashes(Display* display, GC gc, int dash_offset, 
	const char *dash_list, int n)
{
	return 0;
}

int XFreeFontNames(char **list) {
	return 0;
}

int XUtf8LookupString( XIC ic, XKeyPressedEvent* event, char* buffer_return,
    	int bytes_buffer, KeySym*  keysym, Status* status_return)
{
	return 0;
}

XUtf8FontStruct * XCreateUtf8FontStruct (Display *dpy, 
	const char *base_font_name_list)
{
	XUtf8FontStruct *f = (XUtf8FontStruct*) malloc(sizeof(XUtf8FontStruct));
	f->nb_font = 0;
	f->font_name_list = NULL;
	f->encodings = NULL;
	f->fonts = NULL;
	f->fid = 0;
	f->ascent = 0;
	f->descent = 0;
	f->ranges = NULL;
	return f;
}
 

void XUtf8DrawString( Display *display, Drawable d, XUtf8FontStruct *font_set,
        GC gc, int x, int y, const char *string, int num_bytes)
{
	typedef  unsigned char font[256][8];
	typedef font far *fontptr;
	static fontptr f = 0;
	if (f == 0) {
		regs.x.bx = 0x0300;
		regs.x.ax = 0x1130;
		intr(0x10, &regs);
		f = (fontptr)MK_FP(regs.x.es, regs.x.bp);
	}
	static h = 2;
	h++;
	gc->foreground += h ;
	if (f == 0) return;
	y -= 8;
	for (int i = 0; i < num_bytes;i++) {
		for (int j = 0; j < 8; j++) {
			unsigned char mask = 0x36;
			mask = (*f)[(unsigned int)(string[i])][j];
			for(int k = 0;k < 8; k++) {
				if (mask & (128 >> k)) {
					XDrawPoint(display, d, gc, x+k, y+j);
				}
			}
		}
		x += 8;
	}
}


void XUtf8DrawRtlString( Display *display, Drawable d, 
	XUtf8FontStruct  *font_set, GC 	gc, int	x, int 	y,
        const char *string, int  num_bytes)
{
}


void XFreeUtf8FontStruct( Display *dpy, XUtf8FontStruct *font_set){
}


int XUtf8TextWidth( XUtf8FontStruct  *font_set, const char *string,
        int num_bytes)
{
	return num_bytes * 8;
}

int XUtf8UcsWidth( XUtf8FontStruct  *font_set, unsigned int ucs){
	return 0;
}

long XKeysymToUcs(KeySym keysym){
	return 0;
}

char **XListFonts(Display *display, const char *pattern, int maxnames,
	int *actual_count_return)
{
	return 0;
}

int XDrawLine(Display *display, Drawable d, GC gc, 
	int x1, int y1, int x2, int y2)
{
	XDrawPoint(display, d, gc, x1, y1);
	XDrawPoint(display, d, gc, x2, y2);
	return 0;
}

int XFillRectangle(Display *display, Drawable d, GC gc, int x, int y,
	unsigned int width, unsigned int height)
{
	gc->foreground = 2;
	for (unsigned int i = 0; i < width; i++) {
		for(unsigned int j = 0;j < height; j++) {
			XDrawPoint(display, d, gc, x + i, y +j);
		}
	}
	return 0;
}

int XDrawRectangle(Display *display, Drawable d, GC gc, int x, int y,
	unsigned int width, unsigned int height)
{
	printf("Rectangle\n");
	return 0;
}

int XDrawArc(Display *display, Drawable d, GC gc, int x, int y,
	unsigned int width, unsigned int height, int angle1, int angle2)
{
	printf("Draw arc");
	return 0;
}

int XFillArc(Display *display, Drawable d, GC gc, int x, int y,
	unsigned int width, unsigned int height, int angle1, int angle2)
{
	return 0;
}


int XFillPolygon(Display *display, Drawable d, GC gc, XPoint* points,
	int npoints, int shape, int mode)
{
	printf("fill poly");
	return 0;
}

int XDrawLines(Display *display, Drawable d, GC gc, XPoint* points,
	int npoints, int mode)
{
	printf("draw LINES");
	return 0;
}

int XDrawPoints(Display *display, Drawable d, GC gc, XPoint* points,
	int npoints, int mode)
{
	printf("draw points");
	return 0;
}

GC XCreateGC(Display *dpy, Drawable d, unsigned long valuemaks, 
	XGCValues* values)
{
	GC ret = (GC) malloc(sizeof(_XGC));
	ret->foreground = 0;
	return ret;
}
 
int XDrawPoint(Display *display, Drawable d, GC gc, int x, int y)
{
	int off;
	unsigned char far* video=drawables[d].data;
	x += drawables[d].x;
	y += drawables[d].y;
	if (video != VideoRAM) {
		off = x / 2 + y * 320;
		if (x&1) {
			video[off] &=0x0F;
			video[off] |=  gc->foreground << 4;
		} else {
			video[off] &=0xF0;
			video[off] |=  gc->foreground;
		}
	} else {
		unsigned char m = 7 - (x % 8);
		unsigned char o;
		off = (y * 80)  + (x / 8); 
		outpw(0x3ce, ((1 << m) << 8) + 8);
		outpw(0x3ce, (2 << 8) + 5);
		o = video[off];
		video[off] = (o & 0xF0) | (gc->foreground & 0x0F);

		outpw(0x3ce, (0xFF << 8) + 8);
		outpw(0x3ce, 5);
	}
	return 0;
}

Pixmap XCreatePixmap(Display *display, Drawable d, unsigned int width,
	unsigned int height, unsigned int depth)
{
	return 0;
}

int XCopyArea(Display *display, Drawable src, Drawable dest, GC gc,
	int src_x, int src_y, int width, int height, int dest_x, int dest_y)
{
	return 0;
}

int XSetClipOrigin(Display *display, GC gc, int x, int y){
	return 0;
}

Region XCreateRegion(void){
	return 0;
}

int XSetRegion(Display* display, GC gc, Region r){
	return 0;
}

int XIntersectRegion(Region sra, Region srb, Region dr_return){
	return 0;
}
int XRectInRegion(Region r, int x, int y, unsigned int width, 
	unsigned int height)
{
	return 0;
}

int XSetClipMask(Display* display, GC gc, Pixmap pixmap){
	return 0;
}

int XClipBox(Region r, XRectangle *rect_return){
	return 0;
}

char *XGetDefault(Display *display, const char* program,
	const char *option)
{
	return 0;
}

char XParseGeometry(const char * parsestring, int* x_return, int* y_return,
	unsigned int *width_return, unsigned int *height_return)
{
	return 0;
}

int XFreePixmap(Display* display, Pixmap pixmap)
{
	return 0;
}

int XImageByteOrder(Display *display)
{
	return 0;
}

XPixmapFormatValues *XListPixmapFormats(Display *display, int *count_return) {
	return 0;
}

Status XParseColor(Display *display, char colormap, const char *spec,
	XColor *exact_def_return)
{
	if (!strcmp("#000000", spec)) {
		exact_def_return->pixel = 0;
		return 1;
	} else if (!strcmp("#ffffff", spec)) {
		exact_def_return->pixel = 0x0F;
		return 1;
	} else if (!strcmp("#c0c0c0", spec)) {
		exact_def_return->pixel = 0x07;
		return 1;
	} else if (!strcmp("#000080", spec)) {
		exact_def_return->pixel = 0x02;
		return 1;
	}
	return 0;
}

int XPutImage(Display *display, Drawable d, GC gc, XImage *image,
	int src_x, int src_y, int dest_x, int dest_y, unsigned int width,
	unsigned int height)
{
	return 0;
}
Colormap XCreateColormap(Display *display, Window w, Visual* visual,
	int alloc)
{
	return 0;
}

Pixmap XCreateBitmapFromData(Display* display, Drawable d, 
	const char *data, unsigned int width, unsigned int height)
{
	return 0;
}

int XSetStipple(Display *display, GC gc, Pixmap stipple)
{
	return 0;
}

int XSetTSOrigin(Display *display, GC gc, int x, int y)
{
	return 0;
}

int XSetFillStyle(Display *display, GC gc, int fill_style)
{
	return 0;
}

char *XKeysymToString(KeySym keysym)
{
	return 0;
}


/* unistd.h */
char *getcwd(char* buf, int size){
	return 0;
}

int mkdir(const char *pathname, int mode){
	return 0;
}

int select(int n, fd_set *readfs, fd_set *writefds, 
	fd_set *exceptfds, struct timeval *timeout)
{
	return 0;
}

int strcasecmp(const char *str1, const char *str2)
{
	return 0;
}

int rint(int r){
	double d = r + 0.5;
	return (int) d;
}

int gettimeofday(struct timeval *tv, struct timezone *tz) {
	return 0;

}



