/*!
    @file
    @brief Source file describing class OpenGLWidget methods 
*/
#include "OpenGLWidget.hpp"
#include <iostream>

/*!
    @brief Constructor of class

    Initializes class fields and loads data from the settings file
*/
OpenGLWidget::OpenGLWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent)
{
    background_rgba[0] = 255;
    background_rgba[1] = 255;
    background_rgba[2] = 255;
    background_rgba[3] = 255;

    edge_rgb[0] = 0;
    edge_rgb[1] = 0;
    edge_rgb[2] = 0;

    vertex_rgb[0] = 0;
    vertex_rgb[1] = 0;
    vertex_rgb[2] = 0;

    point_size = 1.0f;
    line_type = 0;
    ribs_thickness = 1;
    DisplayTypeVerices = 0;
    parallel_type = false;
    central_type = true;
    displayAxes = true;

    settings_path = QApplication::applicationDirPath() + "/settings.ini";

    load_settings();

    scale_mouse = 1.0f;
    activation = 0;

    current.x = 0;
    current.y = 0;
    current.z = 0;
}

/*!
    @brief Destructor of class
*/
OpenGLWidget::~OpenGLWidget()
{
    if (activation)
        deallocate_memory();
}

/*!
    @brief Allocate memory to arrays
*/
void OpenGLWidget::allocate_memory(){
    carcass = new frame;
    carcass->vertices = new matrix_t;
}

/*!
    @brief Deallocate memory
*/
void OpenGLWidget::deallocate_memory(){

    remove_matrix(carcass->vertices);
    delete carcass->vertices;

    free(carcass->indexes);

    delete carcass;

    delete[] index_vertices;
    delete[] vertices;
    
    delete[] color_vertices;
    delete[] color_edges;
}

/*!
    @brief Load obj file

    Allocates memory, reads vertices and polygons, and then centers and scales the model
*/   
void OpenGLWidget::load_obj_file(char *filename)
{

    if (activation)
    {
        deallocate_memory();
        activation = 0;
    }

    if(!activation)
    {      
        allocate_memory();
        activation = 1;
    }

    int code = parser(filename, carcass);

    if (code != -2)
        centering_and_decrising();
    
    if(code == -2)
    {
        activation = 0;
        delete carcass->vertices;
        delete carcass;
        throw std::runtime_error("Error opening file");
    }
}

/*!
    @brief Scale model

    Calculates the scalability factor and uses affine transformations 
    to change the size of the model
*/
void OpenGLWidget::scale(double new_value)
{
    double scale = new_value / scale_num;

    if (scale > 0 && !std::isnan(scale) && !std::isinf(scale))
    {
        scale_num = new_value;

        affine_scaling(carcass->vertices, scale, &current);

        load_vertices();
        updraw();
    }
}

/*!
    @brief Rotate model

    Calls the affine transformation function to rotate the model
*/
void OpenGLWidget::rotate(int axis, float value)
{
    if( !std::isnan(value) && !std::isinf(value) ){

        if(axis >= 0 && axis <= 2){

            affine_rotation(carcass->vertices, axis, value, &current);

            load_vertices();
            updraw();
        }
    }
}

/*!
    @brief Move model

    Сalls an affine transformation function
    to move a model along a specified axis
*/
void OpenGLWidget::move(int axis, float value)
{   
    if( !std::isnan(value) && !std::isinf(value) ){
        
        if(axis >=0 && axis <= 2){

            affine_move(carcass->vertices, axis, value, &current);

            load_vertices();

            updraw();   
        }
    }
}

/*!
    @brief Centering and decrising the model

    The function is executed only once immediately after loading the model data
*/
void OpenGLWidget::centering_and_decrising()
{       
    std::cout << "maxx = " << carcass->max_points.x << " minx = " << carcass->min_points.x << std::endl;
    std::cout << "maxy = " << carcass->max_points.y << " miny = " << carcass->min_points.y << std::endl;
    std::cout << "maxz = " << carcass->max_points.z << " minz = " << carcass->min_points.z << std::endl;

    double x_center = (carcass->max_points.x + carcass->min_points.x) / 2.0;
    double y_center = (carcass->max_points.y + carcass->min_points.y) / 2.0;
    double z_center = (carcass->max_points.z + carcass->min_points.z) / 2.0;

    std::cout << x_center << " " << y_center << " " << z_center << std::endl;

    current.x = 0;
    current.y = 0; 
    current.z = 0;

////////////////////////////////////
    double x = carcass->max_points.x - carcass->min_points.x;
    double y = carcass->max_points.y - carcass->min_points.y;
    double z = carcass->max_points.z - carcass->min_points.z;

    double nums[3] = {x, y, z};

    double max_number = max_num(nums, 3);

    std::cout << "max_number = " << max_number << std::endl;

    scale_num = 0.5;
    double scale = (scale_num - (scale_num * (-1))) / max_number;

    std::cout << "scale = " << scale << std::endl;

    for (int i = 0; i < carcass->counter_v; i++)
    {
        carcass->vertices->matrix[i][0] = (carcass->vertices->matrix[i][0] - x_center) * scale;
        carcass->vertices->matrix[i][1] = (carcass->vertices->matrix[i][1] - y_center) * scale;
        carcass->vertices->matrix[i][2] = (carcass->vertices->matrix[i][2] - z_center) * scale;
    }
    
    FillingRenderBuffers();
}

/*!
    @brief Load vertices and faces in to arrays

    The function is executed only once after centering and scaling
    the model. Loads vertex coordinates, their indices, colors of vertices, edges into arrays
*/
void OpenGLWidget::FillingRenderBuffers()
{   
    int size = carcass->counter_v * 3;

    index_vertices = new unsigned[carcass->counter_v];
    vertices = new float[size];
    color_vertices = new float[size];

    float r = vertex_rgb[0] / 256.0f, g = vertex_rgb[1] / 256.0f, b = vertex_rgb[2] / 256.0f;
    for (int i = 0, j = 0; i < size; i += 3, j++)
    {
        vertices[i] = carcass->vertices->matrix[j][0];
        vertices[i + 1] = carcass->vertices->matrix[j][1];
        vertices[i + 2] = carcass->vertices->matrix[j][2];

        index_vertices[j] = j;
        
        /////////////////////////
        color_vertices[i] = r;
        color_vertices[i + 1] = g;
        color_vertices[i + 2] = b;
        /////////////////////////
    }

    color_edges = new float[carcass->counter_f * 3];

    load_edges_color();

    updraw();
} 

/*!
    @brief Load edges color in to array
*/
void OpenGLWidget::load_edges_color()
{

    float r = edge_rgb[0] / 256.0f, g = edge_rgb[1] / 256.0f, b = edge_rgb[2] / 256.0f;

    for (int i = 0, j = 0; i < carcass->counter_f; i++, j += 3)
    {
        color_edges[j] = r;
        color_edges[j + 1] = g;
        color_edges[j + 2] = b;
    }
}

/*!
    @brief Load vertices color in to array
*/
void OpenGLWidget::load_vertices_color()
{

    float r = vertex_rgb[0] / 256.0f, g = vertex_rgb[1] / 256.0f, b = vertex_rgb[2] / 256.0f;

    for (int i = 0, j = 0; i < carcass->counter_v; i++, j += 3)
    {
        color_vertices[j] = r;
        color_vertices[j + 1] = g;
        color_vertices[j + 2] = b;
    }
}

/*!
    @brief Load vertices to array
*/
void OpenGLWidget::load_vertices()
{
    int size = carcass->counter_v * 3;

    for (int i = 0, j = 0; i < size; i += 3, j++)
    {
        vertices[i] = carcass->vertices->matrix[j][0];
        vertices[i + 1] = carcass->vertices->matrix[j][1];
        vertices[i + 2] = carcass->vertices->matrix[j][2];
    }
}

/*!
    @brief Initialization of OpenGL

    Determines the order in which objects are drawn based on their depth.
*/
void OpenGLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
}

/*!
    @brief Resize OpenGL widget

    Sets the output area for OpenGL. 
    Sets the current matrix as the projection matrix. 
    Loads the identity matrix into the current matrix.
*/
void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

/*!
    @brief Set settings model

    sets the background color. 
    Clears the color buffer and depth buffer. 
    Sets the display type of the model.
    Line type and width. 
    Rotate and zoom functions using the mouse.
*/
void OpenGLWidget::paintGL()
{
    ////////////////////// Background ////////////////////////////////////
    glClearColor(background_rgba[0] / 256.0f, background_rgba[1] / 256.0f,
                 background_rgba[2] / 256.0f, background_rgba[3] / 256.0f);
    //////////////////////////////////////////////////////////////////////

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (central_type)
        glFrustum(-1, 1, -1, 1, 1, 5);

    if (parallel_type)
        glOrtho(-1, 1, -1, 1, 1, 5);

    glTranslatef(0, 0, -2);

    if (line_type)
    {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(4, 0xAAAA);
    }
    else
        glDisable(GL_LINE_STIPPLE);

    glLineWidth(ribs_thickness);

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glScalef(scale_mouse, scale_mouse, scale_mouse);


    if(activation)
        draw_model();
}

/*!
    @brief Draw model

    Renders arrays of vertex indices, edge colors, 
    then vertex colors and a vertex array. 
    Set the type of display of points and their size
*/
void OpenGLWidget::draw_model()
{   
    std::cout << "vertices count = " << carcass->counter_v << std::endl;
    for(int i = 0; i < carcass->counter_v * 3; i++)
        std::cout << vertices[i] << " " ;
    std::cout << std::endl;
    std::cout << std::endl;

    for(int i = 0; i < carcass->counter_v ; i++)
        std::cout << index_vertices[i] << " " ;
    std::cout << std::endl;
    std::cout << std::endl;

    for(int i = 0; i < carcass->counter_indexes; i++)
        std::cout << carcass->indexes[i] << " " ;
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "///////////////////////////////////////" << std::endl;
    ////////////////////////////////////////////////////////////////////////

    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glPointSize(point_size);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // Установка массива цветов для ребер
        glColorPointer(3, GL_FLOAT, 0, color_edges);

    // Отрисовка ребер
          glDrawElements(GL_LINES, carcass->counter_indexes,
                         GL_UNSIGNED_INT, carcass->indexes);
    
    if(DisplayTypeVerices == Circle){
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    }

    if(DisplayTypeVerices != None){

    // Установка массива цветов для вершин
        glColorPointer(3, GL_FLOAT, 0, color_vertices);

    // Отрисовка вершин
        glDrawElements(GL_POINTS, carcass->counter_v, 
                       GL_UNSIGNED_INT, index_vertices);
    }

    if(DisplayTypeVerices == Circle){
        glDisable(GL_BLEND);
        glDisable(GL_POINT_SMOOTH);
    }

    // Axis
    if(displayAxes){

        GLfloat vertices_axis[] = {
        0.0f, 0.0f, 0.0f,  // Начало
        1.5f, 0.0f, 0.0f,  // Конец X
        0.0f, 0.0f, 0.0f,  // Начало
        0.0f, 1.5f, 0.0f,  // Конец Y
        0.0f, 0.0f, 0.0f,  // Начало
        0.0f, 0.0f, 1.5f   // Конец Z
        };

        GLfloat colors_axis[] = {
            1.0f, 0.0f, 0.0f,  // X
            1.0f, 0.0f, 0.0f, 
            0.0f, 1.0f, 0.0f,  // Y
            0.0f, 1.0f, 0.0f, 
            0.0f, 0.0f, 1.0f,  // Z
            0.0f, 0.0f, 1.0f
        };

        GLuint indices_axis[] = {0, 1, 1, 0, 
                                 2, 3, 3, 2, 
                                 4, 5, 5, 4
                                }; 
        glLineWidth(1);

        glDisable(GL_LINE_STIPPLE);
        glVertexPointer(3, GL_FLOAT, 0, vertices_axis);
        glColorPointer(3, GL_FLOAT, 0, colors_axis);
        glDrawElements(GL_LINES, 12, GL_UNSIGNED_INT, indices_axis);

        glLineWidth(ribs_thickness);
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

/*!
    @brief Redraw model

    Calling the function update to redraw
*/
void OpenGLWidget::updraw()
{
    QOpenGLWidget::update();
}

/*!
    @brief Set point size
    @param value value
*/
void OpenGLWidget::set_point_size(int value){

    if( value >= 0){

        point_size = value;
        save_settings();
        updraw();
    }
}

/*!
    @brief Set rib thickness
    @param value new value
*/
void OpenGLWidget::set_ribs_thickness(int value){

    if (value >= 0){

        ribs_thickness = value;
        save_settings();
        updraw();
    }
}

/*!
    @brief Set parallel projection
    @param value value
*/
void OpenGLWidget::set_parallel_projection(bool value){

    parallel_type = value;

    save_settings();

    updraw();    
}

/*!
    @brief Set central projection
    @param value value
*/
void OpenGLWidget::set_central_projection(bool value){

    central_type = value;

    save_settings();

    updraw(); 
}

/*!
    @brief Set line type
*/
void OpenGLWidget::set_line_type(bool value)
{
    line_type = value;

    save_settings();

    updraw();
}

/*!
    @brief Change the display type of the points
    @param value new value
*/
void OpenGLWidget::set_the_display_of_points(int value){

    if ( value >= 0 && value <= 3 ){
        
        DisplayTypeVerices = value;

        save_settings();
        updraw();
    }
}

/*!
    @brief Mouse press event
    @param mo Mouse press event

    Sets the mouse position
*/
void OpenGLWidget::mousePressEvent(QMouseEvent *mo)
{
    mPos = mo->pos();
}

/*!
    @brief Mouse move event
    @param mo Mouse move event

    Sets the mouse move
*/  
void OpenGLWidget::mouseMoveEvent(QMouseEvent *mo)
{
    xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
    yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
    updraw();
}

/*!
    @brief Change scale model by wheel
    @param factor Scale factor
*/
void OpenGLWidget::changeScale(float factor)
{
    scale_mouse *= factor;
    updraw(); // Инициирование перерисовки виджета OpenGL
}

/*!
    @brief Mouse wheel event
*/
void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
    // Получить значение прокрутки колесика мыши
    int delta = event->angleDelta().y();

    // Определить множитель масштабирования на основе направления прокрутки
    float scaleFactor = 1.0f + 0.1f * (delta > 0 ? 1 : -1);

    // Изменить масштаб сцены
    changeScale(scaleFactor);
}

/*!
    @brief Update background color

    Changes the class field responsible for the background color.
    Saves the value in settings.
*/
void OpenGLWidget::set_background(int red, int green, int blue, int alpha)
{

    if (red >= 0 && green >= 0 && blue >= 0 && alpha >= 0){

        background_rgba[0] = red;
        background_rgba[1] = green;
        background_rgba[2] = blue;
        background_rgba[3] = alpha;

        save_settings();

        updraw();
    }
}

/*!
    @brief Update edges color

    Changes the class field responsible for the edges color.
    Saves the value in settings.
*/
void OpenGLWidget::set_edges_color(int red, int green, int blue, int alpha)
{
    Q_UNUSED(alpha);

    if (red >= 0 && green >= 0 && blue >= 0 && alpha >= 0){

        edge_rgb[0] = red;
        edge_rgb[1] = green;
        edge_rgb[2] = blue;

        if(activation){

            load_edges_color();

            save_settings();

            updraw();
        }
    }
}

/*!
    @brief Update vertices color

    Changes the class field responsible for the vertixes color.
    Saves the value in settings.
*/
void OpenGLWidget::set_vertices_color(int red, int green, int blue, int alpha)
{   
    Q_UNUSED(alpha);
    
    if (red >= 0 && green >= 0 && blue >= 0 && alpha >= 0){

        vertex_rgb[0] = red;
        vertex_rgb[1] = green;
        vertex_rgb[2] = blue;

        if(activation){
            
            load_vertices_color();

            save_settings();

            updraw();
        }
    }
}

/*!
        @brief Set axes display
    */
void OpenGLWidget::set_display_axes(bool value){

    displayAxes = value;

    updraw();
}

/*!
    @brief Getter for parrallel type
*/
bool OpenGLWidget::get_parallel_type(){

    return parallel_type ;
}   

/*!
    @brief Getter for central type
*/
bool OpenGLWidget::get_central_type(){

    return central_type ;
}

/*!
    @brief Getter for line type
*/
int OpenGLWidget::get_line_type(){

    return line_type ;
}

/*!
    @brief Getter for ribs thickness
*/
int OpenGLWidget::get_ribs_thickness(){

    return ribs_thickness ;
}

/*!
    @brief Getter for point size
*/
int OpenGLWidget::get_point_size(){

    return point_size ;
}

/*!
     @brief Getter for points display type
*/
int OpenGLWidget::get_points_display_type(){

    return DisplayTypeVerices ;
}

/*!
    @brief Пetter for application status
*/
bool OpenGLWidget::get_activity(){

    return activation ;
}

/*!
    @brief Getter for number of vertices
*/
int OpenGLWidget::get_number_of_vertices(){

    return carcass->counter_v ;
}

/*!
    @brief Getter for number of faces
*/
int OpenGLWidget::get_number_of_faces(){

    return carcass->counter_f ;
}

/*! 
    @brief Save settings

    Saves the settings in the settings file
*/
void OpenGLWidget::save_settings()
{
    QSettings settings(settings_path, QSettings::NativeFormat);

    settings.setValue("background_r", background_rgba[0]);
    settings.setValue("background_g", background_rgba[1]);
    settings.setValue("background_b", background_rgba[2]);
    settings.setValue("background_a", background_rgba[3]);

    settings.setValue("edge_r", edge_rgb[0]);
    settings.setValue("edge_g", edge_rgb[1]);
    settings.setValue("edge_b", edge_rgb[2]);

    settings.setValue("vertex_r", vertex_rgb[0]);
    settings.setValue("vertex_g", vertex_rgb[1]);
    settings.setValue("vertex_b", vertex_rgb[2]);

    settings.setValue("line_type", line_type);

    settings.setValue("ribs_thickness", ribs_thickness);

    settings.setValue("central_type", central_type);
    settings.setValue("parallel_type", parallel_type);

    settings.setValue("point_size", point_size);

    settings.setValue("display_type_points", DisplayTypeVerices);
}

/*!
    @brief Load settings

    Loads the settings from the settings file
*/
void OpenGLWidget::load_settings()
{
    QSettings settings(settings_path, QSettings::NativeFormat);

    if (settings.contains("background_r"))
        background_rgba[0] = settings.value("background_r", 0).toInt();

    if (settings.contains("background_g"))
        background_rgba[1] = settings.value("background_g", 0).toInt();

    if (settings.contains("background_b"))
        background_rgba[2] = settings.value("background_b", 0).toInt();

    if (settings.contains("background_a"))
        background_rgba[3] = settings.value("background_a", 0).toInt();

    if (settings.contains("edge_r"))
        edge_rgb[0] = settings.value("edge_r", 0).toInt();

    if (settings.contains("edge_g"))
        edge_rgb[1] = settings.value("edge_g", 0).toInt();

    if (settings.contains("edge_b"))
        edge_rgb[2] = settings.value("edge_b", 0).toInt();

    if (settings.contains("line_type"))
        line_type = settings.value("line_type", 0).toInt();

    if (settings.contains("ribs_thickness"))
        ribs_thickness = settings.value("ribs_thickness", 1).toInt();

    if (settings.contains("central_type"))
        central_type = settings.value("central_type", 0).toBool();

    if (settings.contains("parallel_type"))
        parallel_type = settings.value("parallel_type", 0).toBool();

    if (settings.contains("vertex_r"))
        vertex_rgb[0] = settings.value("vertex_r", 0).toInt();

    if (settings.contains("vertex_g"))
        vertex_rgb[1] = settings.value("vertex_g", 0).toInt();

    if (settings.contains("vertex_b"))
        vertex_rgb[2] = settings.value("vertex_b", 0).toInt();

    if (settings.contains("point_size"))
        point_size = settings.value("point_size", 0).toFloat();

    if (settings.contains("display_type_points"))
        DisplayTypeVerices = settings.value("display_type", 0).toInt();
}