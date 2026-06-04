#ifndef CARATTERISTICHE_H
#define CARATTERISTICHE_H


class Caratteristiche
{
public:
    enum linea { biscotti_da_prima_colazione, biscotti_da_te,torte_forno, crostate, torte_salate };
    enum impasto { al_burro, alle_mandorle, pasta_frolla, pasta_sfoglia, classico, con_lievito_madre, ai_cereali, alla_vaniglia };
    enum size { midi, tradizionale, maxi };
    enum tipo { dritto, curvo };
    enum serie { in_vaschetta, cornetto, su_stecco, biscotto, mignon, normal };
    enum formato: unsigned int { mini=0, medium=1, famiglia=2 };
    enum applicazione : unsigned int {unitaria=0, su_min=1 };
    enum scopo { compleanno, laurea, battesimo, Altro };
};

#endif // CARATTERISTICHE_H
