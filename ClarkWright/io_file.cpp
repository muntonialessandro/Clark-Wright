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

