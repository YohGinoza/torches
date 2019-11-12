#include "SequenceKeeper.h"
#include <cstdlib>

SequenceKeeper::SequenceKeeper()
{
	this->m_Range = (rand() % 8) + 3;
	for (int i = 0; i < this->m_Range; i++) {
		m_Sequence.push_back('0');
	}
}

SequenceKeeper::SequenceKeeper(int range)
{
	this->m_Range = range;
}

SequenceKeeper::~SequenceKeeper()
{
}

std::vector<char> SequenceKeeper::GetSequence() const{
	return m_Sequence;
}

void SequenceKeeper::SetSequenceAt(int index, char data) {
	m_Sequence[index] = data;
}

int SequenceKeeper::GetRange() {
	return this->m_Range;
}