#ifndef THREADUSB_H
#define THREADUSB_H

#include <QtCore>
#include <QObject>
#include <QThread>
#include "CustomUSB.h"
#include "QCustomPlot/SignalData.h"


class ThreadUSB : public QThread
{
    Q_OBJECT
public:
    explicit ThreadUSB(CustomUSB *customUSB, QObject *parent = nullptr);
    QVector<double> data;
    QString dataSignal;
    enum Modo { modoNone, modoConected, modoDisconected, modoDato, modoSignal };
    Q_ENUM(Modo)

    void setTime(unsigned long msec = 1000){ time = msec; }
    void setScale(double sf){ scale = sf; }
    unsigned long getTime() { return time; }
    void setModo(Modo m){ modo = m; }
    Modo getModo() { return modo; }
signals:
    void datoNuevoADC(QVector<double> *data);
    void datoNuevoMediciones(QString dataSignal);
public slots:
    void modChange(Modo mod);
    void timeChange(SignalData::samplimngFrecuency fs);
protected:
    void run() override;
private:
    CustomUSB *pCustomUSB;
    unsigned long time;
    double scale;
    Modo modo;

};
#endif // THREADUSB_H
