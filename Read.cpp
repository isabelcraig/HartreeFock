
#include "Read.hpp"

using namespace std;

void READIN::geometry(const char *filename, struct Geometry *geomStruct){
    // open filename
    ifstream input(filename);
    if (not input.is_open()) {
        std::string message = "Unable to open file : ";
        message += filename;
        cout << message.c_str() << endl;
        exit(-1);
    }

    // read the number of atoms from filename
    input >> geomStruct->natom;
    geomStruct->zvals = new int[geomStruct->natom];

    // Dynamically Allocate Space for geom
    geomStruct->geom = new double* [geomStruct->natom];
    for(int i=0; i < geomStruct->natom; i++)
        geomStruct->geom[i] = new double[3];

    // read in the geometry from filename
    for(int i=0; i < geomStruct->natom; i++)
        input >> geomStruct->zvals[i] >> geomStruct->geom[i][0] >> geomStruct->geom[i][1] >> geomStruct->geom[i][2];

    input.close();
}


void READIN::val(const char *filename, double *val) {
    FILE *input;
    input = fopen(filename, "r");
    if(!input) {
        string msg = filename;
        msg = "File opening failed with " + msg;
        perror(msg.c_str());
    }
    fscanf(input, "%lf", val);
    fclose(input);
}

void READIN::val(const char *filename, int *val) {
    FILE *input;
    input = fopen(filename, "r");
    if(!input) {
        string msg = filename;
        msg = "File opening failed with " + msg;
        perror(msg.c_str());
    }
    fscanf(input, "%d", val);
    fclose(input);
}

void READIN::SymMatrix(const char *filename, Eigen::MatrixXd *M) {
    FILE *input;
    setzero(M);
    input = fopen(filename, "r");
    if(!input) {
        string msg = filename;
        msg = "File opening failed with " + msg;
        perror(msg.c_str());
    }
    int i,j;
    double val;
    while (!feof(input)) {
        fscanf(input, "%d %d %lf", &i, &j, &val);
        (*M)(j-1,i-1) = val;
        (*M)(i-1,j-1) = val;
    }
    fclose(input);
}

void READIN::TEI(const char *filename, Eigen::MatrixXd *TEI){
  FILE *input;
  setzero(TEI);
  input = fopen(filename, "r");
    if(!input) {
        string msg = filename;
        msg = "File opening failed with " + msg;
        perror(msg.c_str());
    }
  int i, j, k, l, ij, kl, ji, lk;
  double val;

  while(fscanf(input, "%d %d %d %d %lf", &i, &j, &k, &l, &val) != EOF) {

    ij = compoundIndex(i-1,j-1);
    kl = compoundIndex(k-1,l-1);
    ji = compoundIndex(j-1,i-1);
    lk = compoundIndex(l-1,k-1);

    (*TEI)(compoundIndex(ij,kl)) = val;
    (*TEI)(compoundIndex(ji,kl)) = val;
    (*TEI)(compoundIndex(ij,lk)) = val;
    (*TEI)(compoundIndex(ji,lk)) = val;
    (*TEI)(compoundIndex(kl,ij)) = val;
    (*TEI)(compoundIndex(kl,ji)) = val;
    (*TEI)(compoundIndex(lk,ji)) = val;
    (*TEI)(compoundIndex(lk,ij)) = val;

  }
  fclose(input);
}
