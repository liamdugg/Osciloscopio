#include "ThreadUSB.h"

ThreadUSB::ThreadUSB(CustomUSB *customUSB, QObject *parent)
    : QThread(parent)
{
   pCustomUSB = customUSB;
   modo = Modo::modoSignal;
}

void ThreadUSB::modChange(Modo mod)
{
    setModo(mod);
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
                    if(contador  == 32){
                        emit datoNuevoSingnal(&data);
                        usleep(500);
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
                    emit datoNuevoMesure(dataSignal);
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

