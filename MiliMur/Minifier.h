#pragma once
class Minifier
{
public:
	Minifier(vector<vector<size_t>> inputMatrix, vector<vector<size_t>> currMatrix);
	vector<vector<size_t>> GetResultMatrix();
	~Minifier();
private: 
	vector<vector<size_t>> m_inputMatrix;
	vector<vector<size_t>> m_prevMatrix;
	vector<vector<size_t>> m_currMatrix;
};
