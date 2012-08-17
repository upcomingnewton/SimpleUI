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

#ifdef EnableLog
#define WriteLog fprintf
#else
#define WriteLog
#endif

void CallBackFunction(Fl_Widget *fl, void *Data)
{
  struct FltkCallbackData *data = (struct FltkCallbackData *)Data;
  //Fl_Choice *dd = (Fl_Choice *)fl;
  //printf("\n CALLBACK = %d",dd->value());
  //print_user_data(data);
  
  /*
  1. find widget in list and it's type and send it to getvalue to get value of this widget
  */
  for(struct FltkCallbackData *temp = data; temp ;temp = temp->next )
  {
    if (!strcmp(temp->name,fl->label()))
    {
      GetWidgetValue(fl, temp->meta_info);
      
      if(temp->nextref){
			struct FltkCallbackData *temp2 = temp->nextref;
				while(temp2 != 0)
				{
          // find top level element
          Fl_Widget *t = getWidgetByName(fl,temp2->name);
          // then find this widget ( temp2->name )
          // then call 
          GetWidgetValue(t, temp2->meta_info);
					temp2 = temp2->next;
				}
			} 
			break;
		}
      
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
  if( !strcmp(type,"Fl_Choice"))
  {
    Fl_Choice *dd = (Fl_Choice *)widget;
    Fl_Menu_ *menu = (Fl_Menu_ *)widget;
    fprintf(stdout,"\n [DropDownMenu][%s] %d %s",dd->label(),dd->value(),menu->text());
  }
  else if( !strcmp(type,"Fl_Input"))
  {
    Fl_Input_ *input = (Fl_Input_ *)widget;
    fprintf(stdout,"\n [Input][%s] %s",input->label(),input->value());
  }
  else if( !strcmp(type,"Fl_Check_Button"))
  {
    Fl_Button *btn = (Fl_Button *)widget;
    fprintf(stdout,"\n [CheckButton][%s] %d",btn->label(),btn->value());
  }
  else if( !strcmp(type,"Fl_Round_Button"))
  {
    Fl_Button *btn = (Fl_Button *)widget;
    fprintf(stdout,"\n [RadioButton][%s] %d",btn->label(),btn->value());
  }
  else if( !strcmp(type,"Fl_Value_Slider"))
  {
    Fl_Valuator *slider = (Fl_Valuator *)widget;
    fprintf(stdout,"\n [Slider][%s] %.2f",slider->label(),slider->value());
  }
  return "ok";
}
