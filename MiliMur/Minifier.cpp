#include "stdafx.h"
#include "Minifier.h"


Minifier::Minifier(vector<vector<size_t>> inputMatrix, vector<vector<size_t>> currMatrix)
{
	m_inputMatrix = inputMatrix;
	m_prevMatrix = currMatrix;
}

vector<vector<size_t>> Minifier::GetResultMatrix() {
	while (m_prevMatrix != m_currMatrix) {
		m_currMatrix = m_prevMatrix;
		for (size_t i = 2; i < m_currMatrix.size(); ++i) {
			for (size_t j = 0; j < m_currMatrix[0].size(); ++j) {
				size_t pos = *find(m_currMatrix[1].begin(), m_currMatrix[1].end(), m_inputMatrix[i][j]);
				m_currMatrix[i][j] = m_prevMatrix[0][pos];
			}
		}

	}
	return m_currMatrix;
}


Minifier::~Minifier()
{
}
