#ifndef SIMPLE_UI_XFORMS_H
#define SIMPLE_UI_XFORMS_H

struct sXformsNodeAttributeValue
{
	char *attrName;
	char *attrValue;
	struct sXformsNodeAttributeValue *next;
	struct sXformsNodeAttributeValue *prev;
};


struct sXformsNode
{
	char *type;
	char *name;
	char *value;
	char *hint;
	char *help;
	struct sXformsNodeAttributeValue *attr; // list of all attributes
	struct sXformsNode *prev; // previous sibling
	struct sXformsNode *next; // next sibling
	struct sXformsNode *child; // first child
	struct sXformsNode *par; // parent
	int num_child;
	char * meta_info; // extra public data
	char * private_data; //private data
};


typedef struct sXformsNode sXformsNode;
typedef struct sXformsNodeAttributeValue sXformsNodeAttr;
void AllocateMemoryToNode(sXformsNode **temp);
void sPrintsXformsTree(sXformsNode * head);
void sPrintsXformsNode(sXformsNode * node);
#endif
