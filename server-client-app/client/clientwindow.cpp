#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    socket = new QUdpSocket();
    connect(socket, &QUdpSocket::readyRead, this, &ClientWindow::readSocket);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::sendMessage(const QString message)
{
    QByteArray data = message.toUtf8();
    socket->writeDatagram(data.data(), data.size(), QHostAddress(ui->textEditAdress->toPlainText()), 8888);
}

void ClientWindow::readSocket()
{
    while(socket->hasPendingDatagrams())
    {
        QNetworkDatagram data = socket->receiveDatagram();
        ui->textEditServerMsg->setPlainText(data.data());
    }
}

void ClientWindow::on_pushButton_clicked()
{
    socket->bind(QHostAddress(ui->textEditAdress->toPlainText()), 8888);
    if(ui->textEdit->toPlainText() != nullptr && ui->textEditAdress->toPlainText() != nullptr)
    {
        sendMessage(ui->textEdit->toPlainText());
        ui->textEdit->clear();
        if(socket->waitForReadyRead(1000))
        {
            ui->textEdit->setPlainText("Данные отправлены");
        }
        else
        {
            ui->textEdit->setPlainText("Нет такого адреса!");
        }

    }
    else
    {
        ui->textEdit->setPlainText("Вы не ввели адрес или текст для отправки данных");
    }
    QTimer::singleShot(2000,[this](){ui->textEdit->clear();});
}

