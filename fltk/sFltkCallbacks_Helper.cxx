#include <malloc.h>
#include <string.h>
#include "../misc/misc.h"
#include "sFltk.h"

struct FltkCallbackData * AllocateMemoryForFltkCBNode()
{
    struct FltkCallbackData *node = (struct FltkCallbackData *)malloc(sizeof(struct FltkCallbackData ));
    if ((node) == NULL)
    {
        fprintf(stdout,"\n could not allocate memory");
        (node) = (struct FltkCallbackData *)0;
    }
    else
    {
        (node)->ref = (char *)0;
        (node)->init_val= (char *)0;
        (node)->value= (char *)0;
        (node)->name= (char *)0;
        (node)->meta_info= (char *)0;
        (node)->next = (struct FltkCallbackData *)0;
        (node)->prev= (struct FltkCallbackData *)0;
        (node)->nextref = (struct FltkCallbackData *)0;
    }
    return node;
}

struct FltkCallbackData * AppendNode(struct FltkCallbackData **head,char *ref_, char *init_val_,char *value_,char *name_,char *meta_info_){
    /*
    1. allocate memory
    2. adjust the values
    3. adjust pointers
    4. return pointers to this node
    */
    //fprintf(stdout,"\n ==> , head = %s, name = %s, meta = %s",(*head) != 0 ? (*head)->name : "null",name_,meta_info_);
    static int i = -1;
    i++;
    struct FltkCallbackData *newnode = AllocateMemoryForFltkCBNode();
    if( newnode != 0){
        newnode->ref = s_dupstr(ref_);
        newnode->name = s_dupstr(name_);
        newnode->value = s_dupstr(value_);
        newnode->init_val = s_dupstr(init_val_);
        newnode->meta_info = s_dupstr(meta_info_);
        struct FltkCallbackData *temp = (*head);
        if( (*head) == 0){
            // no node in the system
            (*head) = newnode;
        }
        else
        {
            while( temp->next != 0){
                temp = temp->next;
            }
            temp->next = newnode;
            newnode->prev = temp;
        }
    }
    return newnode;
}

struct FltkCallbackData * MakeDummy()
{
    struct FltkCallbackData *head = (struct FltkCallbackData *)0;
    struct FltkCallbackData *btn =  AppendNode(&head,"btn_personal_info", "NULL","NULL","BtnDone_Main","QPushButton");
    struct FltkCallbackData *btn1 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","BtnPersonalInfoDone","QPushButton");
    struct FltkCallbackData *btn2 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","BtnLoginInfoDone","QPushButton");
    struct FltkCallbackData *btn3 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","BtnProjectInsertDone","QPushButton");//
    struct FltkCallbackData *btn4 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","BtnSliderValueDone","QPushButton");
    struct FltkCallbackData *dd1 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","PersonalInfo_NamePrefix","QComboBox");
    struct FltkCallbackData *radio_button1 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","radioButton_male","QRadioButton");
    struct FltkCallbackData *radio_button2 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","radioButton_female","QRadioButton");
    struct FltkCallbackData *radio_button3 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","radioButton_none","QRadioButton");
    struct FltkCallbackData *check_button1 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","checkBox_newspaper1","QCheckBox");
    struct FltkCallbackData *check_button2 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","checkBox_newspaper2","QCheckBox");
    struct FltkCallbackData *check_button3 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","checkBox_newspaper3","QCheckBox");
    struct FltkCallbackData *check_button4 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","checkBox_newspaper4","QCheckBox");
    struct FltkCallbackData *check_button5 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","checkBox_newspaper5","QCheckBox");
    struct FltkCallbackData *slider =  AppendNode(&head,"btn_personal_info", "NULL","NULL","SliderDemo","QSlider");
    //struct FltkCallbackData *CheckBtn1 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","checkbutton_newpaper1","GtkCheckButton");
    //struct FltkCallbackData *CheckBtn2 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","checkbutton_newpaper3","GtkCheckButton");
    //struct FltkCallbackData *CheckBtn3 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","checkbutton_newpaper5","GtkCheckButton");
    //struct FltkCallbackData *btn1 =  AppendNode(&btn->nextref,"ref2", "init_val","value","combobox_prefix","GtkComboBox");
    //struct FltkCallbackData *btn2 =  AppendNode(&btn->nextref,"ref2", "init_val","value","entry_FirstName","GtkEntry");
    //struct FltkCallbackData *btn3 =  AppendNode(&btn->nextref,"ref2", "init_val","value","entry_MiddleName","GtkEntry");
    //struct FltkCallbackData *btn31 =  AppendNode(&btn->nextref,"ref2", "init_val","value","entry_LastName","GtkEntry");
    //struct FltkCallbackData *btn32 =  AppendNode(&btn->nextref,"ref2", "init_val","value","entry_dob","GtkEntry");//entry_dob
    //struct FltkCallbackData *btn33 =  AppendNode(&btn->nextref,"ref2", "init_val","value","radiobutton_nothing","GtkRadioButton");
    //struct FltkCallbackData *btn4 =  AppendNode(&head,"combobox_prefix", "init_val","value","combobox_prefix","GtkComboBox");

    return head;
}


void print_user_data(struct FltkCallbackData *head)
{
    struct FltkCallbackData *temp = head;
    struct FltkCallbackData *temp2;
    fprintf(stdout,"\n == PRINTING USER DATA == \n");
    while( temp != 0)
    {
        fprintf(stdout,"\n( %s,%s,%s,%s,%s )",temp->ref,temp->init_val,temp->value,temp->name,temp->meta_info);
        temp2 = temp->nextref;
        while( temp2 )
        {
            fprintf(stdout,"\n\t -> ( %s,%s,%s,%s,%s )",temp2->ref,temp2->init_val,temp2->value,temp2->name,temp2->meta_info);
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    fprintf(stdout,"\n");
}

struct FltkCallbackData *get_pointer_to_user_data_by_name(const char *_name, struct FltkCallbackData *head)
{
    struct FltkCallbackData *temp = head;
    while(temp!=0)
    {
        //printf("\n\t\t COM : %s, %s",_name,temp->name);
        if( !(strcmp(_name,temp->name)))
        {
            return temp;
        }
        temp = temp->next;
    }
    return (struct FltkCallbackData *)0;
}

