#include "closer_cw.h"

GraphRoutes closer_cw(QVector<Client> &sites, QVector<Saving> &savings, int cap) {
    
    GraphRoutes graph_route(sites);
    
    int capacity = 0;
    
    while (savings.size()) {
        
        client_id first_client = savings[0].getIdC1();
        client_id second_client = savings[0].getIdC2();
        
        capacity = graph_route.get_client(first_client).get_demand();
        
        if (capacity + graph_route.get_client(second_client).get_demand() <= cap) {
            
            graph_route.insert_client_in_route(graph_route.get_client(first_client).get_route(), second_client, first_client);
            capacity += graph_route.get_client(second_client).get_demand();
        }
        
        route_id route = graph_route.get_client(first_client).get_route();
        
        for (int i = 1; i < savings.size(); i++) {
            
            Client c1 = graph_route.get_client(savings[i].getIdC1());
            Client c2 = graph_route.get_client(savings[i].getIdC2());
            
            if (c1.get_route() == route && c2.is_alone()) {
                
                double saving_next = graph_route.get_saving_client_in_route(c1.get_route(), c2.get_id(), c1.get_id());
                double saving_previous = graph_route.get_saving_client_in_route(c1.get_route(), c2.get_id(), graph_route.get_previous_client(c1.get_id()));
                
                if (saving_next > saving_previous && saving_next > 0) {
                    
                    if (capacity + c2.get_demand() <= cap) {
                        
                        graph_route.insert_client_in_route(c1.get_route(), c2.get_id(), c1.get_id());
                        capacity += c2.get_demand();
                    }
                } else if (saving_previous >= saving_next && saving_previous > 0) {
                    
                    client_id previous_client = graph_route.get_previous_client(c1.get_id());
                    
                    if (capacity + c2.get_demand() <= cap) {
                        
                        graph_route.insert_client_in_route(c1.get_route(), c2.get_id(), previous_client);
                        capacity += c2.get_demand();
                    }
                }
            }
            
            if (c2.get_route() == route && c1.is_alone()) {
                
                double saving_next = graph_route.get_saving_client_in_route(c2.get_route(), c1.get_id(), c2.get_id());
                double saving_previous = graph_route.get_saving_client_in_route(c2.get_route(), c1.get_id(), graph_route.get_previous_client(c2.get_id()));
                
                if (saving_next > saving_previous && saving_next > 0) {
                    
                    if (capacity + c1.get_demand() <= cap) {
                        
                        graph_route.insert_client_in_route(c2.get_route(), c1.get_id(), c2.get_id());
                        capacity += c1.get_demand();
                    }
                } else if (saving_previous >= saving_next && saving_previous > 0) {
                    
                    client_id previous_client = graph_route.get_previous_client(c2.get_id());
                    
                    if (capacity + c1.get_demand() <= cap) {
                        
                        graph_route.insert_client_in_route(c2.get_route(), c1.get_id(), previous_client);
                        capacity += c1.get_demand();
                    }
                }
            }
        }
        
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
