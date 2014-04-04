#ifndef VORONOI_H
#define VORONOI_H

#include "classes/event.h"
#include "classes/client.h"
#include <math.h>
#include <QPoint>
#include <QVector3D>
#include <QMatrix3x3>

QVector<Client> voronoi (QVector<Client> &sites);

void handle_site_event(QLinkedList<Event>::iterator ie, QLinkedList<Event>* Q, QVector<Event>* T, QVector<Client> *sites, int *id_circle);

void handle_circle_event(QLinkedList<Event>::iterator ie, QLinkedList<Event>* Q, QVector<Event>* T, QVector<Client>* sites, int *id_circle);

void check_new_circle_event(int arco, int arco_per_distanza, Event *e, QLinkedList<Event>::iterator ie, QLinkedList<Event>* Q, QVector<Event>* T, int *id_circle);

bool is_under_beach_line (QPair<double, double> &vertex, double sweep_line, QVector<Event> &T, int i);

bool are_allineate(Event &p1, Event &p2, Event &p3);

int bin_search_parabola(Event &e, int first, int last, QVector<Event> &T);

std::vector<double> calculate_parabola (Event &focus, double directrix);

std::vector<double> find_intersections_parabolas (std::vector<double> &p1, std::vector<double> &p2);

std::vector<double> calculate_bisector(Event &p1, Event &p2d);

QPair<double, double> find_intersection_bisectors(Event &p1, Event &p2, Event &p3);

double distance(Event &e, QPair<double, double> &p);

QVector<Event> mergesort_events(QVector<Event> &v);

QVector<Event> merge_events(QVector<Event> &v1, QVector<Event> &v2);

#endif // VORONOI_H
