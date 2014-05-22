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

#include "classic_cw.h"

GraphRoutes classic_cw(QVector<Client> &clients, QVector<Saving> &savings, int vehicle_capacity) {

    // 0. Inizializzazione strutture dati di supporto.
    int i=0, j=0, dim, idSaving=0, savingAttuale, result;
    double costoOriginale, costoNuovo, costoTotaleAtteso, costoTotaleAttuale;
    bool inserimentoInTesta, flagDisabilita, exitLoop = false;
    Client clientCandidato, clientNext, clientPrec;

    QVector<client_id> clients_in_route;
    route_id routeAttuale;            // Recupera la prima route valida da analizzare.
    int tempStampaSaving;


    //  1. Acquisizione dell’input dal benchmark.
    //clients = read_file("/Users/Andre/Desktop/RO-Project/File/vrpnc1.txt", &vehicle_capacity);
    dim = clients.size()-1;


    //  2. Inizializzazione del GraphState con i dati di input:
    GraphRoutes state(clients);     // Inizializzazione dello stato dell'algoritmo, con annessi clienti.


    //  3. Calcolo degli (n^2)/2 saving: il saving dei client (x,y) è uguale al saving di (y, x).
    for(i=1; i<dim; i++){
        for(j=i+1; j<dim; j++){
                costoOriginale = state.get_cost_route(i-1) + state.get_cost_route(j-1);     // 2*(0, i) + 2*(j, 0)
                costoNuovo = ( (state.get_client(0).get_distance(state.get_client(i))) +    // (0, i)
                               (state.get_client(j).get_distance(state.get_client(0))) +    // (j, 0)
                               (state.get_client(i).get_distance(state.get_client(j))) );   // (i, j)

                savings.push_back(Saving(idSaving, i, j, (costoOriginale - costoNuovo)));
                idSaving++;
        }
    }


    // 4. Ordinamento decrescente dei savings. Verranno considerati in senso decrescente.
    std::sort(savings.begin(), savings.end(), Saving::sortSavings);


    // 5. Inizializzazione della prima route.
    savingAttuale = find_true_saving(savings);                           // Indica il saving attualmente analizzato.
    routeAttuale = (savings[savingAttuale].getIdC1() -1);               // Recupera la prima route valida da analizzare.
    state.set_visited_route(routeAttuale);                            // Setta la Route come visitata.
    state.set_client_alone(savings[savingAttuale].getIdC1(), false);    // Disabilita il client della route che si sta costruendo.
    savingAttuale -= 1;


    do{
        savingAttuale += 1;
        flagDisabilita = true;          // Si suppone che il savingAttuale verrà consumato.

        if(savingAttuale != -1){        // Verifica se esistono ancora savings abilitati.

            clients_in_route = state.get_clients_in_route(routeAttuale); // Recupera tutti i client inseriti nella route.
            int lastClientInRouteId = clients_in_route.size()-2;         // Recupera l'ultimo cliente in lista.

            // 6. Verifica la possibilità di consumare il saving attuale.
            result = (check_insert(clients_in_route, savings, savingAttuale, lastClientInRouteId, state));
            switch (result){

            case 1:
                inserimentoInTesta = true;                                                // Inserimento in testa.
                clientCandidato = state.get_client(savings[savingAttuale].getIdC1());     // Client1.
                clientPrec = state.get_client(0);                                         // Il prec e' per forza il deposito.
                clientNext = state.get_client(savings[savingAttuale].getIdC2());          // Il next e' l'altro client che componeva la coppia del saving
                break;

            case 2:
                inserimentoInTesta = false;                                               // Inserimento in coda.
                clientCandidato = state.get_client(savings[savingAttuale].getIdC2());     // Client2.
                clientNext = state.get_client(0);                                         // Il next e' il client che compone il saving insieme al candidato, gia' preso.
                clientPrec = state.get_client(savings[savingAttuale].getIdC1());          // Il prec e' il deposito.
                break;

            case 3:
                flagDisabilita = false;                                                   // Il saving attuale non puo' essere aggiunto alla rotta, quindi non deve essere disabilitato.
                break;
            }



            // 7. Nel caso in cui il saving attuale sia compatibile con i client della route.
            if((result != -2) && (result != 3)){

                // 8. Controllo capacita' del veicolo sufficiente.
                if(vehicle_capacity >= (state.get_total_goods(routeAttuale) + clientCandidato.get_demand())){

                    // 9. Controllo ottenimento risparmio effettivo.
                    costoTotaleAttuale = state.get_total_cost();  // Costo totale di tutte le rotte, precedente al potenziale inserimento del nuovo client.

                    if(!inserimentoInTesta){
                        /* Aggiornamento del costo con inserimento in coda.
                         * Esempio di rotta:  (0, 2, 0)
                         * Esempio di saving: (2, 3).
                         * clientCandidato = 3.
                         * clientPrec = 2.
                         * clientNext = 0.
                         * costoTotaleAttuale = (0, 2) + (2, 0) + (0, 3) + (3, 0)
                         * costoTotaleAtteso  = costoTotaleAttuale - (2, 0) - (0, 3) + (2, 3).
                         * Rotta finale: (0, 2, 3, 0)
                         *
                         */
                        costoTotaleAtteso = costoTotaleAttuale -
                                            clientPrec.get_distance(clientNext) -           // (2, 0)
                                            clientNext.get_distance(clientCandidato) +      // (0, 3)
                                            clientPrec.get_distance(clientCandidato);       // (2, 3)


                    }
                    else{
                        /* Aggiornamento del costo con inserimento in testa.
                         * Esempio di rotta:  (0, 2, 0)
                         * Esempio di saving: (3, 2).
                         * clientCandidato = 3.
                         * clientPrec = 0.
                         * clientNext = 2.
                         * costoTotaleAttuale = (0, 2) + (2, 0) + (0, 3) + (3, 0)
                         * costoTotaleAtteso  = costoTotaleAttuale - (0, 2) - (3, 0) + (3, 2).
                         * Rotta finale: (0, 3, 2, 0)
                         *
                         */
                        costoTotaleAtteso = costoTotaleAttuale -
                                            clientPrec.get_distance(clientNext) -           // (0, 2)
                                            clientCandidato.get_distance(clientPrec) +      // (3, 0)
                                            clientCandidato.get_distance(clientNext);       // (3, 2)


                    }

                    if(costoTotaleAtteso < costoTotaleAttuale){

                        /* 10. Fondi cliente nella rotta
                         * Questa operazione e' eseguita tenendo conto, in seguito, del flag "flagDisabilita". In base al suo valore,
                         * si procede a disabilitare il saving, in modo da riunire tutte le possibili casistiche che porterebbero
                         * alla sua disabilitazione, in una sola: quella dell'if che opera il controllo sul flag stesso.
                         */
                        state.insert_client_in_route(routeAttuale, clientCandidato.get_id(), clientPrec.get_id());  // Inserimento.
                        state.set_client_alone(clientCandidato.get_id(), false);                                    // Disabilita il client aggiunto nella rotta.
                        state.delete_route(clientCandidato.get_route());                                            // Disabilita la route banale di cui il client appena inserito faceva parte

                        // 11. Calcolo del prossimo saving.
                        tempStampaSaving = savingAttuale;
                        savings[savingAttuale].setEnable(false);
                        savingAttuale = find_true_saving(savings);

                        if(savingAttuale == -2){                    // Caso in cui non esista un prossimo saving.
                            savingAttuale = savings.size()-1;
                        }
                        else{
                            savingAttuale -= 1;
                        }

                        flagDisabilita = false;
                    }
                }
            }


            /* 11. Disabilita il saving attuale.
             * Se il saving non è stato consumato ma in futuro non è più
             * utilizzabile, allora deve essere disabilitato definitivamente.
             */
            if(flagDisabilita == true){
                savings[savingAttuale].setEnable(false);                        // Disabilita il saving attuale.
            }

            // 12. Controlla se il saving e' l'ultimo.
            if(savingAttuale == savings.size()-1){
                savingAttuale = find_true_saving(savings);

                // 13. Sono state create tutte le route necessarie, termina.
                if(savingAttuale == -2){
                    exitLoop = true;
                }
                else{                                                                   // E' possibile creare una nuova route.
                    routeAttuale = (savings[savingAttuale].getIdC1() -1);               // Recupera la prima route valida da analizzare.
                    state.set_visited_route(routeAttuale);                            // Setta la Route come visitata.
                    state.set_client_alone(savings[savingAttuale].getIdC1(), false);    // Disabilita il client della route che si sta costruendo.
                    savingAttuale -= 1;
                }
            }
        }
    }

    while(!exitLoop);

//    // Per ogni savings calcolato, partendo dal maggiore:
//    for(int i=0; i<savings.size(); i++){
//        cout<<savings[i].getSaving_id()<<"\t";
//        cout<<savings[i].getIdC1()<<"\t";
//        cout<<savings[i].getIdC2()<<"\t";
//        cout<<savings[i].getEnable()<<"\t";
//        cout<<savings[i].getValue()<<endl<<endl;
//    }


//    int s=0;
//    int pippo;
//    route_id rid;

//    for (rid=state.get_first_route_id(); rid!=-1; rid=state.get_next_route_id(rid)){
//        if(state.get_route_from_state(rid).get_visitated()){
//            cout<<endl<<"Route"<<state.get_route_from_state(rid).get_id()<<". [";
//            for(pippo=0; pippo<state.get_route_from_state(rid).get_n_nodes(); pippo++){
//                cout<<" "<<state.get_route_from_state(rid).get_client(pippo);
//            }
//            cout<<" ]";
//        }
//    }

//    s=0;
//    pippo=0;
//    while((s = state.get_next_route_id(s)) != -1){
//        if((!state.get_route_from_state(s).get_visitated()) && (state.get_route_from_state(s)).is_enabled()){
//            cout<<endl<<"Route"<<state.get_route_from_state(s).get_id()<<". [";
//            for(pippo=0; pippo<state.get_route_from_state(s).get_n_nodes(); pippo++){
//                cout<<" "<<state.get_route_from_state(s).get_client(pippo);
//            }
//            cout<<" ]";
//        }
//    }

//    cout<<endl<<"Costo Totale = "<<state.get_total_cost();
//    cout<<endl<<endl<<endl;

    return state;
}


/**
 * @brief check_insert
 *  Verifica se è possibile inserire il savingAttuale nella routeAttuale
 *  oppure i client del saving e della route non sono compatibili.
 * @param clients_in_route
 * @param savings
 * @param savingAttuale
 * @param lastClientInRouteId
 * @param state
 * @return
 */
int check_insert(QVector<client_id> clients_in_route, QVector<Saving> &savings, int savingAttuale, int lastClientInRouteId, GraphRoutes state){

    if( clients_in_route[1]
            == savings[savingAttuale].getIdC2() ){                          // Caso 1: inserimento in testa.
        if(state.get_client(savings[savingAttuale].getIdC1()).is_alone())
            return 1;
        else
            return -2;
    }
    else if( clients_in_route[lastClientInRouteId] == savings[savingAttuale].getIdC1() ){   // Caso 2: inserimento in coda.
        if(state.get_client(savings[savingAttuale].getIdC2()).is_alone())
            return 2;
        else
            return -2;
    }
    else if( clients_in_route[1] == savings[savingAttuale].getIdC1() ){         // Caso 3: inserimento in testa (Twin)
        if(state.get_client(savings[savingAttuale].getIdC2()).is_alone()){
            savings[savingAttuale].swapClients();
            return 1;
        }else
            return -2;
    }
    else if( clients_in_route[lastClientInRouteId] == savings[savingAttuale].getIdC2() ){   // Caso 4: inserimento in coda (Twin)
        if(state.get_client(savings[savingAttuale].getIdC1()).is_alone()){
            savings[savingAttuale].swapClients();
            return 2;
        }else
            return -2;
    }

    else if((state.get_client(savings[savingAttuale].getIdC1()).is_alone()) && (state.get_client(savings[savingAttuale].getIdC2()).is_alone()))
        return 3;   // tutti e due i client del saving considerato sono enable.

    return -2;      // Almeno uno dei due client del saving e' enable ma non e' di confine nella rotta considerata.
}

/**
 * @brief find_true_saving
 *  Verifica se ci sono ancora saving da processare.
 * @param sav
 * @return
 */
int find_true_saving(QVector<Saving> sav){
    for(int i=0; i<sav.size(); i++){
        if(sav[i].getEnable() == true)
            return i;
    }

    return -2;      // Nessun saving è abilitato, l'algoritmo termina.
}
