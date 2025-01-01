#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QFile>
#include <QMessageBox>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void listFilesWithExtension();

private:
    Ui::MainWindow *ui;

private slots:
    void toggleTask(QListWidgetItem* item);
    void addNewTask();
    void saveList();
    void loadTasks();
};

#endif // MAINWINDOW_H
