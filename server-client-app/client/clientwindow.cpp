#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipExp ("^" + ipRange
                   + "\\." + ipRange
                   + "\\." + ipRange
                   + "\\." + ipRange + "$");
    QRegExpValidator* ipValidator = new QRegExpValidator(ipExp);
    ui->lineEditIP->setValidator(ipValidator);
    ui->textEditOutput->setReadOnly(true);
    isActiveForm(false);
    socket = new QUdpSocket();
    connect(socket, &QUdpSocket::readyRead, this, &ClientWindow::readSocket);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

// Отправка сообщений на сервер
void ClientWindow::sendMessage(const QString message)
{
    QByteArray data = message.toUtf8();
    socket->writeDatagram(data.data(), data.size(),QHostAddress(ui->lineEditIP->text()), 8888);
}

// Получение от сервера сообщений
void ClientWindow::readSocket()
{
    QTime time = QTime::currentTime();
    while(socket->hasPendingDatagrams())
    {
        QNetworkDatagram data = socket->receiveDatagram();
        QString message = QString::fromUtf8(data.data());
        if(message == "Подключено")
        {
            ui->textEditOutput->append("[" + time.toString() + "]" + " " + data.data());
            ui->labelStatus->setText("Подключено!");
            isActiveForm(true);
            isConnection = true;
        }
        else if(message.isEmpty())
        {
            ui->labelStatus->setText("Сервер не найден!");
            isActiveForm(false);
            isConnection = false;
        }
        else
        {
            ui->textEditOutput->append("[" + time.toString() + "]" + " " + data.data());
        }
    }
}


// Событие по кнопки "Подключиться"
void ClientWindow::on_pushButtonConnect_clicked()
{
    sendMessage("connect");
}

// Событие по кнопки "Отправить ввод"
void ClientWindow::on_pushButtonSend_clicked()
{
   if(isConnection == true)
   {
       if(ui->textEditInput->toPlainText().isEmpty() || ui->textEditInput->toPlainText().trimmed().isEmpty())
       {
           ui->labelInformationInput->setText("Поле ввода должно быть заполненным!");
       }
       else
       {
           sendMessage(ui->textEditInput->toPlainText());
           ui->textEditInput->clear();
       }
       QTimer::singleShot(2000,[this](){ui->labelInformationInput->clear();});
   }
}

void ClientWindow::on_pushButtonDisconnect_clicked()
{
    ui->labelStatus->setText("Отключен!");
    isActiveForm(false);
    isConnection = false;
}

void ClientWindow::isActiveForm(const bool isActive)
{
    if(isActive == false)
    {
        ui->textEditInput->setEnabled(false);
        ui->pushButtonSend->setEnabled(false);
        ui->lineEditIP->setEnabled(true);
    }
    else
    {
        ui->textEditInput->setEnabled(true);
        ui->pushButtonSend->setEnabled(true);
        ui->lineEditIP->setEnabled(false);
    }
}


void ClientWindow::on_pushButtonClearInput_clicked()
{
    ui->textEditInput->clear();
}


void ClientWindow::on_pushButtonClearOuput_clicked()
{
    ui->textEditOutput->clear();
}

