#include "sGtk.h"

/*
  Compile with:
    gcc -o  sGtk -g -Wall gtk/sGtk.c gtk/sGtk.h gtk/sGtkCallbacks.c gtk/sGtkCallbackFunctions.c gtk/sGtkCallbackValues.c  misc/misc.h  misc/string_func.c `(pkg-config --cflags --libs gtk+-3.0)` -export-dynamic
 */

#include <gtk/gtk.h>





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

     //Get main window pointer from UI 
    window = GTK_WIDGET( gtk_builder_get_object( builder, "Window_SampleUI" ) );
    struct gtk_cb_data *head = MakeDummy();
    gtk_builder_connect_signals( builder, head );

    g_object_unref( G_OBJECT( builder ) );

    gtk_widget_show( window );

    gtk_main();
fprintf(stdout,"\n");
    return( 0 );
}
