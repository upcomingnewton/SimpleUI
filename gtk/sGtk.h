
#include <gtk/gtk.h>


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

gboolean  on_window_destroy  (GtkWidget *widget,GdkEvent  *event, gpointer   user_data);
void on_btn_personal_info_clicked(GtkButton *button, gpointer user_data);
void on_combobox_prefix_changed(GtkComboBox *widget, gpointer user_data);
void on_radiobutton_toggled(GtkToggleButton *togglebutton,gpointer user_data);
int SearchWidget(GtkWidget *container, char *search_name,GtkWidget **t);


struct gtk_cb_data * AllocateMemoryForGtkCBNode();
struct gtk_cb_data * AppendNode(struct gtk_cb_data **head,char *ref_, char *init_val_,char *value_,char *name_,char *meta_info_);
struct gtk_cb_data * MakeDummy();
void print_user_data(struct gtk_cb_data *head);
struct gtk_cb_data *get_pointer_to_user_data_by_name(const char *_name, struct gtk_cb_data *head);


char * getGtkWidgetValue(char *type, GtkWidget *widget);
char * sGetValueOfTextBox(GtkWidget *widget);
char * sGetValueOfComboBox(GtkWidget *widget);
char * sGetValueOfRadioButton(GtkWidget *widget);
char * sGetValueOfCheckButton(GtkWidget *widget);
