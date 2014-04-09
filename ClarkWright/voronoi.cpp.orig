#include "voronoi.h"

/**
 * @brief voronoi
 *  Restituisce i clienti con le relazioni di adiacenza aggiornate
 * @param sites
 * @return
 */
QVector<Client> voronoi (QVector<Client> &sites){
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
        else
            handle_circle_event(iterator, &Q, &T, &sites, &i);

        //Stampa T ad ogni ciclo
        /*std::cout << "Ciclo: " << j << ": Evento analizzato: \n";
        std::cout << "\t" << (*iterator).to_string() << std::endl;
        std::cout << "Ciclo: " << j << ": T: " << std::endl;
        for (k=0; k < T.size(); k++) std::cout << "\t" << T[k].to_string() << std::endl;*/

        //Stampa Q ad ogni ciclo
        /*std::cout << "Ciclo: " << j << ": Q: " << std::endl;
        QLinkedList<Event>::iterator iterator2 = Q.begin();
        while (iterator2 != Q.end()){
            std::cout << "\t" << (*iterator2).to_string() << std::endl;
            iterator2++;
        }*/

        iterator++;
        j++;
    }

    for (i=0; i<sites.size(); i++){
        std::cout << sites[i].to_string() << std::endl;
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

        // controllo se la tripla per cui i+1 è arco sinistro genera un circle event
        if (i+3 < (*T).size()) check_new_circle_event(i+2, i+1, &e, ie, Q, T, id_circle);

        // controllo se la tripla per cui i+1 è arco destro genera un circle event
        if (i > 0) check_new_circle_event(i, i+1, &e, ie, Q, T, id_circle);
    }
}

/**
 * @brief handle_circle_event
 *  Gestione di un Circle Event
 * @param ie
 * @param Q
 * @param T
 * @param id_circle
 */
void handle_circle_event(QLinkedList<Event>::iterator ie, QLinkedList<Event>* Q, QVector<Event>* T, QVector<Client>* sites, int *id_circle){
    
    Event e = *ie;
    
    int arco_sinistro, arco_destro, i;
    
    //Cerco in T gli elementi associati al circle event
    for (i = 0; i < T->size(); i++) {
        
        // Controllo se l'elemento di T è associato al circle event
        if ((*T)[i].get_associate_circle_event_id() == e.get_client_id()) {
            
            arco_sinistro = i-1;
            arco_destro = i;
            
            // Rimuovo l'elemento da T
            T->remove(i);
        }
    }

    // se l'arco trovato ha circle event associati, li elimino (dall'arco in T e dalla coda Q)
    if ((*T)[arco_sinistro].has_associate_circle_event()) { //arco sinistro
        Q->erase((*T)[arco_sinistro].get_associate_circle_event());
        (*T)[arco_sinistro].remove_associate_circle_event();
    }
    if ((*T)[arco_destro].has_associate_circle_event()) { //arco destro
        Q->erase((*T)[arco_destro].get_associate_circle_event());
        (*T)[arco_destro].remove_associate_circle_event();
    }
    
    // il sito associato all'arco destro è vicino del sito associato all'arco sinistro, e viceversa
    client_id client_left = (*T)[arco_sinistro].get_client_id();
    client_id client_right = (*T)[arco_destro].get_client_id();
    (*sites)[client_left].add_neighbor(client_right);
    (*sites)[client_right].add_neighbor(client_left);

    // Se l'arco sinistro è in mezzo ad altri due archi, controllo se generano un circle event
    if (arco_sinistro > 0) {
        if ((*T)[arco_sinistro].has_associate_circle_event()){ // Cancello l'eventuale circle event associato
            QLinkedList<Event>::iterator iter = (*T)[arco_sinistro].get_associate_circle_event();
            Q->erase(iter);
            (*T)[arco_sinistro].remove_associate_circle_event();
        }
        check_new_circle_event(arco_sinistro, arco_sinistro, &e, ie, Q, T, id_circle);
    }
    
    // Se l'arco destro è in mezzo ad altri due archi, controllo se generano un circle event
    if (arco_destro < T->size() - 1) {
        if ((*T)[arco_destro].has_associate_circle_event()){ // Cancello l'eventuale circle event associato
            QLinkedList<Event>::iterator iter = (*T)[arco_destro].get_associate_circle_event();
            Q->erase(iter);
            (*T)[arco_destro].remove_associate_circle_event();
        }
        check_new_circle_event(arco_destro, arco_destro, &e, ie, Q, T, id_circle);
    }
}

/**
 * @brief check_new_circle_event
 *  Controlla se bisogna inserire un nuovo Circle Event data una tripla di archi adiacenti
 * @param arco
 * @param arco_per_distanza
 * @param e
 * @param ie
 * @param Q
 * @param T
 * @param id_circle
 */
void check_new_circle_event(int arco, int arco_per_distanza, Event *e, QLinkedList<Event>::iterator ie, QLinkedList<Event>* Q, QVector<Event>* T, int *id_circle){
    //Se i punti sono allineati, le bisettrici non si incontrno e non generano circle event
    if (!are_allineate((*T)[arco-1], (*T)[arco], (*T)[arco+1])){
        // Si calcola l'intersezione tra le bisettrici
        QPair<double, double> vertex = find_intersection_bisectors((*T)[arco-1], (*T)[arco], (*T)[arco+1]);
        double dist = distance((*T)[arco_per_distanza], vertex); //distanza tra l'intersezione e uno dei punti
        double x = vertex.first; //coordinate del circle event
        double y = vertex.second - dist;
        //Se sto analizzando un circle event che genera un altro circle event con le stesse coordinate, lo scarto.
        if (e->is_site_event() || y == e->get_y() || x == e->get_x()){
            Event ev(-1, vertex.first, e->get_y(), false, false);
            int i = bin_search_parabola(ev, 0, T->size()-1, *T); //cerco l'arco sotto il circle event
            //Se il circle event non sta sotto uno dei tre archi coinvolti, lo scarto
            if (i == (arco-1) || i == arco || i == (arco+1)){
                //Se  il circle event non sta sotto la beach line, lo scarto
                if (is_under_beach_line(vertex, e->get_y(), *T, i)){
                    // Creo il nuovo circle event
                    Event circle_event(*id_circle, x, y, false, false);

                    QLinkedList<Event>::iterator iter = ie;

                    bool stop = true;
                    while (stop && (iter != Q->end())){ //cerco la posizione in Q in cui inserire l'evento
                        if ((*iter).get_y() > y) iter++;
                        else{
                            if (((*iter).get_y() == y) && ((*iter).get_x() < x)) iter++;
                            else stop = false;
                        }
                    }

                    Q->insert(iter, circle_event); //inserisco l'evento
                    iter--;

                    // Associo il circle event al nodo in T
                    (*T)[arco].set_associate_circle_event(iter, *id_circle);

                    (*id_circle)++;
                }
            }
        }
    }
}

/**
 * @brief is_under_beach_line
 *  Controlla se il vertice sta sotto la parabola di indice i
 *  (la parabola dovrebbe essere quella immediatamente sopra)
 * @param vertex
 * @param sweep_line
 * @param T
 * @param i
 * @return
 */
bool is_under_beach_line (QPair<double, double> & vertex, double sweep_line, QVector<Event> &T, int i){
    std::vector<double> parabola = calculate_parabola(T[i], sweep_line);
    double beach_line = (parabola[0] * pow(vertex.first,2)) + (parabola[1] * vertex.first) + parabola[2];
    if (vertex.second < beach_line) return true;
    else return false;
}

/**
 * @brief are_allineate
 *  restituisce true se tre eventi sono allineati
 * @param p1
 * @param p2
 * @param p3
 * @return
 */
bool are_allineate(Event & p1, Event & p2, Event & p3){
    double a[3][3];
    double determinant = 0;
    a[0][0] = p1.get_x();
    a[0][1] = p1.get_y();
    a[0][2] = 1;
    a[1][0] = p2.get_x();
    a[1][1] = p2.get_y();
    a[1][2] = 1;
    a[2][0] = p3.get_x();
    a[2][1] = p3.get_y();
    a[2][2] = 1;

    determinant = (a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2])
                  -a[1][0] * (a[0][1] * a[2][2] - a[2][1] * a[0][2])
                  +a[2][0] * (a[0][1] * a[1][2] - a[1][1] * a[0][2]));
    if (determinant == 0) return true;
    else return false;
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
int bin_search_parabola(Event & e, int first, int last, QVector<Event> &T){
    if (first == last) return first;
    else {
        double intersection;
        int mid = (first + last) / 2;
        std::vector<double> p_left;
        std::vector<double> p_right;
        std::vector<double> intersections;
        if (T[mid].get_y() != e.get_y())
            p_left = calculate_parabola(T[mid], e.get_y());
        if (T[mid+1].get_y() != e.get_y())
            p_right = calculate_parabola(T[mid+1], e.get_y());
        if (p_left.empty() || p_right.empty()){
            if (p_left.empty()){
                intersections.push_back(T[mid].get_x());
                intersections.push_back(T[mid].get_x());
            }
            if (p_right.empty()){
                intersections.push_back(T[mid+1].get_x());
                intersections.push_back(T[mid+1].get_x());
            }
        }
        else intersections = find_intersections_parabolas(p_left, p_right);

        if (intersections.empty()) {
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
                return mid;
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
std::vector<double> calculate_parabola (Event & focus, double directrix){
    double fx = focus.get_x();
    double fy = focus.get_y();
    std::vector<double> parabola;
    double a = 1 / (2*fy - 2*directrix);
    parabola.push_back(a);
    double b = ((-2 * fx) / (2*fy - 2*directrix));
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
std::vector<double> find_intersections_parabolas (std::vector<double> &p1, std::vector<double> &p2){
    std::vector<double> solutions;
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
std::vector<double> calculate_bisector(Event &p1, Event &p2)
{
    std::vector<double> bisector;
    //Punto medio:
    double xm = (p1.get_x() + p2.get_x()) / 2.0;
    double ym = (p1.get_y() + p2.get_y()) / 2.0;
    //se i punti sono allineati orizzontalmente: bisettrice verticale, della forma x = n
    if ((p2.get_y() - p1.get_y()) == 0)  {
        bisector.push_back(xm);
        return bisector;
    }
    else {
        double rm;
        double m;
        // se i punti sono allineati verticalmente: bisettrice orizzontale, della forma y = 0x + q
        if ((p2.get_x() - p1.get_x()) == 0) m = 0;
        else {
            rm = (p2.get_y() - p1.get_y()) / (p2.get_x() - p1.get_x());
            m = -1.0 / rm;
        }

        bisector.push_back(m);
        //q bisettrice:
        double q = (-m) * xm + ym;
        bisector.push_back(q);
        return bisector;
    }
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
QPair<double, double> find_intersection_bisectors(Event &p1, Event &p2, Event &p3){
    std::vector<double> r1 = calculate_bisector(p1, p2);
    std::vector<double> r2 = calculate_bisector(p2, p3);
    QPair<double, double> point;
    if (r1.size() == 1 || r2.size() == 1){
        if (r1.size() == 1){
            point.first = r1[0];
            point.second = r2[0] * r1[0] + r2[1];
        }
        else {
            point.first = r2[0];
            point.second = r1[0] * r2[0] + r1[1];
        }
    }
    else {
        double x = (r2[1] - r1[1]) / (r1[0] - r2[0]);
        double y = (r1[0] * x) + r1[1];
        point.first = x;
        point.second = y;
        return point;
    }
}

/**
 * @brief distance
 *  Restituisce la distanza tra un evento e un vertice
 * @param e
 * @param p
 * @return
 */
double distance(Event &e, QPair<double, double> &p){
    double e_x = e.get_x();
    double e_y = e.get_y();
    double p_x = p.first;
    double p_y = p.second;
    //distanza euclidea tra i due punti:
    double dist = pow((p_x - e_x),2) + pow((p_y - e_y),2);
    dist = sqrt(dist);
    return dist;
}

/**
 * @brief mergesort_events
 * @param v
 * @return
 */
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
 * @brief merge_events
 *  Dati due vettori ordinati, li fonde
 * @param v1
 * @param v2
 * @return
 */
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
                        if (v1[i].get_x() >= v2[j].get_x()){
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
