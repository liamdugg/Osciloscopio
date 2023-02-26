#ifndef DUTHREAD_H
#define DUTHREAD_H

#include <QObject>
#include <QtCore>
#include <QThread>
#include <QCustomPlot/customplot.h>

class DuThread : public QThread
{
    Q_OBJECT
public:
    explicit DuThread(QCustomPlot *pCustomPlot,QObject *parent = nullptr);
public slots:
    void pushButtonSaveIMG();
signals:

protected:
    void run() override;
private:
    QCustomPlot *duCustomPlot;
};

#endif // DUTHREAD_H
