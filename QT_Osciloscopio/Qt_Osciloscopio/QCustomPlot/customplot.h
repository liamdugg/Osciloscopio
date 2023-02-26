#ifndef CUSTOMPLOT_H
#define CUSTOMPLOT_H

#include "qcustomplot.h"
#include "QCustomPlot/SignalData.h"

class SignalData;

class CustomPlot : public QCustomPlot
{
    Q_OBJECT
public:
    CustomPlot(QWidget *parent = Q_NULLPTR);
    virtual ~CustomPlot() Q_DECL_OVERRIDE;
    void InitGraph();
    enum unidades{ frecuencia, tiempo, Amplitud, Vrms };
    SignalData::samplimngFrecuency convertirFS(QString s);
    SignalData::scaleAmplitud convertirScaleFactor(QString s);
    QString convertir(QString, unidades);
    QString convertirFrecuencia(QString);
    QString convertirPerido(QString);
    QString convertirAmplitud(QString);
    QString convertirVrms(QString);
    /*Dial*/
    void setRangeDialTime(int xmin, int xmax);
Q_SIGNALS:
    void itemMoved(QCPAbstractItem *item, QMouseEvent *event);

    void setTimeChange(SignalData::samplimngFrecuency);
    void mesure(SignalData *signalData);
public slots:
    void pushButtonAutoEscala();
    void LeerADC(QVector<double> *dato);
    void LeerMediciones(QString dato);
    // QWidget interface

    /*Dial*/
    void setValueDialTime(int value);
    void setValueDialVolt(int value);
    void setRangeDialGraph();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    QVector<double> datoTime;
    QVector<double> datoADC;
    SignalData *signalData;

public:
    virtual QSize sizeHint() const Q_DECL_OVERRIDE;

};

#endif // CUSTOMPLOT_H

