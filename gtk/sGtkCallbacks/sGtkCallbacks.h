#ifndef S_GTK_CALLBACKS_H
#define S_GTK_CALLBACKS_H
#include <gtk/gtk.h>
    // ds
    struct gtk_cb_data{
	char *ref;
	char *init_val;
	char *value;
	char *name;
	char *meta_info;
	struct gtk_cb_data *next;
	struct gtk_cb_data *prev;
	struct gtk_cb_data *nextref;	
    };
    // sGtkCallbacks.c
    gboolean  on_window_destroy  (GtkWidget *widget,GdkEvent  *event, gpointer   user_data) ;
    void on_btn_clicked(GtkButton *btn , gpointer user_data);
    void on_combobox_changed(GtkComboBox *widget, gpointer user_data);
    void on_radiobutton_toggled(GtkToggleButton *togglebutton,gpointer user_data);
    void on_checkbutton_toggled(GtkToggleButton *togglebutton,gpointer user_data);
    
    //helper
    int SearchWidget(GtkWidget *container, char *search_name,GtkWidget **t);
    
    //// sGtkCallbacks_GetValues.c
    char * getGtkWidgetValue(char *type, GtkWidget *widget);
    char * sGetValueOfTextBox(GtkWidget *widget);
    char * sGetValueOfComboBox(GtkWidget *widget);
    char * sGetValueOfRadioButton(GtkWidget *widget);
    char * sGetValueOfCheckButton(GtkWidget *widget);
    
    //sGtkCallbacks_HelperFunctions
    struct gtk_cb_data * AllocateMemoryForGtkCBNode();
    struct gtk_cb_data * AppendNode(struct gtk_cb_data **head,char *ref_, char *init_val_,char *value_,char *name_,char *meta_info_);
    struct gtk_cb_data * MakeDummy();
    struct gtk_cb_data *get_pointer_to_user_data_by_name(const char *_name, struct gtk_cb_data *head);
    void print_user_data(struct gtk_cb_data *head);
#endif
