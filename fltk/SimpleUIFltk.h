#ifndef SIMPLE_UI_FLTK_H
	#define SIMPLE_UI_FLTK_H
	#include "../sXforms.h"
	#include<stdio.h>
	#include<string.h>
	
	#include <FL/Fl.H>
	#include <FL/Fl_Button.H>
	#include <FL/Fl_Double_Window.H>
	#include <FL/Fl_Pack.H>
	#include <FL/Fl_Scroll.H>
	#include <FL/Fl_Text_Display.H>
	#include <FL/Fl_Help_View.H>
	
void sGenerateUIFromTree(sXformsNode * );
void sPrintsXformsNode(sXformsNode * );
#endif
