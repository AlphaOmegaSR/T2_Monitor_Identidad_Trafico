#include <iostream>

#include "Analisis.h"
#include "Evento.h"
#include "EventQueue.h"

//Comando para compilar: g++ src/*.cpp -Iinclude -o monitor -lpcap -pthread
//             ejecutar: ./monitor 

extern EventQueue queueEntrada;
extern EventQueue queueSalida;

/*
-----------------------------------------------------
            Loop Principal del Modulo
-----------------------------------------------------
*/
void iniciarAnalisis(){
    std::cout << "[Analisis]: Modulo iniciado\n";

    while(true){
        //1. Recibir evento
        Evento evento = queueEntrada.pop();

        //2. Actualizar estado interno
        actualizarEstado(evento);

        //3. Evaluar reglas de la anomalia
        detectarAnomalias(evento);
        
        //4. Reenviar evento original
        queueSalida.push(evento);
    }
}

/*
-----------------------------------------------------
            Mantener Estado Original
-----------------------------------------------------
*/
void actualizarEstado(const Evento& evento){
    switch(evento.tipo){
        case TipoEvento::ARP:
            std::cout << "[Analisis]: ARP detectado\n";
            break;

        case TipoEvento::ICMP:
            std::cout << "[Analisis]: ICMP detectado\n";
            break;
        
        case TipoEvento::IP_CHANGE:
            std::cout << "[Analisis]: Cambio de IP detectado\n";
            break;

        case TipoEvento::MAC_CHANGE:
            std::cout << "[Analisis]: Cambio de MAC detectado\n";
            break;

        case TipoEvento::UNKNOWN:
            std::cout << "[Analisis]: Evento desconocido detectado\n";
            break;

        default:
            break;
    }

    //Aqui se actualizaran variables contadoras y registros de informacion
}

/*
-----------------------------------------------------
            Evaluar Reglas de Anomalia
-----------------------------------------------------
*/
void detectarAnomalias(const Evento& evento){

    //Aqui se implementaran las reglas definidas

    /*
    if(contadorICMP > 5){
        generarAnomalia(
            "ICMP repetitivo detectado",
            NivelRiesgo::MEDIO,
            evento
        );
    }
    */
}

/*
-----------------------------------------------------
            Crear Evento de Anomalia
-----------------------------------------------------
*/
void generarAnomalia(const std::string& descripcion, NivelRiesgo riesgo, const Evento& eventoOriginal){
    Evento anomaly;

    anomaly.tipo = TipoEvento::ANOMALY;
    anomaly.descripcion = descripcion;
    anomaly.nivelRiesgo = riesgo;
    anomaly.origenModulo = "Analisis";

    //Copiar informacion relevante
    anomaly.ipOrigen = eventoOriginal.ipOrigen;
    anomaly.macOrigen = eventoOriginal.macOrigen;
    anomaly.timestamp = eventoOriginal.timestamp;

    queueSalida.push(anomaly);

    std::cout << "[Analisis]: ANOMALIA" << descripcion << "\n";
}


