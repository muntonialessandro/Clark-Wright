#include "classes/graph_routes.h"
#include "classes/saving.h"

GraphRoutes closer_cw(QVector<Client> &sites, QVector<Saving> &savings, int cap);

GraphRoutes second_closer_cw(QVector<Client> &sites, QVector<Saving> &savings, int cap);

GraphRoutes lelle_closer_cw(QVector<Client> &sites, QVector<Saving> &savings, int cap);

GraphRoutes distance_based_closer_cw(QVector<Client> &sites, QVector<Saving> &savings, int cap);

void update_savings(Client c_route, Client c_next, GraphRoutes &graph_route, QVector<Saving>* route_savings);

void transfer_clients_post_processing(GraphRoutes *graph_routes,  int cap);

void update_savings_post_processing(Client c_route, Client c_next, GraphRoutes &graph_route, QVector<Saving>* route_savings, int cap);

void second_post_processing(GraphRoutes *graph_routes);

int search_insert_index_saving(Saving s, int first, int last, QVector<Saving> & v);
