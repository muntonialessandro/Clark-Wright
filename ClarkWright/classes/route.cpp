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

#include "route.h"

/**
 * @brief Route::Route
 *  Costruttore vuoto di una route. Viene creata una route con origine e destinazione 0,
 *  disabilitata e con id -1.
 */
Route::Route()
{
    this->clients_route.push_back(0);
    this->clients_route.push_back(0);
    this->cost = 0;
    this->id = -1;
    this->enabled = false;
    this->n_nodes = 2;
    this->goods = 0;
}

/**
 * @brief Route::Route
 *  Costruttore: crea una route iniziale nella rete del tipo deposito-cliente-deposito, richiedendo in
 *  ingresso:
 *      - id della route;
 *      - l'unico cliente presente nella route (oltre il deposito);
 *      - costo della route
 *  La route viene abilitata automaticamente.
 * @param id
 * @param client
 * @param cost
 */
Route::Route(int id, Client client, double cost)
{
    this->clients_route.push_back(0);
    this->clients_route.push_back(client.get_id());
    this->clients_route.push_back(0);
    this->cost = cost;
    this->id = id;
    this->enabled = true;
    this->n_nodes = 3;
    this->goods = client.get_demand();
}

/**
 * @brief Route::get_route
 *  Restituisce un QVector contenente gli id dei clienti della route.
 * @return
 */
QVector<client_id> Route::get_route()
{
    return this->clients_route;
}

/**
 * @brief Route::get_n_nodes
 *  Restituisce il numero di nodi presenti in una route, compreso il deposito (due volte)
 * @return
 */
int Route::get_n_nodes()
{
    return this->n_nodes;
}

/**
 * @brief Route::get_cost
 *  Restituisce il costo totale della route
 * @return
 */
double Route::get_cost()
{
    return this->cost;
}

/**
 * @brief Route::insert_client
 *  Inserisce un cliente in una route.
 *  Prende in ingresso l'id del cliente che verrà inserito nella route, e l'indice di posizione
 *  del nodo precedente al nodo da inserire.
 * @param id
 * @param previous_client
 * @return true se l'inserimento è andato a buon fine, false altrimenti
 */
bool Route::insert_client(client_id id, index_client previous_client, int demand)
{
    // se l'indice del cliente precedente all'inserimento rientra nel range dei nodi nella route
    if (previous_client < this->clients_route.size()){
        if (previous_client == this->clients_route.size()-1) // se sto inserendo nell'ultima posizione
            this->clients_route.push_back(id);
        else
            this->clients_route.insert(previous_client+1, id); //inserisco DOPO il precedente
        this->n_nodes++; //nella route vi è un cliente in più
        this->goods += demand;
        return true;
    }
    return false;
}

/**
 * @brief Route::remove_client
 *  Rimuove il cliente in posizione i dalla route. Restituisce true se l'operazione è andata a buon fine.
 * @param i
 * @return
 */
bool Route::remove_client(index_client i)
{
    if (i<clients_route.size()) { //se l'indice del cliente da rimuovere è nel range
        clients_route.remove(i);
        this->n_nodes--;
        return true;
    }
    return false;
}

/**
 * @brief Route::set_cost
 *  Modifica il costo della route
 * @param cost
 */
void Route::set_cost(double cost)
{
    this->cost=cost;
}

/**
 * @brief Route::set_id
 *  Modifica l'id della route
 * @param id
 */
void Route::set_id(route_id id)
{
    this->id = id;
}

/**
 * @brief Route::set_client
 *  Setta il client in posizione i nella route
 * @param i
 * @param c
 */
void Route::set_client(index_client i, client_id c)
{
    this->clients_route[i] = c;
}

/**
 * @brief Route::get_client
 *  Restituice l'id del cliente in posizione i nella route
 * @param i
 * @return
 */
client_id Route::get_client(index_client i)
{
    return clients_route[i];
}

/**
 * @brief Route::enable
 *  Abilita la route.
 */
void Route::enable()
{
    this->enabled = true;
}

/**
 * @brief Route::disable
 *  Disabilita la route
 */
void Route::disable()
{
    this->enabled = false;
}

/**
 * @brief Route::is_enabled
 * @return true se la route è abilitata, false altrimenti.
 */
bool Route::is_enabled()
{
    return this->enabled;
}

/**
 * @brief Route::get_goods
 *  Restituisce i beni trasportati dal mezzo nella route
 * @return
 */
int Route::get_goods()
{
    return this->goods;
}

/**
 * @brief Route::add_goods
 *  Aggiunge una quantità di beni da trasportare nella route
 * @param demand
 */
void Route::add_goods(int demand)
{
    this->goods += demand;
}

/**
 * @brief Route::to_string
 *  Restituisce una stringa contenente i dati della route;
 * @return
 */
std::string Route::to_string()
{
    int i;
    std::stringstream ss;
    ss << "RouteID: " << this->id << "; Enabled: " << this->enabled << "; ";
    if (this->enabled) {
        ss << "Cost: " << this->cost << "; Route: [";
        for (i=0; i<this->clients_route.size(); i++){
            ss << this->clients_route[i] << " ";
        }
        ss << "]; Goods: " << this->goods << ";";
    }
    std::string s = ss.str();
    return s;
}


void Route::set_visited(){
    this->visitated = true;
}

bool Route::get_visitated(){
    return this->visitated;
}

int Route::get_id(){
    return this->id;
}
