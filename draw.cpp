// draw.cpp

#include <QtWidgets>  // Include the necessary Qt Widgets module
#include "draw.h"     // Include the draw header file

// Constructor
draw::draw(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);  // Set attribute for static contents

    modified = false;  // Initialize modified flag as false
    drawing = false;   // Initialize drawing flag as false

    myPenColor = Qt::black;  // Set default pen color to black
    myPenWidth = 1;          // Set default pen width to 1
}

// Open an image file
bool draw::open_image(const QString &fname)
{
    QImage loaded_image;

    if (!loaded_image.load(fname))  // Load the image from the file
    {
        return false;
    }

    QSize new_size = loaded_image.size().expandedTo(size());  // Calculate new size
    resizeImage(&loaded_image, new_size);  // Resize the image
    art = loaded_image;  // Update the image

    modified = false;  // Reset modified flag
    update();  // Update the widget

    return true;
}

// Save the image
bool draw::save_image(const QString &fname, const char *format)
{
    QImage stay_visible = art;
    resizeImage(&stay_visible, size());  // Resize the image to fit the widget size

    if (stay_visible.save(fname, format))  // Save the image to the file
    {
        modified = false;  // Reset modified flag
        return true;
    }
    else
    {
        return false;
    }
}

// Set the pen color
void draw::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

// Set the pen width
void draw::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

// Set the fill color
void draw::setColorFill(const QColor &newColor)
{
    myColorFill = newColor;
}

// Clear the image
void draw::clearImage()
{
    art.fill(qRgb(255, 255, 255));  // Fill the image with white color
    modified = true;  // Set modified flag as true
    update();  // Update the widget
}

// Choose fill color
void draw::colorFill()
{
    QMessageBox::StandardButton warning;
    warning = QMessageBox::warning(this, tr("DAS"),
    tr("This tool will clear the screen if used.\n\n"
    "Are you sure you want to proceed?\n"), QMessageBox::Yes | QMessageBox::No);

    if (warning == QMessageBox::Yes)
    {
        // Open color dialog to select new color
        QColor newColor = QColorDialog::getColor(getColorFill());

        // Fill the screen with the selected color
        if (newColor.isValid())
        {
            art.fill(newColor);
            update();
        }
    }
}

// Select the shape as well as its properties
void draw::selectShape()
{
    // List of available shapes
    QStringList shapeList;
    shapeList << "Rectangle" << "Square" << "Diamond" << "Trapezoid" << "Triangle"
              << "Pentagon" << "Hexagon" << "Heptagon" << "Octagon" << "Star";

    // Prompt the user to select a shape from the list
    QString selectedShape = QInputDialog::getItem(this, tr("Select Shape"), tr("Shape:"), shapeList);
    if (selectedShape.isEmpty())
    {
        return;
    }

    bool ok;

    // Prompt the user to enter the height of the shape
    int shapeHeight = QInputDialog::getInt(this, tr("Dimensions"), tr("Enter the height of the shape:"), 100, 1, 1000, 1, &ok);
    if (!ok)
    {
        return;
    }

    // Prompt the user to enter the width of the shape
    int shapeWidth = QInputDialog::getInt(this, tr("Dimensions"), tr("Enter the width of the shape:"), 100, 1, 1000, 1, &ok);
    if (!ok)
    {
        return;
    }

    // List of available positions
    QStringList positionList;
    positionList << "Center" << "Top-Left" << "Top" << "Top-Right"
                 << "Left" << "Right" << "Bottom-Left" << "Bottom"
                 << "Bottom-Right";

    // Prompt the user to select a position for the shape
    QString selectedPosition = QInputDialog::getItem(this, tr("Select Position"), tr("Position:"), positionList);
    if (selectedPosition.isEmpty())
    {
        return;
    }

    if (!selectedShape.isEmpty())
    {
        // Create a polygon to represent the selected shape
        QPolygon shapePolygon;

        // Construct the shape polygon based on the selected shape
        if (selectedShape == "Rectangle")
        {
            shapePolygon << QPoint(0, 0) << QPoint(shapeWidth * 2, 0)
                         << QPoint(shapeWidth * 2, shapeHeight) << QPoint(0, shapeHeight);
        }

        else if (selectedShape == "Square")
        {
            int sideLength = qMin(shapeWidth, shapeHeight);
            shapePolygon << QPoint(0, 0) << QPoint(sideLength, 0)
                         << QPoint(sideLength, sideLength) << QPoint(0, sideLength);
        }

        else if (selectedShape == "Diamond")
        {
            shapePolygon << QPoint(shapeWidth / 2, 0) << QPoint(shapeWidth, shapeHeight / 2)
                         << QPoint(shapeWidth / 2, shapeHeight) << QPoint(0, shapeHeight / 2);
        }

        else if (selectedShape == "Trapezoid")
        {
            shapePolygon << QPoint(0, 0) << QPoint(shapeWidth, 0)
                         << QPoint(shapeWidth - (shapeHeight * 0.2), shapeHeight)
                         << QPoint(shapeHeight * 0.2, shapeHeight);
        }

        else if (selectedShape == "Parallelogram")
        {
            shapePolygon << QPoint(0, 0) << QPoint(shapeWidth, 0)
                         << QPoint(shapeWidth - (shapeHeight * 0.2), shapeHeight)
                         << QPoint(shapeHeight * 0.2, shapeHeight);
        }

        else if (selectedShape == "Triangle")
        {
            shapePolygon << QPoint(shapeWidth / 2, 0) << QPoint(0, shapeHeight)
                         << QPoint(shapeWidth, shapeHeight);
        }

        else if (selectedShape == "Pentagon")
        {
            int centerX = shapeWidth / 2;
            int centerY = shapeHeight / 2;
            int radius = qMin(shapeWidth, shapeHeight) / 2;
            for (int i = 0; i < 5; ++i)
            {
                double angle = 2 * M_PI * i / 5 - M_PI / 2;
                int x = centerX + radius * cos(angle);
                int y = centerY + radius * sin(angle);
                shapePolygon << QPoint(x, y);
            }
        }

        else if (selectedShape == "Hexagon")
        {
            int centerX = shapeWidth / 2;
            int centerY = shapeHeight / 2;
            int radius = qMin(shapeWidth, shapeHeight) / 2;
            for (int i = 0; i < 6; ++i)
            {
                double angle = 2 * M_PI * i / 6;
                int x = centerX + radius * cos(angle);
                int y = centerY + radius * sin(angle);
                shapePolygon << QPoint(x, y);
            }
        }

        else if (selectedShape == "Heptagon")
        {
            int centerX = shapeWidth / 2;
            int centerY = shapeHeight / 2;
            int radius = qMin(shapeWidth, shapeHeight) / 2;
            for (int i = 0; i < 7; ++i)
            {
                double angle = 2 * M_PI * i / 7 - M_PI / 2;
                int x = centerX + radius * cos(angle);
                int y = centerY + radius * sin(angle);
                shapePolygon << QPoint(x, y);
            }
        }

        else if (selectedShape == "Octagon")
        {
            int centerX = shapeWidth / 2;
            int centerY = shapeHeight / 2;
            int radius = qMin(shapeWidth, shapeHeight) / 2;
            for (int i = 0; i < 8; ++i)
            {
                double angle = 2 * M_PI * i / 8;
                int x = centerX + radius * cos(angle);
                int y = centerY + radius * sin(angle);
                shapePolygon << QPoint(x, y);
            }
        }

        else if (selectedShape == "Star")
        {
            int centerX = shapeWidth / 2;
            int centerY = shapeHeight / 2;
            int outerRadius = qMin(shapeWidth, shapeHeight) / 2;
            int innerRadius = outerRadius * 0.5;
            for (int i = 0; i < 5; ++i)
            {
                double outerAngle = 2 * M_PI * i / 5 - M_PI / 2;
                double innerAngle = 2 * M_PI * (i + 0.5) / 5 - M_PI / 2;
                int outerX = centerX + outerRadius * cos(outerAngle);
                int outerY = centerY + outerRadius * sin(outerAngle);
                int innerX = centerX + innerRadius * cos(innerAngle);
                int innerY = centerY + innerRadius * sin(innerAngle);
                shapePolygon << QPoint(outerX, outerY) << QPoint(innerX, innerY);
            }
        }

        QPoint shapePosition;

        // Determine the position of the shape based on the user's selection
        if (selectedPosition == "Top-Left")
        {
            shapePosition = QPoint(0, 0);
        }

        else if (selectedPosition == "Top")
        {
            shapePosition = QPoint((width() - shapeWidth) / 2, 0);
        }

        else if (selectedPosition == "Top-Right")
        {
            shapePosition = QPoint(width() - shapeWidth, 0);
        }

        else if (selectedPosition == "Left")
        {
            shapePosition = QPoint(0, (height() - shapeHeight) / 2);
        }

        else if (selectedPosition == "Right")
        {
            shapePosition = QPoint(width() - shapeWidth, (height() - shapeHeight) / 2);
        }

        else if (selectedPosition == "Bottom-Left")
        {
            shapePosition = QPoint(0, height() - shapeHeight);
        }

        else if (selectedPosition == "Bottom")
        {
            shapePosition = QPoint((width() - shapeWidth) / 2, height() - shapeHeight);
        }

        else if (selectedPosition == "Bottom-Right")
        {
            shapePosition = QPoint(width() - shapeWidth, height() - shapeHeight);
        }

        else
        {
            // Center position (default)
            shapePosition = QPoint((width() - shapeWidth) / 2, (height() - shapeHeight) / 2);
        }

        // Translate the shape polygon based on the selected position
        shapePolygon.translate(shapePosition);

        // Draw the shape on the canvas
        drawShape(shapePolygon);
    }
}

// Draw the selected shape on the canvas
void draw::drawShape(const QPolygon& shapePolygon)
{
    // Create a QPainter object to perform the drawing operations on the canvas
    QPainter painter(&art);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    // Draw the shape polygon using the QPainter object
    painter.drawPolygon(shapePolygon);

    // Set the modified flag to indicate that the canvas has been updated
    modified = true;

    // Update the canvas to reflect the changes
    update();
}

// Handle mouse press event
void draw::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)  // Check if left mouse button is pressed
    {
        lastPoint = event->pos();  // Store the current position as the last point
        drawing = true;  // Set drawing flag as true
    }
}

// Handle mouse move event
void draw::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() && Qt::LeftButton) && drawing)  // Check if left mouse button is pressed and drawing flag is true
    {
        drawLineTo(event->pos());  // Draw a line to the current position
    }
}

// Handle mouse release event
void draw::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing)  // Check if left mouse button is released and drawing flag is true
    {
        drawLineTo(event->pos());  // Draw a line to the current position
        drawing = false;  // Set drawing flag as false
    }
}

// Handle paint event
void draw::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QRect current_rect = event->rect();
    painter.drawImage(current_rect, art, current_rect);  // Draw the image within the current rectangle
}

// Handle resize event
void draw::resizeEvent(QResizeEvent *event)
{
    if (width() > art.width() || height() > art.height())
    {
        int new_width = qMax(width() + 128, art.width());  // Calculate new width
        int new_height = qMax(height() + 128, art.height());  // Calculate new height

        resizeImage(&art, QSize(new_width, new_height));  // Resize the image
        update();  // Update the widget
    }

    QWidget::resizeEvent(event);
}

// Draw a line to the given point
void draw::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&art);

    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    painter.drawLine(lastPoint, endPoint);  // Draw a line from the last point to the given point

    modified = true;  // Set modified flag as true

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));  // Update the widget

    lastPoint = endPoint;  // Update the last point
}

// Resize the image
void draw::resizeImage(QImage *art, const QSize &new_size)
{
    if (art->size() == new_size)
    {
        return;
    }

    QImage new_image(new_size, QImage::Format_RGB32);  // Create a new image with the new size
    new_image.fill(qRgb(255, 255, 255));  // Fill the image with white color

    QPainter painter(&new_image);
    painter.drawImage(QPoint(0,0), *art);  // Draw the old image on the new image
    *art = new_image;  // Update the image
}
