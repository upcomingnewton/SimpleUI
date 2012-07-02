#include "sGtk.h"

/*
 * Compile with:
 *   gcc -o  sGtk gtk/sGtk.c gtk/sGtk.h gtk/sGtkCallbacks.c `(pkg-config --cflags --libs gtk+-3.0)`
 */

#include <gtk/gtk.h>



void 
on_window_destroy  (GtkWidget *widget,GdkEvent  *event, gpointer   user_data) 
{
	fprintf(stdout,"\n destroy event called");
    gtk_main_quit ();
}

int main( int    argc,char **argv )
{
    GtkBuilder *builder;
    GtkWidget  *window;
    GError     *error = NULL;

    gtk_init( &argc, &argv );

    builder = gtk_builder_new();
    if( ! gtk_builder_add_from_file( builder, sGTK_UI_FILE, &error ) )
    {
        g_warning( "%s", error->message );
        g_free( error );
        return( 1 );
    }

    /* Get main window pointer from UI */
    window = GTK_WIDGET( gtk_builder_get_object( builder, "Window_SampleUI" ) );

    gtk_builder_connect_signals( builder, NULL );

    g_object_unref( G_OBJECT( builder ) );

    gtk_widget_show( window );

    gtk_main();

    return( 0 );
}
