#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFont>

const QString TASKS_DIRECTORY = "./tasks/";
const QString TASKS_EXTENSION = "*.tasks";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("TODO LISTS");

    listFilesWithExtension();
    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::loadTasks);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveList);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::addNewTask);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::toggleTask);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listFilesWithExtension()
{
    QDir dir(TASKS_DIRECTORY);

    if (!dir.exists()) {
        qDebug() << "Folder nie istnieje!";
        return;
    }

    QStringList filters { TASKS_EXTENSION };
    QStringList fileNames = dir.entryList(filters, QDir::Files);
    QStringList existingItems;

    for (int i = 0; i < ui->comboBox->count(); ++i) {
        existingItems << ui->comboBox->itemText(i);
    }

    for (const QString &file : fileNames) {
        if (!existingItems.contains(file)) {
            ui->comboBox->addItem(file);
        }
    }
}

void MainWindow::toggleTask(QListWidgetItem* item)
{
    QFont font = item->font();
    font.setStrikeOut(!font.strikeOut());
    item->setFont(font);
}

void MainWindow::addNewTask()
{
    const QString taskText = ui->lineEdit->text();
    if (taskText.isEmpty()) {
        return;
    }

    ui->listWidget->addItem(taskText);
}

void MainWindow::saveList()
{
    const QString fileName = ui->saveLineEdit->text();
    if (fileName.isEmpty()) {
        QMessageBox::warning(nullptr, "Błąd", "Należy podać nazwę pliku!");
        return;
    }

    QFile file(TASKS_DIRECTORY + fileName + ".tasks");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Błąd", "Nie udało się otworzyć pliku!");
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem* item = ui->listWidget->item(i);
        const QString taskText = item->text();
        const bool isStrikeOut = item->font().strikeOut();
        out << taskText << "," << (isStrikeOut ? "1" : "0") << "\n";
    }

    file.close();
    listFilesWithExtension();
    QMessageBox::information(nullptr, "Sukces", "Zadania zostały zapisane do pliku!");
}

void MainWindow::loadTasks()
{
    ui->listWidget->clear();

    const QString filePath = TASKS_DIRECTORY + ui->comboBox->currentText();
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Błąd", "Nie udało się otworzyć pliku!");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        const QString line = in.readLine();
        const QStringList parts = line.split(",");

        if (parts.size() == 2) {
            const QString taskText = parts[0];
            const bool isStrikeOut = (parts[1] == "1");

            QListWidgetItem* newItem = new QListWidgetItem(taskText);
            QFont font = newItem->font();
            font.setStrikeOut(isStrikeOut);
            newItem->setFont(font);

            ui->listWidget->addItem(newItem);
        }
    }

    file.close();
}
