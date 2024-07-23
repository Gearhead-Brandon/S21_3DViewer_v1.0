/*!
    @file
    @brief Header file including class ColorPicker declaration
*/
#pragma once

#include <QtWidgets>

/** 
 * @brief Class ColorPicker allowing you to choose color
*/
class ColorPicker : public QWidget{
    Q_OBJECT

signals:
    /*!
        @brief Signal emitted when color is picked
        @param red Red color
        @param green Green color
        @param blue Blue color
        @param alpha Alpha value
    */
    void colorPickerClicked(int red , int green, int blue, int alpha);

public:

    /*!
        @brief Constructor of class
    */
    ColorPicker(QWidget *parent);

private:

    /*!
        @brief Mouse press event
        @param event Press mouse event
    */
    void mousePressEvent(QMouseEvent *event) override;
    
    /*!
        @brief Event that is called when the widget needs to be redrawn
        @param event Paint event
    */
    void paintEvent(QPaintEvent *event) override ;
    
    /*!
        @brief Pick color by mouse position
        @param pos Mouse position
        @return Color picked
    */
    QColor pickColor(const QPoint &pos);

    /*!
        @brief Create rainbow gradient
        @return Gradient
    */
    QLinearGradient createRainbowGradient();

    //! Color picked by user
    QColor color;
};