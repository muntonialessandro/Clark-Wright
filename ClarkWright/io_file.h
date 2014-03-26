#ifndef IO_FILE_H
#define IO_FILE_H

#include "classes/client.h"

QVector<Client> read_file(QString filename, int* vehicle_capacity);

#endif // IO_FILE_H
