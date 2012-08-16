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


struct cb_data
{
	char *ref;
	char *initial_val;
	char *val;
};

typedef struct cb_data CallbackData;

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

#define VER_SEP 0
#define HOR_SEP 0
#define H_SPACING 5
#define V_SPACING 10
#define ROW_HEIGHT 25
#define BOX_WIDTH 250
#define SELECT_WIDTH 176
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 680
#define TAB_HEIGHT 25
#define BUTTON_WIDTH 80
#define LABEL_WIDTH  200
#define WIDGET_WIDTH(w)  (w- (2*H_SPACING +  LABEL_WIDTH))



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

sXformsNodeAttr * getAttrFromList(sXformsNode *node,char *name);


void Select1Handler(Fl_Widget *widget, void *data);
void PrintGroupDetails(Fl_Widget *p);
int CalculateTreeChildre(sXformsNode *head);
#endif
