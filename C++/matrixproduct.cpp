#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <papi.h>

using namespace std;

#define SYSTEMTIME clock_t

 
void OnMult(int m_ar, int m_br) {
    SYSTEMTIME Time1, Time2;
    char st[100];
    double temp;
    int i, j, k;

    double *pha, *phb, *phc;

    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

    for (i = 0; i < m_ar; i++)
        for (j = 0; j < m_ar; j++)
            pha[i * m_ar + j] = (double)1.0;

    for (i = 0; i < m_br; i++)
        for (j = 0; j < m_br; j++)
            phb[i * m_br + j] = (double)(i + 1);

    Time1 = clock();

    for (i = 0; i < m_ar; i++) {
        for (j = 0; j < m_br; j++) {
            temp = 0;
            for (k = 0; k < m_ar; k++) {
                temp += pha[i * m_ar + k] * phb[k * m_br + j];
            }
            phc[i * m_ar + j] = temp;
        }
    }

    Time2 = clock();
    sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
    cout << st;

    // display 10 elements of the result matrix to verify correctness
    cout << "Result matrix: " << endl;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < min(10, m_br); j++)
            cout << phc[j] << " ";
    }
    cout << endl;

    free(pha);
    free(phb);
    free(phc);
}

void OnMultLine(int m_ar, int m_br) {
    SYSTEMTIME Time1, Time2;
    char st[100];
    double temp;
    int i, j, k;

    double *pha, *phb, *phc;

    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

    for (i = 0; i < m_ar; i++)
        for (j = 0; j < m_ar; j++)
            pha[i * m_ar + j] = (double)1.0;

    for (i = 0; i < m_br; i++)
        for (j = 0; j < m_br; j++)
            phb[i * m_br + j] = (double)(i + 1);

    for (i = 0; i < m_br; i++)
        for (j = 0; j < m_br; j++)
            phc[i * m_br + j] = 0;

    Time1 = clock();

    for (i = 0; i < m_ar; i++) {
        for (k = 0; k < m_ar; k++) {
            for (j = 0; j < m_br; j++) {
                phc[i * m_ar + j] += pha[i * m_ar + k] * phb[k * m_br + j];
            }
        }
    }

    Time2 = clock();
    sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
    cout << st;

    // display 10 elements of the result matrix to verify correctness
    cout << "Result matrix: " << endl;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < min(10, m_br); j++)
            cout << phc[j] << " ";
    }
    cout << endl;

    free(pha);
    free(phb);
    free(phc);
}

void OnMultBlock(int m_ar, int m_br, int bkSize) {
    SYSTEMTIME Time1, Time2;
    char st[100];
    double temp;

    int i, j, k, bi, bj, bk;

    double *pha, *phb, *phc;

    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

    for (i = 0; i < m_ar; i++)
        for (j = 0; j < m_ar; j++)
            pha[i * m_ar + j] = (double)1.0;

    for (i = 0; i < m_br; i++)
        for (j = 0; j < m_br; j++)
            phb[i * m_br + j] = (double)(i + 1);

    for (i = 0; i < m_br; i++)
        for (j = 0; j < m_br; j++)
            phc[i * m_br + j] = 0;

    Time1 = clock();

    for (bi = 0; bi < m_ar; bi += bkSize) {
        for (bk = 0; bk < m_ar; bk += bkSize) {
            for (bj = 0; bj < m_br; bj += bkSize) {
                for (i = bi; i < bi + bkSize; i++) {
                    for (k = bk; k < bk + bkSize; k++) {
                        for (j = bj; j < bj + bkSize; j++) {
                            phc[i * m_ar + j] += pha[i * m_ar + k] * phb[k * m_br + j];
                        }
                    }
                }
            }
        }
    }

    Time2 = clock();
    sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
    cout << st;

    // display 10 elements of the result matrix to verify correctness
    cout << "Result matrix: " << endl;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < min(10, m_br); j++)
            cout << phc[j] << " ";
    }
    cout << endl;

    free(pha);
    free(phb);
    free(phc);
}

void OnMultLine_Parallel1(int m_ar, int m_br) {
    SYSTEMTIME Time1, Time2;
    char st[100];
    double temp;
    int i, j, k;

    double *pha, *phb, *phc;

    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

    for (i = 0; i < m_ar; i++)
        for (j = 0; j < m_ar; j++)
            pha[i * m_ar + j] = (double)1.0;

    for (i = 0; i < m_br; i++)
        for (j = 0; j < m_br; j++)
            phb[i * m_br + j] = (double)(i + 1);

    for (i = 0; i < m_br; i++)
        for (j = 0; j < m_br; j++)
            phc[i * m_br + j] = 0;

    Time1 = clock();

#pragma omp parallel for private(i, j, k)
    for (i = 0; i < m_ar; i++) {
        for (k = 0; k < m_ar; k++) {
            for (j = 0; j < m_br; j++) {
                phc[i * m_ar + j] += pha[i * m_ar + k] * phb[k * m_br + j];
            }
        }
    }

    Time2 = clock();
    sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
    cout << st;

    // display 10 elements of the result matrix to verify correctness
    cout << "Result matrix: " << endl;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < min(10, m_br); j++)
            cout << phc[j] << " ";
    }
    cout << endl;

    free(pha);
    free(phb);
    free(phc);
}

void OnMultLine_Parallel2(int m_ar, int m_br) {
    SYSTEMTIME Time1, Time2;
    char st[100];
    double temp;
    int i, j, k;

    double *pha, *phb, *phc;

    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

    for (i = 0; i < m_ar; i++)
        for (j = 0; j < m_ar; j++)
            pha[i * m_ar + j] = (double)1.0;

    for (i = 0; i < m_br; i++)
        for (j = 0; j < m_br; j++)
            phb[i * m_br + j] = (double)(i + 1);

    for (i = 0; i < m_br; i++)
        for (j = 0; j < m_br; j++)
            phc[i * m_br + j] = 0;

    Time1 = clock();

#pragma omp parallel for private(i, j, k)
    for (i = 0; i < m_ar; i++) {
        for (k = 0; k < m_ar; k++) {
#pragma omp for
            for (j = 0; j < m_br; j++) {
                phc[i * m_ar + j] += pha[i * m_ar + k] * phb[k * m_br + j];
            }
        }
    }

    Time2 = clock();
    sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
    cout << st;

    // display 10 elements of the result matrix to verify correctness
    cout << "Result matrix: " << endl;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < min(10, m_br); j++)
            cout << phc[j] << " ";
    }
    cout << endl;

    free(pha);
    free(phb);
    free(phc);
}





void handle_error (int retval)
{
  printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
  exit(1);
}

void init_papi() {
  int retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT && retval < 0) {
    printf("PAPI library version mismatch!\n");
    exit(1);
  }
  if (retval < 0) handle_error(retval);

  std::cout << "PAPI Version Number: MAJOR: " << PAPI_VERSION_MAJOR(retval)
            << " MINOR: " << PAPI_VERSION_MINOR(retval)
            << " REVISION: " << PAPI_VERSION_REVISION(retval) << "\n";
}


int main (int argc, char *argv[]) {

    char c;
    int lin, col, blockSize;
    int op;
    
    int EventSet = PAPI_NULL;
    long long values[2];
    int ret;

    ret = PAPI_library_init(PAPI_VER_CURRENT);
    if (ret != PAPI_VER_CURRENT)
        cout << "FAIL" << endl;

    ret = PAPI_create_eventset(&EventSet);
    if (ret != PAPI_OK) cout << "ERROR: create eventset" << endl;

    ret = PAPI_add_event(EventSet, PAPI_L1_DCM);
    if (ret != PAPI_OK) cout << "ERROR: PAPI_L1_DCM" << endl;

    ret = PAPI_add_event(EventSet, PAPI_L2_DCM);
    if (ret != PAPI_OK) cout << "ERROR: PAPI_L2_DCM" << endl;

    op = 1;
    do {
        cout << endl << "1. Multiplication" << endl;
        cout << "2. Line Multiplication" << endl;
        cout << "3. Block Multiplication" << endl;
		cout << "4. Line Multiplication Parallel 1" << endl;
		cout << "5. Line Multiplication Parallel 2" << endl;
        cout << "Selection?: ";
        cin >> op;
        if (op == 0)
            break;
        printf("Dimensions: lins=cols ? ");
        cin >> lin;
        col = lin;

        // Start counting
        ret = PAPI_start(EventSet);
        if (ret != PAPI_OK) cout << "ERROR: Start PAPI" << endl;

        switch (op) {
        case 1:
            OnMult(lin, col);
            break;
        case 2:
            OnMultLine(lin, col);
            break;
        case 3:
            cout << "Block Size? ";
            cin >> blockSize;
            OnMultBlock(lin, col, blockSize);
        case 4:
            OnMultLine_Parallel1(lin, col);
            break;
        case 5:
            OnMultLine_Parallel2(lin, col);
            break;
        }

        ret = PAPI_stop(EventSet, values);
        if (ret != PAPI_OK) cout << "ERROR: Stop PAPI" << endl;
        printf("L1 DCM: %lld \n", values[0]);
        printf("L2 DCM: %lld \n", values[1]);

        ret = PAPI_reset(EventSet);
        if (ret != PAPI_OK)
            std::cout << "FAIL reset" << endl;

    } while (op != 0);

    ret = PAPI_remove_event(EventSet, PAPI_L1_DCM);
    if (ret != PAPI_OK)
        std::cout << "FAIL remove event" << endl;

    ret = PAPI_remove_event(EventSet, PAPI_L2_DCM);
    if (ret != PAPI_OK)
        std::cout << "FAIL remove event" << endl;

    ret = PAPI_destroy_eventset(&EventSet);
    if (ret != PAPI_OK)
        std::cout << "FAIL destroy" << endl;

    return 0;
}
