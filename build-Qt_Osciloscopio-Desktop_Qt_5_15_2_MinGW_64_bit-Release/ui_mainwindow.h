/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QCustomPlot/customplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConection;
    QWidget *centralwidget;
    QGridLayout *gridLayout_8;
    CustomPlot *qCustomPlot;
    QGroupBox *groupBoxCH1;
    QGridLayout *gridLayout_3;
    QLineEdit *PeriodoCH1;
    QLineEdit *VrmsCH1;
    QLabel *labelPeriodo1;
    QPushButton *pushButtonCH1;
    QLabel *labelAmplitud1;
    QLabel *labelVrms1;
    QLineEdit *AmplitudCH1;
    QLabel *labelFrecuencia1;
    QLineEdit *FrecuenciaCH1;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBoxConexion;
    QGridLayout *gridLayout_4;
    QLabel *label_2;
    QLineEdit *lineEditEstado;
    QPushButton *pushButtonConectar;
    QGroupBox *groupBoxCursor;
    QGridLayout *gridLayout_7;
    QLabel *labelModo;
    QComboBox *comboBoxModo;
    QGridLayout *gridLayout_2;
    QLabel *labelCursor1;
    QCheckBox *checkBoxH1;
    QCheckBox *checkBoxV1;
    QLabel *labelCursor2;
    QCheckBox *checkBoxH2;
    QCheckBox *checkBoxV2;
    QGroupBox *groupBoxCH2;
    QGridLayout *gridLayout_6;
    QPushButton *pushButtonCH2;
    QLabel *labelAmplitud;
    QLineEdit *AmplitudCH2;
    QLabel *labelVrms2;
    QLineEdit *VrmsCH2;
    QLabel *labelFrecuencia2;
    QLineEdit *FrecuenciaCH2;
    QLabel *labelPeriodo2;
    QLineEdit *PeriodoCH2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxEscala;
    QGridLayout *gridLayout;
    QDial *dialTime;
    QDial *dialVolt;
    QGroupBox *groupBoxAUTO;
    QGridLayout *gridLayout_5;
    QPushButton *pushButtonAUTO;
    QPushButton *pushButtonIMG;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1700, 710);
        MainWindow->setMinimumSize(QSize(1700, 710));
        MainWindow->setMaximumSize(QSize(1700, 710));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Img/Osciloscopio.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 39); font: 14pt \"Comic Sans MS\";\n"
"color: rgb(255, 255, 255);"));
        MainWindow->setIconSize(QSize(150, 150));
        MainWindow->setAnimated(false);
        actionConection = new QAction(MainWindow);
        actionConection->setObjectName(QString::fromUtf8("actionConection"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_8 = new QGridLayout(centralwidget);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        qCustomPlot = new CustomPlot(centralwidget);
        qCustomPlot->setObjectName(QString::fromUtf8("qCustomPlot"));
        qCustomPlot->setMinimumSize(QSize(900, 650));
        qCustomPlot->setMaximumSize(QSize(16777215, 16777215));
        qCustomPlot->setStyleSheet(QString::fromUtf8("font: italic 14pt \"Comic Sans MS\";"));

        gridLayout_8->addWidget(qCustomPlot, 0, 0, 2, 1);

        groupBoxCH1 = new QGroupBox(centralwidget);
        groupBoxCH1->setObjectName(QString::fromUtf8("groupBoxCH1"));
        groupBoxCH1->setMinimumSize(QSize(380, 340));
        groupBoxCH1->setMaximumSize(QSize(380, 350));
        groupBoxCH1->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 14pt \"Comic Sans MS\";"));
        gridLayout_3 = new QGridLayout(groupBoxCH1);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        PeriodoCH1 = new QLineEdit(groupBoxCH1);
        PeriodoCH1->setObjectName(QString::fromUtf8("PeriodoCH1"));
        PeriodoCH1->setEnabled(false);
        PeriodoCH1->setStyleSheet(QString::fromUtf8("color: lightgreen; background-color: black; border: 2px solid lightgreen; font: 14pt \"Comic Sans MS\";"));
        PeriodoCH1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(PeriodoCH1, 4, 1, 1, 1);

        VrmsCH1 = new QLineEdit(groupBoxCH1);
        VrmsCH1->setObjectName(QString::fromUtf8("VrmsCH1"));
        VrmsCH1->setEnabled(false);
        VrmsCH1->setStyleSheet(QString::fromUtf8("color: lightgreen; background-color: black; border: 2px solid lightgreen; font: 14pt \"Comic Sans MS\";"));
        VrmsCH1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(VrmsCH1, 2, 1, 1, 1);

        labelPeriodo1 = new QLabel(groupBoxCH1);
        labelPeriodo1->setObjectName(QString::fromUtf8("labelPeriodo1"));
        labelPeriodo1->setStyleSheet(QString::fromUtf8("font: 14pt \"Comic Sans MS\";"));

        gridLayout_3->addWidget(labelPeriodo1, 4, 0, 1, 1);

        pushButtonCH1 = new QPushButton(groupBoxCH1);
        pushButtonCH1->setObjectName(QString::fromUtf8("pushButtonCH1"));
        pushButtonCH1->setStyleSheet(QString::fromUtf8("color: black; font: 14pt \"Comic Sans MS\";\n"
"background-color: lightgreen;"));

        gridLayout_3->addWidget(pushButtonCH1, 0, 0, 1, 2);

        labelAmplitud1 = new QLabel(groupBoxCH1);
        labelAmplitud1->setObjectName(QString::fromUtf8("labelAmplitud1"));
        labelAmplitud1->setStyleSheet(QString::fromUtf8("font: 14pt \"Comic Sans MS\";"));

        gridLayout_3->addWidget(labelAmplitud1, 1, 0, 1, 1);

        labelVrms1 = new QLabel(groupBoxCH1);
        labelVrms1->setObjectName(QString::fromUtf8("labelVrms1"));
        labelVrms1->setStyleSheet(QString::fromUtf8("font: 14pt \"Comic Sans MS\";"));

        gridLayout_3->addWidget(labelVrms1, 2, 0, 1, 1);

        AmplitudCH1 = new QLineEdit(groupBoxCH1);
        AmplitudCH1->setObjectName(QString::fromUtf8("AmplitudCH1"));
        AmplitudCH1->setEnabled(false);
        AmplitudCH1->setStyleSheet(QString::fromUtf8("color: lightgreen; background-color: black; border: 2px solid lightgreen; font: 14pt \"Comic Sans MS\";"));
        AmplitudCH1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(AmplitudCH1, 1, 1, 1, 1);

        labelFrecuencia1 = new QLabel(groupBoxCH1);
        labelFrecuencia1->setObjectName(QString::fromUtf8("labelFrecuencia1"));
        labelFrecuencia1->setStyleSheet(QString::fromUtf8("font: 14pt \"Comic Sans MS\";"));

        gridLayout_3->addWidget(labelFrecuencia1, 3, 0, 1, 1);

        FrecuenciaCH1 = new QLineEdit(groupBoxCH1);
        FrecuenciaCH1->setObjectName(QString::fromUtf8("FrecuenciaCH1"));
        FrecuenciaCH1->setEnabled(false);
        FrecuenciaCH1->setStyleSheet(QString::fromUtf8("color: lightgreen; background-color: black; border: 2px solid lightgreen; font: 14pt \"Comic Sans MS\";"));
        FrecuenciaCH1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(FrecuenciaCH1, 3, 1, 1, 1);


        gridLayout_8->addWidget(groupBoxCH1, 0, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBoxConexion = new QGroupBox(centralwidget);
        groupBoxConexion->setObjectName(QString::fromUtf8("groupBoxConexion"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBoxConexion->sizePolicy().hasHeightForWidth());
        groupBoxConexion->setSizePolicy(sizePolicy);
        groupBoxConexion->setMinimumSize(QSize(380, 0));
        groupBoxConexion->setMaximumSize(QSize(16777215, 160));
        groupBoxConexion->setStyleSheet(QString::fromUtf8("font: 12pt \"Comic Sans MS\";\n"
"color: rgb(255, 255, 255);\n"
""));
        gridLayout_4 = new QGridLayout(groupBoxConexion);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_2 = new QLabel(groupBoxConexion);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"Comic Sans MS\";"));

        gridLayout_4->addWidget(label_2, 0, 0, 1, 1);

        lineEditEstado = new QLineEdit(groupBoxConexion);
        lineEditEstado->setObjectName(QString::fromUtf8("lineEditEstado"));
        lineEditEstado->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);\n"
"font: 12pt \"Comic Sans MS\";"));
        lineEditEstado->setAlignment(Qt::AlignCenter);
        lineEditEstado->setReadOnly(true);

        gridLayout_4->addWidget(lineEditEstado, 0, 1, 1, 1);

        pushButtonConectar = new QPushButton(groupBoxConexion);
        pushButtonConectar->setObjectName(QString::fromUtf8("pushButtonConectar"));
        pushButtonConectar->setStyleSheet(QString::fromUtf8("background-color: rgb(31, 58, 147);\n"
"font: 12pt \"Comic Sans MS\";\n"
" border: 2px solid white;"));

        gridLayout_4->addWidget(pushButtonConectar, 1, 0, 1, 2);


        verticalLayout_2->addWidget(groupBoxConexion);

        groupBoxCursor = new QGroupBox(centralwidget);
        groupBoxCursor->setObjectName(QString::fromUtf8("groupBoxCursor"));
        groupBoxCursor->setMinimumSize(QSize(380, 0));
        groupBoxCursor->setMaximumSize(QSize(380, 180));
        groupBoxCursor->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 14pt \"Comic Sans MS\";"));
        gridLayout_7 = new QGridLayout(groupBoxCursor);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        labelModo = new QLabel(groupBoxCursor);
        labelModo->setObjectName(QString::fromUtf8("labelModo"));
        labelModo->setMinimumSize(QSize(0, 0));
        labelModo->setMaximumSize(QSize(16777215, 16777215));
        labelModo->setStyleSheet(QString::fromUtf8("font: 14pt \"Comic Sans MS\";"));

        gridLayout_7->addWidget(labelModo, 0, 0, 1, 1);

        comboBoxModo = new QComboBox(groupBoxCursor);
        comboBoxModo->addItem(QString());
        comboBoxModo->addItem(QString());
        comboBoxModo->addItem(QString());
        comboBoxModo->addItem(QString());
        comboBoxModo->setObjectName(QString::fromUtf8("comboBoxModo"));
        comboBoxModo->setStyleSheet(QString::fromUtf8("font: 11pt \"Comic Sans MS\";"));

        gridLayout_7->addWidget(comboBoxModo, 0, 1, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        labelCursor1 = new QLabel(groupBoxCursor);
        labelCursor1->setObjectName(QString::fromUtf8("labelCursor1"));
        labelCursor1->setStyleSheet(QString::fromUtf8("background-color: lightgreen;\n"
"font: 10pt \"Comic Sans MS\";\n"
"border: 6px solid rgb(0, 0, 39);;"));

        gridLayout_2->addWidget(labelCursor1, 0, 0, 1, 1);

        checkBoxH1 = new QCheckBox(groupBoxCursor);
        checkBoxH1->setObjectName(QString::fromUtf8("checkBoxH1"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 39, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush2(QColor(255, 255, 255, 128));
        brush2.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush2);
#endif
        checkBoxH1->setPalette(palette);
        checkBoxH1->setStyleSheet(QString::fromUtf8("font: 10pt \"Comic Sans MS\";"));

        gridLayout_2->addWidget(checkBoxH1, 0, 1, 1, 1);

        checkBoxV1 = new QCheckBox(groupBoxCursor);
        checkBoxV1->setObjectName(QString::fromUtf8("checkBoxV1"));
        checkBoxV1->setStyleSheet(QString::fromUtf8("font: 10pt \"Comic Sans MS\";\n"
""));

        gridLayout_2->addWidget(checkBoxV1, 0, 2, 1, 1);

        labelCursor2 = new QLabel(groupBoxCursor);
        labelCursor2->setObjectName(QString::fromUtf8("labelCursor2"));
        labelCursor2->setStyleSheet(QString::fromUtf8("background-color: gold;\n"
"font: 10pt \"Comic Sans MS\";\n"
"border: 6px solid rgb(0, 0, 39);"));

        gridLayout_2->addWidget(labelCursor2, 1, 0, 1, 1);

        checkBoxH2 = new QCheckBox(groupBoxCursor);
        checkBoxH2->setObjectName(QString::fromUtf8("checkBoxH2"));
        checkBoxH2->setStyleSheet(QString::fromUtf8("font: 10pt \"Comic Sans MS\";"));

        gridLayout_2->addWidget(checkBoxH2, 1, 1, 1, 1);

        checkBoxV2 = new QCheckBox(groupBoxCursor);
        checkBoxV2->setObjectName(QString::fromUtf8("checkBoxV2"));
        checkBoxV2->setStyleSheet(QString::fromUtf8("font: 10pt \"Comic Sans MS\";\n"
""));

        gridLayout_2->addWidget(checkBoxV2, 1, 2, 1, 1);


        gridLayout_7->addLayout(gridLayout_2, 1, 0, 1, 2);


        verticalLayout_2->addWidget(groupBoxCursor);


        gridLayout_8->addLayout(verticalLayout_2, 0, 2, 1, 1);

        groupBoxCH2 = new QGroupBox(centralwidget);
        groupBoxCH2->setObjectName(QString::fromUtf8("groupBoxCH2"));
        groupBoxCH2->setMinimumSize(QSize(380, 340));
        groupBoxCH2->setMaximumSize(QSize(380, 350));
        groupBoxCH2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 14pt \"Comic Sans MS\";"));
        gridLayout_6 = new QGridLayout(groupBoxCH2);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        pushButtonCH2 = new QPushButton(groupBoxCH2);
        pushButtonCH2->setObjectName(QString::fromUtf8("pushButtonCH2"));
        pushButtonCH2->setStyleSheet(QString::fromUtf8("color: black; font: 14pt \"Comic Sans MS\";\n"
"background-color: gold;"));

        gridLayout_6->addWidget(pushButtonCH2, 0, 0, 1, 2);

        labelAmplitud = new QLabel(groupBoxCH2);
        labelAmplitud->setObjectName(QString::fromUtf8("labelAmplitud"));
        labelAmplitud->setStyleSheet(QString::fromUtf8("font: 14pt \"Comic Sans MS\";"));

        gridLayout_6->addWidget(labelAmplitud, 1, 0, 1, 1);

        AmplitudCH2 = new QLineEdit(groupBoxCH2);
        AmplitudCH2->setObjectName(QString::fromUtf8("AmplitudCH2"));
        AmplitudCH2->setEnabled(false);
        AmplitudCH2->setStyleSheet(QString::fromUtf8("color: yellow; background-color: black; border: 2px solid yellow; font: 14pt \"Comic Sans MS\";"));
        AmplitudCH2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(AmplitudCH2, 1, 1, 1, 1);

        labelVrms2 = new QLabel(groupBoxCH2);
        labelVrms2->setObjectName(QString::fromUtf8("labelVrms2"));
        labelVrms2->setStyleSheet(QString::fromUtf8("font: 14pt \"Comic Sans MS\";"));

        gridLayout_6->addWidget(labelVrms2, 2, 0, 1, 1);

        VrmsCH2 = new QLineEdit(groupBoxCH2);
        VrmsCH2->setObjectName(QString::fromUtf8("VrmsCH2"));
        VrmsCH2->setEnabled(false);
        VrmsCH2->setStyleSheet(QString::fromUtf8("color: yellow; background-color: black; border: 2px solid yellow; font: 14pt \"Comic Sans MS\";"));
        VrmsCH2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(VrmsCH2, 2, 1, 1, 1);

        labelFrecuencia2 = new QLabel(groupBoxCH2);
        labelFrecuencia2->setObjectName(QString::fromUtf8("labelFrecuencia2"));
        labelFrecuencia2->setStyleSheet(QString::fromUtf8("font: 14pt \"Comic Sans MS\";"));

        gridLayout_6->addWidget(labelFrecuencia2, 3, 0, 1, 1);

        FrecuenciaCH2 = new QLineEdit(groupBoxCH2);
        FrecuenciaCH2->setObjectName(QString::fromUtf8("FrecuenciaCH2"));
        FrecuenciaCH2->setEnabled(false);
        FrecuenciaCH2->setStyleSheet(QString::fromUtf8("color: yellow; background-color: black; border: 2px solid yellow; font: 14pt \"Comic Sans MS\";"));
        FrecuenciaCH2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(FrecuenciaCH2, 3, 1, 1, 1);

        labelPeriodo2 = new QLabel(groupBoxCH2);
        labelPeriodo2->setObjectName(QString::fromUtf8("labelPeriodo2"));
        labelPeriodo2->setStyleSheet(QString::fromUtf8("font: 14pt \"Comic Sans MS\";"));

        gridLayout_6->addWidget(labelPeriodo2, 4, 0, 1, 1);

        PeriodoCH2 = new QLineEdit(groupBoxCH2);
        PeriodoCH2->setObjectName(QString::fromUtf8("PeriodoCH2"));
        PeriodoCH2->setEnabled(false);
        PeriodoCH2->setStyleSheet(QString::fromUtf8("color: yellow; background-color: black; border: 2px solid yellow; font: 14pt \"Comic Sans MS\";"));
        PeriodoCH2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(PeriodoCH2, 4, 1, 1, 1);


        gridLayout_8->addWidget(groupBoxCH2, 1, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBoxEscala = new QGroupBox(centralwidget);
        groupBoxEscala->setObjectName(QString::fromUtf8("groupBoxEscala"));
        groupBoxEscala->setMinimumSize(QSize(380, 0));
        groupBoxEscala->setMaximumSize(QSize(380, 16777215));
        groupBoxEscala->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 12pt \"Comic Sans MS\";"));
        groupBoxEscala->setAlignment(Qt::AlignCenter);
        gridLayout = new QGridLayout(groupBoxEscala);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        dialTime = new QDial(groupBoxEscala);
        dialTime->setObjectName(QString::fromUtf8("dialTime"));
        dialTime->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-color: black;\n"
""));
        dialTime->setMinimum(1);
        dialTime->setMaximum(1000);
        dialTime->setSingleStep(2);
        dialTime->setPageStep(100);
        dialTime->setValue(1);
        dialTime->setSliderPosition(1);
        dialTime->setTracking(true);
        dialTime->setOrientation(Qt::Vertical);
        dialTime->setInvertedAppearance(true);
        dialTime->setInvertedControls(false);
        dialTime->setWrapping(false);
        dialTime->setNotchTarget(5.000000000000000);
        dialTime->setNotchesVisible(true);

        gridLayout->addWidget(dialTime, 0, 1, 1, 1);

        dialVolt = new QDial(groupBoxEscala);
        dialVolt->setObjectName(QString::fromUtf8("dialVolt"));
        dialVolt->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-color: black;\n"
""));
        dialVolt->setMinimum(1);
        dialVolt->setMaximum(1000);
        dialVolt->setSingleStep(5);
        dialVolt->setPageStep(100);
        dialVolt->setValue(1);
        dialVolt->setSliderPosition(1);
        dialVolt->setOrientation(Qt::Vertical);
        dialVolt->setInvertedAppearance(true);
        dialVolt->setNotchTarget(5.000000000000000);
        dialVolt->setNotchesVisible(true);

        gridLayout->addWidget(dialVolt, 0, 2, 1, 1);


        verticalLayout->addWidget(groupBoxEscala);

        groupBoxAUTO = new QGroupBox(centralwidget);
        groupBoxAUTO->setObjectName(QString::fromUtf8("groupBoxAUTO"));
        groupBoxAUTO->setMinimumSize(QSize(380, 130));
        groupBoxAUTO->setMaximumSize(QSize(380, 130));
        gridLayout_5 = new QGridLayout(groupBoxAUTO);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        pushButtonAUTO = new QPushButton(groupBoxAUTO);
        pushButtonAUTO->setObjectName(QString::fromUtf8("pushButtonAUTO"));
        pushButtonAUTO->setStyleSheet(QString::fromUtf8("background-color: Dodgerblue;\n"
"font: 12pt \"Comic Sans MS\";"));

        gridLayout_5->addWidget(pushButtonAUTO, 0, 0, 1, 1);

        pushButtonIMG = new QPushButton(groupBoxAUTO);
        pushButtonIMG->setObjectName(QString::fromUtf8("pushButtonIMG"));
        pushButtonIMG->setEnabled(true);
        pushButtonIMG->setMinimumSize(QSize(0, 0));
        pushButtonIMG->setMaximumSize(QSize(100, 100));
        pushButtonIMG->setAutoFillBackground(false);
        pushButtonIMG->setStyleSheet(QString::fromUtf8(""));
        pushButtonIMG->setInputMethodHints(Qt::ImhNone);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Img/screenshoot.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonIMG->setIcon(icon1);
        pushButtonIMG->setIconSize(QSize(80, 80));
        pushButtonIMG->setCheckable(false);
        pushButtonIMG->setChecked(false);
        pushButtonIMG->setAutoRepeat(false);
        pushButtonIMG->setAutoExclusive(false);
        pushButtonIMG->setAutoDefault(false);
        pushButtonIMG->setFlat(true);

        gridLayout_5->addWidget(pushButtonIMG, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBoxAUTO);


        gridLayout_8->addLayout(verticalLayout, 1, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        pushButtonIMG->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Osciloscopio", nullptr));
        actionConection->setText(QCoreApplication::translate("MainWindow", "Desconectado", nullptr));
#if QT_CONFIG(tooltip)
        actionConection->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">Estado de conexi\303\263n</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBoxCH1->setTitle(QCoreApplication::translate("MainWindow", "CH1", nullptr));
        PeriodoCH1->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        VrmsCH1->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        labelPeriodo1->setText(QCoreApplication::translate("MainWindow", "Periodo:", nullptr));
        pushButtonCH1->setText(QCoreApplication::translate("MainWindow", "INICIAR MEDICI\303\223N", nullptr));
        labelAmplitud1->setText(QCoreApplication::translate("MainWindow", "Amplitud:", nullptr));
        labelVrms1->setText(QCoreApplication::translate("MainWindow", "Vrms:", nullptr));
        AmplitudCH1->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        labelFrecuencia1->setText(QCoreApplication::translate("MainWindow", "Frecuencia:", nullptr));
        FrecuenciaCH1->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        groupBoxConexion->setTitle(QCoreApplication::translate("MainWindow", "Conexi\303\263n", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Estado:", nullptr));
        lineEditEstado->setText(QCoreApplication::translate("MainWindow", "Desconectado", nullptr));
        pushButtonConectar->setText(QCoreApplication::translate("MainWindow", "Conectar", nullptr));
        groupBoxCursor->setTitle(QCoreApplication::translate("MainWindow", "Cursor", nullptr));
        labelModo->setText(QCoreApplication::translate("MainWindow", "Modo:", nullptr));
        comboBoxModo->setItemText(0, QCoreApplication::translate("MainWindow", "Ninguno", nullptr));
        comboBoxModo->setItemText(1, QCoreApplication::translate("MainWindow", "Free", nullptr));
        comboBoxModo->setItemText(2, QCoreApplication::translate("MainWindow", "Follow Cursor", nullptr));
        comboBoxModo->setItemText(3, QCoreApplication::translate("MainWindow", "Tracing", nullptr));

        labelCursor1->setText(QString());
        checkBoxH1->setText(QCoreApplication::translate("MainWindow", "Horizontal", nullptr));
        checkBoxV1->setText(QCoreApplication::translate("MainWindow", "Vertical", nullptr));
        labelCursor2->setText(QString());
        checkBoxH2->setText(QCoreApplication::translate("MainWindow", "Horizontal", nullptr));
        checkBoxV2->setText(QCoreApplication::translate("MainWindow", "Vertical", nullptr));
        groupBoxCH2->setTitle(QCoreApplication::translate("MainWindow", "CH2", nullptr));
        pushButtonCH2->setText(QCoreApplication::translate("MainWindow", "INICIAR MEDICI\303\223N", nullptr));
        labelAmplitud->setText(QCoreApplication::translate("MainWindow", "Amplitud:", nullptr));
        AmplitudCH2->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        labelVrms2->setText(QCoreApplication::translate("MainWindow", "Vrms:", nullptr));
        VrmsCH2->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        labelFrecuencia2->setText(QCoreApplication::translate("MainWindow", "Frecuencia:", nullptr));
        FrecuenciaCH2->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        labelPeriodo2->setText(QCoreApplication::translate("MainWindow", "Periodo:", nullptr));
        PeriodoCH2->setText(QCoreApplication::translate("MainWindow", "---", nullptr));
        groupBoxEscala->setTitle(QCoreApplication::translate("MainWindow", "Vertical [s]           Horizontal [V]", nullptr));
        groupBoxAUTO->setTitle(QString());
        pushButtonAUTO->setText(QCoreApplication::translate("MainWindow", "AUTO", nullptr));
        pushButtonIMG->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
