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
g++  -g -I/usr/local/include -I/usr/include/freetype2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT -o 'SimpleUIFltk' fltk/sFltk.cxx fltk/sFltk.h fltk/sFltkWidgets.cxx  fltk/sFltkCallbacks.cxx    sCallbackData/sCallbackData.h  sCallbackData/sCallbackData.c  io/io.h io/io.c xml/sXml.h xml/sParseXforms.c misc/misc.h misc/string_func.c sXforms.h sXforms.c simpleUI.h -lXext -lXft -lfontconfig -lXinerama -lpthread -ldl -lm -lX11 `xml2-config --cflags --libs` `fltk-config --cflags --libs`
 */
 
/* RUNNING
./SimpleUIFltk -i xforms/file9.xhtml
*/

void PrintWidgetDimensions(Fl_Widget *w){
	fprintf(stdout,"\n[== %s ==], dimensions are %4d,%4d,%4d,%4d",w->label(),w->x(),w->y(),w->w(),w->h());
}

void usage(int argc, char ** argv)
{
	fprintf(stdout,"incorrect usage\n");
}

int main ( int argc , char **argv )
{
	fprintf(stdout,"\n===== SIMPLE UI TOOLKIT =====\n\n");
	 const char *wrong_arg = 0;
	 char *output_model_file = 0;
	 char *xforms_text = 0;
	 char *input_xml_file = 0;
	 sXformsNode *head;
	 struct sCbData *CallBackData;
	 xmlDoc *modelDocPtr;
	int error = 0;
	if(argc)
	{
		#define OY_PARSE_STRING_ARG( opt ) \
                        if( pos + 1 < argc && argv[pos][i+1] == 0 ) \
                        { opt = argv[pos+1]; \
                          if( opt == 0 && strcmp(argv[pos+1],"0") ) \
                            wrong_arg = "-" #opt; \
                          ++pos; \
                          i = 1000; \
                        } else if(argv[pos][i+1] == '=') \
                        { opt = &argv[pos][i+2]; \
                          if( opt == 0 && strcmp(&argv[pos][i+2],"0") ) \
                            wrong_arg = "-" #opt; \
                          i = 1000; \
                        } else wrong_arg = "-" #opt; \
                        
                        
  	if(argc != 1)
  	{
    		int pos = 1, i;
    		while(pos < argc)
    		{
      			switch(argv[pos][0])
      			{
			case '-':
			    for(i = 1; i < (int)strlen(argv[pos]); ++i)
			    switch (argv[pos][i])
			    {
			      case 'o': OY_PARSE_STRING_ARG( output_model_file ); break;
			      case 'i': OY_PARSE_STRING_ARG( input_xml_file ); break;
			      case 'v': break;//oy_debug += 1; break;
			      case 'h': /* only for compatibility with cmd line */ break;
			      case 'l': /* only for compatibility with cmd line */ break;
#if 0
			      case '-':
				        if(strcmp(&argv[pos][2],"verbose") == 0)
				        { 
						//oy_debug += 1; 
						i=100; 
						break;
				        }
				        STRING_ADD( t, &argv[pos][2] );
				        text = oyStrrchr_(t, '=');
				        /* get the key only */
				        if(text)
				          text[0] = 0;
				        oyStringListAddStaticString_( &other_args,&other_args_n,
				                                      t,
				                            oyAllocateFunc_,oyDeAllocateFunc_ );
				        if(text)
				        oyStringListAddStaticString_( &other_args,&other_args_n,
				                            oyStrrchr_(&argv[pos][2], '=') + 1,
				                            oyAllocateFunc_,oyDeAllocateFunc_ );
				        else {
				          if(argv[pos+1])
				          {
				            oyStringListAddStaticString_( &other_args,
				                                          &other_args_n,
				                                          argv[pos+1],
				                            oyAllocateFunc_,oyDeAllocateFunc_ );
				            ++pos;
				          } else wrong_arg = argv[pos];
				        }
				        if(t) oyDeAllocateFunc_( t );
				        t = 0;
				        i=100; 
					break;
#endif
			      case '?':
			      default:
				        fprintf(stderr, "%s -%c\n", ("Unknown argument"), argv[pos][i]);
				        usage(argc, argv);
				        exit (0);
				        break;
			    }
            		break;
        		default:
           		wrong_arg = argv[pos];
	      		}
			if( wrong_arg )
			{
				fprintf(stderr, "%s %s\n", ("wrong argument to option:"), wrong_arg);
				exit(1);
			}
	     		++pos;
    		}

  	}
  	}
	


fprintf(stdout,"INPUT FILE = %s\n",input_xml_file);

#if 0
  if(!input_xml_file)
  {
    size_t text_size = 0;
    text = oyReadStdinToMem_(&text_size, oyAllocateFunc_);

    if(text_size == 0)
    {
                        usage(argc, argv);
                        exit (0);
    }
  }

#endif

  
  if(input_xml_file)
  {
   //TODO : read the input file
   xforms_text =  sReadFileToMem(input_xml_file);
   //fprintf(stdout,"output xml file is : %s \n\n",xforms_text);
  }
  Fl::scheme("gtk+");
  Fl_Double_Window * w = new Fl_Double_Window(WINDOW_WIDTH,WINDOW_HEIGHT,("XFORMS in FLTK"));
   // oyCallback_s callback = {oyOBJECT_CALLBACK_S, 0,0,0,
     //                             (void(*)())callback_help_view,0};
//    Fl_Group* o = new Fl_Group(0,0, WINDOW_WIDTH, WINDOW_HEIGHT,"main group");
//    fprintf(stdout,"\n\n\n%s\n\n\n",o->label());
//      Fl_Help_View * help_view = new Fl_Help_View( 0,600,500,80 );
//      help_view->box(FL_ENGRAVED_BOX);
//      help_view->color(FL_BACKGROUND_COLOR);
//      help_view->align(FL_ALIGN_LEFT);
//      help_view->selection_color(FL_DARK1);
//      help_view->value("");
//      //callback.data = help_view;
//    o->end(); // Fl_Group* o
    //oyFormsArgs_ResourceSet( forms_args, OYFORMS_FLTK_HELP_VIEW_REG,
             //                (oyPointer)&callback);

  Fl_Scroll * scroll = new Fl_Scroll( H_SPACING,V_SPACING,WINDOW_WIDTH-2*H_SPACING,WINDOW_HEIGHT-(5*V_SPACING + ROW_HEIGHT),"" );
	scroll->box( FL_NO_BOX );
	{
		Fl_Pack *scroll_pack = new Fl_Pack(scroll->x(),scroll->y(),scroll->w(),WINDOW_HEIGHT,"scroll_pack"); //TODO height of this widget
		scroll_pack->spacing(V_SPACING);
		{
			head = ParseXformsToTree( xforms_text,&modelDocPtr);
			//ptr2func = &DummyIfFunction;
			CallBackData = MainFunction(head,modelDocPtr,&DummyIfFunction);
			//print_user_data(CallBackData);
		}
		scroll_pack->end();

	}
	scroll->end();

  
	Fl_Group *BottomPaneGroup = new Fl_Group(H_SPACING,scroll->h() + 3*V_SPACING,WINDOW_WIDTH - 2*H_SPACING,ROW_HEIGHT+3*V_SPACING ,"");
	{
		 Fl_Button * done_button = new Fl_Button( (BottomPaneGroup->w() - BUTTON_WIDTH)/2, BottomPaneGroup->y() + V_SPACING, BUTTON_WIDTH, ROW_HEIGHT + V_SPACING, ("&Done"));
		 done_button->callback( callback_done, CallBackData );
		 //PrintWidgetDimensions(done_button);
	}
	BottomPaneGroup->end();
	//PrintWidgetDimensions(BottomPaneGroup);
	
	w->resizable( scroll );
	w->end();
	//FL_THIN_UP_BOX );
  //OyFl_Pack_c * pack = new OyFl_Pack_c( 5,1,395,338 );
  //pack->spacing(V_SPACING);
  
  //fprintf(stdout,"\n\n == error no === %d == \n",error);
  //sPrintsXformsTree(head);
  
  //test_widgets();
  //pack->end();
  
  

  //if(print)
    w->show(1, argv);
    Fl::run();

#if 0
  result_xml = oyFormsArgs_ModelGet( forms_args );
  if(output_model_file)
  {
  if(result_xml)
  oyWriteMemToFile_( output_model_file, result_xml, strlen(result_xml) );
    else
      fprintf( stderr, "%s\n", "no model found" );
  }
  else if(output_model)
  {
    if(result_xml)
      printf( "%s\n", result_xml );
    else
      fprintf( stderr, "%s\n", "no model found" );
  }

  oyFormsArgs_Release( &forms_args );

  /* xmlParseMemory sollte der Ebenen gewahr werden wie oyOptions_FromText. */
  opts = oyOptions_FromText( data, 0,0 );

  if(text) free(text); text = 0;
#endif
  if(output_model_file)
  {
      FILE *fp = fopen(output_model_file,"w");
      if( fp != NULL )
      xmlDocDump(fp, modelDocPtr);
      fclose(fp);
  }
  xmlDocDump(stdout, modelDocPtr);

  return 0;

}




