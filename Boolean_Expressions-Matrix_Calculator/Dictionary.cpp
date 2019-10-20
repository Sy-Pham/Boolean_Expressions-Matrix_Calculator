#include "Dictionary.h"

//default constructor
template <class k, class v>
Dictionary<k, v>::Dictionary()
{
}

//destructor 
template <class k, class v>
Dictionary<k, v>::~Dictionary() {
	value.clear();
}

//constructor
template <class k, class v>
Dictionary<k, v>::Dictionary(k key, v value) {
	this->key = key;
	this->value.push_back(value);

}

//adding string into value
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
// overloading operator <
template <class k, class v>
bool  Dictionary<k, v>::operator<(const Dictionary& other) {
	return key < other.key ? 1 : 0;
}