#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>
using namespace std;

template<typename T>
class immutable_queue
{
public:
	immutable_queue();//defalut constructor 
	~immutable_queue();
	immutable_queue(const vector<T> &ini_vector);//constructor with parameter
	immutable_queue(const immutable_queue<T> &other_queue);//copy constructor
	immutable_queue<T> &operator=(const immutable_queue<T> &str_queue);//overload operator =	
	immutable_queue<T> operator+(const immutable_queue<T> &add_queue);
	immutable_queue<T> mergeTwoImmutableQueue(const immutable_queue<T> &another_queue);
	immutable_queue<T> enqueue(T &element);
	immutable_queue<T> dequeue();
	T peek();
	int size();
	void display();
private:
	int queue_size;	
	vector<T> queue_elements;
};

template<typename T>
immutable_queue<T>::immutable_queue()
{
	queue_size=0;
}

template<typename T>
immutable_queue<T>::~immutable_queue()
{
	queue_elements.clear();
}


template<typename T>
immutable_queue<T>::immutable_queue(const vector<T> &ini_vector)
{
	int index,vec_size=ini_vector.size();
	for(index=0;index<vec_size;index++)
	{
		queue_elements.push_back(ini_vector[index]);
	}
	queue_size=vec_size;
}

template<typename T>
immutable_queue<T>::immutable_queue(const immutable_queue<T> &other_queue)
{
	queue_size=other_queue.queue_size;
	queue_elements.clear();
	int index;
	for(index=0;index<other_queue.queue_size;index++)
	{
		queue_elements.push_back(other_queue.queue_elements[index]);
	}
}

template<typename T>
immutable_queue<T> &immutable_queue<T>::operator=(const immutable_queue<T> &str_queue)
{
	if(this==&str_queue)
		return *this;
	queue_size=str_queue.queue_size;
	queue_elements.clear();
	int index;
	for(index=0;index<str_queue.queue_size;index++)
	{
		queue_elements.push_back(str_queue.queue_elements[index]);
	}
	return *this;
}

template<typename T>
immutable_queue<T>  immutable_queue<T>::operator+(const immutable_queue<T> &add_queue)
{
	vector<T> temp;
	int index;
	for(index=0;index<queue_size;index++)
	{
		temp.push_back(queue_elements[index]);
	}
	for(index=0;index<add_queue.queue_size;index++)
	{
		temp.push_back(add_queue.queue_elements[index]);
	}
	immutable_queue<T> result(temp);
	return result;
}

template<typename T>
immutable_queue<T> immutable_queue<T>::mergeTwoImmutableQueue(const immutable_queue<T> &another_queue)
{
	immutable_queue<T> result(*this);
	immutable_queue<T> temp(another_queue);
	int index;
	T element;
	for(index=0;index<another_queue.queue_size;index++)
	{
		element=temp.peek();
		result=result.enqueue(element);
		temp=temp.dequeue();
	}
	return result;
}

template<typename T>
immutable_queue<T>  immutable_queue<T>::enqueue(T &element)
{  
	if(NULL==&element)
	{		   
		throw invalid_argument("invalid_argument");
	}
	vector<T> temp;
	int index;		
	for(index=0;index<queue_size;index++)
	{
		temp.push_back(queue_elements[index]);
	}
	temp.push_back(element);
	immutable_queue<T> new_enqueue(temp);
	return new_enqueue;
}


template<typename T>
immutable_queue<T>  immutable_queue<T>::dequeue()
{
	if(0==queue_size)
	{		  
	   throw  range_error("range_error");
	}	    	
	vector<T> temp;
	int i;
	for(i=1;i<queue_size;i++)
	{
		temp.push_back(queue_elements[i]);
	}
	immutable_queue<T> new_dequeue(temp);
	return new_dequeue;
}

template<typename T>
T  immutable_queue<T>::peek()
{
	if(0==queue_size)
	{
	 throw range_error("range_error");
	 }
	return queue_elements[0];
}

template<typename T>
int  immutable_queue<T>::size()
{
	return queue_size;
}

template<typename T>
void  immutable_queue<T>::display()
{
	cout<<"size="<<queue_size<<endl;
	for(int i=0;i<queue_size;i++)
	   cout<<queue_elements[i]<<"  ";
	cout<<endl;
}

int main()
{ 
   typedef int T;
   vector<T> a,b;
   a.push_back(1);
   a.push_back(2);
   a.push_back(3);
   b.push_back(5);	
   b.push_back(6);
   immutable_queue<T> queue1(a);
   immutable_queue<T> queue2(b),queue3=queue1,queue4(queue2);
   queue1.display();
   queue2.display();
   queue3.display();
   queue4.display();
   return 0;
}


