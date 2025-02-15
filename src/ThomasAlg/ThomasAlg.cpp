#include "ThomasAlg.hpp"

std::vector<float> ThomasAlg(const std::vector<float>& a, const std::vector<float>& b, const std::vector<float>& c, const std::vector<float>& d){
    std::vector<float> p, q;
    int n = b.size();
    p.push_back(-c[0]/b[0]);
    q.push_back(d[0]/b[0]);
    for (int i = 1; i < n-1; i++){
        p.push_back(-c[i]/(a[i-1]*p[i-1] + b[i]));
        q.push_back((d[i] - a[i-1]*q[i-1])/(a[i-1]*p[i-1] + b[i]));
    }
    std::vector<float> x;
    std::vector<float> xf;
    x.push_back((d[n-1] - a[n-2]*q[n-2])/(a[n-2]*p[n-2] + b[n-1]));
    for (int i = 1; i < n; i++){
        x.push_back(p[n-i-1]*x[i-1] + q[n-i-1]);
    }

    for (int i = 0; i < x.size(); i++){
        xf.push_back(x[x.size() - i - 1]);
    }
    return xf;
}   