#ifndef CS540_META_INFO_HPP
#define CS540_META_INFO_HPP



#include <string>
#include <vector>
#include "Value.hpp"


namespace cs540 {



class MetaInfo {
    public:
        virtual ~MetaInfo() {}
        virtual std::string className() const = 0;
	virtual const ObjPtrValue *create(const std::string &type_name)const = 0;
	virtual const Value *invoke(const ObjPtrValue *, const std::string &method_name, const std::vector<const Value *> &args)const=0;
};

class MetaInfoRegisterer {
    public:
        MetaInfoRegisterer(const MetaInfo *);
};



}



#endif
