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

bool Saving::operator ==(Saving &other) const
{
    if (this->value == other.getValue() && this->idc1 == other.getIdC1() && this->idc2 == other.getIdC2())
        return true;
    return false;
}

bool Saving::operator !=(Saving &other) const
{
    return !(*this == other);
}

bool Saving::operator <(Saving &other) const
{
    if (this->value < other.getValue()) return true;
    if (this->value == other.getValue()){
        if (this->idc1 < other.getIdC1()) return true;
        if (this->idc1 == other.getIdC1()){
            if (this->idc2 < other.getIdC2()) return true;
        }
    }
    return false;
}

bool Saving::operator >(Saving &other) const
{
    if (this->value > other.getValue()) return true;
    if (this->value == other.getValue()){
        if (this->idc1 > other.getIdC1()) return true;
        if (this->idc1 == other.getIdC1()){
            if (this->idc2 > other.getIdC2()) return true;
        }
    }
    return false;
}

bool Saving::operator <=(Saving &other) const
{
    return (*this == other || *this < other);
}

bool Saving::operator >=(Saving &other) const
{
    return (*this == other || *this > other);
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

bool Saving::sortSavings(const Saving &s1, const Saving &s2){
    Saving ss1 = s1;
    Saving ss2 = s2;
    return ss1.getValue() > ss2.getValue(); // Ordinamento in senso decrescente.
}


void Saving::setEnable(bool value){
    this->enable = value;
}

void Saving::swapClients(){
    int temp_id = this->getIdC2();
    this->idc2 = this->getIdC1();
    this->idc1 = temp_id;
}
