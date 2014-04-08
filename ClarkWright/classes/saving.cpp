#include "saving.h"

Saving::Saving(){

}


Saving::Saving(idSaving idActual, int idc1, int idc2, double value){
    this->idActual = idActual;
    this->idTwin = -1;          // Verra' settato in seguito all'ordinamento della lista di savings.
    this->idc1 = idc1;
    this->idc2 = idc2;
    this->value = value;
    this->enable = true;
}

idSaving Saving::getSaving_id(){
    return this->idActual;
}

idSaving Saving::getTwinSaving_id(){
    return this->idTwin;
}

int Saving::getIdC1(){
    return this->idc1;
}

int Saving::getIdC2(){
    return this->idc2;
}

double Saving::getValue(){
    return this->value;
}

bool Saving::getEnable(){
    return this->enable;
}

void Saving::setId(idSaving id)
{
    this->idActual = id;
}

std::string Saving::toString()
{
    std::stringstream ss;
    ss << "Saving ID: " << this->idActual << "; Clients: (" << this->idc1 << "; " << this->idc2
       << "); ID Twin: " << this->idTwin << "; Value: " << this->value << "; Enabled: "
       << this->enable << ";";
    std::string s = ss.str();
    return s;
}

void Saving::setTwinSaving_id(int idTwin){
    this->idTwin = idTwin;
}

