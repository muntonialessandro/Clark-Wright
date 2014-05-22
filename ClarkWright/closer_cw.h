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

#include "classes/graph_routes.h"
#include "classes/saving.h"

/**
 * Funzioni relative agli algoritmi di risoluzione del problema VRP
 */

GraphRoutes closer_cw(QVector<Client> &sites, QVector<Saving> savings, int cap);

GraphRoutes create_route(GraphRoutes graph_route, QVector<Saving> &savings, client_id first_client, client_id second_client, int cap);

GraphRoutes second_closer_cw(QVector<Client> &sites, QVector<Saving> savings, int cap);

GraphRoutes last_distance_based_closer_cw(QVector<Client> &sites, QVector<Saving> savings, int cap);

GraphRoutes first_distance_based_closer_cw(QVector<Client> &sites, QVector<Saving> savings, int cap);

void update_savings(Client c_route, Client c_next, GraphRoutes &graph_route, QVector<Saving>* route_savings);

void transfer_clients_post_processing(GraphRoutes *graph_routes,  int cap);

void update_savings_post_processing(Client c_route, Client c_next, GraphRoutes &graph_route, QVector<Saving>* route_savings, int cap);

void second_post_processing(GraphRoutes *graph_routes);

int search_insert_index_saving(Saving s, int first, int last, QVector<Saving> & v);
