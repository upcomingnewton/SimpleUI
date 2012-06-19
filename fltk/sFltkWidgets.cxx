#include "sFltk.h"
#include "../simpleUI.h"
#include "../sXforms.h"
	#include <FL/Fl.H>
	#include <FL/Fl_Button.H>
	#include <FL/Fl_Double_Window.H>
	#include <FL/Fl_Pack.H>
	#include <FL/Fl_Scroll.H>
	#include <FL/Fl_Text_Buffer.H>
	#include <FL/Fl_Text_Display.H>
	#include <FL/Fl_Help_View.H>
	#include <FL/Fl_Choice.H>
	#include <FL/Fl_Input.H>
	#include <FL/Fl_Widget.H>
	#include <FL/Fl_Tabs.H>
	#include <FL/Fl_Value_Slider.H>
	#include <FL/Fl_Check_Button.H>
	#include<FL/Fl_Box.H>
	#include <FL/Fl_Round_Button.H>
	#include <FL/Fl_Button.H>
//	#include <FL/Fl_Color.H>
	
	#include "../xml/sXml.h"
#define EnableLog
#ifdef EnableLog
#define WriteLog fprintf
#else
#define WriteLog
#endif

int CalculateYPosition(Fl_Group *p);

struct sFltkUIHandler_s fltk_handlers[] = {
	{
		(char *)"xf:select1",
  		(char *)"drop downs",
  		(char *)0,
  		(char *)0,
  		0,
  		(sFltkUIHandler_f)sFltkUIHandler_f_Select1Handler
	},
	{
		(char *)"xf:select1",
  		(char *)"radio button list",
		(char *)"appearance",
		(char *)"full",
		1,
  		(sFltkUIHandler_f)sFltkUIHandler_f_RadioButtonList
	},
	{
		(char *)"xf:select",
		(char *)"check box list",
		(char *)"appearance",
		(char *)"full",
		1,
		(sFltkUIHandler_f)sFltkUIHandler_f_CheckBoxList
	},
	{
		(char *)"xf:input",
  		(char *)"xf-input",
  		(char *)0,
  		(char *)0,
  		0, // generic for now
  		(sFltkUIHandler_f)sFltkUIHandler_f_InputHandler
	},
	{
		(char *)"xf:output",
  		(char *)"xf-output",
  		(char *)0,
  		(char *)0,
  		0, // generic for now
  		(sFltkUIHandler_f)sFltkUIHandler_f_LabelHandler
	},
	{
		(char *)"xf:trigger",
  		(char *)"xf-button",
  		(char *)0,
  		(char *)0,
  		1,
  		(sFltkUIHandler_f)sFltkUIHandler_f_ButtonHandler
	},
	{
		(char *)"xf:group",
		(char *)"xf-group-tabs-handler",
		(char *)"type",
		(char *)"tabs",
		0,
		(sFltkUIHandler_f)sFltkUIHandler_f_TabsHandler
	},
		{
		(char *)"xf:group",
		(char *)"start a new frame or a box",
		(char *)"type",
		(char *)"frame",
		1,
		(sFltkUIHandler_f)sFltkUIHandler_f_FrameHandler
	},
	{
		(char *)"xf:range",
		(char *)"xf-sliders",
		(char *)0,
		(char *)0,
		1,
		(sFltkUIHandler_f)sFltkUIHandler_f_RangeHandler
	},
	{
		(char *)"xf:repeat",
		(char *)"xf-repeat-handlers",
		(char *)0,
		(char *)0,
		1,
		(sFltkUIHandler_f)sFltkUIHandler_f_TableHandler
	},

	{
		(char *)0,
  		(char *)0,
  		(char *)0,
  		(char *)0,
  		1,
  		(sFltkUIHandler_f)0
	}
};


void print_label(Fl_Widget *s, const char *text){
	WriteLog(stdout,"\n[%s][%d] %s : %s",__FILE__,__LINE__,__func__,text,s->label());
}


int sGenerateUIFromTree(sXformsNode * head)
{
	static int _y = 0;
	int height = 0;
	int _x = 0,
	    _w = 0,
	    x = 0,
	    _h = 0;
	    Fl_Group *parent = Fl_Group::current();
	    _x = parent->x() + HOR_SEP;
	    _y = parent->y() + VER_SEP;
	    _w = parent->w() - 2*HOR_SEP;
	    _h = parent->h() - 2*VER_SEP;
	if( head == 0 ){
		return 1;
	}
	else{
		sXformsNode *temp ;
		for( temp = head->child;(( temp != 0 ) ) ; temp=temp->next){
			if( temp->meta_info && !strcmp(temp->meta_info,"1")){
				continue;
			}
			x = 0;
			if(temp->attr){
				while(fltk_handlers[x].type != 0){
				if( !strcmp(temp->type,fltk_handlers[x].type)){
					sXformsNodeAttr *tempattr;
					for( tempattr = temp->attr; tempattr; tempattr=tempattr->next){
						if( (fltk_handlers[x].attrname) && (fltk_handlers[x].attrvalue) && ( !strcmp(tempattr->attrName,fltk_handlers[x].attrname) && !strcmp(tempattr->attrValue,fltk_handlers[x].attrvalue))){
							//handle
							WriteLog(stdout,"\n[%s][%d] %s start 'specialised' %s:%s",__func__,__LINE__,parent->label(),temp->type,temp->name);
							height = fltk_handlers[x].handler(temp,_x,_y,_w,_h);
							WriteLog(stdout,"\n[%s][%d] %s end",__func__,__LINE__,parent->label());
							temp->meta_info = (char *)"1"; // node visited
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
				if( !strcmp(temp->type,fltk_handlers[x].type) && !fltk_handlers[x].strict){
					WriteLog(stdout,"\n[%s][%d] %s start 'generic' %s:%s",__func__,__LINE__,parent->label(),temp->type,temp->name);
					height = fltk_handlers[x].handler(temp,_x,_y,_w,_h);
					WriteLog(stdout,"\n[%s][%d] %s end",__func__,__LINE__,parent->label());
					temp->meta_info = (char *)"1"; // node visited
					//break;
				}
				x++;
				}
			}
			if( temp->child == 0){
				continue;
			}else{
				sGenerateUIFromTree(temp);
			}}
		}
	return 0;
}

int sFltkUIHandler_f_TabsHandler(sXformsNode *head,int x, int y, int w, int h){
	Fl_Group *parent = Fl_Group::current();
	if( !parent){
		return -1;
	}
	WriteLog(stdout,"\n[%s][%d] parent = %s, dimensions of parent are (%d,%d,%d,%d)",__func__,__LINE__,parent->label(),parent->x(),parent->y(),parent->w(),parent->h());
	int height = 0;
	Fl_Group * tabsgroup;
	Fl_Tabs *tabs;
	head -> meta_info = (char *)"1";
	sXformsNodeAttr xf_trigger_attr = {"type","tab_trigger",(char *)0,(char *)0,(sXformsNodeAttr *)0,(sXformsNodeAttr *)0};
	int flag_t = 1;
	sXformsNode *xftrigger = SearchSubTreeForNodes(head,(char *)"xf:trigger",&xf_trigger_attr,0,1);
	if( xftrigger != 0){
		tabsgroup = new Fl_Group(parent->x(),parent->y(),parent->w(),parent->h(),"tabsgroup");
		tabsgroup->begin();
		tabs = new Fl_Tabs(parent->x(),parent->y(),parent->w(),parent->h(),"tabs");
	
	while( xftrigger != 0){
		
		flag_t = 0;
		// search for xf:toggle inside this
		sXformsNode * toggle = SearchSubTreeForNodes(xftrigger,(char *)"xf:toggle",(sXformsNodeAttr *)0,0,0);
		if(toggle != 0){
			toggle->meta_info = (char *)"1";
			for(sXformsNodeAttr *attr = toggle->attr; attr; attr=attr->next){
				if(!strcmp(attr->attrName,"case")){
					sXformsNodeAttr xf_case_attr = {"id",attr->attrValue,(char *)0,(char *)0,(sXformsNodeAttr *)0,(sXformsNodeAttr *)0};
					sXformsNode *tab_content = SearchSubTreeForNodes(head->par,(char *)"xf:case",&xf_case_attr,1,1);
					if(tab_content != 0){
						
						tab_content->meta_info = (char *)"1";
						tabs->begin();
						Fl_Group *new_group = new Fl_Group(tabs->x(),tabs->y() + TAB_HEIGHT,tabs->w(),tabs->h()-TAB_HEIGHT - VER_SEP,xftrigger->name);
						new_group->begin();
						{
						char *s = "pack_";
						s = sAppendString(s,xftrigger->name);
						//Fl_Pack *tabs_content_pack = new Fl_Pack(new_group->x() + HOR_SEP,new_group->y() + VER_SEP,new_group->w() - 2*HOR_SEP,new_group->h() - 2*VER_SEP,s);{
							//tabs_content_pack->color(FL_RED);
							//tabs_content_pack->begin();
							sGenerateUIFromTree(tab_content);
						//}
						//tabs_content_pack->end();
						}
						new_group->end();
						tabs->end();
					}
				}
			}
		}else{
			WriteLog(stdout,"\n[%s][%d]ERROR MAKING TABS",__FILE__,__LINE__);
			exit(1);
		}
		xftrigger->meta_info = (char *)"1";
		xftrigger  =  SearchSubTreeForNodes(head,(char *)"xf:trigger",&xf_trigger_attr,0,1);
	}
	tabsgroup->end();
	return tabsgroup->h();
	}
	else{
		return 0;
	}
}

void MarkChildElementsAsVisited(sXformsNode *node){
	for(sXformsNode * temp = node->child; temp; temp = temp->next){
		temp->meta_info = (char *)"1";
		if( temp->child){
			MarkChildElementsAsVisited(temp);
		}
	}
}


// HELPER FUNCTION
/* ========================================================================================== */
int CalculateYPosition(Fl_Group *p){
	int height = 0;
	Fl_Widget *temp;
	if(p->children()){
		for( int i = 0; i < p->children(); i++){
			temp = p->child(i);
			height += temp->h();
		}
	}
	return height;
}
/* ========================================================================================== */

int sFltkUIHandler_f_Select1Handler(sXformsNode *head,int x, int y, int w, int h){
	Fl_Group *parent = Fl_Group::current();
	head->meta_info = (char *)"1";
	if(!parent){
		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
		return -1;
	}
	else{
		WriteLog(stdout,"\n[%s][%d] parent = %s, dimensions of parent are (%d,%d,%d,%d)",__func__,__LINE__,parent->label(),parent->x(),parent->y(),parent->w(),parent->h());
		parent->begin();
		Fl_Group *dropdowngroup = new Fl_Group(parent->x() + HOR_SEP, parent->y() + CalculateYPosition(parent) + VER_SEP , w - 2*HOR_SEP, ROW_HEIGHT + 2*VER_SEP,"dropdowngroup");
		WriteLog(stdout,"\n[%s][%d] parent = %s, dimensions of parent are (%d,%d,%d,%d)",__func__,__LINE__,dropdowngroup->label(),dropdowngroup->x(),dropdowngroup->y(),dropdowngroup->w(),dropdowngroup->h());
		dropdowngroup->color(FL_RED);
		dropdowngroup->box(FL_BORDER_BOX);
//		dropdowngroup->begin();
//				Fl_Choice  *f = new Fl_Choice(dropdowngroup->x() + HOR_SEP,dropdowngroup->y() + VER_SEP,dropdowngroup->w() - 2*HOR_SEP,ROW_HEIGHT,head->name);
//				// parse children here
//				sXformsNode *xfitem = SearchSubTreeForNodes(head,(char *)"xf:item",(sXformsNodeAttr *)0,1,0);
//				while(xfitem){
//					// add item to drop downs
//					f->add(xfitem->name);
//					xfitem->meta_info = (char *)"1";
//					xfitem = SearchSubTreeForNodes(head,(char *)"xf:item",(sXformsNodeAttr *)0,1,0);
//				}
		dropdowngroup->end();
		dropdowngroup->redraw();
		parent->redraw();
		return dropdowngroup->h();
	}
}

int sFltkUIHandler_f_InputHandler(sXformsNode *head,int x, int y, int w, int h){
//	Fl_Group *parent = Fl_Group::current();
//	CalculateYPosition(parent);
//	head->meta_info = (char *)"1";
//	if(!parent){
//		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
//	}
//	else{
//		Fl_Group *inputgroup = new Fl_Group(parent->x(),parent->y() + CalculateYPosition(parent) + VER_SEP,parent->w(),(ROW_HEIGHT + 2*VER_SEP),"inputgroup");
//		inputgroup->begin();
//		Fl_Input  *f = new Fl_Input(inputgroup->x() + HOR_SEP,inputgroup->y() + VER_SEP,parent->w() - 2*HOR_SEP,ROW_HEIGHT,head->name);
//		inputgroup->end();
//		return inputgroup->h();
//	}
//	return 0;
}

int sFltkUIHandler_f_RangeHandler(sXformsNode *head,int x, int y, int w, int h){
//	Fl_Group *parent = Fl_Group::current();
//	head->meta_info = (char *)"1";
//	if(!parent){
//		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
//	}
//	else{
//		Fl_Group *slidergroup = new Fl_Group(parent->x(),parent->y(),parent->w(),(ROW_HEIGHT + 2*VER_SEP),"slidergroup");
//		Fl_Value_Slider *slider;
//		int *start = 0;
//		int *end = 0;
//		int *step = 0;
//		slider = new Fl_Value_Slider(slidergroup->x() + HOR_SEP,slidergroup->y() + VER_SEP,slidergroup->w() - 2*HOR_SEP,ROW_HEIGHT,head->name);
//		slider->type(FL_HORIZONTAL);
//		start = (int *)getAttrValueFromList(head,"start");
//		end = (int *)getAttrValueFromList(head,"end");
//		step = (int *)getAttrValueFromList(head,"step");
//		slider->bounds((double)(*start),(double)(*end));
//		slidergroup->end();
//		return slidergroup->h();
//	}
//	return 0;
}



int sFltkUIHandler_f_TableHandler(sXformsNode *head,int x, int y, int w, int h){
	//xmlXPathObjectPtr r  = sGetXpathValue("nodeset", xmlDocPtr doc)
	return 0;
}


int sFltkUIHandler_f_RadioButtonList(sXformsNode *head,int x, int y, int w, int h){
//	Fl_Group *parent = Fl_Group::current();
//	int height = VER_SEP + ROW_HEIGHT;
//	head->meta_info = (char *)"1"; 
//	if(!parent){
//		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
//	}
//	
//	else{
//		sXformsNode *temp;
//		int ctr = 0;
//		sXformsNode *xfchoices = SearchSubTreeForNodes(head,(char *)"xf:choices",(sXformsNodeAttr *)0,0,0);
//		if( xfchoices ){
//			xfchoices->meta_info = (char *)"1";
//			Fl_Group *RadioButtonListGroup = new Fl_Group(x,y,w,height);
//			RadioButtonListGroup->begin();
//			{

//				for( temp=xfchoices->child; temp != 0; temp=temp->next, ctr++){
//					height += sGenerateUIFromTree(temp);
//				}
//			}
//			RadioButtonListGroup->size(RadioButtonListGroup->w(),height);
//			RadioButtonListGroup->end();
//		}
//	}
}



int sFltkUIHandler_f_CheckBoxList(sXformsNode *head,int x, int y, int w, int h){
//	Fl_Group *parent = Fl_Group::current();
//	int height = parent->y();
//	if( parent->children() == 0){
//		height += TAB_HEIGHT;
//	}
//	head->meta_info = (char *)"1"; 
//	if(!parent){
//		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
//	}
//	
//	else{
//		sXformsNode *temp;
//		int ctr = 0;
//		height += 1*VER_SEP;
//		Fl_Box *CheckBoxListBox = new Fl_Box(x+HOR_SEP,height,parent->w() - 2*HOR_SEP,h,head->name);
//		CheckBoxListBox->box(FL_BORDER_BOX);
//		{
//			for( temp=head->child; temp != 0; temp=temp->next, ctr++){
//				height += VER_SEP;
//				Fl_Check_Button *btn = new Fl_Check_Button(CheckBoxListBox->x() + HOR_SEP,height ,CheckBoxListBox->w() - HOR_SEP,ROW_HEIGHT,temp->name);
//				height += ROW_HEIGHT;
//				temp->meta_info = (char *)"1";
//			}
//		}
//		height += VER_SEP;
//		CheckBoxListBox->size(CheckBoxListBox->w(),height);
//	}
//	return 0;
}


int sFltkUIHandler_f_ButtonHandler(sXformsNode *head,int x, int y, int w, int h){
//	Fl_Group *parent = Fl_Group::current();
//	head->meta_info = (char *)"1"; 
//	if(!parent){
//		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
//	}
//	
//	else{
//		sXformsNode *temp;
//		int ctr = 0;
//		Fl_Group *ButtonGroup = new Fl_Group(x,y,w,4*ROW_HEIGHT);
//		{
//			//Fl_Box *RadioListBox = new Fl_Box(x+HOR_SEP,y,parent->w() - 2*HOR_SEP,4*ROW_HEIGHT,head->name);
//			ButtonGroup->box(FL_BORDER_BOX);
//			{
//				Fl_Button *btn = new Fl_Button(x,y,w,ROW_HEIGHT,head->name);
//			}
//		}
//		//RadioListBox->size(RadioListBox->w(),height);
//	}
}

int sFltkUIHandler_f_FrameHandler(sXformsNode *head,int x, int y, int w, int h){
	Fl_Group *parent = Fl_Group::current();
	int height = 0;
	head -> meta_info = (char *)"1";
	if(parent){
		WriteLog(stdout,"\n[%s][%d] parent = %s, dimensions of parent are (%d,%d,%d,%d)",__func__,__LINE__,parent->label(),parent->x(),parent->y(),parent->w(),parent->h());
		char *s = "new_frame_";
		s = sAppendString(s,head->name);
		height = CalculateYPosition(parent);
		//WriteLog(stdout,"\n[%s][%d] height = %d, before making a sep",__func__,__LINE__,height);
		Fl_Group *sep_group = new Fl_Group(parent->x(),parent->y() + height ,parent->w(),ROW_HEIGHT,"");
		sep_group->end();
		height = CalculateYPosition(parent);
		//WriteLog(stdout,"\n[%s][%d] height = %d, after making a sep",__func__,__LINE__,height);
		Fl_Group *new_frame = new Fl_Group(parent->x(),parent->y() + height ,parent->w(),parent->h() - 2*VER_SEP,s);
		new_frame->color(FL_YELLOW);
		new_frame->labelcolor(FL_RED);
		new_frame->begin();
			sGenerateUIFromTree(head);
			//Fl_Group *child_dummy_grp = new Fl_Group(new_frame->x() + HOR_SEP,new_frame->y() + VER_SEP,new_frame->w() - 2*HOR_SEP,ROW_HEIGHT*4,"");
			//MarkChildElementsAsVisited(head);
		new_frame->end();
		height = CalculateYPosition(new_frame);
		height += 2*VER_SEP;
		WriteLog(stdout,"\n[%s][%d] Resizing, height = %d",__func__,__LINE__,height);
		new_frame->size(new_frame->w(),height);
		new_frame->box(FL_BORDER_BOX);
		return new_frame->h();
	}else{
		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
		return -1;
	}
}


int sFltkUIHandler_f_LabelHandler(sXformsNode *head,int x, int y, int w, int h){
	Fl_Group *parent = Fl_Group::current();
	int height = 0;
	head -> meta_info = (char *)"1";
	if(parent){
		WriteLog(stdout,"\n[%s][%d] parent = %s, dimensions of parent are (%d,%d,%d,%d)",__func__,__LINE__,parent->label(),parent->x(),parent->y(),parent->w(),parent->h());
		height = CalculateYPosition(parent);
		if( height == 0 ){
			height = VER_SEP;
		}
		Fl_Group *outputgroup = new Fl_Group(parent->x() + HOR_SEP,parent->y() + height ,parent->w() - 2*HOR_SEP,2*ROW_HEIGHT + 2*VER_SEP,"");
		outputgroup->begin();
			
		outputgroup->end();
		return outputgroup->h();
	}else{
		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
		return -1;
	}
}