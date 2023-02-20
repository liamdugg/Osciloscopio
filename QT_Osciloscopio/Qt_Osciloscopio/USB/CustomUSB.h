#ifndef CUSTOMUSB_H
#define CUSTOMUSB_H

#include <QObject>
#include <libusb-1.0/libusb.h>
#include <QtCore>
#include <QThread>

#define MY_VENDOR  ((uint16_t) 1155)//0x0483)
#define MY_PRODUCT ((uint16_t) 22352)//0x5910)
#define TRANSFER_SIZE ((uint8_t) 64)

class CustomUSB : public QObject
{
    Q_OBJECT
public:
    explicit CustomUSB(uint16_t VendorID = MY_VENDOR, uint16_t ProductID = MY_PRODUCT);
    ~CustomUSB();

    quint8 conectar();
    quint8 abrirDispositivo();
    quint8 desconectar();
    bool estadoConexion();

    quint8 EnviarMensaje(QByteArray MensajeTX, int lenght);
    quint8 RecibirMensaje(QVector<double> &L);
    quint8 RecibirMensaje(QString &Data);
    void setVendorID(uint16_t VendorID);
    void setProductID(uint16_t ProductID);
    uint16_t getVendorID();
    uint16_t getProductID();
signals:
    void statusChange(bool status);
private:
    void showDeviceData();

    libusb_device **devs = NULL;
    libusb_context *ctx = NULL;

    libusb_device_handle *dev_handle;

    libusb_device_descriptor desc;
    libusb_config_descriptor *config;

    const libusb_interface *inter;
    const libusb_interface_descriptor *interdesc;
    const libusb_endpoint_descriptor *epdesc;

    bool status;
    uint8_t Dispositivo;
    uint8_t CantDisp;
    uint16_t idVendor;
    uint16_t idProduct;
    QVector<double> valorADC;
};

#endif // CUSTOMUSB_H
