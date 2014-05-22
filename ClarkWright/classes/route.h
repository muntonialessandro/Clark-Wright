/*
 *  Copyright (C) 2014 Simone Barbieri, Andrea Loddo, Emanuele Mameli, Alessandro Muntoni, Livio Pompianu
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
 *      - goods         : totale dei beni trasportati dal mezzo nella route
 */
class Route
{
public:
    Route();
    Route(int id, Client client, double cost);
    QVector<client_id> get_route();
    int get_n_nodes();
    double get_cost();
    bool insert_client(client_id id, index_client previous_client, int demand);
    bool remove_client(index_client i);
    void set_cost(double cost);
    void set_id(route_id id);
    void set_client(index_client i, client_id c);
    client_id get_client(index_client i);
    void enable();
    void disable();
    bool is_enabled();
    int get_goods();
    void add_goods(int demand);
    std::string to_string();
    void set_visited();
    bool get_visitated();
    int get_id();


private:
    int id;
    double cost;
    QVector<client_id> clients_route;
    bool enabled;
    int n_nodes;
    int goods;
    bool visitated;                         // Indica se la rotta e' stata considerata dall'algoritmo, diversamente e' una route banale.

};

#endif // ROUTE_H
