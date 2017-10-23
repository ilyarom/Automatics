#include "stdafx.h"
#include "Automatic.h"



CAutomatic::CAutomatic()
{
}


CAutomatic::~CAutomatic()
{
}

void CAutomatic::GetValuesInMooreFormat(ifstream& file) {
	string line;
	string resultStr = "";
	vector<size_t> S;
	while (getline(file, line)) {
		for (size_t i = 0; i < line.size(); ++i) {
			if (line[i] == ' ') {
				S.push_back(atoi(resultStr.c_str()));
				resultStr = "";
			}
			else {
				resultStr += line[i];
			}
			if (i == line.size() - 1) {
				S.push_back(atoi(resultStr.c_str()));
				resultStr = "";
			}
		}
		m_matrix.push_back(S);
		S.clear();
	}
}

vector<vector<size_t>> CAutomatic::GetVerticalMatrix(vector<vector<size_t>> matrix) {
	vector<size_t> column;
	vector<vector<size_t>> verticalMatrix;
	for (size_t i = 0; i < matrix[0].size(); ++i) {
		for (size_t j = 0; j < matrix.size(); ++j) {
			column.push_back(matrix[j][i]);
		}
		verticalMatrix.push_back(column);
		column.clear();
	}
	return verticalMatrix;
}

void CAutomatic::GetValuesInMiliFormat(ifstream& file) {
	string line;
	string resultStr = "";
	vector<size_t> S;
	vector <vector<size_t>> outputStates;
	vector<size_t> lineStates;
	getline(file, line);
	for (size_t i = 0; i < line.size(); ++i) {
		if (line[i] == ' ') {
			S.push_back(atoi(resultStr.c_str()));
			resultStr = "";
		}
		else {
			resultStr += line[i];
		}
		if (i == line.size() - 1) {
			S.push_back(atoi(resultStr.c_str()));
			resultStr = "";
		}
	}
	m_matrix.push_back(S);
	m_matrix.push_back(S);
	S.clear();
	while (getline(file, line)) {
		for (size_t i = 0; i < line.size(); ++i) {
			if (line[i] == ' ') {
				lineStates.push_back(atoi(resultStr.c_str()));
				resultStr = "";
			}
			else if (line[i] == '/') {
				S.push_back(atoi(resultStr.c_str()));
				resultStr = "";
			}
			else {
				resultStr += line[i];
			}
			if (i == line.size() - 1) {
				lineStates.push_back(atoi(resultStr.c_str()));
				resultStr = "";
			}
		}

		m_matrix.push_back(S);
		S.clear();
		outputStates.push_back(lineStates);
		lineStates.clear();
	}
	m_miliStates = outputStates;
	outputStates = GetVerticalMatrix(outputStates);
	vector <size_t> classes(outputStates.size());
	for (size_t i = 0; i < outputStates.size(); ++i) {
		vector<vector<size_t>>::iterator it = find(outputStates.begin(), outputStates.end(), outputStates[i]);
		classes[i] = it - outputStates.begin();
	}
	m_matrix[0] = classes;
}

void CAutomatic::GetValuesFromFile(ifstream& file, Format format) {
	m_format = format;
	if (format == Format::Moore) {
		GetValuesInMooreFormat(file);
	}
	else if (format == Format::Mili) {
		GetValuesInMiliFormat(file);
	}
}	


void CAutomatic::GetVerticalMatrix() {
	vector<size_t> column;
	for (size_t i = 0; i < m_matrix[0].size(); ++i) {
		for (size_t j = 0; j < m_matrix.size(); ++j) {
			column.push_back(m_matrix[j][i]);
		}
		m_verticalMatrix.push_back(column);
		column.clear();
	}
}

bool LessState(vector<size_t> lhs, vector <size_t> rhs) {
	return lhs[0] < rhs[0];
}

void CAutomatic::ArrangeStates() {
	sort(m_verticalMatrix.begin(), m_verticalMatrix.end(), LessState);
}

void CAutomatic::ArrangeStates(vector<vector<size_t>> &matrix) {
	sort(matrix.begin(), matrix.end(), LessState);
}

void CAutomatic::VerticalToHorizontal() {
	vector<size_t> line;
	m_arrangedMatrix.clear();
	for (size_t i = 0; i < m_verticalMatrix[0].size(); ++i) {
		for (size_t j = 0; j < m_verticalMatrix.size(); ++j) {
			line.push_back(m_verticalMatrix[j][i]);
		}
		m_arrangedMatrix.push_back(line);
		line.clear();
	}
}

vector<vector<size_t>> CAutomatic::VerticalToHorizontal(vector<vector<size_t>> matrix) {
	vector<size_t> line;
	vector<vector<size_t>> result;
	for (size_t i = 0; i < matrix[0].size(); ++i) {
		for (size_t j = 0; j < matrix.size(); ++j) {
			line.push_back(matrix[j][i]);
		}
		result.push_back(line);
		line.clear();
	}
	return result;
}

bool isLessMatrix(vector <size_t> lhs, vector <size_t> rhs) {
	for (size_t i = 0; i < lhs.size(); ++i) {
		if (i == 1) {
			continue;
		}
		if (lhs[i] == rhs[i]) {
			continue;
		}
		return lhs[i] < rhs[i];
	}
	return lhs[lhs.size() - 1] < rhs[rhs.size() - 1];
}

bool isEqualColumns(vector <size_t> lhs, vector <size_t> rhs) {
	for (size_t i = 2; i < lhs.size(); ++i) {
		if (i == 1) {
			continue;
		}
		if (lhs[i] == rhs[i]) {
			continue;
		}
		return false;
	}
	return true;
}

vector <vector<size_t>> CAutomatic::Compression(vector<vector<size_t>> matrix) {
	vector <vector<size_t>> result;
	bool compressed = false;
	for (size_t i = 0; i < matrix.size() - 1; ++i) {
		if (matrix[i][0] == matrix[i + 1][0]) {
			continue;
		}
		else {
			result.push_back(matrix[i]);
		}
	}
	result.push_back(matrix[matrix.size() - 1]);
	return result;
}

void CAutomatic::Minify() {
	GetVerticalMatrix();
	ArrangeStates();
	VerticalToHorizontal();
	vector <vector<size_t>> prevMatrix(0);
	vector <vector<size_t>> currMatrix = m_arrangedMatrix;
	PrintMatrix(currMatrix);
	cout << "========================\n";
	while (prevMatrix != currMatrix) {
		prevMatrix = currMatrix;
		for (size_t i = 2; i < currMatrix.size(); ++i) {
			for (size_t j = 0; j < currMatrix[0].size(); ++j) {
				vector<size_t>::iterator it = find(prevMatrix[1].begin(), prevMatrix[1].end(), m_arrangedMatrix[i][j]);
				size_t pos = it - prevMatrix[1].begin();
				currMatrix[i][j] = prevMatrix[0][pos];
			}
		}
		vector <vector<size_t>> verticalMatrix;
		verticalMatrix = GetVerticalMatrix(currMatrix);
		sort(verticalMatrix.begin(), verticalMatrix.end(), isLessMatrix);
		size_t currSet = 0;
		verticalMatrix[0][0] = currSet;
		for (size_t i = 0; i < verticalMatrix.size() - 1; ++i) {
			if (!isEqualColumns(verticalMatrix[i], verticalMatrix[i + 1])) {
				++currSet;
			}
			verticalMatrix[i + 1][0] = currSet;
		}
		ArrangeStates(verticalMatrix);
		currMatrix = VerticalToHorizontal(verticalMatrix);
		PrintMatrix(currMatrix);
		cout << "========================\n";
	}
	vector <vector<size_t>> verticalMatrix = GetVerticalMatrix(currMatrix);
	PrintMatrix(VerticalToHorizontal(Compression(verticalMatrix)));
}



void CAutomatic::PrintMatrix(vector<vector<size_t>> matrix) {
	for (size_t i = 0; i < matrix.size(); ++i) {
		if (i == 1)
			continue;
		else if (i == 0)
			cout << "   ";
		else {
			cout << ((m_format == Format::Moore) ? "x" : "z") << i - 2 << " ";
		}
		for (size_t j = 0; j < matrix[i].size(); ++j) {
			if (i == 0) {
				cout << ((m_format == Format::Moore) ? "y" : "S");
			}
			else {
				cout << ((m_format == Format::Moore) ? "a" : "s");
			}
			if (m_format == Format::Moore) {
				cout << matrix[i][j] << ' ';
			}
			else if (m_format == Format::Mili) {
				cout << matrix[i][j];
				if (i != 0) {
					vector<size_t>::iterator it = find(m_arrangedMatrix[1].begin(), m_arrangedMatrix[1].end(), matrix[1][j]);
					size_t pos = it - m_arrangedMatrix[1].begin();
					cout << '|' << m_miliStates[i - 2][matrix[1][j] - 1] ;
				}
				cout << ' ';
			}
			if (i == 0) {
				cout << "  ";
			}
		}
		cout << "\n";
	}
}
