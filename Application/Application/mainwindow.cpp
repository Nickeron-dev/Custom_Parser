#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include <QHBoxLayout>
#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString URL = ui->url_text->toPlainText();
    std::cout << "URL: " << URL.toStdString() << std::endl;
    Parser parser;
    parser.parse_url(URL.toStdString());
    std::fstream file("index.html");
    std::string html_string;
    file >> html_string;
    QString html_qstring(html_string.c_str());
    ui->html_text->setText(html_qstring);

}

