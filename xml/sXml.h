#ifndef SIMPLE_UI_XML_H
#define SIMPLE_UI_XML_H
#include <libxml/parser.h>
#include "../sXforms.h"
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>


sXformsNode * ParseXformsToTree(const char * xforms);
sXformsNodeAttr * MakeAttributesList(xmlNodePtr cur, xmlDocPtr ptr);
char * sXmlNodeName(xmlNodePtr cur);
char * sAppendString( char *src, char *text);
void sParseNodesAndMakeTree(xmlNodePtr cur,sXformsNode **par, sXformsNode * head, xmlDocPtr ptr);
char * sGetValueFromChildren(xmlNodePtr cur, char *nodeToSearch);
void sAdjustPointersForLinkedList(sXformsNode **par, sXformsNode **child);
char * sGetTextFromNode(xmlNodePtr node);

void makemodel(xmlNodePtr cur,sXformsNode **par,int pos);
char *sGetXpathFromRefAttr(sXformsNodeAttr *attr,xmlDocPtr doc);
char *sGetXpathFromNodeSetAttr(sXformsNodeAttr *attr);
int CompareFirstNChars(char *src1, int start1, char *src2, int start2, int n);

xmlNodeSetPtr sGetXpathValue(char *reference, xmlDocPtr doc);
xmlXPathContextPtr sGetXpathEvalContext(xmlDocPtr doc);
char * EvalNodeSetPtrForInstannce(xmlNodeSetPtr nodeset);
//xmlXPathObjectPtr  sGetXpathObjectPtr(char *reference, xmlDocPtr doc);
#endif
