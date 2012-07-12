#include "sGtk.h"
#include "../misc/misc.h"
#include <string.h>
#include <gtk/gtk.h>

char * getGtkWidgetValue(char *type, GtkWidget *widget)
{
	if(!strcmp(type,"GtkEntry")) return  sGetValueOfTextBox(widget);
	else if(!strcmp(type,"GtkComboBox")) return  sGetValueOfComboBox(widget);
	else if(!strcmp(type,"GtkRadioButton")) return  sGetValueOfRadioButton(widget);
	else if(!strcmp(type,"GtkCheckButton")) return  sGetValueOfCheckButton(widget);
	else return (char *)0;
}

char * sGetValueOfTextBox(GtkWidget *widget)
{
	GtkEntry *entry = (GtkEntry *)widget;
	char *text = gtk_entry_get_text(entry);
	fprintf(stdout,"\n [%s] value is %s",__func__,text);
	return s_dupstr(text);
}

char * sGetValueOfComboBox(GtkWidget *widget)
{
	GtkEntry *combobox = (GtkComboBox *)widget;
	//TODO get the value of the combo box seleted part
	char *text = "text";
	fprintf(stdout,"\n [%s] value is %s",__func__,text);
	return s_dupstr(text);
}

char * sGetValueOfRadioButton(GtkWidget *widget)
{
	// TODO find the group, and then selected radio button
}

char * sGetValueOfCheckButton(GtkWidget *widget)
{
	// TODO find the value
}
