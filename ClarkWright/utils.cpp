#include "utils.h"

/**
 * @brief binary_search
 *  Effettua una ricerca binaria di n sull'array ordinato v.
 *  Restituisce -1 se n non è presente nell'array.
 * @param n:        numero da cercare
 * @param first:    indice del primo elemento dell'array
 * @param last:     indice dell'ultimo elemento dell'array
 * @param v:        array su cui effettuare la ricerca
 * @return          l'indice di n nell'array.
 *                  se n non è presente, restituisce -1.
 */
int binary_search(double n, int first, int last, QVector<double> & v) {
    int mid;
    if (first <= last){
        mid = (first + last) / 2;
        if (v[mid] < n) return (binary_search (n, mid+1, last, v) );
        if (v[mid] == n) return mid;
        if (v[mid] > n) return (binary_search (n, first, mid-1, v) );
    }
    return -1;
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
int search_insert_index(double n, int first, int last, QVector<double> & v) {
    int mid;
    if (first <= last){
        mid = (first + last) / 2;
        if (v[mid] < n) return (search_insert_index (n, mid+1, last, v) );
        if (v[mid] == n) return mid;
        if (v[mid] > n) return (search_insert_index (n, first, mid-1, v) );
    }
    return first;
}

/**
 * @brief merge
 *  dati due array ordinati, la funzione merge restituisce un array contenente tutti gli
 *  elementi di v1 e v2 ordinati.
 * @param v1: array ordinato v1
 * @param v2: array ordinato v2
 * @return l'array ordinato contenente l'unione tra v1 e v2.
 */
QVector<double> merge(QVector<double> &v1, QVector<double> &v2){
    QVector<double> merge;
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
                if (v1[i] <= v2[j]){ // se l'elemento i di v1 è minore o uguale dell'elemento j di v2
                    merge.push_back(v1[i]); // inserisco v1[i] nell'array merge
                    //if (v1[i] == v2[j]) j++; // se v2[j] è uguale a v1[i], incremento anche j per non avere ripetizioni
                    i++; // incremento i
                }
                else { // altrimenti, v2[j] è strettamente minore di v1[i]
                    merge.push_back(v2[j]); // inserisco v2[j] nell'array merge
                    j++; // incremento j
                }
            }
        }

    }
    return merge;
}

QVector<double> mergesort(QVector<double> &v){
    int size = v.size();
    if (size > 1) {
        QVector<double> v1 = v.mid(0, size/2);
        QVector<double> v2 = v.mid(size/2, size-(size/2));
        QVector<double> r1 = mergesort(v1);
        QVector<double> r2 = mergesort(v2);
        QVector<double> r = merge(r1, r2);
        return r;
    }
    else return v;

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
