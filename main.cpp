// main.cpp

#include "window.h"  // Include the window header file
#include "draw.h"    // Include the draw header file

#include <QApplication>  // Include the QApplication module

int main(int argc, char *argv[])
{
    QApplication software(argc, argv);  // Create an instance of QApplication

    software.setStyleSheet("QMenuBar {background-color: #f0f6ed; min-width: 30px; min-height: 30px}");

    window digital_art_software;  // Create an instance of the window class
    digital_art_software.show();  // Show the window

    return software.exec();  // Start the event loop and execute the application
}
