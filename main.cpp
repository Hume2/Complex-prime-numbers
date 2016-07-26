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
vector<Vysledek> cisla = vector<Vysledek>(w*h, Vysledek(false, false));

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
      cout << '0' << t << "  ";
    } else {
      cout << t << "  ";
    }
    for (int x = 0; x < w; x++) {
      if (Komplex(x, y).abs() >= max_abs) continue;
      if (dej(Komplex(x, y)).pr) {
        cout << ":.";
      } else {
        cout << x%10 << y%10;
      }
    }
    cout << endl;
  }
  cout << endl << "00  ";
  for (int x = 0; x < w; x++) {
    int t = ((x%1000)/10);
    if (t < 10) {
      cout << '0' << t;
    } else {
      cout << t;
    }
  }
}

void obsad(Komplex a, Komplex b) {
  Komplex c = a * b;
  if (dej(b).def && c.abs() < max_abs) {
    dej(c).def = true;
  }
}

void bublej(Komplex z) {
  int x, y, d;
  for (d = 0; d < w; d++) {
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
    bublej(z);
  }
}

int main(int argc, char** arg) {
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

  return 0;
}
