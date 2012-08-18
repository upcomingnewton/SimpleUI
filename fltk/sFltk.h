#ifndef SIMPLE_UI_FLTK_H
#define SIMPLE_UI_FLTK_H
#include "../sXforms.h"
#include "../sCallbackData/sCallbackData.h"
#include <FL/Fl_Widget.H>

// FUNCTIONS DEFINED IN MAIN FILE
void PrintWidgetDimensions(Fl_Widget *w);
void usage(int argc, char ** argv);

// FUNCTIONS FOR PARSING FLTK
struct sCbData * MainFunction(sXformsNode * head, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int sGenerateUIFromTree(sXformsNode * head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
void print_label(Fl_Widget *, const char *);

int sFltkUIHandler_f_Select1Handler(sXformsNode *head, struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int sFltkUIHandler_f_InputHandler(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int sFltkUIHandler_f_TabsHandler(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int sFltkUIHandler_f_RangeHandler(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int sFltkUIHandler_f_TableHandler(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int sFltkUIHandler_f_RadioButtonList(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int sFltkUIHandler_f_CheckBoxList(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int sFltkUIHandler_f_ButtonHandler(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int sFltkUIHandler_f_FrameHandler(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int  sFltkUIHandler_f_ListItems(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int sFltkUIHandler_f_LabelHandler(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );

// FUNCTIONS DEFINED IN CALL BACK FILE

void CallBackFunction(Fl_Widget *fl, void *Data);
char *GetWidgetValue(Fl_Widget *widget, char *type);
void UpdateUI(char *ref, char *data, struct sCbData *list,Fl_Widget *widget);
void UpdateWidgetValue(char *type,char *val,Fl_Widget *widget);
Fl_Widget *findWidgetByName(Fl_Widget *par, char *name);
void callback_done( Fl_Widget * w, void *CallBackData );



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



// DATA STRUCTURES FOR PARSING FLTK


typedef int  (*sFltkUIHandler_f) (
	sXformsNode * head,
	struct sCbData **CallBackData,
	xmlDoc *modelPtr,
	CallBackInterfaceFunction func 
);

struct sFltkUIHandler_s {
  char *type;
  char *name;
  char *attrname;
  char *attrvalue;
  int strict; // if 1 , then it means it cannot be used a generic handler
  sFltkUIHandler_f        handler;
};




sXformsNodeAttr * getAttrFromList(sXformsNode *node,char *name);



void Select1Handler(Fl_Widget *widget, void *data);
void PrintGroupDetails(Fl_Widget *p);
int CalculateTreeChildre(sXformsNode *head);
// FUNCTIONS DEFINED IN FLTK PROCESS FILE
int process(char *input_xml_file, char *output_xml_file,CallBackInterfaceFunction cb);

#endif
