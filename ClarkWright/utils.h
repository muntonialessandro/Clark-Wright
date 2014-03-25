#ifndef UTILS_H
#define UTILS_H

#endif // UTILS_H

#include <QVector4D>
#include <QMatrix4x4>

int binary_search(double n, int first, int last, QVector<double> &v);

int search_insert_index(double n, int first, int last, QVector<double> &v);

QVector<double> merge (QVector<double> &v1, QVector<double> &v2);

QVector<double> mergesort(QVector<double> &v);
