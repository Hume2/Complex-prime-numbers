#include <math.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

struct Komplex {
  public:
    Komplex() :
      re(),
      im()
    { }

    Komplex(int r, int i) :
      re(r),
      im(i)
    { }

    int re,im;

    int abs() {
      return sqrt(re*re + im*im);
    }

    void vydel_i() {
      int t = re;
      re = im;
      im = -t;
    }

    void vytiskni() {
      cout << re << "+" << im << "i" << " ";
    }
};

struct Vysledek {
  public:
    Vysledek() :
      def(),
      pr()
    { }

    Vysledek(bool def_, bool pr_) :
      def(def_),
      pr(pr_)
    { }

    bool def, pr;
};

Komplex operator* (Komplex x, Komplex y) {
  return Komplex(x.re * y.re - x.im * y.im, x.re * y.im + x.im * y.re);
}

const int w = 201, h = 201, max_abs = 200;
Vysledek cisla[w*h];
FILE* f;

Vysledek& dej(Komplex z) {
  while (z.re < 0 || z.im < 0) {
    z.vydel_i();
  }
  return cisla[z.re + w*z.im];
}

void ukaz_pole() {
  cout << endl;
  for (int y = h-1; y >= 0; y--) {
    int t = ((y%1000)/10);
    if (t < 10) {
      fprintf(f, "0%d  ", t);
      //cout << '0' << t << "  ";
    } else {
      fprintf(f, "%d  ", t);
      //cout << t << "  ";
    }
    for (int x = 0; x < w; x++) {
      if (Komplex(x, y).abs() >= max_abs) continue;
      if (dej(Komplex(x, y)).pr) {
        fprintf(f, ":.");
        //cout << ":.";
      } else {
        fprintf(f, "%d%d", x%10, y%10);
        //cout << x%10 << y%10;
      }
    }
    fprintf(f, "\n");
  }
  fprintf(f, "\n00  ");
  for (int x = 0; x < w; x++) {
    int t = ((x%1000)/10);
    if (t < 10) {
      fprintf(f, "0%d", t);
      //cout << '0' << t;
    } else {
      fprintf(f, "%d", t);
      //cout << t;
    }
  }
}

void obsad(Komplex a, Komplex b) {
  Komplex c = a * b;
  if (dej(b).def && c.im < max_abs && c.re < max_abs && c.abs() < max_abs) {
    dej(c).def = true;
  }
}

void bublej(Komplex z, int max_d) {
  if (z.re || z.im) {
    max_d = min(max_d, max_abs / z.abs());
  }
  int x, y, d;
  for (d = 0; d <= max_d; d++) {
    x = d;
    for (y = 0; y <= d; y++) {
      obsad(z, Komplex(x, y));
    }
    y = d;
    for (x = y-1; x >= 0; x--) {
      obsad(z, Komplex(x, y));
    }
  }
}

void zkus_cislo(Komplex z, int d) {
  if (z.abs() >= max_abs) return;
  Vysledek& v = dej(z);
  if (!v.def) {
    v.def = true;
    v.pr = true;
    z.vytiskni();
  }
  bublej(z, d);
}

int main(int argc, char** arg) {
  f = fopen("out.txt", "w");
  for (int i = w*h-1; i >= 0; i--) {
    cisla[i] = Vysledek(false, false);
  }
  int x, y, d;
  for (d = 0; d < w; d++) {
    x = d;
    for (y = 0; y <= d; y++) {
      zkus_cislo(Komplex(x, y), d);
    }
    y = d;
    for (x = y-1; x >= 0; x--) {
      zkus_cislo(Komplex(x, y), d);
    }
  }
  ukaz_pole();

  fclose(f);
  return 0;
}
