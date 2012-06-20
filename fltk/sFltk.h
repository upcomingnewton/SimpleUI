#ifndef SIMPLE_UI_FLTK_H
#define SIMPLE_UI_FLTK_H
#include "../sXforms.h"
#include <FL/Fl_Widget.H>

struct sFltkDimensions{
	int x;
	int y;
	int w;
	int h;
};

typedef int  (*sFltkUIHandler_f) (
	sXformsNode * head,
	int x, 
	int y,
	int w, 
	int h
);



struct sFltkUIHandler_s {
  char *type;
  char *name;
  char *attrname;
  char *attrvalue;
  int strict; // if 1 , then it means it cannot be used a generic handler
  sFltkUIHandler_f        handler;
};

#define VER_SEP 4
#define HOR_SEP 5
#define H_SPACING 10
#define V_SPACING 5
#define ROW_HEIGHT 25
#define BOX_WIDTH 250
#define SELECT_WIDTH 176
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 680
#define TAB_HEIGHT 25
#define BUTTON_WIDTH 80


int sGenerateUIFromTree(sXformsNode * head);
void print_label(Fl_Widget *, const char *);

int sFltkUIHandler_f_Select1Handler(sXformsNode *head, int x, int y, int w, int h);
int sFltkUIHandler_f_InputHandler(sXformsNode *head,int x, int y, int w, int h);
int sFltkUIHandler_f_TabsHandler(sXformsNode *head,int x, int y, int w, int h);
int sFltkUIHandler_f_RangeHandler(sXformsNode *head,int x, int y, int w, int h);
int sFltkUIHandler_f_TableHandler(sXformsNode *head,int x, int y, int w, int h);
int sFltkUIHandler_f_RadioButtonList(sXformsNode *head,int x, int y, int w, int h);
int sFltkUIHandler_f_CheckBoxList(sXformsNode *head,int x, int y, int w, int h);
int sFltkUIHandler_f_ButtonHandler(sXformsNode *head,int x, int y, int w, int h);
int sFltkUIHandler_f_FrameHandler(sXformsNode *head,int x, int y, int w, int h);
int  sFltkUIHandler_f_ListItems(sXformsNode *head,int x, int y, int w, int h);
int sFltkUIHandler_f_LabelHandler(sXformsNode *head,int x, int y, int w, int h);
void PrintWidgetDimensions(Fl_Widget *w);
#endif
