#ifndef POINTS_H
#define POINTS_H

namespace XmlParser {

class IntPoint {

private:
    
    int m_a;
    int m_b;

public:
    
    IntPoint(int a, int b) 
        : m_a(a), m_b(b) {
    }

    int a(){ return m_a; }
    int b(){ return m_b; }

};

class DoublePoint {

private:
    
    double m_a;
    double m_b;

public:
    
    DoublePoint(double a, double b)
        : m_a(a), m_b(b) {
    }

    double a(){ return m_a; }
    double b(){ return m_b; }

};

} // XmlParser namespaces
#endif // POINTS_H
