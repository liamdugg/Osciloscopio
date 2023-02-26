#include "ThreadUSB.h"

ThreadUSB::ThreadUSB(CustomUSB *customUSB, QObject *parent)
    : QThread(parent)
{
   pCustomUSB = customUSB;
   modo = Modo::modoSignal;
   setTime(1);
}

void ThreadUSB::modChange(Modo mod)
{
    setModo(mod);
}

void ThreadUSB::timeChange(SignalData::samplimngFrecuency fs)
{
    switch (fs) {
    case SignalData::fs1:
        setTime(524);
        break;
    case SignalData::fs2:
        setTime(134);
        break;
    case SignalData::fs3:
        setTime(36);
        break;
    case SignalData::fs4:
        setTime(17);
        break;
    case SignalData::fs5:
        setTime(17);
        break;
    case SignalData::fs6:
        setTime(17);
        break;
    case SignalData::fs7:
        setTime(17);
        break;
    default:
        break;
    }
}


void ThreadUSB::run()
{
    int contador = 0;
    while(true){
        if(modo == modoSignal){
            if(pCustomUSB->estadoConexion()){
                QByteArray MensajeTX = "#";
                int length = MensajeTX.size();
                pCustomUSB->EnviarMensaje(MensajeTX,length);
                if(pCustomUSB->RecibirMensaje(data)){
                    contador++;
                    if(contador  == 16){
                        emit datoNuevoADC(&data);
                        msleep(getTime());

                        contador = 0;
                    }
                }
            }
        }
        if(modo == modoDato){
            if(pCustomUSB->estadoConexion()){
                QByteArray MensajeTX = "$";
                int length = MensajeTX.size();
                pCustomUSB->EnviarMensaje(MensajeTX,length);
                if(pCustomUSB->RecibirMensaje(dataSignal)){
                    emit datoNuevoMediciones(dataSignal);
                }
                modo = modoSignal;
            }            
        }
        if(modo == modoConected){
            /* Estar conectado sin medir */
            if(pCustomUSB->estadoConexion()){
                QByteArray MensajeTX = "C";
                int length = MensajeTX.size();
                pCustomUSB->EnviarMensaje(MensajeTX,length);
                modo = modoNone;
            }
        }
        if(modo == modoDisconected){
            /* Estar conectado sin medir */
            if(pCustomUSB->estadoConexion()){
                QByteArray MensajeTX = "D";
                int length = MensajeTX.size();
                pCustomUSB->EnviarMensaje(MensajeTX,length);
                modo = modoNone;
            }
        }
        if(modo == modoNone){

        }
    }
}

