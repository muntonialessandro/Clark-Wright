#ifndef ROUTE_H
#define ROUTE_H

#include <QVector>
#include "client.h"

/**
 * @brief The Route class
 *  Modella una route, ossia un percorso di nodi nel grafo.
 *  è composta dagli attributi:
 *      - id            : identifica univocamente una route nel grafo;
 *      - cost          : costo totale della route;
 *      - clients_route : array di clienti presenti nella route, in ordine di percorrenza;
 *                        ogni route parte dal nodo 0 (deposito) e finisce sempre nel nodo 0;
 *      - enabled       : indica se la route è attiva o se è stata eliminata;
 *      - n_nodes       : numero di nodi presenti nella route, compreso il nodo 0 di partenza e il
 *                        nodo 0 di destinazione.
 */
class Route
{
public:
    Route();
    Route(int id, client_id client, double cost);
    QVector<client_id> get_route();
    int get_n_nodes();
    double get_cost();
    bool insert_client(client_id id, index_client previous_client);
    bool remove_client(index_client i);
    void set_cost(double cost);
    void set_id(route_id id);
    client_id get_client(index_client i);
    void enable();
    void disable();
    bool is_enabled();
    std::string to_string();



private:
    int id;
    double cost;
    QVector<client_id> clients_route;
    bool enabled;
    int n_nodes;
};

#endif // ROUTE_H
