#include "sXml.h"
#include "../simpleUI.h"
#include "../sXforms.h"
#include <libxml/parser.h>
#include <string.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

//struct sXformsNode *ParseXformsToTree(const char * xforms){
void print_xpath_nodes(xmlNodeSetPtr nodes, FILE* output);
char *getInstanceXpath(sXformsNodeAttr *attr,xmlDocPtr doc);
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
			sParseNodesAndMakeTree(cur,&head,head,doc);
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
	sPrintsXformsTree(head);
	//xmlXPathObjectPtr result = sGetXpathObjectPtr((),doc);
	//fprintf(stdout,"======/// %s ///=======",sGetXpathValue("/xmlns:html/xmlns:head/xf:model/xf:instance[@id='app_personal_info']/app_personal_info/prefix",doc));
	return head;
}

void sParseNodesAndMakeTree(xmlNodePtr cur,sXformsNode **par, sXformsNode * head, xmlDocPtr doc)
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
				temp->attr = MakeAttributesList(cur,doc);
			}
			//4. mark this node as visited
			cur->extra = 4;
			if ( !strcmp("xf:model",type))
				makemodel(cur,&temp,1);
	}
	sParseNodesAndMakeTree(cur->children,&temp, head,doc);
	cur = cur->next;
	}
}

void makemodel(xmlNodePtr cur,sXformsNode **par, int pos){
	fprintf(stdout,"\n");
	
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

sXformsNodeAttr * MakeAttributesList(xmlNodePtr cur,xmlDocPtr doc ){
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
			if( !strcmp(temp->attrName,"ref")){
				temp->meta_info = sAppendString(temp->meta_info,sGetXpathFromRefAttr(temp,doc));
				xmlNodeSetPtr  xfinstance = sGetXpathValue(temp->meta_info,doc);
				temp->private_data = sAppendString(temp->private_data, EvalNodeSetPtrForInstannce(xfinstance));
				fprintf(stdout,"\n%s : %s",temp->meta_info,temp->private_data);
			}
			if( !strcmp(temp->attrName,"nodeset")){
				temp->meta_info = sGetXpathFromNodeSetAttr(temp);
			}
			attr = attr->next;
		}
		//sPrintsXformsAttrList(head);
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
	//free(src);
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


xmlXPathContextPtr sGetXpathEvalContext(xmlDocPtr doc)
{
	xmlXPathContextPtr context = xmlXPathNewContext( doc );
	char *ref;
	char *url;
	int error = 0;
	ref = "xmlns";
	url = "http://www.w3.org/1999/xhtml";
	error = xmlXPathRegisterNs( context, (xmlChar*)ref, (xmlChar*)url);
	if(error){
		printf("Could not register %s=%s\n", ref, url);
		return context;
	}
	ref = "xf";
	url = "http://www.w3.org/2002/xforms";
	error = xmlXPathRegisterNs( context, (xmlChar*)ref, (xmlChar*)url);
	if(error){
		printf("Could not register %s=%s\n", ref, url);
		return context;
	}
	ref = "ev";
	url = "http://www.w3.org/2001/xml-events";
	error = xmlXPathRegisterNs( context, (xmlChar*)ref, (xmlChar*)url);
	if(error){
		printf("Could not register %s=%s\n", ref, url);
		return context;
	}
	ref = "xsd";
	url = "http://www.w3.org/2001/XMLSchema";
	error = xmlXPathRegisterNs( context, (xmlChar*)ref, (xmlChar*)url);
	if(error){
		printf("Could not register %s=%s\n", ref, url);
		return context;
	}
	return context;
}

xmlNodeSetPtr sGetXpathValue(char *reference, xmlDocPtr doc){
	xmlXPathContextPtr context;  
	xmlXPathObjectPtr result = 0;
	char * text = 0;
  if( reference )
  {
	context = sGetXpathEvalContext(doc);
	result = xmlXPathEvalExpression( (xmlChar*)reference, context );
	if( result !=  NULL)
	{
		return result->nodesetval;
	}
	else return (xmlNodeSetPtr)0;
  }
  else return (xmlNodeSetPtr)0;
}
    
char * EvalNodeSetPtrForInstannce(xmlNodeSetPtr nodeset){
	xmlNodePtr cur;
	int numChild = nodeset ? nodeset->nodeNr : 0;
	//fprintf(stdout,"\n[%s][%d] ENTERED == %d ==",__func__,__LINE__,numChild);
	if( numChild == 1){
		//fprintf(stdout,"\n[%s][%d] %d : %s",__func__,__LINE__,nodeset->nodeTab[0]->type,"name");
		return (char *)nodeset->nodeTab[0]->children->content;
		//cur = cur->children;
		//return (char *)nodeset->nodeTab[0]->children->content;
		//fprintf(stdout,"\n[%s][%d] %d : %s",__func__,__LINE__,cur->type,cur->content);
	}
	else{
		return (char *)"-1";
	}
	//fprintf(stdout,"\n[%s][%d]",__func__,__LINE__);
	//fprintf(stdout,"\n[%s][%d] EXITING",__func__,__LINE__);
	return "Null";
}

    
    /* add the static part */
    //sprintf( xpath, "/xmlns:html/xmlns:head/xf:model/xf:instance" );

/*    STRING_ADD( xpath, reference );*/
/*    char *ref1 = "/xmlns:html/xmlns:head/xf:model/xf:instance";*/
/*    ref1 = sAppendString(ref1,reference);*/
/*    char *ref1 = "/xmlns:html/xmlns:head/xf:model/xf:instance[@id='app_personal_login']/loginform/username";*/
/*	*/
/*	*/
/*	print_xpath_nodes(result->nodesetval,stdout);*/
/*    if( result && !xmlXPathNodeSetIsEmpty( result->nodesetval ) &&*/
/*        result->nodesetval &&*/
/*        result->nodesetval->nodeTab && result->nodesetval->nodeTab[0] &&*/
/*        result->nodesetval->nodeTab[0]->children &&*/
/*        strcmp((char*)result->nodesetval->nodeTab[0]->children->name, "text") == 0 &&*/
/*        result->nodesetval->nodeTab[0]->children->content)*/
/*      text = (char*)result->nodesetval->nodeTab[0]->children->content;*/
/*    else*/
/*      printf( "\nNo result with %s", reference);*/

/*    xmlXPathFreeObject( result );*/
/*    xmlXPathFreeContext( context );*/
/*  }*/
/*  return text;*/
/*}*/



char *sGetXpathFromRefAttr(sXformsNodeAttr *attr,xmlDocPtr doc){
	char *xpath = "";
	if( !strcmp("ref",attr->attrName)){
		
		char *statref = "/xmlns:html/xmlns:head/xf:model/xf:instance";
		xpath = sAppendString(xpath,statref);
		if( CompareFirstNChars(attr->attrValue,0,"instance",0,strlen("instance")) == 1){
			xpath = getInstanceXpath(attr,doc);
		}
		char *p = strchr(attr->attrValue,'/');
		xpath = sAppendString(xpath,p);
		//fprintf(stdout,"\n[%s][%d]\t %s",__func__,__LINE__,xpath);
	}
	
	return xpath;
}

char *getInstanceXpath(sXformsNodeAttr *attr,xmlDocPtr doc){
			int i1 = 0, i2 = 0, firstocc = 0, vallen = 0;
			char *statxpath = "/xmlns:html/xmlns:head/xf:model/xf:instance";
			vallen = strlen(attr->attrValue) + 1;
			char *dupval = (char *)malloc(vallen*sizeof(char));
			strcpy(dupval,attr->attrValue);
			for( i1 = 0; dupval[i1] != '\'';i1++);
			i1++;firstocc = i1;
			for( i2 = 0; dupval[i1] != '\'';i1++, i2++);
			char *id = "[@id=\'";// + enterid here + "\']";
			char *idval = (char *)malloc(sizeof(char)*(i2+1));
			for(i1 = 0; i1 < i2; i1++,firstocc++){
				idval[i1] = dupval[firstocc];
			}
			idval[i1] = '\0';
			id = sAppendString(id,idval);
			id = sAppendString(id,"\']/data");
			statxpath = sAppendString(statxpath,id);
			//fprintf(stdout,"\n[%s][%d] %s",__func__,__LINE__,statxpath);
			return statxpath;
			//xmlNodeSetPtr  xfinstance = sGetXpathValue(statxpath,doc);
			//EvalNodeSetPtrForInstannce(xfinstance);
}

char *sGetXpathFromNodeSetAttr(sXformsNodeAttr *attr){
	char *xpath = "";
/*	if( !strcmp("nodeset",attr->attrName)){*/
/*		char *xpath = "";*/
/*		char *statref = "/xmlns:html/xmlns:head/xf:model/xf:instance";*/
/*		xpath = sAppendString(xpath,statref);*/
/*		*/
/*		fprintf(stdout,"\n[%s][%d] %s\t %s",__func__,__LINE__,attr->attrValue,xpath);*/
/*	}*/
	
	return xpath;
}


int CompareFirstNChars(char *src1, int start1, char *src2, int start2, int n){
	int i = 0, x = 0;
	for(  x = 0; x < n; x++){
		if(src1[x + start1] != src2[x + start2]){
			return -1;
		}
	}
	return 1;
}

void
print_xpath_nodes(xmlNodeSetPtr nodes, FILE* output) {
    xmlNodePtr cur;
    int size;
    int i;
    
    //assert(output);
    size = (nodes) ? nodes->nodeNr : 0;
    
    fprintf(output, "Result (%d nodes):\n", size);
    for(i = 0; i < size; ++i) {
	//assert(nodes->nodeTab[i]);
	
	if(nodes->nodeTab[i]->type == XML_NAMESPACE_DECL) {
	    xmlNsPtr ns;
	    
	    ns = (xmlNsPtr)nodes->nodeTab[i];
	    cur = (xmlNodePtr)ns->next;
	    if(cur->ns) { 
	        fprintf(output, "= namespace \"%s\"=\"%s\" for node %s:%s\n", 
		    ns->prefix, ns->href, cur->ns->href, cur->name);
	    } else {
	        fprintf(output, "= namespace \"%s\"=\"%s\" for node %s\n", 
		    ns->prefix, ns->href, cur->name);
	    }
	} else if(nodes->nodeTab[i]->type == XML_ELEMENT_NODE) {
	    cur = nodes->nodeTab[i];   	    
	    if(cur->ns) { 
    	        fprintf(output, "= element node \"%s:%s\"\n", 
		    cur->ns->href, cur->name);
	    } else {
    	        fprintf(output, "= element node \"%s\"\n", 
		    cur->name);
	    }
	} else {
	    cur = nodes->nodeTab[i];    
	    fprintf(output, "= node \"%s\": type %d\n", cur->name, cur->type);
	}
    }
}

