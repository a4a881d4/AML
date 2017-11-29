#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cassert>
using namespace std;
typedef double Float;
class vec{
public:
    Float x,y;
    vec(){}
    vec(Float _x,Float _y):x(_x),y(_y){}
    vec operator + (const vec &b) {return vec(x + b.x, y + b.y);}
    vec operator - (const vec &b) {return vec(x - b.x, y - b.y);}
    Float operator / (const vec &b) {return x * b.y - y * b.x;}
    Float operator * (const vec &b) {return x * b.x + y * b.y;}
    vec operator * (Float b){return vec(x*b,y*b);}
    vec operator / (Float b){return vec(x/b,y/b);}
    Float _sqrlen(void){return x*x+y*y;}
    Float _crossprd(const vec &b){return x*b.y-b.x*y;}
    friend ostream & operator << (ostream & os, const vec &ve) {
        cout << "(" << ve.x << ", " << ve.y << ")";
        return os;
    }
};

const Float _PI=acos(-1.0);
class angle{//[-PI,PI]
public:
    vec p;
    angle(){}
    angle(Float r){
        p=vec(cos(r),sin(r));
    }
    angle(Float _x,Float _y){
        p=vec(_x,_y);
    }
    angle operator + (Float d){
        //cos(a+b)=cos(a)cos(b)-sin(a)sin(b)
        //sin(a+b)=cos(a)sin(b)+sin(a)cos(b)
        return angle(p.x*cos(d)-p.y*sin(d),  p.x*sin(d)+p.y*cos(d));
    }
    angle operator - (Float d){
        //cos(a-b)=cos(a)cos(b)+sin(a)sin(b)
        //sin(a-b)=sin(a)cos(b)-cos(a)sin(b)
        return angle(p.x*cos(d)+p.y*sin(d), -p.x*sin(d)+p.y*cos(d));
    }
    angle operator * (Float d){
        Float r=atan2(p.y,p.x);
        return angle(r*d);
    }
    angle _approach(const angle &tgt,const angle &lw,const angle &hi){
        assert(p._crossprd(lw) * p._crossprd(hi) <= 0.0);
        //instead of approaching this angle to tgt, "approach" tgt to this angle
        vec2f ret1,ret2;//ret1: countercloskwise, ret2: clockwise
        if(p._crossprd(tgt)>=0){
            if(p._crossprd(lw)>=0&&lw._crossprd(tgt)>=0){
                ret1=lw;
                ret2=hi;
            }
            else if(p._crossprd(hi)>=0&&hi._crossprd(tgt)>=0){
                ret1=hi;
                ret2=lw;
            }
            else{
                return tgt;
            }
        }
        else{
            if(p._crossprd(lw)<=0&&lw._crossprd(tgt)<=0){
                ret1=lw;
                ret2=hi;
            }
            else if(p._crossprd(hi)<=0&&hi._crossprd(tgt)<=0){
                ret1=hi;
                ret2=lw;
            }
            else{
                return tgt;
            }
        }
        if(fabs(ret1._crossprd(tgt))<=fabs(ret2._crossprd(tgt))){
            return ret1;
        }
        else{
            return ret2;
        }
    }
};
