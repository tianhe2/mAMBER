/* $XConsortium: Viewport.h,v 1.21 91/07/22 19:05:23 converse Exp $ */

/************************************************************
Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts,
and the Massachusetts Institute of Technology, Cambridge, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital or MIT not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

********************************************************/

#ifndef _XawViewport_h
#define _XawViewport_h

#include "Form.h"
#include "Reports.h"

/* Resources:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 allowHoriz	     Boolean		Boolean		False
 allowVert	     Boolean		Boolean		False
 background	     Background		Pixel		XtDefaultBackground
 border		     BorderColor	Pixel		XtDefaultForeground
 borderWidth	     BorderWidth	Dimension	1
 destroyCallback     Callback		Pointer		NULL
 foreceBars	     Boolean		Boolean		False
 height		     Height		Dimension	0
 mappedWhenManaged   MappedWhenManaged	Boolean		True
 reportCallback	     ReportCallback	Pointer		NULL
 sensitive	     Sensitive		Boolean		True
 useBottom	     Boolean		Boolean		False
 useRight	     Boolean		Boolean		False
 width		     Width		Dimension	0
 x		     Position		Position	0
 y		     Position		Position	0

*/


/*#########################################################################*/
/*#                                                                       #*/
/*#                           New Resources                               #*/
/*#                                                                       #*/
/*#########################################################################*/
#ifndef XtNforceBars
#define XtNforceBars "forceBars"
#endif

#ifndef XtNallowHoriz
#define XtNallowHoriz "allowHoriz"
#endif

#ifndef XtNallowVert
#define XtNallowVert "allowVert"
#endif

#ifndef XtNuseBottom
#define XtNuseBottom "useBottom"
#endif

#ifndef XtNuseRight
#define XtNuseRight "useRight"
#endif

#ifndef XtNframeWidth
#define XtNframeWidth "frameWidth"
#endif

#ifndef XtNscrollbarWidth
#define XtNscrollbarWidth "scrollbarWidth"
#endif

#ifndef XtNdistance
#define XtNdistance "distance"
#endif

/*#########################################################################*/
/*#                                                                       #*/
/*#                           New Resource Classes                        #*/
/*#                                                                       #*/
/*#########################################################################*/

#ifndef XtCDistance
#define XtCDistance      "Distance"
#endif

#ifndef XtCScrollbarWidth
#define XtCScrollbarWidth "ScrollbarWidth"
#endif

#ifndef XtCFrameWidth
#define XtCFrameWidth    "FrameWidth"
#endif



extern void XawViewportSetLocation (
    Widget		/* gw */,
    /* float */ double	/* xoff */,
    /* float */ double	/* yoff */
);

extern void XawViewportSetCoordinates (
    Widget		/* gw */,
    /* Position */ int	/* x */,
    /* Position */ int	/* y */
);


/*#########################################################################*/
/*#                                                                       #*/
/*#                           Widget Class Pointer                        #*/
/*#                                                                       #*/
/*#########################################################################*/
extern WidgetClass viewportWidgetClass;

typedef struct _ViewportClassRec *ViewportWidgetClass;
typedef struct _ViewportRec  *ViewportWidget;


#endif /* _XawViewport_h */
/* DON'T ADD STUFF AFTER THIS #endif */
