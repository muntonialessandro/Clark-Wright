#ifndef VORONOI_H
#define VORONOI_H

#include "classes/event.h"
#include "classes/client.h"

QVector<Client> voronoi (QVector<Client> sites);

QVector<Event> merge_events(QVector<Event> &v1, QVector<Event> &v2);

QVector<Event> mergesort_events(QVector<Event> &v);

#endif // VORONOI_H
