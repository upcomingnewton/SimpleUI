#include "simpleUI.h"
#include "sXforms.h"
#include<string.h>


//#define ENABLE_LOG
#ifdef ENABLE_LOG
#define WriteLog printf
#else
#define WriteLog
#endif

void AllocateMemoryForAttribute(sXformsNodeAttr **temp)
{
	(*temp) = (sXformsNodeAttr *)malloc(sizeof(sXformsNodeAttr));
	if( (*temp) == NULL )
	{
		WriteLog("Unable to allocate memory for sXformsNodeAttr");
		(*temp) = (sXformsNodeAttr *)0;
	}
	else{
		(*temp)->attrName = (char *)0;
		(*temp)->attrValue = (char *)0;
		(*temp)->private_data = (char *)0;
		(*temp)->meta_info = (char *)0;
		(*temp)->next = (sXformsNodeAttributeValue *)0;
		(*temp)->prev = (sXformsNodeAttributeValue *)0;
	}
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
		WriteLog("Error allocating memory\n");
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
	//WriteLog("\n === PRINTING NODE TREE ===");
	if( head == 0 ){
		WriteLog("\n Head node passed is null");
		
	}
	else{
		sXformsNode *temp ;
		for( temp = head->child; temp != 0 ; temp=temp->next){
			//WriteLog("\n\t %s : %s",temp->type,temp->name);
			sPrintsXformsNode(temp);
			if( temp->child == 0){
				WriteLog("\t\t-- NO CHILD ---\n");
			}else{
				WriteLog("\n\t------------- chilren start -------------\n");
				sPrintsXformsTree(temp);
				WriteLog("\n\t------------- chilren end -------------\n");
			}
		}
	}
}

void sPrintsXformsNode(sXformsNode * node)
{
	char * NotDefined = (char *)"NotDefined";
	if( node != 0){
		WriteLog("\n== Printing Detailed Node Info ==");
		WriteLog("\n Type = %s",node->type != 0 ? node->type :NotDefined );
		WriteLog("\n Name = %s",node->name != 0 ? node->name :NotDefined );
		WriteLog("\n Value = %s",node->value != 0 ? node->value :NotDefined );
		WriteLog("\n Hint = %s",node->hint != 0 ? node->hint :NotDefined );
		WriteLog("\n Help = %s",node->help != 0 ? node->help :NotDefined );
		//WriteLog("\n Attributes = ",node->attr);
		if(node->attr){
			WriteLog("\n ATTRIBUTE LIST");
			sPrintsXformsAttrList(node->attr);
		}
		if( node->prev != 0){
			WriteLog("\n prev = %s:%s",node->prev->type,node->prev->name );
		}
		else{
			WriteLog("\n prev = %s:%s",NotDefined,NotDefined);
		}
		if( node->next != 0){
			WriteLog("\n next = %s:%s",node->next->type,node->next->name );
		}
		else{
			WriteLog("\n next = %s:%s",NotDefined,NotDefined);
		}
		if( node->par != 0){
			WriteLog("\n par = %s:%s",node->par->type,node->par->name );
		}
		else{
			WriteLog("\n par = %s:%s",NotDefined,NotDefined);
		}
		if( node->child != 0){
			WriteLog("\n child = %s:%s",node->child->type,node->child->name );
		}
		else{
			WriteLog("\n child = %s:%s",NotDefined,NotDefined);
		}
		//WriteLog("\n next = ",node->next->type,node->next->name);
		//WriteLog("\n child = ",node->child->type,node->child->name);
		//WriteLog("\n par = ",node->par->type,node->par->name);
		WriteLog("\n number of children = ",node->num_child);
		WriteLog("\n meta info = ",node->meta_info); 
		WriteLog("\n private data = ",node->private_data);
		WriteLog("\n------------------------------------------------------\n");		
	}
}

void sPrintsXformsAttrList(sXformsNodeAttr * node){
	char * NotDefined = (char *)"NotDefined";
	if( node != 0){
		WriteLog("\n\t\t----------------------------------------");
		WriteLog("\n\t\t AttrName  = %s",node->attrName);
		WriteLog("\n\t\t AttrVal  = %s",node->attrValue);
		if(node->meta_info){
			WriteLog("\n\t\t Meta Info  = %s",node->meta_info);
		}
		else{
			WriteLog("\n\t\t Meta Info  = %s",NotDefined);
		}
		if(node->private_data){
			WriteLog("\n\t\t Private Data  = %s",node->private_data);
		}
		else{
			WriteLog("\n\t\t Private Data  = %s",NotDefined);
		}
	}
	if( node->next)
		sPrintsXformsAttrList(node->next);
	else
		WriteLog("\n\t\t----------------------------------------");
}

// 

sXformsNode * SearchSubTreeForNodes(sXformsNode *head,char *type, sXformsNodeAttr *attr, int SearchRecursive, int ComparisonsToCheck){
	sXformsNode *temp;
	int num_match = 0;
	WriteLog("\n\t\t------------------ START ----------------------");
	WriteLog("\n\t == 1 == Head = %s, %s TYPE %s, Recursive %d attr %u",head->type,head->name,type,SearchRecursive,attr);
	// match children
	for(temp=head->child; temp; temp=temp->next){
		if(!(temp->meta_info) && temp->type){
	WriteLog("\n\t == 2 == temp = %s, %s ",temp->type,temp->name);
			if( !strcmp(temp->type,type) ){
	WriteLog("\n\t == 3 == TYPES MATCH =");
				// matches, if attr list is there, match it
				if( attr ){
	WriteLog("\n\t == 4 == ATTRIBUTE LIST IS THERE =");
					if( temp->attr ){
	WriteLog("\n\t == 5 == TEMP ATTRIBUTE LIST IS THERE = (%s,%s)",temp->attr->attrName,temp->attr->attrValue );
						// we need attributes and this node have some
						sXformsNodeAttr *tempattr, *tempattr2;
						for( tempattr = attr; tempattr; tempattr=tempattr->next){
							for(tempattr2= temp->attr;  tempattr2 ; tempattr2=tempattr2->next){
	WriteLog("\n\t == 6 == SEARCHING (%s,%s) PRESENT (%s,%s)",tempattr->attrName,tempattr->attrValue,tempattr2->attrName,tempattr2->attrValue );
								if(!strcmp(tempattr2->attrName,tempattr->attrName) && (!strcmp(tempattr2->attrValue,tempattr->attrValue))){
									num_match++;
	WriteLog("\n\t == 7 == MATCHED =");
									break;
								}
							}
						}
						if(num_match  >= ComparisonsToCheck ){
							// return this node
	WriteLog("\n\t == 8 == PERFECT MATCHED =");
							return temp;
						}
					}
				}
				else{
					// we do not require attributes
					if((!temp->attr) || (ComparisonsToCheck == 0)){
	WriteLog("\n\t == 9 == PERFECT MATCHED =");
					return temp;
				}}
			}
		}
		// if we need to search recursive 
		if(SearchRecursive){
			sXformsNode *cr =  SearchSubTreeForNodes(temp,type,attr,SearchRecursive,ComparisonsToCheck);
			if( cr != 0){
	WriteLog("\n\t == 10 == PERFECT MATCHED =");
				return cr;
			}
		}
	}
	WriteLog("\n\t == 11 == FAILED =");
	return (sXformsNode *)0;
}

void * getAttrValueFromList(sXformsNode *node,char *name){
	if( node == 0){
		return (void *)0;
	}
	if( node->attr == 0){
		return (void *)0;
	}
	sXformsNodeAttr *attr;
	for( attr = node->attr; attr;attr = attr->next){
		if( !strcmp(attr->attrName,name)){
			return (void *)attr->attrValue;
		}
	}
	return (void *)0;
}


sXformsNodeAttr * getAttrFromList(sXformsNode *node,char *name){
	if( node == 0){
		return (sXformsNodeAttr *)0;
	}
	if( node->attr == 0){
		return (sXformsNodeAttr *)0;
	}
	sXformsNodeAttr *attr;
	for( attr = node->attr; attr;attr = attr->next){
		if( !strcmp(attr->attrName,name)){
			return attr;
		}
	}
	return (sXformsNodeAttr *)0;
}
