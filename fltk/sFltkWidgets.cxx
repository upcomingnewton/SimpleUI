#include "sFltk.h"
#include "../simpleUI.h"
#include "../sXforms.h"
	#include <FL/Fl.H>
	#include <FL/Fl_Button.H>
	#include <FL/Fl_Double_Window.H>
	#include <FL/Fl_Pack.H>
	#include <FL/Fl_Scroll.H>
	#include <FL/Fl_Text_Display.H>
	#include <FL/Fl_Help_View.H>
	#include <FL/Fl_Choice.H>
	#include <FL/Fl_Input.H>



struct sFltkUIHandler_s fltk_handlers[] = {
	{
		(char *)"xf:select1",
  		(char *)"xf-select1-handler",
  		(char *)0,
  		(char *)0,
  		(sFltkUIHandler_f)sFltkUIHandler_f_Select1Handler
	},
	{
		(char *)"xf:input",
  		(char *)"xf-input",
  		(char *)0,
  		(char *)0,
  		(sFltkUIHandler_f)sFltkUIHandler_f_InputHandler
	},
	{
		(char *)"xf:group",
		(char *)"xf-group-tabs-handler",
		(char *)"type",
		(char *)"tabs",
		(sFltkUIHandler_f)sFltkUIHandler_f_TabsHandler
	},
	{
		(char *)0,
  		(char *)0,
  		(char *)0,
  		(char *)0,
  		(sFltkUIHandler_f)0
	}
};

void test_widgets(){
	Fl_Group *parent = Fl_Group::current();
	if(!parent){
		fprintf(stdout,"could not find parent");
	}
	else{
		fprintf(stdout,"declared");
		
		Fl_Choice  *f = new Fl_Choice(parent->x(),parent->y(),parent->w(),30,"choice");
		f->add("one");
		f->add("two");
		f->add("three");
	}
}


int sGenerateUIFromTree(sXformsNode * head)
{
	//fprintf(stdout,"\n === PRINTING NODE TREE ===");
	static int y = 0;
	int x = 0,
	    //y = 0,
	    w = 0,
	    h = 0;
	    Fl_Group *parent = Fl_Group::current();
	    x = parent->x();
	    //y = parent->y();
	    w = parent->w();
	    h = 10;
	if( head == 0 ){
		fprintf(stdout,"\n Head node passed is null");
		return 1;
	}
	else{
		sXformsNode *temp ;
		for( temp = head->child;(( temp != 0 ) ) ; temp=temp->next){
			// process this node
			// find corresponding handler 
			if( temp->meta_info && !strcmp(temp->meta_info,"1")){
				continue;
			}
			x = 0;
			// 1. if it has attributes then try finding the handler having same type and attributes
			// 2  else use default handler
			fprintf(stdout,"\n==========================================================");
			fprintf(stdout,"\n\t%s,",temp->type);
				//fprintf(stdout,"\n\t%s,%s,%s,%s",temp->type,temp->name,temp->attr->attrName,temp->attr->attrValue);
			fprintf(stdout,"\n------------------------------------------------------------");
			if(temp->attr){
				while(fltk_handlers[x].type != 0){
				fprintf(stdout,"\n%s,%s,%s",fltk_handlers[x].type,fltk_handlers[x].attrname,fltk_handlers[x].attrvalue);
				fprintf(stdout,"\n++++++++++++++++++++++++++++++++++++++++++++++++++");
				if( !strcmp(temp->type,fltk_handlers[x].type)){
					sXformsNodeAttr *tempattr;
					for( tempattr = temp->attr; tempattr; tempattr=tempattr->next){
						if( (fltk_handlers[x].attrname) && (fltk_handlers[x].attrvalue) && ( !strcmp(tempattr->attrName,fltk_handlers[x].attrname) && !strcmp(tempattr->attrValue,fltk_handlers[x].attrvalue))){
							//handle
							fprintf(stdout,"\n ==** MATCHED **==");
							fltk_handlers[x].handler(temp,x,y,w,h);
							temp->meta_info = (char *)"1"; // node visited
							y = y + 30;
							break;
						}
					}
				}
				if(!(temp->meta_info)){
					x++;
				}else{
					break;
				}
				}
			}
			
			if(!(temp->meta_info)){
				x = 0;
				while(fltk_handlers[x].type != 0){
				fprintf(stdout,"\n==========================================================");
				//sPrintsXformsNode(temp);
				if( !strcmp(temp->type,fltk_handlers[x].type)){
					fltk_handlers[x].handler(temp,x,y,w,h);
					temp->meta_info = (char *)"1"; // node visited
					y = y + 30;
					break;
				}
				x++;
				}
			}
			
			//fprintf(stdout,"\n\t %s : %s",temp->type,temp->name);
			//sPrintsXformsNode(temp);
			#if 1
			//fprintf(stdout,"\n\t\t--temp->child %u,%s ---",temp->child,temp->child->type);
			if( temp->child == 0){
				continue;
			}else{
				//fprintf(stdout,"\n\t------------- chilren -------------\n");
				sGenerateUIFromTree(temp);
				//fprintf(stdout,"\n\t------------- chilren end -------------\n");
			}
			#endif
			}
		}
	}


int sFltkUIHandler_f_Select1Handler(sXformsNode *head,int x, int y, int w, int h){
	fprintf(stdout,"janemann , called this function , lol\n");
	//test_widgets();
	return 0;
}

int sFltkUIHandler_f_InputHandler(sXformsNode *head,int x, int y, int w, int h){
	Fl_Group *parent = Fl_Group::current();
	if(!parent){
		fprintf(stdout,"could not find parent");
	}
	else{
		fprintf(stdout,"declared");
		
		Fl_Input  *f = new Fl_Input(parent->x(),y + V_SPACING,parent->w(),90,head->name);
	}
}


int sFltkUIHandler_f_TabsHandler(sXformsNode *head,int x, int y, int w, int h){
//	1. FIND xf:group
	
	
//	2. PARSE THE SUB-TREE TO FIND XF:TOGGLE ELEMENTS AND MAKE TABS OF THEM
//	3. FIND CORRESPONDING xf:case IN NEXT XF:GROUP AND MAKE A TREE OF THEM 
//	4. CLOSE 
	sXformsNodeAttr xf_trigger_attr = {"type","tab_trigger",(char *)0,(char *)0,(sXformsNodeAttr *)0,(sXformsNodeAttr *)0};
	
	//sXformsNodeAttr xf_toggle_attr = {
	//			{"","tab_trigger",(char *)0,(char *)0,(sXformsNodeAttr *)0,(sXformsNodeAttr *)0};
	sXformsNode *xftrigger = SearchSubTreeForNodes(head,(char *)"xf:trigger",&xf_trigger_attr,0,1);
	while( xftrigger != 0){
		fprintf(stdout,"\n****** TAB NAME = %s",xftrigger->name);
		// search for xf:toggle inside this
		sXformsNode * toggle = SearchSubTreeForNodes(xftrigger,(char *)"xf:toggle",(sXformsNodeAttr *)0,0,0);
		if(toggle != 0){
			fprintf(stdout,"\n****** TAB NAME = %s",toggle->attr->attrName);
			toggle->meta_info = (char *)"1";
			for(sXformsNodeAttr *attr = toggle->attr; attr; attr=attr->next){
				if(!strcmp(attr->attrName,"case")){
					sXformsNodeAttr xf_case_attr = {"id",attr->attrValue,(char *)0,(char *)0,(sXformsNodeAttr *)0,(sXformsNodeAttr *)0};
					sXformsNode *tab_content = SearchSubTreeForNodes(head->par,(char *)"xf:case",&xf_case_attr,1,1);
					if(tab_content != 0){
						fprintf(stdout,"\n +++++++++++++++++++++++++++++++++++++++++++++GOT THE CHILD ");
						tab_content->meta_info = (char *)"1";
						MarkChildElementsAsVisited(tab_content);
					}
				}
			}
			// get the attribute case and it's value and make that tree
			
		}else{
			// error
			fprintf(stdout,"\nERROR MAKING TABS");
			exit(1);
		}
		xftrigger->meta_info = (char *)"1";
		xftrigger  =  SearchSubTreeForNodes(head,(char *)"xf:trigger",&xf_trigger_attr,0,1);
	}
	return 0;
}

void MarkChildElementsAsVisited(sXformsNode *node){
	for(sXformsNode * temp = node->child; temp; temp = temp->next){
		temp->meta_info = (char *)"1";
		if( temp->child){
			MarkChildElementsAsVisited(temp);
		}
	}
}
