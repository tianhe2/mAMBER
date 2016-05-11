/* $XConsortium: Grip.c,v 1.31 91/07/21 18:53:29 gildea Exp $ */

/***********************************************************
Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts,
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

******************************************************************/

/*
 * Grip.c - Grip Widget (Used by Paned Widget)
 *
 */
#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#include "XawInit.h"
#include "GripP.h"

#include "XrawDebug.h"

static void Def_pixel();

static XtResource resources[] = {
  {
    XtNwidth, XtCWidth, XtRDimension, sizeof(Dimension),
    XtOffsetOf(GripRec, core.width), XtRImmediate,
    (XtPointer) DEFAULT_GRIP_SIZE
  },
  {
    XtNheight, XtCHeight, XtRDimension, sizeof(Dimension),
    XtOffsetOf(GripRec, core.height), XtRImmediate,
    (XtPointer) DEFAULT_GRIP_SIZE
  },
  {
    XtNgripForeground, XtCForeground, XtRPixel, sizeof(Pixel),
    XtOffsetOf(GripRec, core.background_pixel), XtRCallProc, 
    (XtPointer) Def_pixel
  },
  {
    XtNborderWidth, XtCBorderWidth, XtRDimension, sizeof(Dimension),
    XtOffsetOf(GripRec, core.border_width), XtRImmediate, (XtPointer)0
  },
  {
    XtNcallback, XtCCallback, XtRCallback, sizeof(XtPointer), 
    XtOffsetOf(GripRec, grip.grip_action), XtRCallback, NULL
  },
  {
    XtNhighlightThickness, XtCHighlightThickness, XtRDimension,
    sizeof(Dimension),
    XtOffsetOf(GripRec, simple.highlight_thickness), XtRImmediate,
    (XtPointer) 0
  },
  {
    XtNshadowWidth, XtCShadowWidth, XtRDimension, sizeof(Dimension),
    XtOffsetOf(GripRec, simple.shadow_thickness), XtRImmediate, (XtPointer) 2
  }
};

/* ARGSUSED */
static void Def_pixel( w, offset, value)
     Widget w;
     int offset; /* unused */
     XrmValue *value;
{
  Widget parent = XtParent(w);
  static Pixel pixel;

  pixel = parent->core.background_pixel;
  
  value->addr = (caddr_t)&pixel;
}

static void GripAction( /* Widget, XEvent*, String*, Cardinal */ );

static XtActionsRec actionsList[] =
{
  {"GripAction",      GripAction},
};

#define SuperClass (&simpleClassRec)

GripClassRec gripClassRec = {
   {
/* core class fields */
    /* superclass         */   (WidgetClass) SuperClass,
    /* class name         */   "Grip",
    /* size               */   sizeof(GripRec),
    /* class initialize   */   XawInitializeWidgetSet,
    /* class_part_init    */   NULL,
    /* class_inited       */   FALSE,
    /* initialize         */   NULL,
    /* initialize_hook    */   NULL,
    /* realize            */   XtInheritRealize,
    /* actions            */   actionsList,
    /* num_actions        */   XtNumber(actionsList),
    /* resources          */   resources,
    /* resource_count     */   XtNumber(resources),
    /* xrm_class          */   NULLQUARK,
    /* compress_motion    */   TRUE,
    /* compress_exposure  */   TRUE,
    /* compress_enterleave*/   TRUE,
    /* visible_interest   */   FALSE,
    /* destroy            */   NULL,
    /* resize             */   NULL,
    /* expose             */   XtInheritExpose,
    /* set_values         */   NULL,
    /* set_values_hook    */   NULL,
    /* set_values_almost  */   XtInheritSetValuesAlmost,
    /* get_values_hook    */   NULL,
    /* accept_focus       */   NULL,
    /* version            */   XtVersion,
    /* callback_private   */   NULL,
    /* tm_table           */   NULL,
    /* query_geometry     */   XtInheritQueryGeometry,
    /* display_accelerator*/   XtInheritDisplayAccelerator,
    /* extension          */   NULL
   },
    /* Simple class fields initialization */
   {
    /* change_sensitive   */   XtInheritChangeSensitive,
    /* display_rect       */   XtInheritDisplayRectProc,
    /* extension          */   NULL
   },
    /* Grip class fields initialization */
   {
    /* not used		  */   0
   }
};

WidgetClass gripWidgetClass = (WidgetClass) &gripClassRec;

static void GripAction( widget, event, params, num_params )
    Widget widget;
    XEvent *event;
    String *params;
    Cardinal *num_params;
{
    XawGripCallDataRec call_data;

    call_data.event = event;
    call_data.params = params;
    call_data.num_params = *num_params;

    XtCallCallbacks( widget, XtNcallback, (XtPointer)&call_data );
}
