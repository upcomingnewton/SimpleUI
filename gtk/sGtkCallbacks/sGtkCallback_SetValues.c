#include "../sGtk.h"
#include "sGtkCallbacks.h"
#include "../../misc/misc.h"
#include <string.h>
#include <gtk/gtk.h>

void UpdateWidgetValue(char *type,char *val,GtkWidget *widget)
{ 
  if( !strcmp(type,"GtkEntry"))
  {
    GtkEntry *input = (GtkEntry *)widget;
    gtk_entry_set_text(input,val);
  }
  else if( !strcmp(type,"GtkLabel"))
  {
    GtkLabel *label = (GtkLabel *)widget;
    gtk_label_set_text(label,val);
  }
}
