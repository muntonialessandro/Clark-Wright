#include "event.h"

Event::Event()
{   
}

/**
 * @brief Event::Event
 *  Crea un evento avente i dati passati come parametro.
 *  Alla creazione non avrà circle event associati.
 * @param client_id
 * @param x
 * @param y
 * @param deposit
 * @param event
 */
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

/**
 * @brief Event::operator ==
 *  Confronto di uguaglianza tra Eventi, effettuato esclusivamente sul client id
 * @param other
 * @return
 */
bool Event::operator ==(Event &other) const
{
    if (other.get_client_id() == this->client_id) return true;
    return false;
}

/**
 * @brief Event::operator !=
 *  Due Eventi sono diversi quando non sono uguali!
 * @param other
 * @return
 */
bool Event::operator !=(Event &other) const
{
    return !(*this == other);
}

/**
 * @brief Event::get_x
 *  Restituisce la coordinata x dell'evento
 * @return
 */
double Event::get_x()
{
    return this->x;
}

/**
 * @brief Event::get_y
 *  Restituisce la coordinata y dell'evento
 * @return
 */
double Event::get_y()
{
    return this->y;
}

/**
 * @brief Event::is_deposit
 *  Restituisce true se l'evento è il deposito, false altrimenti
 * @return
 */
bool Event::is_deposit()
{
    return this->deposit;
}

/**
 * @brief Event::is_site_event
 *  Restituisce true se l'evento è un site event, false se è un circle event
 * @return
 */
bool Event::is_site_event()
{
    return this->event;
}

/**
 * @brief Event::get_client_id
 *  Restituisce il client_id dell'evento
 * @return
 */
int Event::get_client_id()
{
    return this->client_id;
}

/**
 * @brief Event::has_associate_circle_event
 *  Restituisce true se l'evento ha un circle event associato
 * @return
 */
bool Event::has_associate_circle_event()
{
    return this->has_circle_event;
}

/**
 * @brief Event::get_associate_circle_event
 *  Restituisce il puntatore al circle event associato all'evento
 * @return
 */
QLinkedList<Event>::iterator Event::get_associate_circle_event()
{
    if (this->has_circle_event) return this->associate_circle_event;
    else return NULL;
}

/**
 * @brief Event::get_associate_circle_event_id
 *  Restituisce l'id del circle event associato all'evento
 * @return
 */
int Event::get_associate_circle_event_id()
{
    return this->associate_circle_event_id;
}

/**
 * @brief Event::set_associate_circle_event
 *  Setta il circle event associato all'evento
 * @param it
 * @param circle_event_id
 */
void Event::set_associate_circle_event(QLinkedList<Event>::iterator it, int circle_event_id)
{
    this->associate_circle_event = it;
    this->associate_circle_event_id = circle_event_id;
    this->has_circle_event = true;
}

/**
 * @brief Event::remove_associate_circle_event
 *  Rimuove il circle event associato all'evento
 */
void Event::remove_associate_circle_event()
{
    this->associate_circle_event = NULL;
    this->associate_circle_event_id = -1;
    this->has_circle_event = false;
}

/**
 * @brief Event::set_position_in_Q
 *  Setta il puntatore all'evento stesso in Q
 * @param it
 */
void Event::set_position_in_Q(QLinkedList<Event>::iterator it)
{
    this->position_in_Q = it;
}

/**
 * @brief Event::add_generator
 *  Aggiunge un arco generatore all'evento
 * @param e1
 */
void Event::add_generator(Event e1)
{
    this->generators.push_back(e1);
}

/**
 * @brief Event::get_generators
 *  Restituisce l'array di archi generatori dell'evento
 * @return
 */
QVector<Event> Event::get_generators()
{
    return this->generators;
}
/**
 * @brief Event::get_overlying
 *  Restituisce l'array di eventi sovrapposti
 * @return
 */
QVector<int> Event::get_overlying()
{
    return this->overlying;
}

/**
 * @brief Event::has_overlying
 *  Restituisce true se l'evento ha eventi sovrapposti
 * @return
 */
bool Event::has_overlying()
{
    return !(this->overlying.empty());
}

/**
 * @brief Event::add_overlying
 *  Aggiunge un evento sovrapposto all'evento
 * @param id
 */
void Event::add_overlying(int id)
{
    this->overlying.push_back(id);
}

/**
 * @brief Event::to_string
 *  Restituisce una stringa riepilogativa rappresentante l'evento
 * @return
 */
std::string Event::to_string()
{
    std::stringstream ss;
    if (event){ // se è un site event
        ss << "Client ID: " << this->client_id << "; Coordinates: (" << this->x << "; " << this->y << ")";
        if (this->has_circle_event) ss << "; Associate Circle Event: " << this->associate_circle_event_id;
        ss << "; ";
    }
    else {
        ss << "Circle Event ID: " << this->client_id << "; Coordinates: (" << this->x << "; " << this->y << ");";
    }
    std::string s = ss.str();
    return s;
}

