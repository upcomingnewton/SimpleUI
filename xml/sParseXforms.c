#include "sXml.h"
#include "../simpleUI.h"
#include "../sXforms.h"
#include <libxml/parser.h>
#include <string.h>



//struct sXformsNode *ParseXformsToTree(const char * xforms){
char * sXmlNodeName(xmlNodePtr cur);
char * sAppendString( char *src, char *text);
void sParseNodesAndMakeTree(xmlNodePtr cur,sXformsNode **par, sXformsNode * head);
char * sGetValueFromChildren(xmlNodePtr cur, char *nodeToSearch);
void sAdjustPointersForLinkedList(sXformsNode **par, sXformsNode **child);
char * sGetTextFromNode(xmlNodePtr node);
int x = 0;

sXformsNode * ParseXformsToTree(const char * xforms){
	int error = !xforms;
	xmlDocPtr doc;
	xmlNodePtr cur;
	const char *text = xforms;
	sXformsNode *head;
	if (error ){
		return (sXformsNode *)0;
	}
	doc = xmlParseMemory(text, strlen(text));
	cur = xmlDocGetRootElement(doc);
	
	if( doc && cur ){
		//fprintf(stdout,"\ndoc = %u, cur = %u,",doc,cur);
		//fprintf(stdout,"\ncurrent node name is : %s, and ns is %s, extra info here is %u",cur->name,"cur->ns->prefix",cur->extra);
		// 1. make a new element , maybe head and start exploring the tree
		// make a new element
		
		AllocateMemoryToNode(&head);
		if( head != 0 ){ 
			head->name = sAppendString(head->name,(char *)"head");
			// start exploring the tree
			sParseNodesAndMakeTree(cur,&head,head);
		}
		else{
			//fprintf(stdout,"\ncould not allocate memory for head");
			exit(1);
		}
		//xmlFreeDoc(doc);
	}
	else {
		error = 1;
	}
	//sPrintsXformsTree(head);
	return head;
}

void sParseNodesAndMakeTree(xmlNodePtr cur,sXformsNode **par, sXformsNode * head)
{
	char *type = (char *)0;
	char *tempc = 0;
	sXformsNode *temp = *par;
	const xmlChar *prefix = 0;
	while( cur != 0)
	{
		prefix = ( cur->ns && cur->ns->prefix ) ? cur->ns->prefix : 0;
		if(( cur->type == XML_ELEMENT_NODE) && (prefix != 0) && (!strcmp("xf",(char *)prefix)) && (cur->extra != 4 )){
		//1. make this node
		type = sXmlNodeName(cur);
		AllocateMemoryToNode(&temp);
			if( temp != 0 ){
				temp->type=type;
				temp->value=sAppendString(temp->value,sGetValueFromChildren(cur,(char *)"xf:value")); // search for xf:value in children of this node
				temp->hint=sAppendString(temp->hint,sGetValueFromChildren(cur,(char *)"xf:hint"));  // xf:hint
				temp->help=sAppendString(temp->help,sGetValueFromChildren(cur,(char *)"xf:help"));  // xf:help
				tempc = sGetValueFromChildren(cur,(char *)"xf:label");
				////fprintf(stdout,"\n ****** tempc = %s",tempc);
				temp->name = sAppendString(temp->name,tempc);  //xf:label
				//temp->attr=0;  //attributes
				//fprintf(stdout,"\n### %s : %s #####",temp->type,temp->name);
			}
			else{
				//fprintf(stdout,"\ncould not allocate memory for %s",type);
				exit(1);
			}
		
			//2. adjust pointers
			temp->par = *par;
			temp->child = (sXformsNode *)0;
			sAdjustPointersForLinkedList(par, &temp);
			//temp->prev = (sXformsNode *)0; //TODO
			//temp->next = (sXformsNode *)0; //TODO
			//3. make an attributes list
			if( cur->properties){
				temp->attr = MakeAttributesList(cur);
			}
			//4. mark this node as visited
			cur->extra = 4;
			
		}
	sParseNodesAndMakeTree(cur->children,&temp, head);
	cur = cur->next;
	}
}

void sAdjustPointersForLinkedList(sXformsNode **par, sXformsNode **child)
{
	//fprintf(stdout,"\n== (%s,%s)->(%s,%s)",(*par)->type,(*par)->name,(*child)->type,(*child)->name);
	sXformsNode *temp = (*par)->child;
	sXformsNode *next = 0;
	if ( temp == 0){
		// first child
		(*child)->next = 0;
		(*child)->prev = 0;
		(*par)->child = (*child);
	}
	else{
		//fprintf(stdout,"\n");
		while( temp->next != 0){
			//fprintf(stdout,"\t== (%s,%s)",temp->type,temp->name);
			temp=temp->next;
		}
		//fprintf(stdout,"\n");
		(*child)->next = 0;
		(*child)->prev=temp;
		temp -> next = (*child);
	}
}

char * sGetValueFromChildren(xmlNodePtr cur, char *nodeToSearch)
{
	// traverse the child nodes and find matching one. then return corresponding value
	if( cur->children){
		xmlNodePtr child = cur->children;
		while(child){
			if((child->type=XML_ELEMENT_NODE) && (child->extra != 4)){
				if(!strcmp(nodeToSearch,sXmlNodeName(child))){
					// find the text node in this and then return it's content
					////fprintf(stdout,"\n^^ type = %s, name = %s, ns = %s, content = %s \n","child->type",sXmlNodeName(child),child->ns->prefix,(char *)child->content);
					child->extra = 4;
					return sGetTextFromNode(child);
					//return (char *)"found1";
					
				}
			}
		child = child->next;
		}
	}
	return (char *)"NULL";
}

sXformsNodeAttr * MakeAttributesList(xmlNodePtr cur){
	if( cur-> properties){
		sXformsNodeAttr *head = (sXformsNodeAttr *)0;
		xmlAttr *attr = cur->properties;
		while(attr && attr->type == XML_ATTRIBUTE_NODE ){
			//fprintf(stdout,"\n ATTRIBUTE NAME = %s, and VALUE = %s",attr->name,xmlNodeListGetString(cur->doc,attr->children,1));
			sXformsNodeAttr *temp = (sXformsNodeAttr *)0;
			AllocateMemoryForAttribute(&temp);
			if(temp){
				temp->attrName = (char *)attr->name;
				temp->attrValue = (char *)xmlNodeListGetString(cur->doc,attr->children,1);
			}
			else{
				fprintf(stdout,"\n Could not allocate memory");
				exit(1);
			}
			if(head == 0 ){
				head = temp;
			}
			else{
				sXformsNodeAttr *prev = head;
				while(prev->next){
					prev = prev->next;
				}
				prev->next = temp;
				temp->prev = prev;
			}
			attr = attr->next;
		}
		return head;
	}else{
		return (sXformsNodeAttr *)0;
	}
}


// inside element nodes, there are text nodes which contain the values, this returns the values of those text nodes
char * sGetTextFromNode(xmlNodePtr node)
{
	xmlNode *cur_node = 0;
	//  search upto 1 level of child nodes only, it is assumed that enclosing element node is passed
	for (cur_node = node->children; cur_node; cur_node = cur_node->next) {
		if ( cur_node->type ==  XML_TEXT_NODE ) {
           		 //fprintf(stdout,"\n^^**^^ %s, %s", cur_node->name,cur_node->content);
           		 if((cur_node->content[0] != '\n') || (cur_node->content[0] != '\t')){
           		 	return (char *)cur_node->content;
           		 	
           		 }
        	}
	}
}

char * sAppendString( char *src, char *text)
{
	int text_len , text_ctr = 0;
	int src_len, src_ctr = 0;
	if( src == 0){
		src_len = 0;
	}
	else {
		src_len = strlen(src);
	}
	if( text == 0){
		text_len = 0;
	}
	else {
		text_len = strlen(text);
	}
	
	//allocate new memory block and free previous one
	char *temp = (char *)malloc(sizeof(char)*(text_len + src_len + 1));
	int c = 0;
	if( src ){
		while( src[src_ctr] != '\0'){
			temp[c++] = src[src_ctr++];
		}
	free(src);
	}
	if( text ){
		while( text[text_ctr] != '\0' ){
			temp[c++] = text[text_ctr++];
		}
	}
	
	temp[c] = '\0';
	//fprintf(stdout,"\n--- received : %s,%s returned %s----",src,text,temp);
	return temp;
}

// returns ns + ":" + name
char * sXmlNodeName(xmlNodePtr cur)
{
	char *name = 0;
	const xmlChar *prefix = ( cur->ns && cur->ns->prefix ) ? cur->ns->prefix : 0;
	if( prefix )
	{
		char *p = (char *)prefix;
		name = sAppendString(name,p);
		name = sAppendString(name,(char *)":");
	}
	if(cur->name != 0){
		name = sAppendString(name,(char *)cur->name);
	}
	if( name == 0){
		return (char *)"NULL2";
	}
	else{
		return name;
	}
	//fprintf(stdout,"\n\n === %s === ",name);
}
