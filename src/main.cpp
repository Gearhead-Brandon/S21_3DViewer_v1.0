/*!
    @file
    @brief Application launch file
*/
#include "app/3DViewer.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    std::setlocale(LC_NUMERIC, "C");

    App3DViewer *a = new App3DViewer;

    a->show();

    return app.exec();
}