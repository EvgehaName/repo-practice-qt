#include "serverwindow.h"
#include "ui_serverwindow.h"

ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    socket = new QUdpSocket();
    socket->bind(QHostAddress::LocalHost, 8888);
    connect(socket, &QUdpSocket::readyRead, this, &ServerWindow::readSocketUDP);
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::readSocketUDP()
{
    while(socket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = socket->receiveDatagram();
        qDebug() << "Client message: " << datagram.data() << "from: " << datagram.senderAddress().toString();
        socket->writeDatagram("Hello, I server ! ", datagram.senderAddress(), datagram.senderPort());
    }
}
