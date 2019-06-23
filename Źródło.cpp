//3) Program umożliwiający obliczenia na macierzach(1D lub 2D) (trudność 8 / 10 dla wariantu 1D
	//oraz 10 / 10 dla wariantu 2D)
	//- podstawowe działania : +, -, *, /															<-------dzielenie to do
	//-przykład
	//A = [1 2 3; 4 5 6]
	//B = [1 2 3; 4 5 6]
	//C = A + B
	//- interfejs użytkownika umożlwiający wygodną pracę
	//- opcjonalnie(zapis i odczyt z pliku)		

//zapis						wybor_zapis = 1
//brak zapisu				wybor_zapis = 2
// wyczytywanie wszystkiego wybor_wypis = 1
// wyczytywanie ostatniego  wybor_wypis = 2

#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<math.h>
using namespace std;
#define TIME   SYSTEMTIME st; GetLocalTime(&st);
#define ZMIENNE int n, int m, int n1, int n2, int m1, int m2, long double **wynik, long double **uzytkownika1, long double **uzytkownika2, int znak

typedef enum {
	Blad_rozm = 0,
	Menu_glowne = 1,
	Menu_koncowe = 2,
	Menu_ustawien = 3,
	Ustawienia_okna = 4,
	Ustawienia_wypisywania = 5,
	Ustawienia_zapisu = 6,
	Blad_wyboru = 7,
	Zako_ustawien = 8,
	Error = 9,
	Wybor_dzialania = 10,
	Brak_dzialan = 11,
	info = 12,
	menu_info = 13,
	Mnozenie = 14,
	menu_info2 = 15,
} TEXT_ID;

static const char * TEXTS[]{
	"\nBlednie podane rozmiary macierzy!\n\n",						//0
	"Wybierz od czego zaczniemy. Wpisz numer odpowiadajacy\n"		//1
	"wybranej przez Ciebie opcji i zatwierdz enterem.\n"
	"1- Kalkulator macierzy\n"
	"2- Informacje o macierzy i mnozenie przez liczbe\n"
	"3- Ustawienia\n"
	"4- Wyjscie\n\n",
	"Wybierz jedna z ponizszych opcji:\n"							//2
	"1- Jezeli chcesz kontynuowac obliczenia\n"
	"2- Jezeli chcesz powrocic do menu\n"
	"3- Jezeli chcesz zakonczyc prace\n\n",
	"Wybierz ustawienia:\n"											//3
	"1 - Okna\n"
	"2 - Wypisywania wynikow w oknie kalkulatora\n"
	"3 - Zapisywania wynikow do pliku \"Wyniki\"\n"
	"4 - Wyjscie\n\n",
	"Nieodpowiedni wyglad aplikacji prawdopodobnie \n"				//4
	"spowodowany jest nieodpowiednim ustawieniem okna \n"
	"konsoli. Kliknij na gorna belke okna aplikacji prawym \n"
	"przyciskiem myszy, a nastepnie wybierz opcje \n"
	"wlasciwosci.Preferowane ustawienia to : \n"
	"- Czcionka  8x12\n"
	"- Rozmiar buforu ekranu: \n"
	"  Jak najwiekszy\n"
	"- Rozmiar okna: \n"
	"\t- szerokosc > 58\n"
	"\t- wysokosc dowolna proponowane 82\n",
	"Wybierz wedle gustu:\n"										//5
	"1- Wypisywanie wszystkich (wykonanych przy danym \n"
	"uruchomieniu kalkulatora) dzialan\n"
	"2- Wypisywanie tylko ostatniego dzialania\n\n",
	"Wybierz wedle gustu:\n"										//6
	"1- Zapisywanie wszystkich (wykonanych przy danym \n"
	"uruchomieniu kalkulatora) dzialan do pliku Wyniki.txt\n"
	"2- Niezapisywanie\n\n",
	"Blednie podany wybor, zeby sprobowac jeszcze raz kliknij "		//7
	"dowolna cyfre\n\n",
	"Po dostosowaniu ustawien kliknij dowolna cyfre \n"				//8
	"i zatwierdz enterem.\n\n",
	"Blad, ktory nie mial prawa wystapic\n\n",						//9
	"\nWybierz dzialanie, ktore chcesz wykonac na powyzszych\n"		//10
	"macierzach poprzez wpisanie numeru poprzedzajacego wybor.\n",
	"\nZadne z dostepnych dzialan nie jest mozliwe do wykonania.\n"	//11
	"Sprobuj jeszcze raz wybrac jakie macierze beda brac udzial\n"
	"w dzialaniu. Aby kontynuowac kliknij dowolny klawisz.\n\n",
	"Na podanej macierzy nie mozliwe jest policzenie macierzy\n"	//12
	"dopelnien algebraicznych i odwrotnej.\n\n",
	"Wybierz jedna z ponizszych opcji:\n"							//13
	"1- Pomnoz podana macierz przez liczbe\n"
	"2- Przejdz prosto do kalkulatora macierzy\n"
	"3- Uzyskaj informacje o innej macierzy\n"
	"4- Wroc do menu\n"
	"5- Zakoncz prace\n\n",
	"Podaj liczbe, przez ktora nalezy przemnozyc podana macierz\n",	//14
	"Wybierz jedna z ponizszych opcji:\n"							//15
	"1- Pomnoz podana macierz przez inna liczbe\n"
	"2- Przejdz prosto do kalkulatora macierzy\n"
	"3- Uzyskaj informacje o innej macierzy\n"
	"4- Wroc do menu\n"
	"5- Zakoncz prace\n\n",
};

long double **Wynik_tworzenie_macierzy(int n, int m) {
	long double **wynik;
	wynik = new long double *[n];
	for (int i = 0; i < n; i++)
		wynik[i] = new long double[m];
	return wynik;
}

long double wyznacznik(int n, int m, long double **macierz) {
	if (n == m) {
		long double det = 0;
		if (n == 1) { det = macierz[0][0]; }
		else if (n == 2) {
			det = macierz[0][0] * macierz[1][1] - macierz[0][1] * macierz[1][0];
		//	cout << "det= " << det << " macierz[0][0] " << macierz[0][0] << " macierz[0][1] " << macierz[0][1] << " macierz[1][0] " << macierz[1][0] << " macierz[1][1] " << macierz[1][1] << endl;
		}
		else if (n == 3) {
			det = macierz[0][0] * macierz[1][1] * macierz[2][2] +
				macierz[0][1] * macierz[1][2] * macierz[2][0] +
				macierz[0][2] * macierz[1][0] * macierz[2][1] -
				macierz[0][2] * macierz[1][1] * macierz[2][0] -
				macierz[0][0] * macierz[1][2] * macierz[2][1] -
				macierz[0][1] * macierz[1][0] * macierz[2][2];
		//	cout << "det pod" << det << endl;
		}
		else if (n > 3) {
			int l = m;
			int x, y;
			x = n - 1;
			y = m - 1;
			int e = 0;
			int f = 0;
			long double ***podmacierz = new long double **[m];
			for (int i = 0; i < m; i++) {
				podmacierz[i] = new long double*[x];
				for (int j = 0; j < x; j++) {
					podmacierz[i][j] = new long double[y];
				}
			}
//			cout << podmacierz[0][0][0] << endl;
			for (int k = 0; k < m; k++) {
				for (int i = 0; i < x; i++) {
					for (int j = 0; j < y; j++) {
						podmacierz[k][i][j] = 0;
					}
				}
			}
//			cout << podmacierz[0][0][0] << endl;
//			cout << n << m << endl;
			for (int k = 0; k < l; k++) {
				e = 0;
				for (int i = 1; i < n; i++) {
					f = 0;
					for (int j = 0; j < m; j++) {
						if (j != k) {
//							cout << " k, e , f, i , j " << k << e << f << i << j << endl;
							podmacierz[k][e][f] = macierz[i][j];
							f += 1;
						}
					}
					e += 1;
				}
			}
			double v;
			int u;
			for (int j = 0; j < m; j++) {
				u = j + 2;
				v = pow(-1, u);
				det += (macierz[0][j]) * v * wyznacznik(x, y, podmacierz[j]);
			//	cout << "det " << det << "  macierz[0][" << j << "]" << macierz[0][j] << "  v" << v << "  wyznacznik(x, y, podmacierz[j])" << wyznacznik(x, y, podmacierz[j]) << endl;
			}
		}
		else {
			cout << TEXTS[Error];
			det = 0;
		}
		return det;
	}
	else { cout << "Wyznacznik nie istnieje dla podanej macierzy" << endl << endl; return 0; }
}

long double **Transponowanie(int n, int m, long double **macierz) {
	long double **MacierzT;
	MacierzT = new long double *[m];
	for (int i = 0; i < m; i++)
		MacierzT[i] = new long double[n];

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				MacierzT[i][j] = macierz[j][i];
			}
		}
	return MacierzT;
}

class Macierz {
private:

	int n, m;

public:
	long double **tablica2D;
	Macierz() { n = m = 0; }
	Macierz(int valn, int valm) {
		m = valm;
		n = valn;
		tablica2D = new long double *[n];
		for (int i = 0; i < n; i++)
			tablica2D[i] = new long double[m];
		int w, k;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				w = i;
				k = j;
				cout << "Wprowadz element do wiersza " << i + 1 << " i kolumny " << " " << j + 1 << " : ";
				cin >> tablica2D[w][k];
			}
		}
	}

	~Macierz() {
		/*for (int i = 0; i < n; i++) {
			delete[] tablica2D[i];
		}
		delete[] tablica2D;*/
	}

	void read() const {

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << tablica2D[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	long double Wyznacznik_Macierzy() {
		long double w = wyznacznik(n, m, tablica2D);
		return w;
	}

	long double **Macierz_Dopelnien() {
		long double **MacierzDopelnien;
		MacierzDopelnien = new long double *[n];
		for (int i = 0; i < n; i++)
			MacierzDopelnien[i] = new long double[m];
		if ((n == m) && (n > 1) && (m > 1) && (Wyznacznik_Macierzy() != 0)) {
			int d = n;
			int g = m;
			int a = n - 1;
			int b = m - 1;
			long double **MacierzD;
			MacierzD = new long double *[n];
			for (int i = 0; i < n; i++)
				MacierzD[i] = new long double[m];

			long double ****podmacierz;
			podmacierz = new long double ***[g];
			for (int k = 0; k < g; k++) {
				podmacierz[k] = new long double **[d];
				for (int i = 0; i < d; i++) {
					podmacierz[k][i] = new long double*[a];
					for (int j = 0; j < a; j++) {
						podmacierz[k][i][j] = new long double[b];
					}
				}
			}
			for (int i = 0; i < d; i++) {
				for (int j = 0; j < n; j++) {
					MacierzD[i][j] = 0;
				}
			}
			//			cout << a << n << b << m << endl;
			int x = 0, y = 0;
			for (int h = 0; h < g; h++) {
				//cout << "petla h:  " << endl;
				for (int k = 0; k < d; k++) {
					//cout << "petla k:  " << endl;
					x = 0;
					//cout << "x = 0" << endl;
					for (int i = 0; i < n; i++) {
						//	cout << "petla i:  " << endl;
					//		cout << "y = 0 " << endl;
						y = 0;
						for (int j = 0; j < d; j++) {
							//		cout << "petla j:  " << endl;
							//		cout << "h << k << i << j   " << h << k << i << j << endl;
							if ((i != h) && (j != k)) {
								//			cout << "h << k << x << y << i << j   " << h << k << x << y << i << j << endl;
								//			cout << "tablica2D[i][j]" << tablica2D[i][j] << endl;
								podmacierz[h][k][x][y] = tablica2D[i][j];
								//			cout << "podmacierz[h][k][x][y]" << podmacierz[h][k][x][y] << endl;
								y++;
								//			cout << "y++ " << y << endl;
								if (y == b) { continue; }
							}
							if (y == b) { continue; }
						}
						if (y == b) { x++; }
					}
				}
			}
			//int o = m - 1, p = n - 1;
			/////////////////////////////
			/*
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					for (int e = 0; e < a; e++) {
						for (int f = 0; f < b; f++) {
							cout << podmacierz[i][j][e][f] << "  ";
						}
						cout << endl;
					}
					cout << endl;
					cout << endl;
				}
				cout << endl;
				cout << endl;
			}*/
			double v;
			int u;
			//cout << "podmacierze utworzone" << endl;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					u = j + i + 2;
					v = pow(-1, u);
					/*
										cout << "1MacierzD[" << i << "][" << j << "]= " << MacierzD[i][j] << " = wyznacznik (" << "p, " << a << "o, " << b << "podmacierz[i][j])" << wyznacznik(a, b, podmacierz[i][j]) << " * v " << v << endl;
										cout << "podmacierz[" << i << "][" << j << "]= " << endl;
										for (int e = 0; e < a; e++) {
											for (int f = 0; f < b; f++) {
												cout << podmacierz[i][j][e][f] << "  ";
											}
											cout << endl;
										}
					*/
					MacierzD[i][j] = v * wyznacznik(a, b, podmacierz[i][j]);
					//					cout << "2MacierzD[" << i << "][" << j << "]= " << MacierzD[i][j] << " = wyznacznik (" << "p, " << a << "o, " << b << "podmacierz[i][j])" << wyznacznik(a, b, podmacierz[i][j]) << " * v " << v << endl;
				}
			}
			MacierzDopelnien = MacierzD;
		}
		else if ((n == m) && (n == 1) && (Wyznacznik_Macierzy() != 0)) { MacierzDopelnien[0][0] = tablica2D[0][0]; }

		else {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					MacierzDopelnien[i][j] = 0;
				}
			}

		}
		return MacierzDopelnien;
	}

	long double **Macierz_Transponowana() {
		long double **MacierzT = Transponowanie(n, m, tablica2D);
		return MacierzT;
	}

	long double **Macierz_Odwrotna() {
		long double **MacierzO;
		MacierzO = new long double *[n];
		for (int i = 0; i < n; i++)
			MacierzO[i] = new long double[m];
		if (n == m) {
			long double **MacierzDT = Transponowanie(n, m, Macierz_Dopelnien());
			long double x = 1 / wyznacznik(n, m, tablica2D);

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					MacierzO[i][j] = x * MacierzDT[i][j];
				}
			}
		}
		return MacierzO;
	}

};

const int *rozmiary(int nr_macierzy) {
		int n1, m1, n2, m2, rozmiar[2];
		for (int i = 0; i < 2; i++) { rozmiar[i] = 0; }
		if (nr_macierzy == 0) {
			cout << "Podaj rozmiar macierzy :" << endl;
			cout << "1. Liczba wierszy: ";
			cin >> n1;
			cout << "2. Liczba kolumn: ";
			cin >> m1;
			if ((n1 < 1) || (m1 < 1)) {
				cout << TEXTS[Blad_rozm];
			}
			rozmiar[0] = n1;
			rozmiar[1] = m1;
			return rozmiar;
		}
		else if (nr_macierzy == 1) {
			cout << "Podaj rozmiar pierwszej macierzy :" << endl;
			cout << "1. Liczba wierszy: ";
			cin >> n1;
			cout << "2. Liczba kolumn: ";
			cin >> m1;
			if ((n1 < 1) || (m1 < 1)) {
				cout << TEXTS[Blad_rozm];
			}
			rozmiar[0] = n1;
			rozmiar[1] = m1;
			return rozmiar;
		}
		else if (nr_macierzy == 2) {
			cout << endl;
			cout << "Podaj rozmiar drugiej macierzy :" << endl;
			cout << "1. Liczba wierszy: ";
			cin >> n2;
			cout << "2. Liczba kolumn: ";
			cin >> m2;
			if ((n2 < 1) || (m2 < 1)) {
				cout << TEXTS[Blad_rozm];
			}
			rozmiar[0] = n2;
			rozmiar[1] = m2;
			return rozmiar;
		}
		else cout << TEXTS[Error]; return rozmiar;
}

string date() {
	TIME;
	string date;
	string dzien = to_string(st.wDay);
	string d = to_string(st.wDay);
	if (st.wDay < 10) {
		dzien = "0" + d;
	}
	string miesiac = to_string(st.wMonth);
	string mie = to_string(st.wMonth);
	if (st.wMonth < 10) {
		miesiac = "0" + mie;
	}
	string rok = to_string(st.wYear);
	string r = to_string(st.wYear);
	if (st.wYear < 10) {
		rok = "0" + r;
	}
	date = dzien + "." + miesiac + "." + rok;
	return date;
}

string time() {
	TIME;
	string time;
	string godzina = to_string(st.wHour);
	string g = to_string(st.wHour);
	if (st.wHour < 10) {
		godzina = "0" + g;
	}
	string minuta = to_string(st.wMinute);
	string min = to_string(st.wMinute);
	if (st.wMinute < 10) {
		minuta = "0" + min;
	}
	string sekunda = to_string(st.wSecond);
	string s = to_string(st.wSecond);
	if (st.wSecond < 10) {
		sekunda = "0" + s;
	}
	time = godzina + ":" + minuta + ":" + sekunda;
	return time;
}

void reader(ZMIENNE) {
	string czyt_znak;
	if (znak == 1) { czyt_znak = "+"; }
	else if (znak == 2) { czyt_znak = "-"; }
	else if (znak == 3) { czyt_znak = "*"; }
	else if (znak == 4) { czyt_znak = ":"; }
	else { cout << "Blad odczytu znaku." << endl; }
	cout << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i < n1) {
				if (j < m1) cout << uzytkownika1[i][j] << " ";
				else cout << "  ";
			}
			else cout << "  ";
		}

		if (((n % 2 == 0) && (i == (n / 2) - 1)) || ((n % 2 == 1) && (i == (n - 1) / 2))) cout << "\t\t" << czyt_znak << "\t";
		else cout << "\t\t \t";

		for (int j = 0; j < m; j++) {
			if (i < n2) {
				if (j < m2) cout << uzytkownika2[i][j] << " ";
				else cout << "  ";
			}
			else cout << "  ";
		}

		if (((n % 2 == 0) && (i == (n / 2) - 1)) || ((n % 2 == 1) && (i == (n - 1) / 2))) cout << "\t\t=\t";
		else cout << "\t\t \t";

		for (int j = 0; j < m; j++) {
			if (i < n) {
				if (j < m) cout << wynik[i][j] << " ";
				else cout << "  ";
			}
			else cout << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

void saver(ZMIENNE) {
	string czyt_znak;
	if (znak == 1) { czyt_znak = "+"; }
	else if (znak == 2) { czyt_znak = "-"; }
	else if (znak == 3) { czyt_znak = "*"; }
	else if (znak == 4) { czyt_znak = ":"; }
	else { cout << "Blad odczytu znaku." << endl; }

	fstream plik;
	plik.open("Wyniki.txt", ios::out | ios::app);
	plik << date() << endl;
	plik << time() << endl;
	plik << endl;
	if (plik.good())
	{
		cout << "Zapisano" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (i < n1) {
					if (j < m1) {
						plik << uzytkownika1[i][j];
						plik << " ";
					}
					else { plik << " "; }
				}
				else { plik << "  "; }
			}

			if (((n % 2 == 0) && (i == (n / 2) - 1)) || ((n % 2 == 1) && (i == (n - 1) / 2))) {
				plik << "\t\t";
				plik << czyt_znak;
				plik << "\t";
			}
			else plik << "\t\t \t";

			for (int j = 0; j < m; j++) {
				if (i < n2) {
					if (j < m2) { plik << uzytkownika2[i][j]; plik << " "; }
					else plik << "  ";
				}
				else plik << "  ";
			}

			if (((n % 2 == 0) && (i == (n / 2) - 1)) || ((n % 2 == 1) && (i == (n - 1) / 2))) {
				plik << "\t\t=\t";
			}
			else plik << "\t\t \t";

			for (int j = 0; j < m; j++) {
				if (i < n) {
					if (j < m) {
						plik << wynik[i][j];
						plik << " ";
					}
					else plik << "  ";
				}
				else plik << "  ";
			}
			plik << endl;
		}
		plik << endl;
		plik.close();
	}
	else cout << "Nie uzyskano dostepu do pliku" << endl;
}

long double **dzialania(ZMIENNE, long double **macierz2, int wybor_zapis) {
	if (znak == 1) {
		m = m1 = m2;
		n = n1 = n2;
		wynik = new long double *[n];
		for (int i = 0; i < n; i++)
			wynik[i] = new long double[m];

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				wynik[i][j] = uzytkownika1[i][j] + uzytkownika2[i][j];
			}
		}
		cout << endl;
		reader(n, m, n1, n2, m1, m2, wynik, uzytkownika1, uzytkownika2, znak);
		if (wybor_zapis == 1) saver(n, m, n1, n2, m1, m2, wynik, uzytkownika1, uzytkownika2, znak);
		cout << endl;
	}
	else if (znak == 2) {
		m = m1 = m2;
		n = n1 = n2;
		wynik = new long double *[n];
		for (int i = 0; i < n; i++)
			wynik[i] = new long double[m];

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				wynik[i][j] = uzytkownika1[i][j] - uzytkownika2[i][j];
			}
		}
		cout << endl;
		reader(n, m, n1, n2, m1, m2, wynik, uzytkownika1, uzytkownika2, znak);
		if (wybor_zapis == 1) saver(n, m, n1, n2, m1, m2, wynik, uzytkownika1, uzytkownika2, znak);
		cout << endl;
	}
	else if (znak == 3) {
		n = n1;
		m = m2;
		wynik = new long double *[n];
		for (int i = 0; i < n; i++)
			wynik[i] = new long double[m];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				wynik[i][j] = 0;
			}
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				for (int k = 0; k < m1; k++)
					wynik[i][j] += uzytkownika1[i][k] * uzytkownika2[k][j];
			}
		}
		cout << endl;
		reader(n, m, n1, n2, m1, m2, wynik, uzytkownika1, uzytkownika2, znak);
		if (wybor_zapis == 1) saver(n, m, n1, n2, m1, m2, wynik, uzytkownika1, uzytkownika2, znak);
		cout << endl;
	}
	else if (znak == 4) {
		n = n1;
		m = m2;
		wynik = new long double *[n];
		for (int i = 0; i < n; i++)
			wynik[i] = new long double[m];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				wynik[i][j] = 0;
			}
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				for (int k = 0; k < m1; k++)
					wynik[i][j] += uzytkownika1[i][k] * macierz2[k][j];
			}
		}
		cout << endl;
		reader(n, m, n1, n2, m1, m2, wynik, uzytkownika1, uzytkownika2, znak);
		if (wybor_zapis == 1) saver(n, m, n1, n2, m1, m2, wynik, uzytkownika1, uzytkownika2, znak);
		cout << endl;
	}
	return wynik;
}

void Title() {
	system("cls");
	fstream file;
	file.open("Title.txt", ios::in);
	string line;
	while (getline(file, line))
	{
		cout << line << endl;
	}
	file.close();
	cout << endl;
}

void wyborwypisu1() {
	Title();
	fstream plik;
	plik.open("Wyniki.txt", ios::in);
	if (plik.good() == true) {
		string line;
		while (getline(plik, line))
		{
			cout << line << endl;
		}
		plik.close();
		cout << endl;
	}
	else cout << "Dostep do pliku zostal zabroniony!" << endl;
}

void wyborwypisu2(ZMIENNE) {
	Title();
	reader(n, m, n1, n2, m1, m2, wynik, uzytkownika1, uzytkownika2, znak);
}

void choice_wybory(int n1, int n2, int m1, int m2, Macierz & uzytkownika2) {
	cout << TEXTS[Wybor_dzialania];
	if ((m1 == m2) && (n1 == n2)) {
		cout << "1- dodawanie" << endl;
		cout << "2- odejmowanie" << endl;
		if (m1 == n2) {
			cout << "3- mnozenie" << endl;
			if (uzytkownika2.Wyznacznik_Macierzy() != 0) {
				cout << "4- dzielenie" << endl;
			}
		}
	}
	else if (m1 == n2) {
		cout << "3- mnozenie" << endl; 
		if ((n2 == m2) && (uzytkownika2.Wyznacznik_Macierzy() != 0)) {
			cout << "4- dzielenie" << endl;
		}
	}
	else cout << TEXTS[Brak_dzialan];
}

void powroty(int t) {
	int y;
	if (t == 1)cout << TEXTS[Blad_wyboru];
	else if (t == 2)cout << TEXTS[Zako_ustawien];
	cin >> y;
	Title();
}

void informacje (long double **Macierz, long double **MacierzT, long double **MacierzD, long double **MacierzO, int n, int m) {
	cout << "Podana macierz: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << Macierz[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "Transpozycja: " << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << MacierzT[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
	long double w = wyznacznik(n, m, Macierz);
	if (n == m) {
		cout << "Wyznacznik macierzy: " << w << "." << endl << endl;
		if (w != 0) {
			cout << "Macierz dopelnien algebraicznych: " << endl;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					cout << MacierzD[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl << "Macierz odwrotna: " << endl;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					cout << MacierzO[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl << endl;
		}
	}
	else cout << TEXTS[info];
}

void Mnozenie_przez_liczbe(long double **macierz, int n, int m) {
	Title();
	long double x;
	cout << TEXTS[Mnozenie];
	cin >> x;
	long double **wynikM = new long double *[n];
	for (int i = 0; i < n; i++)
		wynikM[i] = new long double[m];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			wynikM[i][j] = x * macierz[i][j];
		}
	}
	cout << "Wynik: \n" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << wynikM[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

int main() {
	int wybormenu = 0, wybor_wypis = 1, wybor_zapis = 1;
	Title();
menu:
	cout << TEXTS[Menu_glowne];
	cin >> wybormenu;
	int t = 0;
	Title();
	if (wybormenu == 1) {
	start:
		int numer_macierzy = 1, n1, m1, n2, n, m, m2, z = 0, nr_macierzy = 1, t = 0;
		const int *rozmiar1 = rozmiary(nr_macierzy);
		n1 = rozmiar1[0];
		m1 = rozmiar1[1];
		Macierz uzytkownika1(n1, m1);
		nr_macierzy = 2;
		const int *rozmiar2 = rozmiary(nr_macierzy);
		n2 = rozmiar2[0];
		m2 = rozmiar2[1];
		Macierz uzytkownika2(n2, m2);									
		int znak;
		int choice;
	choice:
		choice_wybory(n1, n2, m1, m2, uzytkownika2);
		while ((m1 != m2) && (m1 != n2)) { powroty(t);  goto start; }
		cin >> choice;
		long double **macierz2 = uzytkownika2.tablica2D;
		switch (choice)
		{
		case 1:																													//dodawanie
			if ((m1 == m2) && (n1 == n2)) { znak = 1; break; }
			else goto error;
		case 2:																													//odejmowanie
			if ((m1 == m2) && (n1 == n2)) { znak = 2; break; }
			else goto error;
		case 3:																													//mnozenie
			if (m1 == n2) { znak = 3; break; }
			else goto error;
		case 4:																													//dzielenie
			if ((m1 == n2) && (n2 == m2) && (uzytkownika2.Wyznacznik_Macierzy() != 0)) {
				macierz2 = uzytkownika2.Macierz_Odwrotna();
				znak = 4;
				break;
			}
			else goto error;
		default:
		error:
			cout << TEXTS[Blad_wyboru];
			goto choice;
		}
		n = n1;
		m = m2;
		long double **wynik = Wynik_tworzenie_macierzy(n1, m2);
		wynik = dzialania(n, m, n1, n2, m1, m2, wynik, uzytkownika1.tablica2D, uzytkownika2.tablica2D, znak, macierz2, wybor_zapis);
		int finalwyb = 0, again = 0;
		do {
			cout << TEXTS[Menu_koncowe];
			cin >> finalwyb;
			if (finalwyb == 1) {
				again = 0;
				if (wybor_wypis == 2) {
					wyborwypisu2(n, m, n1, n2, m1, m2, wynik, uzytkownika1.tablica2D, uzytkownika2.tablica2D, znak);
					uzytkownika1.~Macierz();
					uzytkownika2.~Macierz();
					for (int i = 0; i < n2; i++) {
						delete[] macierz2[i];
					}
					delete[] macierz2;
					for (int i = 0; i < n; i++) {
						delete[] wynik[i];
					}
					delete[] wynik;
					goto start;
				}
				else if (wybor_wypis == 1) {
					wyborwypisu1();																										//odczyt z pliku
					uzytkownika1.~Macierz();
					uzytkownika2.~Macierz();
					for (int i = 0; i < n2; i++) {
						delete[] macierz2[i];
					}
					delete[] macierz2;
					for (int i = 0; i < n; i++) {
						delete[] wynik[i];
					}
					delete[] wynik;
					goto start;
				}
				else {
					cout << TEXTS[Error];
					again = 1;
				}
			}
			else if (finalwyb == 2) {
				Title();
				uzytkownika1.~Macierz();
				uzytkownika2.~Macierz();
				for (int i = 0; i < n2; i++) {
					delete[] macierz2[i];
				}
				delete[] macierz2;
				for (int i = 0; i < n; i++) {
					delete[] wynik[i];
				}
				delete[] wynik;
				goto menu;
			}
			else if (finalwyb == 3) {
				uzytkownika1.~Macierz();
				uzytkownika2.~Macierz();
				for (int i = 0; i < n2; i++) {
					delete[] macierz2[i];
				}
				delete[] macierz2;
				for (int i = 0; i < n; i++) {
					delete[] wynik[i];
				}
				delete[] wynik;
				goto final;
			}
			else {
				cout << TEXTS[Error];
				again = 1;
			}
		} while (again == 1);
	}
	else if (wybormenu == 2) {
		int menuinf, again = 0, error_wyboru = 0;
		do {
			int n = 0, m = 0;
			const int *rozmiar = rozmiary(0);
			n = rozmiar[0];
			m = rozmiar[1];
			Macierz uzytkownika(n, m);
			long double **MacierzT = uzytkownika.Macierz_Transponowana();
			long double **MacierzD = uzytkownika.Macierz_Dopelnien();
			long double **MacierzO = uzytkownika.Macierz_Odwrotna();
			informacje(uzytkownika.tablica2D, MacierzT, MacierzD, MacierzO, n, m);
			do {
				again = 0;
				if ((error_wyboru == 0) || (error_wyboru == 1)) cout << TEXTS[menu_info];
				else if (error_wyboru == 2) cout << TEXTS[menu_info2];
				else { cout << TEXTS[Error]; again = 1;  continue; }
				cin >> menuinf;
				error_wyboru = 0;
				switch (menuinf) {
				case 1:
					Mnozenie_przez_liczbe(uzytkownika.tablica2D, n, m);
					error_wyboru = 2;
					break;
				case 2:
					Title();
					uzytkownika.~Macierz();
					for (int i = 0; i < m; i++) { delete[] MacierzT[i]; }
					delete[] MacierzT;
					for (int i = 0; i < n; i++) { delete[] MacierzD[i]; }
					delete[] MacierzD;
					for (int i = 0; i < n; i++) { delete[] MacierzO[i]; }
					delete[] MacierzO;
					goto start;
					break;
				case 3:
					uzytkownika.~Macierz();
					Title();
					for (int i = 0; i < m; i++) { delete[] MacierzT[i]; }
					delete[] MacierzT;
					for (int i = 0; i < n; i++) { delete[] MacierzD[i]; }
					delete[] MacierzD;
					for (int i = 0; i < n; i++) { delete[] MacierzO[i]; }
					delete[] MacierzO;
					again = 1;
					break;
				case 4:
					Title();
					for (int i = 0; i < m; i++) { delete[] MacierzT[i]; }
					delete[] MacierzT;
					for (int i = 0; i < n; i++) { delete[] MacierzD[i]; }
					delete[] MacierzD;
					for (int i = 0; i < n; i++) { delete[] MacierzO[i]; }
					delete[] MacierzO;
					uzytkownika.~Macierz();
					goto menu;
					break;
				case 5:
					uzytkownika.~Macierz();
					for (int i = 0; i < m; i++) { delete[] MacierzT[i];}
					delete[] MacierzT;
					for (int i = 0; i < n; i++) { delete[] MacierzD[i]; }
					delete[] MacierzD;
					for (int i = 0; i < n; i++) { delete[] MacierzO[i]; }
					delete[] MacierzO;
					goto final;
					break;
				default:
					cout << TEXTS[Blad_wyboru];
					error_wyboru = 1;
					break;
				}
			} while ((error_wyboru == 2) || (error_wyboru == 1));
		} while (again == 1);
	}
	else if (wybormenu == 3) {
	menu_ustawien:
		Title();
		cout << TEXTS[Menu_ustawien];
		int wybor_ustawienia;
		cin >> wybor_ustawienia;
		if (wybor_ustawienia == 1) {
			Title();
			cout << TEXTS[Ustawienia_okna];
		}
		else if (wybor_ustawienia == 2) {
		menu_ustawien_case2:
			Title();
			cout << TEXTS[Ustawienia_wypisywania];
			cin >> wybor_wypis;
			if ((wybor_wypis != 1) && (wybor_wypis != 2)) {
				t = 1;
				powroty(t);
				goto menu_ustawien_case2;
			}
		}
		else if (wybor_ustawienia == 3) {
		menu_ustawien_case3:
			Title();
			cout << TEXTS[Ustawienia_zapisu];
			cin >> wybor_zapis;
			if ((wybor_zapis != 1) && (wybor_zapis != 2)) {
				t = 1;
				powroty(t);
				goto menu_ustawien_case3;
			}
		}
		else if (wybor_ustawienia == 4) {
			Title();
			goto menu;
		}
		else {
			t = 1;
			powroty(t);
			goto menu_ustawien;
		}
		t = 2;
		powroty(t);
		goto menu_ustawien;

	}
	else if (wybormenu == 4) {
		final:
		return 0;
	}
	else {
		t = 1;
		powroty(t);
		goto menu;
	}
}
