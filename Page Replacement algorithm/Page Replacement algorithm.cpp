#include <iostream>
#include <algorithm>
using namespace std;

bool check_collumn(int work_space[7][20], int i, int page_frames) {
    int check = work_space[0][i];
    for (int k = 1; k <= page_frames; k++) {
        if (check == work_space[k][i]) return true;
    }
    return false;
}

void FIFO(int n, int work_space[7][20], int page_frames, string fault[]) {
    int next = 1;
    for (int i = 0; i < page_frames; i++) {
        int check = 0;
        for (int j = 1; j <= page_frames; j++) {
            if (i == 0) {
                work_space[j][i] = work_space[0][i];
                next++;
                check = 1;
                break;
            }
            else {
                work_space[j][i] = work_space[j][i - 1];
            }
        }
        if (check == 1) {
            continue;
        }
        if (next == page_frames) {
            work_space[next][i] = work_space[0][i];
            next = 1;
        }
        else {
            work_space[next][i] = work_space[0][i];
            next++;
        }
    }
    next = 1;
    for (int i = page_frames; i < n; i++) {
        for (int j = 1; j <= page_frames; j++) {
            work_space[j][i] = work_space[j][i - 1];
        }
        if (check_collumn(work_space, i, page_frames)) {
            fault[i] = "h";
        }
        else {
            fault[i] = "*";
            work_space[next][i] = work_space[0][i];
            next++;
        }
        if (next > page_frames) next = 1;
    }

}

void OPT(int n, int work_space[7][20], int page_frames, string fault[]) {
    int next = 1;
    for (int i = 0; i < page_frames; i++) {
        int check = 0;
        for (int j = 1; j <= page_frames; j++) {
            if (i == 0) {
                work_space[j][i] = work_space[0][i];
                next++;
                check = 1;
                break;
            }
            else {
                work_space[j][i] = work_space[j][i - 1];
            }
        }
        if (check == 1) {
            continue;
        }
        if (next == page_frames) {
            work_space[next][i] = work_space[0][i];
            next = 1;
        }
        else {
            work_space[next][i] = work_space[0][i];
            next++;
        }
    }
    for (int i = page_frames; i < n; i++) {
        int no_more = -1;
        int max = 0;
        for (int j = 1; j <= page_frames; j++) {
            work_space[j][i] = work_space[j][i - 1];
        }
        if (check_collumn(work_space, i, page_frames)) {
            fault[i] = "h";
        }
        else {
            fault[i] = "*";
            for (int k = 1; k <= page_frames; k++) {
                int check = 0;
                for (int l = i + 1; l < n; l++) {
                    if (work_space[k][i] == work_space[0][l] && l > max) {
                        max = l;
                        check = 1;
                    }
                    if (l == n - 1 && check == 0) {
                        no_more = k;
                    }
                }
            }
            if (no_more != -1) {
                work_space[no_more][i] = work_space[0][i];
            }
            else {
                for (int m = 1; m <= page_frames; m++) {
                    if (work_space[m][i] == work_space[0][max]) {
                        work_space[m][i] = work_space[0][i];
                    }
                }
            }
        }
    }

}

void LRU(int n, int work_space[7][20], int page_frames, string fault[]) {
    int next = 1;
    for (int i = 0; i < page_frames; i++) {
        int check = 0;
        for (int j = 1; j <= page_frames; j++) {
            if (i == 0) {
                work_space[j][i] = work_space[0][i];
                next++;
                check = 1;
                break;
            }
            else {
                work_space[j][i] = work_space[j][i - 1];
            }
        }
        if (check == 1) {
            continue;
        }
        if (next == page_frames) {
            work_space[next][i] = work_space[0][i];
            next = 1;
        }
        else {
            work_space[next][i] = work_space[0][i];
            next++;
        }
    }
    for (int i = page_frames; i < n; i++) {
        int queue[10];
        for (int i = 0; i < page_frames; i++) {
            queue[i] = -1;
        }
        int count = 0;
        int max = i - 1;
        int check;
        for (int j = 1; j <= page_frames; j++) {
            work_space[j][i] = work_space[j][i - 1];
        }
        if (check_collumn(work_space, i, page_frames)) {
            fault[i] = "h";
        }
        else {
            fault[i] = "*";
            for (int l = i - 1; l >= 0; l--) {
                check = 0;
                for (int m = 1; m <= page_frames; m++) {
                    if (work_space[0][l] == work_space[m][i]) {
                        for (int d = 0; d < page_frames; d++) {
                            if (work_space[0][l] == queue[d]) {
                                check = 1;
                                break;
                            }
                        }
                        if (check == 1) break;
                        max = l;
                        queue[count] = work_space[m][i];
                        count++;
                    }
                }
            }

            for (int m = 1; m <= page_frames; m++) {
                if (work_space[m][i] == work_space[0][max]) {
                    work_space[m][i] = work_space[0][i];
                }
            }
        }
    }

}


int main()
{
    int n = 11;
    int a[11];
    int choice, page_frames;
    int work_space[7][20];
    string fault[100];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 20; j++) {
            work_space[i][j] = -1;
        }
        cout << "\n";
    }
    system("clear");
    cout << "\n\t ------------------------------------------------------------";
    cout << "\n\t               Page Replacement Algorithm";
    cout << "\n\t              1. Default referenced sequence";
    cout << "\n\t              2. Manual input sequence";
    cout << "\n\t ------------------------------------------------------------";
    cout << "\n\n\t Please choose: ";
    cin >> choice;
    switch (choice) {
    case 1:
        a[0] = 1, a[1] = 9, a[2] = 5, a[3] = 2, a[4] = 1, a[5] = 6, a[6] = 9, a[7] = 5, a[8] = 0, a[9] = 0, a[10] = 7;
        for (int i = 0; i < n; i++) {
            work_space[0][i] = a[i];
        }
        break;
    case 2:
        system("clear");
        cout << "\n\t ------------------------------------------------------------";
        cout << "\n\t               Page Replacement Algorithm";
        cout << "\n\t Input the length of the sequence: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            system("clear");
            cout << "\n\t ------------------------------------------------------------";
            cout << "\n\t               Page Replacement Algorithm";
            cout << "\n\t Input the sequence (hit Enter after every number): ";
            cin >> work_space[0][i];
        }
        break;
    }
    system("clear");
    cout << "\n\t ------------------------------------------------------------";
    cout << "\n\t               Page Replacement Algorithm";
    cout << "\n\t Input page frames: ";
    cin >> page_frames;
    system("clear");
    cout << "\n\t ------------------------------------------------------------";
    cout << "\n\t               Page Replacement Algorithm";
    cout << "\n\t              1. FIFO algorithm";
    cout << "\n\t              2. OPT algorithm";
    cout << "\n\t              3. LRU algorithm";
    cout << "\n\t ------------------------------------------------------------";
    cout << "\n\n\t Please choose: ";
    cin >> choice;
    switch (choice) {
    case 1:
        FIFO(n, work_space, page_frames, fault);
        break;
    case 2:
        OPT(n, work_space, page_frames, fault);
        break;
    case 3:
        LRU(n, work_space, page_frames, fault);
        break;
    }
    system("clear");
    switch (choice) {
    case 1:
        cout << "\n\t ------------------------------------------------------------";
        cout << "\n\t              FIFO Page Replacement Algorithm";
        break;
    case 2:
        cout << "\n\t ------------------------------------------------------------";
        cout << "\n\t              OPT Page Replacement Algorithm";
        break;
    case 3:
        cout << "\n\t ------------------------------------------------------------";
        cout << "\n\t              LRU Page Replacement Algorithm";
        break;
    }
    cout << "\n\n";
    for (int i = 0; i < 7; i++) {
        cout << "\t\t";
        for (int j = 0; j < 20; j++) {
            if (work_space[i][j] == -1) cout << "    ";
            if (work_space[i][j] != -1) {
                cout << work_space[i][j] << "   ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < page_frames; i++) {
        fault[i] = "*";
    }
    cout << "\t        ";
    for (int i = 0; i < n; i++) {
        cout << fault[i] << "   ";

    }
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (fault[i] == "*") count++;

    }
    cout << "\n\t               Number of Page Fault: " << count;
    cout << "\n\t ------------------------------------------------------------\n";
}