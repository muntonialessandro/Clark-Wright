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
