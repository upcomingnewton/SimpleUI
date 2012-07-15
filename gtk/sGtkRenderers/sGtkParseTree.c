#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "sGtkRenderer.h"

void sGenerateGladeFile()
{
    fprintf(stdout,"\n yes, it is working fine");
    xmlDoc *doc = NULL;
    xmlNode *root_node = NULL;
    
    /* required for every window */
    doc = xmlNewDoc(BAD_CAST"1.0");  // create a new document
    root_node = xmlNewNode(NULL,BAD_CAST"interface");  // root node
    xmlDocSetRootElement(doc, root_node); // set root node
    xmlNode *main_window = CreateChildNode(root_node,"object",sGTK_GLADE_MAIN_WINDOW_NAME,"GtkWindow");// create main window
    CreatePropertyNode(main_window,"default_height",GTK_WINDOW_HEIGHT);  // height
    CreatePropertyNode(main_window,"default_width",GTK_WINDOW_WIDTH);  // width
    CreatePropertyNode(main_window,"can_focus","False");  // is th window focusable
    CreateSignalNode(main_window,"destroy","gtk_main_quit",0);  // main exit signal
    xmlNode *child = xmlNewChild(main_window,NULL,BAD_CAST "child",NULL); // add child
    xmlNode *MainWindowContent = xmlNewChild(child,NULL,BAD_CAST "placeholder",NULL); // placeholder
    xmlSaveFormatFileEnc(sGTK_UI_FILE, doc, "UTF-8", 1); // save file
    xmlFreeDoc(doc);  // free document
    xmlCleanupParser();  //clean parser
}

xmlNode * CreateChildNode(xmlNode *par,char *objname,char *id,char *gtk_class)
{
    xmlNode *new_node = NULL;
    new_node = xmlNewNode(NULL,BAD_CAST objname);
    CreateNodeAttribute(new_node,"class",gtk_class);
    CreateNodeAttribute(new_node,"id",id);
    xmlAddChild(par,new_node);
    return new_node;
}

xmlNode * CreatePropertyNode(xmlNode *par,char *propname,char *propvalue)
{
    xmlNode *new_node = NULL, *textnode = NULL;
    new_node = xmlNewNode(NULL,BAD_CAST "property");
    CreateNodeAttribute(new_node,"name",propname);
    textnode = xmlNewText(BAD_CAST propvalue);
    xmlAddChild(new_node,textnode);
    xmlAddChild(par,new_node);
    return new_node;
}

xmlNode * CreateSignalNode(xmlNode *par,char *signalname,char *signalhandler, int swapped)
{
    xmlNode *new_node = NULL;
    new_node = xmlNewNode(NULL,BAD_CAST "signal");
    CreateNodeAttribute(new_node,"name",signalname);
    CreateNodeAttribute(new_node,"handler",signalhandler);
    CreateNodeAttribute(new_node,"swapped",swapped == 1 ? "yes" : "no");
    xmlAddChild(par,new_node);
    return new_node;
}

xmlAttr * CreateNodeAttribute(xmlNode *node, char *attrName, char *attrValue)
{
    xmlAttr *attr = NULL;
    attr = xmlNewProp(node,BAD_CAST attrName,BAD_CAST attrValue);
    return attr;
}
