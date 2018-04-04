#include "epsol/meta/visitor.h"
#include <iostream>
#include <string>

using namespace epsol::meta;

struct D1; struct D2;
struct D1A; struct D1B;

using BV = DefineVisitor<D1, D2>;
using DV = DefineVisitor<D1A, D1B>;

struct B {
    EPSOL_VISITABLE(BV);
    virtual ~B() {}
};

struct D1 : public B {
    EPSOL_VISITABLE(DV)
    EPSOL_ACCEPT_VISITOR_FROM(B)
    int a = 1;
};

struct D1A : public D1 {
    EPSOL_ACCEPT_VISITOR_FROM(D1)
    std::string d = "d1a";
};

struct D1B : public D1 {
    EPSOL_ACCEPT_VISITOR_FROM(D1)
    std::string d = "d1b";
};

struct D2 : public B {
    EPSOL_ACCEPT_VISITOR_FROM(B)
    std::string s = "hahah";
};

struct DVisitorImpl : public DV::Const {
    EPSOL_VISITING(D1A, d1a) {
        std::cout << d1a.d << '\n';
    }
    EPSOL_VISITING(D1B, d1b) {
        std::cout << d1b.d << '\n';
    }
};

struct VMutable : public BV::Mutable {
    EPSOL_VISITING(D1, d1) {
        std::cout << "d1: " << d1.a << '\n';
        d1.a = 1000; // ok VMutable is mutable visitor
        d1.AcceptVisitor(DVisitorImpl());
    }

    EPSOL_VISITING(D2, d2) {
        std::cout << "d2: " << d2.s << '\n';
        d2.s = "10000000"; // ok, VMutable is mutable visitor
    }
};

struct VConst : public BV::Const {
    EPSOL_VISITING(D1, d1) {
        std::cout << "d1.a = " << d1.a << '\n';
        // d1.a = 10000 // error, assignment to const reference
    }
    EPSOL_VISITING(D2, d2) {
        std::cout << "d2.s = " << d2.s << '\n';
    }
};

int main() {
    VMutable vi;
    std::unique_ptr<B> d1a = std::make_unique<D1A>(),
                       d1b = std::make_unique<D1B>(),
                       d2 = std::make_unique<D2>();
    d1a->AcceptVisitor(VMutable());
    d1b->AcceptVisitor(VMutable());
    d2->AcceptVisitor(vi);

    std::cout << '\n';

    d1a->AcceptVisitor(VConst());
    d2->AcceptVisitor(VConst());
}
