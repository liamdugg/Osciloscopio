#include "duthread.h"

DuThread::DuThread(QCustomPlot *pCustomPlot, QObject *parent)
    : QThread{parent}
{
    connect(this,&DuThread::finished, this,&DuThread::deleteLater);
    duCustomPlot = pCustomPlot;
}
void DuThread::run(){
    int cuenta = 0;
    while(true){
        qDebug() << cuenta;
        cuenta++;
        if(cuenta >100)
            cuenta = 0;
        msleep(100);
    }
}
void DuThread::pushButtonSaveIMG()
{
    QString filename = QFileDialog::getSaveFileName();
    if(filename == ""){

    }
    if(filename.endsWith(".png"))
        duCustomPlot->savePng(filename, duCustomPlot->width(), duCustomPlot->height());
    if(filename.endsWith(".jpg"))
        duCustomPlot->saveJpg(filename, duCustomPlot->width(), duCustomPlot->height());
    if(filename.endsWith(".bmp"))
        duCustomPlot->saveBmp(filename, duCustomPlot->width(), duCustomPlot->height());
    //qDebug() << "Guardando Imagen...";
}
