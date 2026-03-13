#include "Identidad.h"

// Constructor: inicializa la referencia a la cola de eventos
ModuloIdentidad::ModuloIdentidad(EventQueue& colaEventos)
    : queueEntrada(colaEventos) {}

// Procesa el estado actual de la interfaz
void ModuloIdentidad::procesarEstadoActual(const std::string& iface, const std::string& ip, const std::string& mac) {
    EstadoIdentidad actual{ip, mac};

    auto it = estadosPrevios.find(iface);
    if (it != estadosPrevios.end()) {
        EstadoIdentidad& previo = it->second;
        if (previo.ip != actual.ip || previo.mac != actual.mac) {
            generarEventoCambio(iface, previo, actual);
        }
    }

    // Actualiza el estado previo de la interfaz
    estadosPrevios[iface] = actual;
}

// Genera un evento de cambio de identidad y lo envía a la cola thread-safe
void ModuloIdentidad::generarEventoCambio(const std::string& iface, const EstadoIdentidad& anterior, const EstadoIdentidad& actual) {
    Evento e;
    e.tipo = Evento::Tipo::CAMBIO_IDENTIDAD;   // Tipo definido en evento.h
    e.interfaceName = iface;
    e.valorPrevio = "IP: " + anterior.ip + ", MAC: " + anterior.mac;
    e.valorNuevo  = "IP: " + actual.ip + ", MAC: " + actual.mac;

    queueEntrada.push(e);
}