#include <stdlib.h>
#include <numeric>

#include <iostream>

#include "Matrix.hpp"

namespace zich{

    Matrix::Matrix(const vector<double> &values, int rows, int cols){
        if(values.size() != rows*cols){
            throw invalid_argument("Wrong input, not valid matrix");
        }
        if(rows < 0 || cols < 0){
            throw invalid_argument("Wrong input, negative rows or cols");
        }
        this->rows = rows;
        this->cols = cols;
        this->values = vector(values);
    }
    Matrix::Matrix(){
        this->rows = 0;
        this->cols = 0;
        this->values = vector<double>();
    }


    double Matrix::sum(){
        return accumulate(this->values.begin(), this->values.end(), 0.0);
    }

    //+
    Matrix Matrix::operator+(const Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        vector<double> vec((unsigned int) (this->cols * this->rows));
        for(unsigned int i = 0; i < (this->cols * this->rows); i++){
            vec.at(i) = (this->values.at(i) + other.values.at(i));
        }
        Matrix m_new(vec, this->rows, this->cols);
        return m_new;
    }

    //+=
    Matrix& Matrix::operator+=(const Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        for(unsigned int i = 0; i < this->cols * this->rows; i++){
            this->values.at(i) += other.values.at(i);
        }
        return *this;
    }

    //plus unary
    Matrix operator+(Matrix &other){
        return (other * 1);
    }


    //-
    Matrix Matrix::operator-(const Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        vector<double> vec((unsigned int) (this->cols * this->rows));
        for(unsigned int i = 0; i < this->cols * this->rows; i++){
            vec.at(i) = (this->values.at(i) - other.values.at(i));
        }
        Matrix m_new(vec, this->rows, this->cols);
        return m_new;
    }

    //-=
    Matrix& Matrix::operator-=(const Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        for(unsigned int i = 0; i < this->cols * this->rows; i++){
            this->values.at(i) -= other.values.at(i);
        }
        return *this;
    }

    //minus unary
    Matrix operator-(Matrix &other){
        return (other * -1);
    }

    // >
    bool Matrix::operator>(Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        return(this->sum()) > other.sum();
    }

    // >=
    bool Matrix::operator>=(Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        return(this->sum()) >= other.sum();
    }

    //<
    bool Matrix::operator<(Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        return(this->sum()) < other.sum();
    }

    //<=
    bool Matrix::operator<=(Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        return(this->sum()) <= other.sum();
    }

    //== friend
    bool operator==(Matrix const &a, Matrix const &b){
        if(a.rows != b.rows || a.cols != b.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        for(unsigned int i = 0; i < a.cols * a.rows; i++){
            if(a.values.at(i) != b.values.at(i)){
                return false;
            }
        }
        return true;
    }

    //!=
    bool Matrix::operator!=(Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        for(unsigned int i = 0; i < this->cols * this->rows; i++){
            if(this->values.at(i) != other.values.at(i)){
                return true;
            }
        }
        return false;
    }

    //++
    //++x
    Matrix& Matrix::operator++(){ //prefix
        for(unsigned int i = 0; i < this->cols * this->rows; i++){
            this->values.at(i) = (this->values.at(i) + 1);
        }
        return *this;
    }

    //x++ 
    Matrix Matrix::operator++(int num){ //postfix
        Matrix temp = *this * 1;
        for(unsigned int i = 0; i < this->cols * this->rows; i++){
            this->values.at(i) = (this->values.at(i) + 1);
        }
        return temp;
    }

    //--
    //--x
    Matrix& Matrix::operator--(){ //prefix
        for(unsigned int i = 0; i < this->cols * this->rows; i++){
            this->values.at(i) = (this->values.at(i) - 1);
        }
        return *this; 
    }

    //x--
    Matrix Matrix::operator--(int num){ //postfix
        Matrix temp = *this * 1;
        for(unsigned int i = 0; i < this->cols * this->rows; i++){
            this->values.at(i) = this->values.at(i) - 1;
        }
        return temp;
    }


    //* mat*num
    Matrix Matrix::operator*(double num){
        vector<double> vec((unsigned int) ((this->cols) * (this->rows)));
        for(unsigned int i = 0; i < vec.size(); i++){
            if(this->values.at(i) == 0){
                continue;
            }

            vec.at(i) = this->values.at(i) * num;
        }
        Matrix m_new(vec, this->rows, this->cols);
        return m_new;
    }

    //* num*mat
    Matrix operator*(const double num, Matrix& mat){
        return (mat * num);
    }

    //*=
    Matrix& Matrix::operator*=(double num){
        for(unsigned int i = 0; i < this->cols * this->rows; i++){
            if(this->values.at(i) == 0){
                continue;
            }

            this->values.at(i) = (this->values.at(i) * num);
        }
        return *this;
    }

    //*  mat*mat
    Matrix Matrix::operator*(const Matrix& other){
        if(this->cols != other.rows){
            throw invalid_argument("Cant multiply these matrices");
        }
        vector<double> vec((unsigned int) (this->rows * other.cols));
        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < other.cols; j++){
                double s = 0;
                for(int k = 0; k < this->cols; k++){
                    s += this->values.at((unsigned int) (i * this->cols + k)) * other.values.at((unsigned int) (j + k*other.cols));
                }
                vec.at((unsigned int) (i * other.cols + j)) = s;
            }
        }
        Matrix m_new(vec, this->rows, other.cols);
        return m_new;
    }

    //*=
    Matrix& Matrix::operator*=(const Matrix& other){
        if(this->cols != other.rows){
            throw invalid_argument("Cant multiply these matrices");
        }
        vector<double> vec((unsigned int) (this->rows * other.cols));
        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < other.cols; j++){
                double s = 0;
                for(int k = 0; k < this->cols; k++){
                    s += this->values.at((unsigned int)(i * this->cols + k)) * other.values.at((unsigned int)(j + k*other.cols));
                }
                vec.at((unsigned int) (i * other.cols + j)) = s;
            }
        }
        this->values = vec;
        this->cols = other.cols;
        return *this; 
    }


    //cout
    std::ostream& operator<< (std::ostream& output, const Matrix& mat){
        for (int i = 0; i < mat.rows; i++){
            output << '[';
            for (int j = 0; j < mat.cols; j++){
                output << mat.values.at((unsigned int)(i * mat.cols + j));
                
                if (j != mat.cols - 1){
                    output << ' ';
                }
            }
            output << "]";
            if(i != mat.rows -1){
                output << "\n";
            }
        }
        return output;
    }
    // from stackoverflow
    // for string delimiter
    vector<string> split (const string &s, const string &delimiter) {
        size_t pos_start = 0;
        size_t pos_end = 0;
        size_t delim_len = delimiter.length();
        string token;
        vector<string> res;

        while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back (token);
        }

        res.push_back (s.substr (pos_start));
        return res;
    }

    //cin "[1 400 300], [1 8 2]\n"
    std::istream& operator>> (std::istream& input , Matrix& mat){
        string s;
        char c = input.get();
        while(c == '\n'){ // ignore empty lines - enter
            c = input.get();
        }
        while(c != '\n'){
            s += c;
            c = input.get();
        }

        // split all vectors by (, )
        vector<string> str_vec = split(s, ", ");

        //every vector-string --> split by ( )
        vector<vector<double>> num_mat;
        int cols = 0;
        for(unsigned int i = 0; i < str_vec.size(); i++){
            string v = str_vec.at(i).substr(1, str_vec.at(i).size()-2);

            //every vector-string --> array
            vector<string> nums = split(v, " ");
            vector<double> final_vec;
            for(unsigned int j = 0; j < nums.size(); j++){ // go over all strings numbers
                final_vec.push_back(stod(nums.at(j))); // push to vector and convert to double
            }
            if(i == 0){
                cols = final_vec.size();
            }

            // all vectors with same size, no -> exc
            else{
                if(cols != final_vec.size()){
                    throw invalid_argument("Not valid matrix");
                }
            }
            num_mat.push_back(final_vec); //push one vector - row
        }

        // create matrix from all the arrays
        vector<double> values;
        for(unsigned int i = 0; i < num_mat.size(); i++){
            for(unsigned int j = 0; j < cols; j++){
                values.push_back(num_mat.at(i).at(j));
            }
        }
        mat.values = values;
        mat.cols = cols;
        mat.rows = num_mat.size();

        return input;
    }
}