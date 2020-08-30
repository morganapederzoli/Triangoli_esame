#include<iostream>
#include<cmath>
#include<vector>
#include<sstream>
#include"triangoli.h"

//METODI

Triangoli::Triangoli(std::vector <double> L, bool x) {
	if(x) {
		for (int i=0; i<2;  i++)
			for (int j=i+1;  j<3;  j++)
				if (L[j] > L[i])
					std::swap(L[i],L[j]);
		for(int i=0; i<3; ++i)
			l.push_back(L[i]);
	}
	else
		L.~vector();
}

std::vector<std::vector<double>> Triangoli::coord(std::vector <double> h, std::vector <double> a) {
		std::vector<std::vector<double>> coordinate{
			{0,0},
			{l[0],0},
			{l[0]-l[1]*cos(a[2]),h[0]}
		};
		return coordinate;
}

double Triangoli::perimetro() {
	double P = l[0]+l[1]+l[2];
	std::cout<<"Il Perimetro del triangolo è"<<'\t'<<P<<std::endl<<std::endl;
	return P;
}

double Triangoli::area(double P) {
	double A, p;
	p = P/2;
	A = sqrt(p*(p-l[0])*(p-l[1])*(p-l[2]));
	std::cout<<"L'Area del triangolo è"<<'\t'<<A<<std::endl<<std::endl;
	return A;
}

std::vector <double> Triangoli::angoli() {
	std::vector <double> a;
	for (int i=0; i<3; ++i) {
		int y, z;
		if(i<2)
			y=i+1;
		else
			y=i-2;
		if (i<1)
			z=i+2;
		else
			z=i-1;
	  	a.push_back(acos((-pow(l[i],2)+pow(l[y],2)+pow(l[z],2))/(2*l[y]*l[z])));
		std::cout<<"L'angolo opposto a "<<l[i]<<"\tè di "<<a[i]*180/M_PI<<"\tgradi"<<std::endl;
	}
	std::cout<<std::endl;
	return a;
}

std::vector <double> Triangoli::altezze(double A) {
	std::vector <double> h;
	for (int i=0; i<3; ++i) {
		h.push_back((A*2)/l[i]);
		std::cout<<"L'altezza che cade su "<<l[i]<<"\tè "<<h[i]<<std::endl;
	}
	std::cout<<std::endl;
	return h;
}

std::vector<double> Triangoli::bari (std::vector<std::vector<double>> coordinate) {
	std::vector<double> coB;
	coB.push_back((coordinate[0][0]+coordinate[1][0]+coordinate[2][0])/3);
	coB.push_back((coordinate[0][1]+coordinate[1][1]+coordinate[2][1])/3);
	return coB;
}

std::vector <double> Triangoli::in(std::vector<std::vector<double>> coordinate, double P, double A) {
	std::vector <double> coI;
	coI.push_back((l[2]*coordinate[0][0]+l[2]*coordinate[1][0]+l[0]*coordinate[2][0])/P);
	coI.push_back((l[2]*coordinate[0][1]+l[2]*coordinate[1][1]+l[0]*coordinate[2][1])/P);
	coI.push_back(2*A/P);
	return coI;
}

std::vector <double> Triangoli::orto(std::vector<std::vector<double>> coordinate) {
	std::vector <double> coO;

		double den= (coordinate[2][1]-coordinate[1][1])*(coordinate[2][0]-coordinate[0][0]) - (coordinate[2][0]-coordinate[1][0])*(coordinate[2][1]-coordinate[0][1]);
		double ynum=(coordinate[1][0]*(coordinate[0][0]-coordinate[2][0])+coordinate[1][1]*(coordinate[0][1]-coordinate[2][1]))*(coordinate[2][0]-coordinate[1][0])-(coordinate[2][0]-coordinate[0][0])*(coordinate[0][0]*(coordinate[1][0]-coordinate[2][0])+coordinate[0][1]*(coordinate[1][1]-coordinate[2][1]));
		double xnum=(coordinate[1][0]*(coordinate[0][0]-coordinate[2][0])+coordinate[1][1]*(coordinate[0][1]-coordinate[2][1]))*(coordinate[2][1]-coordinate[1][1])-(coordinate[2][1]-coordinate[0][1])*(coordinate[0][0]*(coordinate[1][0]-coordinate[2][0])+coordinate[0][1]*(coordinate[1][1]-coordinate[2][1]));

		coO.push_back(-xnum/den);
		coO.push_back(ynum/den);
	return coO;
}

std::vector <double> Triangoli::circo(std::vector<std::vector<double>> coordinate, double A) {
	std::vector <double> coC;
	double den = 2*(coordinate[0][0]*(coordinate[1][1]-coordinate[2][1])+coordinate[1][0]*(coordinate[2][1]-coordinate[0][1])+coordinate[2][0]*(coordinate[0][1]-coordinate[1][1]));
	double square1=coordinate[0][0]*coordinate[0][0]+coordinate[0][1]*coordinate[0][1];
	double square2=coordinate[1][0]*coordinate[1][0]+coordinate[1][1]*coordinate[1][1];
	double square3=coordinate[2][0]*coordinate[2][0]+coordinate[2][1]*coordinate[2][1];
	double xnum=square1*(coordinate[1][1]-coordinate[2][1])+square2*(coordinate[2][1]-coordinate[0][1])+square3*(coordinate[0][1]-coordinate[1][1]);
	double ynum=-square1*(coordinate[1][0]-coordinate[2][0])-square2*(coordinate[2][0]-coordinate[0][0])-square3*(coordinate[0][0]-coordinate[1][0]);

	coC.push_back(xnum/den);
	coC.push_back(ynum/den);
	coC.push_back(l[0]*l[1]*l[2]/(4*A));
	return coC;
}

std::vector<std::vector<double>> Triangoli::coord_not(std::vector<std::vector<double>> coordinate, double P, double A){
	std::vector<double> coB, coI, coO, coC;
	coB=Triangoli::bari(coordinate);
	coI=Triangoli::in(coordinate, P, A);
	coC=Triangoli::circo(coordinate, A);
	coO=Triangoli::orto(coordinate);

	std::vector<std::vector<double>> punti_notevoli;
	punti_notevoli.push_back(coB);
	punti_notevoli.push_back(coI);
	punti_notevoli.push_back(coC);
	punti_notevoli.push_back(coO);
	return punti_notevoli;
}

void Triangoli::disegnetto (std::vector<std::vector<double>> coordinate,std::vector<std::vector<double>> punti_notevoli){
	char k;
	double xmin, xmax, ymin /*= - punti_notevoli[2][2]*/, ymax;
	std::stringstream commandsToTerminal;
	commandsToTerminal << "gnuplot -p -e \" set title \'Triangolo\'; "
			<< "set grid; "
			<< "set size ratio -1; "
			<< "set key off; "
			<< "set xrange [-0.5:" << coordinate[1][0] + 0.5 << "]; "
			<< "set yrange [-0.5:" << coordinate[2][1] + 0.5 << "]; "
			<< "set object 1 polygon from "<<coordinate[0][0]<<","<<coordinate[0][1]<<" to "<<coordinate[1][0]<<","<<coordinate[1][1]<<" to "<<coordinate[2][0]<<","<<coordinate[2][1]<<" to "<<coordinate[0][0]<<","<<coordinate[0][1]<<"; "
 			<< "set object 1 fc rgb "<<"\'cyan\'"<<" fillstyle solid 1.0 border lt -1; "
			<< "plot sqrt(-1)\" ";
	system(commandsToTerminal.str().c_str());
	commandsToTerminal.str(std::string());
	std::cout<<"Oltre a disegnare il triangolo sono anche in grado di disegnare i punti suoi notevoli, la circonferenza inscritta e quella circoscritta.\n";
	std::cout<<"Se vuoi che lo faccia premi s, altrimenti premi n\n";
	lettura(k);
	while(true){
		if(k=='s'){
			if (punti_notevoli[2][0]-punti_notevoli[2][2]<coordinate[0][0]) xmin=punti_notevoli[2][0]-punti_notevoli[2][2]-0.5;
			else xmin=-0.5;
			if (punti_notevoli[2][0]+punti_notevoli[2][2]>coordinate[1][0]) xmax=punti_notevoli[2][0]+punti_notevoli[2][2]+0.5;
			else xmax=coordinate[1][0]+0.5;
			if (punti_notevoli[2][1]-punti_notevoli[2][2]<coordinate[0][1]) ymin=punti_notevoli[2][1]-punti_notevoli[2][2]-0.5;
			else ymin=-0.5;
			if (punti_notevoli[2][1]+punti_notevoli[2][2]>coordinate[2][1]) ymax=punti_notevoli[2][0]+punti_notevoli[2][2]+0.5;
			else ymax=coordinate[1][0]+0.5;
			
		commandsToTerminal  << "gnuplot -p -e \" set title \'TriangoloPunti\'; "
							<< "set grid; "
							<< "set size ratio -1; "
							<< "set key off; "
							<< "set xrange ["<<xmin<<":" << xmax << "]; "
							<< "set yrange ["<<ymin<< ":" << ymax << "]; "
							<< "set object 2 polygon from "<<coordinate[0][0]<<","<<coordinate[0][1]<<" to "<<coordinate[1][0]<<","<<coordinate[1][1]<<" to "<<coordinate[2][0]<<","<<coordinate[2][1]<<" to "<<coordinate[0][0]<<","<<coordinate[0][1]<<"; "
							<< "set object 2 fc rgb \'cyan\' fillstyle solid 1.0 border lt -1; "
							<< "set label at "<<punti_notevoli[0][0]<<","<<punti_notevoli[0][1]<<" \' Baricentro\' point pointtype 7 pointsize 2; "
							<< "set label at "<<punti_notevoli[1][0]<<","<<punti_notevoli[1][1]<<" \' Incentro\' point pointtype 7 pointsize 2; "
							<< "set label at "<<punti_notevoli[2][0]<<","<<punti_notevoli[2][1]<<" \' Circocentro \' point pointtype 7 pointsize 2; "
							<< "set label at "<<punti_notevoli[3][0]<<","<<punti_notevoli[3][1]<<" \' Ortocentro\' point pointtype 7 pointsize 2; "
							<< "set object 3 circle at " <<punti_notevoli[1][0]<<","<<punti_notevoli[1][1]<<" size " << punti_notevoli[1][2]<<" fc rgb \'red\'; " 
							<< "set object 4 circle at " <<punti_notevoli[2][0]<<","<<punti_notevoli[2][1]<<" size " << punti_notevoli[2][2]<<" fc rgb \'red\'; " 
							<< "plot sqrt(-1) \" ";
			system(commandsToTerminal.str().c_str());
			break;
		}
		else if (k=='n'){
			std::cout<<"ok fa lo stesso\n";
			break;
		}
		else
			std::cout<<"Dai riprova!\n";
	}
}

//FUNZIONE TEMPLATE

template <class A> void lettura(A &a) {
	bool x = true;
	while(x) {
		x = false;
		std::cin >> a;
		while (std::cin.fail()) {
			std::cout <<"Suvvia, numeri, non lettere!\n";
			pulisci_cin();
			x = true;
		}
	}
}

//FUNZIONI ESTERNE

std::vector<double> sinus(double A, double bD, double cD) {
	double aR = (180-(bD+cD))*(M_PI/180);
	std::vector<double> l;
	l.push_back(A);
	l.push_back((A/sin(aR))*(sin(bD*(M_PI/180))));
	l.push_back((A/sin(aR))*(sin(cD*(M_PI/180))));
	return l;
}

std::vector<double> carnot(double A, double B, double aD) {
	std::vector<double> l;
	l.push_back(A);
	l.push_back(B);
	l.push_back(sqrt((A*A)+(B*B)-2*A*B*cos(aD*(M_PI/180))));
	return l;
}

void conf_lat(std::vector<double> l, bool g) {
	int q;
	if (l[0]==l[1] || l[0]==l[2] || l[1]==l[2]) {
		if (l[0]==l[1] && l[0]==l[2])
	    		q=3;
		else
	     		q=2;
	}
	else q=1;

	if(g) {
		std::cout<<"\nÈ un triangolo ";
		if( fabs(l[0]-hypot(l[1],l[2]))<1E-9 || fabs(l[1]-hypot(l[0],l[2]))<1E-9 || fabs(l[2]-hypot(l[1],l[0]))<1E-9)
			std::cout<<"rettangolo ";
		if (q==3) std::cout<<"equilatero ";
		else if (q==2) std::cout<<"isoscele ";
		else if (q==1) std::cout<<"scaleno ";
		std::cout<<std::endl<<std::endl;
	}
}

bool dis_tri(std::vector<double> l) {
	bool g;
	for (int i=0; i<3; ++i) {
		int y, z;
		if (i<2) y=i+1;
		else y=i-2;
		if (i<1) z=i+2;
		else z=i-1;
		if (l[i]<l[y]+l[z] && l[i]>fabs(l[y]-l[z])) {
			g=true;
		}
		else
			g=false;
	}
	conf_lat (l, g);
	return g;
}

void pulisci_cin (){
	std::cin.clear();			
	std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
}

//MAIN

int main() {
	int s, check;
	bool g;
	char k,j;
	double P, Area, o[3];
	std::vector <double> a, h, l;
	std::vector <std::vector<double>> coordinate, punti_notevoli;
	
	std::cout<<"\nCiao, io lavoro con i triangoli!\nIl mio compito è costruire triangoli a partire dai dati che mi fornisci.\n\n";
	while (true) {
		std::cout<<"Scegli tu:\n 1_ se vuoi fornirmi i valori dei tre lati digita 1\n 2_ se vuoi fornirmi i valori di un lato e due angoli, digita 2\n 3_ se vuoi fornirmi i valori di due lati e dell'angolo tra essi compreso digita 3\n 4_ se vuoi uscire da questo programma digita 0\n\n";
		lettura(s);
		pulisci_cin();
		check = 1;
		switch(s) {
			case(1) : {
				std::cout<<"\nTrilatula\n\n";
				l = {0,0,0};
				while (check) {
				std::cout<<"Dammi tre numeri e ti dirò se possono formare un triangolo\n";
				for (double &i:l) {
					lettura (i);
					pulisci_cin();
				}
				g=dis_tri(l);
				if (g) {
					std::cout<<"Vuoi avere informazioni su questo triangolo? Se sì digita s, altrimenti digita n\n";
					while (g) {
						lettura(k);
						pulisci_cin();
						if(k=='s' || k=='n') {
							switch (k) {
								case ('s') : {
									Triangoli T(l, g);
									P = T.perimetro ();
									Area = T.area (P);
									a = T.angoli ();
									h = T.altezze(Area);
									coordinate = T.coord(h,a);
									std::cout<<"Hey! Vuoi che ti disegni questo triangolo? Se sì premi s altrimenti andrà bene qualsiasi altro carattere\n";
									lettura(k);
									pulisci_cin();
									if (k=='s') {
										punti_notevoli = T.coord_not(coordinate, P, Area);
										T.disegnetto(coordinate, punti_notevoli);
									}
									else std::cout<<"ok fa lo stesso\n";
									break;
								}
								case ('n') : break;
							}
							break;
						}
						else {
							std::cout<<"Dai riprova!\n";
						}
					}
				}
				else if(!g)
					std::cout<<"\nMi dispiace non è un triangolo\n";
				std::cout<<"Vuoi usare ancora questa stessa funzione? Se sì, premi 1, altrimenti premi 0\n";
				lettura(check);
				pulisci_cin();
				std::cout<<std::endl;
				}
				break;
			}
			case (2) : {
				std::cout<<"\nDuangula\n\n";
				std::vector <double> l;
				while (check) {
					std::cout<<"Vuoi darmi angoli in radianti? Se sì premi s altrimenti, se vuoi darmeli in gradi, premi un qualunque altro tasto\n";
					lettura(j);
					pulisci_cin();
					std::cout<<"Fornisci prima il valore del lato, poi i valori dei due angoli ad esso adiacenti\n";
					for(double &i:o){
						lettura(i);
						pulisci_cin();
					}
					if (j == 's') {
						 o[1] = (o[1]*360/(2*M_PI));
						 o[2] = (o[2]*360/(2*M_PI));
					}
					if  (o[0]<0.00001 || o[1]>=180 || o[2]>=180 || o[1]+o[2]>=180){
						std::cout<<"Mi dispiace non è un triangolo"<<std::endl;
						std::cout<<"Vuoi usare ancora questa stessa funzione? Se sì, premi 1, altrimenti premi 0\n";
						lettura(check);
						pulisci_cin();
						std::cout<<std::endl;
					}
					else {
						l = sinus(o[0], o[1], o[2]);
						g = true;
						Triangoli T (l, g);
						std::cout<<"Con i numeri che mi hai dato ho costruto un triangolo con i seguenti lati:\n"
							 <<l[0]<<" "<<l[1]<<" "<<l[2]<<std::endl;
						conf_lat (l, g);
						std::cout<<"Vuoi avere informazioni su questo triangolo? Se sì digita s, altrimenti digita n\n";
						while (g) {
							lettura(k);
							pulisci_cin();
							if(k=='s' || k=='n') {
								switch (k) {
									case ('s') : {
										P = T.perimetro ();
										Area = T.area (P);
										a = T.angoli ();
										h = T.altezze(Area);
										coordinate = T.coord(h,a);
										std::cout<<"Hey! Vuoi che ti disegni questo triangolo? Se sì premi s altrimenti andrà bene qualsiasi altro carattere\n";
										lettura(k);
										pulisci_cin();
										if (k=='s') {
											punti_notevoli = T.coord_not(coordinate, P, Area);
											T.disegnetto(coordinate, punti_notevoli);
										}
										else std::cout<<"ok fa lo stesso\n";
										break;
									}
									case ('n') : break;
								}
								break;
							}
							else {
								std::cout<<"Dai riprova!\n";
							}
						}
						std::cout<<"Vuoi usare ancora questa funzione? Se sì, premi 1, altrimenti premi 0\n";
						lettura(check);
						pulisci_cin();
						std::cout<<std::endl;
					}
				}
				break;
			}

			case (3) : {
				std::cout<<"\nDulatula\n\n";
				std::vector<double> l;
				while (check){
					std::cout<<"Vuoi darmi angoli in radianti? Se sì premi s altrimenti, se vuoi darmeli in gradi, premi un qualunque altro tasto\n";
					lettura(j);
					pulisci_cin();
					std::cout<<"Fornisci prima i valori dei due lati, poi il valore dell'angolo tra essi compreso\n";
					for(double &i:o){
						lettura(i);
						pulisci_cin();
					}
					if (j == 's')  
						o[2] = (o[2]*360/(2*M_PI));
					if  (o[0]<0.00001 || o[1]<0.00001 || o[2]>=180) {
						std::cout<<"Mi dispiace non è un triangolo"<<std::endl;
						std::cout<<"Vuoi usare ancora questa funzione? Se sì, premi 1, altrimenti premi 0\n";
						lettura(check);
						pulisci_cin();
						std::cout<<std::endl;
					}
					else {
						l = carnot(o[0], o[1], o[2]);
						g = true;
						Triangoli T (l, g);
						std::cout<<"Con i numeri che mi hai dato ho costruto un triangolo con i seguenti lati:\n"<<l[0]
							 <<" "<<l[1]<<" "<<l[2]<<std::endl;
						conf_lat (l, g);
						std::cout<<"Vuoi avere informazioni su questo triangolo? Se sì digita s, altrimenti digita n\n";
						while (g) {
							lettura(k);
							pulisci_cin();
							if(k=='s' || k=='n') {
								switch(k) {
									case('s') : {
										P = T.perimetro();
										Area = T.area(P);
										a = T.angoli();
										h = T.altezze(Area);
										coordinate = T.coord(h,a);
										std::cout<<"Hey! Vuoi che ti disegni questo triangolo? Se sì premi s altrimenti andrà bene qualsiasi altro carattere\n";
										lettura(k);
										pulisci_cin();
										if(k=='s') {
											punti_notevoli = T.coord_not(coordinate, P, Area);
											T.disegnetto(coordinate, punti_notevoli);
										}
										else
											std::cout<<"ok fa lo stesso\n";
									break;
									}
									case('n') : break;
								}
							break;
							}
							else {
								std::cout<<"Dai riprova!\n";
							}
						}
						std::cout<<"Vuoi usare ancora questa funzione? Se sì, premi 1, altrimenti premi 0\n";
						lettura(check);
						pulisci_cin();
						std::cout<<std::endl;
					}
				}
				break;
			}
			case(0) :
				std::cout<<"\nÈ stato un piacere, alla prossima!\n";
				return 0;
		}
	}
}
