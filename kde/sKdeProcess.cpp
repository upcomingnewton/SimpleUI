#include <QApplication>
#include "sKDE.h"
#include "sKdeCallbacks/sKde_Cb.h"
#include "sKdeRenderers/sKdeRenderer.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
#include "../simpleUI.h"
#include "../sXforms.h"
#include "../xml/sXml.h"
#include "../io/io.h"
#include "../sCallbackData/sCallbackData.h"
#include "../sXforms.h"
#include "sKdeProcess.h"


int process(char *input_xml_file, char *output_xml_file,CallBackInterfaceFunction cb)
{
	fprintf(stdout,"\n===== SIMPLE UI TOOLKIT =====\n\n");
	 const char *wrong_arg = 0;
	 char *xforms_text = 0;
	 sXformsNode *head;
	 struct sCbData *CallBackData;
	 xmlDoc *modelDocPtr;
    struct qt_cb_data *cb_data = (struct qt_cb_data *)0;
    
  if(input_xml_file)
  {
   xforms_text =  sReadFileToMem(input_xml_file);
   //fprintf(stdout,"output xml file is : %s \n\n",xforms_text);
  }
  head = ParseXformsToTree( xforms_text,&modelDocPtr);
  //sPrintsXformsTree(head);

  if(cb == 0)
  {
    CallBackData = sKdeGenerateGladeFile(head,modelDocPtr,&DummyIfFunction);
  }
  else
  {
    CallBackData = sKdeGenerateGladeFile(head,modelDocPtr,cb);
  }
  print_user_data(CallBackData);
  int argc = 0;
  char **argv = 0;
      QApplication a(argc, argv);
    SimpleUiKde w(CallBackData);
    w.show();
    a.exec();
   
  
if(output_xml_file)
  {
      FILE *fp = fopen(output_xml_file,"w");
      if( fp != NULL )
      xmlDocDump(fp, modelDocPtr);
      fclose(fp);
  }
  xmlDocDump(stdout, modelDocPtr);
    fprintf(stdout,"\n");
    fprintf(stdout,"\n");
 return 0;
}

