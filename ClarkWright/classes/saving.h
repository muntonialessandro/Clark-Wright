#ifndef SAVING_H
#define SAVING_H

#include <QVector>
#include <sstream>

typedef int idSaving;


class Saving
{
public:
    Saving();
    Saving(idSaving idActual, int idc1, int idc2, double value);
    bool operator ==(Saving &other) const;
    bool operator !=(Saving &other) const;
    bool operator <(Saving &other) const;
    bool operator >(Saving &other) const;
    bool operator <=(Saving &other) const;
    bool operator >=(Saving &other) const;
    idSaving getSaving_id();
    idSaving getTwinSaving_id();
    void setTwinSaving_id(int idTwin);
    int getIdC1();
    int getIdC2();
    double getValue();
    bool getEnable();
    void setId(idSaving id);
    std::string toString();

private:
    idSaving idActual;  // id Saving
    idSaving idTwin;    // id del Saving "simmetrico" rispetto a quello considerato
    int idc1;           // id Client 1
    int idc2;           // id Client 2
    double value;       // valore del saving
    bool enable;        // se settato a false, indica che il twin del saving attuale e' gia' stato utilizzato in una route.
                        // Ovvero il saving attuale non può essere candidato all'inserimento in un'altra route.
};


#endif // SAVING_H
