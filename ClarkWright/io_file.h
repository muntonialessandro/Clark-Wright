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

#ifndef IO_FILE_H
#define IO_FILE_H

#include <QFileDialog>
#include "classes/client.h"
#include "classes/graph_routes.h"

/**
 * Funzioni relative a lettura e salvataggio su file delle route
 */

QVector<Client> read_file(QString filename, int* vehicle_capacity);

bool write_results_in_file(GraphRoutes *route);

#endif // IO_FILE_H
