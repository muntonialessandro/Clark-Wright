#include "voronoi.h"

QVector<Client> voronoi (QVector<Client> sites){
    int i;
    QVector<Event> events;
    for (i=0; i<sites.size(); i++) events.push_back(sites[i].to_Event());
    QVector<Event> ordered_events = mergesort_events(events);

    QLinkedList<Event> Q;
    for (i=0; i<ordered_events.size(); i++) Q.append(ordered_events[i]);
    QVector<Event> T;

    QLinkedListIterator<Event> Qiterator(Q);
    Event actual_event;
    // scorrere Q dal primo all'ultimo elemento
    while ( Qiterator.hasNext() ) {
        // per ogni elemento verificare se è un circle o un site event con le funzioni della classe event

        actual_event = Qiterator.peekNext();
        if ( actual_event.is_site_event() ) { // se è un site event verrà chiamata HandleSiteEvent......

            // HandleSiteEvent

        }else { // altrimenti cirle event verrà chiamata HandleCircleEvent......

            // HandleCircleEvent
        }

        // passa al successivo
        Qiterator.next();
    }



    return sites;
}

QVector<Event> merge_events(QVector<Event> &v1, QVector<Event> &v2){
    QVector<Event> merge;
    int i=0 ,j=0; // indici: i scorre l'array v1, j scorre l'array v2
    int sizev1 = v1.size();
    int sizev2 = v2.size();
    while (i != sizev1  ||  j != sizev2){ // finché entrambi gli indici non hanno raggiungo l'ultimo elemento degli array
        if (i == sizev1){ // se i ha raggiunto l'ultimo elemento di v1 (e j no)
            for (; j<sizev2; j++) merge.push_back(v2[j]); // copio i restanti elementi di v2 nell'array merge
        }
        else {
            if (j == sizev2){ // se j ha raggiunto l'ultimo elemento di v2 (e i no)
                for (; i<sizev1; i++) merge.push_back(v1[i]); // copio i restanti elementi di v1 nell'array merge
            }
            else { // altrimenti, sia i che j non hanno ancora raggiunto l'ultimo elemento
                if (v1[i].get_y() < v2[j].get_y()){ // se l'elemento i di v1 è minore o uguale dell'elemento j di v2
                    merge.push_back(v1[i]); // inserisco v1[i] nell'array merge
                    i++; // incremento i
                }
                else { // altrimenti
                    if (v1[i].get_y() == v2[j].get_y()){
                        if (v1[i].get_x() <= v2[j].get_x()){
                            merge.push_back(v1[i]); // inserisco v1[i] nell'array merge
                            if (v1[i].get_x() == v2[j].get_x()) j++;
                            i++; // incremento i
                        }
                        else {
                            merge.push_back(v2[j]); // inserisco v2[j] nell'array merge
                            j++; // incremento j
                        }
                    }
                    else {
                        merge.push_back(v2[j]); // inserisco v2[j] nell'array merge
                        j++; // incremento j
                    }
                }
            }
        }

    }
    return merge;
}

QVector<Event> mergesort_events(QVector<Event> &v){
    int size = v.size();
    if (size > 1) {
        QVector<Event> v1 = v.mid(0, size/2);
        QVector<Event> v2 = v.mid(size/2, size-(size/2));
        QVector<Event> r1 = mergesort_events(v1);
        QVector<Event> r2 = mergesort_events(v2);
        QVector<Event> r = merge_events(r1, r2);
        return r;
    }
    else return v;

}

/**
 * @brief binary_search_events
 *  Effettua una ricerca binaria di n sull'array ordinato v.
 *  Restituisce -1 se n non è presente nell'array.
 * @param n
 * @param first
 * @param last
 * @param v
 * @return
 */
int binary_search_events(Event n, int first, int last, QVector<Event> &v)
{
    int mid;
    if (first <= last){
        mid = (first + last) / 2;
        if (v[mid].get_x() < n.get_x()) return (search_insert_index_events (n, mid+1, last, v) );
        if (v[mid].get_x() == n.get_x()) {
            if (v[mid].get_y() < n.get_y()) return (search_insert_index_events (n, mid+1, last, v) );
            if (v[mid].get_y() == n.get_y()) return mid;
            if (v[mid].get_y() > n.get_y()) return (search_insert_index_events (n, first, mid-1, v) );
        }
        if (v[mid].get_x() > n.get_x()) return (search_insert_index_events (n, first, mid-1, v) );
    }
    return -1;
}


/**
 * @brief search_insert_index_events
 *  Effettua una ricerca binaria di n sull'array ordinato v,
 *  e restituisce l'indice del primo elemento nell'array
 *  >= a n.
 * @param n
 * @param first
 * @param last
 * @param v
 * @return
 */
int search_insert_index_events(Event n, int first, int last, QVector<Event> &v)
{
    int mid;
    if (first <= last){
        mid = (first + last) / 2;
        if (v[mid].get_x() < n.get_x()) return (search_insert_index_events (n, mid+1, last, v) );
        if (v[mid].get_x() == n.get_x()) {
            if (v[mid].get_y() < n.get_y()) return (search_insert_index_events (n, mid+1, last, v) );
            if (v[mid].get_y() == n.get_y()) return mid;
            if (v[mid].get_y() > n.get_y()) return (search_insert_index_events (n, first, mid-1, v) );
        }
        if (v[mid].get_x() > n.get_x()) return (search_insert_index_events (n, first, mid-1, v) );
    }
    return first;
}
