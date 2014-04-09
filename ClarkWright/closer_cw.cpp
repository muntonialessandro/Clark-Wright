#include "closer_cw.h"

GraphRoutes closer_cw(QVector<Client> &sites, QVector<Saving> &savings, int cap) {
    
    GraphRoutes graph_route(sites);
    
    //int capacity = 0;

    // analizza tutti i savings
    while (savings.size()) {

        // Prendo la coppia di nodi con saving maggiore (in cima alla lista);
        // Tale coppia è caratterizzata dal fatto che entrambi i nodi sono liberi (sono su route banali);
        client_id first_client = savings[0].getIdC1();
        client_id second_client = savings[0].getIdC2();

        // prendo il costo e ...
        //capacity = graph_route.get_client(first_client).get_demand();
        
        // se la capacità del mezzo lo permette, creo la route r_i tra di essi
        if (graph_route.get_client(first_client).get_demand() + graph_route.get_client(second_client).get_demand() <= cap) {
            route_id r_second = graph_route.get_client(second_client).get_route();
            graph_route.delete_route(r_second);
            graph_route.insert_client_in_route(graph_route.get_client(first_client).get_route(), second_client, first_client);
            //capacity += graph_route.get_client(second_client).get_demand();
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
                        //capacity += c2.get_demand();
                    }
                } else if (saving_previous >= saving_next && saving_previous > 0) {
                    
                    client_id previous_client = graph_route.get_previous_client(c1.get_id());
                    
                    if (graph_route.get_total_goods(route) + c2.get_demand() <= cap) {
                        route_id r_c2 = graph_route.get_client(c2.get_id()).get_route();
                        graph_route.delete_route(r_c2);
                        graph_route.insert_client_in_route(c1.get_route(), c2.get_id(), previous_client);
                        //capacity += c2.get_demand();
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
                        //capacity += c1.get_demand();
                    }
                } else if (saving_previous >= saving_next && saving_previous > 0) {
                    
                    client_id previous_client = graph_route.get_previous_client(c2.get_id());
                    
                    if (graph_route.get_total_goods(route) + c1.get_demand() <= cap) {
                        route_id r_c1 = graph_route.get_client(c1.get_id()).get_route();
                        graph_route.delete_route(r_c1);
                        graph_route.insert_client_in_route(c2.get_route(), c1.get_id(), previous_client);
                        //capacity += c1.get_demand();
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

GraphRoutes best_closer_cw(QVector<Client> &sites, QVector<Saving> &savings, int cap) {

    GraphRoutes graph_route(sites);

    int capacity = 0;

    // analizza tutti i savings
    while (savings.size()) {

        // Prendo la coppia di nodi con saving maggiore (in cima alla lista);
        // Tale coppia è caratterizzata dal fatto che entrambi i nodi sono liberi (sono su route banali);
        client_id first_client = savings[0].getIdC1();
        client_id second_client = savings[0].getIdC2();

        // prendo il costo e ...
        capacity = graph_route.get_client(first_client).get_demand();

        // se la capacità del mezzo lo permette, creo la route r_i tra di essi
        if (capacity + graph_route.get_client(second_client).get_demand() <= cap) {
            route_id r_second = graph_route.get_client(second_client).get_route();
            graph_route.delete_route(r_second);
            graph_route.insert_client_in_route(graph_route.get_client(first_client).get_route(), second_client, first_client);
            capacity += graph_route.get_client(second_client).get_demand();
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

                    if (capacity + c2.get_demand() <= cap) {
                        route_id r_c2 = graph_route.get_client(c2.get_id()).get_route();
                        graph_route.delete_route(r_c2);
                        graph_route.insert_client_in_route(c1.get_route(), c2.get_id(), c1.get_id());
                        capacity += c2.get_demand();
                    }
                } else if (saving_previous >= saving_next && saving_previous > 0) {

                    client_id previous_client = graph_route.get_previous_client(c1.get_id());

                    if (capacity + c2.get_demand() <= cap) {
                        route_id r_c2 = graph_route.get_client(c2.get_id()).get_route();
                        graph_route.delete_route(r_c2);
                        graph_route.insert_client_in_route(c1.get_route(), c2.get_id(), previous_client);
                        capacity += c2.get_demand();
                    }
                }
            }

            // ###### c2 appartiene alla route e c1 è da solo
            if (c2.get_route() == route && c1.is_alone()) {

                double saving_next = graph_route.get_saving_client_in_route(c2.get_route(), c1.get_id(), c2.get_id());
                double saving_previous = graph_route.get_saving_client_in_route(c2.get_route(), c1.get_id(), graph_route.get_previous_client(c2.get_id()));

                if (saving_next > saving_previous && saving_next > 0) {

                    if (capacity + c1.get_demand() <= cap) {
                        route_id r_c1 = graph_route.get_client(c1.get_id()).get_route();
                        graph_route.delete_route(r_c1);
                        graph_route.insert_client_in_route(c2.get_route(), c1.get_id(), c2.get_id());
                        capacity += c1.get_demand();
                    }
                } else if (saving_previous >= saving_next && saving_previous > 0) {

                    client_id previous_client = graph_route.get_previous_client(c2.get_id());

                    if (capacity + c1.get_demand() <= cap) {
                        route_id r_c1 = graph_route.get_client(c1.get_id()).get_route();
                        graph_route.delete_route(r_c1);
                        graph_route.insert_client_in_route(c2.get_route(), c1.get_id(), previous_client);
                        capacity += c1.get_demand();
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
