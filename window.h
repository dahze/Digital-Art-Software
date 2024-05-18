// window.h

#ifndef WINDOW_H
#define WINDOW_H

#include <QList>        // Include QList for managing lists of objects
#include <QMainWindow>  // Include QMainWindow for creating the main window

class draw;  // Forward declaration of the draw class

class window : public QMainWindow  // Define the window class inheriting from QMainWindow
{
    Q_OBJECT  // Enable Qt's meta-object system

private:
    draw* drawWindow;  // Pointer to the draw window

    void create_actions();  // Helper function to create actions
    void create_menu();  // Helper function to create menus
    bool export_image(const QByteArray& format);  // Helper function to export image in a given format

    QMenu* file_menu;  // Menu for file-related actions
    QMenu* option_menu;  // Menu for options
    QMenu* save_as_menu;  // Menu for saving options

    QAction* open_action;  // Action for opening a file
    QAction* close_action;  // Action for closing the window
    QAction* clearScreenAct;  // Action for clearing the screen

    QAction* penColorAct;  // Action for selecting pen color
    QAction* penWidthAct;  // Action for selecting pen width
    QAction* colorFillAct; // Action for selecting screen fill color
    QAction* addShapeAct; // Action to add a shape

    QList<QAction*> save_format;  // List of actions for saving in different formats

private slots:
    void open();  // Slot for opening a file
    void save();  // Slot for saving a file

    void penColor();  // Slot for selecting pen color
    void penWidth();  // Slot for selecting pen width

protected:
    void closeEvent(QCloseEvent* event) override;  // Handle close event

public:
    window();  // Constructor
};

#endif
