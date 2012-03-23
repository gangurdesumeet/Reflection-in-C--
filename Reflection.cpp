#include "Reflection.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <iostream>
#include "Value.hpp"
#include "MetaInfo.hpp"
//#include "A.hpp"

using namespace std;



class AA {
    public:
        int f() { return 1234; }
};

namespace cs540 {
void *xy;


template <typename T>
class ObjPtrValue_tmpl : public ObjPtrValue {
    public:
        ObjPtrValue_tmpl(T *t) : m_obj(t) {}
        virtual void print() const;
    private:
        T *const m_obj;
};

template <typename T>
void
ObjPtrValue_tmpl<T>::print() const {
    cout << m_obj << endl;
}



void
Reflection::Load(const string &so_file) {
    void *h = dlopen(("./" + so_file).c_str(), RTLD_LAZY|RTLD_GLOBAL);
    if (h == 0) {
        cerr << dlerror() << endl;
        abort();
    }
  this->ret=h;
  xy=h;
cout<<this->ret<<"1-------------\n";
}

const ObjPtrValue *
Reflection::New(const string &type_name) {
    cout << "Instantiation of type " << type_name << " requested." << endl;
    cout << "CHANGE THIS: " << " currently hard-code to type AA." << endl;
    const ObjPtrValue *pr;
    //char ptr1[50];// = type_name+"_meta";
    //strcpy(ptr1,type_name); 
cout<<this->ret<<"-------------\n";
    void *prj=dlsym(this->ret,"base");
    const MetaInfo *qw = *(MetaInfo  **)prj;
    //const A_meta *qw=new A_meta();
    cout<<prj<<"---adasdasdadas---"<<qw<<"\n";
    return(pr=qw->create(type_name));
    //return new ObjPtrValue_tmpl<AA>(new AA);
}

const Value *
Reflection::Invoke(const ObjPtrValue *obj, const string &method_name,
 const vector<const Value *> &args) {
    printf("Invoke:\n");
const Value *pr;
  //char ptr1[50];// = type_name+"_meta";
    //strcpy(ptr1,type_name); 
    cout<<xy<<"-------------\n";
    void *prj=dlsym(xy,"base");
    const MetaInfo *qw = *(MetaInfo  **)prj;
    pr= qw->invoke(obj,method_name,args);
    cout << "123456:::::"<<pr<<";;;;;;;;;;;;"<<typeid(*obj).name() << endl;
    cout << method_name << endl;
    for (size_t i = 0; i < args.size(); i++) {
        args[i]->print();
    }

    return pr;
}



}
