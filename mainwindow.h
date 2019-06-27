#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>

class PaintingArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();
    void save();
    void pencilColorChanged();
    void pencilWidthChanged();
    void pencilColorTriggered();
    void pencilWidthTriggered();

private:
    void createActions();
    void createMenus();
    void createToolbars();

    bool maybeSave;
    bool saveFile(const QByteArray &fileFormat);

    PaintingArea *paintingArea;

    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorIcon(QColor color);
    QIcon pencilColorToolButton(const QString &image, QColor color);

    //QToolBar *instrumentToolBar;
    QToolBar *colorAndWidthToolBar;

    QToolButton *colorToolButton;
    QToolButton *widthToolButton;

    //QAction *createAct; //don't remember what this for
    QAction *openAct;
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *pencilColorAct;
    QAction *pencilWidthAct;

    //QAction *printAct;
    //QAction *lineAction;


};

#endif // MAINWINDOW_H
