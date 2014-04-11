#include "closer_cw.h"

GraphRoutes closer_cw(QVector<Client> &sites, QVector<Saving> &savings, int cap) {
    
    GraphRoutes graph_route(sites);
    
    // analizza tutti i savings
    while (savings.size()) {

        // Prendo la coppia di nodi con saving maggiore (in cima alla lista);
        // Tale coppia è caratterizzata dal fatto che entrambi i nodi sono liberi (sono su route banali);
        client_id first_client = savings[0].getIdC1();
        client_id second_client = savings[0].getIdC2();
        
        // se la capacità del mezzo lo permette, creo la route r_i tra di essi
        if (graph_route.get_client(first_client).get_demand() + graph_route.get_client(second_client).get_demand() <= cap) {
            route_id r_second = graph_route.get_client(second_client).get_route();
            graph_route.delete_route(r_second);
            graph_route.insert_client_in_route(graph_route.get_client(first_client).get_route(), second_client, first_client);
        }
        
        // prendo l'id della route in cui è presente il primo nodo
        route_id route = graph_route.get_client(first_client).get_route();

        // Scorro la lista delle coppie di nodi ordinata per saving finché non incontro
        // una coppia contenente un nodo c[j]r_i nella route r_i e un nodo l su una route banale;
        for (int i = 1; i < savings.size(); i++) {
            
            Client c1 = graph_route.get_client(savings[i].getIdC1());
            Client c2 = graph_route.get_client(savings[i].getIdC2());
            
            // ###### c1 appartiene alla route e c2 è da solo
            if (c1.get_route() == route && c2.is_alone()) {
                
                double saving_next = graph_route.get_saving_client_in_route(c1.get_route(), c2.get_id(), c1.get_id());
                double saving_previous = graph_route.get_saving_client_in_route(c1.get_route(), c2.get_id(), graph_route.get_previous_client(c1.get_id()));
                

                // Valuto se effettivamente conviene effettuare l’inserimento, calcolando il saving S=Cri+Cl-Cril: ...
                // .. se positivo conviene: elimino dalla route l’arco c[j]ri-c[j+1]ri, e inserisco gli archi c[j]ri-l e l-c[j+1]ri
                if (saving_next > saving_previous && saving_next > 0) {

                    if (graph_route.get_total_goods(route) + c2.get_demand() <= cap) {
                        route_id r_c2 = graph_route.get_client(c2.get_id()).get_route();
                        graph_route.delete_route(r_c2);
                        graph_route.insert_client_in_route(c1.get_route(), c2.get_id(), c1.get_id());
                    }
                } else if (saving_previous >= saving_next && saving_previous > 0) {
                    
                    client_id previous_client = graph_route.get_previous_client(c1.get_id());
                    
                    if (graph_route.get_total_goods(route) + c2.get_demand() <= cap) {
                        route_id r_c2 = graph_route.get_client(c2.get_id()).get_route();
                        graph_route.delete_route(r_c2);
                        graph_route.insert_client_in_route(c1.get_route(), c2.get_id(), previous_client);
                    }
                }
            }
            
            // ###### c2 appartiene alla route e c1 è da solo
            if (c2.get_route() == route && c1.is_alone()) {
                
                double saving_next = graph_route.get_saving_client_in_route(c2.get_route(), c1.get_id(), c2.get_id());
                double saving_previous = graph_route.get_saving_client_in_route(c2.get_route(), c1.get_id(), graph_route.get_previous_client(c2.get_id()));
                
                if (saving_next > saving_previous && saving_next > 0) {
                    
                    if (graph_route.get_total_goods(route) + c1.get_demand() <= cap) {
                        route_id r_c1 = graph_route.get_client(c1.get_id()).get_route();
                        graph_route.delete_route(r_c1);
                        graph_route.insert_client_in_route(c2.get_route(), c1.get_id(), c2.get_id());
                    }
                } else if (saving_previous >= saving_next && saving_previous > 0) {
                    
                    client_id previous_client = graph_route.get_previous_client(c2.get_id());
                    
                    if (graph_route.get_total_goods(route) + c1.get_demand() <= cap) {
                        route_id r_c1 = graph_route.get_client(c1.get_id()).get_route();
                        graph_route.delete_route(r_c1);
                        graph_route.insert_client_in_route(c2.get_route(), c1.get_id(), previous_client);
                    }
                }
            }
        }
        
        // Cancella dal vettore dei saving tutti i saving che includono i nodi della route.
        for (int i = 0; i < savings.size(); i++) {
            
            Client c1 = graph_route.get_client(savings[i].getIdC1());
            Client c2 = graph_route.get_client(savings[i].getIdC2());
            
            if (c1.get_route() == route || c2.get_route() == route) {
                
                savings.remove(i);
                i--;
            }
        }

    }    

    return graph_route;
}

GraphRoutes second_closer_cw(QVector<Client> &sites, QVector<Saving> &savings, int cap) {

    GraphRoutes graph_route(sites);

    // analizza tutti i savings
    while (savings.size()) {

        // Prendo la coppia di nodi con saving maggiore (in cima alla lista);
        // Tale coppia è caratterizzata dal fatto che entrambi i nodi sono liberi (sono su route banali);
        client_id first_client = savings[0].getIdC1();
        client_id second_client = savings[0].getIdC2();

        // se la capacità del mezzo lo permette, creo la route r_i tra di essi
        if (graph_route.get_client(first_client).get_demand() + graph_route.get_client(second_client).get_demand() <= cap) {
            route_id r_second = graph_route.get_client(second_client).get_route();
            graph_route.delete_route(r_second);
            graph_route.insert_client_in_route(graph_route.get_client(first_client).get_route(), second_client, first_client);
        }

        // prendo l'id della route in cui è presente il primo nodo
        route_id route = graph_route.get_client(first_client).get_route();

        QVector<Saving> route_savings;
        QVector<client_id> actual_route = graph_route.get_route(route);
        for (int i = 0; i< actual_route.size()-1; i++){ //l'ultimo nodo 0 non si considera
            Client c_route = graph_route.get_client(actual_route[i]);
            Client c_route_next = graph_route.get_client(actual_route[i+1]);
            update_savings(c_route, c_route_next, graph_route, &route_savings);
        }
        while (route_savings.size()){
            Saving as = route_savings.last();
            route_savings.pop_back();
            Client c_alone = graph_route.get_client(as.getIdC2());
            Client c_next = graph_route.get_client(graph_route.get_next_client(as.getIdC1(), route));
            if (as.getValue() >= 0 && graph_route.get_total_goods(route) + c_alone.get_demand() <= cap && c_alone.is_alone()){
                graph_route.delete_route(c_alone.get_route());
                graph_route.insert_client_in_route(route, as.getIdC2(), as.getIdC1());
                for (int i=0; i<route_savings.size(); i++) {
                    if (route_savings[i].getIdC1() == as.getIdC1()) route_savings.remove(i);
                }
                //Vicini as.IdC1 + vicini c_alone
                update_savings(graph_route.get_client(as.getIdC1()), c_alone, graph_route, &route_savings);
                update_savings(c_alone, c_next, graph_route, &route_savings);
            }
            //std::cout << graph_route.to_string() << std::endl;
        }

        // Cancella dal vettore dei saving tutti i saving che includono i nodi della route.
        for (int i = 0; i < savings.size(); i++) {

            Client c1 = graph_route.get_client(savings[i].getIdC1());
            Client c2 = graph_route.get_client(savings[i].getIdC2());

            if (c1.get_route() == route || c2.get_route() == route) {

                savings.remove(i);
                i--;
            }
        }

    }

    return graph_route;
}

void update_savings(Client c_route, Client c_next, GraphRoutes &graph_route, QVector<Saving>* route_savings){
    QVector<client_id> neighbors = c_route.get_neighbors();
    neighbors += c_next.get_neighbors(); //vicini del nodo attuale e del successivo
    for (int j = 0; j<neighbors.size(); j++){
        Client c_neighbor = graph_route.get_client(neighbors[j]);
        if (c_neighbor.is_alone()){
            double cb = graph_route.get_cost_route(c_neighbor.get_route());
            double ac = c_route.get_distance(c_next);
            double ab = c_route.get_distance(c_neighbor);
            double bc = c_neighbor.get_distance(c_next);
            double value = cb + ac - ab - bc;
            Saving s(-1, c_route.get_id(), c_neighbor.get_id(), value);
            int index = search_insert_index_saving(s, 0, route_savings->size()-1, *route_savings);
            if (index >= 0) route_savings->insert(index, s);
        }
    }
}

void transfer_clients_post_processing(GraphRoutes *graph_routes,  int cap){
    QVector<int> ordered_goods;
    QVector<route_id> associate_routes;
    QVector<route_id> routes;
    route_id rid;
    int goods, in;
    for (rid=graph_routes->get_first_route_id(); rid!=-1; rid=graph_routes->get_next_route_id(rid)) routes.push_back(rid);
    for (int i=0; i<routes.size(); i++){
        goods = graph_routes->get_goods_route(routes[i]);
        in = search_insert_index_int(goods, 0, ordered_goods.size()-1, ordered_goods);
        ordered_goods.insert(in, goods);
        associate_routes.insert(in, routes[i]);
    }
    int i=0;
    while (i != ordered_goods.size()){
        //creo la lista di nodi dell'i-esima route
        //creo la lista ordinata di tutti i vicini che non appartengono all'i-esima route
        QVector<client_id> route = graph_routes->get_route(associate_routes[i]);
        QVector<Saving> route_savings;
        int route_goods = graph_routes->get_goods_route(associate_routes[i]);
        for (int j = 0; j< route.size()-1; j++){
            update_savings_post_processing(graph_routes->get_client(route[j]), graph_routes->get_client(route[j+1]), *graph_routes, &route_savings, cap);
        }
        //dal più conveniente al meno conveniente, valuto se inserirli nella route
        while (route_savings.size()){
            Saving as = route_savings.last();
            route_savings.pop_back();
            Client c_alone = graph_routes->get_client(as.getIdC2());
            Client c_next = graph_routes->get_client(graph_routes->get_next_client(as.getIdC1(), associate_routes[i]));
            if (as.getValue() >= 0 && graph_routes->get_total_goods(associate_routes[i]) + c_alone.get_demand() <= cap){
                route_id rr = c_alone.get_route();
                graph_routes->remove_client_from_route(c_alone.get_id());
                if (graph_routes->get_n_clients_in_route(rr) < 3) {
                    graph_routes->delete_route(rr);
                    for (int i=0; i<associate_routes.size(); i++){
                        if (associate_routes[i]==rr){
                            associate_routes.remove(i);
                            ordered_goods.remove(i);
                        }
                    }
                }
                graph_routes->insert_client_in_route(associate_routes[i], as.getIdC2(), as.getIdC1());
                for (int i=0; i<route_savings.size(); i++) {
                    if (route_savings[i].getIdC1() == as.getIdC1()) route_savings.remove(i);
                }
                //Vicini as.IdC1 + vicini c_alone
                update_savings(graph_routes->get_client(as.getIdC1()), c_alone, *graph_routes, &route_savings);
                update_savings(c_alone, c_next, *graph_routes, &route_savings);
            }
        }
        //se il totale dei beni è cambiato modifico la posizione della route nell'array ordinato per beni, e azzero i
        //altrimenti, incremento i
        int new_route_goods = graph_routes->get_goods_route(associate_routes[i]);
        if(new_route_goods > route_goods){
            route_id rid = associate_routes[i];
            associate_routes.remove(i);
            ordered_goods.remove(i);
            in = search_insert_index_int(new_route_goods, 0, ordered_goods.size()-1, ordered_goods);
            ordered_goods.insert(in, new_route_goods);
            associate_routes.insert(in, rid);
            i=0;
        }
        else i++;
    }
}

void update_savings_post_processing(Client c_route, Client c_next, GraphRoutes &graph_route, QVector<Saving>* route_savings, int cap){
    QVector<client_id> neighbors = c_route.get_neighbors();
    neighbors += c_next.get_neighbors(); //vicini del nodo attuale e del successivo
    route_id rid;
    if (c_route.get_id() != 0) rid = c_route.get_route();
    else rid = c_next.get_route();
    int actual_goods = graph_route.get_goods_route(rid);
    for (int j = 0; j<neighbors.size(); j++){
        Client c_neighbor = graph_route.get_client(neighbors[j]);
        if (c_neighbor.get_route() != rid && (c_neighbor.get_demand() + actual_goods) < cap && c_neighbor.get_id() != 0){
            double value = graph_route.get_saving_transfer_client(neighbors[j], c_neighbor.get_route(), rid, c_route.get_id());
            Saving s(-1, c_route.get_id(), c_neighbor.get_id(), value);
            int index = search_insert_index_saving(s, 0, route_savings->size()-1, *route_savings);
            if (index >= 0) route_savings->insert(index, s);
        }
    }
}

void second_post_processing(GraphRoutes *graph_routes){
    route_id rid;
    double tot_cost;
    double new_cost = graph_routes->get_total_cost();
    do {
        tot_cost = new_cost;
        for (rid=graph_routes->get_first_route_id(); rid!=-1; rid=graph_routes->get_next_route_id(rid)){
            QVector<client_id> route = graph_routes->get_route(rid);
            for (int j = route.size()-2; j>2; j--){
                for (int i=1; i<route.size()-j; i++){
                    if (graph_routes->get_swap_saving_consecutive_in_route(route[i], route[i+j-1]) > 0){
                        graph_routes->swap_consecutive_clients_in_route(route[i], route[i+j-1]);
                        route = graph_routes->get_route(rid);
                    }
                }
            }
        }
        new_cost = graph_routes->get_total_cost();
    } while (tot_cost != new_cost);
}

/**
 * @brief search_insert_index
 *  Effettua una ricerca binaria di n sull'array ordinato v,
 *  e restituisce l'indice del primo elemento nell'array
 *  >= a n.
 * @param n:        numero da cercare
 * @param first:    indice del primo elemento dell'array
 * @param last:     indice dell'ultimo elemento dell'array
 * @param v:        array su cui effettuare la ricerca
 * @return          l'indice del primo elemento >= a n.
 */
int search_insert_index_saving(Saving s, int first, int last, QVector<Saving> & v) {
    int mid;
    if (first <= last){
        mid = (first + last) / 2;
        if (v[mid] < s) return (search_insert_index_saving (s, mid+1, last, v) );
        if (v[mid] == s) return -1;
        if (v[mid] > s) return (search_insert_index_saving (s, first, mid-1, v) );
    }
    return first;
}
