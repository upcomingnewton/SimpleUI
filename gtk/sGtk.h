#ifndef S_GTK_H
#define S_GTK_H
#include <gtk/gtk.h>
#include "sGtkRenderers/sGtkRenderer.h"
#include "../sCallbackData/sCallbackData.h"
int process(char *input_xml_file, char *output_xml_file,CallBackInterfaceFunction cb);
#endif



