#ifndef UTILS_H
#define UTILS_H

#include <QVector4D>
#include <QMatrix4x4>
#include <QFile>
#include <sstream>
#include "classes/client.h"
#include <iostream>
#include <QVector>

int binary_search(double n, int first, int last, QVector<double> &v);

int search_insert_index(double n, int first, int last, QVector<double> &v);

QVector<double> merge (QVector<double> &v1, QVector<double> &v2);

QVector<double> mergesort(QVector<double> &v);

QVector<Client> read_file(QString filename, int* vehicle_capacity);

#endif // UTILS_H
