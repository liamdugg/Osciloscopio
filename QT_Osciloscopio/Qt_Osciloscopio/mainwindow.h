#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCustomPlot/SignalData.h>
#include <QCustomPlot/crossline.h>
#include <USB/ThreadUSB.h>
#include <USB/CustomUSB.h>
#include <QThread>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SignalData;
class CustomUSB;
class ThreadUSB;
class CrossLine;
class QTimer;


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void InicializarUSB();
    void initDial();

signals:
    void pushButtonModo(ThreadUSB::Modo mod);
public slots:
    void ComboBoxUpdate(QString Text);
    void setValueDialTime(int value);
    void setValueDialVolt(int value);
    void pushButtonConexion();
    void pushButtonMediciones();
    void getMesure();
public slots:
    void actualizarMediciones(SignalData *mediciones); // -> signal mesure(SignalData mediciones)
    void actualizarEstado(bool);
private:
    Ui::MainWindow  *ui;
    CustomUSB       *pCustomUSB;
    ThreadUSB       *pThreadUSB;
    QTimer          *time;
};
#endif // MAINWINDOW_H
