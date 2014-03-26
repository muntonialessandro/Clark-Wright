#ifndef EVENT_H
#define EVENT_H

#include <QVector>
#include <QLinkedList>
#include <sstream>


/**
 * @brief The Event class
 *  Classe per modellare gli Event-Point nella costruzione del diagramma di Voronoi
 */
class Event
{
public:
    Event();
    Event(int client_id, double x, double y, bool deposit, bool event);
    double get_x();
    double get_y();
    bool is_deposit();
    bool is_site_event();
    int get_client_id();
    std::string to_string();

private:
    int client_id;
    double x;
    double y;
    bool deposit; //true: è il deposito
    bool event; //true: SiteEvent, false: CircleEvent
    QVector<QLinkedList<Event>::const_iterator> circle_events;
};

#endif // EVENT_H
