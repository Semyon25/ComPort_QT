#ifndef COMPORT_H
#define COMPORT_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QPixmap>

namespace Ui {
class ComPort;
}

class ComPort : public QMainWindow
{
    Q_OBJECT

public:
    explicit ComPort(QWidget *parent = nullptr);
    ~ComPort();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void handleReadyRead();

    void on_Connect_clicked();

    void ChangeNameButton();

private:
    Ui::ComPort *ui;
    QSerialPort *port;
    bool isConnected = false;
    void connect(bool x) {
        if (isConnected!=x)
        {
            isConnected = x;
            emit changeIsConnected();
        }
    }

signals:
    void changeIsConnected();

};

#endif // COMPORT_H
