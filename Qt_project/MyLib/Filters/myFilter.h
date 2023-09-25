#ifndef FILTER_H
#define FILTER_H

template<class T>
class Filter
{
public:
    Filter(){}
    virtual ~Filter(){}
    virtual T operator()(const T & i1, const T & i2) = 0;
};

template<class F>
class lowPassFilter: public Filter<F>
{
public:
    explicit lowPassFilter(const double a = 1):alpha(a){}
    ~lowPassFilter(){}
    F operator()(const F &a, const F& b) {return alpha * a + (1 - alpha) * b;}
    void setAlpha(double i){alpha =i;}
private:
    double alpha;
};

#endif // FILTER_H
