/*!
    @file
    @brief Source file describing constructor and destructor class App3DViewer
*/
#include "3DViewer.hpp"

/*!
    @brief Constructor of class

    Creates the application interface
*/
App3DViewer::App3DViewer()
{
    setWindowTitle(tr("3DViewer"));
    setGeometry(100, 100, 1100, 600);
    setStyleSheet(FontStyle);

    QGridLayout *grid_main;
    QHBoxLayout *box;
    
    this->create_openGLWidget();
    this->create_grid(&grid_main);
    this->initialize_box(&box);

    box->addWidget(glWidget);
    box->addLayout(grid_main);

    setLayout(box);
}

/*!
    @brief Destructor of class
*/
App3DViewer::~App3DViewer(){
    delete textEdit;
    delete glWidget;
}

/*!
    @brief Painting background
*/
void App3DViewer::paintEvent(QPaintEvent *event ) {

    Q_UNUSED(event);

    QPainter painter(this);

    char path[] = "app/images/background.jpeg";

    painter.drawPixmap(glWidget->width(), 0, width(), height(), QPixmap(path));
}

/*!
    @brief Creating a widget for rendering 3D models
*/
void App3DViewer::create_openGLWidget(){

    glWidget = new OpenGLWidget(this);
    QSizePolicy glWidgetSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    glWidget->setSizePolicy(glWidgetSizePolicy);
}

/*!
    @brief Creating a grid and attaching elements to it
*/
void App3DViewer::create_grid(QGridLayout **grid){

    (*grid) = new QGridLayout;

    (*grid)->setColumnMinimumWidth(1, 200);
    (*grid)->setColumnStretch(1, 0);

    this->add_model_load(*grid);
    this->add_recording_methods( *grid);
    this->add_viewing_methods(*grid);
    this->add_drawing_axes(*grid);
    this->add_movement_along_the_axes(*grid);
    this->add_color_choice(*grid);
    this->line_type_changed_box(*grid);
    this->add_scale_box(*grid);
    this->add_ribs_thickness_box(*grid);
    this->add_point_size_box(*grid);
    this->add_axis_rotations(*grid);
    this->add_quit_button(*grid);
    this->add_methods_for_displaying_points(*grid);
}

/*!
    @brief Initializing the box layout
*/
void App3DViewer::initialize_box(QHBoxLayout **box){

    (*box) = new QHBoxLayout;

    (*box)->setContentsMargins(0, 0, 0, 0);
    (*box)->setSpacing(1);
    (*box)->setAlignment(Qt::AlignTop); 
    (*box)->setStretch(0, 1);
    (*box)->setStretch(1, 1);
}

/*!
    @brief Creating a Model Loader
*/
void App3DViewer::add_model_load(QGridLayout * grid){

    this->create_textEdit();

    QPushButton *button = new QPushButton(tr("Load model"));
    button->setStyleSheet(LoadButtonStyle);
    button->setToolTip("Загрузить модель из obj файла");

    connect(button,&QPushButton::clicked, this, &App3DViewer::load_model);

    QVBoxLayout *box = new QVBoxLayout;

    box->addWidget(textEdit);
    box->addWidget(button);
    box->setSpacing(2);
    box->setContentsMargins(10, 0, 10, 0);

    grid->addLayout(box, 0, 0);
}

/*!
    @brief Creating a Model Information View Panel
*/
void App3DViewer::create_textEdit(){

    textEdit = new QTextEdit;
    textEdit->setStyleSheet(TextEditStyle);

    textEdit->setReadOnly(true);
    textEdit->setMaximumHeight(70);
    textEdit->setAlignment(Qt::AlignCenter);
    textEdit->setText("Model: absent\nVertices: 0\nFaces: 0");
}

/*!
    @brief Adding a photo module or video recordings of models
*/
void App3DViewer::add_recording_methods(QGridLayout * grid){
    
    QPushButton* screen = new QPushButton(tr("Screen"));
    screen->setStyleSheet(ScreenButtonStyle);
    screen->setToolTip("Скриншот модели");

    connect(screen, &QPushButton::clicked, this, &App3DViewer::make_screenshot);

    gif_button = new QPushButton(tr("GIF"));
    gif_button->setStyleSheet(GifButtonStyle);
    gif_button->setToolTip("Запись gif-анимации");

    connect(gif_button, &QPushButton::clicked, this, &App3DViewer::on_gif_button_clicked);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &App3DViewer::make_gif);

    QVBoxLayout * box = new QVBoxLayout;
    box->addWidget(screen);
    box->addWidget(gif_button);
    box->setContentsMargins(15, 0, 10, 0);

    grid->addLayout(box, 0, 1);
}

/*!
    @brief Adding a Model Projection Type Module
*/
void App3DViewer::add_viewing_methods(QGridLayout * grid){
    
    QLabel * parallel = new QLabel(tr("Parallel"));
    parallel->setFixedWidth(64);
    parallel->setStyleSheet(LabelStyle);

    QLabel *choose_projection = new QLabel(tr("<- Projection ->"));
    choose_projection->setFixedWidth(120);
    choose_projection->setAlignment(Qt::AlignCenter);
    choose_projection->setStyleSheet(LabelStyle);
    choose_projection->setToolTip("Изменить тип отображения модели");

    QRadioButton* radio_parallel = new QRadioButton("");
    radio_parallel->setFixedWidth(17);
    radio_parallel->setChecked(glWidget->get_parallel_type());
    QObject::connect(radio_parallel, &QRadioButton::toggled, glWidget, &OpenGLWidget::set_parallel_projection);

    QRadioButton* radio_center = new QRadioButton("Central");
    radio_center->setChecked(glWidget->get_central_type());
    radio_center->setStyleSheet(LabelStyle);

    QObject::connect(radio_center, &QRadioButton::toggled, glWidget, &OpenGLWidget::set_central_projection);

    QButtonGroup* group = new QButtonGroup;
    group->setExclusive(true);
    group->addButton(radio_parallel);
    group->addButton(radio_center);

    QHBoxLayout *box = new QHBoxLayout;
    box->addWidget(parallel);
    box->addWidget(radio_parallel);
    box->addWidget(choose_projection);
    box->addWidget(radio_center);
    box->setAlignment(Qt::AlignCenter);
    box->setContentsMargins(20, 0, 10, 0);

    grid->addLayout(box, 1, 0);
}

/*!
    @brief @brief Adding a Model Motion Module
*/
void App3DViewer::add_drawing_axes(QGridLayout * grid){

    QLabel *label = new QLabel(tr("Axis "));
    label->setFixedWidth(40);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet(LabelStyle);
    label->setToolTip("Отображение осей координат");

    QCheckBox* button = new QCheckBox("");
    button ->setChecked(true);
    button->setStyleSheet(LabelStyle);

    QObject::connect(button, &QCheckBox::stateChanged, glWidget, &OpenGLWidget::set_display_axes);

    QHBoxLayout *box = new QHBoxLayout;
    box->addWidget(label);
    box->addWidget(button);
    box->setAlignment(Qt::AlignCenter);
    box->setContentsMargins(10, 0, 10, 0);

    grid->addLayout(box, 1, 1);
}

/*!
    @brief Adding a Model Motion Module
*/
void App3DViewer::add_movement_along_the_axes(QGridLayout * grid){
    
    slider_data data = { -20, 20, 0 } ;
    void (App3DViewer::*pointerToFunction_x)(int) = &App3DViewer::MoveSliderChanged_x; 
    QHBoxLayout * x_box = this->create_axis_mv_sc_box( "X", &slider_x, data, pointerToFunction_x);
    grid->addLayout(x_box, 2, 0);

    data = { -10, 10, 0 };
    void (App3DViewer::*pointerToFunction_y)(int) = &App3DViewer::MoveSliderChanged_y; 
    QHBoxLayout *y_box = this->create_axis_mv_sc_box("Y", &slider_y, data, pointerToFunction_y);
    grid->addLayout(y_box, 3, 0);

    data = { -10, 10, 0};
    void (App3DViewer::*pointerToFunction_z)(int) = &App3DViewer::MoveSliderChanged_z; 
    QHBoxLayout *z_box = this->create_axis_mv_sc_box("Z", &slider_z, data, pointerToFunction_z);
    grid->addLayout(z_box, 4, 0);
}

/*!
    @brief Add Slider Function
*/
QHBoxLayout * App3DViewer::create_axis_mv_sc_box
(const char * name, QSlider ** slider, slider_data data ,
void (App3DViewer::*pointerToFunction)(int)){

    QLabel *label = new QLabel(tr(name));
    label->setFixedWidth(19);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet(LabelStyle);

    *slider = new QSlider(Qt::Horizontal, this);
    (*slider)->setRange(data.min_value, data.max_value);
    (*slider)->setValue(data.current_value);

    (*slider)->setStyleSheet(MoveSliderStyle);

    connect(*slider, &QSlider::valueChanged, this, pointerToFunction);

    QHBoxLayout *box = new QHBoxLayout;
    box->addWidget(label);
    box->addWidget(*slider);
    box->setContentsMargins(10, 0, 10, 0);

    return box;
}

/*!
    @brief Adding a Model Scalability Module
*/
void App3DViewer::add_scale_box(QGridLayout * grid){
    
    slider_data data = { 1, 30, 5};

    void (App3DViewer::*pointerToFunction_sc)(int) = &App3DViewer::ScalingSliderChanged; 
    
    QHBoxLayout *sc_box = this->create_axis_mv_sc_box("Sc", &slider_sc, data, pointerToFunction_sc);
    grid->addLayout(sc_box, 5, 0);
}

/*!
    @brief Adding a module for changing the color of the background, edges and vertices
*/
void App3DViewer::add_color_choice(QGridLayout * grid){
    
    void (OpenGLWidget::*pointerToFunction_background)(int,int,int,int) = &OpenGLWidget::set_background; 
    QHBoxLayout *background = create_color_picker("Background    " , pointerToFunction_background);
    grid->addLayout(background, 2, 1);


    void (OpenGLWidget::*pointerToFunction_edges)(int,int,int,int) = &OpenGLWidget::set_edges_color; 
    QHBoxLayout *edges = create_color_picker("Edges color     " , pointerToFunction_edges);
    grid->addLayout(edges, 4, 1);


    void (OpenGLWidget::*pointerToFunction_vertices)(int,int,int,int) = &OpenGLWidget::set_vertices_color; 
    QHBoxLayout *vertices = create_color_picker("Vertices color" , pointerToFunction_vertices);
    grid->addLayout(vertices, 6, 1);
}

/*!
    @brief Creating a Color Picker Widget
*/
QHBoxLayout* App3DViewer::create_color_picker(const char * name, void (OpenGLWidget::*pointerToFunction)(int,int,int,int)){
    
    QLabel *label = new QLabel(tr(name));
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet(LabelStyle);

    ColorPicker *color_picker = new ColorPicker(nullptr);
    color_picker->setFixedSize(130, 20);
    color_picker->setStyleSheet("margin-left: 50px;");
    connect(color_picker, &ColorPicker::colorPickerClicked, glWidget, pointerToFunction);

    QHBoxLayout *box = new QHBoxLayout;
    box->setSpacing(3);
    box->addWidget(label);
    box->addWidget(color_picker);
    box->setContentsMargins(10, 0, 10, 0);

    return box;
}

/*!
    @brief Adding a model type change module
*/
void App3DViewer::line_type_changed_box(QGridLayout * grid){

    QLabel *label = new QLabel(tr("Line type"));
    label->setAlignment(Qt::AlignCenter);
    label->setFixedWidth(80);
    label->setStyleSheet(LabelStyle);
    label->setToolTip("Изменение типа отображения линий на сплошной или пунктирный");

    LineTypeButton = new QRadioButton("Solid");
    LineTypeButton->setChecked(glWidget->get_line_type());
    
    if((glWidget->get_line_type()) == 1){
        LineTypeButton->setText("Dotted");
        LineTypeButton->setStyleSheet(LineButtonStyleDotted);
    }else
        LineTypeButton->setStyleSheet(LineButtonStyleSolid);

    connect(LineTypeButton, &QRadioButton::clicked,this, &App3DViewer::LineTypeButtonClicked);

    QHBoxLayout *box = new QHBoxLayout;
    box->addWidget(label);
    box->addWidget(LineTypeButton);   
    box->setContentsMargins(5, 0, 90, 0);

    grid->addLayout(box, 3, 1);
}

/*!
    @brief Adding a module for changing the thickness of ribs
*/
void App3DViewer::add_ribs_thickness_box(QGridLayout * grid){

    void (OpenGLWidget::*pointerToFunction)(int) = &OpenGLWidget::set_ribs_thickness;

    QHBoxLayout* box  = create_box_for_increasing_edges_and_points("Thickness ", &value_thickness, 20 ,&slider_ribs_thickness, pointerToFunction );

    grid->addLayout(box, 5, 1);
}

/*! 
    @brief Adding a Point Size Module
*/
void App3DViewer::add_point_size_box(QGridLayout * grid){
    
    void (OpenGLWidget::*pointerToFunction)(int) = &OpenGLWidget::set_point_size;

    QHBoxLayout* box  = create_box_for_increasing_edges_and_points("Point size ", &value_point_size, 30 ,&slider_point_size, pointerToFunction );

    grid->addLayout(box, 7, 1);
}

/*!
    @brief Add Slider Function
*/
QHBoxLayout* App3DViewer::create_box_for_increasing_edges_and_points(const char * name, QLabel ** value, int max_value, QSlider ** slider, void (OpenGLWidget::*pointerToFunction)(int)){

    // label
    QLabel * label =  new QLabel(tr(name));
    label->setStyleSheet(LabelStyle);

    // value 
    char num[5] = {0};
    sprintf(num, "%d", (name[0] == 'T' ? glWidget->get_ribs_thickness() : glWidget->get_point_size() ));
    *value = new QLabel(num);
    (*value)->setAlignment(Qt::AlignCenter);
    (*value)->setFixedWidth(40);
    (*value)->setStyleSheet(ValueStyle);

    // slider
    *slider = new QSlider(Qt::Horizontal, this);
    (*slider)->setRange(1, max_value); // Установка диапазона значений
    (*slider)->setValue(name[0] == 'T' ? glWidget->get_ribs_thickness() : glWidget->get_point_size());    // Установка начального значения
    (*slider)->setTickPosition(QSlider::TicksBothSides);
    (*slider)->setTickInterval(5);

    QObject::connect(*slider,  &QSlider::valueChanged, [&slider =*slider, &label = *value](){
        label->setText(QString::number(slider->value()));
    });

    connect(*slider, &QSlider::valueChanged, glWidget, pointerToFunction);

    // box
    QHBoxLayout *box = new QHBoxLayout;
    box->setContentsMargins(11, 0, 10, 0);
    box->setSpacing(10);

    box->addWidget(label);
    box->addWidget(*value);
    box->addWidget(*slider);

    return box;
}

/*!
    @brief Adding a Model Rotation Module
*/
void App3DViewer::add_axis_rotations(QGridLayout * grid){
    
    void (App3DViewer::*pointerToFunction_x)(int) = &App3DViewer::RotationSliderChanged_x;

    QHBoxLayout *x_box = this->create_axis_rotation_box("xR", &value_x_label, &slider_xR, pointerToFunction_x);
    grid->addLayout(x_box, 6, 0);


    void (App3DViewer::*pointerToFunction_y)(int) = &App3DViewer::RotationSliderChanged_y;

    QHBoxLayout *y_box = this->create_axis_rotation_box("yR", &value_y_label, &slider_yR, pointerToFunction_y);
    grid->addLayout(y_box, 7, 0);


    void (App3DViewer::*pointerToFunction_z)(int) = &App3DViewer::RotationSliderChanged_z;

    QHBoxLayout *z_box = this->create_axis_rotation_box("zR", &value_z_label, &slider_zR, pointerToFunction_z);
    grid->addLayout(z_box, 8, 0);
}

/*!
    @brief Create axis rotation box create axis rotation box
*/
QHBoxLayout* App3DViewer::create_axis_rotation_box(const char * name, QLabel **value, QSlider ** slider, void (App3DViewer::*pointerToFunction)(int)){

    // label
    QLabel *label = new QLabel(tr(name));
    label->setFixedWidth(21);
    label->setAlignment(Qt::AlignLeft);
    label->setStyleSheet(LabelStyle);

    // value
    *value = new QLabel("0");
    (*value)->setAlignment(Qt::AlignCenter);
    (*value)->setFixedWidth(40);
    (*value)->setStyleSheet(ValueStyle);

    // slider
    *slider = new QSlider(Qt::Horizontal, this);
    (*slider)->setRange(0, 360);
    (*slider)->setValue(0);
    (*slider)->setTickPosition(QSlider::TicksBothSides);
    (*slider)->setTickInterval(90);

    connect(*slider, &QSlider::valueChanged, this, pointerToFunction);

    // increase button
    QPushButton *increaseButton = new QPushButton("+");
    increaseButton->setStyleSheet(IncreaseButtonStyle);

    increaseButton->setFixedWidth(15);

    QObject::connect(increaseButton, &QPushButton::pressed, [&slider = *slider, &label = *value]()
                        {
        int value = slider->value();
        if (value < 360)
            slider->setValue(value + 1);
            
        label->setText(QString::number(slider->value()));
    });

    // decrease button
    QPushButton *decreaseButton = new QPushButton("-");
    decreaseButton->setStyleSheet(DecreaseButtonStyle);

    decreaseButton->setFixedWidth(15);

    QObject::connect(decreaseButton, &QPushButton::clicked, [&slider = *slider, &label = *value]()
                        {
        int value = slider->value();
        if (value > 0)
            slider->setValue(value - 1);
        label->setText(QString::number(slider->value()));
    });

    // box
    QHBoxLayout *box = new QHBoxLayout;

    box->addWidget(label);
    box->addWidget(*value);
    box->addWidget(*slider);
    box->addWidget(increaseButton);
    box->addWidget(decreaseButton);

    box->setContentsMargins(10, 0, 10, 0);

    return box;
}

/*!
    @brief Adding an application exit button
*/
void App3DViewer::add_quit_button(QGridLayout * grid){

    QPushButton *button = new QPushButton(tr("Quit"));
    button->setStyleSheet(QuitButtonStyle);

    connect(button, &QPushButton::clicked, this, &App3DViewer::quit);

    QHBoxLayout *box = new QHBoxLayout;
    box->addWidget(button);
    box->setContentsMargins(40, 0, 40, 0);

    grid->addLayout(box, 9, 0);
}

/*!
    @brief Adding a module for changing the display of points
*/
void App3DViewer::add_methods_for_displaying_points(QGridLayout * grid){

    // label
    QLabel * label = new QLabel(tr("Display type"));
    label->setAlignment(Qt::AlignCenter);
    label->setFixedWidth(100);
    label->setStyleSheet(LabelStyle);
    label->setToolTip("Изменения типа отображения точек");

    // combo box
    QComboBox *comboBox = new QComboBox;

    comboBox->addItem("Square");
    comboBox->addItem("Circle");
    comboBox->addItem("None");
    comboBox->setCurrentIndex(glWidget->get_points_display_type());

    connect(comboBox, &QComboBox::activated, glWidget , &OpenGLWidget::set_the_display_of_points);

    // box
    QHBoxLayout *box = new QHBoxLayout;
    box->setSpacing(3);
    box->addWidget(label);
    box->addWidget(comboBox);
    box->setContentsMargins(8, 0, 10, 0);

    grid->addLayout(box, 8, 1);
}