// Douglas_Peucker.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <math.h>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;

struct Dot
{
	double m_x;
	double m_y;
	double m_z;

	Dot(double dX = 0., double dY = 0., double dZ = 0.)
	{
		m_x = dX;
		m_y = dY;
		m_z = dZ;
	};
};

double PerpDist(Dot dotSrc, Dot dotStart, Dot dotEnd);
vector<Dot> DouglasPeucker(const vector<Dot> &vecPoints, double dEpsilon = 0.003);
vector<Dot> ReadPoints(string strPath);
void WritePoints(string strPath, vector<Dot> vecPoints);

int main()
{
	vector<Dot> vecPoints = ReadPoints("D:\\Allen\\Data\\txt\\Contour.txt");
	vector<Dot> vecDP = DouglasPeucker(vecPoints);
	WritePoints("D:\\Allen\\Data\\txt\\Contour_DP.txt", vecDP);

	system("pause");
	return 0;
}

double PerpDist(Dot dotSrc, Dot dotStart, Dot dotEnd)
{
	double dA, dB, dC;
	if (fabs(dotStart.m_x - dotEnd.m_x) < 1.e-7)
	{
		dA = 0.;
		dB = 1.;
		dC = -dotStart.m_y;
	}
	else
	{
		dA = (dotStart.m_y - dotEnd.m_y) / (dotStart.m_x - dotEnd.m_x);
		dB = -1.;
		dC = -dA * dotStart.m_x + dotStart.m_y;
	}

	double dTmp = dA * dotSrc.m_x + dB * dotSrc.m_y + dC;
	return dTmp * dTmp / (dA * dA + dB * dB);
}

vector<Dot> DouglasPeucker(const vector<Dot> &vecPoints, double dEpsilon)
{
	double dMax = 0.;
	int iIndex = 0;
	int iSize = (int)vecPoints.size();
	for (int i = 1; i < iSize - 1; i++)
	{
		double dTmp = PerpDist(vecPoints[i], vecPoints[0], vecPoints[iSize - 1]);
		if (dTmp > dMax)
		{
			iIndex = i;
			dMax = dTmp;
		}
	}

	vector<Dot> vecRet;
	if (dMax > dEpsilon * dEpsilon)
	{
		vector<Dot> vecDiv1(vecPoints.begin(), vecPoints.begin() + iIndex + 1);
		vector<Dot> vecDiv2(vecPoints.begin() + iIndex, vecPoints.end());

		vector<Dot> vecRes1 = DouglasPeucker(vecDiv1, dEpsilon);
		vector<Dot> vecRes2 = DouglasPeucker(vecDiv2, dEpsilon);

		vecRet.insert(vecRet.end(), vecRes1.begin(), vecRes1.end() - 1);
		vecRet.insert(vecRet.end(), vecRes2.begin(), vecRes2.end());
	}
	else
	{
		vecRet.resize(2);
		vecRet[0] = vecPoints[0];
		vecRet[1] = vecPoints[iSize - 1];
	}

	return vecRet;
}

vector<Dot> ReadPoints(string strPath)
{
	ifstream fin;
	fin.open(strPath, ios::in);

	vector<Dot> vecPoints;
	double dX, dY, dZ = 0.;
	char ch;
	//Ignore Z
	//while (fin >> dX >> ch >> dY >> ch >> dZ)
	while (fin >> dX >> ch >> dY)
	//Ignore Z
		vecPoints.push_back(Dot(dX, dY, dZ));

	fin.close();

	return vecPoints;
}

void WritePoints(string strPath, vector<Dot> vecPoints)
{
	ofstream fout;
	fout.open(strPath, ios::out);

	for (int i = 0; i < (int)vecPoints.size(); i++)
		//Ignore Z
		//fout << vecPoints[i].m_x << "," << vecPoints[i].m_y << "," << vecPoints[i].m_z << endl;
		fout << vecPoints[i].m_x << "," << vecPoints[i].m_y << endl;
		//Ignore Z

	fout.close();
}
