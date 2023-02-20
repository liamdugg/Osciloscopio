#include "crossline.h"
#include "cursorhelper.h"
#include "qcustomplot.h"
#include <QDebug>
#include <QMouseEvent>
CrossLine::CrossLine(QCustomPlot *parentPlot, QCPGraph *targetGraph)
    : QObject(parentPlot)
    , mParentPlot(parentPlot)
    , mHLine(new QCPItemLine(parentPlot))
    , mVLine(new QCPItemLine(parentPlot))
    , mHText(new QCPItemText(parentPlot))
    , mVText(new QCPItemText(parentPlot))
    , mTracer(new QCPItemTracer(parentPlot))
    , mTracerText(new QCPItemText(parentPlot))
    , mTracerArrow(new QCPItemCurve(parentPlot))
    , mTargetGraph(Q_NULLPTR)
    , mKey(0)
    , mValue(0)
{
    const QString layer(QStringLiteral("overlay"));
    const QMargins margins(5, 5, 5, 5);

    targetGraph = targetGraph ? targetGraph : mParentPlot->graph();

    setGraph(targetGraph);
    setLineMode(lmFree);
    mTracer->setInterpolating(true);
    mTracer->setStyle(QCPItemTracer::tsCircle);

    mTracerText->setSelectable(false);
    mTracerText->setPadding(margins);
    mTracerText->position->setParentAnchor(mTracer->position);
    mTracerText->position->setType(QCPItemPosition::ptAbsolute);

    mTracerArrow->start->setParentAnchor(mTracerText->left);
    mTracerArrow->startDir->setParentAnchor(mTracerArrow->start);
    mTracerArrow->end->setParentAnchor(mTracer->position);
    mTracerArrow->endDir->setParentAnchor(mTracerArrow->end);
    mTracerArrow->setHead(QCPLineEnding::esSpikeArrow);
    mTracerArrow->setTail(QCPLineEnding(QCPLineEnding::esBar,
                                        (mTracerText->bottom->pixelPosition().y() -
                                         mTracerText->top->pixelPosition().y()) * 0.85));

    mHLine->start->setType(QCPItemPosition::ptAbsolute);
    mHLine->end->setType(QCPItemPosition::ptAbsolute);
    mVLine->start->setType(QCPItemPosition::ptAbsolute);
    mVLine->end->setType(QCPItemPosition::ptAbsolute);

    mHLine->setLayer(layer);
    mVLine->setLayer(layer);
    mTracer->setLayer(layer);
    mTracerText->setLayer(layer);
    mTracerArrow->setLayer(layer);

    mHText->setPadding(margins);
    mHText->setLayer(layer);
    mVText->setPadding(margins);
    mVText->setLayer(layer);
    mVText->setColor(Qt::red);//
    mHText->setColor(Qt::red);//
    connect(parentPlot, SIGNAL(afterReplot()), this, SLOT(update()));
}

CrossLine::~CrossLine()
{

}

void CrossLine::setLineMode(CrossLine::LineMode mode)
{
    CursorHelper *helper = CursorHelper::instance();

    mTracer->setVisible(mode == lmTracing);
    mTracerText->setVisible(mode == lmTracing);
    mTracerArrow->setVisible(mode == lmTracing);
    mHLine->setSelectable(mode == lmFree);
    mVLine->setSelectable(mode != lmFollowCursor);

    if (mode == lmFollowCursor) {
        connect(mParentPlot, SIGNAL(mouseMove(QMouseEvent*)),
                this, SLOT(onMouseMoved(QMouseEvent*)));

        helper->remove(mHLine);
        helper->remove(mVLine);
    } else {
        disconnect(mParentPlot, SIGNAL(mouseMove(QMouseEvent*)),
                   this, SLOT(onMouseMoved(QMouseEvent*)));

        if (mTargetGraph->keyAxis()->orientation() == Qt::Horizontal) {
            helper->setCursor(mVLine, QCursor(Qt::SizeHorCursor));
            helper->setCursor(mHLine, QCursor(Qt::SizeVerCursor));
        } else {
            helper->setCursor(mVLine, QCursor(Qt::SizeVerCursor));
            helper->setCursor(mHLine, QCursor(Qt::SizeHorCursor));
        }

        if (mode == lmTracing) {
            mTracer->setGraphKey(mKey);
            helper->remove(mHLine);
        }
    }
    mLineMode = mode;
    update();
}

/*!
  Set \a orientation line to show or hide.
  \note Note: The vertical line is always perpendicular to the keyAxis, and the horizontal line perpendicular to the valueAxis.
 */
void CrossLine::setLineVisible(Qt::Orientation orientation, bool visible)
{
    if (mTargetGraph->keyAxis()->orientation() == Qt::Horizontal) {
        QCPItemLine *line = (orientation == Qt::Horizontal ? mHLine : mVLine);
        QCPItemText *text = (orientation == Qt::Horizontal ? mHText : mVText);
        line->setVisible(visible);
        text->setVisible(visible);
    } else {
        QCPItemLine *line = (orientation == Qt::Vertical ? mHLine : mVLine);
        QCPItemText *text = (orientation == Qt::Vertical ? mHText : mVText);
        line->setVisible(visible);
        text->setVisible(visible);
    }
}

bool CrossLine::lineVisible(Qt::Orientation orientation)
{
    if (mTargetGraph->keyAxis()->orientation() == Qt::Horizontal) {
        QCPItemLine *line = (orientation == Qt::Horizontal ? mHLine : mVLine);
        return line->visible();
    } else {
        QCPItemLine *line = (orientation == Qt::Vertical ? mHLine : mVLine);
        return line->visible();
    }
}

/*!
  Set the \a graph which tracer sticks to. And only vertical line can be moved.
  To free the tracer from any tracer, set \a graph to 0.
  Set \a graph to 0 means that horizontal line and vertical line can be moved individually.
 */
void CrossLine::setGraph(QCPGraph *graph)
{
    mTracer->setGraph(graph);
    mTracer->setGraphKey(0);

    mTargetGraph = graph ? graph : (mTargetGraph ? mTargetGraph : mParentPlot->graph());
    if (mTargetGraph->keyAxis()->orientation() == Qt::Horizontal) {
        mHText->position->setParentAnchor(mHLine->start);
        mVText->position->setParentAnchor(mVLine->end);
    } else {
        mHText->position->setParentAnchor(mHLine->end);
        mVText->position->setParentAnchor(mVLine->start);
    }
}

void CrossLine::setupColor(const QColor &color)
{
    mHLine->setPen(QPen(color));
    mVLine->setPen(QPen(color));

    mTracerArrow->setPen(QPen(color));
    mTracerText->setColor(color);

    mVText->setColor(color);
    mHText->setColor(color);
}

void CrossLine::onMouseMoved(QMouseEvent *event)
{
    mTargetGraph->pixelsToCoords(event->localPos(), mKey, mValue);
    update();
}

void CrossLine::onItemMoved(QCPAbstractItem *item, QMouseEvent *event)
{
    if (item == Q_NULLPTR || (item != mVLine && item != mHLine))
        return;

    QCPAxis *keyAxis = mTargetGraph->keyAxis();
    QCPAxis *valueAxis = mTargetGraph->valueAxis();

    QPointF localPos = event->localPos();
    double key, value;

    if (keyAxis->orientation() == Qt::Horizontal) {
        key = keyAxis->pixelToCoord(localPos.x());
        value = valueAxis->pixelToCoord(localPos.y());
    } else {
        key = keyAxis->pixelToCoord(localPos.y());
        value = valueAxis->pixelToCoord(localPos.x());
    }

    if (mLineMode == lmTracing) {
        mTracer->setGraphKey(key);
    } else {
        if (item == mHLine) mValue = value;
        else mKey = key;
    }

    update();
}

void CrossLine::update()
{
    updateTracer();
    updateHLine(mValue);
    updateVLine(mKey);
    // we just want replot individual by use overlay layer
    if (mParentPlot->isVisible() && mParentPlot->layer("overlay")->visible()) // for some cases we need to do this
        mParentPlot->layer("overlay")->replot();
}

void CrossLine::updateTracer()
{
    if (mLineMode != lmTracing)
        return;

    mTracer->updatePosition();
    mKey = mTracer->position->key();
    mValue = mTracer->position->value();

    QRect rect = mTargetGraph->keyAxis()->axisRect()->rect();
    QPointF center = rect.center();
    QPointF pixel = mTracer->position->pixelPosition();

    Qt::Alignment alignment = Qt::AlignTop | Qt::AlignLeft;
    double offset = qMax(rect.width(), rect.height()) / double(8.0);
    double offsetX, offsetY;

    const int endOffset = 10;
    const int endDirOffset = 30;
    const int startDirOffset = 40;

    if (pixel.x() <= center.x()) {
        alignment = Qt::AlignLeft;
        offsetX = offset;
        mTracerArrow->start->setParentAnchor(mTracerText->left);
        mTracerArrow->startDir->setCoords(-startDirOffset, 0);
        mTracerArrow->end->setCoords(endOffset, 0);
        mTracerArrow->endDir->setCoords(endDirOffset, 0);
    } else {
        alignment = Qt::AlignRight;
        offsetX = -offset;
        mTracerArrow->start->setParentAnchor(mTracerText->right);
        mTracerArrow->startDir->setCoords(startDirOffset, 0);
        mTracerArrow->end->setCoords(-endOffset, 0);
        mTracerArrow->endDir->setCoords(-endDirOffset, 0);
    }
    if (pixel.y() <= center.y()) {
        alignment |= Qt::AlignTop;
        offsetY = offset;
        mTracerArrow->end->setCoords(mTracerArrow->end->coords().x(), endOffset);
        mTracerArrow->endDir->setCoords(mTracerArrow->endDir->coords().x(), endDirOffset);
    } else {
        alignment |= Qt::AlignBottom;
        offsetY = -offset;
        mTracerArrow->end->setCoords(mTracerArrow->end->coords().x(), -endOffset);
        mTracerArrow->endDir->setCoords(mTracerArrow->endDir->coords().x(), -endDirOffset);
    }
    mTracerText->position->setCoords(offsetX, offsetY);
    mTracerText->setPositionAlignment(alignment);
    mTracerText->setText(QString("(%1, %2)").arg(mKey, 0, 'f', 2).arg(mValue, 0, 'f', 2));
}

void CrossLine::updateHLine(double value)
{
    QCPAxis *valueAxis = mTargetGraph->valueAxis();
    QRect rect = valueAxis->axisRect()->rect();
    QPointF center = rect.center();

    mHText->setText(QString::number(value, 'f', 2));
    mValue = value;

    value = valueAxis->coordToPixel(value);

    if (valueAxis->orientation() == Qt::Vertical) {
        mHLine->start->setCoords(rect.left(), value);
        mHLine->end->setCoords(rect.right(), value);
        Qt::Alignment alignment = (value >= center.y() ? Qt::AlignBottom : Qt::AlignTop) | Qt::AlignLeft;
        mHText->setPositionAlignment(alignment);
    } else {
        mHLine->start->setCoords(value, rect.top());
        mHLine->end->setCoords(value, rect.bottom());
        Qt::Alignment alignment = (value >= center.x() ? Qt::AlignRight : Qt::AlignLeft) | Qt::AlignBottom;
        mHText->setPositionAlignment(alignment);
    }
}

void CrossLine::updateVLine(double key)
{
    QCPAxis *keyAxis = mTargetGraph->keyAxis();
    QRect rect = keyAxis->axisRect()->rect();
    QPointF center = rect.center();

    mVText->setText(QString::number(key, 'f', 3));
    mKey = key;

    key = keyAxis->coordToPixel(key);

    if (keyAxis->orientation() == Qt::Horizontal) {
        mVLine->start->setCoords(key, rect.top());
        mVLine->end->setCoords(key, rect.bottom());
        Qt::Alignment alignment = (key >= center.x() ? Qt::AlignRight : Qt::AlignLeft) | Qt::AlignBottom;
        mVText->setPositionAlignment(alignment);
    } else {
        mVLine->start->setCoords(rect.left(), key);
        mVLine->end->setCoords(rect.right(), key);
        Qt::Alignment alignment = (key >= center.y() ? Qt::AlignBottom : Qt::AlignTop) | Qt::AlignLeft;
        mVText->setPositionAlignment(alignment);
    }
}

void CrossLine::checkBoxUpdateHorizontal(int index)
{
    if(index){
        setLineVisible(Qt::Horizontal, true);
        if( mLineMode == lmTracing){
            mTracerArrow->setVisible(true);
            mTracerText->setVisible(true);
        }
    } else {
        setLineVisible(Qt::Horizontal, false);
        mTracerArrow->setVisible(false);
        mTracerText->setVisible(false);
    }
    mParentPlot->replot();
}

void CrossLine::checkBoxUpdateVertical(int index)
{
    if(index){
        setLineVisible(Qt::Vertical, true);
        if( mLineMode == lmTracing){
            mTracerArrow->setVisible(true);
            mTracerText->setVisible(true);
        }
    } else {
       setLineVisible(Qt::Vertical, false);
       mTracerArrow->setVisible(false);
       mTracerText->setVisible(false);
    }
    mParentPlot->replot();
}
