#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "sGtkRenderer.h"
#include "../../simpleUI.h"
#include "../../sXforms.h"
#include "../../misc/misc.h"
#include "../sGtkCallbacks/sGtkCallbacks.h"
#include "../../sCallbackData/sCallbackData.h"

//#define EnableLog
#ifdef EnableLog
#define WriteLog fWriteLog
#else
#define WriteLog
#endif

char *int2str[] = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20"};
int i = 0;
sGtkUIHandlers handler[100];
int lindex = 0;
char *InputName[10];
char *ActualName[10];
int pos = -1;
struct sGtkUIHandlers_data gtk_handlers[] = {
	{
		(char *)"xf:select1",
  		(char *)"drop downs",
  		(char *)0,
  		(char *)0,
  		0,
  		(sGtkUIHandlers)gtk_f_Select1Handler
	},
	{
		(char *)"xf:select1",
  		(char *)"radio button list",
		(char *)"appearance",
		(char *)"full",
		1,
  		(sGtkUIHandlers)gtk_f_RadioButtonList
	},
	{
		(char *)"xf:select",
		(char *)"check box list",
		(char *)"appearance",
		(char *)"full",
		1,
		(sGtkUIHandlers)gtk_f_CheckBoxList
	},
	{
		(char *)"xf:input",
  		(char *)"xf-input",
  		(char *)0,
  		(char *)0,
  		0, // generic for now
  		(sGtkUIHandlers)gtk_f_InputHandler
	},
	{
	    (char *)"xf:secret",
	    (char *)"password",
	    (char *)0,
	    (char *)0,
	    0,
	    (sGtkUIHandlers)gtk_f_InputHandler
	},
	{
	    (char *)"xf:textarea",
	    (char *)"password",
	    (char *)0,
	    (char *)0,
	    0,
	    (sGtkUIHandlers)gtk_f_InputHandler
	},
	{
		(char *)"xf:output",
  		(char *)"xf-output",
  		(char *)0,
  		(char *)0,
  		0, // generic for now
  		(sGtkUIHandlers)gtk_f_LabelHandler
	},
	{
		(char *)"xf:trigger",
  		(char *)"xf-button",
  		(char *)0,
  		(char *)0,
  		0,
  		(sGtkUIHandlers)gtk_f_ButtonHandler
	},
	{
		(char *)"xf:group",
		(char *)"xf-group-tabs-handler",
		(char *)"type",
		(char *)"tabs",
		0,
		(sGtkUIHandlers)gtk_f_TabsHandler
	},
		{
		(char *)"xf:group",
		(char *)"start a new frame or a box",
		(char *)"type",
		(char *)"frame",
		1,
		(sGtkUIHandlers)gtk_f_FrameHandler
	},
	{
		(char *)"xf:range",
		(char *)"xf-sliders",
		(char *)0,
		(char *)0,
		0,  
		(sGtkUIHandlers)gtk_f_RangeHandler
	},
/*	{*/
/*		(char *)"xf:repeat",*/
/*		(char *)"xf-repeat-handlers",*/
/*		(char *)0,*/
/*		(char *)0,*/
/*		1,*/
/*		(sGtkUIHandlers)gtk_f_TableHandler*/
/*	},*/

	{
		(char *)0,
  		(char *)0,
  		(char *)0,
  		(char *)0,
  		1,
  		(sGtkUIHandlers)0
	}
};

struct sCbData * sGenerateGladeFile(sXformsNode *head,xmlDoc *modelPtr,CallBackInterfaceFunction func )
{
    xmlDoc *doc = NULL;
    xmlNode *root_node = NULL;
    xmlNode *current_node = NULL;
    /* required for every window */
    doc = xmlNewDoc(BAD_CAST"1.0");  // create a new document
    root_node = xmlNewNode(NULL,BAD_CAST"interface");  // root node
    xmlDocSetRootElement(doc, root_node); // set root node
    
    xmlNode *main_window = Create1ObjectNode(root_node,sGTK_GLADE_MAIN_WINDOW_NAME,"GtkWindow",NULL,NULL); // create main window
    char *prop_names[] = {"default_height","default_width","can_focus","title"};
    char *translatable[] = {NULL,NULL,NULL,"yes"};
    char *comments[] = {NULL,NULL,NULL,NULL};
    char *context[] = {NULL,NULL,NULL,NULL};
    char *value[] = {"680","500","False","SimpleUI"};
    CreatePropertyNodes(main_window,prop_names,translatable,comments,context,value,4);
    Create1SignalNode(main_window,"destroy","gtk_main_quit", NULL,"no", NULL, NULL);
    
    xmlNode *main_window_child = Create1ChildNode(main_window,NULL, NULL);
    
    xmlNode *Main_Vbox = Create1ObjectNode(main_window_child,"Vbox_MainVBox","GtkBox",NULL,NULL);
    char *Main_Vbox_propnames[] = {"width_request","height_request","visible","can_focus","orientation"};
    char *Main_Vbox_NullNodes[] = {NULL,NULL,NULL,NULL,NULL};
    char *Main_Vbox_values[] = {"500","680","True","False","vertical"};
    CreatePropertyNodes(Main_Vbox,Main_Vbox_propnames,Main_Vbox_NullNodes,Main_Vbox_NullNodes,Main_Vbox_NullNodes,Main_Vbox_values,5);
    
    // lower close button
    xmlNode *Main_Vbox_Child2 = Create1ChildNode(Main_Vbox,NULL,NULL);
    xmlNode *BottomPaneHBox = Create1ObjectNode(Main_Vbox_Child2,"BottomPaneHBox","GtkBox",NULL,NULL);
    char *BottomPaneHBox_propnames[] = {"height_request","visible","can_focus","homogeneous"};
    char *BottomPaneHBox_NullNodes[] = {NULL,NULL,NULL,NULL};
    char *BottomPaneHBox_values[] = {"30","True","False","True"};
    CreatePropertyNodes(BottomPaneHBox,BottomPaneHBox_propnames,BottomPaneHBox_NullNodes,BottomPaneHBox_NullNodes,BottomPaneHBox_NullNodes,BottomPaneHBox_values,4);
    
    // add 3 children
    xmlNode *BottomPaneHBox_child1 = Create1ChildNodeWithPlaceholder(BottomPaneHBox,NULL,NULL);
    xmlNode *BottomPaneHBox_child2 = Create1ChildNodeWithPlaceholder(BottomPaneHBox,NULL,NULL);
    xmlNode *BottomPaneHBox_child3 = Create1ChildNode(BottomPaneHBox,NULL,NULL);
    
    // add close button to 3rd child
    xmlNode *CloseButton = Create1ObjectNode(BottomPaneHBox_child3,"BtnClose","GtkButton",NULL,NULL);
    char *CloseButton_propnames[] = {"label","use_action_appearance","visible","can_focus","receives_default","halign","use_stock"};
    char *CloseButton_NULL[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    char *CloseButton_values[] = {"gtk-close","False","True","True","True","end","True"};
    CreatePropertyNodes(CloseButton,CloseButton_propnames,CloseButton_NULL,CloseButton_NULL,CloseButton_NULL,CloseButton_values,7);
    Create1SignalNode(CloseButton,"clicked","gtk_main_quit", NULL,"no", NULL, NULL);
    
    // adjust packing properties for this
    char *BottomPaneHBox_packing_propnames[] = {"expand","fill","position","pack_type"};
    char *BottomPaneHBox_packing_NullNodes[] = {NULL,NULL,NULL,NULL};
    char *BottomPaneHBox_packing_values[] = {"False","True","1","end"};
    xmlNode *BottomPaneHBox_packing = CreatePackingNodeWithProperties(Main_Vbox_Child2,BottomPaneHBox_packing_propnames,BottomPaneHBox_packing_NullNodes, BottomPaneHBox_packing_NullNodes,BottomPaneHBox_packing_NullNodes,BottomPaneHBox_packing_values, 4);
    
    // parse the ds here, make child for main contents
    xmlNode *Main_Vbox_Child1 = Create1ChildNode(Main_Vbox,NULL,NULL);
    xmlNode *ContentBox = Create1ObjectNode(Main_Vbox_Child1,"scrolledwindow_ContentArea","GtkScrolledWindow",NULL,NULL);
    char *ContentBox_propnames[] = {"visible","shadow_type","can_focus"};
    char *ContentBox_NullNodes[] = {NULL,NULL,NULL};
    char *ContentBox_values[] = {"True","in","True"};
    CreatePropertyNodes(ContentBox,ContentBox_propnames,ContentBox_NullNodes,ContentBox_NullNodes,ContentBox_NullNodes,ContentBox_values,3);
    char *ContentBox_packing_propnames[] = {"expand","fill","position"};
    char *ContentBox_packing_NullNodes[] = {NULL,NULL,NULL};
    char *ContentBox_packing_values[] = {"True","True","0"};
    CreatePackingNodeWithProperties(Main_Vbox_Child1,ContentBox_packing_propnames,ContentBox_packing_NullNodes, ContentBox_packing_NullNodes,ContentBox_packing_NullNodes,ContentBox_packing_values, 3);
    xmlNode *AddContentHere = Create1ChildNode(ContentBox,NULL,NULL);
    struct sCbData *temp = (struct sCbData *)0;
    sGtkGenerateUIFromTree(head,AddContentHere,&temp,modelPtr,func);
    // main content area
    xmlSaveFormatFileEnc(sGTK_UI_FILE, doc, "UTF-8", 1); // save file
    xmlFreeDoc(doc);  // free document
    xmlCleanupParser();  //clean parse
    return temp;
}


int sGtkGenerateUIFromTree(sXformsNode * head, xmlNode *par ,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func )
{
if( head == 0 ){
	fprintf(stderr,"\n no data to read from\n");
	exit(1);
}
else{
	sXformsNode *temp ;
	int x = 0;
	for( temp = head->child;(( temp != 0 ) ) ; temp=temp->next){
		if( temp->meta_info && !strcmp(temp->meta_info,"1")){
			continue;
		}
		WriteLog(stdout,"\n == %s : %s ==",temp->meta_info, temp->name);
		x = 0;
		if(temp->attr){
			while(gtk_handlers[x].type != 0){
			if( !strcmp(temp->type,gtk_handlers[x].type)){
				sXformsNodeAttr *tempattr;
				for( tempattr = temp->attr; tempattr; tempattr=tempattr->next){
					if( (gtk_handlers[x].attrname) && (gtk_handlers[x].attrvalue) && ( !strcmp(tempattr->attrName,gtk_handlers[x].attrname) && !strcmp(tempattr->attrValue,gtk_handlers[x].attrvalue))){
						WriteLog(stdout,"\n[%s][%d] start specialised %s:%s",__func__,__LINE__,temp->type,temp->name);
						gtk_handlers[x].handler(temp,par,CallBackData,modelPtr,func);
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
			while(gtk_handlers[x].type != 0){
			if( !strcmp(temp->type,gtk_handlers[x].type) && !gtk_handlers[x].strict){
				//WriteLog(stdout,"\n[%s][%d] start generic %s:%s",__func__,__LINE__,temp->type,temp->name);
				gtk_handlers[x].handler(temp,par,CallBackData,modelPtr,func);
				temp->meta_info = (char *)"1"; // node visited
				//break;
			}
			x++;
			}
		}
		if( temp->child == 0){
			continue;
		}else{
			sGtkGenerateUIFromTree(temp,par,CallBackData,modelPtr,func);
		}}
	}
return 0;
}


int gtk_f_TabsHandler(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func )
{
  WriteLog(stdout,"\n[%s][%d][head = %s,%s]",__func__,__LINE__,head->type,head->name);
  static int tabsctr = 0;
	head -> meta_info = (char *)"1";
	sXformsNodeAttr xf_trigger_attr = {"type","tab_trigger",(char *)0,(char *)0,(sXformsNodeAttr *)0,(sXformsNodeAttr *)0};
	int flag_t = 1;
	sXformsNode *xftrigger = SearchSubTreeForNodes(head,(char *)"xf:trigger",&xf_trigger_attr,0,1);
	if( xftrigger != 0){
	    xmlNode *curnode = node;
/*	    // find the parent of this xmlNode child, if it is scrolled window, then add gtkviewport*/
	    xmlNode *par = node->parent;
        if(par == NULL ){
            fprintf(stderr,"\n no parent found \n");
            exit(1);
        }
	    xmlAttr *attr = par->properties;
	    while(attr && attr->type == XML_ATTRIBUTE_NODE ){
			if( !strcmp("class",attr->name) && !strcmp("GtkScrolledWindow",xmlNodeListGetString(node->doc,attr->children,1)))
			{
                xmlNode *ViewPort = Create1ObjectNode(node,"viewport_scrolledwindow_ContentArea","GtkViewport",NULL,NULL);
                char *ViewPort_propnames[] = {"visible","can_focus"};
                char *ViewPort_NullNodes[] = {NULL,NULL,NULL};
                char *ViewPort_values[] = {"True","False"};
                CreatePropertyNodes(ViewPort,ViewPort_propnames,ViewPort_NullNodes,ViewPort_NullNodes,ViewPort_NullNodes,ViewPort_values,2);
                xmlNode *ViewPortChild = Create1ChildNode(ViewPort,NULL,NULL);
                curnode = ViewPortChild;
			    break;
			}
			attr = attr->next;
		}
    // add note book
    xmlNode *GtkNotebook = Create1ObjectNode(node,"GtkNotebook_Main","GtkNotebook",NULL,NULL);
    char *GtkNotebook_propnames[] = {"visible","can_focus"};
    char *GtkNotebook_NullNodes[] = {NULL,NULL,NULL};
    char *GtkNotebook_values[] = {"True","False"};
    CreatePropertyNodes(GtkNotebook,GtkNotebook_propnames,GtkNotebook_NullNodes,GtkNotebook_NullNodes,GtkNotebook_NullNodes,GtkNotebook_values,2);
    curnode = GtkNotebook;
    int i = 0;
	while( xftrigger != 0){
		
		flag_t = 0;
		// search for xf:toggle inside this
		sXformsNode * toggle = SearchSubTreeForNodes(xftrigger,(char *)"xf:toggle",(sXformsNodeAttr *)0,0,0);
		if(toggle != 0){
			toggle->meta_info = (char *)"1";
			sXformsNodeAttr *attr;
			for(attr = toggle->attr; attr; attr=attr->next){
				if(!strcmp(attr->attrName,"case")){
					sXformsNodeAttr xf_case_attr = {"id",attr->attrValue,(char *)0,(char *)0,(sXformsNodeAttr *)0,(sXformsNodeAttr *)0};
					sXformsNode *tab_content = SearchSubTreeForNodes(head->par,(char *)"xf:case",&xf_case_attr,1,1);
					if(tab_content != 0){
						// child with contents
						char *s = "content_";
						s = sAppendString(s,xftrigger->name);
						xmlNode *GtkNotebookChildContent = Create1ChildNode(curnode,NULL,NULL);
						xmlNode *GtkNotebookGtkScrolledWindow = Create1ObjectNode(GtkNotebookChildContent,s,"GtkScrolledWindow",NULL,NULL);
						char *GtkNotebookGtkScrolledWindowPropNames[] = {"visible","can_focus","shadow_type"};
						char *GtkNotebookGtkScrolledWindowNull[] = {NULL,NULL,NULL};
						char *GtkNotebookGtkScrolledWindowValues[] = {"True","False","in"};
                        CreatePropertyNodes(GtkNotebookGtkScrolledWindow,
                                            GtkNotebookGtkScrolledWindowPropNames,
                                            GtkNotebookGtkScrolledWindowNull,
                                            GtkNotebookGtkScrolledWindowNull,
                                            GtkNotebookGtkScrolledWindowNull,
                                            GtkNotebookGtkScrolledWindowValues,3);
                        xmlNode *GtkNotebookGtkViewportChild = Create1ChildNode(GtkNotebookGtkScrolledWindow,NULL,NULL);
                        s = "viewport_";
                        s = sAppendString(s,xftrigger->name);
                        xmlNode *GtkNotebookGtkViewport = Create1ObjectNode(GtkNotebookGtkViewportChild,s,"GtkViewport",NULL,NULL);
                        char *GtkNotebookGtkViewportProp[] = {"visible","can_focus"};
                        char *GtkNotebookGtkViewportNull[] = {NULL,NULL};
                        char *GtkNotebookGtkViewportValues[] = {"True","False"};
                        CreatePropertyNodes(GtkNotebookGtkViewport,
                                            GtkNotebookGtkViewportProp,
                                            GtkNotebookGtkViewportNull,
                                            GtkNotebookGtkViewportNull,
                                            GtkNotebookGtkViewportNull,
                                            GtkNotebookGtkViewportValues,2);
                        xmlNode *TabChild = Create1ChildNode(GtkNotebookGtkViewport,NULL,NULL);
                        // tab content
                        sGtkGenerateUIFromTree(tab_content,TabChild ,CallBackData,modelPtr,func);
                        // child for labels
                        s = "label_";
						s = sAppendString(s,xftrigger->name);
                        xmlNode *GtkNotebookChildLabel = Create1ChildNode(curnode,"tab",NULL);
                        xmlNode *label = Create1ObjectNode(GtkNotebookChildLabel,s,"GtkLabel",NULL,NULL);
                        char *GtkNotebookChildLabel_prop[] = {"visible","can_focus","label"};
                        char *GtkNotebookChildLabel_trans[] = {NULL,NULL,"yes"};
                        char *GtkNotebookChildLabel_null[] = {NULL,NULL,NULL};
                        char *GtkNotebookChildLabel_values[] = {"True","False",xftrigger->name};
                        CreatePropertyNodes(label,GtkNotebookChildLabel_prop,GtkNotebookChildLabel_trans, GtkNotebookChildLabel_null, GtkNotebookChildLabel_null,GtkNotebookChildLabel_values ,3);
                        char *GtkNotebookChildLabel_packing_propnames[] =  {"position","tab_fill"};
                        char *GtkNotebookChildLabel_packing_null[]  = {NULL,NULL};
                        char *GtkNotebookChildLabel_packing_values[] = { int2str[i],"False"};
                        CreatePackingNodeWithProperties(GtkNotebookChildLabel,
                                                        GtkNotebookChildLabel_packing_propnames,
                                                        GtkNotebookChildLabel_packing_null,
                                                        GtkNotebookChildLabel_packing_null,
                                                        GtkNotebookChildLabel_packing_null,
                                                        GtkNotebookChildLabel_packing_values, 2);
                        i++;
					}
				}
			}
		}else{
			WriteLog(stdout,"\n[%s][%d]ERROR MAKING TABS",__FILE__,__LINE__);
			exit(1);
		}
		xftrigger->meta_info = (char *)"1";
		xftrigger  =  SearchSubTreeForNodes(head,(char *)"xf:trigger",&xf_trigger_attr,0,1);
	}}
	else
	{
	    WriteLog(stdout,"\n[%s:%s] COULD NOT PARSE",head->name,head->type);
	}
    return 0;
}

int gtk_f_FrameHandler(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func )
{
    WriteLog(stdout,"\n[%s][%d] HEAD = %s:%s \t\t NODE = %s",__func__,__LINE__,head->name, head->type,node->name);
    int i = 0;
    sXformsNode *temp = head;
     head -> meta_info = (char *)"1";
     // add gtk box
    char *s = "vbox_frame_";s = sAppendString(s,temp->name);
    xmlNode *tempvbox = Create1ObjectNode(node,s,"GtkBox",NULL,NULL);
    char *tempvboxProp[] = {"visible","can_focus","orientation"};
    char *tempvboxNull[] = {NULL,NULL,NULL};
    char *tempvboxValues[] = {"True","False","vertical"};
    CreatePropertyNodes(tempvbox,tempvboxProp,tempvboxNull,tempvboxNull,tempvboxNull,tempvboxValues,3);

    for( i = 0; temp; i++, temp = temp->next)
    {
        // 1. create one child
        // 2. then add one vertical box 
        // 3. parse the contents for this group
        // 4. then add packing information
        temp->meta_info = (char *)"1";
        xmlNode *child = Create1ChildNode(tempvbox,NULL,NULL);
        
        s = "frame_";s = sAppendString(s,temp->name);
        xmlNode *frame_tempvbox = Create1ObjectNode(child,s,"GtkBox",NULL,NULL);
        char *frametempvboxProp[] = {"visible","can_focus","orientation"};
        char *frametempvboxNull[] = {NULL,NULL,NULL};
        char *frametempvboxValues[] = {"True","False","vertical"};
        CreatePropertyNodes(frame_tempvbox,frametempvboxProp,frametempvboxNull,frametempvboxNull,frametempvboxNull,frametempvboxValues,3);
        
        // parse the contents here , passing  frame_tempvbox as parent
        sGtkGenerateUIFromTree(temp,frame_tempvbox ,CallBackData,modelPtr,func);
        
        char *frametempvboxPackingProp[] = {"expand","fill","position"};
        char *frametempvboxPackingNull[] = {NULL,NULL,NULL};
        char *frametempvboxPackingValues[] = {"False","True",int2str[i]};
        CreatePackingNodeWithProperties(child,
                                        frametempvboxPackingProp,
                                        frametempvboxPackingNull,
                                        frametempvboxPackingNull,
                                        frametempvboxPackingNull,
                                        frametempvboxPackingValues,3);
    }
}



int gtk_f_Select1Handler(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func )
{
    static int selectctr = 0;
    WriteLog(stdout,"\n[%s][%d][head = %s]",__func__,__LINE__,head->name);
    int pos = -1;
    // calculate the position of this element among it's siblings'
    head->meta_info = (char *)"1";
    sXformsNode *temp = head;
    for(pos=-1;temp;temp=temp->prev,pos++);

    xmlNode *child = 0;
    xmlNode *hbox  = MakeHBoxForElements(head,node,&child);
    MakeLabel(head,hbox,CallBackData,modelPtr,func,0);
    char *liststorename = sAppendString("liststorename_",int2str[selectctr]);
    gtk_f_MakeListStoreForDropDown(head,node,CallBackData,modelPtr,func,liststorename);

    xmlNode *child_combo = Create1ChildNode(hbox,NULL,NULL);
    xmlNode *combobox = Create1ObjectNode(child_combo,sAppendString("combo_",int2str[selectctr]),"GtkComboBox",NULL,NULL);
    char *combobox_prop[] = {"width_request","height_request","visible","can_focus","model","id_column"};
    char *combobox_null[] = {NULL,NULL,NULL,NULL,NULL,NULL};
    char *combobox_value[] = {"200","25","True","False",liststorename,"1"};
    CreatePropertyNodes(combobox,combobox_prop,combobox_null, combobox_null, combobox_null,combobox_value ,6);
    //AppendNode(CallBackData,"NULL-REFERENCE", "NULL-INITVAL","NULL-VAL",s,"GtkComboBox");
     sXformsNodeAttr *attrref = getAttrFromList(head,"ref");
  	 if(attrref)
  	 {
  	    AppendNode(CallBackData,s_dupstr(attrref->meta_info),s_dupstr(attrref->private_data),(char *)0,sAppendString("combo_",int2str[selectctr]),"GtkComboBox",modelPtr,func);
  	 }
  	 else
  	 {
  	    AppendNode(CallBackData,int2str[0],int2str[0],int2str[0],sAppendString("combo_",int2str[selectctr]),"GtkComboBox",modelPtr,func);
  	 }
    //Create1SignalNode(combobox,"changed","on_combobox_changed",NULL, "no",NULL,NULL);
    Create1SignalNode(combobox,"changed","CallBackFunction",NULL, "no",NULL,NULL);
    xmlNode *CellRendererChild = Create1ChildNode(combobox,NULL,NULL);
    xmlNode *CellRenderer = Create1ObjectNode(CellRendererChild,sAppendString("CellRenderer_",int2str[selectctr]),"GtkCellRendererText",NULL,NULL);
    xmlNode *attr = CreateXmlNodeWithParent(CellRendererChild,"attributes");
    xmlNode *attrchild = CreateXmlNodeWithParent(attr,"attribute");
    CreateNodeText(attrchild,int2str[0]);
    CreateNodeAttribute(attrchild, "name", "text");

    PackElements(child_combo,"True","False",1);
    sGtkGenerateUIFromTree(head,hbox,CallBackData,modelPtr,func);
    
    PackElements(child,"True","False",pos);
    selectctr++;

}

int gtk_f_RadioButtonList(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func )
{
    static int RadioButtonListctr = 0;
    xmlNode *child = 0;
    xmlNode *hbox  = MakeHBoxForElements(head,node,&child);
    head->meta_info = int2str[1];
    int pos  = CalculatePosition(head);
    MakeLabel(head,hbox,CallBackData,modelPtr,func,0);
    xmlNode *buttongroupchild = Create1ChildNode(hbox,NULL,NULL);

    xmlNode *buttongrp = Create1ObjectNode(buttongroupchild,sAppendString("buttongroupName_",int2str[RadioButtonListctr]),"GtkButtonBox",NULL,NULL);
    char *buttongrpprop[] = {"visible","can_focus","layout_style"};
    char *buttongrpnull[] = {NULL,NULL,NULL};
    char *buttongrpval[] = {"True","False","start"};
    CreatePropertyNodes(buttongrp,buttongrpprop,buttongrpnull,buttongrpnull,buttongrpnull,buttongrpval,3);
    char *GroupName = sAppendString("buttongroup_",int2str[RadioButtonListctr]);
    gtk_f_MakeRadioButtonGroup(head,node,CallBackData,modelPtr,func,GroupName);
    sXformsNode *temp;
    int ctr = 0;
    sXformsNode *xfchoices = SearchSubTreeForNodes(head,(char *)"xf:choices",(sXformsNodeAttr *)0,0,0);
    if( xfchoices ){
			xfchoices->meta_info = (char *)"1";
			for( temp=xfchoices->child; temp != 0; temp=temp->next,ctr++){
			    temp->meta_info = int2str[1];
			    MakeRadioButton(head,buttongrp,GroupName, "on_radiobutton_toggled",temp->name,ctr,CallBackData,modelPtr, func);
			}
    }
    sGtkGenerateUIFromTree(head,hbox,CallBackData,modelPtr,func);
    PackElements(buttongroupchild,"True","False",pos);
    PackElements(hbox->parent,"True","False",pos);
    RadioButtonListctr++;
}

int gtk_f_CheckBoxList(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func )
{
    static int checklistctr = 0;
    WriteLog(stdout,"\n[%s][%d][head = %s]",__func__,__LINE__,head->private_data);
    head->meta_info = int2str[1];
    xmlNode *vboxchild = Create1ChildNode(node,NULL,NULL);
    xmlNode *vbox = Create1ObjectNode(vboxchild,sAppendString("CheckBoxList_Vbox_",int2str[checklistctr]),"GtkBox",NULL,NULL);
    char *vboxprop[] = {"visible","can_focus","orientation"};
    char *vboxval[] = {"True","False","vertical"};
    char *vboxnull[] = {NULL,NULL,NULL};
    CreatePropertyNodes(vbox,vboxprop,vboxnull,vboxnull,vboxnull,vboxval,3);
    //label
    MakeLabel(head,vbox,CallBackData,modelPtr,func,0);
    // add a button box
    xmlNode *buttonboxcontainer = Create1ChildNode(vbox,NULL,NULL);
    xmlNode *buttonbox = Create1ObjectNode(buttonboxcontainer,sAppendString("ButtonBox_",int2str[checklistctr]),"GtkButtonBox",NULL,NULL);
    char *buttonboxprop[] = {"visible","can_focus","halign","orientation","layout_style"};
    char *buttonboxval[] = {"True","False","start","vertical","start"};
    char *buttonboxnull[] = {NULL,NULL,NULL,NULL,NULL};
    CreatePropertyNodes(buttonbox,buttonboxprop,buttonboxnull,buttonboxnull,buttonboxnull,buttonboxval,5);
    sXformsNode *temp;
    int ctr = 0;
    sXformsNode *xfchoices = SearchSubTreeForNodes(head,(char *)"xf:choices",(sXformsNodeAttr *)0,0,0);
    if( xfchoices ){
			xfchoices->meta_info = (char *)"1";
			for( temp=xfchoices->child; temp != 0; temp=temp->next,ctr++){
			    temp->meta_info = int2str[1];
			    MakeCheckButton(head,buttonbox,"on_checkbutton_toggled",temp->name,ctr,CallBackData,modelPtr,func);
			}
    }
    PackElements(buttonboxcontainer,"True","False",1);
    sGtkGenerateUIFromTree(head->child,vbox,CallBackData,modelPtr,func);
    // done button
    PackElements(vboxchild,"True","False",0);
    checklistctr++;
}

int gtk_f_InputHandler(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func )
{
    static int inputctr = 0;
    int pos = -1;
    // calculate the position of this element among it's siblings'
    head->meta_info = (char *)"1";
    sXformsNode *temp = head;
    for(pos=-1;temp;temp=temp->prev,pos++);
    xmlNode *child = 0;
    xmlNode *hbox  = MakeHBoxForElements(head,node,&child);
    MakeLabel(head,hbox,CallBackData,modelPtr,func,0);
    xmlNode *child_entry = Create1ChildNode(hbox,NULL,NULL);
    char buf[10];
    sprintf(buf,"entry_%d",inputctr);
    char *name = s_dupstr(buf);
    sXformsNodeAttr *attr = getAttrFromList(head,"ref");
    InputName[lindex] = name;
    ActualName[lindex] = head->name;
    lindex++;
    sXformsNodeAttr *attr_read_only = getAttrFromList(head,"readonly");//TODO editable
    if(attr_read_only)
    {
      //TODO make this entry read only
        	 if(attr)
        	 {
        	    AppendNode(CallBackData,s_dupstr(attr->meta_info),"READONLY",(char *)0,name,"GtkEntry",modelPtr,func);
        	 }
        	 else
        	 {
        	    AppendNode(CallBackData,int2str[0],"READONLY",int2str[0],name,"GtkEntry",modelPtr,func);
        	 }
        	   xmlNode *entry = Create1ObjectNode(child_entry,name,"GtkEntry",NULL,NULL);
            char *entry_prop[] = {"width_request","visible","can_focus","invisible_char","editable"};
            char *entry_null[] = {NULL,NULL,NULL,NULL,NULL};
            char *entry_value[] = {"200","True","True","*","False"};
            CreatePropertyNodes(entry,entry_prop,entry_null, entry_null, entry_null,entry_value ,5);
    }
    else
    {
        	 if(attr)
        	 {
        	    AppendNode(CallBackData,s_dupstr(attr->meta_info),s_dupstr(attr->private_data),(char *)0,name,"GtkEntry",modelPtr,func);
        	 }
        	 else
        	 {
        	    AppendNode(CallBackData,int2str[0],int2str[0],int2str[0],name,"GtkEntry",modelPtr,func);
        	 }
        	  xmlNode *entry = Create1ObjectNode(child_entry,name,"GtkEntry",NULL,NULL);
            char *entry_prop[] = {"width_request","visible","can_focus","invisible_char"};
            char *entry_null[] = {NULL,NULL,NULL,NULL};
            char *entry_value[] = {"200","True","True","*"};
            CreatePropertyNodes(entry,entry_prop,entry_null, entry_null, entry_null,entry_value ,4);
    }
    PackElements(child_entry,"True","False",1);
    PackElements(child,"True","False",pos);
    inputctr++;
}

/* ============= DONE ============= */
int gtk_f_LabelHandler(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func )
{
    head->meta_info = (char *)"1";
    //head->name = s;
    xmlNode *child;
    xmlNode *hbox  = MakeHBoxForElements(head,node,&child);
    int pos  = CalculatePosition(head);
    MakeLabel(head,hbox,CallBackData,modelPtr,func,1);
    PackElements(hbox->parent,"True","False",pos);
}

/* ============= DONE ============= */
int gtk_f_ButtonHandler(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func )
{
    static int btnctr = 0;
    int pos = -1;
    head->meta_info = (char *)"1";
    // calculate the position of this element among it's siblings'
    sXformsNode *temp = head;
    for(pos=-1;temp;temp=temp->prev,pos++);
    xmlNode *child = 0;
    xmlNode *hbox  = MakeHBoxForElements(head,node,&child);
    
    Create1ChildNodeWithPlaceholder(hbox,NULL,NULL);
    xmlNode *btnchild = Create1ChildNode(hbox,NULL,NULL);
    
    xmlNode *button = Create1ObjectNode(btnchild,sAppendString("btn_",int2str[btnctr]),"GtkButton",NULL,NULL);
    char *button_prop[] = {"visible","can_focus","label","use_action_appearance","receives_default","use_action_appearance"};
    char *button_null[] = {NULL,NULL,NULL,NULL,NULL,NULL};
    char *button_trans[] = {NULL,NULL,"yes",NULL,NULL,NULL};
    char *button_value[] = {"True","True",head->name,"False","True","False"};
    CreatePropertyNodes(button,button_prop,button_trans, button_null, button_null,button_value ,6);
    
   struct sCbData *btnref  = AppendNode(CallBackData,"0","0","0",sAppendString("btn_",int2str[btnctr]),"GtkButton",modelPtr,func);
	 temp = head;
	 for( temp = head;temp;temp=temp->prev)
    {
        if( !strcmp(temp->type,"xf:input") || !strcmp(temp->type,"xf:textarea") )
        {
            // find it's name and index and reference
            int i = 0;
            for(  i = 0; i < lindex ;i++)
            {
              if( !strcmp(temp->name,ActualName[i]))
              {
              	 sXformsNodeAttr *attr = getAttrFromList(temp,"ref");
              	 sXformsNodeAttr *attr2 = getAttrFromList(temp,"readonly");
              	 if(attr && !attr2)
              	 {
              	    AppendNode(&btnref->nextref,s_dupstr(attr->meta_info),s_dupstr(attr->private_data),(char *)0,s_dupstr(InputName[i]),"GtkEntry",modelPtr,func);
              	 }
              	 else
              	 {
              	    AppendNode(&btnref->nextref,int2str[0],int2str[0],int2str[0],s_dupstr(InputName[i]),"GtkEntry",modelPtr,func);
              	 }
              }
            }
        }
    }
    lindex = 0;
    
    Create1SignalNode(button,"clicked","CallBackFunction", NULL,"no",NULL,NULL);
    PackElements(btnchild,"True","False",1);
    Create1ChildNodeWithPlaceholder(hbox,NULL,NULL);

    PackElements(child,"True","False",pos);
    btnctr++;
}

/* ============= DONE ============= */
int gtk_f_RangeHandler(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func )
{
    static int scalectr = 0;
    int pos = -1;
    head->meta_info = (char *)"1";
    // calculate the position of this element among it's siblings'
    sXformsNode *temp = head;
    WriteLog(stdout,"\n *************** RANGE ***[%s][%d]",__func__,__LINE__);
    
    xmlNode *vboxchild = Create1ChildNode(node,NULL,NULL);
    xmlNode *vbox = Create1ObjectNode(vboxchild,sAppendString("RangeHandler_Vbox_",int2str[scalectr]),"GtkBox",NULL,NULL);
    char *vboxprop[] = {"visible","can_focus","orientation"};
    char *vboxval[] = {"True","False","vertical"};
    char *vboxnull[] = {NULL,NULL,NULL};
    CreatePropertyNodes(vbox,vboxprop,vboxnull,vboxnull,vboxnull,vboxval,3);
    //label
    MakeLabel(head,vbox,CallBackData,modelPtr,func,0);
    
   // 1. first make label in a vertical row , `
    //gtk_f_LabelHandler(head,node,CallBackData,modelPtr,func);

    pos = CalculatePosition(head) + 1;
   // 2. make slider
    xmlNode *child = Create1ChildNode(node,NULL,NULL);
    xmlNode *scale = Create1ObjectNode(child,sAppendString("GtkScale_",int2str[scalectr]),"GtkScale",NULL,NULL);
    //    xmlNode *Create1ObjectNode(xmlNode *par,char *id, char *classname,char *constructor, char *type_func);
    char *scale_prop[] = {"visible","can_focus","margin_left","margin_right","margin_top","margin_bottom","adjustment","lower_stepper_sensitivity","round_digits"};
    char *scale_null[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    char *scale_value[] = {"True","True","2","2","2","2",sAppendString("GtkScale_Adjustment_",int2str[scalectr]),"off","1"};
    CreatePropertyNodes(scale,scale_prop,scale_null, scale_null, scale_null,scale_value ,9);
    
    PackElements(child,"True","False",pos);
    // make an adjustment here
    // <signal name="value-changed" handler="getRangeValue" swapped="no"/>
    //AppendNode(CallBackData,"NULL-REFERENCE", "NULL-INITVAL","NULL-VAL",sAppendString("GtkScale_",int2str[scalectr]),"GtkScale");
     sXformsNodeAttr *attr = getAttrFromList(head,"ref");
  	 if(attr)
  	 {
  	    AppendNode(CallBackData,s_dupstr(attr->meta_info),s_dupstr(attr->private_data),(char *)0,sAppendString("GtkScale_",int2str[scalectr]),"GtkScale",modelPtr,func);
  	 }
  	 else
  	 {
  	    AppendNode(CallBackData,int2str[0],int2str[0],int2str[0],sAppendString("GtkScale_",int2str[scalectr]),"GtkScale",modelPtr,func);
  	 }
    Create1SignalNode(scale,"value-changed","CallBackFunction", NULL, "no", NULL, NULL);
    PackElements(child,"True","False",2);
    MakeAdjustment(head,node,CallBackData,sAppendString("GtkScale_Adjustment_",int2str[scalectr]));
    scalectr++;
}

/* ============= DONE ============= */
int gtk_f_MakeRadioButtonGroup(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func , char *GtkRadioButtonGroupName)
{
    xmlDoc *doc = node->doc;
    xmlNode *root = xmlDocGetRootElement(doc); 
    xmlNode *GtkRadioButtonGroup =  Create1ObjectNode(root,GtkRadioButtonGroupName,"GtkRadioButton",NULL,NULL);
    char *GtkRadioButtonGroupProp[] = {"label","use_action_appearance","visible","can_focus","receives_default","xalign","active","draw_indicator"};
    char *GtkRadioButtonGroupVal[] = {"radiobutton","False","True","True","False","0","True","True"};
    char *GtkRadioButtonGroupNull[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    char *GtkRadioButtonGroupTran[] = {"yes",NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    CreatePropertyNodes(GtkRadioButtonGroup,GtkRadioButtonGroupProp,GtkRadioButtonGroupTran,GtkRadioButtonGroupNull,GtkRadioButtonGroupNull,GtkRadioButtonGroupVal,8);
}

/* ============= DONE ============= */
int gtk_f_MakeListStoreForDropDown(sXformsNode *head,xmlNode *node ,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func ,char *liststorename)
{
    xmlDoc *doc = node->doc;
    xmlNode *root = xmlDocGetRootElement(doc); 
    xmlNode *GtkRadioButtonGroup =  Create1ObjectNode(root,liststorename,"GtkListStore",NULL,NULL);
    // make columns
    xmlNode *col_cont = CreateXmlNodeWithParent(GtkRadioButtonGroup,"columns");
    xmlNode *data_cont = CreateXmlNodeWithParent(GtkRadioButtonGroup,"data");
    // since it is a drop down, it will contain 2 cols, id and text
    int i = 0;
    for( i = 0; i < 2; i++)
    {
        xmlNode *col = CreateXmlNodeWithParent(col_cont,"column");
        CreateNodeAttribute(col,"type","gchararray");
    }
    // add data here
        sXformsNode *temp;
    int ctr = 0;
    sXformsNode *xfchoices = SearchSubTreeForNodes(head,(char *)"xf:choices",(sXformsNodeAttr *)0,0,0);
    if( xfchoices ){
			xfchoices->meta_info = (char *)"1";
			for( temp=xfchoices->child; temp != 0; temp=temp->next,ctr++){
			    temp->meta_info = int2str[1];
			    xmlNode *row = CreateXmlNodeWithParent(data_cont,"row");
                CreateDataRow(row,int2str[0],"yes",temp->name);
                CreateDataRow(row,int2str[1],"yes",temp->name);
			}
    }
}

/* ============= DONE ============= */
int MakeAdjustment(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData,char *name)
{
    xmlDoc *doc = node->doc;
    xmlNode *root = xmlDocGetRootElement(doc); 
    xmlNode *Adjustment =  Create1ObjectNode(root,name,"GtkAdjustment",NULL,NULL);
    
    char *Adjustment_prop[] = {"upper","step_increment","page_increment"};
    char *Adjustment_value[] = {"100","1","1"};
    char *Adjustment_null[] = {NULL,NULL,NULL};
    CreatePropertyNodes(Adjustment,Adjustment_prop,Adjustment_null, Adjustment_null, Adjustment_null,Adjustment_value ,3);
    
}

// helpers
/* ============= DONE ============= */
void MakeCheckButton(sXformsNode *head, xmlNode *par, char *handlername, char *label, int pos,struct sCbData **CallBackData,xmlDoc *modelPtr, CallBackInterfaceFunction func)
{
    static int checkptr = 0;
    char *checkname = sAppendString("checkbutton_",int2str[checkptr]);
    xmlNode *checkbutton = Create1ChildNode(par,NULL,NULL);
    xmlNode *check = Create1ObjectNode(checkbutton,checkname,"GtkCheckButton",NULL,NULL);
    char *check_prop[] = {"label","use_action_appearance","width_request","visible","can_focus","receives_default","margin_top","margin_bottom","xalign","draw_indicator"};
    char *check_value[] = {label,"False","200","True","True","False","2","2","0","True"};
    char *check_null[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    char *check_trans[] = {"yes",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    CreatePropertyNodes(check,check_prop,check_trans, check_null, check_null,check_value ,10);
     sXformsNodeAttr *attr = getAttrFromList(head,"ref");
  	 if(attr)
  	 {
  	    AppendNode(CallBackData,s_dupstr(attr->meta_info),s_dupstr(attr->private_data),(char *)0,checkname,"GtkCheckButton",modelPtr,func);
  	 }
  	 else
  	 {
  	    AppendNode(CallBackData,int2str[0],int2str[0],int2str[0],checkname,"GtkCheckButton",modelPtr,func);
  	 }
    Create1SignalNode(check,"toggled","CallBackFunction", NULL, "no", NULL, NULL);
    
    PackElements(checkbutton,"True","False",pos);
    checkptr++;
}

int CalculatePosition(sXformsNode *head)
{
    int pos = -1;
    sXformsNode *temp = head;
    for(pos=-1;temp;temp=temp->prev,pos++);
    return pos;
}

/* ============= DONE ============= */
xmlNode *MakeHBoxForElements(sXformsNode *head,xmlNode *node,xmlNode **childToreturn)
{
    static int hboxctr = 0;
    char buf[10];
    sprintf(buf,"hbox_%d",hboxctr);
    xmlNode *child = Create1ChildNode(node,NULL,NULL);
    (*childToreturn) = child;
    xmlNode *hbox = Create1ObjectNode(child,buf,"GtkBox",NULL,NULL);
    char *hbox_prop[] = {"visible","can_focus","margin_left","margin_right","margin_top","margin_bottom"};
    char *hbox_null[] = {NULL,NULL,NULL,NULL,NULL,NULL};
    char *hbox_value[] = {"True","False","2","2","2","2"};
    CreatePropertyNodes(hbox,hbox_prop,hbox_null, hbox_null, hbox_null,hbox_value ,6);
    // need to insert nodes here
    hboxctr = hboxctr + 1;
    return hbox;
}

/* ============= DONE ============= */
void PackElements( xmlNode *par,char *fill, char *expand, int pos)
{
    char *packing_prop[] = {"fill","expand","position"};
    char *packing_null[] = {NULL,NULL,NULL};
    char *packing_value[] = {fill,expand,int2str[pos]};
    CreatePackingNodeWithProperties(par,
                                    packing_prop,
                                    packing_null,
                                    packing_null,
                                    packing_null,
                                    packing_value,3);

}
/* ============= DONE ============= */
void MakeLabel(sXformsNode *head,xmlNode *hbox,struct sCbData **CallBackData,xmlDoc *modelPtr,CallBackInterfaceFunction func, int MakeCB)
{
    static int labalctr = 0;
    char *labelname = sAppendString("label_",int2str[labalctr]);
    xmlNode *child_label = Create1ChildNode(hbox,NULL,NULL);
    if(MakeCB)
    {
      sXformsNodeAttr *attr = getAttrFromList(head,"ref");
    	 if(attr)
    	 {
    	    AppendNode(CallBackData,s_dupstr(attr->meta_info),s_dupstr(attr->private_data),(char *)0,labelname,"GtkLabel",modelPtr,func);
    	 }
    	 else
    	 {
    	    AppendNode(CallBackData,int2str[0],int2str[0],int2str[0],labelname,"GtkLabel",modelPtr,func);
    	 }
  	 }
    xmlNode *label = Create1ObjectNode(child_label,labelname,"GtkLabel",NULL,NULL);
    char *label_prop[] = {"width_request","height_request","visible","can_focus","margin_right","label"};
    char *label_null[] = {NULL,NULL,NULL,NULL,NULL,NULL};
    char *label_value[] = {"100","25","True","False","10",head->name};
    char *label_trans[] = {NULL,NULL,NULL,NULL,NULL,"yes"};
    CreatePropertyNodes(label,label_prop,label_trans, label_null, label_null,label_value ,6);
    PackElements(child_label,"True","False",0);
    labalctr++;

}
/* ============= DONE ============= */
void MakeRadioButton(sXformsNode *head, xmlNode *par,char *groupname, char *handlername, char *label, int pos, struct sCbData **CallBackData, xmlDoc *modelPtr, CallBackInterfaceFunction func)
{
    static int radioctr = 0;
    char *radioname = sAppendString("radiobutton_",int2str[radioctr]);
    xmlNode *radiochild = Create1ChildNode(par,NULL,NULL);
    xmlNode *radio = Create1ObjectNode(radiochild,radioname,"GtkRadioButton",NULL,NULL);
    char *radio_prop[] = {"label","use_action_appearance","visible","can_focus","receives_default","xalign","draw_indicator","group"};
    char *radio_value[] = {label,"False","True","True","False","0","True",groupname};
    char *radio_null[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    char *radio_trans[] = {"yes",NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    CreatePropertyNodes(radio,radio_prop,radio_trans, radio_null, radio_null,radio_value ,8);
     sXformsNodeAttr *attr = getAttrFromList(head,"ref");
  	 if(attr)
  	 {
  	    AppendNode(CallBackData,s_dupstr(attr->meta_info),s_dupstr(attr->private_data),(char *)0,radioname,"GtkRadioButton",modelPtr,func);
  	 }
  	 else
  	 {
  	    AppendNode(CallBackData,int2str[0],int2str[0],int2str[0],radioname,"GtkRadioButton",modelPtr,func);
  	 }
    Create1SignalNode(radio,"toggled","CallBackFunction", NULL, "no", NULL, NULL);
    PackElements(radiochild,"True","False",pos);
    radioctr++;
}
