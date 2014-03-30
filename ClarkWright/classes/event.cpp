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
    this->associate_circle_event_id = -1;
    this->associate_circle_event = NULL;
    this->has_circle_event = false;
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

bool Event::has_associate_circle_event()
{
    return this->has_circle_event;
}

QLinkedList<Event>::iterator Event::get_associate_circle_event()
{
    if (this->has_circle_event) return this->associate_circle_event;
    else return NULL;
}

int Event::get_associate_circle_event_id()
{
    return this->associate_circle_event_id;
}

void Event::set_associate_circle_event(QLinkedList<Event>::iterator it, int circle_event_id)
{
    this->associate_circle_event = it;
    this->associate_circle_event_id = circle_event_id;
    this->has_circle_event = true;
}

void Event::remove_associate_circle_event()
{
    this->associate_circle_event = NULL;
    this->associate_circle_event_id = -1;
    this->has_circle_event = false;
}

void Event::set_position_in_Q(QLinkedList<Event>::iterator it)
{
    this->position_in_Q = it;
}

std::string Event::to_string()
{
    std::stringstream ss;
    if (event){ // se è un site event
        ss << "Client ID: " << this->client_id << "; Coordinates: (" << this->x << "; " << this->y;
        if (this->has_circle_event) ss << "Associate Circle Event: " << this->associate_circle_event_id << "; ";
        ss << ");";
    }
    else {
        ss << "Circle Event ID: " << this->client_id << "; Coordinates: (" << this->x << "; " << this->y << ");";
    }
    std::string s = ss.str();
    return s;
}

