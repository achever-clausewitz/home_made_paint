#ifndef PAINTINGAREA_H
#define PAINTINGAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class PaintingArea : public QWidget
{
    Q_OBJECT

public:
    PaintingArea(QWidget *parent = 0);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPencilColor(const QColor &newColor);
    void setPencilWidth(int newWidth);

    bool isModified() const { return modified; }
    QColor pencilColor() const { return myPencilColor; }
    int pencilWidth() const { return myPencilWidth; }

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    //void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    //void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool painting;

    QColor myPencilColor;
    int myPencilWidth;

    QImage image; //stores the image being drawn
    QPoint lastPoint;

    //QList<QPoint> drawBuffer;
    //bool drawMode;
};

#endif // PAINTINGAREA_H
