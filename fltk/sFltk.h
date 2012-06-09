#ifndef SIMPLE_UI_FLTK_H
#define SIMPLE_UI_FLTK_H
#include "../sXforms.h"

struct sFltkUIHandlers{
	char *name;
	
};

void sGenerateUIFromTree(sXformsNode * );
void sPrintsXformsNode(sXformsNode * );
void test_widgets();
#endif
