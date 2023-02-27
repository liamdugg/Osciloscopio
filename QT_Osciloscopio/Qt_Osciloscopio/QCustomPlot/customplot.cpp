#include "customplot.h"
#include "cursorhelper.h"
#include "qcustomplot.h"

CustomPlot::CustomPlot(QWidget *parent)
    : QCustomPlot(parent)
{
    setSelectionTolerance(6);
    InitGraph();
    signalData = new SignalData;
    connect(signalData, &SignalData::valueChangeDial, this, &CustomPlot::setValueDialTimeMax);
}

CustomPlot::~CustomPlot()
{
    CursorHelper::release();
}

void CustomPlot::InitGraph()
{
    QCPTextElement *title = new QCPTextElement(this);
    title->setTextColor(QColor(32, 178, 170));
    title->setText("Osciloscopio Digital");
    title->setFont(QFont("Comic Sans MS", 14, QFont::Bold));
    QCustomPlot::plotLayout()->insertRow(0);
    QCustomPlot::plotLayout()->addElement(0, 0, title);

    QCustomPlot::xAxis2->setVisible(true);
    QCustomPlot::yAxis2->setVisible(true);
    QCustomPlot::xAxis->setBasePen(QPen(QColor(192, 192, 192)));
    QCustomPlot::yAxis->setBasePen(QPen(QColor(192, 192, 192)));
    QCustomPlot::xAxis2->setBasePen(QPen(QColor(192, 192, 192)));
    QCustomPlot::yAxis2->setBasePen(QPen(QColor(192, 192, 192)));

    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(1);
    QCustomPlot::xAxis->setTickPen(pen);
    QCustomPlot::yAxis->setTickPen(pen);
    QCustomPlot::xAxis2->setTickPen(pen);
    QCustomPlot::yAxis2->setTickPen(pen);

    QCustomPlot::xAxis->setTickLengthIn(15);
    QCustomPlot::xAxis2->setTickLengthIn(15);
    QCustomPlot::yAxis->setTickLengthIn(15);
    QCustomPlot::yAxis2->setTickLengthIn(15);
    QCustomPlot::xAxis->setTickLengthOut(0);
    QCustomPlot::xAxis2->setTickLengthOut(0);
    QCustomPlot::yAxis->setTickLengthOut(0);
    QCustomPlot::yAxis2->setTickLengthOut(0);

    QCustomPlot::xAxis->setSubTickPen(pen);
    QCustomPlot::yAxis->setSubTickPen(pen);
    QCustomPlot::xAxis2->setSubTickPen(pen);
    QCustomPlot::yAxis2->setSubTickPen(pen);

    QCustomPlot::xAxis->setSubTickLengthIn(5);
    QCustomPlot::xAxis2->setSubTickLengthIn(5);
    QCustomPlot::yAxis->setSubTickLengthIn(5);
    QCustomPlot::yAxis2->setSubTickLengthIn(5);
    QCustomPlot::xAxis->setSubTickLengthOut(0);
    QCustomPlot::xAxis2->setSubTickLengthOut(0);
    QCustomPlot::yAxis->setSubTickLengthOut(0);
    QCustomPlot::yAxis2->setSubTickLengthOut(0);

    QCustomPlot::xAxis2->setTickLabels(true);//显示刻度值
    QCustomPlot::xAxis2->setTickLabelSide(QCPAxis::LabelSide::lsInside);//显示在内部
    QCustomPlot::xAxis2->setLabel("Tiempo: [mS]");//轴标签
    QCustomPlot::xAxis2->setLabelColor(QColor(255, 255, 255, 255));
    QCustomPlot::yAxis2->setTickLabels(true);//显示刻度值
    QCustomPlot::yAxis2->setTickLabelSide(QCPAxis::LabelSide::lsInside);//显示在内部
    QCustomPlot::yAxis2->setLabel("Tension: [V]");//轴标签
    QCustomPlot::yAxis2->setLabelColor(QColor(255, 255, 255, 255));

    QCustomPlot::addGraph(QCustomPlot::xAxis, QCustomPlot::yAxis);
    QCustomPlot::graph()->setPen(QPen(Qt::green));
    QCustomPlot::setBackground(QBrush((QColor(0, 0, 39))));
    QCustomPlot::yAxis->grid()->setPen(QPen(QColor(255, 255, 255, 255), 1, Qt::DotLine));
    QCustomPlot::xAxis->grid()->setPen(QPen(QColor(255, 255, 255, 255), 1, Qt::DotLine));
    QCustomPlot::xAxis->setTickLabelColor(Qt::white);
    QCustomPlot::yAxis->setTickLabelColor(Qt::white);
    QCustomPlot::replot();
}

SignalData::samplimngFrecuency CustomPlot::convertirFS(QString s)
{
    if(s.indexOf("FS1",Qt::CaseInsensitive)>= 0)
        return SignalData::fs1;
    if(s.indexOf("FS2",Qt::CaseInsensitive)>= 0)
        return SignalData::fs2;
    if(s.indexOf("FS3",Qt::CaseInsensitive)>= 0)
        return SignalData::fs3;
    if(s.indexOf("FS4",Qt::CaseInsensitive)>= 0)
        return SignalData::fs4;
    if(s.indexOf("FS5",Qt::CaseInsensitive)>= 0)
        return SignalData::fs5;
    if(s.indexOf("FS6",Qt::CaseInsensitive)>= 0)
        return SignalData::fs6;
    if(s.indexOf("FS7",Qt::CaseInsensitive)>= 0)
        return SignalData::fs7;
    return SignalData::fs1;
}

SignalData::scaleAmplitud CustomPlot::convertirScaleFactor(QString s)
{
    if(s.indexOf("G0")>= 0)
        return SignalData::aten_03;
    if(s.indexOf("G1")>= 0)
        return SignalData::aten_05;
    if(s.indexOf("G2")>= 0)
        return SignalData::amp_1;
    if(s.indexOf("G3")>= 0)
        return SignalData::amp_3;
    if(s.indexOf("G4")>= 0)
        return SignalData::amp_5;
    if(s.indexOf("G5")>= 0)
        return SignalData::amp_10;
    if(s.indexOf("G6")>= 0)
        return SignalData::amp_31;
    if(s.indexOf("G7")>= 0)
        return SignalData::amp_50;
    return SignalData::amp_1;
}

QString CustomPlot::convertir(QString s, unidades Unidad)
{
    switch (Unidad) {
    case frecuencia:
        return convertirFrecuencia(s);
        break;
    case tiempo:
        return convertirPerido(s);
        break;
    case Amplitud:
        return convertirAmplitud(s);
    case Vrms:
        return convertirVrms(s);
    default:
        break;
    }
    return QString("xxx.xx");
}

QString CustomPlot::convertirFrecuencia(QString s)
{
    QString x;
    int indexEndK;
    int indexEndH;
    int indexBegin;
    indexBegin = s.indexOf("F");
    indexEndK = s.indexOf("K", indexBegin);
    indexEndH = s.indexOf("Hz", indexBegin);
    if(indexEndK>=0){
        for(int k = indexBegin+1; k<indexEndK; k++)
            x.append(s.data()[k]);
        return ( QString::number(x.toDouble(),'f',2)+" kHz");
    }
    if(indexEndH){
        for(int k = indexBegin+1; k<indexEndH; k++)
            x.append(s.data()[k]);
        return ( QString::number(x.toInt())+" Hz");
    }
    return QString("---");
}

QString CustomPlot::convertirPerido(QString s)
{
    QString x;
    QString y;
    QString z = "---";
    double d;
    int indexEndK;
    int indexEndH;
    x = convertirFrecuencia(s);
    indexEndK = x.indexOf(" KHz",0,Qt::CaseInsensitive);
    indexEndH = x.indexOf(" Hz",0,Qt::CaseInsensitive);
    if(indexEndK>0){
       for(int i=0; i<indexEndK; i++){
           y.append(x.data()[i]);
       }
       d= 1/y.toDouble();
       if(d<0.5){
           d *= 1000.0;
           return (QString::number(d,'f',2)+" uSg");
       } else {
           return (QString::number(d,'f',2)+" mSg");
       }
    }
    if(indexEndH>0){
       for(int i=0; i<indexEndH; i++){
           y.append(x.data()[i]);
       }
       d= 1/y.toDouble()*1000.0;
       return (QString::number(d,'f',2)+" mSg");
    }
    return z;
}

QString CustomPlot::convertirAmplitud(QString s)
{
    QString x;
    int indexEndV;
    int indexEndm;
    int indexBegin;
    indexBegin = s.indexOf("A");
    indexEndV = s.indexOf("VR",indexBegin);
    indexEndm = s.indexOf("mVR",indexBegin);
    if(indexEndm>=0){
        for(int k = indexBegin+1; k<indexEndm; k++)
            x.append(s.data()[k]);
        return ( QString::number(x.toDouble(),'f',2)+" mV");
    } else {
        for(int k = indexBegin+1; k<indexEndV; k++)
            x.append(s.data()[k]);
        return ( QString::number(x.toDouble(),'f',2)+" V");
    }
}

QString CustomPlot::convertirVrms(QString s)
{
    QString x;
    int indexEndV;
    int indexEndm;
    int indexBegin;
    indexBegin = s.indexOf("R");
    indexEndV = s.indexOf("V",indexBegin);
    indexEndm = s.indexOf("m",indexBegin);
    if(indexEndm>=0){
        for(int k = indexBegin+1; k<indexEndm; k++)
            x.append(s.data()[k]);
        return ( QString::number(x.toDouble(),'f',2)+" mV");
    } else {
        for(int k = indexBegin+1; k<indexEndV; k++)
            x.append(s.data()[k]);
        return ( QString::number(x.toDouble(),'f',3)+" V");
    }
}

void CustomPlot::pushButtonAutoEscala()
{
    /*
    QCustomPlot::graph()->rescaleAxes();
    QCustomPlot::replot();
    */
    emit setValueDialTimeMax();
}

void CustomPlot::LeerADC(QVector<double> *dato)
{
    datoADC << *dato;
    dato->clear();
    double value;
    double amplitudPico = 0;
    double trigger_point = 256;
    double i;
    double trigger_level =  2048;
    for(int k = 210; k <=500 ; k++){
        // flanco descendente
        if((datoADC[k-1] < trigger_level ) && (datoADC[k]) > trigger_level ){
            trigger_point = k;
            break;
        }
    }
    i = -signalData->getSamplingFrecuency() * trigger_point;
    QCustomPlot::graph()->data().data()->clear();
    while(!datoADC.isEmpty()){
        value = (datoADC.takeFirst()-2048)*(3.3/4096.0)/signalData->getFactor();
        if(value > amplitudPico){
            amplitudPico = value;
        }
        QCustomPlot::graph()->addData(i,value);
        i +=signalData->getSamplingFrecuency();
    }
    signalData->setAmplitude(QString::number(2*amplitudPico,'f',2)+" Vpp");
    datoADC.clear();
    QCustomPlot::replot();
}

void CustomPlot::LeerMediciones(QString dato)
{
    /* Procesamiento de mediciones */
    signalData->setFrecuncy(convertir(dato,frecuencia));
    signalData->setPeriod(convertir(dato,tiempo));
    signalData->setAmplitude(signalData->getAmplitude());
    signalData->setVrms(convertir(dato,Vrms));
    signalData->setSamplingFrecuency(convertirFS(dato));
    signalData->setScaleFactor(convertirScaleFactor(dato));
    emit setTimeChange(convertirFS(dato));
    emit mesure(signalData); // conectado a: actualizaMediciones
}

void CustomPlot::setValueDialTime(int value)
{
    QCustomPlot::xAxis->setRange((double)(-(signalData->getA()*value+signalData->getB())),
                                 (double)(signalData->getA()*value+signalData->getB()));
    QCustomPlot::replot();
}

void CustomPlot::setValueDialVolt(int value)
{
    double aV = 0.012;
    double bV = 0.006;
    QCustomPlot::yAxis->setRange(-(aV*value+bV), aV*value+bV);
    QCustomPlot::replot();
}

void CustomPlot::setRangeDialGraph()
{

}

void CustomPlot::setValueDialTimeMax()
{
    emit setValueDialTimeMaximiun();
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
