#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include <QHBoxLayout>
#include <QMessageBox>
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
    if (parser.parse_url(URL.toStdString()) == 0)
    {
        QMessageBox::information(this, "Result", "The page was successfully received!", QMessageBox::Ok);
        std::ifstream file;
        file.open("../build-Application-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/index.html");
        std::string html_string {}, buffer {};
        while(!file.eof()) {
            getline(file, buffer);
            html_string += buffer + "\n";
        }
        ui->html_text->clear();
        ui->html_text->insertPlainText(html_string.c_str());
        file.close();
    }
    else
    {
        QMessageBox::warning(this, "Result", "The page was not received. Failed!", QMessageBox::Ok);
    }
}
