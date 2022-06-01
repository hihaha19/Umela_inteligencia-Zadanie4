#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <time.h>


#define SUCCESS				0
#define GENERAL_ERROR		3
#define USED_COORDINATES	2

typedef struct Bod {
	int x;
	int y;
	char farba[8];
	char farba_urcena_klasifikatorom[8];
	int j;
}BOD;

typedef struct Usporiadanie {
	float vzdialenost;
	int x;
	int y;
	char farba[8];
}USPORIADANIE;

typedef struct Pocetnost_farieb {
	char farba[8];
	int pocet_vyskytov;
}POCETNOST_FARIEB;

typedef struct Farby_s_rovnakym_poctom_vyskytov {
	char farba[8];
}FARBY_S_ROVNAKYM_POCTOM_VYSKYTOV;

typedef struct Mapa {
	int x;
	int y;
}MAPA;

BOD* body;
int pravd = 0;
int pocet_bodov = 0;


void display() {
	int i = 0, pocet_nezhodujucich_farieb = 0;

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();


	glBegin(GL_POINTS);
	glPointSize(10);


	for (i = 0; i < 20020; i++) {
		if (strcmp(body[i].farba, body[i].farba_urcena_klasifikatorom) != 0)
			pocet_nezhodujucich_farieb++;


		if (strcmp(body[i].farba_urcena_klasifikatorom, "cervena") == 0) 
			glColor3f(1.0, 0.0, 0.0);	
		else if (strcmp(body[i].farba_urcena_klasifikatorom, "modra") == 0)
			glColor3f(0.0, 0.0, 1.0);
		else if (strcmp(body[i].farba_urcena_klasifikatorom, "zelena") == 0)
			glColor3f(0.0, 1.0, 0.0);
		else if (strcmp(body[i].farba_urcena_klasifikatorom, "fialova") == 0)
			glColor3f(0.7, 0, 1);

		glVertex2f(body[i].x, body[i].y);
	}

	glEnd();
	glFlush();
	printf("Pocet nezhodujich farieb %d\n", pocet_nezhodujucich_farieb);
}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5000, 5000, -5000, 5000);
	glMatrixMode(GL_MODELVIEW);
}

int prirad_farbu(int x, int y, int k, char farba[]) {
	int i = 0, j = 0, max_index = 0, max_pocet_vyskytu = 0, rovnaky_pocet = 0, pocet_rovnakeho_poctu_farieb = 0, zmena_indexu = 0;
	char farba_vybrana_klasifikatorom[8] = { 0 }, najblizsia_farba[8] = { 0 };
	float vzdialenost = 0;
	USPORIADANIE* usporiadane_vzdialenosti = (USPORIADANIE*)malloc(pocet_bodov * sizeof(USPORIADANIE));


	for (i = 0; i < pocet_bodov; i++) {
		vypocitaj_vzdialenost_pre_mapu(x, y, i, &vzdialenost);
		memcpy(usporiadane_vzdialenosti[i].farba, body[i].farba_urcena_klasifikatorom, sizeof(body[i].farba));
		usporiadane_vzdialenosti[i].x = body[i].x;
		usporiadane_vzdialenosti[i].y = body[i].y;
		usporiadane_vzdialenosti[i].vzdialenost = vzdialenost;
	}

	selectionSort(usporiadane_vzdialenosti, pocet_bodov);
	
	strcpy(farba, usporiadane_vzdialenosti[0].farba);

	free(usporiadane_vzdialenosti);
	return 0;
}


int generuj_prve_body() {
	int i;

	for (i = 0; i < 5; i++) {
		strcpy(body[i].farba, "cervena");
		strcpy(body[i].farba_urcena_klasifikatorom, "cervena");
	}
		

	body[0].x = -4100; body[0].y = -4400;
	body[1].x = -4100; body[1].y = -3000;
	body[2].x = -1800; body[2].y = -2400;
	body[3].x = -2500; body[3].y = -3400;
	body[4].x = -2000; body[4].y = -1400;

	for (i = 5; i < 10; i++) {
		strcpy(body[i].farba, "zelena");
		strcpy(body[i].farba_urcena_klasifikatorom, "zelena");
	}
		
	body[5].x = 4500; body[5].y = -4400;
	body[6].x = 4100; body[6].y = -3000;
	body[7].x = 1800; body[7].y = -2400;
	body[8].x = 2500; body[8].y = -3400;
	body[9].x = 2000; body[9].y = -1400;


	for (i = 10; i < 15; i++) {
		strcpy(body[i].farba, "modra");
		strcpy(body[i].farba_urcena_klasifikatorom, "modra");
	}
		

	body[10].x = -4500; body[10].y = 4400;
	body[11].x = -4100; body[11].y = 3000;
	body[12].x = -1800; body[12].y = 2400;
	body[13].x = -2500; body[13].y = 3400;
	body[14].x = -2000; body[14].y = 1400;

	
	for (i = 15; i < 20; i++) {
		strcpy(body[i].farba_urcena_klasifikatorom, "fialova");
		strcpy(body[i].farba, "fialova");
	}
		

	body[15].x = 4500; body[15].y = 4400;
	body[16].x = 4100; body[16].y = 3000;
	body[17].x = 1800; body[17].y = 2400;
	body[18].x = 2500; body[18].y = 3400;
	body[19].x = 2000; body[19].y = 1400;
}

int kontrola_unikatnosti(int x, int y, BOD *body, int pocet_bodov) {
	int rv = GENERAL_ERROR, i = 0;

	for (i = 0; i < pocet_bodov; i++) {
		if (body[i].x == x) 
			if (body[i].y == y) {
				rv = USED_COORDINATES;
				goto err;
			}
	}
	
	rv = SUCCESS;

err:
	return rv;
}

int generuj_nahodne_cislo(int *suradnica_x, int *suradnica_y, char farba[], int pocet_bodov, BOD *body) {

	int pravdepodobnost = rand() % 100, x = 0, y = 0, pouzite_suradnice = 1;

	// ak je pravdepodobnost 0, bod sa generuje hocikde okrem svojej vyznacenej oblasti
	if (0 == pravdepodobnost) {
		printf("%d\n", pravd);
		pravd++;
		while (0 != pouzite_suradnice) {
			if (strcmp(farba, "cervena") == 0) {

				x = (rand() % (5000 - 500 + 1)) + 500;
				y = (rand() % (5000 - 500 + 1)) + 500;
			}

			else if (strcmp(farba, "modra") == 0) {

				x = (rand() % (5000 - 500 + 1)) + 500;
				y = (rand() % (-500 + 5000 + 1)) - 5000;
			}

			else if (strcmp(farba, "zelena") == 0) {

				x = (rand() % (-500 - (-5000) + 1)) - 500;
				y = (rand() % (5000 - 500 + 1)) + 500;
			}

			else if (strcmp(farba, "fialova") == 0) {

				x = (rand() % (-500 + 5000 + 1)) - 5000;
				y = (rand() % (5000 + 500 + 1)) + 500;
			}

			pouzite_suradnice = kontrola_unikatnosti(x, y, body, pocet_bodov);
		}
	}
	
	// 99% uspesnost
	 else {
		while (0 != pouzite_suradnice) {
			if (strcmp(farba, "cervena") == 0) {
				x = (rand() % (499 + 5000 + 1)) - 5000;
				y = (rand() % (499 + 5000 + 1)) - 5000;
			}

			else if (strcmp(farba, "zelena") == 0) {
				x = (rand() % (5000 + 499 + 1)) - 499;
				y = (rand() % (499 + 5000 + 1)) - 5000;
			}

			else if (strcmp(farba, "modra") == 0) {
				x = (rand() % (499 + 5000 + 1)) - 5000;
				y = (rand() % (5000 + 499 + 1)) - 499;
			}

			else if (strcmp(farba, "fialova") == 0) {
				x = (rand() % (5000 + 499 + 1)) - 499;
				y = (rand() % (5000 + 499 + 1)) - 499;
			}
			//kontrola unikatnosti
			pouzite_suradnice = kontrola_unikatnosti(x, y, body, pocet_bodov);
		}
	
			
	}	
	*suradnica_x = x;
	*suradnica_y = y;

	return 0;	
}

int generuj_bod(BOD *bod, int poradie) {

	int x, y, rv = GENERAL_ERROR, unikatny = 0;
	char farba[8] = { 0 };
	if (strcmp(bod[poradie].farba, "cervena") == 0)
		strcpy(farba, "cervena");

	else if (strcmp(bod[poradie].farba, "modra") == 0)
		strcpy(farba, "modra");

	else if (strcmp(bod[poradie].farba, "zelena") == 0)
		strcpy(farba, "zelena");

	else if (strcmp(bod[poradie].farba, "fialova") == 0)
		strcpy(farba, "fialova");

	else 
		goto err;

	generuj_nahodne_cislo(&x, &y, farba, poradie, bod);
	bod[poradie].x = x;
	bod[poradie].y = y;

	rv = SUCCESS;

err:
	return rv;

}

int vypocitaj_vzdialenost(int pocet_bodov, int i, float *vysledok) {
	int rozdiel_x = 0, rozdiel_y = 0;
	long int na_druhu = 0;

	rozdiel_x = abs(body[pocet_bodov].x - body[i].x);
	rozdiel_y = abs(body[pocet_bodov].y - body[i].y);

	na_druhu = pow(rozdiel_x, 2) + pow(rozdiel_y, 2);
	*vysledok = sqrt(na_druhu);

	return 0;
}

int vypocitaj_vzdialenost_pre_mapu(int x, int y, int i, float* vysledok) {
	int rozdiel_x = 0, rozdiel_y = 0;
	long int na_druhu = 0;

	rozdiel_x = abs(x - body[i].x);
	rozdiel_y = abs(y - body[i].y);

	na_druhu = pow(rozdiel_x, 2) + pow(rozdiel_y, 2);
	*vysledok = sqrt(na_druhu);

	return 0;
}

// nasledujuce 2 funkcie prebrate a upravene z: https://www.geeksforgeeks.org/selection-sort/
int swap(float* xp, float* yp, char farba1[], char farba2[], int *x1, int *x2, int *y1, int *y2) {
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
	char temp2[8];

	strcpy(temp2, farba1);
	strcpy(farba1, farba2);
	strcpy(farba2, temp2);

	temp = *x1;
	*x1 = *x2;
	*x2 = temp;

	temp = *y1;
	*y1 = *y2;
	*y2 = temp;

	return 0;
}

int selectionSort(USPORIADANIE *pole, int n) {
	int i, j, min_idx;

	for (i = 0; i < n; i++) {

		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (pole[j].vzdialenost < pole[min_idx].vzdialenost)
				min_idx = j;


		swap(&pole[min_idx].vzdialenost, &pole[i].vzdialenost, &pole[min_idx].farba, &pole[i].farba, &pole[min_idx].x, &pole[i].x, &pole[min_idx].y, &pole[i].y);
	}

	return 0;
}


int classify(int x, int y, int k) {
	int i = 0, j = 0, max_index = 0, max_pocet_vyskytu = 0, rovnaky_pocet = 0, pocet_rovnakeho_poctu_farieb = 0, zmena_indexu = 0;
	char farba_vybrana_klasifikatorom[8] = { 0 }, najblizsia_farba[8] = { 0 };
	float vzdialenost = 0;
	USPORIADANIE *usporiadane_vzdialenosti = (USPORIADANIE*) malloc (pocet_bodov * sizeof(USPORIADANIE));
	POCETNOST_FARIEB* pocetnost = (POCETNOST_FARIEB*)calloc(4, sizeof(POCETNOST_FARIEB));
	FARBY_S_ROVNAKYM_POCTOM_VYSKYTOV* farby_s_rovnakym_vyskytom = (FARBY_S_ROVNAKYM_POCTOM_VYSKYTOV*)calloc(4, sizeof(FARBY_S_ROVNAKYM_POCTOM_VYSKYTOV));

	strcpy(pocetnost[0].farba, "cervena");
	strcpy(pocetnost[1].farba, "zelena");
	strcpy(pocetnost[2].farba, "modra");
	strcpy(pocetnost[3].farba, "fialova");

	for (i = 0; i < pocet_bodov; i++) {
		vypocitaj_vzdialenost(pocet_bodov, i, &vzdialenost);
		memcpy(usporiadane_vzdialenosti[i].farba, body[i].farba_urcena_klasifikatorom, sizeof(body[i].farba));
		usporiadane_vzdialenosti[i].x = body[i].x;
		usporiadane_vzdialenosti[i].y = body[i].y;
		usporiadane_vzdialenosti[i].vzdialenost = vzdialenost;
	}

	selectionSort(usporiadane_vzdialenosti, pocet_bodov);


	if (k == 1) {
		strcpy(farba_vybrana_klasifikatorom, usporiadane_vzdialenosti[0].farba);
		strcpy(body[pocet_bodov].farba_urcena_klasifikatorom, usporiadane_vzdialenosti[0].farba);
	}
	

	// vypocitanie prvych vyskytov z usporiadaneho pola
	else {
		for (j = 0; j < k; j++) {
			if (strcmp(usporiadane_vzdialenosti[j].farba, "cervena") == 0)
				pocetnost[0].pocet_vyskytov++;
			else if (strcmp(usporiadane_vzdialenosti[j].farba, "zelena") == 0)
				pocetnost[1].pocet_vyskytov++;
			else if (strcmp(usporiadane_vzdialenosti[j].farba, "modra") == 0)
				pocetnost[2].pocet_vyskytov++;
			else if (strcmp(usporiadane_vzdialenosti[j].farba, "fialova") == 0)
				pocetnost[3].pocet_vyskytov++;
		}


		max_pocet_vyskytu = pocetnost[0].pocet_vyskytov;
		max_index = 0;


		for (i = 1; i < 4; i++) {
			if (pocetnost[i].pocet_vyskytov >= max_pocet_vyskytu) {
				if (pocetnost[i].pocet_vyskytov > max_pocet_vyskytu)
					zmena_indexu = 0;
				else 
					zmena_indexu = 1;
				max_pocet_vyskytu = pocetnost[i].pocet_vyskytov;
				max_index = i;
				rovnaky_pocet = 0;	
			}

			if (pocetnost[i].pocet_vyskytov == max_pocet_vyskytu && zmena_indexu == 1) {
				rovnaky_pocet = 1;
			}
		}

		if (rovnaky_pocet == 0) {

			if (max_index == 0)
				strcpy(body[pocet_bodov].farba_urcena_klasifikatorom, "cervena");

			else if (max_index == 1)
				strcpy(body[pocet_bodov].farba_urcena_klasifikatorom, "zelena");

			else if (max_index == 2)
				strcpy(body[pocet_bodov].farba_urcena_klasifikatorom, "modra");

			else if (max_index == 3)
				strcpy(body[pocet_bodov].farba_urcena_klasifikatorom, "fialova");
		}

		//ak je viac ako jeden vyskyt s rovnakym poctom 
		else if (rovnaky_pocet == 1) {
			i = 0; j = 0;
			while (i < 4) {
				if (max_pocet_vyskytu == pocetnost[i].pocet_vyskytov) {
					strcpy(farby_s_rovnakym_vyskytom[j].farba, pocetnost[i].farba);
					pocet_rovnakeho_poctu_farieb++;
					j++;
				}

				i++;
			}

			if (pocet_rovnakeho_poctu_farieb == 4) {
				strcpy(body[pocet_bodov].farba_urcena_klasifikatorom, usporiadane_vzdialenosti[0].farba);
			}
			// hladam pri vyskyt niektorej z 3 farieb, tieto 3 farby su ulozene v farba_s_rovnakym_poctom_vyskytov
			else if (pocet_rovnakeho_poctu_farieb == 3) {
				int o = 0;
				while (o < pocet_bodov) {	//lebo hladam najblizsi bod
					if (strcmp(farby_s_rovnakym_vyskytom[0].farba, usporiadane_vzdialenosti[o].farba) == 0) {
						strcpy(farba_vybrana_klasifikatorom, usporiadane_vzdialenosti[o].farba);
						strcpy(body[pocet_bodov].farba_urcena_klasifikatorom, farby_s_rovnakym_vyskytom[0].farba);
						break;
					}

					else if (strcmp(farby_s_rovnakym_vyskytom[1].farba, usporiadane_vzdialenosti[o].farba) == 0) {
						strcpy(farba_vybrana_klasifikatorom, usporiadane_vzdialenosti[o].farba);
						strcpy(body[pocet_bodov].farba_urcena_klasifikatorom, farby_s_rovnakym_vyskytom[1].farba);
						break;
					}

					else if (strcmp(farby_s_rovnakym_vyskytom[2].farba, usporiadane_vzdialenosti[o].farba) == 0) {
						strcpy(farba_vybrana_klasifikatorom, usporiadane_vzdialenosti[o].farba);
						strcpy(body[pocet_bodov].farba_urcena_klasifikatorom, farby_s_rovnakym_vyskytom[2].farba);
						break;
					}
				}
				o++;
			}

			else if (pocet_rovnakeho_poctu_farieb == 2) {
				int o = 0;
				while (o < pocet_bodov) {
					if (strcmp(farby_s_rovnakym_vyskytom[0].farba, usporiadane_vzdialenosti[o].farba) == 0) {
						strcpy(farba_vybrana_klasifikatorom, usporiadane_vzdialenosti[o].farba);
						strcpy(body[pocet_bodov].farba_urcena_klasifikatorom, farby_s_rovnakym_vyskytom[0].farba);
						break;
					}

					else if (strcmp(farby_s_rovnakym_vyskytom[1].farba, usporiadane_vzdialenosti[o].farba) == 0) {
						strcpy(farba_vybrana_klasifikatorom, usporiadane_vzdialenosti[o].farba);
						strcpy(body[pocet_bodov].farba_urcena_klasifikatorom, farby_s_rovnakym_vyskytom[1].farba);
						break;
					}
					o++;
				}

			}
		}
	}


	free(usporiadane_vzdialenosti);
	free(farby_s_rovnakym_vyskytom);
	return 0;
}

int main(int argc, char** argv) {
	int k = 0;
	clock_t start_cas, end;
	double time_spent = 0;
	body = (BOD*)calloc(20020, sizeof(BOD));

	printf("Ktore 'k' chcem pouzit?\n");
	scanf("%d", &k);

	start_cas = clock();
	generuj_prve_body();


	for (pocet_bodov = 20; pocet_bodov < 20020; pocet_bodov++) {
		if(pocet_bodov % 4 == 0)
			strcpy(body[pocet_bodov].farba, "cervena");
		else if (pocet_bodov % 4 == 1)
			strcpy(body[pocet_bodov].farba, "zelena");
		else if (pocet_bodov % 4 == 2)
			strcpy(body[pocet_bodov].farba, "modra");
		else if (pocet_bodov % 4 == 3)
			strcpy(body[pocet_bodov].farba, "fialova");

		generuj_bod(body, pocet_bodov);
		classify(body[pocet_bodov].x, body[pocet_bodov].y, k);

	} 

	//943 pre 10 000
	end = clock();
	time_spent = (double)(end - start_cas) / CLOCKS_PER_SEC;
	printf("Cas %f\n", time_spent);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Points");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	myinit();
	
	
	glutMainLoop();

	return 0;
}