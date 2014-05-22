/*
 *  Copyright (C) 2014 Simone Barbieri, Andrea Loddo, Emanuele Mameli, Alessandro Muntoni, Livio Pompianu
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
int binary_search_double(double n, int first, int last, QVector<double> & v) {
    int mid;
    if (first <= last){
        mid = (first + last) / 2;
        if (v[mid] < n) return (binary_search_double (n, mid+1, last, v) );
        if (v[mid] == n) return mid;
        if (v[mid] > n) return (binary_search_double (n, first, mid-1, v) );
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
int search_insert_index_double(double n, int first, int last, QVector<double> & v) {
    int mid;
    if (first <= last){
        mid = (first + last) / 2;
        if (v[mid] < n) return (search_insert_index_double (n, mid+1, last, v) );
        if (v[mid] == n) return mid;
        if (v[mid] > n) return (search_insert_index_double (n, first, mid-1, v) );
    }
    return first;
}

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
int binary_search_distance_client(QPair<int, double> n, int first, int last, QVector< QPair<int, double> > & v) {
    int mid;
    if (first <= last){
        mid = (first + last) / 2;
        if (v[mid].second < n.second) return (binary_search_distance_client (n, mid+1, last, v) );
        if (v[mid].second == n.second) return mid;
        if (v[mid].second > n.second) return (binary_search_distance_client (n, first, mid-1, v) );
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
int search_insert_index_distance_client(QPair<int, double> n, int first, int last, QVector< QPair<int, double> > &v) {
    int mid;
    if (first <= last){
        mid = (first + last) / 2;
        if (v[mid].second < n.second) return (search_insert_index_distance_client (n, mid+1, last, v) );
        if (v[mid].second == n.second) return mid;
        if (v[mid].second > n.second) return (search_insert_index_distance_client (n, first, mid-1, v) );
    }
    return first;
}

int binary_search_int(int n, int first, int last, QVector<int> &v)
{
    int mid;
    if (first <= last){
        mid = (first + last) / 2;
        if (v[mid] < n) return (binary_search_int (n, mid+1, last, v) );
        if (v[mid] == n) return mid;
        if (v[mid] > n) return (binary_search_int (n, first, mid-1, v) );
    }
    return -1;
}

int search_insert_index_int(int n, int first, int last, QVector<int> &v)
{
    int mid;
    if (first <= last){
        mid = (first + last) / 2;
        if (v[mid] < n) return (search_insert_index_int (n, mid+1, last, v) );
        if (v[mid] == n) return mid;
        if (v[mid] > n) return (search_insert_index_int (n, first, mid-1, v) );
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


double absolute(double num)
{
    if (num < 0) return -num;
    else return num;
}
