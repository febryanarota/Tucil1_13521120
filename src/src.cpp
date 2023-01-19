#include <iostream>
#include <algorithm>
#include <array>
#include <cstdlib>
#include <fstream>
#include <ctime>
using namespace std;

float calc(int ops, float a, float b) { //calculate
  /*operator list:
  0 = sum, 1 = sub, 2 = mul, else = div*/
  if (ops == 0) {
    return a + b;
  } else if (ops == 1) {
    return a - b;
  } else if (ops == 2) {
    return a * b; 
  } else {
    return a / b ;
  }
}

int main() {
  cout << "--24 PUZZLE SOLVER--" << endl;
  cout << "1. Manual Input" << endl;
  cout << "2. Randomize" << endl;
  int input;

  do {
    cout << "Pilih menu: ";
    cin >> input;
  } while (!(input == 1 || input == 2));

  int values[4];
  int value, n;
  int count = 0;
  char card[4]; 
  
  if (input == 1) { //input manual
    cout << "\nMasukkan 4 kartu (2-10, J, Q, K)!" << endl ;
    for (int i=0; i< 4; i++) {
      cout << "kartu ke-" << i+1 << ": ";
      cin >> card; 
      value = atoi(card); //convert string to integer
      
      if (card[0] == 'A' && card[1] == '\0') {
        values[i] = 1;
      } else if (card[0] == 'J' && card[1] == '\0') {
        values[i] = 11;
      } else if (card[0] == 'Q' && card[1] == '\0') {
        values[i] = 12;
      } else if (card[0] == 'K' && card[1] == '\0') {
        values[i] = 13;
      } else if (value >= 2 && value <= 9 && card[1] == '\0') {
        values[i] = value;
      } else if (value == 10 && card[2] == '\0') {
        values[i] = value;
      } else {
        cout << "Masukan salah. Ulangi. \n\n";
        i-=1;
      }
    }
  } else if (input == 2) { //input random
    srand(time(0)); //random seed
    cout << "\nKartu: \n";
    for (int i = 0; i < 4; i++) {
      values[i] = 1 + rand() % 13;
      if (values[i] == 1) {
        cout << "A ";
      } else if (values[i] == 11) {
        cout << "J ";
      } else if (values[i] == 12) {
        cout << "Q ";
      } else if (values[i] == 13) {
        cout << "K ";
      } else {
        cout << values[i] << " ";
      }
    }
  }
  
  clock_t time_req; //start execution timer
  time_req = clock();

  //sorting array values untuk proses permutasi
  n = sizeof(values) / sizeof(values[0]);
  std::sort(values, values+n);
  /*kemungkinan
    a # b # c # d
    a # c # b # d
    a # d # b # c
    dst
  */

  char ops[4] = {'+', '-', '*', '/'};
  cout << "\n\nSolusi: \n";
  do {
    int a = values[0]; int b = values[1]; int c = values[2]; int d = values[3];
    for (int i = 0; i<4; i++) {
      for (int j = 0; j<4; j++) {
        for (int k = 0; k<4; k++) {

          // ((a #i b) #j c) #k d
          if (calc(k, calc(j, calc(i, a, b), c), d) == 24) {
            count += 1;
            cout << count << ". ((" << a << ops[i] << b << ")" << ops[j] << c << ")" << ops[k] << d << endl;
          }

          // (a #i (b #j c)) #k d
          if (calc(k, calc(i, a, calc(j, b, c)), d) == 24) {
            count += 1;
            cout << count << ". (" << a << ops[i] << "(" << b << ops[j] << c << "))" << ops[k] << d << endl;
          }
          
          // (a #i b) #j (c #k d)
          if (calc(j, calc(i, a, b), calc(k, c, d)) == 24) {
            count += 1;
            cout << count << ". (" << a << ops[i] << b << ")" << ops[j] << "(" << c << ops[k] << d << ")" << endl;
          }

          // a #i ((b #j c) #k d)
          if (calc(i, a, calc(k, calc(j ,b, c),d)) == 24) {
            count += 1;
            cout << count << ". " << a << ops [i] << "((" << b << ops[j] << c << ")" << ops[k] << d << ")" << endl;
          }

          // a #i (b #j (c #k d))
          if (calc(i, a, calc(j, b, calc(k,c,d))) == 24) {
            count += 1;
            cout << count << ". "<< a << ops[i] << "(" << b << ops[j] << "(" << c << ops[k] << d << "))" << endl;
          }
        }
      }
    }
  } while (next_permutation(values, values+4)); //permutasi

  if (count == 0) {
    cout << "Tidak ada solusi.";
  } else {
    cout << "\nTotal solusi: " << count << endl;
  }
  time_req = clock() - time_req;
  cout << "Waktu eksekusi: " <<(float)time_req/CLOCKS_PER_SEC << " detik" << endl;

  char save;
  do {
    cout << "\nSimpan solusi? (y/n) " ;
    cin >> save;
  } while (!(save == 'y' || save == 'n'));

  if (save == 'y') {
    string filename;
    cout << "Masukkan nama file: ";
    cin >> filename;
    filename = filename + ".txt";
    ofstream file(filename);

    file << "Kartu:\n";
    for (int i = 0; i < 4; i++){
      if (values[i] == 1) {
        file << "A ";
      } else if (values[i] == 11) {
        file << "J ";
      } else if (values[i] == 12) {
        file << "Q ";
      } else if (values[i] == 13) {
        file << "K ";
      } else {
        file << values[i] << " ";
      }
    }

    file << "\n\nSolusi: \n";
    count = 0;
    do {
      int a = values[0]; int b = values[1]; int c = values[2]; int d = values[3];
      for (int i = 0; i<4; i++) {
        for (int j = 0; j<4; j++) {
          for (int k = 0; k<4; k++) {
            if (calc(k, calc(j, calc(i, a, b), c), d) == 24) {
              count += 1;
              file << count << ". ((" << a << ops[i] << b << ")" << ops[j] << c << ")" << ops[k] << d << endl;
            } if (calc(k, calc(i, a, calc(j, b, c)), d) == 24) {
              count += 1;
              file << count << ". (" << a << ops[i] << "(" << b << ops[j] << c << "))" << ops[k] << d << endl;
            } if (calc(j, calc(i, a, b), calc(k, c, d)) == 24) {
              count += 1;
              file << count << ". (" << a << ops[i] << b << ")" << ops[j] << "(" << c << ops[k] << d << ")" << endl;
            } if (calc(i, a, calc(k, calc(j ,b, c),d)) == 24) {
              count += 1;
              file << count << ". " << a << ops [i] << "((" << b << ops[j] << c << ")" << ops[k] << d << ")" << endl;
            } if (calc(i, a, calc(j, b, calc(k,c,d))) == 24) {
              count += 1;
              file << count << ". "<< a << ops[i] << "(" << b << ops[j] << "(" << c << ops[k] << d << "))" << endl;
            }
          }
        }
      }
    } while (next_permutation(values, values+4)); //permutasi

    if (count == 0) {
      file << "Tidak ada solusi.";
    } else {
      file << "\nTotal solusi: " << count << endl;
    }
    file << "Waktu eksekusi: " <<(float)time_req/CLOCKS_PER_SEC << " detik" << endl;
  }
}

