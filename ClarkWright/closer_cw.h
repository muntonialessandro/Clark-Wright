#include "classes/graph_routes.h"
#include "classes/saving.h"

GraphRoutes closer_cw(QVector<Client> &sites, QVector<Saving> &savings, int cap);

GraphRoutes best_closer_cw(QVector<Client> &sites, QVector<Saving> &savings, int cap);
