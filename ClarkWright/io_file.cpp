#include "io_file.h"

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
         std::cout << "Error in line 0 (file non trovato)" << std::endl;
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

bool write_results_in_file(GraphRoutes* routes){

    if( routes->get_first_route_id() == (-1) ) {
        qDebug("Nessuna rotta da salvare.");
        return false;
    }

    QString fileName = QFileDialog::getSaveFileName( NULL,
                               "Salva in un file di testo",
                               "./RouteAndResult.txt",
                               "RoutesTxt (*.txt)") ;
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug("File non trovato.");
        return false;
    }

    QTextStream out(&file); // the streaming of the text file

    for( int id_route = routes->get_first_route_id() ; id_route != (-1) ;
         id_route = routes->get_next_route_id( id_route ) ){


        QVector<client_id> clients = routes->get_route( id_route );
        Client actual_client;

        out << "Route id: " << id_route <<
               "  Goods: " << routes->get_goods_route( id_route ) << endl;   // Route id: 11  Goods: 155
        while ( clients.size() > 1 ) {
            actual_client = routes->get_client( clients.last() );           // prendi l'ultimo così non rialloca vettore

            out << "("      << actual_client.get_x()       <<               // ( x  , y  ) demand
                   ","      << actual_client.get_y()       <<               // ( 10 , 15 ) 34
                   ")  "    << actual_client.get_demand()
                   << endl;

            clients.pop_back();                                             // togli il cliente appena inserito
        }

        out << endl;                                                        // vai a capo
    }

    return true;
}
