#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QCustomPlot/customplot.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CustomPlot *pCustomPlot = ui->qCustomPlot;
    pCustomUSB = new CustomUSB();
    pThreadUSB = new ThreadUSB(pCustomUSB, this);
    time = new QTimer(this);
    connect(pThreadUSB, &ThreadUSB::datoNuevoSingnal, pCustomPlot, &CustomPlot::LeerSignal);
    connect(pThreadUSB, &ThreadUSB::datoNuevoMesure, pCustomPlot, &CustomPlot::LeerMesure);
    connect(ui->pushButtonAUTO, &QPushButton::clicked, pCustomPlot, &CustomPlot::pushButtonAutoEscala);
    connect(pCustomPlot, &CustomPlot::mesure, this, &MainWindow::actualizarMediciones);

    QComboBox *comboBoxModo = ui->comboBoxModo;
    CrossLine *crossLine1 = new CrossLine(pCustomPlot, pCustomPlot->graph());
    connect(comboBoxModo, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),  [crossLine1](int index) {
        crossLine1->setLineMode(CrossLine::LineMode(index));
    });
    connect(pCustomPlot, SIGNAL(itemMoved(QCPAbstractItem*,QMouseEvent*)),
            crossLine1, SLOT(onItemMoved(QCPAbstractItem*,QMouseEvent*)));

    CrossLine *crossLine2 = new CrossLine(pCustomPlot, pCustomPlot->graph());
    connect(comboBoxModo, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),  [crossLine2](int index) {
        crossLine2->setLineMode(CrossLine::LineMode(index));
    });
    connect(pCustomPlot, SIGNAL(itemMoved(QCPAbstractItem*,QMouseEvent*)),
            crossLine2, SLOT(onItemMoved(QCPAbstractItem*,QMouseEvent*)));

    crossLine1->setupColor(QColor(144, 238, 144));
    crossLine2->setupColor(QColor(255, 215, 0));

    connect(pCustomPlot, &QCustomPlot::mousePress, [pCustomPlot](QMouseEvent *event) {
        if (pCustomPlot->itemAt(event->localPos()) && !pCustomPlot->selectedItems().isEmpty())
            pCustomPlot->setInteractions( QCP::iSelectItems);
    });
    connect(pCustomPlot, &QCustomPlot::mouseRelease, [pCustomPlot](){
        pCustomPlot->setInteractions(QCP::iSelectItems);
    });

    connect(ui->checkBoxH1, static_cast<void (QCheckBox:: *)(int)>(&QCheckBox::stateChanged), crossLine1, &CrossLine::checkBoxUpdateHorizontal);
    connect(ui->checkBoxV1, static_cast<void (QCheckBox:: *)(int)>(&QCheckBox::stateChanged), crossLine1, &CrossLine::checkBoxUpdateVertical);
    connect(ui->checkBoxH2, static_cast<void (QCheckBox:: *)(int)>(&QCheckBox::stateChanged), crossLine2, &CrossLine::checkBoxUpdateHorizontal);
    connect(ui->checkBoxV2, static_cast<void (QCheckBox:: *)(int)>(&QCheckBox::stateChanged), crossLine2, &CrossLine::checkBoxUpdateVertical);

    connect(ui->comboBoxModo, &QComboBox::currentTextChanged, this, &MainWindow::ComboBoxUpdate);
    crossLine1->setLineVisible(Qt::Horizontal, false);
    crossLine1->setLineVisible(Qt::Vertical, false);
    crossLine2->setLineVisible(Qt::Horizontal, false);
    crossLine2->setLineVisible(Qt::Vertical, false);

    InicializarUSB();
    actualizarEstado(false);
    initDial();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InicializarUSB()
{
    connect(ui->pushButtonConectar, &QPushButton::clicked, this, &MainWindow::pushButtonConexion);
    connect(ui->pushButtonCH1, &QPushButton::clicked, this, &MainWindow::pushButtonMediciones);
    connect(this, &MainWindow::pushButtonModo, pThreadUSB, &ThreadUSB::modChange);
    connect(time, &QTimer::timeout, this, &MainWindow::getMesure);
    connect(pCustomUSB, &CustomUSB::statusChange, this, &MainWindow::actualizarEstado);
}

void MainWindow::initDial()
{
    connect(ui->dialTime, &QDial::valueChanged, this, &MainWindow::setValueDialTime);
    connect(ui->dialVolt, &QDial::valueChanged, this, &MainWindow::setValueDialVolt);
}

void MainWindow::ComboBoxUpdate(QString Text)
{
    if("Ninguno" == Text){
        ui->checkBoxH1->setCheckState(Qt::Unchecked);
        ui->checkBoxH2->setCheckState(Qt::Unchecked);
        ui->checkBoxV1->setCheckState(Qt::Unchecked);
        ui->checkBoxV2->setCheckState(Qt::Unchecked);
        ui->checkBoxH1->setEnabled(false);
        ui->checkBoxH2->setEnabled(false);
        ui->checkBoxV1->setEnabled(false);
        ui->checkBoxV2->setEnabled(false);
    } else {
        ui->checkBoxH1->setEnabled(true);
        ui->checkBoxH2->setEnabled(true);
        ui->checkBoxV1->setEnabled(true);
        ui->checkBoxV2->setEnabled(true);
    }
}

void MainWindow::setValueDialTime(int value)
{
    ui->qCustomPlot->xAxis->setRange((double)(-(0.00079*value+0.04925)), (double)(0.00079*value+0.04925));
    ui->qCustomPlot->replot();
}

void MainWindow::setValueDialVolt(int value)
{
    ui->qCustomPlot->yAxis->setRange(-value/1000.0, value/1000.0);
    ui->qCustomPlot->replot();
}
void MainWindow::pushButtonConexion()
{
    if(!pCustomUSB->estadoConexion()){
        emit pushButtonModo(ThreadUSB::modoConected);
        if(pCustomUSB->conectar()){
            qDebug() << "Conectando...";
            pThreadUSB->start();
        }
    } else {
        emit pushButtonModo(ThreadUSB::modoDisconected);
        if(time->isActive()){
            emit ui->pushButtonCH1->clicked();
        }
        /* tiempo hasta que envie el aviso de desconexion */
        Sleep(1);
        if(pCustomUSB->desconectar()){
            qDebug() << "Desconectando...";
            pThreadUSB->terminate();
        }
    }
}

void MainWindow::pushButtonMediciones()
{
    static bool var = true;
    if(pCustomUSB->estadoConexion()){
        if(var == true){
            ui->pushButtonCH1->setText("DETENER MEDICION");
            ui->pushButtonCH1->setStyleSheet("font-weight: bold; color: white; background-color: lightgreen;");
            emit pushButtonModo(ThreadUSB::modoSignal);
            time->start(1000);
            var = false;
        } else {
            ui->pushButtonCH1->setText("INICIAR MEDICION");
            ui->pushButtonCH1->setStyleSheet("font-weight: bold; color: black; background-color: lightgreen;");
            emit pushButtonModo(ThreadUSB::modoNone);
            time->stop();
            var = true;
        }
    }
}

void MainWindow::getMesure()
{
    emit pushButtonModo(ThreadUSB::modoDato);
}

void MainWindow::actualizarMediciones(SignalData *mediciones)
{
    ui->AmplitudCH1->setText(mediciones->getAmplitude());
    ui->VrmsCH1->setText(mediciones->getVrms());
    ui->FrecuenciaCH1->setText(mediciones->getFrecuency());
    ui->PeriodoCH1->setText(mediciones->getPeriod());
}

void MainWindow::actualizarEstado(bool estado)
{
    if(estado == true){
        ui->lineEditEstado->setStyleSheet("font-weight: bold; color: black; background-color: lightgreen;");
        ui->lineEditEstado->setText("Conectado");
        ui->pushButtonConectar->setText("Desconectar");
        ui->groupBoxCH1->setEnabled(true);
        ui->groupBoxCH2->setDisabled(true);
        ui->groupBoxCursor->setEnabled(true);
        ui->groupBoxEscala->setEnabled(true);
        ui->groupBoxAUTO->setEnabled(true);
        //emit ui->comboBoxModo->currentTextChanged("Ninguno");
    } else {
        ui->lineEditEstado->setStyleSheet("font-weight: bold; color: white; background-color: red;");
        ui->lineEditEstado->setText("Desconectado");
        ui->pushButtonConectar->setText("Conectar");
        ui->groupBoxCH1->setDisabled(true);
        ui->groupBoxCH2->setDisabled(true);
        ui->groupBoxCursor->setDisabled(true);
        ui->groupBoxEscala->setDisabled(true);
        ui->groupBoxAUTO->setDisabled(true);
    }
}
