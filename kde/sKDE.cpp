#include <QtUiTools/QUiLoader>
#include <QtUiTools/QtUiTools>
 #include <QtGui>
#include <string.h>
#include <QString>
#include <QLabel>
 #include "sKDE.h"
 #include "sKdeCallbacks/sKde_Cb.h"
 #include "sKdeRenderers/sKdeRenderer.h"
 #include <QPushButton>
 #include <QTextStream>
 #include <QApplication>
 #include <QAbstractButton>
 #include "../sCallbackData/sCallbackData.h"
  SimpleUiKde::SimpleUiKde(struct sCbData  *temp, QWidget *parent)
     : QWidget(parent)
 {
     QUiLoader loader;
     QFile file("sKde.ui");
     file.open(QFile::ReadOnly);
     QWidget *formWidget = loader.load(&file, this);
     file.close();
     
     cb_data = temp;
     
     //printf("\n cp-1");
     // find widgets here 
     DisableDefaultAndConnectSignals();
     QPushButton *btn = qFindChild<QPushButton *>(this, sKDE_CLOSE_BUTTON);
     btn->setAutoDefault(false);
     connect(btn, SIGNAL(clicked()), this, SLOT(on_DoneButton_click()));
    //printf("\n cp-2");
 }
 
 void SimpleUiKde::on_DoneButton_click()
 {
     QTextStream cout(stdout);
     cout << "QUITING ..." << "\n";
     UpdateModel(cb_data);
    qApp->quit();
 }
 
void SimpleUiKde::DisableDefaultAndConnectSignals()
 {
    struct sCbData  *temp = cb_data;
    //print_user_data(temp);
    while( temp != 0)
    {
      //printf("\n %s",temp->name);
      if( !strcmp(temp->meta_info,"QPushButton"))
      {
          QPushButton *btn = qFindChild<QPushButton *>(this, temp->name);
          if( btn )
          {
              btn->setAutoDefault(false);
              connect(btn, SIGNAL(clicked()), this, SLOT(on_QPushButton_click()));
          }
          
      }
      else if( !strcmp(temp->meta_info,"QComboBox"))
      {
          QComboBox *dd = qFindChild<QComboBox *>(this, temp->name);
          if( dd )
          {
              //dd->setAutoDefault(false);
              connect(dd, SIGNAL(currentIndexChanged (int)), this, SLOT(on_QComboBox_current_index_change(int)));
              connect(dd, SIGNAL(currentIndexChanged (QString)), this, SLOT(on_QComboBox_current_index_change( const QString &  )));
          }
      }
      else if( !strcmp(temp->meta_info,"QRadioButton"))
      {
          QRadioButton *btn = qFindChild<QRadioButton *>(this, temp->name);
          if( btn )
          {
              //btn->setAutoDefault(false);
              connect(btn, SIGNAL(toggled(bool)), this, SLOT(on_QRadioButton_toggled(bool)));
          }
      }
      else if( !strcmp(temp->meta_info,"QCheckBox"))
      {
          QCheckBox *btn = qFindChild<QCheckBox *>(this, temp->name);
          if( btn )
          {
              //btn->setAutoDefault(false);
              connect(btn, SIGNAL(toggled(bool)), this, SLOT(on_QCheckBox_toggled(bool)));
          }
      }
      else if( !strcmp(temp->meta_info,"QSlider"))
      {
          QSlider *slider = qFindChild<QSlider *>(this, temp->name);
          if( slider )
          {
              //slider->setAutoDefault(false);
              connect(slider, SIGNAL(valueChanged(int)), this, SLOT(on_QSlider_valueChanged(int)));
          }
      }
      temp = temp->next;
    }
 }

 
 void SimpleUiKde::on_QPushButton_click()
 {
    QPushButton *btn = qobject_cast<QPushButton *>(QObject::sender());
    if( btn != NULL)
    {
        QTextStream cout(stdout);
        cout << btn->objectName() << "\n";
        // find this object name in the cb_data and then get it's next ref
        struct sCbData *temp = cb_data;
        while( temp )
        {
          if( !strcmp(temp->name,btn->objectName().toStdString().c_str()))
          {
//            if( strcmp(temp->ref,"0")  && strcmp(temp->init_val,"READONLY")){ 
//              UpdateModelandCallUserFunction(temp->ref,value,cb_data);
//            }
            FindReferencesAndUpdateData(temp->name);
            break;
          }
          temp = temp->next;
        }
    //UPDATE UI here
    //QApplication::quit();
   }
   UpdateUI();
 }
 
 void SimpleUiKde::on_QComboBox_current_index_change(int index)
 {
    printf("\n == %d == \n",index);
    UpdateUI();
 }
 
void SimpleUiKde::on_QComboBox_current_index_change(const QString & text)
 {
  QComboBox *combobox = qobject_cast<QComboBox *>(QObject::sender());
    QTextStream cout(stdout);
    cout << text << "\n";
    char *value = s_dupstr((char *)text.toStdString().c_str());
    struct sCbData *temp = cb_data;
    while( temp )
    {
      if( !strcmp(temp->name,combobox->objectName().toStdString().c_str()))
      {
        if( strcmp(temp->ref,"0")  && strcmp(temp->init_val,"READONLY")){ 
          UpdateModelandCallUserFunction(temp->ref,value,cb_data);
        }
        FindReferencesAndUpdateData(temp->name);
        break;
      }
      temp = temp->next;
    }
    //UPDATE UI here
    UpdateUI();
 }
 
 void SimpleUiKde::on_QRadioButton_toggled(bool value)
 {
    QRadioButton *btn = qobject_cast<QRadioButton *>(QObject::sender());
    char *val;
    if( btn != NULL)
    {
        QTextStream cout(stdout);
        cout << btn->objectName() << " == ";
        if( value)
        {
           cout << " checked \n";
        }
        else
        {
           cout << " un-checked \n";
        }
    }
    val = s_dupstr((char *)btn->objectName().toStdString().c_str());
    struct sCbData *temp = cb_data;
    while( temp )
    {
      if( !strcmp(temp->name,val))
      {
        if( strcmp(temp->ref,"0")  && strcmp(temp->init_val,"READONLY")){ 
          UpdateModelandCallUserFunction(temp->ref,val,cb_data);
        }
        FindReferencesAndUpdateData(temp->name);
        break;
      }
      temp = temp->next;
    }
    //UPDATE UI here
    UpdateUI();
 }
 
 void SimpleUiKde::on_QCheckBox_toggled(bool value)
 {
    QCheckBox *btn = qobject_cast<QCheckBox *>(QObject::sender());
    if( btn != NULL)
    {
        QTextStream cout(stdout);
        cout << btn->objectName() << " == ";
        if( value)
        {
           cout << " checked \n";
        }
        else
        {
           cout << " un-checked \n";
        }
    }
    struct sCbData *temp = cb_data;
    while( temp )
    {
      if( !strcmp(temp->name,btn->objectName().toStdString().c_str()))
      {
        if( strcmp(temp->ref,"0")  && strcmp(temp->init_val,"READONLY")){ 
          UpdateModelandCallUserFunction(temp->ref,"1",cb_data);
        }
        FindReferencesAndUpdateData(temp->name);
        break;
      }
      temp = temp->next;
    }
    //UPDATE UI here
    UpdateUI();
 }
 
 void SimpleUiKde::on_QSlider_valueChanged(int newval)
 {
    QSlider *slider = qobject_cast<QSlider *>(QObject::sender());
    char buf[5];
    if( slider != NULL)
    {
        sprintf(buf,"%d",newval);
    }
    struct sCbData *temp = cb_data;
    while( temp )
    {
      if( !strcmp(temp->name,slider->objectName().toStdString().c_str()))
      {
        if( strcmp(temp->ref,"0")  && strcmp(temp->init_val,"READONLY")){ 
          UpdateModelandCallUserFunction(temp->ref,s_dupstr(buf),cb_data);
        }
        FindReferencesAndUpdateData(temp->name);
        break;
      }
      temp = temp->next;
    }
    //UPDATE UI here
    UpdateUI();
 }
 
 void SimpleUiKde::FindReferencesAndUpdateData(char *name)
 {
        struct sCbData  *temp = cb_data;
        while( temp )
        {
          if( !strcmp(temp->name,name))//btn->objectName().toStdString().c_str())
          {
            struct sCbData  *temp2 = temp->nextref;
             while(temp2 != 0)
	          {

//1. GET THE TYPE OF WIDGET 
//2. USE AN IF - CASE 
//3. GET WIDGET'S VALUE
//4. UPDATE CB_DATA
//5. CALL UPDATEDATA
                  char *value;
                  if(!strcmp("QLineEdit",temp2->meta_info))
                  {
                    QLineEdit *input = qFindChild<QLineEdit *>(this, temp2->name);
                    
                    value = s_dupstr((char *)input->text().toStdString().c_str());//TODO find a convenient way of getting this value
                    printf("\n ==== %s, %s",temp2->name,value);
                  }
                  else if(!strcmp("QSlider",temp2->meta_info))
                  {
                    QSlider *slider = qFindChild<QSlider *>(this, temp2->name);
                    int val = slider->value();
                    char buf[5];
                    sprintf(buf,"%d",val);
                    value = s_dupstr(buf);
                  }
                  else if(!strcmp("QCheckBox",temp2->meta_info))
                  {
                    QCheckBox *checkbox = qFindChild<QCheckBox *>(this, temp2->name);
                    if(checkbox->isChecked())
                    {
                      value = "1";
                    }
                    else
                    {
                      value = "0";
                    }
                  }
                  else if(!strcmp("QRadioButton",temp2->meta_info))
                  {
                    QRadioButton *radiobtn = qFindChild<QRadioButton *>(this, temp2->name);
                    if(radiobtn->isChecked())
                    {
                      value = s_dupstr(temp2->name);
                    }
                  }
                  else if(!strcmp("QComboBox",temp2->meta_info))
                  {
                    QComboBox *combobox = qFindChild<QComboBox *>(this, temp2->name);
                    value = s_dupstr((char *)combobox->currentText().toStdString().c_str());
                  }
                  if( strcmp(temp2->ref,"0")  && strcmp(temp2->init_val,"READONLY")){ 
                    UpdateModelandCallUserFunction(temp2->ref,value,cb_data);
                  }
		              temp2 = temp2->next;
	            }
              break;
          }
          temp = temp->next;
        }
 }
 
 
 void SimpleUiKde::UpdateUI()
{
    struct sCbData *temp, *temp2;
    for( temp = cb_data ; temp ; temp =temp->next )
    {
      if( strcmp(temp->ref,"0"))
      {
        UpdateWidgetValue(temp->meta_info,temp->value,temp->name);
      }
      if( temp->nextref )
      {
          for( temp2 = temp->nextref ; temp2 ; temp2 =temp2->next )
          {
            if( strcmp(temp2->ref,"0"))
            {
              UpdateWidgetValue(temp2->meta_info,temp2->value,temp2->name);
            }
          }
      }
    }
}

void SimpleUiKde::UpdateWidgetValue(char *type,char*value,char *name)
{
  //QString val = new QString(value);
  QTextStream cout(stdout);
  //cout << val << "\n";
  if( !strcmp(type,"QLabel"))
  {
    QLabel *label = qFindChild<QLabel *>(this, name);
    //label->setText(&val);
    label->setText(value);
  }
  else  if( !strcmp(type,"QLineEdit"))
  {
    QLineEdit *input = qFindChild<QLineEdit *>(this, name);
    input->setText(value);
    //input->setText(val);
  }
}
