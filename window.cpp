// window.cpp

#include <QtWidgets>  // Include the necessary Qt Widgets module

#include "window.h"  // Include the window header file
#include "draw.h"    // Include the draw header file

// Constructor
window::window()
{
    drawWindow = new draw;  // Create an instance of the draw class
    setCentralWidget(drawWindow);  // Set the draw widget as the central widget
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowState(Qt::WindowMaximized);

    create_actions();  // Create actions for menu
    create_menu();     // Create menu

    setWindowTitle(tr("DAS"));  // Set window title
    resize(500, 500);           // Set window size
}

// Handle close event
void window::closeEvent(QCloseEvent* event)
{
    event->accept();
}

// Open image file
void window::open()
{
    QString fname = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());  // Get file name using file dialog

    if (!fname.isEmpty())
    {
        drawWindow->open_image(fname);  // Open the image in the draw widget
    }
}

// Save the image
void window::save()
{
    QAction* action = qobject_cast<QAction*>(sender());  // Get the sender action
    QByteArray format = action->data().toByteArray();    // Get the format data from the action
    export_image(format);  // Export the image with the specified format
}

// Choose pen color
void window::penColor()
{
    // Open color dialog to select new color
    QColor newColor = QColorDialog::getColor(drawWindow->penColor());

    if (newColor.isValid())
    {
        drawWindow->setPenColor(newColor);  // Set the new color for the pen
    }
}

// Choose pen width
void window::penWidth()
{
    bool ok;

    // Show input dialog to select new pen width
    int newWidth = QInputDialog::getInt(this, tr("DAS"),
    tr("Select pen width:"), drawWindow->penWidth(), 1, 50, 1, &ok);

    if (ok)
    {
        drawWindow->setPenWidth(newWidth);  // Set the new pen width
    }
}

// Create actions for menu
void window::create_actions()
{
    open_action = new QAction(tr("&Open"), this);
    open_action->setShortcuts(QKeySequence::Open);
    connect(open_action, SIGNAL(triggered()), this, SLOT(open()));

    foreach(QByteArray format, QImageWriter::supportedImageFormats())
    {
        QString format_text = tr("%1...").arg(QString(format).toUpper());
        QAction* action = new QAction(format_text, this);  // Create action for each supported image format
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        save_format.append(action);  // Append the action to the save_format list
    }

    close_action = new QAction(tr("&Exit"), this);
    close_action->setShortcuts(QKeySequence::Close);
    connect(close_action, SIGNAL(triggered()), this, SLOT(close()));

    penColorAct = new QAction(tr("&Pen Color"), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAct = new QAction(tr("Pen &Width"), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    colorFillAct = new QAction(tr("Fill"), this);
    connect(colorFillAct, SIGNAL(triggered()), drawWindow, SLOT(colorFill()));

    addShapeAct = new QAction(tr("Shapes"), this);
    connect(addShapeAct, SIGNAL(triggered()), drawWindow, SLOT(selectShape()));

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    connect(clearScreenAct, SIGNAL(triggered()), drawWindow, SLOT(clearImage()));
}

// Create menu
void window::create_menu()
{
    // File Menu
    file_menu = new QMenu(tr("&File"), this);

    file_menu->addAction(open_action);
    file_menu->addSeparator();

    save_as_menu = new QMenu(tr("&Save As"), this);

    foreach(QAction * action, save_format)
    {
        save_as_menu->addAction(action);  // Add each save action to the save_as_menu
    }

    file_menu->addMenu(save_as_menu);  // Add save_as_menu to the file_menu
    file_menu->addSeparator();

    file_menu->addAction(close_action);

    // Options Menu
    option_menu = new QMenu(tr("&Tools"), this);

    option_menu->addAction(colorFillAct);
    option_menu->addAction(addShapeAct);
    option_menu->addSeparator();

    option_menu->addAction(penColorAct);
    option_menu->addAction(penWidthAct);
    option_menu->addSeparator();

    option_menu->addAction(clearScreenAct);

    // Adding menus to the menubar
    menuBar()->addMenu(file_menu);
    menuBar()->addMenu(option_menu);
}

// Export image with the specified format
bool window::export_image(const QByteArray& format)
{
    QString ini_path = QDir::currentPath() + "/untitled." + format;

    // Get the save file name using file dialog
    QString fname = QFileDialog::getSaveFileName(this, tr("Save As"),
    ini_path, tr("%1 Files (*.%2);; All Files(*)")
    .arg(QString::fromLatin1(format.toUpper()), (QString::fromLatin1(format))));

    if (fname.isEmpty())
    {
        return false;
    }

    else
    {
        return drawWindow->save_image(fname, format.constData());  // Save the image with the specified format
    }
}
