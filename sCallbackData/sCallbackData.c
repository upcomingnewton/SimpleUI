#include "sCallbackData.h"
#include "../misc/misc.h"
#include <malloc.h>
#include <libxml/parser.h>
#include <string.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

struct sCbData * AllocateMemoryForCBNode()
{
	struct sCbData *node = (struct sCbData *)malloc(sizeof(struct sCbData ));
	if ((node) == NULL)
	{
		fprintf(stdout,"\n could not allocate memory");
		(node) = (struct sCbData *)0;
	}
	else
	{
		(node)->ref = (char *)0;
		(node)->init_val= (char *)0;
		(node)->value= (char *)0;
		(node)->name= (char *)0;
		(node)->meta_info= (char *)0;
		(node)->next = (struct sCbData *)0;
		(node)->prev= (struct sCbData *)0;
		(node)->nextref = (struct sCbData *)0;
	}
	return node;
}

struct sCbData * AppendNode(struct sCbData **head,char *ref_, char *init_val_,char *value_,char *name_,char *meta_info_, xmlDoc *_doc, CallBackInterfaceFunction _cbFunction){
	/*
	1. allocate memory
	2. adjust the values
	3. adjust pointers
	4. return pointers to this node
	*/
	//fprintf(stdout,"\n ==> , head = %s, name = %s, meta = %s",(*head) != 0 ? (*head)->name : "null",name_,meta_info_);
	static int i = -1;
	i++;
	struct sCbData *newnode = AllocateMemoryForCBNode();
	if( newnode != 0){
		newnode->ref = s_dupstr(ref_);
		newnode->name = s_dupstr(name_);
		newnode->value = s_dupstr(value_);
		newnode->init_val = s_dupstr(init_val_);
		newnode->meta_info = s_dupstr(meta_info_);
		newnode->cbFunction = _cbFunction;
		newnode->doc = _doc;
		struct sCbData *temp = (*head);
		if( (*head) == 0){
			// no node in the system
			(*head) = newnode;
		}
		else
		{
			while( temp->next != 0){
				temp = temp->next;
			}
			temp->next = newnode;
			newnode->prev = temp;
		}
	}
	return newnode;
}

struct sCbData * MakeDummyData()
{
  xmlDoc *dummyptr = xmlNewDoc(BAD_CAST "1.0");
	struct sCbData *head = (struct sCbData *)0;
	struct sCbData *btn =  AppendNode(&head,"btn_personal_info", "NULL","NULL","btn_personal_info","xf:trigger",dummyptr,DummyIfFunction);
	struct sCbData *CheckBtn1 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","checkbutton_newpaper1","GtkCheckButton",dummyptr,DummyIfFunction);
	struct sCbData *CheckBtn2 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","checkbutton_newpaper3","GtkCheckButton",dummyptr,DummyIfFunction);
	struct sCbData *CheckBtn3 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","checkbutton_newpaper5","GtkCheckButton",dummyptr,DummyIfFunction);
	struct sCbData *btn1 =  AppendNode(&btn->nextref,"ref2", "init_val","value","combobox_prefix","GtkComboBox",dummyptr,DummyIfFunction);
	struct sCbData *btn2 =  AppendNode(&btn->nextref,"ref2", "init_val","value","entry_FirstName","GtkEntry",dummyptr,DummyIfFunction);
	struct sCbData *btn3 =  AppendNode(&btn->nextref,"ref2", "init_val","value","entry_MiddleName","GtkEntry",dummyptr,DummyIfFunction);
	struct sCbData *btn31 =  AppendNode(&btn->nextref,"ref2", "init_val","value","entry_LastName","GtkEntry",dummyptr,DummyIfFunction);
	struct sCbData *btn32 =  AppendNode(&btn->nextref,"ref2", "init_val","value","entry_dob","GtkEntry",dummyptr,DummyIfFunction);//entry_dob
	struct sCbData *btn33 =  AppendNode(&btn->nextref,"ref2", "init_val","value","radiobutton_nothing","GtkRadioButton",dummyptr,DummyIfFunction);
	struct sCbData *btn4 =  AppendNode(&head,"combobox_prefix", "init_val","value","combobox_prefix","GtkComboBox",dummyptr,DummyIfFunction);
	
	return head;
}

void DummyIfFunction(xmlDoc *ptr)
{
/*  printf("\n =============================== ");*/
  printf("\n i am in dummy interface function");
/*  printf("\n =============================== ");*/
}

void print_user_data(struct sCbData *head)
{
	struct sCbData *temp = head;
	struct sCbData *temp2;
	fprintf(stdout,"\n == PRINTING USER DATA == \n");
	while( temp != 0)
	{
		fprintf(stdout,"\n( %s,%s,%s,%s,%s )",temp->ref,temp->init_val,temp->value,temp->name,temp->meta_info);
		temp2 = temp->nextref;
		while( temp2 )
		{
			fprintf(stdout,"\n\t -> ( %s,%s,%s,%s,%s )",temp2->ref,temp2->init_val,temp2->value,temp2->name,temp2->meta_info);
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
	fprintf(stdout,"\n");
}

struct sCbData *get_pointer_to_user_data_by_name(const char *_name, struct sCbData *head)
{
	struct sCbData *temp = head;
	while(temp!=0)
	{
		if( !(strcmp(_name,temp->name)))
		{
			return temp;
		}
		temp = temp->next;
	}
	return (struct sCbData *)0;
}

void UpdateModelandCallUserFunction(char *ref, char *data,struct sCbData *list )
{
  // 1. update all references
  UpdateCallbackData(ref,data,list);
  // 2. update model
  UpdateModel(list);
  // 3. call user function with this model
  list->cbFunction(list->doc);
  // 4. update ref from model returned
  UpdateRefsFromModel(list);
  //print_user_data(list);
}

void UpdateCallbackData(char *ref, char *data, struct sCbData *list)
{
  if(strcmp(ref,"0")){
  struct sCbData *temp;
    for( temp = list ; temp ; temp =temp->next )
    {
      if(!strcmp(temp->ref,ref))
      {
        temp->value = data;
/*        Fl_Widget *target = findWidgetByName(widget->window(),temp->name);*/
/*        temp->cbFunction(temp->doc);*/
/*        if( target != 0 )*/
/*        {*/
/*          UpdateWidgetValue(temp->meta_info,temp->value,target);*/
/*        }*/
      }
      if( temp->nextref )
      {
        struct sCbData *temp2;
          for( temp2 = temp->nextref ; temp2 ; temp2 =temp2->next )
          {
                if(!strcmp(temp2->ref,ref))
                {
                  temp2->value = data;
                }
          }
      }
    }
  }
}


int UpdateModel(struct sCbData * head)
{
  xmlXPathContextPtr xpathcontext; 
  xmlXPathObjectPtr xpathobject;
  xmlDoc *modelDocPtr = head->doc;
  struct sCbData * temp ;
  struct sCbData * temp2;
  //TODO Error checking
  // Namespace issue's
  xmlNodeSetPtr nodes;
   xpathcontext = xmlXPathNewContext(modelDocPtr);
	if(xmlXPathRegisterNs( xpathcontext, (xmlChar*)"xf", (xmlChar*)"http://www.w3.org/2002/xforms")){
		printf("Could not register %s=%s\n", "xf", "http://www.w3.org/2002/xforms");
		return -1;
	}
    if(xpathcontext == NULL) {
        fprintf(stderr,"Error: unable to create new XPath context\n");
        return -1;
    }
    
    for(temp = head; temp; temp = temp->next)
    {
      if(strcmp(temp->ref,"0"))
      {
        xpathobject = xmlXPathEvalExpression((xmlChar *)temp->ref, xpathcontext);
        if(xpathobject == NULL) {
            fprintf(stderr,"[ %s ]Error: unable to evaluate XPath context\n",temp->name);
        }
        else
        {
          nodes = xpathobject->nodesetval;
          //printf("\n[1][ %s ] number of nodes inside here is %d",temp->name, nodes->nodeNr);
          if(temp->value !=  0 )
	  xmlNodeSetContent(nodes->nodeTab[0],(xmlChar *) temp->value);
        }
      }
      if( temp->nextref )
      {
        for( temp2 = temp->nextref; temp2 ; temp2 = temp2->next)
        if(strcmp(temp2->ref,"0"))
        {
            xpathobject = xmlXPathEvalExpression((xmlChar *)temp2->ref, xpathcontext);
            
            if(xpathobject == NULL) {
                fprintf(stderr,"[ %s ]Error: unable to evaluate XPath context\n",temp2->name);
            }
            else
            {
              nodes = xpathobject->nodesetval;
              //printf("\n[2][ %s ] number of nodes inside here is %d",temp2->name, nodes->nodeNr);
              if(temp->value !=  0 )
	      xmlNodeSetContent(nodes->nodeTab[0],(xmlChar *) temp2->value);
            }
        }
      }
    }
    return 0;
}


int UpdateRefsFromModel(struct sCbData * head)
{
  xmlXPathContextPtr xpathcontext; 
  xmlXPathObjectPtr xpathobject;
  xmlDoc *modelDocPtr = head->doc;
  struct sCbData * temp;
  struct sCbData * temp2;
  //TODO Error checking
  // Namespace issue's
  xmlNodeSetPtr nodes;
   xpathcontext = xmlXPathNewContext(modelDocPtr);
	if(xmlXPathRegisterNs( xpathcontext, (xmlChar*)"xf", (xmlChar*)"http://www.w3.org/2002/xforms")){
		printf("Could not register %s=%s\n", "xf", "http://www.w3.org/2002/xforms");
		return -1;
	}
    if(xpathcontext == NULL) {
        fprintf(stderr,"Error: unable to create new XPath context\n");
        return -1;
    }
    for( temp = head; temp; temp = temp->next)
    {
      if(strcmp(temp->ref,"0"))
      {
        xpathobject = xmlXPathEvalExpression((xmlChar *)temp->ref, xpathcontext);
        if(xpathobject == NULL) {
            fprintf(stderr,"[ %s ]Error: unable to evaluate XPath context\n",temp->name);
        }
        else
        {
          nodes = xpathobject->nodesetval;
          //printf("\n[1][ %s ] number of nodes inside here is %d",temp->name, nodes->nodeNr);
          temp->value = (char *)xmlNodeGetContent(nodes->nodeTab[0]);//TODO
          //printf("\n[2] [ %s ] = [ %s ]",temp->ref,temp->value);
        }
      }
      if( temp->nextref )
      {
        for( temp2 = temp->nextref; temp2 ; temp2 = temp2->next)
        if(strcmp(temp2->ref,"0"))
        {
            xpathobject = xmlXPathEvalExpression((xmlChar *)temp2->ref, xpathcontext);
            
            if(xpathobject == NULL) {
                fprintf(stderr,"[ %s ]Error: unable to evaluate XPath context\n",temp2->name);
            }
            else
            {
              nodes = xpathobject->nodesetval;
              //printf("\n[2][ %s ] number of nodes inside here is %d",temp2->name, nodes->nodeNr);
              temp2->value = (char *)xmlNodeGetContent(nodes->nodeTab[0]);//TODO
              //printf("\n[2] [ %s ] = [ %s ]",temp2->ref,temp2->value);
            }
        }
      }
    }
    return 0;
}
