/*!
    @file
    @brief Header file describing the class for rendering 3D models using opengl
*/
#pragma once

#ifdef __cplusplus

    double max_num(double *arr, int size);

    /// Enumeration of model point display types
    enum DisplayType {
        Square,           //< Square
        Circle,           //< Circle
        None              //< None
    };

    #include <QtOpenGLWidgets>

    #include <GL/gl.h>

extern "C"
{
#endif

    #include "./C_module/C_module.h"

#ifdef __cplusplus
}
#endif

/*!
    @brief Class for rendering 3D models using opengl
*/
class OpenGLWidget : public QOpenGLWidget
{
    //Q_OBJECT

private:

    //! An array storing the indexes vertices
    unsigned int *index_vertices;

    //! Array for storing coordinates vertices
    float *vertices;

    //! An array storing the color for each edge
    float *color_edges;

    //! An array storing the color for each vertex
    float *color_vertices;

    //! Array for storing edges color
    int edge_rgb[3];

    //! Array for storing vertexes color
    int vertex_rgb[3];

    //! Array for storing background color
    int background_rgba[4];

    //! Variable with x rotation value using mouse
    float xRot;
    
    //! Variable with y rotation value using mouse
    float yRot;
    
    //! Variable with z rotation value using mouse
    float zRot;
    
    //! Variable with mouse scaling value
    float scale_mouse;

    //! Variable with scaling value
    double scale_num;

    //! Variable with mouse position
    QPoint mPos;

    //! Path to settings
    QString settings_path;

    //! Carcass model
    frame *carcass;

    //! Render activation status
    bool activation;

    //! Line type
    int line_type;

    //! Ribs thickness
    int ribs_thickness;

    //! Point size
    int point_size;

    //! Display type of vertices
    int DisplayTypeVerices;

    //! Display type of model
    bool parallel_type, central_type;

    //! Axes display
    bool displayAxes;

    xyzPoint current;

public:

    /*!
        @brief Constructor of class
    */
    OpenGLWidget(QWidget *parent);

    /*!
        @brief Destructor of class
    */
    ~OpenGLWidget();

    /*!
        @brief Load obj file
    */    
    void load_obj_file(char *filename);
    
    ////// MUTATORS //////

    /*!
        @brief Rotate model
    */
    void rotate(int axis, float value);

    /*!
        @brief Move model
    */
    void move(int axis, float value);

    /*!
        @brief Scale model
    */
    void scale(double new_value);

    /*!
        @brief Set line type
    */
    void set_line_type(bool value);

    /*!
        @brief Update background color
    */
    void set_background(int red, int green, int blue, int alpha);

    /*!
        @brief Update edges color
    */
    void set_edges_color(int red, int green, int blue, int alpha);

    /*!
        @brief Update vertices color
    */
    void set_vertices_color(int red, int green, int blue, int alpha);

    /*!
        @brief Set parallel projection
        @param value value
    */
    void set_parallel_projection(bool value);

    /*!
        @brief Set central projection
        @param value value
    */
    void set_central_projection(bool value);

    /*!
        @brief Change the display type of the points
        @param value new value
    */
    void set_the_display_of_points(int value);

    /*!
        @brief Set point size
        @param value value
    */
    void set_point_size(int value);

    /*!
        @brief Set rib thickness
        @param value new value
    */
    void set_ribs_thickness(int value);

    /*!
        @brief Set axes display
    */
    void set_display_axes(bool value);


    ////// ACCESSORS //////

    /*!
        @brief Getter for parrallel type
    */
    bool get_parallel_type();

    /*!
        @brief Getter for central type
    */
    bool get_central_type();

    /*!
        @brief Getter for line type
    */
    int get_line_type();

    /*!
        @brief Getter for ribs_thickness
    */
    int get_ribs_thickness();

    /*!
        @brief Getter for point size
    */
    int get_point_size();

    /*!
        @brief Getter for points display type
    */
    int get_points_display_type();

    /*!
        @brief Getter for application status
    */
    bool get_activity();

    /*!
        @brief Getter for number of vertices
    */
    int get_number_of_vertices();

    /*!
        @brief Getter for number of faces
    */
    int get_number_of_faces();

private:

    /*!
        @brief Allocate memory to arrays
    */
    void allocate_memory();

    /*!
        @brief Delete memory
    */
    void deallocate_memory();

    /*!
        @brief Centering and decrising the model
    */
    void centering_and_decrising();

    /*!
        @brief Load vertices and faces in to arrays
    */
    void FillingRenderBuffers();

    /*!
        @brief Load vertices
    */
    void load_vertices();

    /*!
        @brief Load edges color in to array
    */
    void load_edges_color();

    /*!
        @brief Load vertices color in to array
    */
    void load_vertices_color();

    /*!
        @brief Initialization of OpenGL
    */
    void initializeGL() override;

    /*!
        @brief Resize OpenGL widget
    */
    void resizeGL(int w, int h) override;

    /*!
        @brief Set settings model
    */
    void paintGL() override;

    /*!
        @brief Draw model
    */
    void draw_model();

    /*!
        @brief Mouse press event
    */
    void mousePressEvent(QMouseEvent *mo) override;

    /*!
        @brief Mouse move event
    */  
    void mouseMoveEvent(QMouseEvent *mo) override;

    /*!
        @brief Mouse wheel event
    */
    void wheelEvent(QWheelEvent *event) override;

    /*!
        @brief Change scale model by wheel
    */
    void changeScale(float factor);

    /*!
        @brief Redraw model
    */
    void updraw();

    /*! 
        @brief Save settings
    */
    void save_settings();

    /*!
        @brief Load settings
    */
    void load_settings();

public:
};