#include "sFltk.h"
#include "../simpleUI.h"
#include "../sXforms.h"
#include "../sCallbackData/sCallbackData.h"
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
	#include <FL/Fl_Output.H>
//	#include <FL/Fl_Color.H>
#include "../misc/misc.h"
	
	#include "../xml/sXml.h"
//#define EnableLog
#ifdef EnableLog
#define WriteLog fWriteLog
#else
#define WriteLog
#endif

int CalculateYPosition(Fl_Group *p,char *s);
char *int2str[] = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"};
int lindex = 0;
char *InputName[10];
char *ActualName[10];

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
  		0,
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
		0,
		(sFltkUIHandler_f)sFltkUIHandler_f_RangeHandler
	},
	{
	    (char *)"xf:secret",
	    (char *)"password",
	    (char *)0,
	    (char *)0,
	    0,
	    (sFltkUIHandler_f)sFltkUIHandler_f_InputHandler
	},
	{
	    (char *)"xf:textarea",
	    (char *)"password",
	    (char *)0,
	    (char *)0,
	    0,
	    (sFltkUIHandler_f)sFltkUIHandler_f_InputHandler
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


struct sCbData * MainFunction(sXformsNode * head, xmlDoc *modelPtr,CallBackInterfaceFunction func )
{
    struct sCbData *temp = (struct sCbData *)0;
    sGenerateUIFromTree(head,&temp,modelPtr,func);
    return temp;
}

int sGenerateUIFromTree(sXformsNode * head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func )
{
  int x = 0;
	int height = 0;
	if( head == 0 ){
		return 1;
	}
	else{
	  Fl_Group *parent = Fl_Group::current();
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
							height = fltk_handlers[x].handler(temp,CallBackData,modelPtr,func);
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
					height = fltk_handlers[x].handler(temp,CallBackData,modelPtr,func);
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
				sGenerateUIFromTree(temp,CallBackData,modelPtr,func);
			}}
		}
	return 0;
}

int sFltkUIHandler_f_TabsHandler(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func ){
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
							sGenerateUIFromTree(tab_content,CallBackData,modelPtr,func);
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
int CalculateTreeChildre(sXformsNode *head)
{
    // since it is a frame , hence none of it's children would have been implemented till now
    sXformsNode * temp = head->child;
    int count = 0;
    for( count = 0;temp ;  temp=temp->next)
    {
      count = count + 1;
      if( !strcmp(temp->type,"xf:select1"))
      {
      // it can be a radio button group
        // check attributes for appearance == full
        sXformsNodeAttr *tempattr;
				for( tempattr = temp->attr; tempattr; tempattr=tempattr->next){
						if(( !strcmp(tempattr->attrName,"appearance") && !strcmp(tempattr->attrValue,"full"))){
						    count = count + CalculateTreeChildre(temp->child) + 1;
						}
				}
      }
      else if( !strcmp(temp->type,"xf:select"))
      {
        // it is a check box list
        count = count + CalculateTreeChildre(temp->child) + 1;
      }
      else if( !strcmp(temp->type,"xf:range"))
      {
        // it is a check box list
        count = count  + 1;
      }
    }
    WriteLog("\n HEAD = %s, CHULDREN ARE %d",head->name, count);
    return count;
}

int CalculateYPosition(Fl_Group *p, char *s){
  
	int height = 0, i = 0;
	Fl_Widget *temp;
	//WriteLog("\n[%s]",s);
	if(p->children()){
		for(i = 0; i < p->children(); i++)
		{
			temp = p->child(i);
			//WriteLog("\n\t[CAL_POSITION][%s][%d,%d,%d,%d] %d, %d",temp->label(),temp->x(),temp->y(),temp->w(),temp->h(),i, i*(temp->h() + V_SPACING));
		  height += temp->h() + V_SPACING;
		}
		//WriteLog("\n[CAL_POSITION][%s][%d,%d,%d,%d] %d, %d",p->label(),p->x(),p->y(),p->w(),p->h(),i, height);
		return height;
	}
	//WriteLog("\n[CAL_POSITION][%s][%d,%d,%d,%d] NO-CHILDREN",p->label(),p->x(),p->y(),p->w(),p->h());
	return 0;
}

void PrintGroupDetails(Fl_Group *p)
{
  WriteLog("\n =================== %s ==============",p->label());
  Fl_Widget *temp;
    //PrintWidgetDimensions(p);
    WriteLog("\n NUBER OF CHILDREN = %d",p->children());
    if(p->children()){
      for(int i = 0; i < p->children(); i++){
          temp=p->child(i);
          //PrintWidgetDimensions(temp);
        }
    }
  WriteLog("\n ================================");
}
/* ========================================================================================== */

int sFltkUIHandler_f_FrameHandler(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func){
  static int frameCounter = 0;
	Fl_Group *parent = Fl_Group::current();
	int height = 0;
	head -> meta_info = (char *)"1";
	if(parent){
	  WriteLog("\n [GROUP] %s",head->name);
    //TODO there was a sepator group here which separates this group from others
    CalculateTreeChildre(head);
    // TODO CalculateYPosition is being used to find number of children and then calculate height of parent. It is based on assumption
    // that all it's children fit in 1 row , that is , no sub-tabs are defined etc. A better approach is to change height of this 
    // group after it's children have been rendered. But in doing so, fltk resizes children along with it. Find some method to change 
    // or resize the parent group without changing dimensions of child widgets
		Fl_Group *new_frame = new Fl_Group(parent->x(),CalculateYPosition(parent,head->name) + parent->y() ,parent->w(),(CalculateTreeChildre(head)*(V_SPACING + ROW_HEIGHT)) + V_SPACING,"");
		new_frame->color(FL_YELLOW);
		//new_frame->labelcolor(FL_RED);
		new_frame->begin();
			sGenerateUIFromTree(head,CallBackData,modelPtr,func);
		new_frame->end();
		//TODO calculate new height and adjust it's height
		
//		new_frame->resize(new_frame->x(),new_frame->y(),new_frame->w(),CalculateYPosition(new_frame,head->name) + V_SPACING);
		WriteLog("\n ......(%d,%d,%d,%d)",new_frame->x(),new_frame->y(),new_frame->w(),new_frame->h());
  		new_frame->box(FL_BORDER_BOX);
//		PrintGroupDetails(new_frame);
//		return new_frame->h();
		frameCounter++;
		return 0;
	}else{
		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
		return -1;
	}
}

/* ========================================================================================== */

int sFltkUIHandler_f_Select1Handler(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func){
  WriteLog("\n[%s]",__func__);
	Fl_Group *parent = Fl_Group::current();
	head->meta_info = (char *)"1";
	static int ddctr = 0;
	if(!parent){
		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
		exit(1);
	}
	else{
	char *name = head->name;
	          if( get_pointer_to_user_data_by_name(name,(*CallBackData)) != 0 )
	          {
	              name = sAppendString(name,int2str[ddctr]);
	              ddctr++;
	          }
	              	 sXformsNodeAttr *attr = getAttrFromList(head,"ref");
     	 if(attr)
  	 {
  	    AppendNode(CallBackData,s_dupstr(attr->meta_info),s_dupstr(attr->private_data),(char *)0,s_dupstr(name),"Fl_Choice",modelPtr,func);
  	 }
  	 else
  	 {
  	    AppendNode(CallBackData,int2str[0],int2str[0],int2str[0],s_dupstr(name),"Fl_Choice",modelPtr,func);
  	 }
		parent->begin();
				Fl_Choice  *f = new Fl_Choice(parent->x() + H_SPACING +  LABEL_WIDTH ,CalculateYPosition(parent,head->name) + V_SPACING+ parent->y(), WIDGET_WIDTH(parent->w()) , ROW_HEIGHT,name);
				f->callback(CallBackFunction,(*CallBackData));
				sXformsNode *xfitem = SearchSubTreeForNodes(head,(char *)"xf:item",(sXformsNodeAttr *)0,1,0);
				while(xfitem){
					// add item to drop downs
					f->add(xfitem->name);
					xfitem->meta_info = (char *)"1";
					xfitem = SearchSubTreeForNodes(head,(char *)"xf:item",(sXformsNodeAttr *)0,1,0);
				}
		return 0;
	}
}

int sFltkUIHandler_f_InputHandler(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func){
  WriteLog("\n[%s]",__func__);
	Fl_Group *parent = Fl_Group::current();
	head->meta_info = (char *)"1";
	static int inputctr = 0;
	if(!parent){
		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
		exit(1);
	}
	else{
	char *name = head->name;
	WriteLog("\n[%s] name = %s",__func__,name);
	          if( get_pointer_to_user_data_by_name(name,(*CallBackData)) != 0 )
	          {
	              name = sAppendString(name,int2str[inputctr]);
	              inputctr++;
	          }
	 sXformsNodeAttr *attr = getAttrFromList(head,"ref");
   InputName[lindex] = name;
	 ActualName[lindex] = head->name;
   lindex++;
		Fl_Input  *f = new Fl_Input(parent->x() + H_SPACING +  LABEL_WIDTH ,CalculateYPosition(parent,head->name) + V_SPACING+ parent->y(), WIDGET_WIDTH(parent->w()) , ROW_HEIGHT,name);
		sXformsNodeAttr * attr_read_only = getAttrFromList(head,"readonly");
		if(attr_read_only)
		{
		  f->readonly(1);
		  if(attr)
  	 {
  	    AppendNode(CallBackData,s_dupstr(attr->meta_info),"READONLY",(char *)0,s_dupstr(name),"Fl_Input",modelPtr,func);
  	 }
  	 else
  	 {
  	    AppendNode(CallBackData,int2str[0],"READONLY",int2str[0],s_dupstr(name),"Fl_Input",modelPtr,func);
  	 }
		}
		else
		{
		  if(attr)
  	 {
  	    AppendNode(CallBackData,s_dupstr(attr->meta_info),s_dupstr(attr->private_data),(char *)0,s_dupstr(name),"Fl_Input",modelPtr,func);
  	 }
  	 else
  	 {
  	    AppendNode(CallBackData,int2str[0],int2str[0],int2str[0],s_dupstr(name),"Fl_Input",modelPtr,func);
  	 }
		}
	}
	return 0;
}

int sFltkUIHandler_f_RangeHandler(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func){
  WriteLog("\n[%s]",__func__);
	Fl_Group *parent = Fl_Group::current();
	head->meta_info = (char *)"1";
	static int rangectr = 0;
	if(!parent){
		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
	}
	else{
	  char *name = head->name;
	          if( get_pointer_to_user_data_by_name(name,(*CallBackData)) != 0 )
	          {
	              name = sAppendString(name,int2str[rangectr]);
	              rangectr++;
	          }
  	 sXformsNodeAttr *attr = getAttrFromList(head,"ref");
  	 if(attr)
  	 {
  	    AppendNode(CallBackData,s_dupstr(attr->meta_info),s_dupstr(attr->private_data),(char *)0,s_dupstr(name),"Fl_Value_Slider",modelPtr,func);
  	 }
  	 else
  	 {
  	    AppendNode(CallBackData,int2str[0],int2str[0],int2str[0],s_dupstr(name),"Fl_Value_Slider",modelPtr,func);
  	 }
    
	  Fl_Output *Label = new Fl_Output(parent->x() + H_SPACING  ,CalculateYPosition(parent,head->name) + V_SPACING+ parent->y(), parent->w() - 2*H_SPACING , ROW_HEIGHT,"");
	    Label->value(head->name);
		Fl_Value_Slider *slider;
		int *start = 0;
		int *end = 0;
		int *step = 0;
		slider = new Fl_Value_Slider(parent->x() + H_SPACING  ,CalculateYPosition(parent,head->name) + V_SPACING+ parent->y(),parent->w() - 2*H_SPACING , ROW_HEIGHT,name);
		slider->callback(CallBackFunction,(*CallBackData));
		slider->type(FL_HORIZONTAL);
		slider->bounds(0.0,100.0);
	}
	return 0;
}

int sFltkUIHandler_f_RadioButtonList(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func){
  WriteLog("\n[%s]",__func__);
	Fl_Group *parent = Fl_Group::current();
	head->meta_info = (char *)"1"; 
	static int radioctr = 0;
	if(!parent){
		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
	}
	else{
		sXformsNode *temp;
		int ctr = 0;
		
		sXformsNode *xfchoices = SearchSubTreeForNodes(head,(char *)"xf:choices",(sXformsNodeAttr *)0,0,0);
		if( xfchoices ){
			xfchoices->meta_info = (char *)"1";
			
			Fl_Group *RadioButtonListGroup = new Fl_Group(parent->x(),CalculateYPosition(parent,head->name) + parent->y() ,parent->w(),((CalculateTreeChildre(xfchoices) + 1)*(V_SPACING + ROW_HEIGHT)),"");
			RadioButtonListGroup->begin();
			Fl_Output *Label = new Fl_Output(RadioButtonListGroup->x() + H_SPACING  ,CalculateYPosition(RadioButtonListGroup,head->name) + V_SPACING+ RadioButtonListGroup->y(), RadioButtonListGroup->w() - 2*H_SPACING , ROW_HEIGHT,"");
	    Label->value(head->name);
			{
				for( temp=xfchoices->child; temp != 0; temp=temp->next, ctr++){
				    char *name = temp->name;
	          if( get_pointer_to_user_data_by_name(name,(*CallBackData)) != 0 )
	          {
	              name = sAppendString(name,int2str[radioctr]);
	              radioctr++;
	          }
          	 sXformsNodeAttr *attr = getAttrFromList(head,"ref");
          	 if(attr)
          	 {
          	    AppendNode(CallBackData,s_dupstr(attr->meta_info),s_dupstr(attr->private_data),(char *)0,s_dupstr(name),"Fl_Round_Button",modelPtr,func);
          	 }
          	 else
          	 {
          	    AppendNode(CallBackData,int2str[0],int2str[0],int2str[0],s_dupstr(name),"Fl_Round_Button",modelPtr,func);
          	 }
				    Fl_Round_Button *btn = new  Fl_Round_Button(RadioButtonListGroup->x() + H_SPACING ,CalculateYPosition(RadioButtonListGroup,head->name) + V_SPACING+ RadioButtonListGroup->y(), RadioButtonListGroup->w() - 2*H_SPACING , ROW_HEIGHT,name);//temp->name);
				    {
				      btn->down_box(FL_ROUND_DOWN_BOX);
				      btn->type(102);
				    }
				    btn->callback(CallBackFunction,(*CallBackData));
            temp->meta_info = (char *)"1";
				}
			}
			RadioButtonListGroup->end();
		}
	}
}



int sFltkUIHandler_f_CheckBoxList(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func){
  WriteLog("\n[%s]",__func__);
	Fl_Group *parent = Fl_Group::current();
	head->meta_info = (char *)"1"; 
	static int chkctr = 0;
	if(!parent){
		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
	}
	
	else{
		sXformsNode *temp;
		sXformsNode *xfchoices = SearchSubTreeForNodes(head,(char *)"xf:choices",(sXformsNodeAttr *)0,0,0);
		if( xfchoices ){
		int ctr = 0;
		xfchoices->meta_info = (char *)"1";
		Fl_Output *Label = new Fl_Output(parent->x() + H_SPACING  ,CalculateYPosition(parent,head->name) + V_SPACING+ parent->y(), parent->w() - 2*H_SPACING , ROW_HEIGHT,"");
	    Label->value(head->name);
			for( temp=xfchoices->child; temp != 0; ctr++,temp=temp->next){
				char *name = temp->name;
	      if( get_pointer_to_user_data_by_name(name,(*CallBackData)) != 0 )
	      {
	          name = sAppendString(name,int2str[chkctr]);
	          chkctr++;
	      }
      	 sXformsNodeAttr *attr = getAttrFromList(temp,"ref");
      	 if(attr)
      	 {
      	    AppendNode(CallBackData,s_dupstr(attr->meta_info),s_dupstr(attr->private_data),(char *)0,s_dupstr(name),"Fl_Check_Button",modelPtr,func);
      	 }
      	 else
      	 {
      	    AppendNode(CallBackData,int2str[0],int2str[0],int2str[0],s_dupstr(name),"Fl_Check_Button",modelPtr,func);
      	 }
	Fl_Check_Button *btn = new Fl_Check_Button(parent->x() + H_SPACING  ,CalculateYPosition(parent,head->name) + V_SPACING+ parent->y(), WIDGET_WIDTH(parent->w()) , ROW_HEIGHT,name);//temp->name
				temp->meta_info = (char *)"1";
				btn->callback(CallBackFunction,(*CallBackData));
			}
		}
		}
	return 0;
}


int sFltkUIHandler_f_ButtonHandler(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func){
  WriteLog("\n[%s]",__func__);
	Fl_Group *parent = Fl_Group::current();
	head->meta_info = (char *)"1"; 
	static int btnctr = 0;
	if(!parent){
		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
	}
	
	else{
	  parent->begin();
	  	char *name = head->name;
	    if( get_pointer_to_user_data_by_name(name,(*CallBackData)) != 0 )
	    {
	        name = sAppendString(name,int2str[btnctr]);
	        btnctr++;
	    }
    struct sCbData *btnref  = AppendNode(CallBackData,"0","0","0",s_dupstr(name),"Fl_Button",modelPtr,func);
	  Fl_Button *btn = new Fl_Button(parent->x() + H_SPACING  ,CalculateYPosition(parent,head->name) + V_SPACING+ parent->y(), WIDGET_WIDTH(parent->w()) , ROW_HEIGHT,name);//head->name
	  btn->callback(CallBackFunction,(*CallBackData));
	 for(sXformsNode * temp = head;temp;temp=temp->prev)
    {
        if( !strcmp(temp->type,"xf:input") || !strcmp(temp->type,"xf:textarea") )
        {
            // find it's name and index and reference
            for( int i = 0; i < lindex ;i++)
            {
              if( !strcmp(temp->name,ActualName[i]))
              {
              	 sXformsNodeAttr *attr = getAttrFromList(temp,"ref");
              	 sXformsNodeAttr *attr2 = getAttrFromList(temp,"readonly");
              	 if(attr && !attr2)
              	 {
              	    AppendNode(&btnref->nextref,s_dupstr(attr->meta_info),s_dupstr(attr->private_data),(char *)0,s_dupstr(InputName[i]),"Fl_Input",modelPtr,func);
              	 }
              	 else
              	 {
              	    AppendNode(&btnref->nextref,int2str[0],int2str[0],int2str[0],s_dupstr(InputName[i]),"Fl_Input",modelPtr,func);
              	 }
              }
            }
        }
    }
    lindex = 0;
	  parent->end();
}
}

int sFltkUIHandler_f_LabelHandler(sXformsNode *head,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func){
  WriteLog("\n[%s]",__func__);
	Fl_Group *parent = Fl_Group::current();
	head -> meta_info = (char *)"1";
	static int labelctr = 0;
	if(parent){
	    char *name = head->name;
	    if( get_pointer_to_user_data_by_name(name,(*CallBackData)) != 0 )
	    {
	        name = sAppendString(name,int2str[labelctr]);
	        labelctr++;
	    }
  	 sXformsNodeAttr *attr = getAttrFromList(head,"ref");
  	 if(attr)
  	 {
  	    AppendNode(CallBackData,s_dupstr(attr->meta_info),s_dupstr(attr->private_data),(char *)0,s_dupstr(name),"Fl_Output",modelPtr,func);
  	 }
  	 else
  	 {
  	    AppendNode(CallBackData,int2str[0],int2str[0],int2str[0],s_dupstr(name),"Fl_Output",modelPtr,func);
  	 }
	    Fl_Output *Label = new Fl_Output(parent->x() + H_SPACING  ,CalculateYPosition(parent,head->name) + V_SPACING+ parent->y(), parent->w() - 2*H_SPACING , ROW_HEIGHT,name);// ""
	    Label->value(head->name);
	}else{
		WriteLog(stdout,"\n[%s][%d]could not find parent",__FILE__,__LINE__);
		return -1;
	}
}

