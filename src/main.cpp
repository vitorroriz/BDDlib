
#include <iostream>
#include "Manager.h"

using namespace ClassProject;

int main(int argc, char* argv[])
{
    Manager* m = new Manager();
    BDD_ID a = m->createVar("a");
    BDD_ID b = m->createVar("b");
    BDD_ID c = m->createVar("c");
    BDD_ID d = m->createVar("d");
    /*m->and2(a,c);

    BDD_ID f = m->or2(m->and2(a,b),m->and2(m->neg(a),c));

    BDD_ID g = m->or2(m->and2(a,m->neg(b)),m->and2(m->neg(a),m->neg(c)));

    m->or2(m->and2(a,b),c);

    m->neg(d);
    BDD_ID ANDab = m->and2(a,b);
    BDD_ID ORab = m->or2(a,b);
    BDD_ID NANDab = m->nand2(a,b);
    BDD_ID NORab = m->nor2(a,b);
    BDD_ID XORab = m->xor2(a,b);

    BDD_ID ANDabc = m->and2(ANDab,c);
    BDD_ID ORabc = m->or2(ORab,c);
    BDD_ID NANDabc = m->nand2(NANDab,c);
    BDD_ID NORabc = m->nor2(NORab,c);
    BDD_ID XORabc = m->xor2(XORab,c);

    m->and2(ANDabc,d);
    m->or2(ORabc,d);
    m->nand2(NANDabc,d);
    m->nor2(NORabc,d);
    m->xor2(XORabc,d);*/

    BDD_ID XORab = m->xor2(a,b);
    cout << "XORab = " << XORab << endl;
    BDD_ID T2 = m->xor2(a,b);
    cout << "T2 = " << T2 << endl;

    BDD_ID XORabc = m->xor2(XORab,c);
     cout << "XORabc = " << XORabc << endl;

    cout << "XORabbc = " << m->xor2(XORabc,d) << endl;

    m->printUniqueTable();
}


