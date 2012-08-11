/********************************************************************************
** Form generated from reading UI file 'sKde.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKDE_H
#define UI_SKDE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sample1
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *TabWidget;
    QWidget *TabWelcome;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_6;
    QLabel *label;
    QWidget *TabPersonalInformation;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_2;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *lineEdit_4;
    QLabel *label_5;
    QComboBox *PersonalInfo_NamePrefix;
    QLabel *label_6;
    QPushButton *BtnPersonalInfoDone;
    QGroupBox *GroupBoxRadioButtons;
    QRadioButton *radioButton_male;
    QRadioButton *radioButton_female;
    QRadioButton *radioButton_none;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_2;
    QLabel *label_8;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_6;
    QLabel *label_9;
    QLineEdit *lineEdit_5;
    QLabel *label_10;
    QPushButton *BtnLoginInfoDone;
    QWidget *TabProjectInfo;
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_9;
    QGridLayout *gridLayout_3;
    QLabel *label_13;
    QLineEdit *lineEdit_8;
    QLabel *label_14;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_9;
    QLabel *label_11;
    QLabel *label_12;
    QPushButton *BtnProjectInsertDone;
    QTextEdit *textEdit;
    QSpacerItem *verticalSpacer_2;
    QWidget *TabPreferences;
    QVBoxLayout *verticalLayout_5;
    QScrollArea *scrollArea_4;
    QWidget *scrollAreaWidgetContents_4;
    QVBoxLayout *verticalLayout_10;
    QGridLayout *gridLayout_4;
    QCheckBox *checkBox_newspaper1;
    QCheckBox *checkBox_newspaper4;
    QLabel *label_15;
    QCheckBox *checkBox_newspaper3;
    QCheckBox *checkBox_newspaper2;
    QCheckBox *checkBox_newspaper5;
    QGridLayout *gridLayout_5;
    QSlider *SliderDemo;
    QLabel *label_20;
    QLabel *label_16;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *BtnSliderValueDone;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *BtnDone_Main;

    void setupUi(QWidget *sample1)
    {
        if (sample1->objectName().isEmpty())
            sample1->setObjectName(QString::fromUtf8("sample1"));
        sample1->resize(681, 458);
        verticalLayout_2 = new QVBoxLayout(sample1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        TabWidget = new QTabWidget(sample1);
        TabWidget->setObjectName(QString::fromUtf8("TabWidget"));
        TabWelcome = new QWidget();
        TabWelcome->setObjectName(QString::fromUtf8("TabWelcome"));
        verticalLayout_3 = new QVBoxLayout(TabWelcome);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        scrollArea_2 = new QScrollArea(TabWelcome);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 639, 342));
        verticalLayout_6 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label = new QLabel(scrollAreaWidgetContents_2);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_6->addWidget(label);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_3->addWidget(scrollArea_2);

        TabWidget->addTab(TabWelcome, QString());
        TabPersonalInformation = new QWidget();
        TabPersonalInformation->setObjectName(QString::fromUtf8("TabPersonalInformation"));
        verticalLayout = new QVBoxLayout(TabPersonalInformation);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(TabPersonalInformation);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 621, 432));
        verticalLayout_8 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEdit = new QLineEdit(scrollAreaWidgetContents);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 2, 1, 1);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_3 = new QLineEdit(scrollAreaWidgetContents);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 3, 2, 1, 1);

        lineEdit_2 = new QLineEdit(scrollAreaWidgetContents);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 2, 2, 1, 1);

        label_7 = new QLabel(scrollAreaWidgetContents);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 5, 0, 1, 1);

        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        lineEdit_4 = new QLineEdit(scrollAreaWidgetContents);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 4, 2, 1, 1);

        label_5 = new QLabel(scrollAreaWidgetContents);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        PersonalInfo_NamePrefix = new QComboBox(scrollAreaWidgetContents);
        PersonalInfo_NamePrefix->setObjectName(QString::fromUtf8("PersonalInfo_NamePrefix"));

        gridLayout->addWidget(PersonalInfo_NamePrefix, 0, 2, 1, 1);

        label_6 = new QLabel(scrollAreaWidgetContents);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        BtnPersonalInfoDone = new QPushButton(scrollAreaWidgetContents);
        BtnPersonalInfoDone->setObjectName(QString::fromUtf8("BtnPersonalInfoDone"));

        gridLayout->addWidget(BtnPersonalInfoDone, 6, 0, 1, 1);

        GroupBoxRadioButtons = new QGroupBox(scrollAreaWidgetContents);
        GroupBoxRadioButtons->setObjectName(QString::fromUtf8("GroupBoxRadioButtons"));
        GroupBoxRadioButtons->setCheckable(false);
        GroupBoxRadioButtons->setChecked(false);
        radioButton_male = new QRadioButton(GroupBoxRadioButtons);
        radioButton_male->setObjectName(QString::fromUtf8("radioButton_male"));
        radioButton_male->setGeometry(QRect(30, 0, 108, 26));
        radioButton_female = new QRadioButton(GroupBoxRadioButtons);
        radioButton_female->setObjectName(QString::fromUtf8("radioButton_female"));
        radioButton_female->setGeometry(QRect(160, 0, 108, 26));
        radioButton_none = new QRadioButton(GroupBoxRadioButtons);
        radioButton_none->setObjectName(QString::fromUtf8("radioButton_none"));
        radioButton_none->setGeometry(QRect(310, 0, 108, 26));

        gridLayout->addWidget(GroupBoxRadioButtons, 5, 2, 1, 1);


        verticalLayout_7->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_8 = new QLabel(scrollAreaWidgetContents);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 0, 1, 1, 1);

        lineEdit_7 = new QLineEdit(scrollAreaWidgetContents);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        gridLayout_2->addWidget(lineEdit_7, 2, 2, 1, 1);

        lineEdit_6 = new QLineEdit(scrollAreaWidgetContents);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        gridLayout_2->addWidget(lineEdit_6, 0, 2, 1, 1);

        label_9 = new QLabel(scrollAreaWidgetContents);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 1, 1, 1, 1);

        lineEdit_5 = new QLineEdit(scrollAreaWidgetContents);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        gridLayout_2->addWidget(lineEdit_5, 1, 2, 1, 1);

        label_10 = new QLabel(scrollAreaWidgetContents);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 2, 1, 1, 1);

        BtnLoginInfoDone = new QPushButton(scrollAreaWidgetContents);
        BtnLoginInfoDone->setObjectName(QString::fromUtf8("BtnLoginInfoDone"));

        gridLayout_2->addWidget(BtnLoginInfoDone, 3, 1, 1, 1);


        verticalLayout_7->addLayout(gridLayout_2);


        verticalLayout_8->addLayout(verticalLayout_7);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        TabWidget->addTab(TabPersonalInformation, QString());
        TabProjectInfo = new QWidget();
        TabProjectInfo->setObjectName(QString::fromUtf8("TabProjectInfo"));
        verticalLayout_4 = new QVBoxLayout(TabProjectInfo);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        scrollArea_3 = new QScrollArea(TabProjectInfo);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 639, 342));
        verticalLayout_9 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_13 = new QLabel(scrollAreaWidgetContents_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_3->addWidget(label_13, 2, 0, 1, 1);

        lineEdit_8 = new QLineEdit(scrollAreaWidgetContents_3);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));

        gridLayout_3->addWidget(lineEdit_8, 2, 1, 1, 1);

        label_14 = new QLabel(scrollAreaWidgetContents_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_3->addWidget(label_14, 3, 0, 1, 1);

        lineEdit_10 = new QLineEdit(scrollAreaWidgetContents_3);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));

        gridLayout_3->addWidget(lineEdit_10, 0, 1, 1, 1);

        lineEdit_9 = new QLineEdit(scrollAreaWidgetContents_3);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));

        gridLayout_3->addWidget(lineEdit_9, 1, 1, 1, 1);

        label_11 = new QLabel(scrollAreaWidgetContents_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_3->addWidget(label_11, 0, 0, 1, 1);

        label_12 = new QLabel(scrollAreaWidgetContents_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_3->addWidget(label_12, 1, 0, 1, 1);

        BtnProjectInsertDone = new QPushButton(scrollAreaWidgetContents_3);
        BtnProjectInsertDone->setObjectName(QString::fromUtf8("BtnProjectInsertDone"));

        gridLayout_3->addWidget(BtnProjectInsertDone, 4, 0, 1, 1);

        textEdit = new QTextEdit(scrollAreaWidgetContents_3);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout_3->addWidget(textEdit, 3, 1, 1, 1);


        verticalLayout_9->addLayout(gridLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_2);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_4->addWidget(scrollArea_3);

        TabWidget->addTab(TabProjectInfo, QString());
        TabPreferences = new QWidget();
        TabPreferences->setObjectName(QString::fromUtf8("TabPreferences"));
        verticalLayout_5 = new QVBoxLayout(TabPreferences);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        scrollArea_4 = new QScrollArea(TabPreferences);
        scrollArea_4->setObjectName(QString::fromUtf8("scrollArea_4"));
        scrollArea_4->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 639, 342));
        verticalLayout_10 = new QVBoxLayout(scrollAreaWidgetContents_4);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        checkBox_newspaper1 = new QCheckBox(scrollAreaWidgetContents_4);
        checkBox_newspaper1->setObjectName(QString::fromUtf8("checkBox_newspaper1"));

        gridLayout_4->addWidget(checkBox_newspaper1, 1, 0, 1, 1);

        checkBox_newspaper4 = new QCheckBox(scrollAreaWidgetContents_4);
        checkBox_newspaper4->setObjectName(QString::fromUtf8("checkBox_newspaper4"));

        gridLayout_4->addWidget(checkBox_newspaper4, 4, 0, 1, 1);

        label_15 = new QLabel(scrollAreaWidgetContents_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_4->addWidget(label_15, 0, 0, 1, 1);

        checkBox_newspaper3 = new QCheckBox(scrollAreaWidgetContents_4);
        checkBox_newspaper3->setObjectName(QString::fromUtf8("checkBox_newspaper3"));

        gridLayout_4->addWidget(checkBox_newspaper3, 3, 0, 1, 1);

        checkBox_newspaper2 = new QCheckBox(scrollAreaWidgetContents_4);
        checkBox_newspaper2->setObjectName(QString::fromUtf8("checkBox_newspaper2"));

        gridLayout_4->addWidget(checkBox_newspaper2, 2, 0, 1, 1);

        checkBox_newspaper5 = new QCheckBox(scrollAreaWidgetContents_4);
        checkBox_newspaper5->setObjectName(QString::fromUtf8("checkBox_newspaper5"));

        gridLayout_4->addWidget(checkBox_newspaper5, 5, 0, 1, 1);


        verticalLayout_10->addLayout(gridLayout_4);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        SliderDemo = new QSlider(scrollAreaWidgetContents_4);
        SliderDemo->setObjectName(QString::fromUtf8("SliderDemo"));
        SliderDemo->setMaximum(100);
        SliderDemo->setValue(50);
        SliderDemo->setOrientation(Qt::Horizontal);
        SliderDemo->setTickPosition(QSlider::TicksBothSides);
        SliderDemo->setTickInterval(5);

        gridLayout_5->addWidget(SliderDemo, 1, 0, 1, 1);

        label_20 = new QLabel(scrollAreaWidgetContents_4);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_5->addWidget(label_20, 0, 0, 1, 1);

        label_16 = new QLabel(scrollAreaWidgetContents_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_5->addWidget(label_16, 4, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        BtnSliderValueDone = new QPushButton(scrollAreaWidgetContents_4);
        BtnSliderValueDone->setObjectName(QString::fromUtf8("BtnSliderValueDone"));

        horizontalLayout_3->addWidget(BtnSliderValueDone);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        gridLayout_5->addLayout(horizontalLayout_3, 5, 0, 1, 1);


        verticalLayout_10->addLayout(gridLayout_5);

        scrollArea_4->setWidget(scrollAreaWidgetContents_4);

        verticalLayout_5->addWidget(scrollArea_4);

        TabWidget->addTab(TabPreferences, QString());

        verticalLayout_2->addWidget(TabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        BtnDone_Main = new QPushButton(sample1);
        BtnDone_Main->setObjectName(QString::fromUtf8("BtnDone_Main"));

        horizontalLayout->addWidget(BtnDone_Main);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(sample1);

        TabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(sample1);
    } // setupUi

    void retranslateUi(QWidget *sample1)
    {
        sample1->setWindowTitle(QApplication::translate("sample1", "sample1", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("sample1", "THIS IS WELCOME TAB", 0, QApplication::UnicodeUTF8));
        TabWidget->setTabText(TabWidget->indexOf(TabWelcome), QApplication::translate("sample1", "Welcome", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("sample1", "Enter your first name", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("sample1", "Select your gender", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("sample1", "Enter your middle name", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("sample1", "Name Prefix", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("sample1", "Enter your last name", 0, QApplication::UnicodeUTF8));
        PersonalInfo_NamePrefix->clear();
        PersonalInfo_NamePrefix->insertItems(0, QStringList()
         << QApplication::translate("sample1", "Mr.", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sample1", "Mrs.", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sample1", "Dr.", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("sample1", "Enter your date of birth", 0, QApplication::UnicodeUTF8));
        BtnPersonalInfoDone->setText(QApplication::translate("sample1", "Done", 0, QApplication::UnicodeUTF8));
        GroupBoxRadioButtons->setTitle(QString());
        radioButton_male->setText(QApplication::translate("sample1", "Male", 0, QApplication::UnicodeUTF8));
        radioButton_female->setText(QApplication::translate("sample1", "female", 0, QApplication::UnicodeUTF8));
        radioButton_none->setText(QApplication::translate("sample1", "not disclose", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("sample1", "User Name", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("sample1", "Password", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("sample1", "Confirm Password", 0, QApplication::UnicodeUTF8));
        BtnLoginInfoDone->setText(QApplication::translate("sample1", "Done", 0, QApplication::UnicodeUTF8));
        TabWidget->setTabText(TabWidget->indexOf(TabPersonalInformation), QApplication::translate("sample1", "Personal Information", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("sample1", "Enter Key skills", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("sample1", "Enter Description", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("sample1", "Enter Start Date", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("sample1", "Enter End Date", 0, QApplication::UnicodeUTF8));
        BtnProjectInsertDone->setText(QApplication::translate("sample1", "Insert Project", 0, QApplication::UnicodeUTF8));
        TabWidget->setTabText(TabWidget->indexOf(TabProjectInfo), QApplication::translate("sample1", "Project Information", 0, QApplication::UnicodeUTF8));
        checkBox_newspaper1->setText(QApplication::translate("sample1", "newspaper1", 0, QApplication::UnicodeUTF8));
        checkBox_newspaper4->setText(QApplication::translate("sample1", "newspaper4", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("sample1", "Select the newspaper you like", 0, QApplication::UnicodeUTF8));
        checkBox_newspaper3->setText(QApplication::translate("sample1", "newspaper3", 0, QApplication::UnicodeUTF8));
        checkBox_newspaper2->setText(QApplication::translate("sample1", "newspaper2", 0, QApplication::UnicodeUTF8));
        checkBox_newspaper5->setText(QApplication::translate("sample1", "newspaper5", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("sample1", "Select some value", 0, QApplication::UnicodeUTF8));
        label_16->setText(QString());
        BtnSliderValueDone->setText(QApplication::translate("sample1", "get Value", 0, QApplication::UnicodeUTF8));
        TabWidget->setTabText(TabWidget->indexOf(TabPreferences), QApplication::translate("sample1", "Preferences", 0, QApplication::UnicodeUTF8));
        BtnDone_Main->setText(QApplication::translate("sample1", "Done", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class sample1: public Ui_sample1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKDE_H
