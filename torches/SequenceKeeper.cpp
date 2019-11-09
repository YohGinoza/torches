#include "SequenceKeeper.h"
#include <cstdlib>

template <class T>
SequenceKeeper<T>::SequenceKeeper()
{
	this->m_Range = (rand() % 8) + 3;
}

template <class T>
SequenceKeeper<T>::SequenceKeeper(int range)
{
	this->m_Range = range;
}

template <class T>
SequenceKeeper<T>::~SequenceKeeper()
{
}

template <class T>
std::vector<T>& SequenceKeeper<T>::GetSequence() const{
	return m_Sequence;
}

template <class T>
void SequenceKeeper<T>::SetSequenceAt(int index, T data) {
	m_Sequence[index] = data;
}

template <class T>
int SequenceKeeper<T>::GetRange() {
	return this->m_Range;
}