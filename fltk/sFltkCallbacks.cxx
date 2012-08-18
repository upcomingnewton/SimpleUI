#include "sFltk.h"
#include "../simpleUI.h"
#include "../sXforms.h"
#include "../sCallbackData/sCallbackData.h"
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Menu_.H>
#include <FL/Fl_Valuator.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input_.H>
#include <FL/Fl_Output.H>
#include "../misc/misc.h"

#ifdef EnableLog
#define WriteLog fprintf
#else
#define WriteLog
#endif

void CallBackFunction(Fl_Widget *fl, void *Data)
{
  struct sCbData *data = (struct sCbData *)Data;
  for(struct sCbData *temp = data; temp ;temp = temp->next )
  {
    if (!strcmp(temp->name,fl->label()))
    {
      char *newvalue = GetWidgetValue(fl, temp->meta_info);
      if( strcmp(temp->ref,"0")){
        UpdateModelandCallUserFunction(temp->ref,newvalue,data);
        UpdateUI(temp->ref,newvalue,data,fl);
      }
      if(temp->nextref){
			struct sCbData *temp2 = temp->nextref;
				while(temp2 != 0)
				{
          Fl_Widget *t = findWidgetByName(fl,temp2->name);
          char *newvalue2 = GetWidgetValue(t, temp->meta_info);
          if( strcmp(temp2->ref,"0")){
            UpdateModelandCallUserFunction(temp->ref,newvalue2,data);
            UpdateUI(temp->ref,newvalue,data,t);
          }
					temp2 = temp2->next;
				}
			} 
			break;
		}
  }
  //print_user_data(data);
}

void UpdateUI(char *ref, char *data, struct sCbData *list,Fl_Widget *widget)
{
  if(strcmp(ref,"0")){
    for( struct sCbData *temp = list ; temp ; temp =temp->next )
    {
      if(!strcmp(temp->ref,ref))
      {
        Fl_Widget *target = findWidgetByName(widget->window(),temp->name);
        if( target != 0 )
        {
          UpdateWidgetValue(temp->meta_info,temp->value,target);
        }
      }
      if( temp->nextref )
      {
          for( struct sCbData *temp2 = temp->nextref ; temp2 ; temp2 =temp2->next )
          {
                if(!strcmp(temp2->ref,ref))
                {
                  Fl_Widget *target = findWidgetByName(widget->window(),temp2->name);
                  if( target != 0 )
                  {
                    UpdateWidgetValue(temp2->meta_info,temp2->value,target);
                  }
                }
          }
      }
    }
  }
}

Fl_Widget *findWidgetByName(Fl_Widget *par, char *name)
{
  Fl_Group *p = par->as_group();
  if(p)
  {
    for( int i = 0; i < p->children(); i++ )
    {
      Fl_Widget *child = p->child(i);
      if(!strcmp(name,child->label()))
      {
        return child;
      }
      else
      {
        Fl_Widget *temp;
        temp = findWidgetByName(child,name);
        if(temp != 0)
        {
          return temp;
        }
      }
    }
  }
  else
  {
    return (Fl_Widget *)0;
  }
}

char *GetWidgetValue(Fl_Widget *widget, char *type)
{
  char *val = 0;
  if( !strcmp(type,"Fl_Choice"))
  {
    Fl_Choice *dd = (Fl_Choice *)widget;
    Fl_Menu_ *menu = (Fl_Menu_ *)widget;
    val = (char *)malloc(sizeof(char)*(1+strlen(menu->text())));
    val = strcpy(val,menu->text());
    fprintf(stdout,"\n [DropDownMenu][%s] %d %s",dd->label(),dd->value(),val);
  }
  else if( !strcmp(type,"Fl_Input"))
  {
    Fl_Input_ *input = (Fl_Input_ *)widget;
    val = (char *)malloc(sizeof(char)*(1+strlen(input->value())));
    val = strcpy(val,input->value());
    fprintf(stdout,"\n [Input][%s] %s",input->label(),val);
  }
  else if( !strcmp(type,"Fl_Check_Button"))
  {
    Fl_Button *btn = (Fl_Button *)widget;
    if( btn->value() == 0) val = "0";
    else val = "1";
    fprintf(stdout,"\n [CheckButton][%s] %d",btn->label(),val);
  }
  else if( !strcmp(type,"Fl_Round_Button"))
  {
    Fl_Button *btn = (Fl_Button *)widget;
    val = (char *)malloc(sizeof(char)*(1+strlen(btn->label())));
    if( btn->value() == 1) val = strcpy(val,btn->label());
    fprintf(stdout,"\n [RadioButton][%s] %d",btn->label(),val);
  }
  else if( !strcmp(type,"Fl_Value_Slider"))
  {
    Fl_Valuator *slider = (Fl_Valuator *)widget;
    val = (char *)malloc(sizeof(char)*7);
    sprintf(val,"%3.3f",slider->value());
    fprintf(stdout,"\n [Slider][%s] %.2f",slider->label(),val);
  }
  return val;
}

void UpdateWidgetValue(char *type,char *val,Fl_Widget *widget)
{
  if( !strcmp(type,"Fl_Output"))
  {
    Fl_Output *output = (Fl_Output *)widget;
    printf("[Update-Widget][Fl_Output] %s, %s",output->label(),val);
    output->value(val);
  }
}

void callback_done( Fl_Widget * w, void *CallBackData )
{
  struct sCbData *data = (struct sCbData *)CallBackData;
  //print_user_data(data);
  UpdateModel(data);
  w->window()->hide();
}
