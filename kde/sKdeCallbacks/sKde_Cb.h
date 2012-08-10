#ifndef SIMPLE_UI_KDE_CB_H
#define SIMPLE_UI_KDE_CB_H

struct qt_cb_data{
    char *ref;
    char *init_val;
    char *value;
    char *name;
    char *meta_info;
    struct qt_cb_data *next;
    struct qt_cb_data *prev;
    struct qt_cb_data *nextref;
};

//sQtCallbacks_HelperFunctions
    struct qt_cb_data * AllocateMemoryForQtCBNode();
    struct qt_cb_data * AppendNode(struct qt_cb_data **head,char *ref_, char *init_val_,char *value_,char *name_,char *meta_info_);
    struct qt_cb_data * MakeDummy();
    struct qt_cb_data *get_pointer_to_user_data_by_name(const char *_name, struct qt_cb_data *head);
    void print_user_data(struct qt_cb_data *head);

#endif // SAMPLE1_CB_H

