#include "classes/graph_routes.h"
#include "timer.h"
#include "utils.h"
#include "io_file.h"
#include "voronoi.h"
#include <iostream>
#include <QVector>

#include "user_interface/mainwindow.h"

void esempi_di_utilizzo_per_algoritmo( void );

int main(int argc, char *argv[]){

    if(true) {     //MODALITA' TERMINALE = TRUE

        //esempi_di_utilizzo_per_algoritmo();

        int cap;
        QVector<Client> clients;
        clients = read_file("../../../vrpnc1.txt", &cap); // lelle
//        clients = read_file("vrpnc1.txt", &cap); // Ale
        voronoi(clients);

    }
    else {          //MODALITA' INTERFACCIA = false

        // Launch interface example
        QApplication a(argc, argv);     //crea l'applicazione per ..
        QWidget w;                      // .. poter inserire il widget ..
        MainWindow window(&w);          // .. e inserire la finestra ..
        window.G_draw_interface(&a);    // .. al suo interno.

        // draw routes example
        QList< G_arrows_points_path > routes;
        window.G_draw_routes( routes );

        // draw notes example
        QList< G_node_and_label > nodes;
        window.G_draw_nodes( nodes );

    }

    return 0;

}


void esempi_di_utilizzo_per_algoritmo( void )
{

    Timer timer("C&W Algorithm");
    timer.start();

    /** ALGORITHMS */

    //Prova Mergesort
    int i;
    QVector<double> v;
    v << 4 << 6 << 1 << 7 << 2.2 << 10 << 5 << 2.4 << 11 << 8;

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

//        return 0;
}









// go ..
    // Prendo la coppia di nodi con saving maggiore (in cima alla lista);
    // Tale coppia è caratterizzata dal fatto che entrambi i nodi sono liberi (sono su route banali);

    // creo la route r_i tra di essi;

    // Scorro la lista delle coppie di nodi ordinata per saving finché non
    // incontro una coppia contenente un nodo c[j]_(r_i) nella route r_i e un nodo l su una route banale;

    // Valuto se effettivamente conviene effettuare l’inserimento,
    // calcolando il saving S=C_(r_i) + C_l - C_(r_i,l) : se positivo conviene:
    // elimino dalla route l’arco c[j]_(r_i)-c[j+1]_(r_i),
    // e inserisco gli archi c[j]_(r_i) - l e l-c[j+1]_(r_i)

// Until la route non è satura;

// Finché non vi sono più coppie di nodi liberi nella lista di savings;
// Eventuale Post-Processing











