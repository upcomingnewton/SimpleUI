#include "sFltk.h"
#include "../simpleUI.h"
#include "../sXforms.h"
#include "../xml/sXml.h"
#include "../io/io.h"
#include "../sXforms.h"
#include "../misc/misc.h"
	#include <FL/Fl.H>
	#include <FL/Fl_Button.H>
	#include <FL/Fl_Double_Window.H>
	#include <FL/Fl_Pack.H>
	#include <FL/Fl_Scroll.H>
	#include <FL/Fl_Text_Display.H>
	#include <FL/Fl_Help_View.H>
	#include "../sCallbackData/sCallbackData.h"

//fltk/sFltkCallbacks_Helper.cxx

/* compilation
g++  -g -I/usr/local/include -I/usr/include/freetype2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT -o 'SimpleUIFltk' fltk/sFltkProcess.cxx fltk/sFltk.h fltk/sFltkWidgets.cxx  fltk/sFltkCallbacks.cxx    sCallbackData/sCallbackData.h  sCallbackData/sCallbackData.c  io/io.h io/io.c xml/sXml.h xml/sParseXforms.c misc/misc.h misc/string_func.c sXforms.h sXforms.c simpleUI.h -lXext -lXft -lfontconfig -lXinerama -lpthread -ldl -lm -lX11 `xml2-config --cflags --libs` `fltk-config --cflags --libs`
 */


int process(char *input_xml_file, char *output_xml_file,CallBackInterfaceFunction cb)
{
  	const char *wrong_arg = 0;
	 char *xforms_text = 0;
	 sXformsNode *head;
	 xmlDoc *modelDocPtr;
	 struct sCbData *CallBackData;
	  int error = 0;
	  
	  if(input_xml_file)
	  {
	    xforms_text =  sReadFileToMem(input_xml_file);
	    if( xforms_text  == 0)
	    {
	      printf("\n ERROR ");
	      return -1;
	    }
	  }
	  Fl::scheme("gtk+");
    Fl_Double_Window * w = new Fl_Double_Window(WINDOW_WIDTH,WINDOW_HEIGHT,("XFORMS in FLTK"));
    Fl_Scroll * scroll = new Fl_Scroll( H_SPACING,V_SPACING,WINDOW_WIDTH-2*H_SPACING,WINDOW_HEIGHT-(5*V_SPACING + ROW_HEIGHT),"" );
	  scroll->box( FL_NO_BOX );
	  {
		  Fl_Pack *scroll_pack = new Fl_Pack(scroll->x(),scroll->y(),scroll->w(),WINDOW_HEIGHT,"scroll_pack"); //TODO height of this widget
		  scroll_pack->spacing(V_SPACING);
		  {
			  head = ParseXformsToTree( xforms_text,&modelDocPtr);
			  if( cb == 0)
			  CallBackData = MainFunction(head,modelDocPtr,&DummyIfFunction);
			  else
			  CallBackData = MainFunction(head,modelDocPtr,cb);
		  }
		  scroll_pack->end();
    }
	  scroll->end();
    Fl_Group *BottomPaneGroup = new Fl_Group(H_SPACING,scroll->h() + 3*V_SPACING,WINDOW_WIDTH - 2*H_SPACING,ROW_HEIGHT+3*V_SPACING ,"");
	  {
		   Fl_Button * done_button = new Fl_Button( (BottomPaneGroup->w() - BUTTON_WIDTH)/2, BottomPaneGroup->y() + V_SPACING, BUTTON_WIDTH, ROW_HEIGHT + V_SPACING, ("&Done"));
		   done_button->callback( callback_done, CallBackData );
	  }
	  BottomPaneGroup->end();
	
	w->resizable( scroll );
	w->end();
  w->show();
    Fl::run();
  if(output_xml_file)
  {
      FILE *fp = fopen(output_xml_file,"w");
      if( fp != NULL )
      xmlDocDump(fp, modelDocPtr);
      fclose(fp);
  }
  return 0;
}
