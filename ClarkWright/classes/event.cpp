#include "event.h"

Event::Event()
{   
}

Event::Event(int client_id, double x, double y, bool deposit, bool event)
{
    this->client_id = client_id;
    this->x = x;
    this->y = y;
    this->deposit = deposit;
    this->event = event;
    this->circle_events.clear();
}

double Event::get_x()
{
    return this->x;
}

double Event::get_y()
{
    return this->y;
}

bool Event::is_deposit()
{
    return this->deposit;
}

bool Event::is_site_event()
{
    return this->event;
}

int Event::get_client_id()
{
    return this->client_id;
}

