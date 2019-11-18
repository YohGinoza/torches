#include "SequenceKeeper.h"
#include <cstdlib>

SequenceKeeper::SequenceKeeper()
{
	this->m_Range = (rand() % 8) + 3;
	for (int i = 0; i < this->m_Range; i++) {
		m_Sequence.push_back(0);
	}
}

SequenceKeeper::SequenceKeeper(int range)
{
	this->m_Range = range;
}

SequenceKeeper::~SequenceKeeper()
{
}

int SequenceKeeper::GetSequence(int index){
	return m_Sequence.at(index);
}

void SequenceKeeper::SetSequenceAt(int index, int data) {
	m_Sequence[index] = data;
}

int SequenceKeeper::GetRange() {
	return this->m_Range;
}