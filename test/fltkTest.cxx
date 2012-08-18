#include<stdio.h>
#include "../fltk/sFltk.h"
#include <libxml/parser.h>
#include <string.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

/* compilation
g++  -g -I/usr/local/include -I/usr/include/freetype2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT -o 'SimpleUIFltkTest' fltk/sFltkProcess.cxx fltk/sFltk.h fltk/sFltkWidgets.cxx  fltk/sFltkCallbacks.cxx test/fltkTest.cxx   sCallbackData/sCallbackData.h  sCallbackData/sCallbackData.c  io/io.h io/io.c xml/sXml.h xml/sParseXforms.c misc/misc.h misc/string_func.c sXforms.h sXforms.c simpleUI.h -lXext -lXft -lfontconfig -lXinerama -lpthread -ldl -lm -lX11 `xml2-config --cflags --libs` `fltk-config --cflags --libs`
 */

void RemoteCallbackfunction(xmlDoc *ptr)
{
  printf("\n************************************");
  printf("\n %s",__func__);
  printf("\n************************************");
}

int main()
{
  int s = process("/home/nitin/projects/SimpleUI/xforms/file9.xhtml",(char *)0,&RemoteCallbackfunction);
  printf("\n ********* %d\n",s);
}
