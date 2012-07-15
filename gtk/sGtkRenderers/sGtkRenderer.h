#ifndef S_GTK_RENDERER_H
    #include <libxml/parser.h>
    #include <libxml/tree.h>
    #define S_GTK_RENDERER_H
    #define sGTK_UI_FILE  "xforms/sGtkSampleTest2.glade"
    #define sGTK_GLADE_MAIN_WINDOW_NAME "sGTK_GLADE_MAIN_WINDOW_NAME"
    #define GTK_WINDOW_HEIGHT "360"
    #define GTK_WINDOW_WIDTH "480"
    void sGenerateGladeFile();
    xmlNode * CreateChildNode(xmlNode *par,char *objname,char *id,char *gtk_class);
    xmlAttr * CreateNodeAttribute(xmlNode *node, char *attrName, char *attrValue);
    xmlNode * CreatePropertyNode(xmlNode *par,char *propname,char *propvalue);
    xmlNode * CreateSignalNode(xmlNode *par,char *signalname,char *signalhandler, int swapped);
#endif

