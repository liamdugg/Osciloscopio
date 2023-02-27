#ifndef SIGNALDATA_H
#define SIGNALDATA_H

#include <QtCore>
#include <QObject>
#define FS7     (double)(1/1400.0)
#define FS6     (double)(1/700.0)
#define FS5     (double)(1/250.0)
#define FS4     (double)(1/63.0)
#define FS3     (double)(1/15.7)
#define FS2     (double)(1/3.9)
#define FS1     (double)(1/0.98)

#define YM7     (double)(0.15)
#define YM6     (double)(0.25)
#define YM5     (double)(0.6)
#define YM4     (double)(3.0)
#define YM3     (double)(10.0)
#define YM2     (double)(50.0)
#define YM1     (double)(210.0)

#define Ym7     (double)(250/28571.0)
#define Ym6     (double)(500/2857.0)
#define Ym5     (double)(125/2551.0)
#define Ym4     (double)(50/257.0)
#define Ym3     (double)(25/32.0)
#define Ym2     (double)(3.125)
#define Ym1     (double)(12.5)

#define At3		(double)(0.3)
#define At5		(double)(0.5)
#define Am1		(double)(1.0)
#define Am3		(double)(3.0)
#define Am5		(double)(5.0)
#define Am10	(double)(10.0)
#define Am31	(double)(31.0)
#define Am50	(double)(50.0)

#define ATEN_03		"G0"	//A0
#define ATEN_05		"G1"	//A1
#define AMP_1		"G2"	//A2
#define AMP_3		"G3"	//A3
#define AMP_5		"G4"	//A4
#define AMP_10		"G5"	//A5
#define AMP_31		"G6"	//A6
#define AMP_50		"G7"	//A7

#define XMax        (double) 1000.0
#define Xmin        (double) 1.0
class SignalData : public QObject
{
        Q_OBJECT
public:
    SignalData(double fs = FS1, QString Frec = "0 Hz", QString Period = "0 Sg", QString Amp = "0 V" , QString Vrms = "0 V", double sf = Am1 )
    {
        setSamplingFrecuency(fs);
        setScaleFactor(sf);
        setFrecuncy(Frec);
        setPeriod(Period);
        setAmplitude(Amp);
        setVrms(Vrms);
    }
    enum uFrecuency { MHz, KHz, Hz };
    enum uPeriod    { uSg, mSg, Sg };
    enum uVolt      { uVolt, mVlot, Volt };
    enum samplimngFrecuency { fs1, fs2, fs3, fs4, fs5, fs6, fs7 };
    enum scaleAmplitud { aten_03, aten_05, amp_1, amp_3, amp_5, amp_10, amp_31, amp_50 };
    /* Metodos seters */
    void setScaleFactor(double sf){ Sf = sf; }
    void setSamplingFrecuency(samplimngFrecuency mode) {
        switch (mode) {
        case fs1:
            if(setSamplingFrecuency(FS1)){
                CalculoDial(YM1, Ym1);
                emit valueChangeDial();
            }
            break;
        case fs2:
            if(setSamplingFrecuency(FS2)){
                CalculoDial(YM2, Ym2);
                emit valueChangeDial();
            }
            break;
        case fs3:
            if(setSamplingFrecuency(FS3)){
                CalculoDial(YM3, Ym3);
                emit valueChangeDial();
            }
            break;
        case fs4:
            if(setSamplingFrecuency(FS4)){
                CalculoDial(YM4, Ym4);
                emit valueChangeDial();
            }
            break;
        case fs5:
            if(setSamplingFrecuency(FS5)){
                CalculoDial(YM5, Ym5);
                emit valueChangeDial();
            }
            break;
        case fs6:
            if(setSamplingFrecuency(FS6)){
                CalculoDial(YM6, Ym6);
                emit valueChangeDial();
            }
            break;
        case fs7:
            if(setSamplingFrecuency(FS7)){
                CalculoDial(YM7, Ym7);
                emit valueChangeDial();
            }
            break;
        default:
            break;
        }
    }
    void setScaleFactor(scaleAmplitud factor){
        switch (factor) {
        case aten_03:
            Sf = At3;
            break;
        case aten_05:
            Sf = At5;
            break;
        case amp_1:
            Sf = Am1;
            break;
        case amp_3:
            Sf = Am3;
            break;
        case amp_5:
            Sf = Am5;
            break;
        case amp_10:
            Sf = Am10;
            break;
        case amp_31:
            Sf = Am31;
            break;
        case amp_50:
            Sf = Am50;
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
    double getFactor(){ return Sf; }
    QString getFrecuency() { return Frecuencia; }
    QString getPeriod() { return Periodo; }
    QString getAmplitude() { return Amplitud; }
    QString getVrms(){ return Vrms; }

    /* Rango del dial */
    void CalculoDial(double max, double min){
        double a;
        double b;
        a = (max-min)/(XMax-Xmin);
        b = max - a*XMax;
        setA(a);
        setB(b);
    }
    void setA(double Pendiente){ a = Pendiente; }
    void setB(double termInd) { b = termInd; }

    double getA(){ return a; }
    double getB(){ return b; }
signals:
    void valueChangeDial();
private:
    bool setSamplingFrecuency(double fs){
        if(Fs != fs){
            Fs = fs;
            return true;
        }
        return false;
    }
    double a;
    double b;

protected:
    QString Amplitud;
    QString Frecuencia;
    QString Vrms;
    QString Periodo;
    QString FrecSam;
    double Sf;
    double Fs;
};

#endif // SIGNALDATA_H
