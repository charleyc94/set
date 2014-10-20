#include "stdafx.h"
#include <iostream>
#include "set.h"
#include "node.h"
//#include "hashtable.h"
#include <string>
#include <ctype.h>
#include "iterator.h"
using namespace::std;

using std::string;

template <class T>
Iterator<T>& Iterator<T>::operator++()
{
	counter++;
    current++;
    return *this;
}

template <class T>
Iterator<T>& Iterator<T>::operator ++(int)
{
	Iterator<T> temp(current, counter);
	counter++;
	current++;
	return temp;
}

template <class T>
bool Iterator<T>::operator==(const Iterator<T>& right_side)
{
	return(this->current==right_side.current);
}
	  
template <class T>
bool Iterator<T>::operator!=(const Iterator<T>& right_side)
{
	return(this->current!=right_side.current);
}

template <class T>
Node<T>* Iterator<T>::operator*()
{
	return current[0];
}



namespace charley
{
   template <class T>
   void headInsert(Node<T>*& head, const T& theData)
   {
	
       head = new Node<T>(theData, head);
   }

   template <class T>
   void insert(Node<T>* afterMe, const T& theData)
   {
       afterMe->setLink( new Node<T>(theData, afterMe->getLink( )));
   }

   template <class T>
   Node<T>* search(Node<T>* head, const T& target)
   {
      Node<T>* here = head;
      if (here == NULL)
      {
         return NULL;
      }
      else
      {
          while (here->getData( ) != target && here->getLink( ) != NULL)
                 here = here->getLink( );
          if (here->getData( ) == target)
              return here;
          else
              return NULL;
      }
    }
}



using charley::headInsert;
using charley::search;

/*template <class T>
int operator % (string s, T size)
{
	int result=0;
	for(size_t i=0; i<s.length(); i++)
	{
		result= result*80 + s[i];
	}
	
	return result % size;
}*/


template <class T>
Set<T>& Set<T>::operator=(const Set<T>& other)
{
	Node<T>* temp;
	if(&other==this)
		return *this;
	for(int i=0; i<array_size; i++)
	{
		delete hash_array[i];
	}
	delete [] hash_array;
	array_size=other.array_size;
	hash_array= new Node<T>* [array_size];
	for(int j=0; j<array_size; j++)
	{
		hash_array[j]=NULL;
	}
	for(int i=0; i<other.array_size; i++)
	{
		temp=other.hash_array[i];
		while(temp!=NULL)
		{
			this->add(temp->getData());
			temp=temp->getLink();
		}
	}
	return *this;
}


template <class T>
Set<T>::Set(const Set<T>& other)
{
	Node<T>* temp;
	array_size=other.array_size;
	hash_array= new Node<T>* [array_size];
	for(int j=0; j<array_size; j++)
	{
		hash_array[j]=NULL;
	}
	for(int i=0; i<other.array_size; i++)
	{   
		temp=other.hash_array[i];
		while(temp!=NULL)
		{
			this->add(temp->getData());
			temp=temp->getLink();
		}
	}
}

template <class T>
int Set<T>::size()
{
	return items;
}

template <class T>
int Set<T>::compute(T item) const
{
//	cout<<"item "<<item<<" array_size "<<array_size<<endl;
//	cout<<"this is key "<<item % array_size<<endl;
	double cut_off=item;
	int hold=item;
	cut_off-=hold;
	int num=cut_off*100;
	hold+=num;
	int i=hold % array_size;
	int j=(i-3) % 2;
	if(hold<array_size)
		return hold % array_size;
	else
		return (hold+j) % array_size;


}

int Set<string>::compute(string item) const
{
	int result=0;
	for(size_t i=0; i<item.length(); i++)
	{
		result= result*(19)+(item[i]-'0');  
	}
	if(result<0)
	{
		result*=-1;
	}
	return result % array_size;
}

/*int Set<char*>::compute(char* item)
{
	int result=0;
	for(size_t i=0; item[i]!='/0'; i++)
	{
		result= result*80 + item[i];
	}

	return result % array_size;
}*/

template <class T>
void Set<T>::add(T item)
{
	if(!contains(item) && array_size!=0)
	{
		//cout<<"it's late"<<endl;
	//	Node<T>** other_ptr=hash_array;
		//other_ptr+=compute(item);
		//headInsert(*other_ptr, item);
		//cout<<(*other_ptr)->getData()<<endl;
		headInsert(hash_array[compute(item)], item);
		this->items++;
		//cout<<(*other_ptr)->getLink()<<endl;
		
	}
	if(array_size==0)
	{
		array_size=100;
		array_size=2*compute(item)+1;
	    hash_array= new Node<T>*[array_size];
		Node<T>** ptr=hash_array;
		for(int i=0; i<array_size; i++)
	    {
			ptr=hash_array+i;
		    *ptr=NULL;
	    }
		Node<T>** other=hash_array;
		other+=compute(item);
		headInsert(*other, item);
		this->items++;
	}
}

template <class T>
Set<T>::Set(int num)
{
	items=0;
	array_size=num;
	hash_array= new Node<T>*[num];
	/*Node<T>** ptr=hash_array;
	for(int i=0; i<array_size; i++)
	{
		ptr+=i;
		*ptr=NULL;
		cout<<*(hash_array+i)<<endl;
	}*/
	for(int i=0; i<array_size; i++)
	{
		hash_array[i]=NULL;
	}
}

template <class T>
bool Set<T>::contains(T target) const
{
	/*
	for(int k=0; k<array_size; k++)
	{
		if(search(hash_array[k], target)!=NULL)
			return true;
	}
	return false;*/
	if(array_size==0)
	{
	    return false;
	}
	else
	{
		int index=compute(target);
		if(search(hash_array[index],target)!=NULL)
			return true;
		else
			return false;
	}

}

template <class T>
Set<T>::~Set()
{
	Node<T>** ptr=hash_array;
	Node<T>* node_ptr=*ptr;
	Node<T>* to_delete;
	for(int i=0; i<array_size; i++)
	{
		ptr=hash_array+i;
		node_ptr=*ptr;
		to_delete=node_ptr;
		while(node_ptr!=NULL)
		{
			node_ptr=node_ptr->getLink();
			delete to_delete;
			to_delete=node_ptr;
		}
	}

	delete [] hash_array;
}


template <class T>
Set<T>* Set<T>::setIntersection(const Set<T>& otherSet)
{
	Node<T>** current=hash_array;
	Node<T>* node_ptr=*current;
	int i=array_size + otherSet.array_size;
	Set<T>* temp;
	temp= new Set<T>(i);
	for(int k=0; k<array_size; k++)
	{
		current=hash_array+k;
		node_ptr=*current;
		if((*current)==NULL)
			continue;
		while(node_ptr!=NULL)
		{
			if(otherSet.contains(node_ptr->getData()))
		    {
				temp->add(node_ptr->getData());
		    }
			node_ptr=node_ptr->getLink();
		}
	}
	return temp;

}

template <class T>
Set<T>* Set<T>::setUnion(const Set<T>& otherSet)
{
	Node<T>** current;
	Node<T>** node_ptr;
	Node<T>* ptr;
	Set<T>* temp;
	temp= new Set<T>(array_size + otherSet.array_size);
	for(int k=0; k<array_size; k++)
	{
		current=hash_array+k;
		ptr=*current;
		while(ptr!=NULL)
	    {
			if(ptr!=NULL)
		    {
			    temp->add(ptr->getData());
		    }
			ptr=ptr->getLink();
		}
	}
	for(int k=0; k<otherSet.array_size; k++)
	{
		node_ptr=(otherSet.hash_array)+k;
		ptr=*node_ptr;
	    while(ptr!=NULL)
		{
			if(ptr!=NULL)
		    {
			    temp->add(ptr->getData());
			}
			ptr=ptr->getLink();
		}
	}
	return temp;

}


template <class T>
void Set<T>::output()
{
	Node<T>** current=hash_array;
	Node<T>* node_ptr=*current;
	for(int k=0; k<array_size; k++)
	{	
		//Node<T>** current=hash_array+k;
		 current=hash_array+k;
		 node_ptr=*current;
		while(node_ptr!=NULL)
		{
			cout<<(node_ptr->getData())<<" "<<k;
			cout<<endl;
			node_ptr=node_ptr->getLink();
		}
	}
}





int main()
{
	Set<int> obj(10);
   // Set<int> obj;
	
	obj.add(1);
	obj.add(2);
	obj.add(3);
	obj.add(4);
	obj.add(12);
	obj.add(17);

	cout<<"Size of obj "<<obj.size()<<endl;
	cout<<boolalpha<<obj.contains(5)<<endl;
	cout<<boolalpha<<obj.contains(17)<<endl;
	obj.output();
	cout<<endl;
	
	Set<int> obj_2;
	obj_2.add(12);
	cout<<boolalpha<<obj_2.contains(12)<<endl;
	obj_2.add(23);
	obj_2.add(26);
	obj_2.add(1);
	obj_2.add(14345);
	obj_2.add(12234);
	cout<<boolalpha<<obj_2.contains(26)<<endl;
	obj_2.output();

	cout<<endl;
	cout<<"Size of obj 2 "<<obj_2.size()<<endl;
	Set<int>* obj_ptr;
	obj_ptr=obj.setIntersection(obj_2);
	obj_ptr->output();

	cout<<endl;

	Set<int>* ptr;
	obj_2.output();
	cout<<endl;
	obj_2.output();
	ptr=obj.setUnion(obj_2);
	cout<<endl;
	ptr->output();
	
	cout<<endl;
	Set<float> j(13);
	j.add(3.55f);
	j.add(4.56f);
	j.add(4.7f);
	j.add(9.92f);
	j.add(9.39f);
	j.add(9.59f);
	j.add(9.89f);
	cout<<boolalpha<<j.contains(4.56f)<<endl;
	j.output();

	Set<string> i(13);
	i.add("hello");
	i.add("yeee");
	i.add("yolo");
    i.add("apple");
	i.add("elppa");
	i.add("olleh");
	i.add("THIS Isgoa dsss Keeyyss");
	cout<<boolalpha<<i.contains("yeee")<<endl;
	i.output();
	cout<<endl;

	Set<int>::iterator itr;
	Node<int>* p;

	for(itr=obj.begin(); itr!=obj.end(); ++itr)
	{
		p=*itr;
		while(p!=NULL)
		{
			cout<<(p->getData())<<endl;
			p=p->getLink();
		}
	}

	/*Set<char*> c(4);
	c.add("helloo");
	c.add("little");
	c.output();*/

	cout<<"testing copy constructor and assignment operator"<<endl;
	Set<int> jonathan(obj);
	jonathan.output();
	cout<<endl;
	Set<int> coolKid;
	coolKid=jonathan;
	coolKid.output();

}
