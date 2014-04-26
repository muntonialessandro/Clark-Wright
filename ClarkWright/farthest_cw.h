#ifndef FARTHESTCW_H
#define FARTHESTCW_H

#include <QVector>
#include <iostream>

#include "classes/graph_routes.h"
#include "classes/saving.h"
#include "timer.h"
#include "utils.h"
#include "io_file.h"
#include "user_interface/mainwindow.h"

using namespace std;

/*
 * Implementazione dell'algoritmo di base.
 */
GraphRoutes FarthestCW(QVector<Client> &clients, QVector<Saving> &savings, int vehicle_capacity);

/*
 * Verifica se ci sono ancora saving da processare.
 */
int cercaSavingTrue(QVector<Saving> sav);

/*
 * Verifica se è possibile inserire il savingAttuale nella routeAttuale
 * oppure i client del saving e della route non sono compatibili.
 */
int verificaInserimento(QVector<client_id> clients_in_route, QVector<Saving> &savings,
                        int savingAttuale, int lastClientInRouteId, GraphRoutes state);

#endif // FARTHESTCW_H
