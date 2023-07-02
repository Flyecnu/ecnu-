#include <bits/stdc++.h>
using namespace std;

#define U 1000
#define I 999

double mat[U][I] = {0};
double sim[U][U] = {0};
double user_ave[U];
double item_ave[I];

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

void user_sim_cal_pearson_cos(string to_path){
    ofstream outFile(to_path, ios::out);
    if ( ! outFile ) {
        printf("Open file failed. \n");
        return;
    }
    for ( int ua = 0; ua < 1000; ++ ua ){
        if ( ua % 100 == 0 )
            printf("Processing user %d...\n", ua);
        sim[ua][ua] = 1; // 自己和自己的相似度为1
        for ( int ub = ua + 1; ub < 1000; ++ ub ){
            double r_a = user_ave[ua];
            double r_b = user_ave[ub];
            double E = 0, Sa = 0, Sb = 0;
            bool comm_flag = false;
            // 计算余弦相似度
            int nPa ,  nPb, nNa, nNb, nP, nN; // a,b给高分、a,b给低分、共同给分
            nPa = nPb =  nNa = nNb = nP = nN = 0;
            for ( int item = 0; item < 999; ++ item ){
                double r_ai = mat[ua][item];
                double r_bi = mat[ub][item];
                if ( r_ai >= 3 )        // a给高分3,4,5
                    nPa += 1;
                else if ( r_ai >= 1 )   // a给低分1,2
                    nNa += 1;
                else if ( r_bi >= 3 )   // b给高分3,4,5
                    nPb += 1;
                else if ( r_bi >= 1 )   // b给低分1,2
                    nNb += 1;
                if ( r_ai > 0 && r_bi > 0 ){ // a和b同时给i打过分
                    comm_flag = true;
                    if ( r_ai >= 3 and r_bi >= 3 )
                        nP += 1;
                    else if ( (1 <= r_ai && r_ai < 3 )&& (1 <= r_bi && r_bi < 3 ))
                        nN += 1;
                    E += ( r_ai - r_a ) * ( r_bi - r_b );
                    Sa += ( r_ai - r_a ) * ( r_ai - r_a );
                    Sb += ( r_bi - r_b ) * ( r_bi - r_b );
                }
            }
            if ( Sa * Sb != 0 )
                sim[ua][ub] = E / ( sqrt(Sa) * sqrt(Sb) );
            else if ( nPa != 0 && nPb != 0 )
                sim[ua][ub] = nP / sqrt(nPa * nPb);
            else if ( nNa != 0 && nNb != 0 )
                sim[ua][ub] = nN / sqrt(nNa * nNb);
            else{  // 没有共同打分或某一用户所有商品打分都一样
                //printf("Sa * Sb == 0: ua %d ub %d\n", ua, ub);
                sim[ua][ub] = 0;
            }
            sim[ub][ua] = sim[ua][ub];
        }
        for ( int ub = 0; ub < 1000; ++ ub ){   // 写入一行
            outFile << sim[ua][ub];
            outFile << ( ub == 1000 - 1 ? '\n' : ',');
        }
    }
    outFile.close();
    cout << "finish writing similarity" << endl;
}

void user_sim_cal_pearson(string to_path){
    ofstream outFile(to_path, ios::out);
    if ( ! outFile ) {
        printf("Open file failed. \n");
        return;
    }
    for ( int ua = 0; ua < U; ++ ua ){
        if ( ua % 100 == 0 )
            printf("Processing user %d...\n", ua);
        sim[ua][ua] = 1; // 自己和自己的相似度为1
        for ( int ub = ua + 1; ub < U; ++ ub ){
            double r_a = user_ave[ua];
            double r_b = user_ave[ub];
            double E = 0, Sa = 0, Sb = 0;
            int simcnt = 0;
            for ( int item = 0; item < I; ++ item ){
                double r_ai = mat[ua][item];
                double r_bi = mat[ub][item];
                if ( r_ai > 0 && r_bi > 0 ){ // a和b同时给i打过分
                    ++ simcnt;
                    E += ( r_ai - r_a ) * ( r_bi - r_b );
                    Sa += ( r_ai - r_a ) * ( r_ai - r_a );
                    Sb += ( r_bi - r_b ) * ( r_bi - r_b );
                }
            }
            if ( simcnt > 1 && Sa * Sb != 0 ){
                sim[ua][ub] = E / sqrt(Sa * Sb);
                printf("cnt = %d ua = %d ub = %d sim_ab = %.5f\n", simcnt, ua, ub, sim[ua][ub]);
            }else{  // 没有共同打分或某一用户所有商品打分都一样
                // printf("Sa * Sb == 0: ua %d ub %d\n", ua, ub);
                sim[ua][ub] = 0;
                // cout << simcnt << endl;
            }
            sim[ub][ua] = sim[ua][ub];
        }
        for ( int ub = 0; ub < U; ++ ub ){   // 写入一行
            outFile << sim[ua][ub];
            outFile << ( ub == U - 1 ? '\n' : ',');
        }
    }
    outFile.close();
    cout << "finish writing similarity" << endl;
}

void user_sim_sort(string to_path){
    ofstream outFile(to_path, ios::out);
    if ( ! outFile ) {
        printf("Open file failed. \n");
        return;
    }
    for ( int ua = 0; ua < U; ++ ua ){
        sort(sim[ua], sim[ua] + U, greater<double>());
        for ( int ub = 0; ub < U; ++ ub ){   // 写入一行
            outFile << sim[ua][ub];
            outFile << ( ub == U - 1 ? '\n' : ',');
        }
    }
    cout << "finish sorting" << endl;
}

void floyd(string to_path){
    ofstream outFile(to_path, ios::out);
    if ( ! outFile ) {
        printf("Open file failed. \n");
        return;
    }
    for ( int k = 0; k < U; ++ k )
        for ( int i = 0; i < U; ++ i )
            for ( int j = 0; j < U; ++ j )
                if ( sim[i][j] == 0 && sim[i][k] * sim[k][j] > 0 )
                    sim[i][j] = sim[i][k] * sim[k][j];
    for ( int ia = 0; ia < U; ++ ia )
        for ( int ib = 0; ib < U; ++ ib ){
            outFile << sim[ia][ib];
            outFile << ( ib == U - 1 ? '\n' : ',');
        }
    cout << "finish writing simarity floyd" << endl;
}
void user_sim_cal_cosine(string to_path) {
    ofstream outFile(to_path, ios::out);
    if (!outFile) {
        printf("Open file failed. \n");
        return;
    }
    for (int ua = 0; ua < U; ++ua) {
        if (ua % 100 == 0)
            printf("Processing user %d...\n", ua);
        sim[ua][ua] = 1; // 自己和自己的相似度为1
        for (int ub = ua + 1; ub < U; ++ub) {
            double numerator = 0, denominator_a = 0, denominator_b = 0;
            int simcnt = 0;
            for (int item = 0; item < I; ++item) {
                double r_ai = mat[ua][item];
                double r_bi = mat[ub][item];
                if (r_ai > 0 && r_bi > 0) { // a和b同时给i打过分
                    ++simcnt;
                    numerator += r_ai * r_bi;
                    denominator_a += r_ai * r_ai;
                    denominator_b += r_bi * r_bi;
                }
            }
            if (simcnt > 0) {
                sim[ua][ub] = numerator / (sqrt(denominator_a) * sqrt(denominator_b));
                sim[ub][ua] = sim[ua][ub];
                // printf("cnt = %d ia = %d ib = %d sim_ab = %.5f\n", simcnt, ia, ib, sim[ia][ib]);
            }
            else {
                sim[ua][ub] = sim[ub][ua] = 0; // 没有共同打分
            }
        }
        for (int ub = 0; ub < U; ++ub) {   // 写入一行
            outFile << sim[ua][ub];
            outFile << (ub == U - 1 ? '\n' : ',');
        }
    }
    outFile.close();
    cout << "finish writing similarity" << endl;
}


void user_sim_cal_user_iif(string to_path) {
    ofstream outFile(to_path, ios::out);
    if (!outFile) {
        printf("Open file failed. \n");
        return;
    }
    vector<int> item_cnt(I, 0);
    for (int item = 0; item < I; ++item) {
        for (int user = 0; user < U; ++user) {
            if (mat[user][item] > 0) {
                ++item_cnt[item];
            }
        }
    }
    for (int ua = 0; ua < U; ++ua) {
        if (ua % 100 == 0)
            printf("Processing user %d...\n", ua);
        sim[ua][ua] = 1; // 自己和自己的相似度为1
        double u_a_iif = 0;
        for (int item = 0; item < I; ++item) {
            if (mat[ua][item] > 0) {
                u_a_iif += log(1 + U / item_cnt[item]);
            }
        }
        for (int ub = ua + 1; ub < U; ++ub) {
            double numerator = 0, denominator_a = 0, denominator_b = 0;
            int simcnt = 0;
            double u_b_iif = 0;
            for (int item = 0; item < I; ++item) {
                double r_ai = mat[ua][item];
                double r_bi = mat[ub][item];
                if (r_ai > 0 && r_bi > 0) { // a和b同时给i打过分
                    ++simcnt;
                    numerator += (r_ai - u_a_iif) * (r_bi - u_b_iif);
                    denominator_a += pow(r_ai - u_a_iif, 2);
                    denominator_b += pow(r_bi - u_b_iif, 2);
                }
            }
            if (simcnt > 2) {
                denominator_a = sqrt(denominator_a);
                denominator_b = sqrt(denominator_b);
                double sim_value = numerator / (denominator_a * denominator_b);
                sim[ua][ub] = sim_value;
                sim[ub][ua] = sim_value;
            }
            else {
                sim[ua][ub] = sim[ub][ua] = 0; // 没有共同打分
            }
        }
        for (int ub = 0; ub < U; ++ub) {   // 写入一行
            outFile << sim[ua][ub];
            outFile << (ub == U - 1 ? '\n' : ',');
        }
    }
    outFile.close();
    cout << "finish writing similarity" << endl;
}

string sim_path = dst_path + "usim.csv";
string sim_sorted_path = dst_path + "usim_sorted.csv";

int main(){
    // 读取 u_i_matrix
    read_matrix(matrix_path);
    read_list(user_path, user_ave);
    read_list(item_path, item_ave);
    //
    // 1. Pearson + Cosine
     user_sim_cal_pearson_cos(sim_path);
    // 2. Pearson
    // user_sim_cal_pearson(sim_path);
    // 
          // 3
     user_sim_cal_cosine(sim_path);
// 4
     // user_sim_cal_user_iif(sim_path);

         floyd(sim_path); // 相似传递
    // 


     user_sim_sort(sim_sorted_path); // 查看输出的相似度
    return 0;
}