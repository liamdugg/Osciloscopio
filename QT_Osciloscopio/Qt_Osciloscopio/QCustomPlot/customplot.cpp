#include "customplot.h"
#include "cursorhelper.h"
#include "qcustomplot.h"

CustomPlot::CustomPlot(QWidget *parent)
    : QCustomPlot(parent)
{
    setSelectionTolerance(6);
    InitGraph();
    signalData = new SignalData;
}

CustomPlot::~CustomPlot()
{
    CursorHelper::release();
}

void CustomPlot::InitGraph()
{
    QCustomPlot::addGraph(QCustomPlot::xAxis, QCustomPlot::yAxis);
    QCustomPlot::graph()->setPen(QPen(Qt::green));
    QCustomPlot::setBackground(QBrush((QColor(0, 0, 39))));
    QCustomPlot::yAxis->grid()->setPen(QPen(QColor(255, 255, 255, 255), 1, Qt::DotLine));
    QCustomPlot::xAxis->grid()->setPen(QPen(QColor(255, 255, 255, 255), 1, Qt::DotLine));
    QCustomPlot::xAxis->setTickLabelColor(Qt::white);
    QCustomPlot::yAxis->setTickLabelColor(Qt::white);
    QCustomPlot::replot();
}

void CustomPlot::pushButtonAutoEscala()
{
    QCustomPlot::graph()->rescaleAxes();
    QCustomPlot::replot();
}

void CustomPlot::LeerSignal(QVector<double> *dato)
{
    datoADC << *dato;
    dato->clear();
    double value;
    double trigger_point = 0;
    double i = -0.8;
    static bool flag = false;
    double trigger_level =  2048;
    for(int k = 505; k <=1024 ; k++){
        // flanco descendente
        if((datoADC[k-1] < trigger_level ) && (datoADC[k]) > trigger_level ){
            trigger_point = k;
            break;
        }
        if(flag){
            QCustomPlot::graph()->data().data()->remove(i);
        }
    }
    i = -1/640.0 * trigger_point;
    QCustomPlot::graph()->data().data()->clear();
    while(!datoADC.isEmpty()){
        value = (datoADC.takeFirst()-2048)*(3.3/4096.0);
        QCustomPlot::graph()->addData(i,value);
        i +=1/640.0;
    }
    datoADC.clear();
    QCustomPlot::replot();
}

void CustomPlot::LeerMesure(QString dato)
{
    /* Procesamiento de mediciones */
    qDebug() << dato;
    signalData->setFrecuncy(dato);
    emit mesure(signalData); // conectado a: actualizaMediciones
}

void CustomPlot::mousePressEvent(QMouseEvent *event)
{
    QCPAbstractItem *item = itemAt(event->localPos());
    if (item && item->selectable()) {
        item->setSelected(true);
        item->layer()->replot();
    }
    QCustomPlot::mousePressEvent(event);
}

void CustomPlot::mouseReleaseEvent(QMouseEvent *event)
{
    QCustomPlot::mouseReleaseEvent(event);
    foreach (QCPAbstractItem *item, selectedItems()) {
        item->setSelected(false);
        item->layer()->replot();
    }
}

void CustomPlot::mouseMoveEvent(QMouseEvent *event)
{
    QCustomPlot::mouseMoveEvent(event);

    QPointF localPos = event->localPos();
    QCPAbstractItem *item = itemAt(localPos);

    QCPAbstractItem *selectedItem = (selectedItems().isEmpty() ? Q_NULLPTR : selectedItems().at(0));

    // set item cursor
    if (item || selectedItem) {
        QCPAbstractItem *obj = selectedItem ? selectedItem : item;
        QCursor itemCursor = CursorHelper::instance()->cursor(obj);
        if (itemCursor.shape() != cursor().shape())
            setCursor(itemCursor);
    } else {
        if (cursor().shape() != Qt::ArrowCursor)
            unsetCursor();
    }

    if (selectedItem && (event->buttons() & Qt::LeftButton)) {
        Q_EMIT itemMoved(selectedItem, event);
        selectedItem->layer()->replot();
    }
}


QSize CustomPlot::sizeHint() const
{
    return QSize(400, 300);
}
