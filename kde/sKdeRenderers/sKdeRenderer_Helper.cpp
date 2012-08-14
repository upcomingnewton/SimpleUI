#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "sKdeRenderer.h"

xmlNode *Create1GeometryProp(xmlNode *par,char *x, char *y, char *width, char *height)
{
  xmlNode *propnode = NULL;
  propnode = CreateXmlNode(NULL,"property");
  CreateNodeAttribute(propnode,"name","geometry");
  
  xmlNode *rectnode = NULL;
  rectnode = CreateXmlNode(NULL,"rect");
  Create1ObjectNode(rectnode,"x",x);
  Create1ObjectNode(rectnode,"y",y);
  Create1ObjectNode(rectnode,"width",width);
  Create1ObjectNode(rectnode,"height",height);
  xmlAddChild(propnode,rectnode);
  xmlAddChild(par,propnode);
  return propnode;
}
void CreatePropertyNodes(xmlNode *par,char **prop_name, char **prop_type, char **value, int num_prop)
{
    int i = 0;
    for( i = 0 ; i < num_prop ; i++)
    {
    	Create1PropertyNode(par,prop_name[i],prop_type[i],value[i]);
    }
}

xmlNode *Create1PropertyNode(xmlNode *par,char *prop_name,char *prop_type, char *value)
{
    xmlNode *new_node = NULL;
    new_node = CreateXmlNode(NULL,"property");
    if( prop_name != NULL) { CreateNodeAttribute(new_node,"name",prop_name); }
    if( value != NULL) { 
        xmlNode *propvalue = NULL;
        propvalue  = CreateXmlNode(NULL,prop_type);
        xmlNode *textnode = NULL;
        textnode = xmlNewText(BAD_CAST value);
        xmlAddChild(propvalue,textnode);
        xmlAddChild(new_node,propvalue);
    }
    xmlAddChild(par,new_node);
    return new_node;
}

xmlNode *Create1WidgetNode(xmlNode *par,char *name, char *classname,char **prop_name, char **prop_type, char **value, int num_prop)
{
    xmlNode *new_node = NULL;
    int i = 0;
    new_node = CreateXmlNode(NULL,"widget");
    if( classname != NULL) { CreateNodeAttribute(new_node,"class",classname); }
    if( name != NULL) { CreateNodeAttribute(new_node,"name",name); }
    xmlAddChild(par,new_node);
    for( i = 0 ; i < num_prop ; i++)
    {
    	Create1PropertyNode(new_node,prop_name[i],prop_type[i],value[i]);
    }
    return new_node;
}

xmlNode *Create1WidgetNodeWithStringProp(xmlNode *par,char *name, char *classname,char *propname, char *strval)
{
    xmlNode *new_node = NULL;
    new_node = CreateXmlNode(NULL,"widget");
    if( classname != NULL) { CreateNodeAttribute(new_node,"class",classname); }
    if( name != NULL) { CreateNodeAttribute(new_node,"name",name); }
    if( par != 0)
    {
      xmlAddChild(par,new_node);
    }
    CreateStringProperty(new_node,propname,strval );
    return new_node;
}

xmlAttr * CreateNodeAttribute(xmlNode *node, char *attrName, char *attrValue)
{
    xmlAttr *attr = NULL;
    attr = xmlNewProp(node,BAD_CAST attrName,BAD_CAST attrValue);
    return attr;
}

xmlNode *CreateNodeText(xmlNode* par,char *val)
{
    xmlNode *textnode = NULL;
    textnode = xmlNewText(BAD_CAST val);
    xmlAddChild(par,textnode);
    return textnode;
}

xmlNode *Create1ObjectNode(xmlNode *par,char *nodename, char *value)
{
    xmlNode *new_node = NULL;
    new_node = CreateXmlNode(NULL,nodename);
    if( value != 0)
    {
      CreateNodeText(new_node,value);
    }
    xmlAddChild(par,new_node);
    return new_node;
}

xmlNode *CreateStringProperty(xmlNode *par,char *propname, char *strval )
{
  xmlNode *new_node = NULL;
  new_node = CreateXmlNode(NULL,"property");
  CreateNodeAttribute(new_node,"name",propname); 
  Create1ObjectNode(new_node,"string",strval);
  xmlAddChild(par,new_node);
}

xmlNode *CreateLayout(xmlNode *par,char *classname, char *name )
{
  xmlNode *layoutNode = Create1ObjectNode(par,"layout",0);
  CreateNodeAttribute(layoutNode,"class",classname); 
  CreateNodeAttribute(layoutNode,"name",name); 
  return layoutNode;
}


/*

       <item>
        <spacer name="horizontalSpacer">
         <property name="orientation">
          <enum>Qt::Horizontal</enum>
         </property>
         <property name="sizeHint" stdset="0">
          <size>
           <width>40</width>
           <height>20</height>
          </size>
         </property>
        </spacer>
       </item>
       
*/

xmlNode *CreateSpacer(xmlNode *par,char *spacerName, char *orientation, char *width, char *height )
{
  xmlNode *itemNode = CreateXmlNode(NULL,"item");
  xmlNode *spacerNode = CreateXmlNode(NULL,"spacer");
  CreateNodeAttribute(spacerNode,"name",spacerName); 
  xmlNode *PropNode = CreateXmlNode(NULL,"property");
  CreateNodeAttribute(PropNode,"name","orientation"); 
  Create1ObjectNode(PropNode,"enum",orientation);
  xmlAddChild(itemNode,spacerNode);
  xmlAddChild(spacerNode,PropNode);
  xmlNode *PropNode2 = CreateXmlNode(NULL,"property");
  CreateNodeAttribute(PropNode2,"name","sizeHint"); 
  CreateNodeAttribute(PropNode2,"stdset","0"); 
  xmlAddChild(spacerNode,PropNode2);
  xmlNode *sizeNode = CreateXmlNode(NULL,"size");
  Create1ObjectNode(sizeNode,"width",width);
  Create1ObjectNode(sizeNode,"height",height);
  xmlAddChild(PropNode2,sizeNode);
  xmlAddChild(par,itemNode);
  return itemNode;
}

xmlNode *CreateItemNode(xmlNode *par,xmlNode *child, char * row, char * column)
{
  xmlNode *itemNode = CreateXmlNode(NULL,"item");
  if( row != 0 && column != 0)
  {
    CreateNodeAttribute(itemNode,"row",row); 
    CreateNodeAttribute(itemNode,"column",column); 
  }
  if( child != 0 )
  {
    xmlAddChild(itemNode,child);
  }
  if( par != 0 )
  {
    xmlAddChild(par,itemNode);
  }
}

xmlNode * CreateXmlNode(xmlNsPtr ns, char * name)
{
    return xmlNewNode(ns,BAD_CAST name);
}
