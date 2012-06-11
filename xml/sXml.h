#ifndef SIMPLE_UI_XML_H
#define SIMPLE_UI_XML_H
#include <libxml/parser.h>
#include "../sXforms.h"
sXformsNode * ParseXformsToTree(const char * xforms);
sXformsNodeAttr * MakeAttributesList(xmlNodePtr cur);
#endif
