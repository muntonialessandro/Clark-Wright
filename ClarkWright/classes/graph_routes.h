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
    void delete_route(route_id rid);
    bool remove_client_from_route(client_id client);
    bool insert_client_in_route(client_id client, client_id previous_in_route);
    Client get_client(client_id cid);
    double get_standard_saving(client_id c1, client_id c2);
    double get_saving_client_in_route(route_id rid, client_id c_insert, client_id previous_client);
    std::string to_string();
    QList< QPair<QPoint,QString> > get_list_point_label_pairs();
    QList< QList<QPoint> > get_list_edges();

private:
    QVector<Client> clients;
    QVector<Route> routes;
    int n_routes;
    int n_clients;
};

#endif // GRAPH_ROUTES_H
