#include "voronoi.h"

QVector<Client> voronoi (QVector<Client> sites){
    int i;
    QVector<Event> events;
    for (i=0; i<sites.size(); i++) events.push_back(sites[i].to_Event());
    QVector<Event> ordered_events = mergesort_events(events);
    for (i=0; i<ordered_events.size(); i++){
        std::cout << ordered_events[i].to_string() << std::endl;
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
