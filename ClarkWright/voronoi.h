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

#ifndef VORONOI_H
#define VORONOI_H

#include "classes/event.h"
#include "classes/client.h"
#include "classes/saving.h"
#include <math.h>
#include <QPoint>
#include <QVector3D>
#include <QMatrix3x3>
#include <cmath>

/**
 * Funzioni utilizzate per il calcolo del diagramma di Voronoi
 */

QVector<Client> voronoi (QVector<Client> &sites, QVector<Saving> *savings);

void handle_site_event(QLinkedList<Event>::iterator ie, QLinkedList<Event>* Q, QVector<Event>* T, QVector<Client> *sites, int *id_circle, Event &deposit, QVector<Saving>* savings);

void handle_circle_event(QLinkedList<Event>::iterator ie, QLinkedList<Event>* Q, QVector<Event>* T, QVector<Client>* sites, int *id_circle, Event &deposit, QVector<Saving>* savings);

void check_new_circle_event(int arco, int arco_per_distanza, Event *e, QLinkedList<Event>::iterator ie, QLinkedList<Event>* Q, QVector<Event>* T, int *id_circle);

bool is_under_beach_line (QPair<double, double> &vertex, double sweep_line, QVector<Event> &T, int i);

bool are_allineate(Event &p1, Event &p2, Event &p3);

int are_visited_generators(QVector<Event> generators, QVector<Event> &T, int arco);

int bin_search_parabola(Event &e, int first, int last, QVector<Event> &T);

std::vector<double> calculate_parabola (Event &focus, double directrix);

std::vector<double> find_intersections_parabolas (std::vector<double> &p1, std::vector<double> &p2);

std::vector<double> calculate_bisector(Event &p1, Event &p2d);

QPair<double, double> find_intersection_bisectors(Event &p1, Event &p2, Event &p3);

double vertex_distance(Event &e, QPair<double, double> &p);

double events_distance(Event &e1, Event &e2);

double get_saving(Event &c1, Event &c2, Event &deposit);

int search_insert_index_saving(double n, int first, int last, QVector<Saving> & v);

QVector<Event> mergesort_events(QVector<Event> &v);

QVector<Event> merge_events(QVector<Event> &v1, QVector<Event> &v2);

#endif // VORONOI_H
