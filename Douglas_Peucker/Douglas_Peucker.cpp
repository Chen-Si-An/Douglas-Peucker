// Douglas_Peucker.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <Windows.h>
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
vector<Dot> DouglasPeucker(const vector<Dot> &vecPoints, double dEpsilon);
vector<Dot> ReadPoints(const wstring &strPath);
void WritePoints(const wstring &strPath, vector<Dot> vecPoints);

int main()
{
	TCHAR chBuf[MAX_PATH];
	GetModuleFileNameW(NULL, chBuf, MAX_PATH);
	wstring strPath(chBuf);
	size_t iPos = strPath.find_last_of(L"\\/");
	strPath = strPath.substr(0, iPos);

	vector<Dot> vecPoints = ReadPoints(strPath + L"\\Contour.txt");
	vector<Dot> vecDP = DouglasPeucker(vecPoints, 0.03);
	WritePoints(strPath + L"\\Contour_DP.txt", vecDP);

	system("pause");
	return 0;
}

//Compute the square of the perpendicular distance of a point to a specific line 
double PerpDist(Dot dotSrc, Dot dotStart, Dot dotEnd)
{
	double dA, dB, dC;
	if (fabs(dotStart.m_x - dotEnd.m_x) < 1.e-7)
	{
		dA = 1.;
		dB = 0.;
		dC = -dotStart.m_x;
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

vector<Dot> ReadPoints(const wstring &strPath)
{
	wifstream fin;
	fin.open(strPath, ios::in);

	vector<Dot> vecPoints;
	double dX, dY, dZ = 0.;
	TCHAR ch;
	//Ignore Z
	//while (fin >> dX >> ch >> dY >> ch >> dZ)
	while (fin >> dX >> ch >> dY)
	//Ignore Z
		vecPoints.push_back(Dot(dX, dY, dZ));

	fin.close();

	return vecPoints;
}

void WritePoints(const wstring &strPath, vector<Dot> vecPoints)
{
	wofstream fout;
	fout.open(strPath, ios::out);

	for (int i = 0; i < (int)vecPoints.size(); i++)
		//Ignore Z
		//fout << vecPoints[i].m_x << "," << vecPoints[i].m_y << "," << vecPoints[i].m_z << endl;
		fout << vecPoints[i].m_x << L"," << vecPoints[i].m_y << endl;
		//Ignore Z

	fout.close();
}
