#ifndef IO_FILE_H
#define IO_FILE_H

#include <QFileDialog>
#include "classes/client.h"
#include "classes/graph_routes.h"

QVector<Client> read_file(QString filename, int* vehicle_capacity);

bool write_results_in_file(GraphRoutes *route);

#endif // IO_FILE_H
