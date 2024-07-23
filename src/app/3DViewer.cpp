/*!
    @file
    @brief Source file describing class App3DViewer methods
*/
#include "3DViewer.hpp"

/*!
    @brief Load model from obj file

    Checks whether the file can be opened and 
    calls the obj file reading method from the OpenGLWidget class,
    Then fills in information about the loaded model.
*/
int App3DViewer::load_model()
{
    memset(model_name, 0, 100);
    int code = open_file();

    if(code != -1){
        old_m_x = -100;
        old_m_y = -100;
        old_m_z = -100;

        old_Rx = 0;
        old_Ry = 0;
        old_Rz = 0;

        slider_x->setValue(0);
        slider_y->setValue(0);
        slider_z->setValue(0);

        slider_sc->setValue(5);

        slider_xR->setValue(0);
        slider_yR->setValue(0);
        slider_zR->setValue(0);

        int vertices = 0, faces = 0;

        char name[150] = {0};

        try {

            glWidget->load_obj_file(model_path);

            vertices = glWidget->get_number_of_vertices();
            faces = glWidget->get_number_of_faces();

            strcpy(name, model_name);

        } catch (const std::runtime_error& e) {
            
            vertices = 0;
            faces = 0;

            strcpy(name, "absent");
            
        }

        char buffer[230] = {0};
        sprintf(buffer, "Model: %s\nVertices: %d\nFaces: %d", name, vertices, faces);
                                    
        textEdit->setText(QString::fromUtf8(buffer));
    }
    
    return code;
}

/*!
    @brief Opening a file through QFileDialog
    @sa QFileDialog
*/
int App3DViewer::open_file(){
    int code = 0;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));

    if (fileName != ""){

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            code = -1;

            char buffer[200] = {0};
            sprintf(buffer, "Model: %s\nVertices: 0\nFaces: 0", "Error");
            textEdit->setText(QString::fromUtf8(buffer));

        }else{

            std::string path = fileName.toStdString();

            strcpy(model_path, path.c_str());

            size_t lastSlashIndex = path.find_last_of('/');
            std::string str = path.substr(lastSlashIndex + 1);

            size_t lastDotIndex = path.find_last_of('.');
            std::string extension = path.substr(lastDotIndex + 1);

            if(extension == "obj")
                strcpy(model_name, str.c_str());
            else
                code = -1;

            file.close();
        }
    }else
        code = -1;

    return code;
}

/*!
    @brief Movement of the model along the X axis through the slider
    @param value Displacement value
*/
void App3DViewer::MoveSliderChanged_x(int value){

    if(glWidget->get_activity()){

        SliderProccesing_move(0, &old_m_x, value, 0.1);

        old_m_x = value;
    }
}

/*!
    @brief Movement of the model along the Y axis through the slider
    @param value Displacement value
*/
void App3DViewer::MoveSliderChanged_y(int value){

    if(glWidget->get_activity()){

        SliderProccesing_move(1, &old_m_y, value, 0.2);

        old_m_y = value;
    }
}

/*!
    @brief Movement of the model along the Z axis through the slider
    @param value Displacement value
*/
void App3DViewer::MoveSliderChanged_z(int value){

    if(glWidget->get_activity()){

        SliderProccesing_move(2, &old_m_z, value, 0.1);

        old_m_z = value;
    }
}

/*!
    @brief Motion value handler
    @param index axis
    @param old_value old value
    @param value new value
    @param coef coefficient
*/
void App3DViewer::SliderProccesing_move(int index, int *old_value ,int value, float coef){
    
    float diff = value - *old_value;

    if (*old_value == -100)
        glWidget->move(index, coef * value);
    else
        glWidget->move(index, coef * diff);

    *old_value = value;
}

/*!
    @brief Scaling of the model through the slider
    @param value Scaling value
*/
void App3DViewer::ScalingSliderChanged(int value){

    if(glWidget->get_activity())
        glWidget->scale(value/10.0);
}

/*!
    @brief Rotation of the model along the X axis through the sliders
    @param value Rotation value
*/
void App3DViewer::RotationSliderChanged_x(int value){

    if(glWidget->get_activity()){

        int da = value - old_Rx;

        glWidget->rotate(0, da);

        old_Rx = value;
    }
    value_x_label->setText(QString::number(value));
}

/*!
    @brief Rotation of the model along the Y axis through the sliders
    @param value Rotation value
*/
void App3DViewer::RotationSliderChanged_y(int value){

    if(glWidget->get_activity()){

        int da = value - old_Ry;

        glWidget->rotate(1, da );

        old_Ry = value;
    }
    value_y_label->setText(QString::number(value));
}

/*!
    @brief Rotation of the model along the Z axis through the sliders
    @param value Rotation value
*/
void App3DViewer::RotationSliderChanged_z(int value){

    if(glWidget->get_activity()){

        int  da = value - old_Rz;
        
        glWidget->rotate(2, da );

        old_Rz = value;
    }
    value_z_label->setText(QString::number(value));
}

/*!
    @brief Selecting the line type
*/
void App3DViewer::LineTypeButtonClicked(){

    bool value = LineTypeButton->isChecked();

    LineTypeButton->setText( value ? "Dotted" : "Solid");

    LineTypeButton->setStyleSheet( value ? LineButtonStyleDotted : LineButtonStyleSolid );

    glWidget->set_line_type(value);
}

/*!
    @brief Make a screenshot
*/
void App3DViewer::make_screenshot(){

    QScreen *screen;
    QPixmap qpx_pixmap;

    screen = QGuiApplication::primaryScreen();

    qpx_pixmap = screen->grabWindow(0, glWidget->mapToGlobal(QPoint(0, 0)).x(), glWidget->mapToGlobal(QPoint(0, 0)).y(),
                                glWidget->width(), glWidget->height());
    
    QFileDialog dialog(nullptr, "Save Image", "", "JPEG (*.jpg);;BMP (*.bmp)");

    dialog.setAcceptMode(QFileDialog::AcceptSave);

    if (dialog.exec()) {
        QString filePath = dialog.selectedFiles().first();
        QString extension = QFileInfo(filePath).suffix(); // Получаем расширение файла

        QString selectedFilter = dialog.selectedNameFilter(); // Получаем выбранный фильтр

        if (extension.isEmpty()) {
            selectedFilter = dialog.selectedNameFilter(); // Получаем выбранный фильтр

            if (selectedFilter == "JPEG (*.jpg)")
                filePath += ".jpg";
            else if (selectedFilter == "BMP (*.bmp)")
                filePath += ".bmp";
        }

        qpx_pixmap.save(filePath, nullptr, 100);
    }
}

/*!
    @brief Clicking on the GIF creation buttons

    Start a timer with one millisecond.
*/
void App3DViewer::on_gif_button_clicked(){

    if(glWidget->get_activity()){

        gif_name = QFileDialog::getSaveFileName(this, tr("Save a gif animation"),
                                                "Screen Cast.gif", tr("gif (*.gif)"));

        if (gif_name != "") {
            gif_button->setDisabled(true);
            gif_frame = new QGifImage;
            gif_frame->setDefaultDelay(10);
            
            timer->setInterval(100);
            timer->start();
        }
    }
}

/*!
    @brief Make a GIF
    @sa QTimer
    @sa on_gif_button_clicked()

    Called when the timer started in the on_gif_button_clicked method expires.
    Collects 50 screenshots, the timer stops and a GIF file is created.
*/
void App3DViewer::make_gif(){

    QImage image = glWidget->grabFramebuffer();

    QSize image_size(640, 480);

    QImage scaled_image = image.scaled(image_size);

    gif_frame->addFrame(scaled_image);

    if (frames_counter == 50) {
        timer->stop();
        gif_frame->save(gif_name);
        frames_counter = 0;

        delete gif_frame;
        gif_button->setEnabled(true);
    }

    frames_counter++;
}

/*!
    @brief Key press event handler for exit the application
*/
void App3DViewer::keyPressEvent(QKeyEvent *event){
    
    if (event->key() == Qt::Key_Escape || event->key() == Qt::Key_Q)
        quit();
}

/*!
    @brief App3DViewer::quit
*/
void App3DViewer::quit(){
    delete textEdit;
    delete glWidget;
    QApplication::quit();
}