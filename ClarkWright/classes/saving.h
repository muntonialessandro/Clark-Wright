#ifndef SAVING_H
#define SAVING_H

#include <QVector>
#include <sstream>

typedef int idSaving;

/**
 * @brief The Saving class
 * Modella un saving, ossia un guadagno nel fondere due nodi in una route.
 * assumendo che il saving è relativo a due nodi generici x, y, il saving è composto da:
 *  - idActual: id del saving relativo ai nodi x, y
 *  - idTwin  : id del saving relativo ai nodi y, x (non utilizzato nei problemi simmetrici)
 *  - idc1    : id del nodo x
 *  - idc2    : id del nodo y
 *  - value   : entità del guadagno dell'inserimento
 *  - enable  : variabile booleana che indica se il saving viene ancora utilizzato o meno
 */
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

    static bool sortSavings(const Saving &s1, const Saving &s2);
    void setEnable(bool value);
    void swapClients();


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
