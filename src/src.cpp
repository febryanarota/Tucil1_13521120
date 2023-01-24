#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

float calc(int ops, float a, float b) { 
  /*Mengembalikan nilai operasi a terhadap b*/
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
string ToString(int num){
  /*Mengubah integer menjadi string*/
  string str = "";
  while (num > 0){
      str = (char)(num % 10 + 48) + str;
      num /= 10;
  }
  return str;
}

int main() {
  cout << R"(
    .------..------.     .------..------..------..------..------..------.
    |2.--. ||4.--. |.-.  |P.--. ||U.--. ||Z.--. ||Z.--. ||L.--. ||E.--. |
    | (\/) || :/\: |     | :/\: || (\/) || :(): || :(): || :/\: || (\/) |
    | :\/: || :\/: |'-.-.| (__) || :\/: || ()() || ()() || (__) || :\/: |
    | '--'2|| '--'4|     | '--'P|| '--'U|| '--'Z|| '--'Z|| '--'L|| '--'E|
    `------'`------'  '-'`------'`------'`------'`------'`------'`------'
     2       4            P       U       Z       Z       L       E
  )";
  cout << "\n\n1. Manual Input" << endl;
  cout << "2. Randomize" << endl;
  int input;

  do {
    cout << "Pilih menu: ";
    cin >> input;
  } while (!(input == 1 || input == 2));

  int values[4];
  int n;
  int count = 0;
  char card[4]; 
  
  if (input == 1) { //input manual
    cout << "\nMasukkan 4 kartu (2-10, A, J, Q, K)!" << endl ;
    for (int i=0; i< 4; i++) {
      cout << "kartu ke-" << i+1 << ": ";
      cin >> card; 
      if (card[0] == 'A' && card[1] == '\0') {
        values[i] = 1;
      } else if (card[0] == 'J' && card[1] == '\0') {
        values[i] = 11;
      } else if (card[0] == 'Q' && card[1] == '\0') {
        values[i] = 12;
      } else if (card[0] == 'K' && card[1] == '\0') {
        values[i] = 13;
      } else if (int(card[0]) >= 50 && int(card[0]) <= 57 && card[1] == '\0') {
        values[i] = int(card[0]) - 48;
      } else if (card[0] == '1' && card[1] =='0' && card[2] == '\0') {
        values[i] = 10;
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
  vector<string> vec;
  string str;

  //permutasi urutan 4 bilangan (max 4! = 24)
  /*kemungkinan
    a # b # c # d
    a # c # b # d
    a # d # b # c
    dst
  */
  int perm[24][4];
  int p = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        for (int l = 0; l < 4; l++) {
          if (!(i == j || i == k || i == l || j == k || j == l || k == l)) {
            perm[p][0] = values[i];
            perm[p][1] = values[j];
            perm[p][2] = values[k];
            perm[p][3] = values[l];
            p++;
          }
        }
      }
    }
  }
  
  //Memeriksa apakah terdapat permutasi yang sama
  for (int i = 0; i<24; i++) {
    for (int j = i +1 ; j < 24; j++) {
      if (perm[j][0] == perm[i][0] && perm[j][1]== perm[i][1] && perm[j][2] == perm[i][2] && perm[j][3] == perm[i][3]) {
        perm[i][0] = 0; //tanda duplicate
      }
    }
  }

  char ops[4] = {'+', '-', '*', '/'};
  for (int i = 0; i<24; i++) {
    if (perm[i][0] != 0) {
      int a = perm[i][0]; int b = perm[i][1]; int c = perm[i][2]; int d = perm[i][3];
      for (int i = 0; i<4; i++) {
        for (int j = 0; j<4; j++) {
          for (int k = 0; k<4; k++) {
          
            // ((a #i b) #j c) #k d
            if (calc(k, calc(j, calc(i, a, b), c), d) == 24) {
              count += 1;
              str = ToString(count) + ". ((" + ToString(a) + ops[i] + ToString(b) + ")" + ops[j] + ToString(c) + ")" + ops[k] + ToString(d) + "\n";
              vec.push_back(str);
            }

            // (a #i (b #j c)) #k d
            if (calc(k, calc(i, a, calc(j, b, c)), d) == 24) {
              count += 1;
              str = ToString(count) + ". (" + ToString(a) + ops[i] + "(" + ToString(b) + ops[j] + ToString(c) + "))" + ops[k] + ToString(d) + "\n";
              vec.push_back(str);
            }
            
            // (a #i b) #j (c #k d)
            if (calc(j, calc(i, a, b), calc(k, c, d)) == 24) {
              count += 1;
              str = ToString(count) + ". (" + ToString(a) + ops[i] + ToString(b) + ")" + ops[j] + "(" + ToString(c) + ops[k] + ToString(d) + ")" + "\n";
              vec.push_back(str);
            }

            // a #i ((b #j c) #k d)
            if (calc(i, a, calc(k, calc(j ,b, c),d)) == 24) {
              count += 1;
              str = ToString(count) + ". " + ToString(a) + ops[i] + "((" + ToString(b) + ops[j] + ToString(c) + ")" + ops[k] + ToString(d) + ")" + "\n";
              vec.push_back(str);
            }

            // a #i (b #j (c #k d))
            if (calc(i, a, calc(j, b, calc(k,c,d))) == 24) {
              count += 1;
              str = ToString(count) + ". " + ToString(a) + ops[i] + "(" + ToString(b) + ops[j] + "(" + ToString(c) + ops[k] + ToString(d) + "))" + "\n";
              vec.push_back(str);
            }
          }
        }
      }
    }
  }

  if (count == 0) {
    cout << "\n\nTidak ada solusi.\n";
  } else {
    cout << "\n\nTotal solusi: " << count << endl;
    for (auto i : vec) {
      cout << i;
    }
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
    filename = "../test/" + filename + ".txt";
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

    if (count == 0) {
      file << "\n\nTidak ada solusi.\n";
    } else {
      file << "\n\nTotal solusi: " << count << endl;
      for (auto i : vec) {
        file << i;
      }
    }
    file << "Waktu eksekusi: " <<(float)time_req/CLOCKS_PER_SEC << " detik" << endl;
    cout << "\nSolusi berhasil disimpan!";
  }

}

