#include "graph_routes.h"

GraphRoutes::GraphRoutes(){}

/**
 * @brief GraphRoutes::GraphRoutes
 *  Crea un "grafo con le routes" iniziale. Prende in ingresso un QVector di Client e inizializza
 *  le routes banali su di essi. Il primo elemento del QVector è il deposito.
 * @param clients
 */
GraphRoutes::GraphRoutes(QVector<Client> clients)
{
    int i;
    this->clients = clients;
    this->n_routes = 0;
    for (i=1; i<this->clients.size(); i++){ //inizializzazione route (una per ogni cliente, tranne deposito)
        Route r(i-1, i, (this->clients[0].get_distance(this->clients[i]) * 2.0));
        this->routes.push_back(r); //inserisco la route
        this->clients[i].set_route(i-1); //salvo nel cliente la route a cui appartiene
        this->n_routes++; //incremento numero routes
    }
    this->n_clients = this->clients.size(); //salvo numero client
}

/**
 * @brief GraphRoutes::get_route
 *  Restituisce il QVector contenente i clienti visitati nella route rid;
 * @param rid
 * @return
 */
QVector<client_id> GraphRoutes::get_route(route_id rid)
{
    return routes[rid].get_route();
}

/**
 * @brief GraphRoutes::get_first_route_id
 *  Restituisce l'id della prima route attiva presente nell'array delle route;
 * @return
 */
route_id GraphRoutes::get_first_route_id()
{
    int i=0;
    while (!routes[i].is_enabled()) { //quando trovo ula prossima route enabled, mi fermo
        i++;
        if (i == routes.size()) return -1; //se i va out of bound, non ci sono altre route attive
    }
    return i;
}

/**
 * @brief GraphRoutes::get_next_route_id
 *  Restituisce l'id della route attiva successiva a quella passata in ingresso nell'array delle route.
 *  Se non vi è una route successiva, viene restituito -1.
 * @param rid
 * @return
 */
route_id GraphRoutes::get_next_route_id(route_id rid)
{
    rid++; //route successiva a quella in input
    if (rid == routes.size()) return -1; //se è out of bound, non ci sono altre route attive
    while (!routes[rid].is_enabled()) { //quando trovo ula prossima route enabled, mi fermo
        rid++;
        if (rid == routes.size()) return -1; //se rid va out of bound, non ci sono altre route attive
    }
    return rid;
}

/**
 * @brief GraphRoutes::get_cost_route
 *  Restituisce il costo della route rid;
 * @param rid
 * @return
 */
double GraphRoutes::get_cost_route(route_id rid)
{
    return this->routes[rid].get_cost();
}

/**
 * @brief GraphRoutes::get_total_cost
 *  Restituisce la somma dei costi di tutte le route
 * @return
 */
double GraphRoutes::get_total_cost()
{
    int i, cost = 0;
    for (i=0; i<routes.size(); i++){
        if (routes[i].is_enabled()) cost += routes[i].get_cost();
    }
    return cost;
}

/**
 * @brief GraphRoutes::delete_route
 *  Elimina una route.
 *  N.B. è compito dell'utente fare in modo che i nodi presenti in tale route vengano prima assegnati
 *  ad altre route. è consigliabile quindi utilizzare questo metodo soltanto se la route non contiene
 *  più nodi se non il deposito.
 * @param rid
 */
void GraphRoutes::delete_route(route_id rid)
{
    this->routes[rid].disable();
    this->n_routes--;
}

/**
 * @brief GraphRoutes::remove_client_from_route
 *  Rimuove, dalla route a cui appartiene, il client passato come parametro. La route a cui appartiene
 *  il client viene settata a -1. è altamente consigliato quindi, inserire il cliente appena rimosso dalla
 *  route in un'altra route. Aggiusta tutti i riferimenti degli altri clienti presenti nella route, e
 *  aggiorna il costo della route.
 * @param client
 * @return true se l'operazione è andata a buon fine, false altrimenti.
 */
bool GraphRoutes::remove_client_from_route(client_id client)
{
    route_id rid = clients[client].get_route(); //route dove si trova il client
    if (!routes[rid].is_enabled()) return false; //se la route non è attiva
    index_client i = clients[client].get_position_in_route(); //posizione del client nella route
    index_client previous = i-1, next = i+1; //posizioni del predecessore e successore
    //id del predecessore e successore
    client_id pid = routes[rid].get_client(previous), nid = routes[rid].get_client(next);
    double cost = routes[rid].get_cost(); //costo della route prima della rimozione
    //aggiorno il costo: sottraggo i costi di pred-c e c-succ, e aggiungo il costo pred-succ
    cost = cost - clients[pid].get_distance(clients[client]) -
                  clients[client].get_distance(clients[nid]) +
                  clients[pid].get_distance(clients[nid]);
    routes[rid].set_cost(cost);
    bool res = routes[rid].remove_client(i); //rimuovo il client dalla route
    clients[client].set_route(-1); //il client non sta più in nessuna route
    clients[client].set_position_in_route(-1); //il client non ha posizione in una route
    //aggiorno le posizioni dei client dal successore in poi, tranne il deposito alla fine
    for (; i<routes[rid].get_route().size()-1; i++) {
        client = routes[rid].get_client(i); //id del client
        clients[client].set_position_in_route(i); //set della nuova posizione nella route
    }
    return res;
}

/**
 * @brief GraphRoutes::insert_client_in_route
 *  Inserisce il cliente dopo il nodo indicato, nella route a cui appartiene tale nodo.
 *  Aggiusta tutti i riferimenti degli altri clienti presenti nella route e tutti gli
 *  attributi del cliente inserito.
 * @param client
 * @param previous_in_route
 * @param route
 */
bool GraphRoutes::insert_client_in_route(route_id rid, client_id client, client_id previous_in_route)
{
//    route_id route = clients[previous_in_route].get_route(); //route in cui si farà l'inserimento
    if (!routes[rid].is_enabled()) return false; //se la route non è attiva
    index_client previous = clients[previous_in_route].get_position_in_route(); //indice predecessore
    index_client next = previous+1; //indice in cui verrà inserito il client
    client_id nid = routes[rid].get_client(next); //id del client successivo
    double cost = routes[rid].get_cost(); //costo precedente all'inserimento
    //aggiorno il costo: aggiungo i costi di pred-c e c-succ, e sottraggo il costo pred-succ
    cost = cost + clients[previous_in_route].get_distance(clients[client]) +
                  clients[client].get_distance(clients[nid]) -
                  clients[previous_in_route].get_distance(clients[nid]);
    routes[rid].set_cost(cost);
    bool res = routes[rid].insert_client(client, previous); //inserisco il client dopo il predecessore
    clients[client].set_route(rid); //setto la nuova route a cui appartiene il client inserito
    index_client i;
    //partendo dal client inserito, aggiorno le posizioni dei clienti nella route, tranne il deposito
    for (i=previous+1; i<routes[rid].get_route().size()-1; i++){
        client = routes[rid].get_client(i); //id del client da aggiornare
        clients[client].set_position_in_route(i); //set della posizione
    }
    return res;
}

/**
 * @brief GraphRoutes::get_client
 *  Restituisce l'oggetto Client che ha id uguale al parametro;
 * @param cid
 * @return
 */
Client GraphRoutes::get_client(client_id cid)
{
    return clients[cid];
}

/**
 * @brief GraphRoutes::get_standard_saving
 *  Calcola e restituisce il saving standard tra i due client passati come parametri, ossia
 *  assumendo che si trovino entrambi nella loro route iniziale banale (anche se in realtà non lo sono).
 * @param c1
 * @param c2
 * @return
 */
double GraphRoutes::get_standard_saving(client_id c1, client_id c2)
{
    double d1 = (this->clients[c1].get_distance(clients[0]) * 2.0) +
                (this->clients[c2].get_distance(clients[0]) * 2.0);
    double d2 = this->clients[c1].get_distance(clients[0]) +
                this->clients[c1].get_distance(clients[c2]) +
                this->clients[c2].get_distance(clients[0]);
    return d1-d2;
}

/**
 * @brief GraphRoutes::get_saving_client_in_route
 *  Calcola e restituisce il saving che si ha nel caso in cui il client c_insert (che si assume sia
 *  nella sua route iniziale banale) venga inserito nella route rid, dopo il previous_client.
 * @param rid
 * @param c_insert
 * @param previous_client
 * @return
 */
double GraphRoutes::get_saving_client_in_route(route_id rid, client_id c_insert, client_id previous_client)
{
//    route_id route = clients[previous_client].get_route(); //route in cui si farà l'inserimento
    if (!routes[rid].is_enabled()) return -1; //se la route non è attiva
    //costo della route + costo della route banale del client c_insert
    double d1 = (this->clients[c_insert].get_distance(clients[0]) * 2.0) + this->routes[rid].get_cost();
    //calcolo del costo della route modificata:
    double d2 = routes[rid].get_cost(); //costo della route attuale
    index_client pid = clients[previous_client].get_position_in_route(); //posizione del precedente
    index_client nid = pid+1; //posizione del successivo (al nodo che verrà inserito)
    client_id next_client = routes[rid].get_client(nid); //id del successivo
    //costo rimosso con l'inserimento del nodo:
    double deleted = clients[previous_client].get_distance(clients[next_client]);
    //costo aggiunto con l'inserimento del nodo:
    double added = clients[previous_client].get_distance(clients[c_insert]) +
                   clients[c_insert].get_distance(clients[next_client]);
    double saving = d1 - (d2 - deleted + added);
    return saving;
}

/**
 * @brief GraphRoutes::to_string
 *  Restituisce una stringa riepilogativa dei clienti e delle route attive.
 * @return
 */
std::string GraphRoutes::to_string()
{
    int i;
    std::string s = "GraphRoutes:\n Clients:\n";
    for (i=0; i<clients.size(); i++){
        s += "\t";
        s += clients[i].to_string();
        s += "\n";
    }
    s += " Routes:\n";
    for (i=0; i<routes.size(); i++){
        if (routes[i].is_enabled()){
            s += "\t";
            s += routes[i].to_string();
            s += "\n";
        }
    }
    return s;
}

/**
 * @brief GraphRoutes::get_list_point_label_pairs
 * Restituisce una lista di coppie punto (x,y)/label (che è l'id sottoforma di stringa)
 * @return
 */
QList<QPair<QPoint, QString> > GraphRoutes::get_list_point_label_pairs()
{
    int i;
    QList< QPair<QPoint,QString> > pointList;
    for (i=0; i<clients.size(); i++){
        pointList.append(clients[i].to_point_label_pair());
    }
    return pointList;
}

/**
 * @brief GraphRoutes::get_list_edges
 *  Restituisce una lista di liste di qpoint, ogni lista contiene i qpoint di una route.
 * @return
 */
QList< QList<QPoint> > GraphRoutes::get_list_edges()
{
    QList< QList<QPoint> > list_routes;
    route_id rid;
    index_client j;
    for (rid=this->get_first_route_id(); rid!=-1; rid=this->get_next_route_id(rid)){
        QList<QPoint> list_points;
        for (j=0; j<routes[rid].get_n_nodes(); j++) {
            QPoint p = clients[routes[rid].get_client(j)].to_QPoint();
            list_points.append(p);
        }
        list_routes.append(list_points);
    }
    return list_routes;
}

QVector<Event> GraphRoutes::to_events_vector()
{
    QVector<Event> qe;
    int i;
    for (i=0; i<this->clients.size(); i++){
        qe.push_back(clients[i].to_Event());
    }
    return qe;
}

client_id GraphRoutes::get_previous_client(client_id client)
{
    index_client index = clients[client].get_position_in_route();
    
    return clients[index - 1].get_id();
}

