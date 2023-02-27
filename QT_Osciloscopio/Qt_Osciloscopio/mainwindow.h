#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCustomPlot/SignalData.h>
#include <QCustomPlot/crossline.h>
#include <USB/ThreadUSB.h>
#include <USB/CustomUSB.h>
#include <duthread.h>
#include <QThread>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SignalData;
class CustomUSB;
class ThreadUSB;
class CrossLine;
class DuThread;
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
    void pushButtonConexion();
    void pushButtonMediciones();
    void pushButtonSaveIMG();
    void getMesure();
public slots:
    void actualizarMediciones(SignalData *mediciones); // -> signal mesure(SignalData mediciones)
    void actualizarEstado(bool);
    void setValueDialTime();
private slots:

private:
    Ui::MainWindow  *ui;
    CustomUSB       *pCustomUSB;
    ThreadUSB       *pThreadUSB;
    QTimer          *time;
    DuThread        *pDuThread;
};
#endif // MAINWINDOW_H
