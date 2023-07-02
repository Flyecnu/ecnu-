#include <bits/stdc++.h>
using namespace std;

#define U 1000
#define I 999

double mat[U][I] = {0};
double sim[I][I] = {0};
double user_ave[U];
double item_ave[I];
int user_active[U] = {0};

string dst_path = "./Assign-1-result/";
string user_path = dst_path + "user_ave.csv";
string item_path = dst_path + "item_ave.csv";
string matrix_path = dst_path + "matrix.csv";
////////

void read_matrix(string path){
    ifstream inFile(path, ios::in);
    if ( ! inFile) {
        printf("Open file failed. \n");
        return;
    }
    int i = 0, j;
    string line;
    string field;
    while (getline(inFile, line)){// 按行读取CSV文件中的数据
        string field;
        istringstream sin(line); // 将整行字符串line读入到字符串流sin中
        j = 0;
        while ( getline(sin, field, ',') ){
            //////////////////////////////////////
            mat[i][j] = atof(field.c_str());
            //////////////////////////////////////
            ++ j;
        }
        ++ i;
    }
    inFile.close();
    cout << "total lines: " << i << endl;
    cout << "finish reading" << endl;
}

void read_list(string path, double * dst){
    ifstream inFile(path, ios::in);
    if ( ! inFile ) {
        printf("Open file failed. \n");
        return;
    }
    int i = 0;
    string line, field;
    while (getline(inFile, line)){// 按行读取CSV文件中的数据
        string field;
        istringstream sin(line); // 将整行字符串line读入到字符串流sin中
        getline(sin, field, ',');
        dst[i] = atof(field.c_str());
        ++ i;
    }
    inFile.close();
    cout << "total lines: " << i << endl;
    cout << "finish reading" << endl;
}

void user_active_cal(){
    for ( int u = 0; u < U; ++ u )
        for ( int i = 0; i < I; ++ i )
            if ( mat[u][i] > 0 )
                ++ user_active[u];
}

void item_sim_cal_penal(string to_path){
    ofstream outFile(to_path, ios::out);
    if ( ! outFile ) {
        printf("Open file failed. \n");
        return;
    }
    for ( int ia = 0; ia < I; ++ ia ){
        if ( ia % 100 == 0 )
            printf("Processing item %d...\n", ia);
        sim[ia][ia] = 1;    // 自己和自己的相似度为1
        for ( int ib = ia + 1; ib < I; ++ ib ){
            int Na = 0, Nb = 0;
            double penal = 0;
            for ( int u = 0; u < U; ++ u ){
                if ( mat[u][ia] > 3 )
                    ++ Na;
                if ( mat[u][ib] > 3 )
                    ++ Nb;
                if ( mat[u][ia] > 3 && mat[u][ib] > 3 )
                    penal += 1.0 / log2(1+user_active[u]);
            }
            if ( Na * Nb > 0 )
                sim[ia][ib] = penal / sqrt(Na * Nb);
            else
                sim[ia][ib] = 0;
            sim[ib][ia] = sim[ia][ib];
        }
        for ( int ib = 0; ib < I; ++ ib ){
            outFile << sim[ia][ib];
            outFile << ( ib == I - 1 ? '\n' : ',');
        }
    }
    outFile.close();
    cout << "finish writing similarity" << endl;
}

void item_sim_cal_cos(string to_path){
    ofstream outFile(to_path, ios::out);
    if ( ! outFile ) {
        printf("Open file failed. \n");
        return;
    }
    for ( int ia = 0; ia < I; ++ ia ){
        if ( ia % 100 == 0 )
            printf("Processing item %d...\n", ia);
        sim[ia][ia] = 1;    // 自己和自己的相似度为1
        double ra = item_ave[ia];   // ia 平均得分
        for ( int ib = ia + 1; ib < I; ++ ib ){
            double rb = item_ave[ib];   // ib 平均得分
            double E = 0, Sa = 0, Sb = 0;
            int simcnt = 0;
            for ( int u = 0; u < U; ++ u ){
                if ( mat[u][ia] > 0 && mat[u][ib] > 0 ){
                    ++ simcnt;
                    E += ( mat[u][ia] - ra ) * ( mat[u][ib] - rb );
                    Sa += ( mat[u][ia] - ra ) * ( mat[u][ia] - ra );
                    Sb += ( mat[u][ib] - rb ) * ( mat[u][ib] - rb );
                }
            }
            // sim[ia][ib]
            if ( simcnt > 5 && Sa * Sb != 0 ){
                sim[ia][ib] = E / sqrt(Sa*Sb);
                printf("cnt = %d ia = %d ib = %d sim_ab = %.5f\n", simcnt, ia, ib, sim[ia][ib]);
            }else{
                sim[ia][ib] = 0;
            }
            // 对称
            sim[ib][ia] = sim[ia][ib];
        }
        for ( int ib = 0; ib < I; ++ ib ){
            outFile << sim[ia][ib];
            outFile << ( ib == I - 1 ? '\n' : ',');
        }
    }
    outFile.close();
    cout << "finish writing similarity" << endl;
}

void floyd(string to_path){
    ofstream outFile(to_path, ios::out);
    if ( ! outFile ) {
        printf("Open file failed. \n");
        return;
    }
    for ( int k = 0; k < I; ++ k )
        for ( int i = 0; i < I; ++ i )
            for ( int j = 0; j < I; ++ j )
                if ( sim[i][j] == 0 && sim[i][k] * sim[k][j] > 0 )
                    sim[i][j] = sim[i][k] * sim[k][j];
    for ( int ia = 0; ia < I; ++ ia )
        for ( int ib = 0; ib < I; ++ ib ){
            outFile << sim[ia][ib];
            outFile << ( ib == I - 1 ? '\n' : ',');
        }
}

void item_sim_sort(string to_path){
    ofstream outFile(to_path, ios::out);
    if ( ! outFile ) {
        printf("Open file failed. \n");
        return;
    }
    for ( int a = 0; a < I; ++ a ){
        sort(sim[a], sim[a] + I, greater<double>());
        for ( int b = 0; b < I; ++ b ){   // 写入一行
            outFile << sim[a][b];
            outFile << ( b == I - 1 ? '\n' : ',');
        }
    }
    cout << "finish sorting" << endl;
}

string sim_path = dst_path + "isim.csv";
string sim_sorted_path = dst_path + "isim_sorted.csv";

int main(){
    // 读取数据
    read_matrix(matrix_path);
    read_list(user_path, user_ave);
    read_list(item_path, item_ave);
    //
    // 1. Inverse User Frequency ///
    // user_active_cal();
    // item_sim_cal_penal(sim_path);
    // 2. Consine Similarity //////
     item_sim_cal_cos(sim_path);
    //
  //floyd(sim_path); // 相似传递
    // 
    item_sim_sort(sim_sorted_path); // 查看输出的相似度
    return 0;
}