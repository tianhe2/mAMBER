#include 	<X11/IntrinsicP.h>
#include	<X11/StringDefs.h>
#include	<X11/keysym.h>
#include        <X11/cursorfont.h>


#include        "xaLeap.h"
#include        "xcursor.h"

VARARRAY shellVarArray;
VARARRAY waitCursorWindow;

#define TURN_CURSORS 25
static Cursor turn[TURN_CURSORS];


#define turn1_width 32
#define turn1_height 32
static char turn1_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x8c, 0x38, 0x00,
  0x00, 0xff, 0xc0, 0x00, 0x80, 0x7f, 0x00, 0x01, 0xc0, 0x7f, 0x00, 0x02,
  0xe0, 0xff, 0x00, 0x04, 0xf0, 0xff, 0x00, 0x08, 0xe8, 0xff, 0x00, 0x10,
  0xe8, 0x1f, 0x00, 0x10, 0xec, 0x5f, 0xe0, 0x21, 0xc4, 0x7f, 0xff, 0x27,
  0x84, 0x9f, 0xff, 0x3f, 0x02, 0x03, 0xf8, 0x5f, 0x02, 0x00, 0xf8, 0x5f,
  0x02, 0x00, 0xf8, 0x5f, 0x02, 0x00, 0xf0, 0x5f, 0x02, 0x00, 0xf0, 0x4f,
  0x02, 0x00, 0xc0, 0x4f, 0x04, 0x00, 0x80, 0x27, 0x04, 0x00, 0x80, 0x27,
  0x04, 0x00, 0x80, 0x33, 0x08, 0x00, 0x80, 0x13, 0x18, 0x00, 0x80, 0x19,
  0x10, 0x00, 0x80, 0x0d, 0x20, 0x00, 0x00, 0x04, 0x40, 0x00, 0x80, 0x03,
  0x80, 0x00, 0x00, 0x01, 0x00, 0xf3, 0xcf, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn10_width 32
#define turn10_height 32
static char turn10_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0x00, 0x00, 0x7c, 0x20, 0x00,
  0x00, 0x1e, 0xc0, 0x00, 0x80, 0x1f, 0x00, 0x01, 0xc0, 0x0f, 0x00, 0x02,
  0xe0, 0x2f, 0x00, 0x04, 0xe0, 0x23, 0x00, 0x08, 0xf0, 0x01, 0x00, 0x10,
  0xf8, 0x01, 0x00, 0x10, 0xf8, 0x03, 0x00, 0x20, 0xfc, 0x01, 0x00, 0x20,
  0xfe, 0x00, 0x00, 0x20, 0x7e, 0x00, 0x00, 0x40, 0xfe, 0x20, 0x00, 0x40,
  0xfe, 0x10, 0x00, 0x40, 0xce, 0x00, 0x0a, 0x40, 0x02, 0x08, 0x00, 0x40,
  0x82, 0x16, 0x02, 0x40, 0x04, 0x01, 0x10, 0x20, 0x04, 0x85, 0x7f, 0x20,
  0x04, 0xc0, 0xff, 0x20, 0x08, 0xc0, 0x7f, 0x10, 0x08, 0xe0, 0x7f, 0x10,
  0x10, 0xe0, 0x37, 0x08, 0x20, 0xc0, 0x01, 0x04, 0x40, 0x00, 0x00, 0x02,
  0x80, 0x00, 0x00, 0x01, 0x00, 0x03, 0xc0, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xe0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn11_width 32
#define turn11_height 32
static char turn11_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x3c, 0x38, 0x00,
  0x00, 0x3f, 0xc0, 0x00, 0x80, 0x3f, 0x80, 0x01, 0xc0, 0x3f, 0x81, 0x03,
  0xe0, 0x0f, 0x80, 0x07, 0xf0, 0x0f, 0x80, 0x0f, 0xf8, 0x1f, 0x00, 0x1f,
  0xf8, 0x0f, 0x00, 0x1e, 0xfc, 0x1f, 0x00, 0x38, 0xfc, 0x07, 0x00, 0x30,
  0xfe, 0x07, 0x00, 0x38, 0xfe, 0x87, 0x01, 0x40, 0x3e, 0x07, 0x00, 0x40,
  0x3a, 0x00, 0x44, 0x40, 0x32, 0x60, 0x00, 0x40, 0x32, 0x42, 0x00, 0x40,
  0x12, 0x08, 0x50, 0x40, 0x04, 0x00, 0xf8, 0x23, 0x04, 0x00, 0xf8, 0x23,
  0x04, 0x00, 0xfc, 0x23, 0x08, 0x00, 0xfe, 0x13, 0x08, 0x00, 0x9e, 0x11,
  0x10, 0x00, 0x04, 0x08, 0x20, 0x00, 0x00, 0x04, 0x40, 0x00, 0x00, 0x02,
  0x80, 0x00, 0x00, 0x01, 0x00, 0x03, 0xc0, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn12_width 32
#define turn12_height 32
static char turn12_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x0f, 0x00, 0x00, 0xfe, 0x30, 0x00,
  0x00, 0xff, 0xc0, 0x00, 0x80, 0xff, 0x00, 0x01, 0xc0, 0x7f, 0x02, 0x02,
  0xe0, 0x7f, 0x04, 0x04, 0xf0, 0xff, 0x04, 0x08, 0xf8, 0xff, 0x08, 0x10,
  0xf8, 0x7f, 0x04, 0x10, 0xfc, 0x3f, 0x00, 0x20, 0xfc, 0x3f, 0x00, 0x20,
  0xfc, 0x7d, 0x00, 0x20, 0xfe, 0x01, 0x00, 0x41, 0xde, 0x01, 0x04, 0x40,
  0xce, 0x01, 0x02, 0x40, 0x8e, 0xe0, 0x00, 0x40, 0x06, 0x80, 0xc1, 0x47,
  0x06, 0x00, 0xc4, 0x4f, 0x0c, 0x00, 0xe4, 0x3f, 0x04, 0x00, 0xe0, 0x3f,
  0x04, 0x00, 0xf0, 0x27, 0x08, 0x00, 0xf0, 0x10, 0x08, 0x00, 0x70, 0x10,
  0x10, 0x00, 0x00, 0x08, 0x20, 0x00, 0x00, 0x04, 0x40, 0x00, 0x00, 0x02,
  0x80, 0x00, 0x00, 0x01, 0x00, 0x03, 0xc0, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn13_width 32
#define turn13_height 32
static char turn13_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x7c, 0x3b, 0x00,
  0x00, 0x7f, 0xc7, 0x00, 0x80, 0xff, 0x01, 0x01, 0xc0, 0xff, 0x03, 0x02,
  0xe0, 0xff, 0x07, 0x04, 0xf0, 0xff, 0x07, 0x08, 0xf8, 0xff, 0x03, 0x10,
  0xf8, 0xff, 0x01, 0x10, 0xfc, 0xff, 0x03, 0x20, 0xfc, 0x0f, 0x03, 0x20,
  0xfc, 0x0f, 0x00, 0x28, 0x7e, 0x06, 0x70, 0x40, 0x3e, 0x04, 0x10, 0x40,
  0x3e, 0x00, 0x08, 0x48, 0x1e, 0x00, 0x00, 0x5e, 0x3e, 0x00, 0x00, 0x7e,
  0x3e, 0x00, 0x00, 0x7f, 0x3c, 0x00, 0x00, 0x3f, 0x1c, 0x00, 0x80, 0x3f,
  0x1c, 0x00, 0x00, 0x33, 0x38, 0x00, 0x00, 0x10, 0x78, 0x00, 0x00, 0x10,
  0xf0, 0x01, 0x00, 0x08, 0xe0, 0x00, 0x00, 0x04, 0xc0, 0x01, 0x00, 0x02,
  0x80, 0x03, 0x00, 0x01, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn14_width 32
#define turn14_height 32
static char turn14_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xff, 0xdf, 0x00, 0x80, 0xff, 0x0f, 0x01, 0xc0, 0xff, 0x1f, 0x02,
  0xe0, 0xff, 0x3f, 0x04, 0xf0, 0xff, 0x1f, 0x08, 0xf8, 0xff, 0x0f, 0x10,
  0xf8, 0xff, 0x1e, 0x10, 0xfc, 0x7f, 0x00, 0x20, 0xfc, 0x71, 0x00, 0x21,
  0xfc, 0x61, 0x00, 0x23, 0xfe, 0x01, 0x00, 0x40, 0xfe, 0x00, 0x00, 0x70,
  0x7e, 0x00, 0x00, 0x70, 0xfe, 0x01, 0x00, 0x78, 0xfe, 0x01, 0x00, 0x78,
  0xfe, 0x01, 0x00, 0x7c, 0xfc, 0x00, 0x00, 0x3c, 0xfc, 0x00, 0x00, 0x20,
  0xf4, 0x00, 0x00, 0x20, 0xf8, 0x01, 0x00, 0x10, 0xe8, 0x03, 0x00, 0x10,
  0xd0, 0x03, 0x00, 0x08, 0xe0, 0x03, 0x00, 0x04, 0xc0, 0x03, 0x00, 0x02,
  0x80, 0x00, 0x00, 0x01, 0x00, 0x07, 0xc0, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn15_width 32
#define turn15_height 32
static char turn15_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xff, 0xff, 0x00, 0x80, 0xff, 0xff, 0x01, 0xc0, 0xff, 0xff, 0x02,
  0xe0, 0xff, 0x7f, 0x04, 0xf0, 0xff, 0x7f, 0x08, 0xf8, 0xff, 0xe7, 0x10,
  0xf8, 0xff, 0x07, 0x10, 0xcc, 0x03, 0x03, 0x24, 0xcc, 0x1f, 0x02, 0x2c,
  0xfc, 0x0f, 0x00, 0x22, 0xfe, 0x07, 0x00, 0x40, 0xfe, 0x03, 0x00, 0x40,
  0xfe, 0x0f, 0x00, 0x60, 0xfe, 0x0f, 0x00, 0x60, 0xfe, 0x07, 0x00, 0x70,
  0xfe, 0x07, 0x00, 0x70, 0xfc, 0x03, 0x00, 0x30, 0xf4, 0x07, 0x00, 0x20,
  0xe4, 0x07, 0x00, 0x20, 0xe8, 0x6f, 0x00, 0x10, 0xc8, 0x4f, 0x00, 0x10,
  0x90, 0x0f, 0x00, 0x08, 0x20, 0x1f, 0x00, 0x04, 0x40, 0x1e, 0x00, 0x02,
  0x80, 0x0c, 0x00, 0x01, 0x00, 0x03, 0xf0, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn16_width 32
#define turn16_height 32
static char turn16_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xff, 0xff, 0x00, 0x80, 0xff, 0xff, 0x01, 0xc0, 0xff, 0xfe, 0x03,
  0xe0, 0xff, 0xff, 0x05, 0xf0, 0xef, 0x3f, 0x0b, 0xf8, 0xff, 0x78, 0x14,
  0x78, 0xfe, 0x70, 0x10, 0x3c, 0xff, 0x20, 0x30, 0xfc, 0x77, 0x00, 0x20,
  0xfc, 0x2f, 0x00, 0x20, 0xfe, 0x0f, 0x00, 0x40, 0xfe, 0x7f, 0x00, 0x40,
  0xfe, 0x7f, 0x00, 0x40, 0xfe, 0x3f, 0x00, 0x40, 0xfe, 0x3f, 0x00, 0x60,
  0xfe, 0x3f, 0x00, 0x70, 0xcc, 0x3f, 0x00, 0x30, 0xc4, 0x7f, 0x04, 0x38,
  0x84, 0x7f, 0x06, 0x28, 0x08, 0x7f, 0x06, 0x10, 0x08, 0xfe, 0x00, 0x10,
  0x10, 0xfe, 0x00, 0x08, 0x20, 0xfc, 0x00, 0x04, 0x40, 0x30, 0x00, 0x02,
  0x80, 0x00, 0x00, 0x01, 0x00, 0x03, 0xc0, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn17_width 32
#define turn17_height 32
static char turn17_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xff, 0xff, 0x00, 0x80, 0xff, 0xff, 0x01, 0x40, 0x3f, 0xff, 0x03,
  0xe0, 0xff, 0xff, 0x07, 0xf0, 0xff, 0xc7, 0x08, 0x28, 0xf0, 0x87, 0x10,
  0x78, 0xfc, 0x07, 0x10, 0xf4, 0xbf, 0x03, 0x30, 0xf4, 0x7f, 0x00, 0x20,
  0xf4, 0xff, 0x07, 0x20, 0xfa, 0xff, 0x07, 0x40, 0xfa, 0xff, 0x03, 0x40,
  0xfa, 0xff, 0x03, 0x40, 0xfa, 0xff, 0x01, 0x40, 0xfa, 0xff, 0x03, 0x40,
  0x72, 0xfe, 0x03, 0x40, 0x04, 0xfc, 0x33, 0x20, 0x04, 0xf8, 0x37, 0x20,
  0x04, 0xf8, 0x07, 0x20, 0x08, 0xf0, 0x07, 0x10, 0x08, 0xe0, 0x03, 0x10,
  0x10, 0xc0, 0x03, 0x08, 0x20, 0x80, 0x01, 0x04, 0x40, 0x00, 0x00, 0x02,
  0x80, 0x00, 0x00, 0x01, 0x00, 0x03, 0xc0, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn18_width 32
#define turn18_height 32
static char turn18_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xff, 0xff, 0x00, 0x80, 0xfc, 0xfc, 0x01, 0x40, 0xff, 0xff, 0x03,
  0x20, 0x8f, 0x1f, 0x07, 0x10, 0x83, 0x3f, 0x0a, 0xc8, 0xe2, 0x3f, 0x10,
  0xc8, 0xff, 0x13, 0x10, 0xc4, 0xff, 0x3f, 0x20, 0xe4, 0xff, 0x7f, 0x20,
  0xe4, 0xff, 0x3f, 0x20, 0xe2, 0xff, 0x3f, 0x40, 0xe2, 0xff, 0x1f, 0x40,
  0xe2, 0xff, 0x1f, 0x40, 0xc2, 0xf7, 0x3f, 0x40, 0x82, 0xe1, 0x3f, 0x43,
  0x02, 0xc0, 0x3f, 0x43, 0x04, 0x80, 0x3f, 0x20, 0x04, 0x80, 0x3f, 0x20,
  0x04, 0x00, 0x3f, 0x20, 0x08, 0x00, 0x1f, 0x10, 0x08, 0x00, 0x1e, 0x10,
  0x10, 0x00, 0x0c, 0x08, 0x20, 0x00, 0x00, 0x04, 0x40, 0x00, 0x00, 0x02,
  0x80, 0x00, 0x00, 0x01, 0x00, 0xc3, 0xc3, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn19_width 32
#define turn19_height 32
static char turn19_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xbc, 0x3f, 0x00,
  0x00, 0xfb, 0xff, 0x00, 0x80, 0xf8, 0xff, 0x01, 0x40, 0x3c, 0xfc, 0x03,
  0x20, 0x04, 0xfe, 0x04, 0x10, 0x9e, 0xff, 0x08, 0x08, 0xfe, 0xff, 0x10,
  0x08, 0xfe, 0xff, 0x11, 0x04, 0xfe, 0xff, 0x21, 0x04, 0xff, 0xff, 0x21,
  0x04, 0xff, 0xff, 0x21, 0x02, 0xff, 0xff, 0x40, 0x02, 0xff, 0xff, 0x41,
  0x02, 0x1e, 0xfe, 0x41, 0x02, 0x00, 0xfe, 0x45, 0x02, 0x00, 0xfc, 0x41,
  0x02, 0x00, 0xf8, 0x41, 0x04, 0x00, 0xf8, 0x21, 0x04, 0x00, 0xf8, 0x21,
  0x64, 0x00, 0xf0, 0x20, 0xe8, 0x00, 0x60, 0x10, 0xe8, 0x00, 0x00, 0x10,
  0xf0, 0x00, 0x00, 0x08, 0xe0, 0x00, 0x00, 0x04, 0x40, 0x00, 0x00, 0x02,
  0x80, 0x00, 0x00, 0x01, 0x00, 0xc3, 0xc3, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn2_width 32
#define turn2_height 32
static char turn2_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0xbc, 0x38, 0x00,
  0x00, 0xff, 0xc3, 0x00, 0x80, 0xff, 0x07, 0x01, 0xc0, 0xff, 0x03, 0x02,
  0xa0, 0xff, 0x07, 0x04, 0x10, 0xff, 0x04, 0x08, 0x08, 0xff, 0x00, 0x10,
  0x08, 0xfe, 0x87, 0x1f, 0x04, 0xe4, 0xcf, 0x2f, 0x04, 0x40, 0xe8, 0x3f,
  0x04, 0x00, 0xc0, 0x3f, 0x02, 0x00, 0x80, 0x7f, 0x02, 0x00, 0xc0, 0x7f,
  0x02, 0x00, 0xc0, 0x7f, 0x02, 0x00, 0x00, 0x7f, 0x02, 0x00, 0x00, 0x7e,
  0x02, 0x00, 0x00, 0x7c, 0x04, 0x00, 0x00, 0x3c, 0x04, 0x00, 0x00, 0x2c,
  0x04, 0x00, 0x00, 0x2c, 0x08, 0x00, 0x00, 0x16, 0x08, 0x00, 0x00, 0x16,
  0x10, 0x00, 0x00, 0x08, 0x20, 0x00, 0x00, 0x06, 0x40, 0x00, 0x00, 0x02,
  0x80, 0x00, 0x00, 0x01, 0x00, 0x03, 0xc0, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn20_width 32
#define turn20_height 32
static char turn20_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xf3, 0xff, 0x00, 0x80, 0xf0, 0xf9, 0x01, 0x40, 0x20, 0xf8, 0x03,
  0x20, 0xf8, 0xff, 0x07, 0x10, 0xf0, 0xff, 0x0b, 0x08, 0xf0, 0xff, 0x1f,
  0x08, 0xf0, 0xff, 0x1f, 0x04, 0xf8, 0xff, 0x27, 0x04, 0xf8, 0xff, 0x27,
  0x04, 0xf0, 0xff, 0x27, 0x02, 0xf0, 0xf3, 0x47, 0x02, 0xe0, 0xf0, 0x4f,
  0x02, 0x40, 0xe0, 0x6f, 0x02, 0x00, 0xc0, 0x67, 0x02, 0x00, 0xc0, 0x57,
  0x02, 0x00, 0xc0, 0x4f, 0x04, 0x00, 0x80, 0x27, 0xe4, 0x03, 0x80, 0x27,
  0xe4, 0x03, 0x00, 0x23, 0xe8, 0x03, 0x00, 0x10, 0xc8, 0x07, 0x00, 0x10,
  0xd0, 0x07, 0x00, 0x08, 0xe0, 0x07, 0x00, 0x04, 0xc0, 0x03, 0x00, 0x02,
  0x80, 0x00, 0x80, 0x01, 0x00, 0x07, 0xf0, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn21_width 32
#define turn21_height 32
static char turn21_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x9c, 0x3f, 0x00,
  0x00, 0x83, 0xff, 0x00, 0x80, 0x80, 0xe0, 0x01, 0x40, 0xc0, 0xff, 0x03,
  0x20, 0x80, 0xff, 0x07, 0x30, 0x80, 0xff, 0x0f, 0x18, 0x80, 0xff, 0x1f,
  0x08, 0x80, 0xff, 0x1f, 0x0c, 0x80, 0xff, 0x3f, 0x0c, 0x80, 0x3f, 0x3e,
  0x04, 0x00, 0x0c, 0x3e, 0x02, 0x00, 0x00, 0x7f, 0x02, 0x00, 0x00, 0x7e,
  0x02, 0x00, 0x00, 0x7e, 0x06, 0x00, 0x00, 0x5e, 0x02, 0x00, 0x00, 0x5e,
  0xf2, 0x00, 0x00, 0x5c, 0xf4, 0x3f, 0x00, 0x3c, 0xf4, 0x1f, 0x00, 0x28,
  0xf4, 0x1f, 0x00, 0x20, 0xf8, 0x3f, 0x00, 0x10, 0xe8, 0x3f, 0x00, 0x10,
  0xd0, 0x1f, 0x00, 0x08, 0xa0, 0x1f, 0x00, 0x04, 0x40, 0x1f, 0x00, 0x02,
  0x80, 0x3e, 0x00, 0x01, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x3c, 0x3c, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn22_width 32
#define turn22_height 32
static char turn22_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x1c, 0x3e, 0x00,
  0x00, 0x03, 0xc0, 0x00, 0x80, 0x00, 0xfe, 0x01, 0xc0, 0x00, 0xfc, 0x03,
  0x60, 0x00, 0xfc, 0x07, 0x70, 0x00, 0xfc, 0x0f, 0x38, 0x00, 0xfc, 0x1f,
  0x18, 0x00, 0xf8, 0x1f, 0x1c, 0x00, 0xf8, 0x3e, 0x0c, 0x00, 0x60, 0x3c,
  0x0c, 0x00, 0x00, 0x38, 0x06, 0x00, 0x00, 0x78, 0x02, 0x00, 0x00, 0x78,
  0x06, 0x00, 0x00, 0x78, 0x1a, 0x08, 0x00, 0x78, 0xc2, 0x8f, 0x00, 0x70,
  0xe2, 0xff, 0x01, 0x60, 0xc4, 0xff, 0x01, 0x20, 0xc4, 0xff, 0x01, 0x20,
  0xc4, 0xff, 0x01, 0x20, 0x88, 0xff, 0x01, 0x10, 0x08, 0xff, 0x00, 0x10,
  0x10, 0xfc, 0x00, 0x08, 0x20, 0xf8, 0x00, 0x04, 0x40, 0x78, 0x00, 0x02,
  0x80, 0x70, 0x80, 0x01, 0x00, 0x63, 0xc0, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn23_width 32
#define turn23_height 32
static char turn23_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x1c, 0x3c, 0x00,
  0x00, 0x03, 0xfc, 0x00, 0x80, 0x03, 0xf0, 0x01, 0xc0, 0x01, 0xe0, 0x03,
  0xe0, 0x01, 0xe0, 0x07, 0xf0, 0x00, 0xe0, 0x0f, 0x78, 0x00, 0xc0, 0x1f,
  0x78, 0x00, 0xc0, 0x1f, 0x7c, 0x00, 0x00, 0x38, 0x3c, 0x00, 0x00, 0x30,
  0x1c, 0x00, 0x00, 0x20, 0x0e, 0x00, 0x00, 0x60, 0x1e, 0x00, 0x00, 0x60,
  0x3e, 0x7c, 0x00, 0x60, 0x72, 0xff, 0x1e, 0x60, 0x02, 0xff, 0x0f, 0x60,
  0x02, 0xfe, 0x0f, 0x60, 0x04, 0xff, 0x0f, 0x20, 0x04, 0xff, 0x0f, 0x20,
  0x04, 0xfc, 0x0f, 0x20, 0x08, 0xfc, 0x07, 0x10, 0x08, 0xe0, 0x07, 0x10,
  0x10, 0xe0, 0x07, 0x08, 0x20, 0xc0, 0x03, 0x04, 0x40, 0x80, 0x03, 0x02,
  0x80, 0x80, 0x81, 0x01, 0x00, 0x03, 0xc3, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn24_width 32
#define turn24_height 32
static char turn24_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0x03, 0xd0, 0x00, 0x80, 0x0e, 0xc0, 0x01, 0xc0, 0x07, 0xc0, 0x03,
  0xe0, 0x07, 0x80, 0x07, 0xf0, 0x03, 0x00, 0x0f, 0xf8, 0x01, 0x00, 0x1f,
  0xf8, 0x01, 0x00, 0x1c, 0xfc, 0x00, 0x00, 0x20, 0x7c, 0x00, 0x00, 0x20,
  0x3c, 0x00, 0x00, 0x20, 0x3a, 0x00, 0x00, 0x40, 0x72, 0xf1, 0x47, 0x40,
  0x72, 0xf1, 0xff, 0x40, 0x02, 0xf8, 0x7f, 0x40, 0x02, 0xf0, 0xff, 0x40,
  0x02, 0xf0, 0xff, 0x40, 0x04, 0xf0, 0xff, 0x20, 0x04, 0xc0, 0x7f, 0x20,
  0x04, 0x80, 0x3f, 0x20, 0x08, 0x00, 0x3f, 0x10, 0x08, 0x00, 0x1f, 0x10,
  0x10, 0x00, 0x1e, 0x08, 0x20, 0x00, 0x1e, 0x04, 0x40, 0x00, 0x0e, 0x02,
  0x80, 0x00, 0x0e, 0x01, 0x00, 0x03, 0xc2, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn0_width 32
#define turn0_height 32
static char turn0_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0x3f, 0xc0, 0x00, 0x80, 0x3d, 0x80, 0x01, 0xc0, 0x3f, 0x00, 0x03,
  0xe0, 0x1f, 0x00, 0x06, 0xf0, 0x1f, 0x00, 0x0c, 0xe8, 0x0f, 0x00, 0x10,
  0xf8, 0x07, 0x00, 0x10, 0xf4, 0x01, 0x00, 0x20, 0xf4, 0x01, 0x00, 0x20,
  0xe4, 0x01, 0x7e, 0x20, 0x82, 0x0b, 0xff, 0x43, 0x02, 0x90, 0xff, 0x47,
  0x02, 0x80, 0xff, 0x47, 0x02, 0x80, 0xff, 0x47, 0x02, 0x80, 0xff, 0x47,
  0x02, 0x00, 0xff, 0x43, 0x04, 0x00, 0xfe, 0x23, 0x04, 0x00, 0xf8, 0x21,
  0x04, 0x00, 0xf8, 0x21, 0x08, 0x00, 0xf0, 0x11, 0x08, 0x00, 0xf0, 0x11,
  0x10, 0x00, 0xf0, 0x08, 0x20, 0x00, 0x70, 0x04, 0x40, 0x00, 0x30, 0x02,
  0x80, 0x00, 0x10, 0x01, 0x00, 0x07, 0xc8, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn3_width 32
#define turn3_height 32
static char turn3_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xff, 0xcf, 0x00, 0x80, 0xff, 0x8f, 0x01, 0xc0, 0xfe, 0x0f, 0x02,
  0x20, 0xf8, 0x03, 0x04, 0x10, 0xf0, 0x03, 0x08, 0x08, 0x80, 0x2f, 0x12,
  0x08, 0x00, 0x00, 0x1e, 0x04, 0x00, 0x00, 0x3f, 0x04, 0x00, 0x00, 0x3e,
  0x04, 0x00, 0x00, 0x3e, 0x02, 0x00, 0x00, 0x7c, 0x02, 0x00, 0x00, 0x7c,
  0x02, 0x00, 0x00, 0x78, 0x02, 0x00, 0x00, 0x70, 0x02, 0x00, 0x00, 0x70,
  0x02, 0x00, 0x00, 0x70, 0x04, 0x00, 0x00, 0x30, 0x04, 0x00, 0x00, 0x30,
  0x04, 0x00, 0x00, 0x38, 0x08, 0x00, 0x00, 0x18, 0x08, 0x00, 0x00, 0x18,
  0x10, 0x00, 0x00, 0x08, 0x20, 0x00, 0x00, 0x04, 0x40, 0x00, 0x00, 0x02,
  0x80, 0x00, 0x00, 0x01, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn4_width 32
#define turn4_height 32
static char turn4_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xff, 0xff, 0x00, 0x80, 0xe1, 0x3f, 0x01, 0x40, 0xc0, 0x1f, 0x02,
  0x20, 0x80, 0x1f, 0x04, 0x10, 0x00, 0x78, 0x08, 0x08, 0x00, 0x80, 0x19,
  0x08, 0x00, 0x00, 0x1c, 0x04, 0x00, 0x00, 0x3c, 0x04, 0x00, 0x00, 0x38,
  0x04, 0x00, 0x00, 0x30, 0x02, 0x00, 0x00, 0x70, 0x02, 0x00, 0x00, 0x70,
  0x02, 0x00, 0x00, 0x60, 0x02, 0x00, 0x00, 0x60, 0x02, 0x00, 0x00, 0x60,
  0x02, 0x00, 0x00, 0x60, 0x04, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00, 0x20,
  0x04, 0x00, 0x00, 0x20, 0x08, 0x00, 0x00, 0x10, 0x08, 0x00, 0x00, 0x10,
  0x10, 0x00, 0x00, 0x08, 0x20, 0x00, 0x00, 0x04, 0x40, 0x00, 0x00, 0x02,
  0x80, 0x00, 0x80, 0x01, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn5_width 32
#define turn5_height 32
static char turn5_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xdf, 0xff, 0x00, 0x80, 0x00, 0xff, 0x01, 0x40, 0x00, 0x78, 0x02,
  0x20, 0x00, 0xc0, 0x04, 0x10, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x10,
  0x08, 0x00, 0x00, 0x10, 0x04, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00, 0x20,
  0x04, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x40,
  0x02, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x40,
  0x02, 0x00, 0x00, 0x40, 0x04, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00, 0x20,
  0x04, 0x00, 0x00, 0x20, 0x08, 0x00, 0x00, 0x10, 0x08, 0x00, 0x00, 0x10,
  0x10, 0x00, 0x00, 0x08, 0x20, 0x00, 0x00, 0x04, 0x40, 0x00, 0x00, 0x02,
  0x80, 0x00, 0x80, 0x01, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn6_width 32
#define turn6_height 32
static char turn6_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0x07, 0xfc, 0x00, 0x80, 0x00, 0xf8, 0x01, 0x40, 0x00, 0x80, 0x03,
  0x20, 0x00, 0x00, 0x06, 0x10, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x10,
  0x08, 0x00, 0x00, 0x10, 0x0c, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00, 0x20,
  0x04, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x40,
  0x02, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x40,
  0x02, 0x00, 0x00, 0x40, 0x04, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00, 0x20,
  0x04, 0x00, 0x00, 0x20, 0x48, 0x00, 0x00, 0x10, 0xe8, 0x00, 0x00, 0x10,
  0xf0, 0x01, 0x00, 0x08, 0xe0, 0x07, 0x00, 0x04, 0xc0, 0x0f, 0x00, 0x02,
  0x80, 0x1f, 0x00, 0x01, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn7_width 32
#define turn7_height 32
static char turn7_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x3c, 0x38, 0x00,
  0x00, 0x07, 0xc0, 0x00, 0x80, 0x03, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x02,
  0xe0, 0x00, 0x00, 0x04, 0xf0, 0x00, 0x00, 0x08, 0x78, 0x00, 0x00, 0x10,
  0x38, 0x00, 0x00, 0x10, 0x3c, 0x00, 0x00, 0x20, 0x1c, 0x00, 0x00, 0x20,
  0x1c, 0x00, 0x00, 0x20, 0x0e, 0x00, 0x00, 0x40, 0x0e, 0x00, 0x00, 0x40,
  0x0e, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x40,
  0x02, 0x00, 0x00, 0x40, 0x24, 0x0c, 0x00, 0x20, 0x74, 0x1c, 0x00, 0x20,
  0x34, 0x00, 0x00, 0x20, 0x28, 0x7c, 0x00, 0x10, 0x08, 0xfe, 0x01, 0x10,
  0x10, 0xff, 0x03, 0x08, 0x20, 0xff, 0x03, 0x04, 0x40, 0xfe, 0x01, 0x02,
  0x80, 0x08, 0x00, 0x01, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn8_width 32
#define turn8_height 32
static char turn8_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x3c, 0x38, 0x00,
  0x00, 0x07, 0xc0, 0x00, 0x80, 0x03, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x02,
  0xe0, 0x00, 0x00, 0x04, 0xf0, 0x00, 0x00, 0x08, 0x78, 0x00, 0x00, 0x10,
  0x78, 0x00, 0x00, 0x10, 0x3c, 0x00, 0x00, 0x20, 0x1c, 0x00, 0x00, 0x20,
  0x1c, 0x00, 0x00, 0x20, 0x0e, 0x00, 0x00, 0x40, 0x0e, 0x00, 0x00, 0x40,
  0x0e, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0x40,
  0x02, 0x00, 0x00, 0x40, 0x24, 0x0c, 0x00, 0x20, 0x74, 0x1c, 0x00, 0x20,
  0x34, 0x00, 0x00, 0x20, 0x28, 0x7c, 0x00, 0x10, 0x08, 0xfe, 0x00, 0x10,
  0x10, 0xff, 0x03, 0x08, 0x20, 0xff, 0x03, 0x04, 0x40, 0xfe, 0x01, 0x02,
  0x80, 0x08, 0x00, 0x01, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn9_width 32
#define turn9_height 32
static char turn9_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0x07, 0xc0, 0x00, 0x80, 0x03, 0x00, 0x01, 0xc0, 0x03, 0x00, 0x02,
  0xe0, 0x03, 0x00, 0x04, 0xf0, 0x01, 0x00, 0x08, 0xf8, 0x00, 0x00, 0x10,
  0x78, 0x00, 0x00, 0x10, 0x7c, 0x00, 0x00, 0x20, 0x7c, 0x00, 0x00, 0x20,
  0x7c, 0x00, 0x00, 0x20, 0x3e, 0x00, 0x00, 0x40, 0x1e, 0x00, 0x00, 0x40,
  0x1e, 0x00, 0x00, 0x40, 0x3a, 0x00, 0x00, 0x40, 0x32, 0x00, 0x00, 0x40,
  0x92, 0xe1, 0x00, 0x40, 0x94, 0x01, 0x00, 0x20, 0xa4, 0x00, 0x00, 0x20,
  0x44, 0xa0, 0x03, 0x20, 0x08, 0xf0, 0x0f, 0x10, 0x08, 0xf8, 0x0f, 0x10,
  0x10, 0xf8, 0x0f, 0x08, 0x20, 0xf8, 0x0f, 0x04, 0x40, 0xf0, 0x00, 0x02,
  0x80, 0x00, 0x00, 0x01, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x1c, 0x38, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define turn_inv_width 32
#define turn_inv_height 32
static char turn_inv_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xff, 0xff, 0x00, 0x80, 0xff, 0xff, 0x01, 0xc0, 0xff, 0xff, 0x03,
  0xe0, 0xff, 0xff, 0x07, 0xf0, 0xff, 0xff, 0x0f, 0xf8, 0xff, 0xff, 0x1f,
  0xf8, 0xff, 0xff, 0x1f, 0xfc, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0x3f,
  0xfc, 0xff, 0xff, 0x3f, 0xfe, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0x7f,
  0xfe, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0x7f,
  0xfe, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0xff, 0x3f, 0xfc, 0xff, 0xff, 0x3f,
  0xfc, 0xff, 0xff, 0x3f, 0xf8, 0xff, 0xff, 0x1f, 0xf8, 0xff, 0xff, 0x1f,
  0xf0, 0xff, 0xff, 0x0f, 0xe0, 0xff, 0xff, 0x07, 0xc0, 0xff, 0xff, 0x03,
  0x80, 0xff, 0xff, 0x01, 0x00, 0xff, 0xff, 0x00, 0x00, 0xfc, 0x3f, 0x00,
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, };


void
MakeTurnCursors(Widget widget, Window window)
{
  
  XColor   cursor_foreground, cursor_background, dummy;
  Pixmap   source ,mark;
  Colormap colormap;
  
  if (XtIsRealized(widget))
    colormap = widget->core.colormap;
  else
    colormap = DefaultColormapOfScreen(XtScreen(widget));
  
  (void) XAllocNamedColor
    ( GdDisplay, colormap, "blue", &cursor_foreground, &dummy );
  
  (void) XAllocNamedColor
    ( GdDisplay, colormap, "yellow", &cursor_background, &dummy );
  
  mark = XCreateBitmapFromData( GdDisplay, window,
			       turn_inv_bits,
			       turn_inv_width,
			       turn_inv_height);
/*-----------------------------------------------------------------------*/
#define CREATE_CURSOR(cursor,turn,turn_bits,turn_width,turn_height)       \
    source = XCreateBitmapFromData (                                      \
				    GdDisplay,                            \
				    window,                               \
				    turn_bits,                            \
				    turn_width,                           \
				    turn_height                           \
				    );                                    \
    cursor = XCreatePixmapCursor                                          \
      ( GdDisplay, source, mark,                                          \
        &cursor_background, &cursor_foreground, 0, 0);                    \
    XFreePixmap( GdDisplay, source)                                       \
/*-----------------------------------------------------------------------*/

  CREATE_CURSOR( turn[ 0], turn0, turn0_bits, turn0_width, turn0_height );
  CREATE_CURSOR( turn[ 1], turn1, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[ 2], turn2, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[ 3], turn3, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[ 4], turn4, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[ 5], turn5, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[ 6], turn6, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[ 7], turn7, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[ 8], turn8, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[ 9], turn9, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[10], turn10,turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[11], turn11,turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[12], turn12, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[13], turn13, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[14], turn14, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[15], turn15, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[16], turn16, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[17], turn17, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[18], turn18, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[19], turn19, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[20], turn20, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[21], turn21, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[22], turn22, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[23], turn23, turn1_bits, turn1_width, turn1_height );
  CREATE_CURSOR( turn[24], turn24, turn1_bits, turn1_width, turn1_height );
  
        XFreePixmap( GdDisplay, mark);
}

typedef struct {
  Window window;
  int    next_cursor;
} TurnCursor;

static void 
my_timer( XtPointer client_data, XtIntervalId *id)
{
  Window wait_window = ((TurnCursor*) client_data)->window;
  int *next_cursor   = &((TurnCursor*) client_data)->next_cursor;

  (*next_cursor)++;
  *next_cursor %= TURN_CURSORS;
  XDefineCursor(GdDisplay, wait_window, turn[*next_cursor] ); 

  (void) XtAppAddTimeOut(GxtacApp, 100, my_timer, client_data);

  
}

Window 
CreateWaitCursorWindow( Widget parent)
{
  Window root;
  int xr, yr;
  unsigned int dr, wr, hr, bwr;
  unsigned long valuemask = 0;
  XSetWindowAttributes xswa;
  Window wait_window;
  TurnCursor* turn = (TurnCursor*) XtMalloc(sizeof(TurnCursor));

  
  (void)XGetGeometry( GdDisplay, XtWindow(parent),
		     &root, &xr, &yr, &wr, &hr, &bwr, &dr);

  wait_window = XCreateWindow( GdDisplay, XtWindow(parent),
			      0, 0, wr, hr, 0, 0,
			      InputOnly,CopyFromParent,
			      valuemask, &xswa); 
  XMapRaised( GdDisplay, wait_window);

  MakeTurnCursors( parent,wait_window);
  
  turn->window = wait_window;
  turn->next_cursor = 0;

  (void) XtAppAddTimeOut(GxtacApp, 100, my_timer, (XtPointer) turn); 
  
  return (wait_window);
  
}

XtEventHandler
Configure( Widget w, caddr_t client_data, XEvent *event, Boolean *cont)
{
  Window root;
  int xr, yr;
  unsigned int dr, wr, hr, bwr;
  unsigned long valuemask;
  XWindowChanges xswa;
  Window window = (Window) client_data;

  if (event != NULL && event->type != ConfigureNotify) return;
  
  (void)XGetGeometry( GdDisplay, XtWindow(w),
		     &root, &xr, &yr, &wr, &hr, &bwr, &dr);
  valuemask       = 0;
  xswa.width      = wr;
  valuemask      |= CWWidth;
  xswa.height     = hr;
  valuemask      |= CWHeight;
  xswa.stack_mode = Above;
  valuemask      |= CWStackMode;


  XConfigureWindow( GdDisplay, window, valuemask, &xswa);
  XRaiseWindow( GdDisplay, window);

}


/*ARGSUSED*/
void
AddShellToShellVarArray( Widget shell, caddr_t clientData, caddr_t callData)
{
  Window window;

  XtRealizeWidget( shell);

  VarArrayAdd( shellVarArray, (GENP)&shell);
  window = CreateWaitCursorWindow( shell);
  VarArrayAdd( waitCursorWindow, (GENP)&window);

  XtAddEventHandler( shell, StructureNotifyMask, False,
		    (XtEventHandler)Configure, (caddr_t)window);
  

}


/*ARGSUSED*/
void
DeleteShellFromShellVarArray( Widget shell, caddr_t clientData, caddr_t callData)
{
  int i = iVarArrayPointerToIndex(shellVarArray,(char*)shell);

  XDestroyWindow( GdDisplay, (Window)(PVAI( waitCursorWindow, Window, i)));
  VarArrayDeleteMore( shellVarArray, i, 1);
  VarArrayDeleteMore( waitCursorWindow, i, 1);



}

void
SetWaitCursor( Window window, Cursor cursor)
{
  unsigned long valuemask;
  XSetWindowAttributes xswa;

/*  xswa.cursor = cursor;*/
  xswa.cursor = XCreateFontCursor( GdDisplay, XC_watch);
  valuemask   = CWCursor; 
#if debug_cursor
  printf("SetWaitCursor: \n");
#endif
/*  XChangeWindowAttributes( GdDisplay, window, valuemask, &xswa); */

  XMapRaised( GdDisplay, window);

}


/*ARGSUSED*/
void
SetWaitForAllShell(Widget shell, caddr_t clientData, caddr_t callData)
{
  int n = iVarArrayElementCount(waitCursorWindow);
  int i;

#if debug_cursor
  printf("SetWaitForAllShell: %s\n", XtName(shell));
#endif
  for( i = 0; i < n; i++ )
    SetWaitCursor( *PVAI( waitCursorWindow, Window, i), 
		  XCreateFontCursor( GdDisplay, XC_watch));


}

/*ARGSUSED*/
void
UnSetWaitForAllShell(Widget shell, caddr_t clientData, caddr_t callData)
{
  int n = iVarArrayElementCount(waitCursorWindow);
  int i;

#if debug_cursor
  printf("UnSetWaitForAllShell: %s\n", XtName(shell));
#endif
/*
  for( i = 0; i < n; i++ )
    SetWaitCursor( PVAI( waitCursorWindow, Window, i), None);
    XLowerWindow( GdDisplay, *PVAI( waitCursorWindow, Window, i));

*/

}





