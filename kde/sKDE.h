#ifndef SIMPLE_UI_KDE_H
#define SIMPLE_UI_KDE_H
#include "sKdeCallbacks/sKde_Cb.h"
#include <QWidget>
 #include <QPushButton>

class SimpleUiKde : public QWidget
{
    Q_OBJECT
    
public:
    SimpleUiKde(QWidget *parent = 0);
    
private slots:
    void on_QPushButton_click();
private:
    struct qt_cb_data *cb_data;
    QPushButton *ui_push_button;
    void DisableDefaultAndConnectSignals();
};

#endif // SAMPLE1_H
