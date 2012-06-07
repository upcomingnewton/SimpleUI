#include "simpleUI.h"
#include "sXforms.h"
#include<string.h>
#define ENABLE_ERROR_LOG
#ifdef ENABLE_ERROR_LOG
#define ERROR_LOG(msg,args...) fprintf(stderr,msg,args...);
#else
#define ERROR_LOG(msg,args...)
#endif

sXformsNodeAttr * AllocateMemoryForAttribute()
{
	sXformsNodeAttr *  temp = (sXformsNodeAttr *)malloc(sizeof(sXformsNodeAttr));
	if( temp == NULL )
	{
		fprintf(stderr,"Unable to allocate memory for sXformsNodeAttr");
		temp = (sXformsNodeAttr *)0;
	}
	return temp;
}

#if 0
sXformsNodeAttr * sXformsAppendAttrToList(sXformsNodeAttr **head, const char *attrname, const char *value )
{
	sXformsNodeAttr *temp = AllocateMemoryForAttribute();
	int templen = strlen(attrname);
	temp -> attrName = (char *)malloc(sizeof(char)*(templen + 1));
	strcpy(attrname,temp->attrName);
	
	int templen = strlen(value);
	temp -> attrName = (char *)malloc(sizeof(char)*(templen + 1));
	strcpy(value,temp->attrValue);
	
	return temp;
}
#endif

void AllocateMemoryToNode(sXformsNode **temp)
{
	(*temp) = (sXformsNode *)malloc(sizeof(sXformsNode));
	if( !(*temp) ){
		fprintf(stderr,"Error allocating memory\n");
		(*temp) = (sXformsNode *)0;
	}
	else{
		(*temp)->type = (char *)0;
		(*temp)->name = (char *)0;
		(*temp)->value = (char *)0;
		(*temp)->hint = (char *)0;
		(*temp)->help = (char *)0;
		(*temp)->attr = (struct sXformsNodeAttributeValue *)0; // list of all attributes
		(*temp)->prev = (struct sXformsNode*)0; // previous sibling
		(*temp)->next = (struct sXformsNode*)0; // next sibling
		(*temp)->child = (struct sXformsNode*)0; // first child
		(*temp)->par  = (struct sXformsNode*)0; // parent
		(*temp)->num_child = 0;
		(*temp)->meta_info  = (char *)0; // extra public data
		(*temp)->private_data = (char *)0; //private data
	}
}

void sPrintsXformsTree(sXformsNode * head)
{
	//fprintf(stdout,"\n === PRINTING NODE TREE ===");
	if( head == 0 ){
		fprintf(stdout,"\n Head node passed is null");
	}
	else{
		sXformsNode *temp ;
		for( temp = head->child; temp != 0 ; temp=temp->next){
			fprintf(stdout,"\n\t %s : %s",temp->type,temp->name);
			if( temp->child == 0){
				fprintf(stdout,"\t\t-- NO CHILD ---\n");
			}else{
				fprintf(stdout,"\n\t------------- chilren -------------\n");
				sPrintsXformsTree(temp);
				fprintf(stdout,"\n\t------------- chilren end -------------\n");
			}
		}
	}
}

void sPrintsXformsNode(sXformsNode * node)
{
	char * NotDefined = (char *)"NotDefined";
	if( node != 0){
		fprintf(stdout,"\n== Printing Detailed Node Info ==");
		fprintf(stdout,"\n Type = %s",node->type != 0 ? node->type :NotDefined );
		fprintf(stdout,"\n Name = %s",node->name != 0 ? node->name :NotDefined );
		fprintf(stdout,"\n Value = %s",node->value != 0 ? node->value :NotDefined );
		fprintf(stdout,"\n Hint = %s",node->hint != 0 ? node->hint :NotDefined );
		fprintf(stdout,"\n Help = %s",node->help != 0 ? node->help :NotDefined );
		//fprintf(stdout,"\n Attributes = ",node->attr);
		if( node->prev != 0){
			fprintf(stdout,"\n prev = %s:%s",node->prev->type,node->prev->name );
		}
		else{
			fprintf(stdout,"\n prev = %s:%s",NotDefined,NotDefined);
		}
		if( node->next != 0){
			fprintf(stdout,"\n next = %s:%s",node->next->type,node->next->name );
		}
		else{
			fprintf(stdout,"\n next = %s:%s",NotDefined,NotDefined);
		}
		if( node->par != 0){
			fprintf(stdout,"\n par = %s:%s",node->par->type,node->par->name );
		}
		else{
			fprintf(stdout,"\n par = %s:%s",NotDefined,NotDefined);
		}
		if( node->child != 0){
			fprintf(stdout,"\n child = %s:%s",node->child->type,node->child->name );
		}
		else{
			fprintf(stdout,"\n child = %s:%s",NotDefined,NotDefined);
		}
		//fprintf(stdout,"\n next = ",node->next->type,node->next->name);
		//fprintf(stdout,"\n child = ",node->child->type,node->child->name);
		//fprintf(stdout,"\n par = ",node->par->type,node->par->name);
		fprintf(stdout,"\n number of children = ",node->num_child);
		fprintf(stdout,"\n meta info = ",node->meta_info); 
		fprintf(stdout,"\n private data = ",node->private_data);
		fprintf(stdout,"\n------------------------------------------------------\n");		
	}
}
