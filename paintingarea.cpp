#include <QtWidgets>
#include "paintingarea.h"

PaintingArea::PaintingArea(QWidget *parent)
    : QWidget(parent)
{
    //drawMode = false;
    modified = false;
    painting = false;
    myPencilColor = Qt::black;
    myPencilWidth = 1;
}

bool PaintingArea::openImage(const QString &fileName)
{
    QImage loadedImage;

    if(!loadedImage.load(fileName))
        return false;

    image = loadedImage;
    modified = true;
    update();
    return true;
}

bool PaintingArea::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage beingSaved;

    if(beingSaved.save(fileName, fileFormat))
    {
        modified = false;
        return true;
    } else return false;
}

void PaintingArea::setPencilColor(const QColor &newColor)
{
    myPencilColor = newColor;
}

void PaintingArea::setPencilWidth(int newWidth)
{
    myPencilWidth = newWidth;
}

void PaintingArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        painting = true;
    }
}

void PaintingArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && painting)
        drawLineTo(event->pos());
}

void PaintingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && painting) {
        drawLineTo(event->pos());
        painting = false;
    }
}

void PaintingArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QRect modifiedRect = event->rect();

    painter.drawImage(modifiedRect, image, modifiedRect);
}

void PaintingArea::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);

    painter.setPen(QPen(myPencilColor, myPencilWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPencilWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                         .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

