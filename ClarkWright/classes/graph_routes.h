#ifndef GRAPH_ROUTES_H
#define GRAPH_ROUTES_H

#include "client.h"
#include "route.h"

/**
 * @brief The GraphRoutes class
 *  Modella l'insieme di tutti i nodi e delle route costruite su essi, fornendo delle operazioni standard
 *  per la creazione degli algoritmi.
 */
class GraphRoutes
{
public:
    GraphRoutes();
    GraphRoutes(QVector<Client> clients);
    QVector<client_id> get_route(route_id rid);
    route_id get_first_route_id();
    route_id get_next_route_id(route_id rid);
    double get_cost_route(route_id rid);
    double get_total_cost();
    int get_goods_route(route_id rid);
    void delete_route(route_id rid);
    bool remove_client_from_route(client_id client);
    bool insert_client_in_route(route_id rid, client_id client, client_id previous_in_route);
    bool swap_consecutive_clients_in_route(client_id c1, client_id c2);
    int get_n_clients();
    int get_n_clients_in_route(route_id rid);
    Client get_client(client_id cid);
    QVector<Client> get_clients();
    int get_total_goods(route_id rid);
    double get_standard_saving(client_id c1, client_id c2);
    double get_saving_client_in_route(route_id rid, client_id c_insert, client_id previous_client);
    double get_saving_transfer_client(client_id id, route_id from_route, route_id to_route, client_id previous_client);
    double get_swap_saving(client_id c1, client_id c2);
    double get_swap_saving_consecutive_in_route(client_id c1, client_id c2);
    std::string to_string();
    QList< QPair<QPoint,QString> > get_list_point_label_pairs();
    QList< QList<QPoint> > get_list_edges();
    QVector<Event> to_events_vector();
    client_id get_previous_client(client_id client);
    client_id get_next_client(client_id client, route_id rid);

private:
    QVector<Client> clients;
    QVector<Route> routes;
    int n_routes;
    int n_clients;
};

#endif // GRAPH_ROUTES_H
