#include "sGtk.h"
#include "sGtkRenderers/sGtkRenderer.h"
#include <gtk/gtk.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

/*
  Compile with:
    gcc -o  sGtk -g -Wall gtk/sGtk.c gtk/sGtk.h gtk/sGtkRenderers/sGtkParseTree.c  gtk/sGtkRenderers/sGtkRenderer.h  misc/misc.h  misc/string_func.c `(pkg-config --cflags --libs gtk+-3.0)` `xml2-config --cflags --libs` -export-dynamic
 */



#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
int main( int  argc,char **argv )
{
    GtkBuilder *builder;
    GtkWidget  *window;
    GError     *error = NULL;

    gtk_init( &argc, &argv );

    builder = gtk_builder_new();
    sGenerateGladeFile();
    if( ! gtk_builder_add_from_file( builder, sGTK_UI_FILE, &error ) )
    {
        g_warning( "%s", error->message );
        g_free( error );
        return( 1 );
    }

     //Get main window pointer from UI 
    window = GTK_WIDGET( gtk_builder_get_object( builder, sGTK_GLADE_MAIN_WINDOW_NAME) );
    //struct gtk_cb_data *head = MakeDummy();
    //gtk_builder_connect_signals( builder, head );
    g_object_unref( G_OBJECT( builder ) );
    gtk_widget_show( window );
    gtk_main();
    fprintf(stdout,"\n");
    return( 0 );
}
#else
    int main(int argc, char **argv)
    {
        fprintf(stderr,"\n ERROR. LIB-XML IS NOT PROPERLY COMPILED");
        exit(1);
    }
#endif




