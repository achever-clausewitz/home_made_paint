#include <QtWidgets>

#include "mainwindow.h"
#include "paintingarea.h"

MainWindow::MainWindow()
{
    paintingArea = new PaintingArea;
    setCentralWidget(paintingArea);

    createActions();
    createMenus();
    createToolbars();

    setWindowTitle(tr("Superpaint"));
    resize(500, 500);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //here should be some stuff about maybeSave
    QMessageBox::StandardButton res;
    res = QMessageBox::question(this, QApplication::applicationName(),
                                tr("Wanna save?"),
                                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                QMessageBox::Yes);
    if(res == QMessageBox::No)
    {
        event->accept();
    } else if (res == QMessageBox::Cancel)
    {
        event->ignore();
    } else
    {
        //here will be some saving actions
        event->accept();
    }
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Open file"), QDir::currentPath());
    paintingArea->openImage(fileName);
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

/*void MainWindow::pencilColorChanged()
{
    QColor newColor = QColorDialog::getColor(paintingArea->pencilColor());
    if(newColor.isValid())
        paintingArea->setPencilColor(newColor);
}*/

void MainWindow::pencilColorChanged()
{
    pencilColorAct = qobject_cast<QAction *>(sender());
    colorToolButton->setIcon(pencilColorToolButton(
                                 ":/images/coloricon.png",
                                 qvariant_cast<QColor>(pencilColorAct->data())));
    pencilColorTriggered();
}

void MainWindow::pencilWidthChanged()
{
    pencilWidthAct = qobject_cast<QAction *>(sender());

    pencilWidthTriggered();
}

void MainWindow::pencilColorTriggered()
{

}

void MainWindow::pencilWidthTriggered()
{

}

void MainWindow::createActions()
{
    // Create the action tied to the menu
    openAct = new QAction(tr("&Open..."), this);

    // Define the associated shortcut key
    openAct->setShortcuts(QKeySequence::Open);

    // Tie the action to MainWindow::open()
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    // Get a list of the supported file formats
    // QImageWriter is used to write images to files
    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        // Create an action for each file format
        QAction *action = new QAction(text, this);

        // Set an action for each file format
        action->setData(format);

        // When clicked call MainWindow::save()
        connect(action, SIGNAL(triggered()), this, SLOT(save()));

        // Attach each file format option menu item to Save As
        saveAsActs.append(action);
    }

}

void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);

    menuBar()->addMenu(fileMenu);
}

void MainWindow::createToolbars()
{
    colorToolButton = new QToolButton;
    colorToolButton->setPopupMode(QToolButton::MenuButtonPopup);

    colorAndWidthToolBar = addToolBar(tr("Color&Width"));
    colorAndWidthToolBar->addWidget(colorToolButton);
    colorAndWidthToolBar->addWidget(widthToolButton);
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    // Define path, name and default file type
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    // Get selected file from dialog
    // Add the proper file formats and extensions
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));

    // If no file do nothing
    if (fileName.isEmpty()) {
        return false;
    } else {

        // Call for the file to be saved
        return paintingArea->saveImage(fileName, fileFormat.constData());
    }
}


QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue")
          << tr("yellow");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()), this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor)
            colorMenu->setDefaultAction(action);
    }
    return colorMenu;
}

QIcon MainWindow::pencilColorToolButton(const QString &imageFile, QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}

QIcon MainWindow::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}
