#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QMessageBox>

void init()
{
    QDir dir("./tasks/");
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            QMessageBox::warning(nullptr, "Błąd", "Nie udało się utworzyć katalogu ./tasks/");
            return;
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    init();

    MainWindow w;
    w.setFixedSize(800, 600);
    w.show();

    return app.exec();
}
