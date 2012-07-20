#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "sGtkRenderer.h"
#include "../../simpleUI.h"
#include "../../sXforms.h"

char *int2str[] = {"0","1","2","3","4","5","6","7","8","9"};
int i = 0;
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
		1,
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

void sGenerateGladeFile(sXformsNode *head)
{
    ////////fprintf(stdout,"\n yes, it is working fine");
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
    
    sGtkGenerateUIFromTree(head,AddContentHere);
    // main content area
    xmlSaveFormatFileEnc(sGTK_UI_FILE, doc, "UTF-8", 1); // save file
    xmlFreeDoc(doc);  // free document
    xmlCleanupParser();  //clean parser
}


int sGtkGenerateUIFromTree(sXformsNode * head, xmlNode *par)
{
if( head == 0 ){
	////////fprintf(stderr,"\n no data to read from");
	exit(1);
}
else{
	sXformsNode *temp ;
	int x = 0;
	for( temp = head->child;(( temp != 0 ) ) ; temp=temp->next){
	    fprintf(stdout,"\n %s:%s, meta info = %s",temp->type,temp->name,temp->meta_info);
		if( temp->meta_info && !strcmp(temp->meta_info,"1")){
			continue;
		}
		x = 0;
		if(temp->attr){
			while(gtk_handlers[x].type != 0){
			if( !strcmp(temp->type,gtk_handlers[x].type)){
				sXformsNodeAttr *tempattr;
				for( tempattr = temp->attr; tempattr; tempattr=tempattr->next){
					if( (gtk_handlers[x].attrname) && (gtk_handlers[x].attrvalue) && ( !strcmp(tempattr->attrName,gtk_handlers[x].attrname) && !strcmp(tempattr->attrValue,gtk_handlers[x].attrvalue))){
						fprintf(stdout,"\n[%s][%d] start 'specialised' %s:%s",__func__,__LINE__,temp->type,temp->name);
						gtk_handlers[x].handler(temp,par);
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
				fprintf(stdout,"\n[%s][%d] start generic %s:%s",__func__,__LINE__,temp->type,temp->name);
				gtk_handlers[x].handler(temp,par);
				temp->meta_info = (char *)"1"; // node visited
				//break;
			}
			x++;
			}
		}
		if( temp->child == 0){
			continue;
		}else{
			sGtkGenerateUIFromTree(temp,par);
		}}
	}
return 0;
}


int gtk_f_TabsHandler(sXformsNode *head,xmlNode *node)
{
    ////////fprintf(stdout,"\n[%s][%d][head = %s]",__func__,__LINE__,head->type);
	head -> meta_info = (char *)"1";
	sXformsNodeAttr xf_trigger_attr = {"type","tab_trigger",(char *)0,(char *)0,(sXformsNodeAttr *)0,(sXformsNodeAttr *)0};
	int flag_t = 1;
	sXformsNode *xftrigger = SearchSubTreeForNodes(head,(char *)"xf:trigger",&xf_trigger_attr,0,1);
	if( xftrigger != 0){
	    xmlNode *curnode = node;
/*	    // find the parent of this xmlNode child, if it is scrolled window, then add gtkviewport*/
	    xmlNode *par = node->parent;
        if(par == NULL ){
            ////////fprintf(stderr,"\n no parent found \n");
            exit(1);
        }
	    xmlAttr *attr = par->properties;
	    while(attr && attr->type == XML_ATTRIBUTE_NODE ){
			////////fprintf(stdout,"\n ATTRIBUTE NAME = %s, and VALUE = %s",attr->name,xmlNodeListGetString(node->doc,attr->children,1));
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
                        sGtkGenerateUIFromTree(tab_content,TabChild );
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
			////////fprintf(stdout,"\n[%s][%d]ERROR MAKING TABS",__FILE__,__LINE__);
			exit(1);
		}
		xftrigger->meta_info = (char *)"1";
		xftrigger  =  SearchSubTreeForNodes(head,(char *)"xf:trigger",&xf_trigger_attr,0,1);
	}}
    return 0;
}

int gtk_f_FrameHandler(sXformsNode *head,xmlNode *node)
{
    ////////fprintf(stdout,"\n[%s][%d] HEAD = %s:%s \t\t NODE = %s",__func__,__LINE__,head->name, head->type,node->name);
/*
    1. count the number of children this node has
    2. add a vertical box with those many rows + 1
    3. add a done button at end
    4. build the interier content of this node
*/
    int i = 0;
    sXformsNode *temp = head;
     head -> meta_info = (char *)"1";
     // add gtk box
    char *s = "vbox_tab_";
    s = sAppendString(s,temp->name);
    xmlNode *tempvbox = Create1ObjectNode(node,s,"GtkBox",NULL,NULL);
    char *tempvboxProp[] = {"visible","can_focus","orientation"};
    char *tempvboxNull[] = {NULL,NULL,NULL};
    char *tempvboxValues[] = {"True","False","vertical"};
    CreatePropertyNodes(tempvbox,tempvboxProp,tempvboxNull,tempvboxNull,tempvboxNull,tempvboxValues,3);

     // find all groups inside it which have type=frame attr set
   // sXformsNodeAttr xf_frame_attr = {"type","frame",(char *)0,(char *)0,(sXformsNodeAttr *)0,(sXformsNodeAttr *)0};
	//sXformsNode *frames = SearchSubTreeForNodes(temp,(char *)"xf:group",&xf_frame_attr,1,1);
    for( i = 0; temp; i++, temp = temp->next)
    {
        // 1. create one child
        // 2. then add one vertical box 
        // 3. parse the contents for this group
        // 4. then add packing information
        ////////fprintf(stdout, "\n[%s][%d]NUMBER = %d",__func__,__LINE__,i);
        temp->meta_info = (char *)"1";
        xmlNode *child = Create1ChildNode(tempvbox,NULL,NULL);
        
        s = "frame_";
        s = sAppendString(s,temp->name);
        xmlNode *frame_tempvbox = Create1ObjectNode(child,s,"GtkBox",NULL,NULL);
        char *frametempvboxProp[] = {"visible","can_focus","orientation"};
        char *frametempvboxNull[] = {NULL,NULL,NULL};
        char *frametempvboxValues[] = {"True","False","vertical"};
        CreatePropertyNodes(frame_tempvbox,frametempvboxProp,frametempvboxNull,frametempvboxNull,frametempvboxNull,frametempvboxValues,3);
        
        // parse the contents here , passing  frame_tempvbox as parent
        sGtkGenerateUIFromTree(temp,frame_tempvbox );
        
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
    //////////fprintf(stdout,"\n[%s][%d] NUMBER OF CHILDREN %d",__func__,__LINE__,i);
}



int gtk_f_Select1Handler(sXformsNode *head,xmlNode *node)
{
    ////fprintf(stdout,"\n[%s][%d][head = %s]",__func__,__LINE__,head->name);
    int pos = -1;
    // calculate the position of this element among it's siblings'
    head->meta_info = (char *)"1";
    sXformsNode *temp = head;
    for(pos=-1;temp;temp=temp->prev,pos++);
    ////fprintf(stdout,"\n[%s][%d][head = %s] POSITION = %d",__func__,__LINE__,head->name,pos);
    char *s = "hbox_";
    s = sAppendString(s,head->name);
    
    xmlNode *child = Create1ChildNode(node,NULL,NULL);
    xmlNode *hbox = Create1ObjectNode(child,s,"GtkBox",NULL,NULL);
    char *hbox_prop[] = {"visible","can_focus","margin_left","margin_right","margin_top","margin_bottom"};
    char *hbox_null[] = {NULL,NULL,NULL,NULL,NULL,NULL};
    char *hbox_value[] = {"True","False","2","2","2","2"};
    CreatePropertyNodes(hbox,hbox_prop,hbox_null, hbox_null, hbox_null,hbox_value ,6);
    
        //label
    s = "lbl_";
    s = sAppendString(s,head->name);
    xmlNode *child_label = Create1ChildNode(hbox,NULL,NULL);
    xmlNode *label = Create1ObjectNode(child_label,s,"GtkLabel",NULL,NULL);
    char *label_prop[] = {"width_request","height_request","visible","can_focus","margin_right","label"};
    char *label_null[] = {NULL,NULL,NULL,NULL,NULL,NULL};
    char *label_value[] = {"100","25","True","False","10",head->name};
    char *label_trans[] = {NULL,NULL,NULL,NULL,NULL,"yes"};
    CreatePropertyNodes(label,label_prop,label_trans, label_null, label_null,label_value ,6);
    
    char *label_packing_prop[] = {"fill","expand","position"};
    char *label_packing_null[] = {NULL,NULL,NULL};
    char *label_packing_value[] = {"True","False","0"};
    CreatePackingNodeWithProperties(child_label,
                                    label_packing_prop,
                                    label_packing_null,
                                    label_packing_null,
                                    label_packing_null,
                                    label_packing_value,3);
    // make a list store first here, name = liststore_ + head->name
    char *liststore_name = "liststore_";
    liststore_name = sAppendString(liststore_name,head->name);
    s = "combo_";
    s = sAppendString(s,head->name);
    xmlNode *child_combo = Create1ChildNode(hbox,NULL,NULL);
    xmlNode *combobox = Create1ObjectNode(child_combo,s,"GtkComboBox",NULL,NULL);
    char *combobox_prop[] = {"width_request","height_request","visible","can_focus","model","id_column"};
    char *combobox_null[] = {NULL,NULL,NULL,NULL,NULL,NULL};
    char *combobox_value[] = {"200","25","True","False",liststore_name,"1"};
    CreatePropertyNodes(combobox,combobox_prop,combobox_null, combobox_null, combobox_null,combobox_value ,6);
    //TODO signal + child 
    Create1SignalNode(combobox,"changed","on_combobox_prefix_changed",NULL, "no",NULL,NULL);
    xmlNode *CellRendererChild = Create1ChildNode(combobox,NULL,NULL);
    s = "CellRenderer_";  s = sAppendString(s,head->name);
    xmlNode *CellRenderer = Create1ObjectNode(CellRendererChild,s,"GtkComboBox",NULL,NULL);
    //TODO : create attributes here
/*    <attributes>*/
/*         <attribute name="text">0</attribute>*/
/*    </attributes>*/
    
    char *combobox_packing_prop[] = {"fill","expand","position"};
    char *combobox_packing_null[] = {NULL,NULL,NULL};
    char *combobox_packing_value[] = {"True","False","1"};
    CreatePackingNodeWithProperties(child_combo,
                                    combobox_packing_prop,
                                    combobox_packing_null,
                                    combobox_packing_null,
                                    combobox_packing_null,
                                    combobox_packing_value,3);
    
    char *hbox_packing_prop[] = {"fill","expand","position"};
    char *hbox_packing_null[] = {NULL,NULL,NULL};
    char *hbox_packing_value[] = {"True","False",int2str[pos]};
    CreatePackingNodeWithProperties(child,
                                    hbox_packing_prop,
                                    hbox_packing_null,
                                    hbox_packing_null,
                                    hbox_packing_null,
                                    hbox_packing_value,3);
                                    
}

int gtk_f_RadioButtonList(sXformsNode *head,xmlNode *node)
{
    //fprintf(stdout,"\n[%s][%d][head = %s]",__func__,__LINE__,head->name);
    xmlNode *hbox  = MakeHBoxForElements(head,node);
    int pos  = CalculatePosition(head);
    //fprintf(stdout,"\n[%s][%d][head = %s] POSITION = %d",__func__,__LINE__,head->name,pos);
    MakeLabel(head,hbox);
    // add radio elements here
    xmlNode *buttongroupchild = Create1ChildNode(hbox,NULL,NULL);
    char *s = "buttongroup_"; s = sAppendString(s,head->name);
    xmlNode *buttongrp = Create1ObjectNode(buttongroupchild,s,"GtkButtonBox",NULL,NULL);
    char *buttongrpprop[] = {"visible","can_focus","layout_style"};
    char *buttongrpnull[] = {NULL,NULL,NULL};
    char *buttongrpval[] = {"True","False","start"};
    CreatePropertyNodes(buttongrp,buttongrpprop,buttongrpnull,buttongrpnull,buttongrpnull,buttongrpval,3);
    // add 3 radio buttons for time being
    MakeRadioButton(head,buttongrp,"radiobutton1", "on_radiobutton_toggled","NOT DISCLOSE",0);
    MakeRadioButton(head,buttongrp,"radiobutton1", "on_radiobutton_toggled","MALE",1);
    MakeRadioButton(head,buttongrp,"radiobutton1", "on_radiobutton_toggled","FEMALE",2);
    PackElements(buttongroupchild,"True","False",pos);
    PackElements(hbox->parent,"True","False",pos);
}

int gtk_f_CheckBoxList(sXformsNode *head,xmlNode *node)
{
    fprintf(stdout,"\n[%s][%d][head = %s]",__func__,__LINE__,head->name);
    //vbox-1 
    // child 1 - label
    // child-2 - buttonbox
    // child-3 - btn done
    char *s = "vbox_"; s = sAppendString(s,head->name);
    xmlNode *vboxchild = Create1ChildNode(node,NULL,NULL);
    xmlNode *vbox = Create1ObjectNode(vboxchild,s,"GtkBox",NULL,NULL);
    char *vboxprop[] = {"visible","can_focus","orientation"};
    char *vboxval[] = {"True","False","vertical"};
    char *vboxnull[] = {NULL,NULL,NULL};
    CreatePropertyNodes(vbox,vboxprop,vboxnull,vboxnull,vboxnull,vboxval,3);
    //label
    MakeLabel(head,vbox);
    // add a button box
    xmlNode *buttonboxcontainer = Create1ChildNode(vbox,NULL,NULL);
    s = "ButtonBox_"; s = sAppendString(s,head->name);
    xmlNode *buttonbox = Create1ObjectNode(buttonboxcontainer,s,"GtkButtonBox",NULL,NULL);
    char *buttonboxprop[] = {"visible","can_focus","halign","orientation","layout_style"};
    char *buttonboxval[] = {"True","False","start","vertical","start"};
    char *buttonboxnull[] = {NULL,NULL,NULL,NULL,NULL};
    CreatePropertyNodes(buttonbox,buttonboxprop,buttonboxnull,buttonboxnull,buttonboxnull,buttonboxval,5);
    MakeChildButton(head,buttonbox,"onclick","newspaper1",0);
    MakeChildButton(head,buttonbox,"onclick","newspaper2",1);
    MakeChildButton(head,buttonbox,"onclick","newspaper3",2);
    PackElements(buttonboxcontainer,"True","False",1);
    // done button
    s = "done_button_"; s = sAppendString(s,head->name);
    //xmlNode *donebtncontainer = Create1ChildNode(vbox,NULL,NULL);
    xmlNode *hboxdonebtn = MakeHBoxForElements(head,vbox);
    Create1ChildNodeWithPlaceholder(hboxdonebtn,NULL,NULL);
    xmlNode *DoneButtonChild = Create1ChildNode(hboxdonebtn,NULL,NULL);
    xmlNode *DoneButton = Create1ObjectNode(DoneButtonChild,s,"GtkButton",NULL,NULL);
    char *DoneButtonProp[] = {"label","use_action_appearance","visible","can_focus","receives_default",""};
    char *DoneButtonVal[] = {head->name,"False","True","True","True"};
    char *DoneButtonTran[] = {"yes",NULL,NULL,NULL,NULL};
    char *DoneButtonNull[] = {NULL,NULL,NULL,NULL,NULL};
    CreatePropertyNodes(DoneButton,DoneButtonProp,DoneButtonTran,DoneButtonNull,DoneButtonNull,DoneButtonVal,5);
    Create1ChildNodeWithPlaceholder(hboxdonebtn,NULL,NULL);
    //PackElements(donebtncontainer,"True","False",2);
    PackElements(vboxchild,"True","False",0);
}

int CalculatePosition(sXformsNode *head)
{
    int pos = -1;
    sXformsNode *temp = head;
    for(pos=-1;temp;temp=temp->prev,pos++);
    return pos;
}

xmlNode *MakeHBoxForElements(sXformsNode *head,xmlNode *node)
{
    char *s = "hbox_";
    if(head->name == 0) s = sAppendString(s,int2str[i++]);
    else{ s = sAppendString(s,head->name); }
    xmlNode *child = Create1ChildNode(node,NULL,NULL);
    xmlNode *hbox = Create1ObjectNode(child,s,"GtkBox",NULL,NULL);
    char *hbox_prop[] = {"visible","can_focus","margin_left","margin_right","margin_top","margin_bottom"};
    char *hbox_null[] = {NULL,NULL,NULL,NULL,NULL,NULL};
    char *hbox_value[] = {"True","False","2","2","2","2"};
    CreatePropertyNodes(hbox,hbox_prop,hbox_null, hbox_null, hbox_null,hbox_value ,6);
    // need to insert nodes here
    return hbox;
}

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

void MakeLabel(sXformsNode *head,xmlNode *hbox)
{
    char *s = "lbl_";
    s = sAppendString(s,head->name);
    xmlNode *child_label = Create1ChildNode(hbox,NULL,NULL);
    xmlNode *label = Create1ObjectNode(child_label,s,"GtkLabel",NULL,NULL);
    char *label_prop[] = {"width_request","height_request","visible","can_focus","margin_right","label"};
    char *label_null[] = {NULL,NULL,NULL,NULL,NULL,NULL};
    char *label_value[] = {"100","25","True","False","10",head->name};
    char *label_trans[] = {NULL,NULL,NULL,NULL,NULL,"yes"};
    CreatePropertyNodes(label,label_prop,label_trans, label_null, label_null,label_value ,6);
    PackElements(child_label,"True","False",0);
/*    char *label_packing_prop[] = {"fill","expand","position"};*/
/*    char *label_packing_null[] = {NULL,NULL,NULL};*/
/*    char *label_packing_value[] = {};*/
/*    CreatePackingNodeWithProperties(child_label,*/
/*                                    label_packing_prop,*/
/*                                    label_packing_null,*/
/*                                    label_packing_null,*/
/*                                    label_packing_null,*/
/*                                    label_packing_value,3);*/
}

void MakeRadioButton(sXformsNode *head, xmlNode *par,char *groupname, char *handlername, char *label, int pos)
{
    char *s = "radiobutton_"; s = sAppendString(s,head->name); s = sAppendString(s,int2str[pos]);
    xmlNode *radiochild = Create1ChildNode(par,NULL,NULL);
    xmlNode *radio = Create1ObjectNode(radiochild,s,"GtkRadioButton",NULL,NULL);
    char *radio_prop[] = {"label","use_action_appearance","visible","can_focus","receives_default","xalign","draw_indicator","group"};
    char *radio_value[] = {label,"False","True","True","False","0","True",groupname};
    char *radio_null[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    char *radio_trans[] = {"yes",NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    CreatePropertyNodes(radio,radio_prop,radio_trans, radio_null, radio_null,radio_value ,8);
    Create1SignalNode(radio,"toggled",handlername, NULL, "no", NULL, NULL);
    
    PackElements(radiochild,"True","False",pos);
}

void MakeChildButton(sXformsNode *head, xmlNode *par, char *handlername, char *label, int pos)
{
    char *s = "checkbutton_"; s = sAppendString(s,head->name); s = sAppendString(s,int2str[pos]);
    xmlNode *checkbutton = Create1ChildNode(par,NULL,NULL);
    xmlNode *check = Create1ObjectNode(checkbutton,s,"GtkCheckButton",NULL,NULL);
    char *check_prop[] = {"label","use_action_appearance","width_request","visible","can_focus","receives_default","margin_top","margin_bottom","xalign","draw_indicator"};
    char *check_value[] = {label,"False","200","True","True","False","2","2","0","True"};
    char *check_null[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    char *check_trans[] = {"yes",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    CreatePropertyNodes(check,check_prop,check_trans, check_null, check_null,check_value ,10);
    Create1SignalNode(check,"toggled",handlername, NULL, "no", NULL, NULL);
    
    PackElements(checkbutton,"True","False",pos);
}

int gtk_f_InputHandler(sXformsNode *head,xmlNode *node)
{
    int pos = -1;
    // calculate the position of this element among it's siblings'
    head->meta_info = (char *)"1";
    sXformsNode *temp = head;
    for(pos=-1;temp;temp=temp->prev,pos++);
    ////////fprintf(stdout,"\n[%s][%d][head = %s] POSITION = %d",__func__,__LINE__,head->name,pos);
    char *s = "hbox_";
    s = sAppendString(s,head->name);
    xmlNode *child = Create1ChildNode(node,NULL,NULL);
    xmlNode *hbox = Create1ObjectNode(child,s,"GtkBox",NULL,NULL);
    char *hbox_prop[] = {"visible","can_focus","margin_left","margin_right","margin_top","margin_bottom"};
    char *hbox_null[] = {NULL,NULL,NULL,NULL,NULL,NULL};
    char *hbox_value[] = {"True","False","2","2","2","2"};
    CreatePropertyNodes(hbox,hbox_prop,hbox_null, hbox_null, hbox_null,hbox_value ,6);
    

    
    s = "lbl_";
    s = sAppendString(s,head->name);
    xmlNode *child_label = Create1ChildNode(hbox,NULL,NULL);
    xmlNode *label = Create1ObjectNode(child_label,s,"GtkLabel",NULL,NULL);
    char *label_prop[] = {"width_request","height_request","visible","can_focus","margin_right","label"};
    char *label_null[] = {NULL,NULL,NULL,NULL,NULL,NULL};
    char *label_value[] = {"100","25","True","False","10",head->name};
    char *label_trans[] = {NULL,NULL,NULL,NULL,NULL,"yes"};
    CreatePropertyNodes(label,label_prop,label_trans, label_null, label_null,label_value ,6);
    
    char *label_packing_prop[] = {"fill","expand","position"};
    char *label_packing_null[] = {NULL,NULL,NULL};
    char *label_packing_value[] = {"True","False","0"};
    CreatePackingNodeWithProperties(child_label,
                                    label_packing_prop,
                                    label_packing_null,
                                    label_packing_null,
                                    label_packing_null,
                                    label_packing_value,3);
    s = "entry_";
    s = sAppendString(s,head->name);
    xmlNode *child_entry = Create1ChildNode(hbox,NULL,NULL);
    xmlNode *entry = Create1ObjectNode(child_entry,s,"GtkEntry",NULL,NULL);
    char *entry_prop[] = {"width_request","visible","can_focus","invisible_char"};
    char *entry_null[] = {NULL,NULL,NULL,NULL};
    char *entry_value[] = {"200","True","True","*"};
    CreatePropertyNodes(entry,entry_prop,entry_null, entry_null, entry_null,entry_value ,4);
    
    char *entry_packing_prop[] = {"fill","expand","position"};
    char *entry_packing_null[] = {NULL,NULL,NULL};
    char *entry_packing_value[] = {"True","False","1"};
    CreatePackingNodeWithProperties(child_entry,
                                    entry_packing_prop,
                                    entry_packing_null,
                                    entry_packing_null,
                                    entry_packing_null,
                                    entry_packing_value,3);
                                    
    char *hbox_packing_prop[] = {"fill","expand","position"};
    char *hbox_packing_null[] = {NULL,NULL,NULL};
    char *hbox_packing_value[] = {"True","False",int2str[pos]};
    CreatePackingNodeWithProperties(child,
                                    hbox_packing_prop,
                                    hbox_packing_null,
                                    hbox_packing_null,
                                    hbox_packing_null,
                                    hbox_packing_value,3);
}

int gtk_f_LabelHandler(sXformsNode *head,xmlNode *node)
{
    //fprintf(stdout,"\n[%s][%d][head = %s]",__func__,__LINE__,head->name);
    char *s = "label_"; s = sAppendString(s,int2str[i++]);
    head->meta_info = (char *)"1";
    head->name = s;
    xmlNode *hbox  = MakeHBoxForElements(head,node);
    int pos  = CalculatePosition(head);
    //fprintf(stdout,"\n[%s][%d][head = %s] POSITION = %d",__func__,__LINE__,head->name,pos);
    MakeLabel(head,hbox);
    PackElements(hbox->parent,"True","False",pos);
}

int gtk_f_ButtonHandler(sXformsNode *head,xmlNode *node)
{
    //////fprintf(stdout,"\n[%s][%d][head = %s]",__func__,__LINE__,head->name);
    int pos = -1;
    head->meta_info = (char *)"1";
    // calculate the position of this element among it's siblings'
    sXformsNode *temp = head;
    for(pos=-1;temp;temp=temp->prev,pos++);
    //////fprintf(stdout,"\n[%s][%d][head = %s] POSITION = %d",__func__,__LINE__,head->name,pos);
    
    char *s = "hbox_";
    s = sAppendString(s,head->name);
    
    xmlNode *child = Create1ChildNode(node,NULL,NULL);
    xmlNode *hbox = Create1ObjectNode(child,s,"GtkBox",NULL,NULL);
    char *hbox_prop[] = {"visible","can_focus","margin_left","margin_right","margin_top","margin_bottom"};
    char *hbox_null[] = {NULL,NULL,NULL,NULL,NULL,NULL};
    char *hbox_value[] = {"True","False","2","2","2","2"};
    CreatePropertyNodes(hbox,hbox_prop,hbox_null, hbox_null, hbox_null,hbox_value ,6);
    
    Create1ChildNodeWithPlaceholder(hbox,NULL,NULL);
    xmlNode *btnchild = Create1ChildNode(hbox,NULL,NULL);
    s = "btn_";
    s = sAppendString(s,head->name);
    xmlNode *button = Create1ObjectNode(btnchild,s,"GtkButton",NULL,NULL);
    char *button_prop[] = {"visible","can_focus","label","use_action_appearance","receives_default","use_action_appearance"};
    char *button_null[] = {NULL,NULL,NULL,NULL,NULL,NULL};
    char *button_trans[] = {NULL,NULL,"yes",NULL,NULL,NULL};
    char *button_value[] = {"True","True","Done","False","True","False"};
    CreatePropertyNodes(button,button_prop,button_trans, button_null, button_null,button_value ,6);
    Create1SignalNode(button,"clicked","on_btn_clicked", NULL,"no",NULL,NULL);
    char *button_packing_prop[] = {"fill","expand","position"};
    char *button_packing_null[] = {NULL,NULL,NULL};
    char *button_packing_value[] = {"True","False","1"};
    CreatePackingNodeWithProperties(btnchild,
                                    button_packing_prop,
                                    button_packing_null,
                                    button_packing_null,
                                    button_packing_null,
                                    button_packing_value,3);
    Create1ChildNodeWithPlaceholder(hbox,NULL,NULL);
    
    char *hbox_packing_prop[] = {"fill","expand","position"};
    char *hbox_packing_null[] = {NULL,NULL,NULL};
    char *hbox_packing_value[] = {"True","False",int2str[pos]};
    CreatePackingNodeWithProperties(child,
                                    hbox_packing_prop,
                                    hbox_packing_null,
                                    hbox_packing_null,
                                    hbox_packing_null,
                                    hbox_packing_value,3);
}


int gtk_f_RangeHandler(sXformsNode *head,xmlNode *node)
{
    ////////fprintf(stdout,"\n[%s][%d]",__func__,__LINE__);
}



