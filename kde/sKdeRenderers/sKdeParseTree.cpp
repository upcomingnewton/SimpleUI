#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "sKdeRenderer.h"
#include "../../simpleUI.h"
#include "../../sXforms.h"
#include "../sKdeCallbacks/sKde_Cb.h"
#include "../../xml/sXml.h"

char *int2str[] = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19"};
int i = 0;
int row = 0;
int column = 0;
sKdeUIHandlers handler[100];
struct sKdeUIHandlers_data kde_handlers[] = {
	{
		(char *)"xf:select1",
  		(char *)"drop downs",
  		(char *)0,
  		(char *)0,
  		0,
  		(sKdeUIHandlers)kde_f_Select1Handler
	},
	{
		(char *)"xf:select1",
  		(char *)"radio button list",
		(char *)"appearance",
		(char *)"full",
		1,
  		(sKdeUIHandlers)kde_f_RadioButtonList
	},
	{
		(char *)"xf:select",
		(char *)"check box list",
		(char *)"appearance",
		(char *)"full",
		1,
		(sKdeUIHandlers)kde_f_CheckBoxList
	},
	{
		(char *)"xf:input",
  		(char *)"xf-input",
  		(char *)0,
  		(char *)0,
  		0, // generic for now
  		(sKdeUIHandlers)kde_f_InputHandler
	},
	{
	    (char *)"xf:secret",
	    (char *)"password",
	    (char *)0,
	    (char *)0,
	    0,
	    (sKdeUIHandlers)kde_f_InputHandler
	},
	{
	    (char *)"xf:textarea",
	    (char *)"password",
	    (char *)0,
	    (char *)0,
	    0,
	    (sKdeUIHandlers)kde_f_InputHandler
	},
	{
		(char *)"xf:output",
  		(char *)"xf-output",
  		(char *)0,
  		(char *)0,
  		0, // generic for now
  		(sKdeUIHandlers)kde_f_LabelHandler
	},
	{
		(char *)"xf:trigger",
  		(char *)"xf-button",
  		(char *)0,
  		(char *)0,
  		0,
  		(sKdeUIHandlers)kde_f_ButtonHandler
	},
	{
		(char *)"xf:group",
		(char *)"xf-group-tabs-handler",
		(char *)"type",
		(char *)"tabs",
		0,
		(sKdeUIHandlers)kde_f_TabsHandler
	},
		{
		(char *)"xf:group",
		(char *)"start a new frame or a box",
		(char *)"type",
		(char *)"frame",
		1,
		(sKdeUIHandlers)kde_f_FrameHandler
	},
	{
		(char *)"xf:range",
		(char *)"xf-sliders",
		(char *)0,
		(char *)0,
		0,
		(sKdeUIHandlers)kde_f_RangeHandler
	},
	{
		(char *)0,
  		(char *)0,
  		(char *)0,
  		(char *)0,
  		1,
  		(sKdeUIHandlers)0
	}
};


struct qt_cb_data * sKdeGenerateGladeFile(sXformsNode *head)
{
    xmlDoc *doc = NULL;
    xmlNode *root_node = NULL;
    xmlNode *current_node = NULL;
    /* required for every window */
    doc = xmlNewDoc(BAD_CAST"1.0");  // create a new document
    root_node = xmlNewNode(NULL,BAD_CAST"ui");  // root node
    CreateNodeAttribute(root_node,"version","4.0");
    xmlDocSetRootElement(doc, root_node); // set root node
    xmlNode *classname = Create1ObjectNode(root_node,"class", "SimpleUiKde"); // create main window
    xmlNode * classwidget = Create1WidgetNodeWithStringProp(root_node,"classwidget","QWidget","windowTitle",sKDE_MAIN_WINDOW_NAME);
    Create1GeometryProp(classwidget,"0","0",KDE_WINDOW_WIDTH, KDE_WINDOW_HEIGHT);
    xmlNode *main_layout = CreateLayout(classwidget,"QVBoxLayout","verticalLayout_2");
      xmlNode *ContentItem = CreateItemNode(main_layout,0,0,0);
      
      
       xmlNode *lowerBarItem = CreateItemNode(main_layout,0,0,0);
       xmlNode *horizontalLayout2 = CreateLayout(lowerBarItem,"QHBoxLayout","horizontalLayout2");
       xmlNode *horizontalLayout2Item = CreateItemNode(horizontalLayout2,0,0,0);
       xmlNode *horizontalLayout = CreateLayout(horizontalLayout2Item,"QHBoxLayout","horizontalLayout");
       xmlNode *spacer = CreateSpacer(horizontalLayout,"horizontalSpacer","Qt::Horizontal","40","20");
       xmlNode *DoneBtnItem = CreateItemNode(horizontalLayout,0,0,0);
       xmlNode *DoneBtn = Create1WidgetNodeWithStringProp(DoneBtnItem,"BtnDone_Main","QPushButton","text","Done");
    
    xmlNode *layoutdefault = CreateXmlNode(NULL,"layoutdefault");
    CreateNodeAttribute(layoutdefault,"spacing","6");
    CreateNodeAttribute(layoutdefault,"margin","11");
    xmlNode *resources = CreateXmlNode(NULL,"resources");

    struct qt_cb_data *temp = (struct qt_cb_data *)0;
    sKdeGenerateUIFromTree(head,ContentItem,&temp);
    // main content area
    xmlSaveFormatFileEnc(sKDE_UI_FILE, doc, "UTF-8", 1); // save file
    xmlFreeDoc(doc);  // free document
    xmlCleanupParser();  //clean parse
    return temp;
}

int sKdeGenerateUIFromTree(sXformsNode * head, xmlNode *par,struct qt_cb_data **cb_data_head)
{
if( head == 0 ){
	//fprintf(stderr,"\n no data to read from");
	exit(1);
}
else{
	sXformsNode *temp ;
	int x = 0;
	for( temp = head->child;(( temp != 0 ) ) ; temp=temp->next){
	 //fprintf(stdout,"\n %s:%s,%s",temp->type,temp->name,temp->private_data);
		if( temp->meta_info && !strcmp(temp->meta_info,"1")){
			continue;
		}
		//fprintf(stdout,"\n cp-1");
		x = 0;
		if(temp->attr){
			while(kde_handlers[x].type != 0){
	if( !strcmp(temp->type,kde_handlers[x].type)){
				sXformsNodeAttr *tempattr;
				for( tempattr = temp->attr; tempattr; tempattr=tempattr->next){
					if( (kde_handlers[x].attrname) && (kde_handlers[x].attrvalue) && ( !strcmp(tempattr->attrName,kde_handlers[x].attrname) && !strcmp(tempattr->attrValue,kde_handlers[x].attrvalue))){
						//fprintf(stdout,"\t 'specialised'");
						fprintf(stdout,"\n[%s][%d] start specialised %s:%s",__func__,__LINE__,temp->type,temp->name);
						kde_handlers[x].handler(temp,par,cb_data_head);
						temp->meta_info = (char *)"1";  //node visited
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
			while(kde_handlers[x].type != 0){
			if( !strcmp(temp->type,kde_handlers[x].type) && !kde_handlers[x].strict){
			    //fprintf(stdout,"\t 'generic'");
				fprintf(stdout,"\n[%s][%d] start generic %s:%s",__func__,__LINE__,temp->type,temp->name);
				kde_handlers[x].handler(temp,par,cb_data_head);
				temp->meta_info = (char *)"1";  //node visited
				break;
			}
			x++;
			}
		}
		if( temp->child == 0){
			continue;
		}else{
			sKdeGenerateUIFromTree(temp,par,cb_data_head);
		}}
	}
return 0;
}


int kde_f_TabsHandler(sXformsNode *head,xmlNode *node,struct qt_cb_data **cb_data_head)
{
  //fprintf(stdout,"\n[%s][%d][head = %s,%s]",__func__,__LINE__,head->type,head->name);
 	head -> meta_info = (char *)"1"; 
 	sXformsNodeAttr xf_trigger_attr = {"type","tab_trigger",(char *)0,(char *)0,(sXformsNodeAttr *)0,(sXformsNodeAttr *)0}; 
 	int flag_t = 1; 
 	sXformsNode *xftrigger = SearchSubTreeForNodes(head,(char *)"xf:trigger",&xf_trigger_attr,0,1); 
 	if( xftrigger != 0){ 
     char *propname[] = {"currentIndex"};
     char *proptype[] = {"number"};
     char *propval[] = {"0"};
     xmlNode *MaintabWidget  = Create1WidgetNode(node,"TabWidget","QTabWidget",propname,proptype,propval,1);
     
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
 				printf("\n ========================== %s",xftrigger->name);
      xmlNode *TabWidget = Create1WidgetNode(MaintabWidget, sAppendString("Tab_",xftrigger->name),"QWidget",0,0,0,0);
      CreateStringAttribute(TabWidget,xftrigger->name);
      xmlNode *TabVerticalLayout = CreateLayout(TabWidget,"QVBoxLayout",sAppendString("Tab_VerticalLayout_",xftrigger->name) );
      xmlNode *TabVerticalLayoutItem = CreateItemNode(TabVerticalLayout,0,0,0);
      xmlNode *TabScrollWidget = Create1WidgetNode(TabVerticalLayoutItem,sAppendString("Tab_QScrollArea_",xftrigger->name),"QScrollArea",0,0,0,0);
      Create1PropertyNode(TabScrollWidget,"widgetResizable","bool", "true");
      xmlNode *TabScrollWidgetContent = Create1WidgetNode(TabScrollWidget,sAppendString("Tab_QScrollAreaContent_",xftrigger->name),"QWidget",0,0,0,0);
      Create1GeometryProp(TabScrollWidgetContent,"0", "0", "639","342");
      xmlNode *ContentLayout = CreateLayout(TabScrollWidgetContent,"QVBoxLayout",sAppendString("verticalLayout",xftrigger->name) );
      sKdeGenerateUIFromTree(tab_content,ContentLayout ,cb_data_head); 
      i++; 
 					} 
 				} 
 			} 
 		}else{ 
 			//fprintf(stdout,"\n[%s][%d]ERROR MAKING TABS",__FILE__,__LINE__); 
 			exit(1); 
 		} 
 		xftrigger->meta_info = (char *)"1"; 
 		xftrigger  =  SearchSubTreeForNodes(head,(char *)"xf:trigger",&xf_trigger_attr,0,1); 
 	}} 
 	else 
 	{ 
 	    //fprintf(stdout,"\n[%s:%s] COULD NOT PARSE",head->name,head->type); 
 	} 
     return 0; 
}

int kde_f_FrameHandler(sXformsNode *head,xmlNode *node,struct qt_cb_data **cb_data_head)
{

     int i = 0; 
     sXformsNode *temp = head; 
     head -> meta_info = (char *)"1"; 
     for( i = 0; temp;  i++, temp = temp->next) 
     {
        fprintf(stdout,"\n[%s][%d] HEAD = %s:%s \t\t NODE = %s",__func__,__LINE__,temp->name, temp->type,node->name);
        row = 0;
        xmlNode *ItemContent = CreateItemNode(node,0,0,0);
        xmlNode *GridLayout = CreateLayout(ItemContent,"QGridLayout",sAppendString("Layout_",head->name) );
        temp -> meta_info = (char *)"1"; 
        sPrintsXformsTree(temp);
        sKdeGenerateUIFromTree(temp,GridLayout ,cb_data_head); 
        CreateSpacer(node,sAppendString("Spacer_",head->name),"Qt::Vertical","20","40");
     } 
     fprintf(stdout,"\n[%s][%d] NUMBER OF CHILDREN %d",__func__,__LINE__,i); 
}

int kde_f_Select1Handler(sXformsNode *head,xmlNode *node,struct qt_cb_data **cb_data_head)
{
    static int ddctr = 0;
    head->meta_info = (char *)"1";
    
    xmlNode *lblitem = CreateItemNode(node,0,int2str[row],int2str[0]);
    Create1WidgetNodeWithStringProp(lblitem,sAppendString("Label_",sAppendString("DDlbl_",int2str[ddctr])), "QLabel","text", head->name); 
    
    xmlNode *dditem = CreateItemNode(node,0,int2str[row],int2str[2]);
    xmlNode *dd = Create1WidgetNode(dditem,sAppendString("DD_",int2str[ddctr]),"QComboBox",0,0,0,0);
    
    sXformsNode *temp;
    sXformsNode *xfchoices = SearchSubTreeForNodes(head,(char *)"xf:choices",(sXformsNodeAttr *)0,0,0);
    if( xfchoices ){
			xfchoices->meta_info = (char *)"1";
			for( temp=xfchoices->child; temp != 0; temp=temp->next){
			    temp->meta_info = int2str[1];
          xmlNode *choice = CreateItemNode(dd,0,0,0);
          CreateStringProperty(choice,"text", temp->name);
			}
    }
    ddctr++;
    row++;
}


int kde_f_RadioButtonList(sXformsNode *head,xmlNode *node,struct qt_cb_data **cb_data_head)
{
    static int radioctr = 0;
    head->meta_info = (char *)"1";
  
    xmlNode *lblitem = CreateItemNode(node,0,int2str[row],int2str[0]);
    Create1WidgetNodeWithStringProp(lblitem,sAppendString("DDlbl_",int2str[radioctr]), "QLabel","text", head->name); 
    xmlNode *radioitem = CreateItemNode(node,0,int2str[row],int2str[2]);
    char *proptype[] = {"string","bool","bool"};
    char *propname[] = {"title","checkable","checked"};
    char *propval[] = {(char *)0,"false","false"};
    xmlNode *QGroupBox = Create1WidgetNode(radioitem,sAppendString("QGroupBox_",int2str[radioctr]), "QGroupBox",propname,proptype,propval,3);    
    sXformsNode *temp;
    sXformsNode *xfchoices = SearchSubTreeForNodes(head,(char *)"xf:choices",(sXformsNodeAttr *)0,0,0);
    if( xfchoices ){
			xfchoices->meta_info = (char *)"1";
			int ctr = 0;
			for( temp=xfchoices->child; temp != 0; ctr++, temp=temp->next){
			    char buffer[5];
			    sprintf(buffer,"%d",5 + 80*ctr);
			    temp->meta_info = int2str[1];
			    xmlNode *radio = Create1WidgetNode(QGroupBox,sAppendString("radio_",int2str[ctr]),"QRadioButton",0,0,0,0);
          Create1GeometryProp(radio,buffer,"0","108", "26"); 
          CreateStringProperty(radio,"text",temp->name);
			}
    }
    radioctr++;
    row++;
}

int kde_f_CheckBoxList(sXformsNode *head,xmlNode *node,struct qt_cb_data **cb_data_head)
{
    static int checkboxctr = 0;
    head->meta_info = (char *)"1"; 
    sXformsNode *temp;
    sXformsNode *xfchoices = SearchSubTreeForNodes(head,(char *)"xf:choices",(sXformsNodeAttr *)0,0,0);
    if( xfchoices ){
			xfchoices->meta_info = (char *)"1";
			int ctr = 0;
			for( temp=xfchoices->child; temp != 0; ctr++,row++, temp=temp->next){
			    xmlNode *item = CreateItemNode(node,0,int2str[row],int2str[0]);
			    temp->meta_info = int2str[1];
          Create1WidgetNodeWithStringProp(item,sAppendString("CheckBox_",int2str[checkboxctr++]),"QCheckBox","text",temp->name);
			}
    }
    row++;
}

int kde_f_InputHandler(sXformsNode *head,xmlNode *node,struct qt_cb_data **cb_data_head)
{
    static int inputctr = 0;
    head->meta_info = (char *)"1";
    xmlNode *lblitem = CreateItemNode(node,0,int2str[row],int2str[0]);
    Create1WidgetNodeWithStringProp(lblitem,sAppendString("Label_",sAppendString("Inputlbl_",int2str[inputctr])), "QLabel","text", head->name); 
    xmlNode *inputitem = CreateItemNode(node,0,int2str[row],int2str[2]);
    Create1WidgetNode(inputitem,sAppendString("Input_",int2str[inputctr]),"QLineEdit",0,0,0,0);
    row++;
    inputctr++;
}

int kde_f_LabelHandler(sXformsNode *head,xmlNode *node,struct qt_cb_data **cb_data_head)
{
    static int labelctr = 0;
    head->meta_info = (char *)"1";
    xmlNode *item = CreateItemNode(node,0,int2str[row++],int2str[0]);
    Create1WidgetNodeWithStringProp(item,sAppendString("Label_",int2str[labelctr++]), "QLabel","text", "NULL"); //TODO fix naming issue
}

int kde_f_ButtonHandler(sXformsNode *head,xmlNode *node,struct qt_cb_data **cb_data_head)
{
    static int btnctr = 0;
    head->meta_info = (char *)"1";
    xmlNode *item = CreateItemNode(node,0,int2str[row++],int2str[0]);
    Create1WidgetNodeWithStringProp(item,sAppendString("Btn_",int2str[btnctr++]), "QPushButton","text", head->name);
}

int kde_f_RangeHandler(sXformsNode *head,xmlNode *node,struct qt_cb_data **cb_data_head)
{
    fprintf(stdout,"\n[%s][%d] HEAD = %s:%s \t\t NODE = %s",__func__,__LINE__,head->name, head->type,node->name);
    static int sliderctr = 0;
    xmlNode *lblitem = CreateItemNode(node,0,int2str[row++],int2str[0]);
    Create1WidgetNodeWithStringProp(lblitem,sAppendString("LabelSlider_",int2str[sliderctr++]), "QLabel","text", head->name); 
    xmlNode *item = CreateItemNode(node,0,int2str[row++],int2str[0]);
    char *proptype[] = {"number","number","enum","enum","number"};
    char *propval[] = {"100","50","Qt::Horizontal","QSlider::TicksBothSides","5"};
    char *propname[] = {"maximum","value","orientation","tickPosition","tickInterval"};
    Create1WidgetNode(item,sAppendString("Slider_",int2str[sliderctr++]),"QSlider",propname,proptype,propval,5);
}



