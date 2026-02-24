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
    ui->textEditOutput->setReadOnly(true);
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::readSocketUDP()
{
    while(socket->hasPendingDatagrams())
    {
        QTime time = QTime::currentTime();
        QNetworkDatagram datagram = socket->receiveDatagram();
        QByteArray array = datagram.data();
        QString message = QString::fromUtf8(array);
        QString msg = "Client IP: " + datagram.senderAddress().toString() + " [" +time.toString() +  "]" + " " + message;
        qDebug() << "Client message: " << message << "from: " << datagram.senderAddress().toString();
        ui->textEditOutput->append(msg);
        if(datagram.data() == "connect")
        {
            socket->writeDatagram("Подключено", datagram.senderAddress(), datagram.senderPort());
            ui->textEditOutput->append(msg);
        }
        else
        {
            socket->writeDatagram(datagram.data(), datagram.senderAddress(), datagram.senderPort());
        }
    }
}

void ServerWindow::on_pushButtonClearOutput_clicked()
{
    ui->textEditOutput->clear();
}

