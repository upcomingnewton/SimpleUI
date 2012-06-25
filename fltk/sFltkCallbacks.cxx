#include "sFltk.h"
#include "../simpleUI.h"
#include "../sXforms.h"
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Choice.H>


#ifdef EnableLog
#define WriteLog fprintf
#else
#define WriteLog
#endif

void Select1Handler(Fl_Widget *widget, void *data){
	CallbackData *cb_data = (CallbackData *)data;
//	Fl_Choice  *f = (Fl_Choice *)widget;
	fprintf(stdout,"\n[%s][%d] %s",__func__,__LINE__, cb_data->initial_val);
}
