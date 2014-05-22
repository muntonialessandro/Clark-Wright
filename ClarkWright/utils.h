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

#ifndef UTILS_H
#define UTILS_H

#include <QVector4D>
#include <QMatrix4x4>
#include <QFile>
#include <sstream>
#include <iostream>
#include <QVector>
#include <QPair>

/**
 * Funzioni utili utilizzate in diverse parti del progetto
 */

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
