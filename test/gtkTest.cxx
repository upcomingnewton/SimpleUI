#include<stdio.h>
#include "../fltk/sFltk.h"
#include <libxml/parser.h>
#include <string.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

/* compilation
g++  -g -I/usr/local/include -I/usr/include/freetype2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT -o 'SimpleUIFltkTest' fltk/sFltkProcess.cxx fltk/sFltk.h fltk/sFltkWidgets.cxx  fltk/sFltkCallbacks.cxx test/fltkTest.cxx   sCallbackData/sCallbackData.h  sCallbackData/sCallbackData.c  io/io.h io/io.c xml/sXml.h xml/sParseXforms.c misc/misc.h misc/string_func.c sXforms.h sXforms.c simpleUI.h -lXext -lXft -lfontconfig -lXinerama -lpthread -ldl -lm -lX11 `xml2-config --cflags --libs` `fltk-config --cflags --libs`
 */
char * GetDataAndUpdateModel(xmlDoc *modelDocPtr, char *xpath, char *val, int op);
void RemoteCallbackfunction(xmlDoc *ptr)
{
    printf("\n ================================== ");
    char *xpath_read_red = "/xf:model/xf:instance[@id='ui_color_choser']/data/red";
    char *xpath_read_blue = "/xf:model/xf:instance[@id='ui_color_choser']/data/blue";
    char *xpath_read_green = "/xf:model/xf:instance[@id='ui_color_choser']/data/green";
    char *xpath_set_red = "/xf:model/xf:instance[@id='cb_color_choser']/data/red";
    char *xpath_set_blue = "/xf:model/xf:instance[@id='cb_color_choser']/data/blue";
    char *xpath_set_green = "/xf:model/xf:instance[@id='cb_color_choser']/data/green";
    char *red = 0;
    char *green = 0;
    char *blue = 0;
    char bufred[6];
    char bufgreen[6];
    char bufblue[6];
    // 1. read value and convert it to integer
    red = GetDataAndUpdateModel(ptr,xpath_read_red,0, 2);
    printf("\n RECEIVED : RED = %s",red);
    // 2. convert it to hex
    sprintf(bufred,"%x",atoi(red));
    printf("\t UPDATED : RED = %s\n",bufred);
    // 3. update value
    GetDataAndUpdateModel(ptr,xpath_set_red,bufred, 1);
    
    blue = GetDataAndUpdateModel(ptr,xpath_read_blue,0, 2);
    printf("\n RECEIVED : blue = %s",blue);
    // 2. convert it to hex
    sprintf(bufblue,"%x",atoi(blue));
    printf("\t UPDATED : blue = %s\n",bufblue);
    // 3. update value
    GetDataAndUpdateModel(ptr,xpath_set_blue,bufblue, 1);
    
    green = GetDataAndUpdateModel(ptr,xpath_read_green,0, 2);
    printf("\n RECEIVED : green = %s",green);
    // 2. convert it to hex
    sprintf(bufgreen,"%x",atoi(green));
    printf("\t UPDATED : green = %s\n",bufgreen);
    // 3. update value
    GetDataAndUpdateModel(ptr,xpath_set_green,bufgreen, 1);
}

char * GetDataAndUpdateModel(xmlDoc *modelDocPtr, char *xpath, char *val, int op)
{
  // op = 1 => update
  // op = 2 => read
    xmlXPathContextPtr xpathcontext; 
  xmlXPathObjectPtr xpathobject;
  //TODO Error checking
  // Namespace issue's
  xmlNodeSetPtr nodes;
  xpathcontext = xmlXPathNewContext(modelDocPtr);
	if(xmlXPathRegisterNs( xpathcontext, (xmlChar*)"xf", (xmlChar*)"http://www.w3.org/2002/xforms")){
		printf("Could not register %s=%s\n", "xf", "http://www.w3.org/2002/xforms");
		return 0;
	}
    if(xpathcontext == NULL) {
        fprintf(stderr,"Error: unable to create new XPath context\n");
        return 0;
    }
    xpathobject = xmlXPathEvalExpression((xmlChar *)xpath, xpathcontext);
    nodes = xpathobject->nodesetval;
    if( op == 1)
    {
      //update
      xmlNodeSetContent(nodes->nodeTab[0],(xmlChar *)val);
      return 0;
    }
    else if( op == 2 )
    {
      //read
      return (char *)xmlNodeGetContent(nodes->nodeTab[0]);
    }
    return 0;
}


int main()
{
  int s = process("/home/nitin/projects/SimpleUI/xforms/color.xhtml",(char *)0,&RemoteCallbackfunction);
  printf("\n ********* %d\n",s);
}
