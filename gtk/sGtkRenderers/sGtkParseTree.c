#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "sGtkRenderer.h"
#include "../../simpleUI.h"
#include "../../sXforms.h"


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
  		1,
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
    fprintf(stdout,"\n yes, it is working fine");
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
	fprintf(stderr,"\n no data to read from");
	exit(1);
}
else{
	sXformsNode *temp ;
	int x = 0;
	for( temp = head->child;(( temp != 0 ) ) ; temp=temp->next){
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
    fprintf(stdout,"\n[%s][%d][head = %s]",__func__,__LINE__,head->type);
    char *int2str[] = {"0","1","2","3","4","5","6","7","8","9"};
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
			fprintf(stdout,"\n ATTRIBUTE NAME = %s, and VALUE = %s",attr->name,xmlNodeListGetString(node->doc,attr->children,1));
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
						fprintf(stdout, "\n\t\t\t\t implement tabs here");
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
/*                        <child>*/
/*                          <object class="GtkViewport" id="ViewportScrollWindowTabWelcome">*/
/*                            <property name="visible">True</property>*/
/*                            <property name="can_focus">False</property>*/
/*                            <child>*/
/*                              <placeholder/>*/
/*                            </child>*/
/*                          </object>*/
/*                        </child>*/
/*                      </object>*/
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
                        if( i == 0){
                        }

                    
                    
/*						tab_content->meta_info = (char *)"1";*/
/*						tabs->begin();*/
/*						Fl_Group *new_group = new Fl_Group(tabs->x(),tabs->y() + TAB_HEIGHT,tabs->w(),tabs->h()-TAB_HEIGHT - VER_SEP,xftrigger->name);*/
/*						new_group->begin();*/
/*						{*/
/*						char *s = "pack_";*/
/*						s = sAppendString(s,xftrigger->name);*/
/*						//Fl_Pack *tabs_content_pack = new Fl_Pack(new_group->x() + HOR_SEP,new_group->y() + VER_SEP,new_group->w() - 2*HOR_SEP,new_group->h() - 2*VER_SEP,s);{*/
/*							//tabs_content_pack->color(FL_RED);*/
/*							//tabs_content_pack->begin();*/
/*							sGenerateUIFromTree(tab_content);*/
/*						//}*/
/*						//tabs_content_pack->end();*/
/*						}*/
/*						new_group->end();*/
/*						tabs->end();*/
					}
				}
			}
		}else{
			fprintf(stdout,"\n[%s][%d]ERROR MAKING TABS",__FILE__,__LINE__);
			exit(1);
		}
		xftrigger->meta_info = (char *)"1";
		xftrigger  =  SearchSubTreeForNodes(head,(char *)"xf:trigger",&xf_trigger_attr,0,1);
	}}
    return 0;
}

int gtk_f_Select1Handler(sXformsNode *head,xmlNode *node)
{
    fprintf(stdout,"\n[%s][%d][head = %s]",__func__,__LINE__,head->name);
}

int gtk_f_RadioButtonList(sXformsNode *head,xmlNode *node)
{
    fprintf(stdout,"\n[%s][%d][head = %s]",__func__,__LINE__,head->name);
}

int gtk_f_CheckBoxList(sXformsNode *head,xmlNode *node)
{
    fprintf(stdout,"\n[%s][%d][head = %s]",__func__,__LINE__,head->name);
}

int gtk_f_InputHandler(sXformsNode *head,xmlNode *node)
{
    fprintf(stdout,"\n[%s][%d][head = %s]",__func__,__LINE__,head->name);
}

int gtk_f_LabelHandler(sXformsNode *head,xmlNode *node)
{
    fprintf(stdout,"\n[%s][%d][head = %s]",__func__,__LINE__,head->name);
}

int gtk_f_ButtonHandler(sXformsNode *head,xmlNode *node)
{
    fprintf(stdout,"\n[%s][%d][head = %s]",__func__,__LINE__,head->name);
}


int gtk_f_FrameHandler(sXformsNode *head,xmlNode *node)
{
    fprintf(stdout,"\n[%s][%d]",__func__,__LINE__);
}

int gtk_f_RangeHandler(sXformsNode *head,xmlNode *node)
{
    fprintf(stdout,"\n[%s][%d]",__func__,__LINE__);
}



