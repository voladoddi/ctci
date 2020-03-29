#include<bits/stdc++.h> 
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


vector<vector<int>> multiply(vector<vector<int>> & matrix1, vector<vector<int>> & matrix2)
{
    vector <vector<int>> result(matrix1.size(), vector<int>(matrix2[0].size(), 0));

    for(int i = 0; i < matrix1.size(); ++i)
        for(int j = 0; j < matrix2[0].size(); ++j)
            for(int k = 0; k < matrix1[0].size(); ++k)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }

    return result;

}

vector<vector<int>> transpose(vector<vector<int>> & input)
{
    vector<vector<int >> result;

    for (int i = 0; i < input[0].size(); i++) {
        vector<int>row;
        for (int j = 0; j < input.size(); j++) {
            row.push_back(input[j][i]);
        }
        result.push_back(row);
        row.clear();
    }

    return result;
}

vector<vector<int>> extract_matrix(string & s)
{
    vector<vector<int> > result;
    
    vector<int> row;
    for(int i = 0; i < s.size(); i++) {
        if(isalnum(s[i])) {
            string num(1, s[i]);
            row.push_back(stoi(num));
        } else if (s[i]==']' || s[i]==';') {
            result.push_back(row);
            row.clear();
        }
    }

    return result;
}

int trace(vector<vector<int>> & matrix)
{
    int tr = 0;

    for(int i = 0; i < matrix.size(); i++)
        tr += matrix[i][i];

    return tr;
}

int get_trace(string & input)
{ 
    vector<vector<int>> input_mat = extract_matrix(input);
    cout << "Extracted matrix : " << "(" << input_mat.size() << ", " << input_mat[0].size() << ")" << endl;
    vector<vector<int>> mat_transpose = transpose(input_mat);
    cout << "Tranpose matrix : " << "(" << mat_transpose.size() << ", " << mat_transpose[0].size() << ")" << endl;
    vector<vector<int>> multiplied_matrix = multiply(input_mat, mat_transpose);
    cout << "Multiplied matrix : " << "(" << multiplied_matrix.size() << ", " << multiplied_matrix[0].size() << ")" << endl;

    int tr = trace(multiplied_matrix);

    return tr;
}

int main()
{
    string s("[2,3,4;3,1,2]");
    int trace = get_trace(s);
    cout << "Trace of AA' : " << trace << endl;

    return 0;
}