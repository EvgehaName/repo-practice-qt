#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDebug>
#include <QTimer>
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
    void on_pushButton_clicked();

private:
    Ui::ClientWindow *ui;
    QUdpSocket *socket;
    void sendMessage(const QString message);
    void readSocket();

};
#endif // CLIENTWINDOW_H
