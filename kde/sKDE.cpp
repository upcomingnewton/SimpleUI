#include <QtUiTools/QUiLoader>
#include <QtUiTools/QtUiTools>
 #include <QtGui>

 #include "sKDE.h"
 #include "sKdeCallbacks/sKde_Cb.h"
 #include <QPushButton>
 #include <QTextStream>
 #include <QApplication>
  SimpleUiKde::SimpleUiKde(QWidget *parent)
     : QWidget(parent)
 {
     QUiLoader loader;
     QFile file(":/forms/sKde.ui");
     file.open(QFile::ReadOnly);
     QWidget *formWidget = loader.load(&file, this);
     file.close();
     
     cb_data = MakeDummy();
     
     
     // find widgets here 
     DisableDefaultAndConnectSignals();

 }
 
void SimpleUiKde::DisableDefaultAndConnectSignals()
 {
    struct qt_cb_data *temp = cb_data;
    print_user_data(temp);
    while( temp != 0)
    {
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
              //dd->setAutoDefault(false);
              connect(btn, SIGNAL(toggled(bool)), this, SLOT(on_QRadioButton_toggled(bool)));
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
    }
    //QApplication::quit();
 }
 
 void SimpleUiKde::on_QComboBox_current_index_change(int index)
 {
    printf("\n == %d == \n",index);
 }
 
void SimpleUiKde::on_QComboBox_current_index_change(const QString & text)
 {
    QTextStream cout(stdout);
    cout << text << "\n";
 }
 
 void SimpleUiKde::on_QRadioButton_toggled(bool value)
 {
    QRadioButton *btn = qobject_cast<QRadioButton *>(QObject::sender());
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
 }
