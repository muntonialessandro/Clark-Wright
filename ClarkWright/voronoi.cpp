#include "voronoi.h"

/**
 * @brief voronoi
 *  Restituisce i clienti con le relazioni di adiacenza aggiornate
 * @param sites
 * @return
 */
QVector<Client> voronoi (QVector<Client> sites){
    int i, k;
    QVector<Event> events;
    for (i=0; i<sites.size(); i++) events.push_back(sites[i].to_Event());
    QVector<Event> ordered_events = mergesort_events(events);

    //for (i=0; i<ordered_events.size(); i++) std::cout << ordered_events[i].to_string() << std::endl;

    QLinkedList<Event> Q;
    for (i=0; i<ordered_events.size(); i++) {
        Q.push_front(ordered_events[i]);
        QLinkedList<Event>::iterator iterator = Q.begin();
        (*iterator).set_position_in_Q(iterator);
    }

    //Da questo momento, i sarà utilizzata per gli id da associare ai circle event
    QVector<Event> T;
    int j = 0;
    QLinkedList<Event>::iterator iterator = Q.begin();
    while (iterator != Q.end()){
        if ((*iterator).is_site_event())
            handle_site_event(iterator, &Q, &T, &sites, &i);
        else ;

        iterator++;

        /*std::cout << "Ciclo: " << j << ": Q: " << std::endl;
        //for (k=0; k < T.size(); k++) std::cout << "\t" << T[k].to_string() << std::endl;

        QLinkedList<Event>::iterator iterator2 = Q.begin();
        while (iterator2 != Q.end()){
            std::cout << "\t" << (*iterator2).to_string() << std::endl;
            iterator2++;
        }

        j++;*/
    }

    return sites;
}

/**
 * @brief handle_site_event
 *  Gestisce un site event
 * @param e
 * @param Q
 * @param T
 * @param sites
 */
void handle_site_event(QLinkedList<Event>::iterator ie, QLinkedList<Event>* Q, QVector<Event>* T, QVector<Client>* sites, int* id_circle){
    Event e = *ie;
    if (T->size() == 0) T->push_back(e);
    else {
        // cerco in T l'arco di parabola i immediatamente sopra il site event e
        int i = bin_search_parabola(e, 0, T->size()-1, *T);
        // se l'arco trovato ha circle event associati, li elimino (dall'arco in T e dalla coda Q)
        if ((*T)[i].has_associate_circle_event()) {
            std::cout << (*T)[i].get_associate_circle_event()->to_string() << std::endl;
            Q->erase((*T)[i].get_associate_circle_event());
            (*T)[i].remove_associate_circle_event();
        }
        // il sito associato all'arco i è vicino del site event e, e viceversa
        client_id client_event = e.get_client_id();
        client_id client_neighbor = (*T)[i].get_client_id();
        (*sites)[client_event].add_neighbor(client_neighbor);
        (*sites)[client_neighbor].add_neighbor(client_event);
        // inserisco due archi: a destra di i metto e, e a destra di e metto di nuovo i
        T->insert(i+1, e);
        T->insert(i+2, (*T)[i]);
        // tripla per cui i+1 è arco sinistro
        if (i+3 < (*T).size()) {
            QLinkedList<Event>::iterator it = ie;
            QPoint vertex = find_intersection_bisectors((*T)[i+1], (*T)[i+2], (*T)[i+3]);
            if (vertex.y() < e.get_y()){ //se l'intersezione è sotto la sweep line
                double dist = distance((*T)[i+1], vertex);
                double x = vertex.x(); //coordinate del circle event
                double y = vertex.y() - dist;
                Event circle_event(*id_circle, x, y, false, false);
                bool stop = true;
                while (stop){ //cerco la posizione in Q in cui inserire l'evento
                    if ((*it).get_y() < y) it++;
                    else{
                        if (((*it).get_y() == y) && ((*it).get_x() < x)) it++;
                        else stop = false;
                    }
                }
                it--;
                Q->insert(it, circle_event); //inserisco l'evento
                (*T)[i+2].set_associate_circle_event(it, *id_circle); //associo all'arco i+2 (centrale) il circle event
                (*id_circle)++;
            }
        }
        // tripla per cui i+1 è arco destro
        if (i > 0) {
            QLinkedList<Event>::iterator it = ie;
            QPoint vertex = find_intersection_bisectors((*T)[i-1], (*T)[i], (*T)[i+1]);
            if (vertex.y() < e.get_y()){ //se l'intersezione è sotto la sweep line
                double dist = distance((*T)[i+1], vertex);
                double x = vertex.x(); //coordinate circle event
                double y = vertex.y() - dist;
                Event circle_event(*id_circle, x, y, false, false);
                bool stop = true;
                while (stop){ //cerco la posizione in Q in cui inserire l'evento
                    if ((*it).get_y() < y) it++;
                    else{
                        if (((*it).get_y() == y) && ((*it).get_x() < x)) it++;
                        else stop = false;
                    }
                }
                it--;
                Q->insert(it, circle_event); //inserisco l'evento
                (*T)[i].set_associate_circle_event(it, *id_circle); //associo all'arco i (centrale) il circle event
                (*id_circle)++;
            }
        }
    }
}

/**
 * @brief bin_search_parabola
 *  Effettua una ricerca binaria in T dell'arco di parabola immediatamente superiore
 *  all'evento e. Restituisce l'indice dell'arco trovato.
 * @param e
 * @param first
 * @param last
 * @param T
 * @return
 */
int bin_search_parabola(Event e, int first, int last, QVector<Event> &T){
    if (first == last) return first;
    else {
        double intersection;
        int mid = (first + last) / 2;
        QVector<double> p_left;
        QVector<double> p_right;
        QVector<double> intersections;
        if (T[mid].get_y() != e.get_y())
            p_left = calculate_parabola(T[mid], e.get_y());
        if (T[mid+1].get_y() != e.get_y())
            p_right = calculate_parabola(T[mid+1], e.get_y());
        if (p_left.isEmpty() || p_right.isEmpty()){
            if (p_left.isEmpty()){
                intersections.push_back(T[mid].get_x());
                intersections.push_back(T[mid].get_x());
            }
            if (p_right.isEmpty()){
                intersections.push_back(T[mid+1].get_x());
                intersections.push_back(T[mid+1].get_x());
            }
        }
        else intersections = find_intersections_parabolas(p_left, p_right);
        if (intersections.isEmpty()) {
            std::cout << "Le parabole non hanno intersezioni: ?????" << std::endl;
            return -1;
        }
        else {
            if (intersections[0] == intersections[1]) intersection = intersections[0];
            else {
                if (T[mid].get_y() > T[mid+1].get_y()){
                    if (intersections[0] < intersections[1]) intersection = intersections[0];
                    else intersection = intersections[1];
                }
                if (T[mid].get_y() < T[mid+1].get_y()){
                    if (intersections[0] > intersections[1]) intersection = intersections[0];
                    else intersection = intersections[1];
                }
            }
            if (e.get_x() < intersection){
                return bin_search_parabola(e, first, mid, T);
            }
            if (e.get_x() > intersection){
                return bin_search_parabola(e, mid+1, last, T);
            }
            if (e.get_x() == intersection){
                std::cout << "Merda: evento sotto un breakpoint!" << std::endl;
                return -1;
            }
        }
    }

}

/**
 * @brief calculate_parabola
 *  Restituisce l'equazione della parabola dati punto di fuoco e direttrice.
 *  L'equazione è della forma y=ax^2 + bx + c, dove:
 *  parabola[0] = a;
 *  parabola[1] = b;
 *  parabola[2] = c;
 * @param focus
 * @param directrix
 * @return
 */
QVector<double> calculate_parabola (Event focus, double directrix){
    double fx = focus.get_x();
    double fy = focus.get_y();
    QVector<double> parabola;
    double a = 1 / (2*fy - 2*directrix);
    parabola.push_back(a);
    double b = - ((2 * fx) / (2*fy - 2*directrix));
    parabola.push_back(b);
    double c = (pow(fx, 2) + pow(fy, 2) - pow(directrix, 2)) / (2*fy - 2*directrix);
    parabola.push_back(c);
    return parabola;
}

/**
 * @brief find_intersections_parabolas
 *  Calcola le intersezioni tra due parabole, le cui equazioni sono passate come vettori.
 *  Restituisce un array di due elementi, contenente appunto le due intersezioni.
 * @param p1
 * @param p2
 * @return
 */
QVector<double> find_intersections_parabolas (QVector<double> p1, QVector<double> p2){
    QVector<double> solutions;
    double a = p1[0] - p2[0];
    double b = p1[1] - p2[1];
    double c = p1[2] - p2[2];
    double delta = (pow(b,2) - 4*a*c);
    if (delta < 0) return solutions;
    double s1 = (- b + sqrt(delta)) / (2 * a);
    double s2 = (- b - sqrt(delta)) / (2 * a);
    solutions.push_back(s1);
    solutions.push_back(s2);
    return solutions;
}

/**
 * @brief calculate_bisector
 *  Dati due punti, restituisce l'equazione della retta bisettrice.
 *  L'equazione della retta è nella forma y = mx + q, dove
 *  bisector[0] = m;
 *  bisector[1] = q.
 * @param p1
 * @param p2
 * @return
 */
QVector<double> calculate_bisector(Event p1, Event p2)
{
    QVector<double> bisector;
    //Punto medio:
    double xm = (p1.get_x() + p2.get_x()) / 2;
    double ym = (p1.get_y() + p2.get_y()) / 2;
    //coeff. angolare retta passante per p1 e p2
    double rm = (p2.get_y() - p1.get_y()) / (p2.get_x() - p1.get_x());
    //coeff. angolare retta bisettrice:
    double m = -1 / rm;
    bisector.push_back(m);
    //q bisettrice:
    double q = -m * xm + ym;
    bisector.push_back(q);
    return bisector;
}

/**
 * @brief find_intersection_bisectors
 *  Restituisce il punto di intersezione delle due bisettrici generate dai punti
 *  passati in ingresso.
 * @param p1
 * @param p2
 * @param p3
 * @return
 */
QPoint find_intersection_bisectors(Event p1, Event p2, Event p3){
    QVector<double> r1 = calculate_bisector(p1, p2);
    QVector<double> r2 = calculate_bisector(p2, p3);
    double x = (r2[1] - r1[1]) / (r1[0] - r2[0]);
    double y = (r1[0] * x) + r1[1];
    return QPoint(x,y);
}

double distance(Event e, QPoint p){
    double e_x = e.get_x();
    double e_y = e.get_y();
    double p_x = p.x();
    double p_y = p.y();
    //distanza euclidea tra i due punti:
    double dist = pow((p_x - e_x),2) + pow((p_y - e_y),2);
    dist = sqrt(dist);
    return dist;
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
