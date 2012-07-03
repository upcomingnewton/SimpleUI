#include <gtk/gtk.h>
#include "sGtk.h"

/*void */
/*on_window_destroy (GtkWidget *widget, gpointer user_data)*/
/*{*/
/*	fprintf(stdout,"\n destroy event called");*/
/*    gtk_main_quit ();*/
/*}*/
gboolean 
on_window_destroy  (GtkWidget *widget,GdkEvent  *event, gpointer   user_data) 
{
	fprintf(stdout,"\n destroy event called");
    gtk_main_quit ();
}

void on_btn_personal_info_clicked(GtkButton *button, gpointer user_data)
{
	fprintf(stdout,"\nclicked !");
}

void on_btn_clicked(GtkButton *btn , gpointer user_data)
{
	fprintf(stdout,"\n Button clicked %s", gtk_buildable_get_name (GTK_BUILDABLE (btn)));
	GtkWidgetPath *  gpath =    gtk_widget_get_path (btn);
	char * g_path_str  = gtk_widget_path_to_string (gpath);
	fprintf(stdout,"\n path is : %s",g_path_str);
	GtkWidget *par = gtk_widget_get_toplevel( (GtkWidget *)btn);
	if(gtk_widget_is_toplevel(par))
	{
		fprintf(stdout,"\n par-name is : %s",gtk_buildable_get_name (GTK_BUILDABLE (par)));
	}
}


GtkWidget * SearchWidget(GtkWidget *container, char *search_name){
	if( !strcmp(search_name,gtk_buildable_get_name(GTK_BUILDABLE(container))))
		return container;
	else
	{
		GtkWidget *temp;
		GList *children = 
	}
}
