#include "sFltk.h"
#include "../simpleUI.h"
#include "../sXforms.h"

void test_widgets(){
	Fl_Group *parent = Fl_Group::current();
	if(!parent){
		fprintf(stderr,"could not find parent");
	}
	else{
		
	}
}

void sGenerateUIFromTree(sXformsNode * head)
{
	//fprintf(stdout,"\n === PRINTING NODE TREE ===");
	if( head == 0 ){
		fprintf(stdout,"\n Head node passed is null");
	}
	else{
		sXformsNode *temp ;
		for( temp = head->child; temp != 0 ; temp=temp->next){
			//fprintf(stdout,"\n\t %s : %s",temp->type,temp->name);
			sPrintsXformsNode(temp);
			if( temp->child == 0){
				fprintf(stdout,"\t\t-- NO CHILD ---\n");
			}else{
				fprintf(stdout,"\n\t------------- chilren -------------\n");
				sGenerateUIFromTree(temp);
				fprintf(stdout,"\n\t------------- chilren end -------------\n");
			}
		}
	}
}


