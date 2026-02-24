#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDebug>
#include <QTimer>
#include <QRegExpValidator>
#include <QTime>
QT_BEGIN_NAMESPACE
namespace Ui {
class ClientWindow;
}
QT_END_NAMESPACE

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private slots:
    void on_pushButtonConnect_clicked();

    void on_pushButtonSend_clicked();

    void on_pushButtonDisconnect_clicked();

    void on_pushButtonClearInput_clicked();

    void on_pushButtonClearOuput_clicked();

private:
    Ui::ClientWindow *ui;
    QUdpSocket *socket;
    bool isConnection = false;
    void sendMessage(const QString message);
    void readSocket();
    void isActiveForm(const bool active);
};
#endif // CLIENTWINDOW_H
