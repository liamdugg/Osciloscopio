#include "CustomUSB.h"

CustomUSB::CustomUSB(uint16_t VendorID, uint16_t ProductID)
{
    setVendorID(VendorID);
    setProductID(ProductID);
}

CustomUSB::~CustomUSB()
{
    if(estadoConexion())
    {
        status = false;
        libusb_free_device_list(devs,1);
        libusb_exit(ctx);
    }
}

quint8 CustomUSB::conectar()
{
    status = 0;
    libusb_init(&ctx);
    libusb_set_option(ctx, LIBUSB_OPTION_MAX);
    CantDisp = libusb_get_device_list(ctx,&devs);
    for(int i = 0; i< CantDisp; i++){
        if(libusb_get_device_descriptor(devs[i],&desc)<0)
        {
            qDebug() << "Error con el device descriptor del dispositivo";
            return 0;
        }

        if(desc.idProduct == getProductID() && desc.idVendor == getVendorID())
            Dispositivo = i;
    }
    showDeviceData();
    if(abrirDispositivo()){
        status = true;
        emit statusChange(status);
        return 1;
    }  else {
        return 0;
    }
}

quint8 CustomUSB::abrirDispositivo()
{
    if(libusb_open(devs[Dispositivo],&dev_handle) < 0)
        return 0;
    return 1;
}

quint8 CustomUSB::desconectar()
{
    if(estadoConexion())
    {
        status = false;
        emit statusChange(status);
        libusb_free_device_list(devs,1);
        libusb_exit(ctx);
        return 1;
    }
    return 0;
}

bool CustomUSB::estadoConexion()
{
    return status;
}

quint8 CustomUSB::EnviarMensaje(QByteArray MensajeTX, int lenght)
{
    unsigned char TxData [lenght];

    for(int i = 0; i<lenght; i++)
    {
        TxData[i] = MensajeTX[i];
    }
    libusb_claim_interface(dev_handle, 0);
    if( libusb_interrupt_transfer(dev_handle , 0x01 ,TxData, sizeof (TxData) , &lenght , 0) < 0){
        return 0;
    }
    return 1;
}

quint8 CustomUSB::RecibirMensaje(QVector<double> &L)
{
    QByteArray dato;
    int actual_length;
    unsigned char RxData [0x40];
    if(!libusb_interrupt_transfer(dev_handle , 0x81 ,RxData , sizeof (RxData) , &actual_length , 0) )
    {
        dato.resize(actual_length);
        for(int i = 0; i<actual_length; i++)
            dato[i] = RxData[i];
        quint16 *p = (quint16*) dato.data();
        for (int i=0; i<actual_length/2; i++) {
            L << qFromBigEndian(p[i]);
        }
        return 1;
    }
    return 0;
}

quint8 CustomUSB::RecibirMensaje(QString &Data)
{
    int actual_length;
    unsigned char RxData [0x40];
    if(!libusb_interrupt_transfer(dev_handle , 0x81 ,RxData , sizeof (RxData) , &actual_length , 0) )
    {
        Data.resize(actual_length);
        for(int i = 0; i<actual_length; i++)
            Data[i] = RxData[i];
        return 1;
    }
    return 0;
}

void CustomUSB::setVendorID(uint16_t VendorID)
{
    idVendor = VendorID;
}

void CustomUSB::setProductID(uint16_t ProductID)
{
    idProduct = ProductID;
}

uint16_t CustomUSB::getVendorID()
{
    return idVendor;
}

uint16_t CustomUSB::getProductID()
{
    return idProduct;
}

void CustomUSB::showDeviceData()
{
    libusb_get_config_descriptor(devs[Dispositivo], 0, &config);
    qDebug() <<"Interfaces: "<<(uint8_t)config->bNumInterfaces;

    for(int j=0; j<(uint8_t )(config->bNumInterfaces); j++)
    {
        inter = &config->interface[j];
        qDebug()<<"Cantidad de conf. alternativas: "<<(uint8_t) (inter->num_altsetting);

        for(int k=0; k < (uint8_t) (inter->num_altsetting); k++)
        {
            interdesc = &inter->altsetting[k];
            qDebug() << "Cant. de Interfaces: "<<(uint8_t )interdesc->bInterfaceNumber;
            qDebug() << "Cant. de Endpoints: "<<(uint8_t )interdesc->bNumEndpoints;

            for(int p= 0 ; p<(uint8_t )interdesc->bNumEndpoints; p++)
            {
                   epdesc = &interdesc->endpoint[p];
                   qDebug() << "Tipo de Descriptor: "<<(uint8_t )epdesc->bDescriptorType;
                   qDebug() << "Dirección de EP: "<< Qt::hex << (uint8_t )epdesc->bEndpointAddress;
            }
        }
    }
    libusb_free_config_descriptor(config);
}
