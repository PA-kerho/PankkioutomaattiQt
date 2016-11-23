#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow){
    olioSLRFID = new SLRFID;
    olioCheckCard = new CheckCard;
    ui->setupUi(this);
    CheckCardCalled = false;
    CanUseReadCard = true;
    if(!olioSLRFID->Connect("/dev/ttyACM0")){
        ui->TextLabel->setText("Automaatti ei ole käytössä");
    } else {
        if(!olioCheckCard->Connect()){
            ui->TextLabel->setText("Automaatti ei ole käytössä");
        } else {
            connect(olioSLRFID, SIGNAL(ReadyRead()), this, SLOT(ReadCard()));
        }
    }
}

MainWindow::~MainWindow(){
    delete olioSLRFID;
    delete olioCheckCard;
    delete ui;
}
void MainWindow::on_pushButtonClose_clicked(){
    this->close();
}

void MainWindow::ReadCard(){
    if(CanUseReadCard){
        CanUseReadCard = false;
        CardID = olioSLRFID->ReturnData().mid(3,10);
        qDebug() << CardID;
        ui->TextLabel->setText("Tarkistetaan korttia...");
        disconnect(Connect);
        Connect = connect(&timer, SIGNAL(timeout()), this, SLOT(FuncCheckCard()));
        timer.start(1000);
    }
}

void MainWindow::FuncCheckCard(){
    QString PinCode = olioCheckCard->GetCard(CardID);
    qDebug() << PinCode;
    if(PinCode != "false"){
       CheckPinCode(PinCode);
    } else {
        Restart(3000, "Tuntematon kortti");
    }
}

void MainWindow::CheckPinCode(QString PinCode){
    if(1){//TÄSSÄ KYSYTÄÄN PINKOODI
        disconnect(Connect);
        Connect = connect(&timer, SIGNAL(timeout()), this, SLOT(ShowActions()));
        timer.start(1000);
    } else {
        Restart(100,"");
    }
}

void MainWindow::ShowActions(){
    ActionWindow.showFullScreen();
    Restart(100,"");
}

void MainWindow::Restart(int Time, QString Error){
    ui->TextLabel->setText(Error);
    disconnect(Connect);
    Connect = connect(&timer, SIGNAL(timeout()), this, SLOT(GoToStart()));
    timer.start(Time);
}

void MainWindow::GoToStart(){
    ui->TextLabel->setText("Laita kortti lukijaan aloittaaksesi");
    CanUseReadCard = true;
}

