#include<vector>

class Triangoli {
  public:
    Triangoli (std::vector<double> , bool );
    std::vector<std::vector<double>> coord(std::vector <double> , std::vector <double>);
    double perimetro();
    double area(double);
    std::vector <double> angoli();
    std::vector <double> altezze(double);
    std::vector <double> bari (std::vector<std::vector<double>>);
    std::vector <double> in(std::vector<std::vector<double>>, double, double);
    std::vector <double> orto(std::vector<std::vector<double>>);
    std::vector <double> circo(std::vector <std::vector<double>>, double);
    std::vector<std::vector<double>> coord_not(std::vector<std::vector<double>> , double, double);
    void disegnetto (std::vector<std::vector<double>>, std::vector<std::vector<double>>);
  private:
    std::vector <double> l;
};

std::vector<double> sinus(double, double, double);
std::vector<double> carnot(double, double, double);
void conf_lat(std::vector<double>, bool);
bool dis_tri(std::vector<double>);
void pulisci_cin();
template <class A> void lettura(A &);
