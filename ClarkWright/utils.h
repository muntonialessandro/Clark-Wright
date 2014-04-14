#ifndef UTILS_H
#define UTILS_H

#include <QVector4D>
#include <QMatrix4x4>
#include <QFile>
#include <sstream>
#include <iostream>
#include <QVector>
#include <QPair>

int binary_search_double(double n, int first, int last, QVector<double> &v);

int search_insert_index_double(double n, int first, int last, QVector<double> &v);

int binary_search_distance_client(QPair<int, double> n, int first, int last, QVector< QPair<int, double> > &v);

int search_insert_index_distance_client(QPair<int, double> n, int first, int last, QVector< QPair<int, double> > &v);

int binary_search_int(int n, int first, int last, QVector<int> &v);

int search_insert_index_int(int n, int first, int last, QVector<int> &v);

QVector<double> merge (QVector<double> &v1, QVector<double> &v2);

QVector<double> mergesort(QVector<double> &v);

double absolute (double num);

#endif // UTILS_H
