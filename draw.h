// draw.h

#ifndef DRAW_H
#define DRAW_H

#include <QWidget>  // Include the QWidget class for inheritance
#include <QImage>   // Include the QImage class for image manipulation
#include <QColor>   // Include the QColor class for color selection
#include <QPoint>   // Include the QPoint class for storing points

class draw : public QWidget  // Define the draw class inheriting from QWidget
{
    Q_OBJECT  // Enable Qt's meta-object system

private:
    void drawLineTo(const QPoint& endPoint);  // Draw a line to the given point
    void resizeImage(QImage* art, const QSize& new_size);  // Resize the image

    bool modified;  // Flag to track if the image has been modified
    bool drawing;  // Flag to track if the user is currently drawing

    QColor myPenColor;  // Current pen color
    int myPenWidth;  // Current pen width
    QColor myColorFill; // Current fill color

    QImage art;  // Image object
    QPoint lastPoint;  // Last point of the mouse

protected:
    void mousePressEvent(QMouseEvent* event) override;  // Handle mouse press event
    void mouseMoveEvent(QMouseEvent* event) override;   // Handle mouse move event
    void mouseReleaseEvent(QMouseEvent* event) override;  // Handle mouse release event

    void paintEvent(QPaintEvent* event) override;  // Handle paint event

    void resizeEvent(QResizeEvent* event) override;  // Handle resize event

public:
    draw(QWidget* parent = 0);  // Constructor

    bool open_image(const QString& fname);  // Open an image file
    bool save_image(const QString& fname, const char* format);  // Save the image

    void setPenColor(const QColor &newColor);  // Set the pen color
    void setPenWidth(int newWidth);  // Set the pen width
    void setColorFill(const QColor &newColor); // Set the screen fill color

    QColor penColor() const {return myPenColor;}  // Get the current pen color
    int penWidth() const {return myPenWidth;}  // Get the current pen width
    QColor getColorFill() const {return myColorFill;} // Get the screen fill color

    bool modified_check() const;  // Check if the image has been modified

public slots:
    void clearImage();  // Clear the image
    void colorFill(); // Slot for selecting screen fill color
    void selectShape(); // Slot to select a shape
    void drawShape(const QPolygon& shapePolygon); // Slot to draw the selected shape
};

#endif
