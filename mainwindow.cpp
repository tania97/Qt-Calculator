#include "mainwindow.h"
#include "ui_mainwindow.h"

double calcValue = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->myDisplay->setText(QString::number(calcValue));
    QPushButton *numButtons[10]; //array of buttons

    for(int i =0; i<10; ++i){
        QString buttonName = "pushButton" + QString::number(i); //to get the name of every button
        numButtons[i] = MainWindow::findChild<QPushButton *>(buttonName);
        connect(numButtons[i],SIGNAL(released()),this, SLOT(NumberPressed())); //when button is released go to NumPressed function
    }
    connect(ui->pushButton_plus, SIGNAL(released()),this, SLOT(MathButtonPressed()));
    connect(ui->pushButton_minus, SIGNAL(released()),this, SLOT(MathButtonPressed()));
    connect(ui->pushButton_divide, SIGNAL(released()),this, SLOT(MathButtonPressed()));
    connect(ui->pushButton_multiply, SIGNAL(released()),this, SLOT(MathButtonPressed()));
    connect(ui->pushButton_equal, SIGNAL(released()),this, SLOT(EqualButtonPressed()));
    connect(ui->pushButton_plusMinus, SIGNAL(released()),this, SLOT(ChangeNumberSign()));
    connect(ui->pushButton_clear, SIGNAL(released()), this, SLOT(ClearButtonPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumberPressed(){
    QPushButton *button = (QPushButton*)sender();
    QString buttonVal = button->text(); //get the value of button
    QString displayVal = ui->myDisplay->text(); //get value of display

    if((displayVal.toDouble()==0 || displayVal.toDouble()==0.0)){
        ui->myDisplay->setText(buttonVal);
    }else{
        QString newVal  = displayVal + buttonVal; //add new value to already shown number
        double d_newVal = newVal.toDouble();
        ui->myDisplay->setText(QString::number(d_newVal));
    }
}

void MainWindow::MathButtonPressed(){
    divTrigger = false;
    mulTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = ui->myDisplay->text();
    calcValue = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender(); //signal sends the action to this function
    QString buttonVal = button->text();

    if(QString::compare(buttonVal, "/", Qt::CaseInsensitive)==0){
        divTrigger = true;
    } else if (QString::compare(buttonVal, "*", Qt::CaseInsensitive)==0){
        mulTrigger = true;
    } else if (QString::compare(buttonVal, "+", Qt::CaseInsensitive)==0){
        addTrigger = true;
    } else {
        subTrigger = true;
    }

    ui->myDisplay->setText(""); //set the math sign text
}

void MainWindow::EqualButtonPressed(){

    double solution = 0.0;
    QString displayVal = ui->myDisplay->text();
    double d_displayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || divTrigger || mulTrigger){
        if(addTrigger){
            solution = calcValue + d_displayVal;

        } else if(subTrigger){
            solution = calcValue - d_displayVal;

        } else if(mulTrigger){
            solution = calcValue * d_displayVal;

        } else {
            solution = calcValue / d_displayVal;
        }
    }
    ui->myDisplay->setText(QString::number(solution));
}

void MainWindow::ClearButtonPressed(){
    ui->myDisplay->clear();
}

void MainWindow::ChangeNumberSign(){

    double changedNum = 0.0;
    QString number = ui->myDisplay->text();
    double d_number = number.toDouble();

    QPushButton *signButton = (QPushButton *)sender(); //signal sends the action to this function
    QString buttonVal = signButton->text();

    if(QString::compare(buttonVal, "+/-", Qt::CaseInsensitive)==0){

        changedNum = (-1) * d_number;

    }else{

        changedNum = d_number;

    }
    ui->myDisplay->setText(QString::number(changedNum));

}
