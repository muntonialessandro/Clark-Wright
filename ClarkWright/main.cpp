#include "classes/graph_routes.h"
#include "timer.h"
#include "utils.h"
#include <iostream>
#include <QFile>
#include <sstream>
#include <QVector>

QVector<Client> read_file(QString filename, int* vehicle_capacity);

int main(){
    Timer timer("C&W Algorithm");
    timer.start();

    /** ALGORITHMS */

    //Prova Mergesort
    int i;
    QVector<double> v = {4, 6, 1, 7, 2.2, 10, 5, 2.4, 11, 8};
    QVector<double> res = mergesort(v);
    for (i=0; i<res.size(); i++) std::cout << res[i] << "; ";
    std::cout << std::endl;

    //Prova GraphRoute
    QVector<Client> clients;
    Client d(0, 2, 2, 0);
    Client c1(1, 3, 3, 13);
    Client c2(2, 1, 3, 20);
    Client c3(3, 0, 1, 25);
    Client c4(4, 2, 0, 5);
    Client c5(5, 3, 1, 40);
    clients.push_back(d);
    clients.push_back(c1);
    clients.push_back(c2);
    clients.push_back(c3);
    clients.push_back(c4);
    clients.push_back(c5);
    GraphRoutes state(clients); //inizializzo lo stato dell'algoritmo
    std::string s1 = state.to_string();
    std::cout << s1;

    state.remove_client_from_route(1); //rimuove 1 dalla sua route
    state.insert_client_in_route(1, 2); //inserisce il nodo 1 dopo il nodo 2, nella route di 2
    state.delete_route(0); //la route di 1 era banale: la si elimina
    std::cout << state.to_string();

    double saving = state.get_saving_client_in_route(1, 5, 1);
    std::cout << saving << std::endl;

    //Prova ciclo route attive
    state.delete_route(3); //non si dovrebbe fare, il nodo 4 ora non ha route!
    std::cout << state.to_string();
    route_id rid;
    std::cout << "Route attive: ";
    for (rid=state.get_first_route_id(); rid!=-1; rid=state.get_next_route_id(rid)){
        std::cout << rid << "; ";
    }
    std::cout << std::endl;

    int cap;
    clients.clear();
    clients = read_file("vrpnc1.txt", &cap);
    GraphRoutes state2(clients);
    std::cout << cap << std::endl;
    std::cout << state2.to_string();

    timer.stop_and_print();

    return 0;
}

QVector<Client> read_file(QString filename, int* vehicle_capacity){
    int n_clients, temp;
    int x_deposit, y_deposit;
    int x_client, y_client, demand;
    int i;
    QFile file(filename);
    QVector<Client> clients;
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        std::cout << "Error Reading File " << filename.toStdString() << std::endl;
        return clients;
    }

    QByteArray line = file.readLine();
    char *tmp = line.data();
    std::stringstream s1(tmp);
    s1 >> n_clients >> *vehicle_capacity >> temp >> temp;

    if( s1.fail() == true )
    {
         std::cout << "Error in line 0" << std::endl;
         file.close();
         return clients;
    }

    line = file.readLine();
    tmp = line.data();
    std::stringstream s2(tmp);
    s2 >> x_deposit >> y_deposit;

    Client c(0, x_deposit, y_deposit, 0);
    clients.push_back(c);

    for (i=0; i<n_clients; i++){
        line = file.readLine();
        tmp = line.data();
        std::stringstream s(tmp);
        s >> x_client >> y_client >> demand;
        c = Client(i+1, x_client, y_client, demand);
        clients.push_back(c);
    }
    file.close();

    return clients;

}
