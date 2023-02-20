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
    enum Channel{ CH1, CH2, CH3, CH4 };
    Q_ENUM(Channel)
Q_SIGNALS:
    void itemMoved(QCPAbstractItem *item, QMouseEvent *event);
    void mesure(SignalData *signalData);
public slots:
    void pushButtonAutoEscala();
    void LeerSignal(QVector<double> *dato);
    void LeerMesure(QString dato);
    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    QVector<double> datoTime;
    QVector<double> datoADC;
    SignalData *signalData;
    // QWidget interface
public:
    virtual QSize sizeHint() const Q_DECL_OVERRIDE;
private:
    Channel canal;
};

#endif // CUSTOMPLOT_H

