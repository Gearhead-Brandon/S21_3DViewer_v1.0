/*!
    @file
    @brief Header file describing the application class.
*/
#pragma once

#ifdef __cplusplus

    #include "gifmaker/qgifimage.h"

    #include "OpenGLWidget.hpp"
    #include "ColorPicker.hpp"
    #include "Styles/StylesTables.hpp"

    #include <QtGui>
    #include <QtCore>

extern "C"
{
#endif

    #include "./C_module/C_module.h"

#ifdef __cplusplus
}
#endif

/*!
    @brief Class App3DViewer is the main class of the application.
*/
class App3DViewer : public QWidget
{
    typedef struct {
        int min_value;
        int max_value;
        int current_value;
    } slider_data ;

    //Q_OBJECT

public:

    /*!
        @brief Constructor of class
    */
    App3DViewer();
  
private:

    /*!
        @brief Painting background
    */
    void paintEvent(QPaintEvent *event) override;

    /*!
        @brief Creating a widget for rendering 3D models
    */
    void create_openGLWidget();

    /*!
        @brief Initializing the box layout
    */
    void initialize_box(QHBoxLayout ** box);

    /*!
        @brief Creating a grid and attaching elements to it
    */
    void create_grid(QGridLayout ** grid);

    /*!
        @brief Creating a Model Loader
    */
    void add_model_load(QGridLayout * grid);

    /*!
        @brief Creating a Model Information View Panel
    */
    void create_textEdit();

    /*!
        @brief Adding a photo module or video recordings of models
    */
    void add_recording_methods(QGridLayout * grid);

    /*!
        @brief Adding a Model Projection Type Module
    */
    void add_viewing_methods(QGridLayout * grid);

    /*!
        @brief Adding axes drawing selection
    */
    void add_drawing_axes(QGridLayout * grid);

    /*!
        @brief Adding a Model Motion Module
    */
    void add_movement_along_the_axes(QGridLayout * grid);

    /*!
        @brief Add Slider Function
    */
    QHBoxLayout * create_axis_mv_sc_box(const char * name, QSlider ** slider, slider_data data ,void (App3DViewer::*pointerToFunction)(int) );

    /*!
        @brief Adding a module for changing the color of the background, edges and vertices
    */
    void add_color_choice(QGridLayout * grid);

    /*!
        @brief Creating a Color Picker Widget
    */
    QHBoxLayout *create_color_picker(const char * name, void (OpenGLWidget::*pointerToFunction)(int,int,int,int));

    /*!
        @brief Adding a model type change module
    */
    void line_type_changed_box(QGridLayout * grid);

    /*!
        @brief Adding a Model Scalability Module
    */
    void add_scale_box(QGridLayout * grid);

    /*!
        @brief Adding a module for changing the thickness of ribs
    */
    void add_ribs_thickness_box(QGridLayout * grid);

    /*! 
        @brief Adding a Point Size Module
    */
    void add_point_size_box(QGridLayout * grid);

    /*!
        @brief Add Slider Function
    */
    QHBoxLayout* create_box_for_increasing_edges_and_points(const char * name, QLabel ** value, int max_value , QSlider ** slider, void (OpenGLWidget::*pointerToFunction)(int));

    /*!
        @brief Adding a Model Rotation Module
    */
    void add_axis_rotations(QGridLayout * grid);

    /*!
        @brief Create axis rotation box create axis rotation box
    */
    QHBoxLayout* create_axis_rotation_box(const char * name, QLabel **value, QSlider ** slider,void (App3DViewer::*pointerToFunction)(int));

    /*!
        @brief Adding an application exit button
    */
    void add_quit_button(QGridLayout * grid);
    
    /*!
        @brief Adding a module for changing the display of points
    */
    void add_methods_for_displaying_points(QGridLayout * grid);

    /*!
        @brief Destructor of class
    */
    ~App3DViewer();

    /*!
        @brief Load model from obj file
    */
    int load_model();

    /*!
        @brief Opening a file through QFileDialog
        @sa QFileDialog
    */
    int open_file();

    /*!
        @brief Movement of the model along the X axis through the slider
        @param value Displacement value
    */
    void MoveSliderChanged_x(int value);

    /*!
        @brief Movement of the model along the Y axis through the slider
        @param value Displacement value
    */
    void MoveSliderChanged_y(int value);

    /*!
        @brief Movement of the model along the Z axis through the slider
        @param value Displacement value
    */
    void MoveSliderChanged_z(int value);

    /*!
        @brief Motion value handler
        @param index axis
        @param old_value old value
        @param value new value
        @param coef coefficient
    */
    void SliderProccesing_move(int index, int *old_value, int value, float coef);
    
    /*!
        @brief Rotation of the model along the X axis through the sliders
        @param value Rotation value
    */
    void RotationSliderChanged_x(int value);

    /*!
        @brief Rotation of the model along the Y axis through the sliders
        @param value Rotation value
    */
    void RotationSliderChanged_y(int value);

    /*!
        @brief Rotation of the model along the Z axis through the sliders
        @param value Rotation value
    */
    void RotationSliderChanged_z(int value);

    /*!
        @brief Scaling of the model through the slider
        @param value Scaling value
    */
    void ScalingSliderChanged(int value);

    /*!
        @brief Selecting the line type
    */
    void LineTypeButtonClicked();

    /*!
        @brief Make a screenshot
    */
    void make_screenshot();

    /*!
        @brief Clicking on the GIF creation buttons
    */
    void on_gif_button_clicked();

    /*!
        @brief Make a GIF
    */
    void make_gif();

    /*!
        @brief Quit the application
    */
    void quit();

    /*!
        @brief Key press event handler for exit the application
    */
    void keyPressEvent(QKeyEvent *event) override;

private:

    //! Old value of model movement along the X axis
    int old_m_x;

    //! Old value of model movement along the Y axis
    int old_m_y; 

    //! Old value of model movement along the Z axis
    int old_m_z;

    //! Old value of model rotation along the X axis
    int old_Rx;

    //! Old value of model rotation along the Y axis
    int old_Ry;

    //! Old value of model rotation along the Z axis
    int old_Rz;

    //! Model path
    char model_path[230];

    //! Model name
    char model_name[100];

    //! Displaying Model Information
    QTextEdit *textEdit;

    //! Rotation values in degrees along the X axis
    QLabel *value_x_label;

    //! Rotation values in degrees along the Y axis
    QLabel *value_y_label;

    //! Rotation values in degrees along the Z axis
    QLabel *value_z_label;

    //! Value ribs thickness
    QLabel *value_thickness;

    //! Value points size
    QLabel *value_point_size;

    //! Line type radio button
    QRadioButton* LineTypeButton;

    //! OpenGL Widget
    OpenGLWidget *glWidget;

    //! Slider with movement values along the X axis
    QSlider *slider_x;

    //! Slider with movement values along the Y axis 
    QSlider *slider_y;

    //! Slider with movement values along the Z axis
    QSlider *slider_z;

    //! Slider with zoom scale values
    QSlider *slider_sc;

    //! Slider with rotation values along the X axis
    QSlider *slider_xR;

    //! Slider with rotation values along the Y axis
    QSlider *slider_yR;

    //! Slider with rotation values along the Z axis
    QSlider *slider_zR;

    //! Slider with ribs thickness values
    QSlider *slider_ribs_thickness;

    //! Slider with ribs thickness values
    QSlider *slider_point_size;

    //! GIF creation buttons
    QPushButton *gif_button;

    //! GIF name
    QString gif_name;

    //! GIF frame
    QGifImage *gif_frame;

    //! GIF frame counter
    int frames_counter = 0;

    //! Timer for the GIF creation
    QTimer *timer;
};