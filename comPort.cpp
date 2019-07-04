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
    ChangeNameButton();

    QObject::connect(port, &QSerialPort::readyRead, this, &ComPort::handleReadyRead);
    QObject::connect(this, &ComPort::changeIsConnected, this, &ComPort::ChangeNameButton);

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

void ComPort::on_Connect_clicked() // Подключение/Отключение
{
    if (isConnected) {
        connect(false);
        port->close();
        auto infos = QSerialPortInfo::availablePorts();
        ui->comboBox->clear();
        for (auto &info : infos) {
            ui->comboBox->addItem(info.portName());
        }
    }
    else {
    QString s = ui->comboBox->currentText();
    port->setPortName(s);
    port->setBaudRate(9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    connect(port->open(QIODevice::ReadWrite));
    auto infos = QSerialPortInfo::availablePorts();
    ui->comboBox->clear();
    for (auto &info : infos) {
        ui->comboBox->addItem(info.portName());
    }
    }
}

void ComPort::ChangeNameButton(){
    if (isConnected) {
        ui->Connect->setText("Отключить");
        QPixmap pix(":/res/img/1.png");
        ui->image->setPixmap(pix);
        ui->statusBar -> showMessage("Подключено");
    }
    else
    {
        ui->Connect->setText("Подключить");
        QPixmap pix(":/res/img/2.png");
        ui->image->setPixmap(pix);
        ui->statusBar -> showMessage("Не подключено");
    }
}
