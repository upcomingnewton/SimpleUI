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


struct FltkCallbackData{
    char *ref;
    char *init_val;
    char *value;
    char *name;
    char *meta_info;
    struct FltkCallbackData *next;
    struct FltkCallbackData *prev;
    struct FltkCallbackData *nextref;
};

int UpdateModel(struct FltkCallbackData * head);

struct FltkCallbackData * AllocateMemoryForFltkCBNode();
struct FltkCallbackData * AppendNode(struct FltkCallbackData **head,char *ref_, char *init_val_,char *value_,char *name_,char *meta_info_);
struct FltkCallbackData * MakeDummy();
struct FltkCallbackData *get_pointer_to_user_data_by_name(const char *_name, struct FltkCallbackData *head);
void print_user_data(struct FltkCallbackData *head);


void CallBackFunction(Fl_Widget *fl, void *Data);
char *GetWidgetValue(Fl_Widget *widget, char *type);
Fl_Widget *getWidgetByName(Fl_Widget *present_widget, char *name);
Fl_Widget *find(Fl_Widget *p, char *name);
void UpdateCallbackData(char *ref, char *data, struct FltkCallbackData *list,Fl_Widget *widget);
void UpdateWidgetValue(char *type,char *val,Fl_Widget *widget);
Fl_Widget *findWidgetByName(Fl_Widget *par, char *name);

typedef int  (*sFltkUIHandler_f) (
	sXformsNode * head,
	struct FltkCallbackData **CallBackData
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


struct FltkCallbackData * MainFunction(sXformsNode * head);
int sGenerateUIFromTree(sXformsNode * head,struct FltkCallbackData **CallBackData);
void print_label(Fl_Widget *, const char *);

int sFltkUIHandler_f_Select1Handler(sXformsNode *head, struct FltkCallbackData **CallBackData);
int sFltkUIHandler_f_InputHandler(sXformsNode *head,struct FltkCallbackData **CallBackData);
int sFltkUIHandler_f_TabsHandler(sXformsNode *head,struct FltkCallbackData **CallBackData);
int sFltkUIHandler_f_RangeHandler(sXformsNode *head,struct FltkCallbackData **CallBackData);
int sFltkUIHandler_f_TableHandler(sXformsNode *head,struct FltkCallbackData **CallBackData);
int sFltkUIHandler_f_RadioButtonList(sXformsNode *head,struct FltkCallbackData **CallBackData);
int sFltkUIHandler_f_CheckBoxList(sXformsNode *head,struct FltkCallbackData **CallBackData);
int sFltkUIHandler_f_ButtonHandler(sXformsNode *head,struct FltkCallbackData **CallBackData);
int sFltkUIHandler_f_FrameHandler(sXformsNode *head,struct FltkCallbackData **CallBackData);
int  sFltkUIHandler_f_ListItems(sXformsNode *head,struct FltkCallbackData **CallBackData);
int sFltkUIHandler_f_LabelHandler(sXformsNode *head,struct FltkCallbackData **CallBackData);
void PrintWidgetDimensions(Fl_Widget *w);

sXformsNodeAttr * getAttrFromList(sXformsNode *node,char *name);


void Select1Handler(Fl_Widget *widget, void *data);
void PrintGroupDetails(Fl_Widget *p);
int CalculateTreeChildre(sXformsNode *head);
#endif
