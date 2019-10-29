#include "Dictionary.h"

//usage: default constructor
template <class k, class v>
Dictionary<k, v>::Dictionary()
{
}

//usage: destructor 
template <class k, class v>
Dictionary<k, v>::~Dictionary() {
	value.clear();
}

//usage: constructor
template <class k, class v>
Dictionary<k, v>::Dictionary(k key, v value) {
	this->key = key;
	this->value.push_back(value);

}

//input: v value
//output: Dictionary<k, v>&
//usage: adding string into value
template <class k, class v>
Dictionary<k, v>& Dictionary<k, v>::append(v value) {
	int count = 0;
	for (int i = 0; i < this->value.size(); i++)
	{
		if (this->value[i] == value) count++;
		if (count)
			break;
	}
	if (!count)
		this->value.push_back(value);

	return *this;
}

//input: const Dictionary& other
//output: bool
// overloading operator <
template <class k, class v>
bool  Dictionary<k, v>::operator<(const Dictionary& other) {
	return key < other.key ? 1 : 0;
}