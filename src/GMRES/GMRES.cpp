#include <GMRES/GMRES.hpp>


CMM::CMM(){
    n_rows = 0;
    n_cols = 0;
}
CMM::CMM(int r, int c){
    n_cols = c;
    n_rows = r;
    mat.resize(c*r);
}


std::pair<int, int> CMM::shape(){
    return std::make_pair(n_rows, n_cols);
}
double CMM::operator()(int i, int j){
    return mat[i-1+n_rows*(j-1)];
}
void CMM::operator()(int i, int j, double val){
    mat[i-1+n_rows*(j-1)] = val;
}
std::vector<double> operator*(const std::vector<double>& one);
CMM operator*(CMM& one); 