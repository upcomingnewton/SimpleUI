#include "sGtk.h"
#include "../misc/misc.h"
#include <string.h>
#include <gtk/gtk.h>

char * getGtkWidgetValue(char *type, GtkWidget *widget)
{
	if(!strcmp(type,"GtkEntry")) return  sGetValueOfTextBox(widget);
	else return (char *)0;
}

char * sGetValueOfTextBox(GtkWidget *widget)
{
	GtkEntry *entry = (GtkEntry *)widget;
	char *text = gtk_entry_get_text(entry);
	fprintf(stdout,"\n [%s] value is %s",__func__,text);
	return s_dupstr(text);
}
