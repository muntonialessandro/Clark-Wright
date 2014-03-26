#ifndef VORONOI_H
#define VORONOI_H

#include "classes/event.h"
#include "classes/client.h"

QVector<Client> voronoi (QVector<Client> sites);

void hadnle_site_event(Event e, QLinkedList<Event>* Q, QVector<Event>* T);

QVector<Event> merge_events(QVector<Event> &v1, QVector<Event> &v2);

QVector<Event> mergesort_events(QVector<Event> &v);

int binary_search_events(Event n, int first, int last, QVector<Event> &v);

int search_insert_index_events(Event n, int first, int last, QVector<Event> &v);

#endif // VORONOI_H
