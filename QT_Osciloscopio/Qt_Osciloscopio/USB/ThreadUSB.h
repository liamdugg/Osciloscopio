#ifndef THREADUSB_H
#define THREADUSB_H

#include <QtCore>
#include <QObject>
#include <QThread>
#include "CustomUSB.h"



class ThreadUSB : public QThread
{
    Q_OBJECT
public:
    explicit ThreadUSB(CustomUSB *customUSB, QObject *parent = nullptr);
    QVector<double> data;
    QString dataSignal;
    enum Modo { modoNone, modoConected, modoDisconected, modoDato, modoSignal };
    Q_ENUM(Modo)

    void setModo(Modo m){ modo = m; }
    Modo getModo() { return modo; }
signals:
    void datoNuevoSingnal(QVector<double> *data);
    void datoNuevoMesure(QString dataSignal);
public slots:
    void modChange(Modo mod);
protected:
    void run() override;
private:
    CustomUSB *pCustomUSB;
    Modo modo;

};
#endif // THREADUSB_H
