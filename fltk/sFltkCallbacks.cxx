#include "sFltk.h"
#include "../simpleUI.h"
#include "../sXforms.h"
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
  struct FltkCallbackData *data = (struct FltkCallbackData *)Data;
  //Fl_Choice *dd = (Fl_Choice *)fl;
  //printf("\n CALLBACK = %s",fl->label());
  //print_user_data(data);
  
  /*
  1. find widget in list and it's type and send it to getvalue to get value of this widget
  */
  for(struct FltkCallbackData *temp = data; temp ;temp = temp->next )
  {
    if (!strcmp(temp->name,fl->label()))
    {
      UpdateCallbackData(temp->ref,GetWidgetValue(fl, temp->meta_info),data,fl);
      // TODO UpdateUI(data,temp);
      //      UpdateModel(temp->ref,temp->value);
      if(temp->nextref){
			struct FltkCallbackData *temp2 = temp->nextref;
				while(temp2 != 0)
				{
          // find top level element
          //printf("\n callback %s", temp2->name);
          Fl_Widget *t = getWidgetByName(fl,temp2->name);
          // then find this widget ( temp2->name )
          // then call 
          UpdateCallbackData(temp2->ref,GetWidgetValue(t, temp2->meta_info),data,t);
          // TODO UpdateUI(data,temp2);
          //      UpdateModel(temp->ref,temp->value);
					temp2 = temp2->next;
				}
			} 
			break;
		}
      
  }
  print_user_data(data);
}

void UpdateCallbackData(char *ref, char *data, struct FltkCallbackData *list,Fl_Widget *widget)
{
  if(strcmp(ref,"0")){
    for( struct FltkCallbackData *temp = list ; temp ; temp =temp->next )
    {
      if(!strcmp(temp->ref,ref))
      {
        temp->value = data;
        Fl_Widget *target = findWidgetByName(widget->window(),temp->name);
        if( target != 0 )
        {
          UpdateWidgetValue(temp->meta_info,temp->value,target);
        }
      }
      if( temp->nextref )
      {
          for( struct FltkCallbackData *temp2 = temp->nextref ; temp2 ; temp2 =temp2->next )
          {
                if(!strcmp(temp2->ref,ref))
                {
                  temp2->value = data;
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

Fl_Widget *getWidgetByName(Fl_Widget *present_widget, char *name)
{
  Fl_Widget *temp = (Fl_Widget *)0;
  Fl_Group *p = present_widget->parent();
  if( p->as_group())
  {
    if( (temp = find(p,name)) != 0)
      return temp;
    else{
      Fl_Group *p2 = p->parent();
      return getWidgetByName(p2,name);
      }
  }
  else
    return getWidgetByName(p->parent(),name);
}

Fl_Widget *find(Fl_Widget *p, char *name)
{
  Fl_Group *t = p->as_group();
  if( t )
  {
    for( int i = 0; i < t->children(); i++ )
    {
      Fl_Widget *child = t->child(i);
      if( !strcmp(name,child->label()))
      {
        return child;
      }
      else
      {
        if( child->as_group() ){
          Fl_Widget *t;
          if ( ( t == find(child,name))!= 0)
          {
              return t;
          }
        }
      }
    }
  }
  return (Fl_Widget *)0;
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
