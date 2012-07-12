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
	// get the value of the combo box seleted part
	//int p = gtk_combo_box_get_active( combobox );
	char *txt = gtk_combo_box_get_active_id( combobox );
	//fprintf(stdout,"\n [%s] value is [currently selected index] %d",__func__,p);
	fprintf(stdout,"\n [%s] value is [currently selected index] %s",__func__,txt);
	return s_dupstr("text");
}

char * sGetValueOfRadioButton(GtkWidget *widget)
{
	// TODO find the group, and then selected radio button
	GSList *temp = gtk_radio_button_get_group((GtkRadioButton *)(widget));
	GtkToggleButton *radio_btn;
	while( temp )
	{
		radio_btn = (GtkToggleButton *)temp->data;
		if ((gtk_toggle_button_get_active (radio_btn)) == TRUE )
		{
			// get the widget's details'
			char *text = gtk_button_get_label((GtkButton *)radio_btn);
			fprintf(stdout,"\n [%s] value is %s",__func__,text);
			return s_dupstr(text);
		}
		temp = temp->next;
	}
	return "null";
}

char * sGetValueOfCheckButton(GtkWidget *widget)
{
	// TODO find the value
}
