#ifndef SIGNALDATA_H
#define SIGNALDATA_H

#include <QtCore>

#define FS1     (double)(1/640.0)
#define FS2     (double)(1/320.0)
#define FS3     (double)(1/160.0)
#define FS4     (double)(1/80.0)

class SignalData
{
public:
    SignalData(double fs = FS1, QString Frec = "0 Hz", QString Period = "0 Sg", QString Amp = "0 V" , QString Vrms = "0 V" )
    {
        Fs = fs;
        setFrecuncy(Frec);
        setPeriod(Period);
        setAmplitude(Amp);
        setVrms(Vrms);
    }
    enum uFrecuency { MHz, KHz, Hz };
    enum uPeriod    { uSg, mSg, Sg };
    enum uVolt      { uVolt, mVlot, Volt };
    enum samplimngFrecuency { fs1, fs2, fs3, fs4 };

    /* Metodos seters */
    void setSamplingFrecuency(samplimngFrecuency mode) {
        switch (mode) {
        case fs1:
            Fs = FS1;
            break;
        case fs2:
            Fs = FS2;
            break;
        case fs3:
            Fs = FS3;
            break;
        case fs4:
            Fs = FS4;
            break;
        default:
            break;
        }
    }
    void setFrecuncy(QString Frecuency){ Frecuencia = Frecuency; }
    void setPeriod(QString Period){ Periodo = Period; }
    void setAmplitude(QString Amp){ Amplitud = Amp; }
    void setVrms(QString vrms) { Vrms = vrms; }

    /* Metodos geters */
    double getSamplingFrecuency() { return Fs; }
    QString getFrecuency() { return Frecuencia; }
    QString getPeriod() { return Periodo; }
    QString getAmplitude() { return Amplitud; }
    QString getVrms(){ return Vrms; }
protected:
    QString Amplitud;
    QString Frecuencia;
    QString Vrms;
    QString Periodo;
    QString FrecSam;
    double Fs;
};

#endif // SIGNALDATA_H
