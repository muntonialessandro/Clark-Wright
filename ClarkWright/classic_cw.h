#ifndef CLASSICCW_H
#define CLASSICCW_H

#include <QVector>
#include <iostream>

#include "classes/graph_routes.h"
#include "classes/saving.h"
#include "timer.h"
#include "utils.h"
#include "io_file.h"
#include "user_interface/mainwindow.h"

/**
 * Funzioni relative all'algoritmo di risoluzione classico di Clark & Wright
 */
GraphRoutes classic_cw(QVector<Client> &clients, QVector<Saving> &savings, int vehicle_capacity);

int find_true_saving(QVector<Saving> sav);

int check_insert(QVector<client_id> clients_in_route, QVector<Saving> &savings,
                        int savingAttuale, int lastClientInRouteId, GraphRoutes state);

#endif CLASSICCW_H
