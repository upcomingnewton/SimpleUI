#ifndef _S_CALLBACK_DATA_H_
#define _S_CALLBACK_DATA_H_

#include "../misc/misc.h"
#include <malloc.h>
#include <libxml/parser.h>
#include <string.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

typedef void (*CallBackInterfaceFunction)(xmlDoc *ModelDocPtr);

struct sCbData{
    char *ref;
    char *init_val;
    char *value;
    char *name;
    char *meta_info;
    xmlDoc *doc;
    CallBackInterfaceFunction cbFunction;
    struct sCbData *next;
    struct sCbData *prev;
    struct sCbData *nextref;
};

struct sCbData * AllocateMemoryForCBNode();
struct sCbData * AppendNode(struct sCbData **head,char *ref_, char *init_val_,char *value_,char *name_,char *meta_info_, xmlDoc *_doc, CallBackInterfaceFunction _cbFunction);
    struct sCbData * MakeDummyData();
    struct sCbData *get_pointer_to_user_data_by_name(const char *_name, struct sCbData *head);
    void print_user_data(struct sCbData *head);
    void DummyIfFunction(xmlDoc *ptr);

int UpdateModel(struct sCbData * head);
void UpdateCallbackData(char *ref, char *data, struct sCbData *list);
void UpdateModelandCallUserFunction(char *ref, char *data,struct sCbData *list );
int UpdateRefsFromModel(struct sCbData * head);
#endif
