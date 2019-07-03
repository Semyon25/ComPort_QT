#include "comPort.h"
#include "ui_comPort.h"

ComPort::ComPort(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComPort)
{
    ui->setupUi(this);
    port = new QSerialPort(this);
    auto infos = QSerialPortInfo::availablePorts();
    for (auto &info : infos) {
        ui->comboBox->addItem(info.portName());
    }

    QPixmap pix(":/res/img/2.png");
    ui->image->setPixmap(pix);
    ui->statusBar -> showMessage("Не подключено");

    QObject::connect(port, &QSerialPort::readyRead, this, &ComPort::handleReadyRead);
}

ComPort::~ComPort()
{
    delete ui;
}

void ComPort::on_pushButton_clicked() // Отправка
{
    if (!isConnected) return;
    QByteArray str = ((ui->lineEdit->text()).append("\n")).toUtf8();
    if (str=="\n") return;
    port->write(str);

}

void ComPort::on_pushButton_2_clicked() // Очистка
{
    ui->plainTextEdit->clear();
}

void ComPort::handleReadyRead() // Получение данных
{
    QString str = (port->readAll().data());

    ui->plainTextEdit->insertPlainText(str);
}

void ComPort::on_Connect_clicked() // Подключение
{
    QString s = ui->comboBox->currentText();
    port->setPortName(s);
    port->setBaudRate(9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    if (port->open(QIODevice::ReadWrite)){
        //QMessageBox::information(this, "", "Port open");
        isConnected = true;
        QPixmap pix(":/res/img/1.png");
        ui->image->setPixmap(pix);
        ui->statusBar -> showMessage("Подключено");
    }
    else {

        QMessageBox::warning(this, "", "Port not open");
        isConnected = false;
    }
}

