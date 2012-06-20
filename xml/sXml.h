#ifndef SIMPLE_UI_XML_H
#define SIMPLE_UI_XML_H
#include <libxml/parser.h>
#include "../sXforms.h"
sXformsNode * ParseXformsToTree(const char * xforms);
sXformsNodeAttr * MakeAttributesList(xmlNodePtr cur);
char * sXmlNodeName(xmlNodePtr cur);
char * sAppendString( char *src, char *text);
void sParseNodesAndMakeTree(xmlNodePtr cur,sXformsNode **par, sXformsNode * head);
char * sGetValueFromChildren(xmlNodePtr cur, char *nodeToSearch);
void sAdjustPointersForLinkedList(sXformsNode **par, sXformsNode **child);
char * sGetTextFromNode(xmlNodePtr node);
const char * sGetXpathValue(char *reference, xmlDocPtr ptr);
//xmlXPathObjectPtr  sGetXpathObjectPtr(char *reference, xmlDocPtr doc);
#endif
