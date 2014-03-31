#ifndef VORONOI_H
#define VORONOI_H

#include "classes/event.h"
#include "classes/client.h"
#include <math.h>
#include <QPoint>

QVector<Client> voronoi (QVector<Client> sites);

void handle_site_event(QLinkedList<Event>::iterator ie, QLinkedList<Event>* Q, QVector<Event>* T, QVector<Client> *sites, int *id_circle);

void handle_cirlce_event(QLinkedList<Event>::iterator ie, QLinkedList<Event>* Q, QVector<Event>* T, int *id_circle);

void check_new_circle_event(int arco, int arco_per_distanza, Event *e, QLinkedList<Event>::iterator ie, QLinkedList<Event>* Q, QVector<Event>* T, int *id_circle);

int bin_search_parabola(Event e, int first, int last, QVector<Event> &T);

QVector<double> calculate_parabola (Event focus, double directrix);

QVector<double> find_intersections_parabolas (QVector<double> p1, QVector<double> p2);

QVector<double> calculate_bisector(Event p1, Event p2d);

QPoint find_intersection_bisectors(Event p1, Event p2, Event p3);

double distance(Event e, QPoint p);

QVector<Event> mergesort_events(QVector<Event> &v);

QVector<Event> merge_events(QVector<Event> &v1, QVector<Event> &v2);

#endif // VORONOI_H
