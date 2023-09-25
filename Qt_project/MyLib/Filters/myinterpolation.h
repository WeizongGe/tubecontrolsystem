#ifndef MYINTERPOLATION_H
#define MYINTERPOLATION_H
#include<vector>
#include<cmath>
template<class T>
 class Interpolation
{
public:
    Interpolation(){}
    virtual ~Interpolation(){}
    virtual std::vector<double> CalcPara(std::vector<T> ini, std::vector<T> end, double t) = 0;
    virtual std::vector<double> CalcPara(T ini, T end, double t) = 0;
    virtual const T operator()(double t) = 0;
};


 template<class T>
 class CubicInter:public Interpolation<T>
 {
/// FILEDS:
 public:

 private:
     double a[4];
     double timeUpperBound;

 /// MEMBERFUNCTION:
 public:
     CubicInter():a{0}, timeUpperBound(0){};
     ~CubicInter(){};
     std::vector<double> CalcPara(std::vector<T> ini, std::vector<T> end, double t) override;
     std::vector<double> CalcPara(T ini, T end, double t) override;
     void setPara(std::vector<double> para);
     const T operator()(double t) override;

     CubicInter(const CubicInter& i) = delete;

 };

 /// InterPolation:

 /// Implementation:
template<class T>
std::vector<double> CubicInter<T>::CalcPara(std::vector<T> ini, std::vector<T> end, double t)
{
    // 未设置异常类型
    if(t < 1e-8) return std::vector(4, 0.0);
    a[0] = ini[0];
    a[1] = ini[1];
    a[2] =  3 * (end[0] - ini[0])/ std::pow(t, 2)  - 2 * ini[1] / t - end[1] / t;
    a[3] = -2 * (end[0] - ini[0])/ std::pow(t, 3) + (ini[1] + end[1]) / std::pow(t, 2);
    timeUpperBound = t;
    return std::vector{a[0], a[1], a[2], a[3]};
}

template<class T>
std::vector<double> CubicInter<T>::CalcPara(T ini, T end, double t)
{
    if(t < 1e-8) return std::vector(4, 0.0);
    a[0] = ini;
    a[1] = 0;
    a[2] = 3 * (end - ini) / std::pow(t, 2);
    a[3] =-2 * (end - ini) / std::pow(t, 3);
    timeUpperBound = t;
    return std::vector{a[0], a[1], a[2], a[3]};
}

template<class T>
void CubicInter<T>::setPara(std::vector<double> para)
{
    for(int i = 0; i < 4; ++i)
    {
        a[i] = para[i];
    }
}

template<class T>
const T CubicInter<T>::operator()(double t)
{
    return a[0] + a[1] * t + a[2] * std::pow(t, 2) + a[3] * std::pow(t, 3);
}
#endif // MYINTERPOLATION_H
