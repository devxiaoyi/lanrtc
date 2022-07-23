/********************************************************************************
** Form generated from reading UI file 'recordmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDMAINWINDOW_H
#define UI_RECORDMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecordMainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *m_b_pushplay;
    QFrame *vdMain;
    QLabel *m_l_url;
    QLineEdit *m_url;
    QLineEdit *m_t_data;
    QLabel *m_l_url_2;
    QLineEdit *m_t_recv;
    QPushButton *m_b_senddata;
    QMenuBar *menubar;

    void setupUi(QMainWindow *RecordMainWindow)
    {
        if (RecordMainWindow->objectName().isEmpty())
            RecordMainWindow->setObjectName(QString::fromUtf8("RecordMainWindow"));
        RecordMainWindow->resize(1007, 823);
        RecordMainWindow->setStyleSheet(QString::fromUtf8("QWidget, QLabel{\n"
"                        color:white;\n"
"                        border: 1px solid white;\n"
"                        padding:0;\n"
"                        border-radius:5px;\n"
"							background-color:rgb(20,50,70);\n"
"                      /**  background-color:rgba(250,170,0,150);**/\n"
"  }\n"
"\n"
"/*TabWidget*/\n"
"QTabWidget{\n"
"/*\347\273\231tabwidget\350\256\276\347\275\256etAttribute(Qt::WA_StyledBackground)*/\n"
"border: 1px solid white;\n"
"background-color:rgb(20,50,70);\n"
"}\n"
"QTabWidget::tab-bar{\n"
"alignment:left;\n"
"left:1px;\n"
"}\n"
"QTabWidget::pane { \n"
"/*background-color:rgb(20,50,70);*/\n"
"border:1px solid white;\n"
"} \n"
"QTabBar{\n"
"/*\345\217\252\346\234\211\346\234\211\346\214\211\351\222\256\347\232\204\345\234\260\346\226\271\346\211\215\346\230\257tabbar\357\274\214\347\251\272\347\231\275\345\244\204\346\230\257tabwidget\347\232\204*/\n"
"background-color:white;\n"
"}\n"
"QTabBar::tab{/*\351\241\265\347\255\276*/\n"
"min-height:28px;\n"
"padding"
                        ":0 10px;\n"
"border:0;\n"
"margin:1px 1px 0 0;\n"
"background-color:rgb(20,50,70);\n"
"}\n"
"QTabBar::tab:first{\n"
"margin-left:1px;\n"
"}\n"
"QTabBar::tab:hover{\n"
"color:cyan;\n"
"}\n"
"QTabBar::tab:selected{\n"
"background-color: rgb(20, 100, 150);\n"
"}\n"
"QTabBar::tab:selected:hover{\n"
"}\n"
"\n"
"QTabBar::tear{\n"
"}\n"
"QTabBar::scroller{\n"
"}\n"
"QMenu {\n"
"     background-color: rgb(20,50,70); /* sets background of the menu \350\256\276\347\275\256\346\225\264\344\270\252\350\217\234\345\215\225\345\214\272\345\237\237\347\232\204\350\203\214\346\231\257\350\211\262\357\274\214\346\210\221\347\224\250\347\232\204\346\230\257\347\231\275\350\211\262\357\274\232white*/\n"
"     border: 1px solid white;/*\346\225\264\344\270\252\350\217\234\345\215\225\345\214\272\345\237\237\347\232\204\350\276\271\346\241\206\347\262\227\347\273\206\343\200\201\346\240\267\345\274\217\343\200\201\351\242\234\350\211\262*/\n"
" }\n"
"  \n"
" QMenu::item {\n"
"     /* sets background of menu item. set this to somet"
                        "hing non-transparent\n"
"         if you want menu color and menu item color to be different */\n"
"     background-color: transparent;\n"
"     padding:8px 32px;/*\350\256\276\347\275\256\350\217\234\345\215\225\351\241\271\346\226\207\345\255\227\344\270\212\344\270\213\345\222\214\345\267\246\345\217\263\347\232\204\345\206\205\350\276\271\350\267\235\357\274\214\346\225\210\346\236\234\345\260\261\346\230\257\350\217\234\345\215\225\344\270\255\347\232\204\346\235\241\347\233\256\345\267\246\345\217\263\344\270\212\344\270\213\346\234\211\344\272\206\351\227\264\351\232\224*/\n"
"     margin:0px 8px;/*\350\256\276\347\275\256\350\217\234\345\215\225\351\241\271\347\232\204\345\244\226\350\276\271\350\267\235*/\n"
"     border-bottom:1px solid #DBDBDB;/*\344\270\272\350\217\234\345\215\225\351\241\271\344\271\213\351\227\264\346\267\273\345\212\240\346\250\252\347\272\277\351\227\264\351\232\224*/\n"
" }\n"
"  \n"
" QMenu::item:selected { /* when user selects item using mouse or keyboard */\n"
"     backgro"
                        "und-color: #2dabf9;/*\350\277\231\344\270\200\345\217\245\346\230\257\350\256\276\347\275\256\350\217\234\345\215\225\351\241\271\351\274\240\346\240\207\347\273\217\350\277\207\351\200\211\344\270\255\347\232\204\346\240\267\345\274\217*/\n"
" }"));
        centralwidget = new QWidget(RecordMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        m_b_pushplay = new QPushButton(centralwidget);
        m_b_pushplay->setObjectName(QString::fromUtf8("m_b_pushplay"));
        m_b_pushplay->setGeometry(QRect(750, 660, 101, 31));
        vdMain = new QFrame(centralwidget);
        vdMain->setObjectName(QString::fromUtf8("vdMain"));
        vdMain->setGeometry(QRect(30, 20, 951, 621));
        vdMain->setFrameShape(QFrame::StyledPanel);
        vdMain->setFrameShadow(QFrame::Raised);
        m_l_url = new QLabel(centralwidget);
        m_l_url->setObjectName(QString::fromUtf8("m_l_url"));
        m_l_url->setGeometry(QRect(100, 660, 80, 31));
        m_url = new QLineEdit(centralwidget);
        m_url->setObjectName(QString::fromUtf8("m_url"));
        m_url->setGeometry(QRect(210, 660, 521, 29));
        m_t_data = new QLineEdit(centralwidget);
        m_t_data->setObjectName(QString::fromUtf8("m_t_data"));
        m_t_data->setGeometry(QRect(462, 710, 261, 42));
        m_l_url_2 = new QLabel(centralwidget);
        m_l_url_2->setObjectName(QString::fromUtf8("m_l_url_2"));
        m_l_url_2->setGeometry(QRect(89, 720, 91, 31));
        m_t_recv = new QLineEdit(centralwidget);
        m_t_recv->setObjectName(QString::fromUtf8("m_t_recv"));
        m_t_recv->setGeometry(QRect(210, 710, 231, 42));
        m_b_senddata = new QPushButton(centralwidget);
        m_b_senddata->setObjectName(QString::fromUtf8("m_b_senddata"));
        m_b_senddata->setGeometry(QRect(750, 710, 141, 41));
        RecordMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RecordMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1007, 50));
        RecordMainWindow->setMenuBar(menubar);

        retranslateUi(RecordMainWindow);

        QMetaObject::connectSlotsByName(RecordMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RecordMainWindow)
    {
        RecordMainWindow->setWindowTitle(QCoreApplication::translate("RecordMainWindow", "Webrtc p2p\344\272\222\345\212\250\347\233\264\346\222\255demo", nullptr));
        m_b_pushplay->setText(QCoreApplication::translate("RecordMainWindow", "\346\216\250\346\213\211\346\265\201", nullptr));
        m_l_url->setText(QCoreApplication::translate("RecordMainWindow", "URL:", nullptr));
        m_t_data->setText(QCoreApplication::translate("RecordMainWindow", "hello,metaRTC4.0!", nullptr));
        m_l_url_2->setText(QCoreApplication::translate("RecordMainWindow", "RECV:", nullptr));
        m_b_senddata->setText(QCoreApplication::translate("RecordMainWindow", "SendData", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RecordMainWindow: public Ui_RecordMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDMAINWINDOW_H
