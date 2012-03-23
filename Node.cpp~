#include "Node.hpp"
#include <assert.h>
#include <map>
#include <string>
#include <utility>
#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include "Value.hpp"
#include "Token.hpp"
#include "Reflection.hpp"


//const deque<const Node *> *d_q;
using namespace std;



namespace cs540 {
struct node_to_use *start;
map<string,const Value*>link_list;
vector<const Value *> d_q;
namespace {
    
}



// Actual type: const IdentToken *id
// The node is just an expression.
AssignmentNode::AssignmentNode(const Token *id, const Node *e) {
this->p=e;
this->imp=id;


cout<< "IN AssignmentNode of node.cpp"<<"\n";
    // FILL IN.
}


const Value *
AssignmentNode::execute() const {
   const IdentToken *pq;
//static int prob;

cout<< "\nIN AssignmentNode exe  of node.cpp up"<<"\n";
pq=dynamic_cast<const IdentToken *>(this->imp);
map<string,const Value *>::iterator it;
link_list[pq->name_use]=p->execute();
/*
it=link_list.begin();
cout<<"in else \n";
if(link_list.find(pq->name_use)==link_list.end())
{
link_list[pq->name_use]=p->execute();
}
else
{
 cout<<"in last else \n";
 //it=link_list.find(pq->name_use);
 cout<< "IN AssignmentNode exe  of node.cpp done"<<"\n";
 //link_list.erase(it);
 link_list[pq->name_use]=p->execute();
}*/
   // struct node_to_use vm;
   // cout<< "IN AssignmentNode exe  of node.cpp"<<"\n";
    // FILL IN.
    //assert(false);
    
    return p->execute();
//}
}

// Actual type: const IdentToken *t
VarNode::VarNode(const Token *t) {
this->q=dynamic_cast<const IdentToken *>(t);
cout<<"*********"<<q->name_use<<"\n";
}

const Value *
VarNode::execute() const {
 map<string,const Value *>::iterator it;
it=link_list.begin();
//const Token *temp;
//cout<<"1 node.cpp\n";
it=link_list.find(q->name_use);
if(it==link_list.end())
{
 cout<<"error::Wrong i/p\n";
 assert(false);
 return 0;
} 
else
{
const Value *temp=link_list[q->name_use];
cout<<"::::::"<<q->name_use<<"\n";
return temp;
}
//    assert(false);
}

// Actual type: const IntegerToken *t
IntegerNode::IntegerNode(const Token *t) {
this->q=dynamic_cast<const IntegerToken *>(t);
this->val=new IntegerValue(q->val) ;
//cout<< "IN integerNode of node.cpp:"<<q->val<<"\n";
//this->execute();
}

const Value *
IntegerNode::execute() const {
//cout<< "IN integerNode exe of node.cpp"<<q->val<<"\n"<<this->val<<"\n";
   // assert(false);
    return this->val;
}

// Actual type: const StringToken *t
StringNode::StringNode(const Token *t) 
{
this->strq=dynamic_cast<const StringToken *>(t);
this->val=new StringValue(strq->val) ;



}

const Value *
StringNode::execute() const {
cout<<"2 node.cpp\n";
 //   assert(false);
    return this->val;
}

const Value *
AdditionNode::execute() const {
//cout<<"in addition\n";
const Value *tmp=first->execute();
const Value *tmp2=second->execute();
const Value *ret=tmp->addition(tmp2);
return(ret);
    //assert(false);
//    return 0;
}




// Actual type: const IdentToken *t
NewNode::NewNode(const Token *t) {
cout<<"in new node.cpp\n";
p=t;
this->q=dynamic_cast<const IdentToken *>(t);
Reflection *pq=new Reflection();
pq->Load("class_"+q->name_use +".so");
this->val=pq->New(q->name_use);

}

const Value *
NewNode::execute() const {
cout<<"*********"<<q->name_use<<"\n";
cout<<"In new exe node.cpp\n";

   // assert(false);
    return this->val;
}

// Node is some epression.
PrintNode::PrintNode(const Node *n) {
cout<<"In print"<<"\n";
p=n;
}

const Value *
PrintNode::execute() const {
   // assert(false);
const Value *printing = p->execute();
if(printing!=0)
printing->print();

cout<<"PPPPPPPPPPPPPP\n";
    return 0;
}

// Actual types: const IdentToken *obj, const IdentToken *method
// Each node in the deque is some expression.
InvocationNode::InvocationNode(const Token *obj, const Token *method, 
 const deque<const Node *> *al)
 {
  size_t i;
  cout<<"in deque\n";
  //d_q=al;
  this->p=dynamic_cast<const IdentToken *>(obj);
  this->q=dynamic_cast<const IdentToken *>(method);
  Reflection *pq=new Reflection();
  //this->first=obj;
  //this->second=method;
cout<<"in deque 122\n";
  const std::string name_use=q->name_use;
  const Node *temp;
  for(i=0;i<al->size();i++)
   {
    d_q.push_back((al->at(i))->execute());
   }
cout<<"in deque 124\n";
//this->p=dynamic_cast<const IdentToken *>(obj);
//Reflection *pq=new Reflection();
//pq->Load("class_"+p->name_use +".so");
pq->Invoke((ObjPtrValue *)link_list[p->name_use],name_use,d_q);
 }

const Value *
InvocationNode::execute() const {
//  pq->Invoke(link_list[p->name_use],q->name_use,d_q);
cout<<"3 node.cpp\n";
//    assert(false);

    return 0;
}



}
