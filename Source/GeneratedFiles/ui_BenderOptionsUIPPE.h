/********************************************************************************
** Form generated from reading UI file 'BenderOptionsUIPPE.ui'
**
** Created: Fri Sep 24 17:50:40 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BENDEROPTIONSUIPPE_H
#define UI_BENDEROPTIONSUIPPE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuOptions
{
public:
    QTabWidget *optionTabs;
    QWidget *silOpsTab;
    QSlider *silOpsThetaNSlider;
    QLabel *silOpsThetaNLabel;
    QLabel *silOpsThetaPLabel;
    QPushButton *silOpsDefaultsButton;
    QDoubleSpinBox *silOpsThetaNSpinBox;
    QDoubleSpinBox *silOpsThetaPSpinBox;
    QSlider *silOpsThetaPSlider;
    QWidget *hndOpsTab;
    QLabel *hndOpsProxLabel;
    QLabel *hndOpsSimLabel;
    QPushButton *hndOpsRedoButton;
    QPushButton *hndOpsDefaultsButton;
    QSlider *hndOpsBalanceSlider;
    QWidget *roiOpsTab;
    QLabel *roiOpsScalerLabel;
    QDoubleSpinBox *roiOpsScalerSpinBox;
    QPushButton *roiOpsRedoButton;
    QPushButton *roiOpsDefaultsButton;
    QSlider *roiOpsScalerSlider;
    QWidget *lseOpsTab;
    QLabel *lseOpsHndLabel;
    QPushButton *lseOpsRedoButton;
    QPushButton *lseOpsDefaultsButton;
    QDoubleSpinBox *lseOpsHandleSpinBox;
    QSlider *lseOpsHandleSlider;

    void setupUi(QWidget *MenuOptions)
    {
        if (MenuOptions->objectName().isEmpty())
            MenuOptions->setObjectName(QString::fromUtf8("MenuOptions"));
        MenuOptions->resize(349, 190);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MenuOptions->sizePolicy().hasHeightForWidth());
        MenuOptions->setSizePolicy(sizePolicy);
        MenuOptions->setMinimumSize(QSize(349, 190));
        MenuOptions->setMaximumSize(QSize(349, 190));
        MenuOptions->setBaseSize(QSize(0, 0));
        optionTabs = new QTabWidget(MenuOptions);
        optionTabs->setObjectName(QString::fromUtf8("optionTabs"));
        optionTabs->setGeometry(QRect(0, 0, 351, 191));
        silOpsTab = new QWidget();
        silOpsTab->setObjectName(QString::fromUtf8("silOpsTab"));
        silOpsThetaNSlider = new QSlider(silOpsTab);
        silOpsThetaNSlider->setObjectName(QString::fromUtf8("silOpsThetaNSlider"));
        silOpsThetaNSlider->setGeometry(QRect(90, 80, 160, 19));
        silOpsThetaNSlider->setMaximum(100);
        silOpsThetaNSlider->setOrientation(Qt::Horizontal);
        silOpsThetaNLabel = new QLabel(silOpsTab);
        silOpsThetaNLabel->setObjectName(QString::fromUtf8("silOpsThetaNLabel"));
        silOpsThetaNLabel->setGeometry(QRect(20, 80, 61, 16));
        silOpsThetaPLabel = new QLabel(silOpsTab);
        silOpsThetaPLabel->setObjectName(QString::fromUtf8("silOpsThetaPLabel"));
        silOpsThetaPLabel->setGeometry(QRect(20, 40, 61, 16));
        silOpsDefaultsButton = new QPushButton(silOpsTab);
        silOpsDefaultsButton->setObjectName(QString::fromUtf8("silOpsDefaultsButton"));
        silOpsDefaultsButton->setGeometry(QRect(260, 130, 75, 23));
        silOpsThetaNSpinBox = new QDoubleSpinBox(silOpsTab);
        silOpsThetaNSpinBox->setObjectName(QString::fromUtf8("silOpsThetaNSpinBox"));
        silOpsThetaNSpinBox->setGeometry(QRect(270, 80, 62, 22));
        silOpsThetaNSpinBox->setDecimals(3);
        silOpsThetaNSpinBox->setMinimum(0.001);
        silOpsThetaNSpinBox->setMaximum(0.05);
        silOpsThetaNSpinBox->setSingleStep(0.001);
        silOpsThetaNSpinBox->setValue(0.02);
        silOpsThetaPSpinBox = new QDoubleSpinBox(silOpsTab);
        silOpsThetaPSpinBox->setObjectName(QString::fromUtf8("silOpsThetaPSpinBox"));
        silOpsThetaPSpinBox->setGeometry(QRect(270, 40, 62, 22));
        silOpsThetaPSpinBox->setDecimals(4);
        silOpsThetaPSpinBox->setMinimum(0.0001);
        silOpsThetaPSpinBox->setMaximum(0.01);
        silOpsThetaPSpinBox->setSingleStep(0.0001);
        silOpsThetaPSpinBox->setValue(0.005);
        silOpsThetaPSlider = new QSlider(silOpsTab);
        silOpsThetaPSlider->setObjectName(QString::fromUtf8("silOpsThetaPSlider"));
        silOpsThetaPSlider->setGeometry(QRect(90, 40, 160, 19));
        silOpsThetaPSlider->setMaximum(100);
        silOpsThetaPSlider->setOrientation(Qt::Horizontal);
        optionTabs->addTab(silOpsTab, QString());
        hndOpsTab = new QWidget();
        hndOpsTab->setObjectName(QString::fromUtf8("hndOpsTab"));
        hndOpsProxLabel = new QLabel(hndOpsTab);
        hndOpsProxLabel->setObjectName(QString::fromUtf8("hndOpsProxLabel"));
        hndOpsProxLabel->setGeometry(QRect(20, 60, 61, 16));
        hndOpsSimLabel = new QLabel(hndOpsTab);
        hndOpsSimLabel->setObjectName(QString::fromUtf8("hndOpsSimLabel"));
        hndOpsSimLabel->setGeometry(QRect(270, 60, 61, 16));
        hndOpsRedoButton = new QPushButton(hndOpsTab);
        hndOpsRedoButton->setObjectName(QString::fromUtf8("hndOpsRedoButton"));
        hndOpsRedoButton->setGeometry(QRect(260, 130, 75, 23));
        hndOpsDefaultsButton = new QPushButton(hndOpsTab);
        hndOpsDefaultsButton->setObjectName(QString::fromUtf8("hndOpsDefaultsButton"));
        hndOpsDefaultsButton->setGeometry(QRect(180, 130, 75, 23));
        hndOpsBalanceSlider = new QSlider(hndOpsTab);
        hndOpsBalanceSlider->setObjectName(QString::fromUtf8("hndOpsBalanceSlider"));
        hndOpsBalanceSlider->setGeometry(QRect(90, 60, 160, 19));
        hndOpsBalanceSlider->setMaximum(100);
        hndOpsBalanceSlider->setOrientation(Qt::Horizontal);
        optionTabs->addTab(hndOpsTab, QString());
        roiOpsTab = new QWidget();
        roiOpsTab->setObjectName(QString::fromUtf8("roiOpsTab"));
        roiOpsScalerLabel = new QLabel(roiOpsTab);
        roiOpsScalerLabel->setObjectName(QString::fromUtf8("roiOpsScalerLabel"));
        roiOpsScalerLabel->setGeometry(QRect(20, 60, 61, 16));
        roiOpsScalerSpinBox = new QDoubleSpinBox(roiOpsTab);
        roiOpsScalerSpinBox->setObjectName(QString::fromUtf8("roiOpsScalerSpinBox"));
        roiOpsScalerSpinBox->setGeometry(QRect(270, 60, 62, 22));
        roiOpsScalerSpinBox->setMaximum(4);
        roiOpsScalerSpinBox->setSingleStep(0.01);
        roiOpsScalerSpinBox->setValue(2);
        roiOpsRedoButton = new QPushButton(roiOpsTab);
        roiOpsRedoButton->setObjectName(QString::fromUtf8("roiOpsRedoButton"));
        roiOpsRedoButton->setGeometry(QRect(260, 130, 75, 23));
        roiOpsDefaultsButton = new QPushButton(roiOpsTab);
        roiOpsDefaultsButton->setObjectName(QString::fromUtf8("roiOpsDefaultsButton"));
        roiOpsDefaultsButton->setGeometry(QRect(180, 130, 75, 23));
        roiOpsScalerSlider = new QSlider(roiOpsTab);
        roiOpsScalerSlider->setObjectName(QString::fromUtf8("roiOpsScalerSlider"));
        roiOpsScalerSlider->setGeometry(QRect(90, 60, 160, 19));
        roiOpsScalerSlider->setMaximum(100);
        roiOpsScalerSlider->setOrientation(Qt::Horizontal);
        optionTabs->addTab(roiOpsTab, QString());
        lseOpsTab = new QWidget();
        lseOpsTab->setObjectName(QString::fromUtf8("lseOpsTab"));
        lseOpsHndLabel = new QLabel(lseOpsTab);
        lseOpsHndLabel->setObjectName(QString::fromUtf8("lseOpsHndLabel"));
        lseOpsHndLabel->setGeometry(QRect(20, 60, 51, 16));
        lseOpsRedoButton = new QPushButton(lseOpsTab);
        lseOpsRedoButton->setObjectName(QString::fromUtf8("lseOpsRedoButton"));
        lseOpsRedoButton->setGeometry(QRect(260, 130, 75, 23));
        lseOpsDefaultsButton = new QPushButton(lseOpsTab);
        lseOpsDefaultsButton->setObjectName(QString::fromUtf8("lseOpsDefaultsButton"));
        lseOpsDefaultsButton->setGeometry(QRect(180, 130, 75, 23));
        lseOpsHandleSpinBox = new QDoubleSpinBox(lseOpsTab);
        lseOpsHandleSpinBox->setObjectName(QString::fromUtf8("lseOpsHandleSpinBox"));
        lseOpsHandleSpinBox->setGeometry(QRect(270, 60, 62, 22));
        lseOpsHandleSpinBox->setMinimum(0.01);
        lseOpsHandleSpinBox->setMaximum(2);
        lseOpsHandleSpinBox->setSingleStep(0.01);
        lseOpsHandleSpinBox->setValue(0.5);
        lseOpsHandleSlider = new QSlider(lseOpsTab);
        lseOpsHandleSlider->setObjectName(QString::fromUtf8("lseOpsHandleSlider"));
        lseOpsHandleSlider->setGeometry(QRect(90, 60, 160, 19));
        lseOpsHandleSlider->setMaximum(100);
        lseOpsHandleSlider->setOrientation(Qt::Horizontal);
        optionTabs->addTab(lseOpsTab, QString());

        retranslateUi(MenuOptions);

        optionTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MenuOptions);
    } // setupUi

    void retranslateUi(QWidget *MenuOptions)
    {
        MenuOptions->setWindowTitle(QApplication::translate("MenuOptions", "Options", 0, QApplication::UnicodeUTF8));
        silOpsThetaNLabel->setText(QApplication::translate("MenuOptions", "theta_n", 0, QApplication::UnicodeUTF8));
        silOpsThetaPLabel->setText(QApplication::translate("MenuOptions", "theta_p", 0, QApplication::UnicodeUTF8));
        silOpsDefaultsButton->setText(QApplication::translate("MenuOptions", "Defaults", 0, QApplication::UnicodeUTF8));
        optionTabs->setTabText(optionTabs->indexOf(silOpsTab), QApplication::translate("MenuOptions", "Silhouettes", 0, QApplication::UnicodeUTF8));
        hndOpsProxLabel->setText(QApplication::translate("MenuOptions", "proximity", 0, QApplication::UnicodeUTF8));
        hndOpsSimLabel->setText(QApplication::translate("MenuOptions", "similarity", 0, QApplication::UnicodeUTF8));
        hndOpsRedoButton->setText(QApplication::translate("MenuOptions", "Redo", 0, QApplication::UnicodeUTF8));
        hndOpsDefaultsButton->setText(QApplication::translate("MenuOptions", "Defaults", 0, QApplication::UnicodeUTF8));
        optionTabs->setTabText(optionTabs->indexOf(hndOpsTab), QApplication::translate("MenuOptions", "Handle", 0, QApplication::UnicodeUTF8));
        roiOpsScalerLabel->setText(QApplication::translate("MenuOptions", "rad_scaler", 0, QApplication::UnicodeUTF8));
        roiOpsRedoButton->setText(QApplication::translate("MenuOptions", "Redo", 0, QApplication::UnicodeUTF8));
        roiOpsDefaultsButton->setText(QApplication::translate("MenuOptions", "Defaults", 0, QApplication::UnicodeUTF8));
        optionTabs->setTabText(optionTabs->indexOf(roiOpsTab), QApplication::translate("MenuOptions", "ROI", 0, QApplication::UnicodeUTF8));
        lseOpsHndLabel->setText(QApplication::translate("MenuOptions", "w_handle", 0, QApplication::UnicodeUTF8));
        lseOpsRedoButton->setText(QApplication::translate("MenuOptions", "Redo", 0, QApplication::UnicodeUTF8));
        lseOpsDefaultsButton->setText(QApplication::translate("MenuOptions", "Defaults", 0, QApplication::UnicodeUTF8));
        optionTabs->setTabText(optionTabs->indexOf(lseOpsTab), QApplication::translate("MenuOptions", "LSE", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MenuOptions: public Ui_MenuOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BENDEROPTIONSUIPPE_H
