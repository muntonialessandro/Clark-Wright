#include "client.h"

Client::Client(){}

/**
 * @brief Client::Client
 *  Costruttore: crea un cliente nella rete, richiedendo in ingresso:
 *      - id;
 *      - coordinate x, y;
 *      - quantità di merce richiesta.
 *  Setta in automatico:
 *      - la variabile "alone" a true: indica se il cliente è da solo nella route in cui si trova;
 *      - la posizione (indice) nella route, che all'inizio è 1 se non è il nodo 0 (deposito)
 *  NON setta la route a cui appartiene il cliente, a meno che non sia il nodo 0 (deposito)
 * @param id
 * @param x
 * @param y
 * @param demand
 */
Client::Client(client_id id, double x, double y, double demand)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->demand = demand;
    this->alone = true;
    this->neighbors.clear();
    this->distances.clear();
    if (id == 0) { // se è il deposito
        this->position_in_route = -1;
        this->rid = -1;
    }
    else this->position_in_route = 1; //all'inizio, i clienti sono sempre in posizione 1 nelle route
}

/**
 * @brief Client::set_id
 *  Modifica l'id del cliente
 * @param id
 */
void Client::set_id(client_id id)
{
    this->id = id;
}

/**
 * @brief Client::get_id
 *  Restituisce l'id del cliente
 * @return
 */
client_id Client::get_id()
{
    return this->id;
}

/**
 * @brief Client::set_coordinates
 *  Modifica le coordinate del cliente
 * @param x
 * @param y
 */
void Client::set_coordinates(double x, double y)
{
    this->x = x;
    this->y = y;
}

/**
 * @brief Client::get_x
 *  Restituisce la coordinata x del cliente
 * @return
 */
double Client::get_x()
{
    return this->x;
}

/**
 * @brief Client::get_y
 *  Restituisce la coordinata y del cliente
 * @return
 */
double Client::get_y()
{
    return this->y;
}

/**
 * @brief Client::get_demand
 *  Restituisce la quantità di merce richiesta dal cliente
 * @return
 */
double Client::get_demand()
{
    return this->demand;
}

/**
 * @brief Client::get_route
 *  Restituisce la route alla quale appartiene il cliente
 * @return
 */
route_id Client::get_route()
{
    return this->rid;
}

/**
 * @brief Client::set_demand
 *  Modifica la quantità di merce richiesta dal cliente
 * @param demand
 */
void Client::set_demand(double demand)
{
    this->demand = demand;
}

/**
 * @brief Client::get_distance
 *  Restituisce la distanza euclidea tra il cliente this e il cliente passato come parametro;
 * @param c
 * @return
 */
double Client::get_distance(Client c)
{
    double c_x = c.get_x();
    double c_y = c.get_y();
    //distanza euclidea tra i due punti:
    double dist = pow((this->x - c_x),2) + pow((this->y - c_y),2);
    dist = sqrt(dist);
    return dist;
}

/**
 * @brief Client::set_route
 *  Modifica la route a cui appartiene il cliente;
 * @param rid
 */
void Client::set_route(route_id rid)
{
    this->rid = rid;
}

/**
 * @brief Client::get_position_in_route
 *  Restituisce la posizione del cliente nella route in cui si trova;
 * @return
 */
index_client Client::get_position_in_route()
{
    return this->position_in_route;
}

/**
 * @brief Client::set_position_in_route
 *  Modifica la posizione del cliente nella route in cui si trova;
 * @param position
 */
void Client::set_position_in_route(index_client position)
{
    this->position_in_route = position;
}

/**
 * @brief Client::is_alone
 *  Restituisce l'attributo "alone"
 * @return
 */
bool Client::is_alone()
{
    return this->alone;
}

/**
 * @brief Client::set_alone
 *  Modifica l'attributo "alone"
 * @param a
 */
void Client::set_alone(bool a)
{
    this->alone = a;
}

/**
 * @brief Client::add_neighbor
 *  aggiunge un nuovo vicino alla lista dei vicini del cliente.
 * @param neighbor
 */
void Client::add_neighbor(client_id neighbor, double distance)
{
    int index = search_insert_index_double(distance, 0, this->distances.size()-1, this->distances);
    this->distances.insert(index, distance);
    this->neighbors.insert(index, neighbor);
}

/**
 * @brief Client::to_string
 *  Restituisce una stringa contenente i dati del cliente;
 * @return
 */
std::string Client::to_string()
{
    int i;
    std::stringstream ss;
    ss << "Client ID: " << this->id << "; Coordinates: (" << this->x << "; " << this->y
       << "); Demand: " << this->demand << "; RouteID: " << this->rid << "; Position: "
       << this->position_in_route << "; Alone: " << this->alone << ";" << std::endl;
    ss << "\tNeighbors: ";
    for (i=0; i<this->neighbors.size(); i++) ss << this->neighbors[i] << "; ";
    std::string s = ss.str();
    return s;
}

/**
 * @brief Client::to_point_label_pair
 *  Restituisce una coppia punto (x,y)/label (che è l'id sottoforma di stringa)
 * @return
 */
QPair<QPoint, QString> Client::to_point_label_pair()
{
    std::stringstream ss;
    ss << this->id; //per trasformare id in stringa
    QPoint p(this->x, this->y);
    std::string s = ss.str(); //da stream a string
    QString qs;
    qs = qs.fromStdString(s); //da string a QString
    QPair<QPoint, QString> pair = qMakePair(p, qs); //creo la coppia
    return pair;
}

/**
 * @brief Client::to_QPoint
 *  Restituisce il QPoint con le coordinate del cliente.
 * @return
 */
QPoint Client::to_QPoint()
{
    QPoint p(this->x, this->y);
    return p;
}

Event Client::to_Event()
{
    bool dep;
    if (this->id == 0) dep = true;
    else dep = false;
    return Event(this->id, this->x, this->y, dep, true);
}
