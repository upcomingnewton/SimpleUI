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
