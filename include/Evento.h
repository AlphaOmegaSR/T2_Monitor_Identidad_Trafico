#pragma once
#include <string>

enum class TipoEvento
{
    ARP,
    ICMP,
    IP_CHANGE,
    MAC_CHANGE,
    UNKNOWN,
    ANOMALY
};

enum class NivelRiesgo
{
    BAJO,
    MEDIO,
    ALTO,
    CRITICO,
    NONE
};

struct Evento
{
    TipoEvento tipo = TipoEvento::UNKNOWN;

    std::string origenModulo;
    std::string descripcion;

    std::string ipOrigen;
    std::string ipDestino;

    std::string macOrigen;
    std::string macDestino;

    std::string timestamp;

    NivelRiesgo nivelRiesgo = NivelRiesgo::NONE;
};