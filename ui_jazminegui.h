/********************************************************************************
** Form generated from reading UI file 'jazminegui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JAZMINEGUI_H
#define UI_JAZMINEGUI_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JazmineGui
{
public:
    QAction *actionBackup;
    QAction *actionCold_Wallet;
    QAction *actionExit;
    QAction *actionDocumentation;
    QAction *actionSupport;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *accountsTab;
    QHBoxLayout *horizontalLayout_2;
    QWebView *webView;
    QWidget *jazminedLogTab;
    QHBoxLayout *horizontalLayout_3;
    QPlainTextEdit *plainTextEdit;
    QWidget *jazmineWalletdLog;
    QHBoxLayout *horizontalLayout_4;
    QPlainTextEdit *plainTextEdit_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *JazmineGui)
    {
        if (JazmineGui->objectName().isEmpty())
            JazmineGui->setObjectName(QStringLiteral("JazmineGui"));
        JazmineGui->resize(938, 504);
        actionBackup = new QAction(JazmineGui);
        actionBackup->setObjectName(QStringLiteral("actionBackup"));
        actionCold_Wallet = new QAction(JazmineGui);
        actionCold_Wallet->setObjectName(QStringLiteral("actionCold_Wallet"));
        actionExit = new QAction(JazmineGui);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionDocumentation = new QAction(JazmineGui);
        actionDocumentation->setObjectName(QStringLiteral("actionDocumentation"));
        actionSupport = new QAction(JazmineGui);
        actionSupport->setObjectName(QStringLiteral("actionSupport"));
        centralWidget = new QWidget(JazmineGui);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        accountsTab = new QWidget();
        accountsTab->setObjectName(QStringLiteral("accountsTab"));
        horizontalLayout_2 = new QHBoxLayout(accountsTab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        webView = new QWebView(accountsTab);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));

        horizontalLayout_2->addWidget(webView);

        tabWidget->addTab(accountsTab, QString());
        jazminedLogTab = new QWidget();
        jazminedLogTab->setObjectName(QStringLiteral("jazminedLogTab"));
        horizontalLayout_3 = new QHBoxLayout(jazminedLogTab);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        plainTextEdit = new QPlainTextEdit(jazminedLogTab);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        horizontalLayout_3->addWidget(plainTextEdit);

        tabWidget->addTab(jazminedLogTab, QString());
        jazmineWalletdLog = new QWidget();
        jazmineWalletdLog->setObjectName(QStringLiteral("jazmineWalletdLog"));
        horizontalLayout_4 = new QHBoxLayout(jazmineWalletdLog);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        plainTextEdit_2 = new QPlainTextEdit(jazmineWalletdLog);
        plainTextEdit_2->setObjectName(QStringLiteral("plainTextEdit_2"));

        horizontalLayout_4->addWidget(plainTextEdit_2);

        tabWidget->addTab(jazmineWalletdLog, QString());

        horizontalLayout->addWidget(tabWidget);

        JazmineGui->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(JazmineGui);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 938, 20));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        JazmineGui->setMenuBar(menuBar);
        mainToolBar = new QToolBar(JazmineGui);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        JazmineGui->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(JazmineGui);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        JazmineGui->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionBackup);
        menuFile->addAction(actionCold_Wallet);
        menuFile->addAction(actionExit);
        menuAbout->addAction(actionDocumentation);
        menuAbout->addAction(actionSupport);

        retranslateUi(JazmineGui);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(JazmineGui);
    } // setupUi

    void retranslateUi(QMainWindow *JazmineGui)
    {
        JazmineGui->setWindowTitle(QApplication::translate("JazmineGui", "JazmineGui", Q_NULLPTR));
        actionBackup->setText(QApplication::translate("JazmineGui", "Backup", Q_NULLPTR));
        actionCold_Wallet->setText(QApplication::translate("JazmineGui", "Cold Wallet", Q_NULLPTR));
        actionExit->setText(QApplication::translate("JazmineGui", "Exit", Q_NULLPTR));
        actionDocumentation->setText(QApplication::translate("JazmineGui", "Documentation", Q_NULLPTR));
        actionSupport->setText(QApplication::translate("JazmineGui", "Support", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(accountsTab), QApplication::translate("JazmineGui", "Accounts", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(jazminedLogTab), QApplication::translate("JazmineGui", "Jazmined Log", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(jazmineWalletdLog), QApplication::translate("JazmineGui", "JazmineWalletd Log", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("JazmineGui", "File", Q_NULLPTR));
        menuAbout->setTitle(QApplication::translate("JazmineGui", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class JazmineGui: public Ui_JazmineGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JAZMINEGUI_H
