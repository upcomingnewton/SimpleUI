#include <string.h>
#include "../simpleUI.h"
#include "../sXforms.h"
#include "../xml/sXml.h"
#include "../io/io.h"
#include "../sXforms.h"
#include "sGtk.h"
#include "sGtkRenderers/sGtkRenderer.h"
#include "../sCallbackData/sCallbackData.h"
#include <gtk/gtk.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

//gtk/sGtkCallbacks/sGtkCallback_HelperFunctions.c
/*
gcc -o sgtk -g -Wall gtk/sGtkProcess.c gtk/sGtk.h gtk/sGtkRenderers/sGtkParseTree.c gtk/sGtkRenderers/sGtkRenderer_Helper.c gtk/sGtkRenderers/sGtkRenderer.h gtk/sGtkCallbacks/sGtkCallbacks.h gtk/sGtkCallbacks/sGtkCallbacks.c sCallbackData/sCallbackData.h  sCallbackData/sCallbackData.c   gtk/sGtkCallbacks/sGtkCallback_GetValues.c  gtk/sGtkCallbacks/sGtkCallback_SetValues.c   misc/misc.h misc/string_func.c io/io.h io/io.c xml/sXml.h xml/sParseXforms.c sXforms.h sXforms.c simpleUI.h `(pkg-config --cflags --libs gtk+-3.0)` `xml2-config --cflags --libs` -export-dynamic
*/

/*
./sgtk -i xforms/file2.xhtml
*/


#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
int process(char *input_xml_file, char *output_xml_file,CallBackInterfaceFunction cb)
{
	fprintf(stdout,"\n===== SIMPLE UI TOOLKIT =====\n\n");
	 const char *wrong_arg = 0;
	 char *xforms_text = 0;
	 sXformsNode *head;
	 struct sCbData *CallBackData;
	 xmlDoc *modelDocPtr;
    GtkBuilder *builder;
    GtkWidget  *window;
    GError     *error = NULL;
   fprintf(stdout,"INPUT FILE = %s\n",input_xml_file);

  if(input_xml_file)
  {
   xforms_text =  sReadFileToMem(input_xml_file);
  }
  else
  {
    return -1;
  }
  head = ParseXformsToTree( xforms_text,&modelDocPtr);
  int argc = 0;
  char **argv = 0;
  gtk_init( &argc, &argv );
  builder = gtk_builder_new();
  if(  cb == 0)
  {
    CallBackData = sGenerateGladeFile(head,modelDocPtr,&DummyIfFunction);
  }
  else
  {
    CallBackData = sGenerateGladeFile(head,modelDocPtr,cb);
  }
  if( ! gtk_builder_add_from_file( builder, sGTK_UI_FILE, &error ) )
    {
        g_warning( "%s", error->message );
        g_free( error );
        return( 1 );
    }
    
     //Get main window pointer from UI 
    window = GTK_WIDGET( gtk_builder_get_object( builder, sGTK_GLADE_MAIN_WINDOW_NAME) );
    // = MakeDummy();
    
    gtk_builder_connect_signals( builder, CallBackData);
    g_object_unref( G_OBJECT( builder ) );
    gtk_widget_show( window );
    gtk_main();
  if(output_xml_file)
  {
      FILE *fp = fopen(output_xml_file,"w");
      if( fp != NULL )
      xmlDocDump(fp, modelDocPtr);
      fclose(fp);
  }
  xmlDocDump(stdout, modelDocPtr);
    fprintf(stdout,"\n");
    return( 0 );
}
#endif


