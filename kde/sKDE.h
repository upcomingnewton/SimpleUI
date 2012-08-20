#ifndef SIMPLE_UI_KDE_H
#define SIMPLE_UI_KDE_H
#include "sKdeCallbacks/sKde_Cb.h"
#include <QWidget>
#include <QPushButton>
#include "../sCallbackData/sCallbackData.h"

class SimpleUiKde : public QWidget
{
    Q_OBJECT
    
public:
    SimpleUiKde(struct sCbData *temp,QWidget *parent = 0);
    
private slots:
    void on_DoneButton_click();
    void on_QPushButton_click();
    void on_QComboBox_current_index_change(int index);
    void on_QComboBox_current_index_change( const QString & text );
    void on_QRadioButton_toggled(bool);
    void on_QCheckBox_toggled(bool);
    void on_QSlider_valueChanged(int);
private:
    struct sCbData *cb_data;
    QPushButton *ui_push_button;
    void FindReferencesAndUpdateData(char *name);
    void UpdateUI();
    void UpdateWidgetValue(char *type,char*value,char *name);
    void DisableDefaultAndConnectSignals();
};

#endif // SAMPLE1_H
