#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "sGtkRenderer.h"

xmlNode *Create1ObjectNode(xmlNode *par,char *id, char *classname,char *constructor, char *type_func)
{
    xmlNode *new_node = NULL;
    new_node = CreateXmlNode(NULL,"object");
    if( id != NULL) { CreateNodeAttribute(new_node,"id",id); }
    if( classname != NULL) { CreateNodeAttribute(new_node,"class",classname); }
    if( constructor != NULL) { CreateNodeAttribute(new_node,"constructor",constructor); }
    if( type_func != NULL) { CreateNodeAttribute(new_node,"type-func",type_func); }
    xmlAddChild(par,new_node);
    return new_node;
}

xmlNode *Create1PropertyNode(xmlNode *par,char *prop_name,char *translatable, char *comments, char *context, char *value)
{
    xmlNode *new_node = NULL;
    new_node = CreateXmlNode(NULL,"property");
    if( prop_name != NULL) { CreateNodeAttribute(new_node,"name",prop_name); }
    if( translatable != NULL) { CreateNodeAttribute(new_node,"translatable",translatable); }
    if( comments != NULL) { CreateNodeAttribute(new_node,"comments",comments); }
    if( context != NULL) { CreateNodeAttribute(new_node,"context",context); }
    if( value != NULL) { 
        xmlNode *textnode = NULL;
        textnode = xmlNewText(BAD_CAST value);
        xmlAddChild(new_node,textnode);
    }
    xmlAddChild(par,new_node);
    return new_node;
}

void CreatePropertyNodes(xmlNode *par,char **prop_name,char **translatable, char **comments, char **context, char **value, int num_prop)
{
    int i = 0;
    for( i = 0 ; i < num_prop ; i++)
    {
    	Create1PropertyNode(par,prop_name[i],translatable[i],comments[i],context[i],value[i]);
    }
}

xmlNode * Create1SignalNode(xmlNode *par,char *name, char *handler, char *after, char *swapped, char *object, char *last_modification_time)
{
    xmlNode *new_node = NULL;
    new_node = CreateXmlNode(NULL,"signal");
    if( name != NULL) { CreateNodeAttribute(new_node,"name",name); }
    if( handler != NULL) { CreateNodeAttribute(new_node,"handler",handler); }
    if( after != NULL) { CreateNodeAttribute(new_node,"after",after); }
    if( swapped != NULL) { CreateNodeAttribute(new_node,"swapped",swapped); }
    if( object != NULL) { CreateNodeAttribute(new_node,"object",object); }
    if( last_modification_time != NULL) { CreateNodeAttribute(new_node,"last_modification_time",last_modification_time); }
    xmlAddChild(par,new_node);
    return new_node;
}

xmlNode * Create1ChildNode(xmlNode *par,char *type, char *internal_child)
{
    xmlNode *new_node = NULL;
    new_node = CreateXmlNode(NULL,"child");
    if( type != NULL) { CreateNodeAttribute(new_node,"type",type); }
    if( internal_child != NULL) { CreateNodeAttribute(new_node,"internal_child",internal_child); }
    xmlAddChild(par,new_node);
    return new_node;
}

xmlNode * Create1ChildNodeWithPlaceholder(xmlNode *par,char *type, char *internal_child)
{
    xmlNode *new_node = NULL, *placeholder = NULL;
    new_node = CreateXmlNode(NULL,"child");
    placeholder = CreateXmlNode(NULL,"placeholder");
    if( type != NULL) { CreateNodeAttribute(new_node,"type",type); }
    if( internal_child != NULL) { CreateNodeAttribute(new_node,"internal_child",internal_child); }
    xmlAddChild(new_node,placeholder);
    xmlAddChild(par,new_node);
    return new_node;
}

xmlNode *CreatePackingNodeWithProperties(xmlNode *par,char **prop_name,char **translatable, char **comments, char **context, char **value, int num_prop)
{
	xmlNode *new_node = NULL;
	new_node = CreateXmlNode(NULL,"packing");
	CreatePropertyNodes(new_node,prop_name,translatable,comments,context,value, num_prop);
	xmlAddChild(par,new_node);
	return new_node;
}

xmlAttr * CreateNodeAttribute(xmlNode *node, char *attrName, char *attrValue)
{
    xmlAttr *attr = NULL;
    attr = xmlNewProp(node,BAD_CAST attrName,BAD_CAST attrValue);
    return attr;
}

xmlNode * CreateXmlNode(xmlNsPtr ns, char * name)
{
    return xmlNewNode(ns,BAD_CAST name);
}
