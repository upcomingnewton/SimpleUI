#include <QApplication>
#include "sKDE.h"
#include "sKdeCallbacks/sKde_Cb.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    SimpleUiKde w;
    w.show();
    
    return a.exec();
}

