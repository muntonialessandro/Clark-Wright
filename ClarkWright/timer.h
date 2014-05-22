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

#ifndef TIMER_H
#define TIMER_H

#include <QString>

#include <time.h>
#include <iostream>

/**
 * @brief The Timer class
 * Classe utilizzata per l'utilizzo del timer per il calcolo dei tempi degli algoritmi
 */

class Timer
{

public:
    Timer (QString _caption) : caption(_caption) {
        secs = 0.f;
        start();
    }

    inline void start() {
        _start = clock();
    }

    inline void stop_and_print() {
        _stop = clock();
        float cycles = _stop - _start;
        secs = ((float)cycles) / ((float)CLOCKS_PER_SEC);
        std::cout << caption.toStdString() << " [" << secs << " secs]" << std::endl;
    }

    inline float delay() {
        return secs;
    }

private:
    QString caption;
    clock_t _start, _stop;
    float secs;

};

#endif // TIMER_H
