#pragma once

class CAutomatic
{
public:
	CAutomatic();
	~CAutomatic();
	void GetValuesInMiliFormat(ifstream& file);
	void GetValuesInMooreFormat(ifstream& file);
	void GetValuesFromFile(ifstream &file, Format format);
	vector<vector<size_t>> GetVerticalMatrix(vector <vector<size_t>> matrix);
	void GetVerticalMatrix();
	void ArrangeStates();
	void ArrangeStates(vector<vector<size_t>> &matrix);
	vector<vector<size_t>> VerticalToHorizontal(vector<vector<size_t>> matrix);
	vector <vector<size_t>> Compression(vector<vector<size_t>> matrix);
	void VerticalToHorizontal();
	void PrintMatrix(vector<vector<size_t>> matrix);
	void Minify();
private:
	vector <vector<size_t>> m_matrix;
	vector <vector<size_t>> m_verticalMatrix;
	vector <vector<size_t>> m_arrangedMatrix;
	vector <vector<size_t>> m_miliStates;
	Format m_format;
	
};

