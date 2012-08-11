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
    void on_QComboBox_current_index_change(int index);
    void on_QComboBox_current_index_change( const QString & text );
    void on_QRadioButton_toggled(bool);
    void on_QCheckBox_toggled(bool);
    void on_QSlider_valueChanged(int);
private:
    struct qt_cb_data *cb_data;
    QPushButton *ui_push_button;
    void DisableDefaultAndConnectSignals();
};

#endif // SAMPLE1_H
